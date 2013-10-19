#define __test__MP5__
#ifndef __test__MP5__


#include    <wb.h>

// Check ec2-174-129-21-232.compute-1.amazonaws.com:8080/mp/6 for more information


#define wbCheck(stmt) do {                                 \
cudaError_t err = stmt;                            \
if (err != cudaSuccess) {                          \
wbLog(ERROR, "Failed to run stmt ", #stmt);    \
return -1;                                     \
}                                                  \
} while(0)


#define Mask_width  5
#define Mask_radius (Mask_width/2)

//@@ INSERT CODE HERE
#define TILE_SIZE 16
#define CHANNELS 3

__global__ void convolution_2D_basic_kernel(float *I, const float * __restrict__ K, float *P, int Width, int Height, int W, int H) {
  	__shared__ float N_ds[TILE_SIZE + Mask_width - 1][TILE_SIZE + Mask_width - 1][CHANNELS];
  	int bx = blockIdx.x, by = blockIdx.y;
  	int tx = threadIdx.x, ty = threadIdx.y, tz = threadIdx.z;
  	int ix = bx*TILE_SIZE + tx, iy = by*TILE_SIZE + ty;
  	//map to input
  	int id = (iy*Width + ix)*CHANNELS + tz;
  	int index;
    
  	//top left
  	if (tx < Mask_radius && ty < Mask_radius) {
      	index = id - (Mask_radius*Width + Mask_radius)*CHANNELS;
      	N_ds[tx][ty][tz] = (ix - Mask_radius >= 0 && ix < Width && iy - Mask_radius >= 0 && iy < Height) ? I[index] : 0;
  	}
    
  	//top right
  	if (tx >= TILE_SIZE - Mask_radius && ty < Mask_radius) {
      	index = id - (Mask_radius*Width - Mask_radius)*CHANNELS;
      	N_ds[tx + 2*Mask_radius][ty][tz] = (ix >= 0 && ix + Mask_radius < Width && iy - Mask_radius >= 0 && iy < Height) ? I[index] : 0;
  	}
    
  	//bottom left
  	if (tx < Mask_radius && ty >= TILE_SIZE - Mask_radius) {
      	index = id - (-Mask_radius*Width + Mask_radius)*CHANNELS;
      	N_ds[tx][ty + 2*Mask_radius][tz] = (ix - Mask_radius >= 0 && ix < Width && iy >= 0 && iy + Mask_radius < Height) ? I[index] : 0;
  	}
    
  	//bottom right
  	if (tx >= TILE_SIZE - Mask_radius && ty >= TILE_SIZE - Mask_radius) {
      	index = id - (-Mask_radius*Width - Mask_radius)*CHANNELS;
      	N_ds[tx + 2*Mask_radius][ty + 2*Mask_radius][tz] = (ix >= 0 && ix + 2*Mask_radius < Width && iy >= 0 && iy + Mask_radius < Height) ? I[index] : 0;
  	}
  	
  	//top rows
  	if (ty < Mask_radius) {
      	index = id - (Mask_radius*Width)*CHANNELS;
      	N_ds[tx + Mask_radius][ty][tz] = (ix >= 0 && ix < Width && iy - Mask_radius >= 0 && iy < Height) ? I[index] : 0;
    }
  	
  	//bottom rows
  	if (ty >= TILE_SIZE - Mask_radius) {
      	index = id + (Mask_radius*Width)*CHANNELS;
      	N_ds[tx + Mask_radius][ty + 2*Mask_radius][tz] = (ix >= 0 && ix < Width && iy >= 0 && iy + Mask_radius < Height) ? I[index] : 0;
    }
  	
  	//left cols
  	if (tx < Mask_radius) {
      	index = id - Mask_radius*CHANNELS;
      	N_ds[tx][ty + Mask_radius][tz] = (ix - Mask_radius >= 0 && ix < Width && iy >= 0 && iy < Height) ? I[index] : 0;
    }
    
  	//right cols
  	if (tx >= TILE_SIZE - Mask_radius) {
      	index = id + Mask_radius*CHANNELS;
      	N_ds[tx + 2*Mask_radius][ty + Mask_radius][tz] = (ix >= 0 && ix + Mask_radius < Width && iy >= 0 && iy < Height) ? I[index] : 0;
    }
  	
  	//matrix
  	N_ds[tx + Mask_radius][ty + Mask_radius][tz] = (ix >= 0 && ix < Width && iy >= 0 && iy < Height) ? I[id] : 0;
    
  	__syncthreads();
    
  	float Pval = 0;
  	for (int i = 0; i < Mask_width; ++i) {
      	for (int j = 0; j < Mask_width; ++j) {
           	Pval += N_ds[tx + i][ty + j][tz] * K[i + j*Mask_width];
      	}
  	}
  	
  	if (ix >= 0 && ix < Width && iy >= 0 && iy < Height)
      	P[(iy*Width + ix)*CHANNELS + tz] = min(max(Pval, 0.0), 1.0);
}

int main(int argc, char* argv[]) {
    wbArg_t arg;
    int maskRows;
    int maskColumns;
    int imageChannels;
    int imageWidth;
    int imageHeight;
    char * inputImageFile;
    char * inputMaskFile;
    wbImage_t inputImage;
    wbImage_t outputImage;
    float * hostInputImageData;
    float * hostOutputImageData;
    float * hostMaskData;
    float * deviceInputImageData;
    float * deviceOutputImageData;
    float * deviceMaskData;
    
    arg = wbArg_read(argc, argv); /* parse the input arguments */
    
    inputImageFile = wbArg_getInputFile(arg, 0);
    inputMaskFile = wbArg_getInputFile(arg, 1);
    
    inputImage = wbImport(inputImageFile);
    hostMaskData = (float *) wbImport(inputMaskFile, &maskRows, &maskColumns);
    
    assert(maskRows == 5); /* mask height is fixed to 5 in this mp */
    assert(maskColumns == 5); /* mask width is fixed to 5 in this mp */
    
    imageWidth = wbImage_getWidth(inputImage);
    imageHeight = wbImage_getHeight(inputImage);
    imageChannels = wbImage_getChannels(inputImage);
    
    outputImage = wbImage_new(imageWidth, imageHeight, imageChannels);
    
    hostInputImageData = wbImage_getData(inputImage);
    hostOutputImageData = wbImage_getData(outputImage);
    
    wbTime_start(GPU, "Doing GPU Computation (memory + compute)");
    
    wbTime_start(GPU, "Doing GPU memory allocation");
    cudaMalloc((void **) &deviceInputImageData, imageWidth * imageHeight * imageChannels * sizeof(float));
    cudaMalloc((void **) &deviceOutputImageData, imageWidth * imageHeight * imageChannels * sizeof(float));
    cudaMalloc((void **) &deviceMaskData, maskRows * maskColumns * sizeof(float));
    wbTime_stop(GPU, "Doing GPU memory allocation");
    
    
    wbTime_start(Copy, "Copying data to the GPU");
    cudaMemcpy(deviceInputImageData,
               hostInputImageData,
               imageWidth * imageHeight * imageChannels * sizeof(float),
               cudaMemcpyHostToDevice);
    cudaMemcpy(deviceMaskData,
               hostMaskData,
               maskRows * maskColumns * sizeof(float),
               cudaMemcpyHostToDevice);
    wbTime_stop(Copy, "Copying data to the GPU");
    
    
    wbTime_start(Compute, "Doing the computation on the GPU");
    //@@ INSERT CODE HERE
    int W = (imageWidth - 1) / (float)TILE_SIZE + 1, H = (imageHeight - 1) / (float)TILE_SIZE + 1;
    dim3 DimGrid(W, H, 1);
  	dim3 DimBlock(TILE_SIZE, TILE_SIZE, CHANNELS);
  	convolution_2D_basic_kernel<<<DimGrid, DimBlock>>>(deviceInputImageData, deviceMaskData, deviceOutputImageData, imageWidth, imageHeight, W*TILE_SIZE, H*TILE_SIZE);
    wbTime_stop(Compute, "Doing the computation on the GPU");
	
    
    wbTime_start(Copy, "Copying data from the GPU");
    cudaMemcpy(hostOutputImageData,
               deviceOutputImageData,
               imageWidth * imageHeight * imageChannels * sizeof(float),
               cudaMemcpyDeviceToHost);
    wbTime_stop(Copy, "Copying data from the GPU");
    
    wbTime_stop(GPU, "Doing GPU Computation (memory + compute)");
    
    wbSolution(arg, outputImage);
    
    cudaFree(deviceInputImageData);
    cudaFree(deviceOutputImageData);
    cudaFree(deviceMaskData);
    
    free(hostMaskData);
    wbImage_delete(outputImage);
    wbImage_delete(inputImage);
    
    return 0;
}


#include    <wb.h>

// Check ec2-174-129-21-232.compute-1.amazonaws.com:8080/mp/6 for more information


#define wbCheck(stmt) do {                                 \
cudaError_t err = stmt;                            \
if (err != cudaSuccess) {                          \
wbLog(ERROR, "Failed to run stmt ", #stmt);    \
return -1;                                     \
}                                                  \
} while(0)


#define Mask_width  5
#define Mask_radius (Mask_width/2)

//@@ INSERT CODE HERE
#define TILE_SIZE 16
#define CHANNELS 3

__global__ void convolution_2D_basic_kernel(float *I, const float * __restrict__ K, float *P, int Width, int Height, int W, int H) {
  	__shared__ float N_ds[TILE_SIZE + Mask_width - 1][TILE_SIZE + Mask_width - 1][CHANNELS];
  	int bx = blockIdx.x, by = blockIdx.y;
  	int tx = threadIdx.x, ty = threadIdx.y, tz = threadIdx.z;
  	int ix = bx*TILE_SIZE + tx, iy = by*TILE_SIZE + ty;
  	//map to input
  	int id = (iy*W + ix)*CHANNELS + tz;
  	int index;
    
  	//top left
  	if (tx < Mask_radius && ty < Mask_radius) {
      	index = id - (Mask_radius*W + Mask_radius)*CHANNELS;
      	N_ds[tx][ty][tz] = (ix - Mask_radius >= 0 && ix < W && iy - Mask_radius >= 0 && iy < H) ? I[index] : 0;
  	}
    
  	//top right
  	if (tx >= TILE_SIZE - Mask_radius && ty < Mask_radius) {
      	index = id - (Mask_radius*W - Mask_radius)*CHANNELS;
      	N_ds[tx + 2*Mask_radius][ty][tz] = (ix >= 0 && ix + Mask_radius < W && iy - Mask_radius >= 0 && iy < H) ? I[index] : 0;
  	}
    
  	//bottom left
  	if (tx < Mask_radius && ty >= TILE_SIZE - Mask_radius) {
      	index = id - (-Mask_radius*W + Mask_radius)*CHANNELS;
      	N_ds[tx][ty + 2*Mask_radius][tz] = (ix - Mask_radius >= 0 && ix < W && iy >= 0 && iy + Mask_radius < H) ? I[index] : 0;
  	}
    
  	//bottom right
  	if (tx >= TILE_SIZE - Mask_radius && ty >= TILE_SIZE - Mask_radius) {
      	index = id - (-Mask_radius*W - Mask_radius)*CHANNELS;
      	N_ds[tx + 2*Mask_radius][ty + 2*Mask_radius][tz] = (ix >= 0 && ix + 2*Mask_radius < W && iy >= 0 && iy + Mask_radius < H) ? I[index] : 0;
  	}
  	
  	//matrix
  	N_ds[tx + Mask_radius][ty + Mask_radius][tz] = (ix >= 0 && ix < W && iy >= 0 && iy < H) ? I[id] : 0;
    
  	__syncthreads();
    
  	float Pval = 0;
  	for (int i = 0; i < Mask_width; ++i) {
      	for (int j = 0; j < Mask_width; ++j) {
          	Pval += N_ds[tx + i][ty + j][tz] * K[i + j*Mask_width];
      	}
  	}
  	
  	if (ix >= 0 && ix < W && iy >= 0 && iy < H)
      	P[id] = Pval;
}

int main(int argc, char* argv[]) {
    wbArg_t arg;
    int maskRows;
    int maskColumns;
    int imageChannels;
    int imageWidth;
    int imageHeight;
    char * inputImageFile;
    char * inputMaskFile;
    wbImage_t inputImage;
    wbImage_t outputImage;
    float * hostInputImageData;
    float * hostOutputImageData;
    float * hostMaskData;
    float * deviceInputImageData;
    float * deviceOutputImageData;
    float * deviceMaskData;
    
    arg = wbArg_read(argc, argv); /* parse the input arguments */
    
    inputImageFile = wbArg_getInputFile(arg, 0);
    inputMaskFile = wbArg_getInputFile(arg, 1);
    
    inputImage = wbImport(inputImageFile);
    hostMaskData = (float *) wbImport(inputMaskFile, &maskRows, &maskColumns);
    
    assert(maskRows == 5); /* mask height is fixed to 5 in this mp */
    assert(maskColumns == 5); /* mask width is fixed to 5 in this mp */
    
    imageWidth = wbImage_getWidth(inputImage);
    imageHeight = wbImage_getHeight(inputImage);
    imageChannels = wbImage_getChannels(inputImage);
    
    outputImage = wbImage_new(imageWidth, imageHeight, imageChannels);
    
    hostInputImageData = wbImage_getData(inputImage);
    hostOutputImageData = wbImage_getData(outputImage);
    
    wbTime_start(GPU, "Doing GPU Computation (memory + compute)");
    
    wbTime_start(GPU, "Doing GPU memory allocation");
    cudaMalloc((void **) &deviceInputImageData, imageWidth * imageHeight * imageChannels * sizeof(float));
    cudaMalloc((void **) &deviceOutputImageData, imageWidth * imageHeight * imageChannels * sizeof(float));
    cudaMalloc((void **) &deviceMaskData, maskRows * maskColumns * sizeof(float));
    wbTime_stop(GPU, "Doing GPU memory allocation");
    
    
    wbTime_start(Copy, "Copying data to the GPU");
    cudaMemcpy(deviceInputImageData,
               hostInputImageData,
               imageWidth * imageHeight * imageChannels * sizeof(float),
               cudaMemcpyHostToDevice);
    cudaMemcpy(deviceMaskData,
               hostMaskData,
               maskRows * maskColumns * sizeof(float),
               cudaMemcpyHostToDevice);
    wbTime_stop(Copy, "Copying data to the GPU");
    
    
    wbTime_start(Compute, "Doing the computation on the GPU");
    //@@ INSERT CODE HERE
    int W = (imageWidth - 1) / (float)TILE_SIZE + 1, H = (imageHeight - 1) / (float)TILE_SIZE + 1;
    dim3 DimGrid(W, H, 1);
  	dim3 DimBlock(TILE_SIZE, TILE_SIZE, CHANNELS);
  	convolution_2D_basic_kernel<<<DimGrid, DimBlock>>>(deviceInputImageData, deviceMaskData, deviceOutputImageData, imageWidth, imageHeight, W, H);
    wbTime_stop(Compute, "Doing the computation on the GPU");
	
    
    wbTime_start(Copy, "Copying data from the GPU");
    cudaMemcpy(hostOutputImageData,
               deviceOutputImageData,
               imageWidth * imageHeight * imageChannels * sizeof(float),
               cudaMemcpyDeviceToHost);
    wbTime_stop(Copy, "Copying data from the GPU");
    
    wbTime_stop(GPU, "Doing GPU Computation (memory + compute)");
    
    wbSolution(arg, outputImage);
    
    cudaFree(deviceInputImageData);
    cudaFree(deviceOutputImageData);
    cudaFree(deviceMaskData);
    
    free(hostMaskData);
    wbImage_delete(outputImage);
    wbImage_delete(inputImage);
    
    return 0;
}


#include    <wb.h>

// Check ec2-174-129-21-232.compute-1.amazonaws.com:8080/mp/6 for more information


#define wbCheck(stmt) do {                                 \
cudaError_t err = stmt;                            \
if (err != cudaSuccess) {                          \
wbLog(ERROR, "Failed to run stmt ", #stmt);    \
return -1;                                     \
}                                                  \
} while(0)


#define Mask_width  5
#define Mask_radius (Mask_width/2)

//@@ INSERT CODE HERE
#define TILE_SIZE 16
#define CHANNELS 3

__global__ void convolution_2D_basic_kernel(float *I, const float * __restrict__ K, float *P, int Width, int Height) {
  	
}

int main(int argc, char* argv[]) {
    wbArg_t arg;
    int maskRows;
    int maskColumns;
    int imageChannels;
    int imageWidth;
    int imageHeight;
    char * inputImageFile;
    char * inputMaskFile;
    wbImage_t inputImage;
    wbImage_t outputImage;
    float * hostInputImageData;
    float * hostOutputImageData;
    float * hostMaskData;
    float * deviceInputImageData;
    float * deviceOutputImageData;
    float * deviceMaskData;
    
    arg = wbArg_read(argc, argv); /* parse the input arguments */
    
    inputImageFile = wbArg_getInputFile(arg, 0);
    inputMaskFile = wbArg_getInputFile(arg, 1);
    
    inputImage = wbImport(inputImageFile);
    hostMaskData = (float *) wbImport(inputMaskFile, &maskRows, &maskColumns);
    
    assert(maskRows == 5); /* mask height is fixed to 5 in this mp */
    assert(maskColumns == 5); /* mask width is fixed to 5 in this mp */
    
    imageWidth = wbImage_getWidth(inputImage);
    imageHeight = wbImage_getHeight(inputImage);
    imageChannels = wbImage_getChannels(inputImage);
    
    outputImage = wbImage_new(imageWidth, imageHeight, imageChannels);
    
    hostInputImageData = wbImage_getData(inputImage);
    hostOutputImageData = wbImage_getData(outputImage);
    
    wbTime_start(GPU, "Doing GPU Computation (memory + compute)");
    
    wbTime_start(GPU, "Doing GPU memory allocation");
    cudaMalloc((void **) &deviceInputImageData, imageWidth * imageHeight * imageChannels * sizeof(float));
    cudaMalloc((void **) &deviceOutputImageData, imageWidth * imageHeight * imageChannels * sizeof(float));
    cudaMalloc((void **) &deviceMaskData, maskRows * maskColumns * sizeof(float));
    wbTime_stop(GPU, "Doing GPU memory allocation");
    
    
    wbTime_start(Copy, "Copying data to the GPU");
    cudaMemcpy(deviceInputImageData,
               hostInputImageData,
               imageWidth * imageHeight * imageChannels * sizeof(float),
               cudaMemcpyHostToDevice);
    cudaMemcpy(deviceMaskData,
               hostMaskData,
               maskRows * maskColumns * sizeof(float),
               cudaMemcpyHostToDevice);
    wbTime_stop(Copy, "Copying data to the GPU");
    
    
    wbTime_start(Compute, "Doing the computation on the GPU");
    //@@ INSERT CODE HERE
    dim3 DimGrid((imageWidth - 1) / (float)TILE_SIZE + 1, (imageHeight - 1) / (float)TILE_SIZE + 1, 1);
  	dim3 DimBlock(TILE_SIZE, TILE_SIZE, CHANNELS);
  	convolution_2D_basic_kernel<<<DimGrid, DimBlock>>>(deviceInputImageData, deviceMaskData, deviceOutputImageData, imageWidth, imageHeight);
    wbTime_stop(Compute, "Doing the computation on the GPU");
	
    
    wbTime_start(Copy, "Copying data from the GPU");
    cudaMemcpy(hostOutputImageData,
               deviceOutputImageData,
               imageWidth * imageHeight * imageChannels * sizeof(float),
               cudaMemcpyDeviceToHost);
    wbTime_stop(Copy, "Copying data from the GPU");
    
    wbTime_stop(GPU, "Doing GPU Computation (memory + compute)");
    
    wbSolution(arg, outputImage);
    
    cudaFree(deviceInputImageData);
    cudaFree(deviceOutputImageData);
    cudaFree(deviceMaskData);
    
    free(hostMaskData);
    wbImage_delete(outputImage);
    wbImage_delete(inputImage);
    
    return 0;
}












// MP 5 Scan
// Given a list (lst) of length n
// Output its prefix sum = {lst[0], lst[0] + lst[1], lst[0] + lst[1] + ... + lst[n-1]}
// Due Tuesday, January 22, 2013 at 11:59 p.m. PST

#include    <wb.h>

#define BLOCK_SIZE 512 //@@ You can change this

#define wbCheck(stmt) do {                                 \
cudaError_t err = stmt;                            \
if (err != cudaSuccess) {                          \
wbLog(ERROR, "Failed to run stmt ", #stmt, "Error: ", cudaGetErrorString(err));    \
return -1;                                     \
}                                                  \
} while(0)

__global__ void sumup(float *output, float *blocksum, int len) {
  	int t = threadIdx.x;
  	int start = blockIdx.x*blockDim.x;
  	if (blockIdx.x > 0 && t + start < len) {
      	output[t + start] += blocksum[blockIdx.x - 1];
    }
}

__global__ void scan(float * input, float * output, int len, float *blocksum) {
    //@@ Modify the body of this function to complete the functionality of
    //@@ the scan on the device
    //@@ You may need multiple kernel calls; write your kernels before this
    //@@ function and call them from here
    __shared__ float scan_array[BLOCK_SIZE];
  	int t = threadIdx.x;
  	int start = blockIdx.x*blockDim.x;
  	if (t + start < len) {
      	scan_array[t] = input[t + start];
  	}
  	else {
      	scan_array[t] = 0;
    }
  	__syncthreads();
  	int stride = 1;
  	while (stride < BLOCK_SIZE){
      	int index = (t + 1)*2*stride - 1;
      	if (index < BLOCK_SIZE) {
          	scan_array[index] += scan_array[index - stride];
      	}
      	stride <<= 1;
      	__syncthreads();
    }
  	for (stride = BLOCK_SIZE/4; stride > 0; stride >>= 1) {
      	int index = (t + 1)*2*stride - 1;
      	if (index + stride < BLOCK_SIZE) {
          	scan_array[index + stride] += scan_array[index];
        }
      	__syncthreads();
    }
  	__syncthreads();
  	if (t + start < len)
      	output[t + start] = scan_array[t];
  	blocksum[blockIdx.x] = scan_array[BLOCK_SIZE - 1];
}

int main(int argc, char ** argv) {
    wbArg_t args;
    float * hostInput; // The input 1D list
    float * hostOutput; // The output list
    float * deviceInput;
    float * deviceOutput;
    int numElements; // number of elements in the list
    
    args = wbArg_read(argc, argv);
    
    wbTime_start(Generic, "Importing data and creating memory on host");
    hostInput = (float *) wbImport(wbArg_getInputFile(args, 0), &numElements);
    hostOutput = (float*) malloc(numElements * sizeof(float));
    wbTime_stop(Generic, "Importing data and creating memory on host");
    
    wbLog(TRACE, "The number of input elements in the input is ", numElements);
    
    wbTime_start(GPU, "Allocating GPU memory.");
    wbCheck(cudaMalloc((void**)&deviceInput, numElements*sizeof(float)));
    wbCheck(cudaMalloc((void**)&deviceOutput, numElements*sizeof(float)));
    wbTime_stop(GPU, "Allocating GPU memory.");
    
    wbTime_start(GPU, "Clearing output memory.");
    wbCheck(cudaMemset(deviceOutput, 0, numElements*sizeof(float)));
    wbTime_stop(GPU, "Clearing output memory.");
    
    wbTime_start(GPU, "Copying input memory to the GPU.");
    wbCheck(cudaMemcpy(deviceInput, hostInput, numElements*sizeof(float), cudaMemcpyHostToDevice));
    wbTime_stop(GPU, "Copying input memory to the GPU.");
    
    //@@ Initialize the grid and block dimensions here
    int numBlock = (numElements - 1) / (float)BLOCK_SIZE + 1;
  	float *hostsum = (float*) malloc(numBlock*sizeof(float));
  	float *devicesum;
  	wbCheck(cudaMalloc((void**)&devicesum, numBlock*sizeof(float)));
	dim3 DimGrid(numBlock, 1, 1);
  	dim3 DimBlock(BLOCK_SIZE, 1, 1);
  	
    wbTime_start(Compute, "Performing CUDA computation");
    //@@ Modify this to complete the functionality of the scan
    //@@ on the deivce
	scan<<<DimGrid, DimBlock>>>(deviceInput, deviceOutput, numElements, devicesum);
  	wbCheck(cudaMemcpy(hostsum, devicesum, numBlock*sizeof(float), cudaMemcpyDeviceToHost));
  	for (int ii = 1; ii < numBlock; ++ii)
      	hostsum[ii] += hostsum[ii - 1];
  	wbCheck(cudaMemcpy(devicesum, hostsum, numBlock*sizeof(float), cudaMemcpyHostToDevice));
  	sumup<<<DimGrid, DimBlock>>>(deviceOutput, devicesum, numElements);
    cudaDeviceSynchronize();
    wbTime_stop(Compute, "Performing CUDA computation");
    
    wbTime_start(Copy, "Copying output memory to the CPU");
    wbCheck(cudaMemcpy(hostOutput, deviceOutput, numElements*sizeof(float), cudaMemcpyDeviceToHost));
    wbTime_stop(Copy, "Copying output memory to the CPU");
    
    wbTime_start(GPU, "Freeing GPU Memory");
    cudaFree(deviceInput);
    cudaFree(deviceOutput);
  	cudaFree(devicesum);
    wbTime_stop(GPU, "Freeing GPU Memory");
    
    wbSolution(args, hostOutput, numElements);
    
    free(hostInput);
    free(hostOutput);
  	free(hostsum);
    
    return 0;
}

/*
 * Copyright 1993-2009 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation and
 * any modifications thereto.  Any use, reproduction, disclosure, or distribution
 * of this software and related documentation without an express license
 * agreement from NVIDIA Corporation is strictly prohibited.
 *
 */

#ifndef _SCAN_BEST_KERNEL_CU_
#define _SCAN_BEST_KERNEL_CU_

// Define this to more rigorously avoid bank conflicts,
// even at the lower (root) levels of the tree
// Note that due to the higher addressing overhead, performance
// is lower with ZERO_BANK_CONFLICTS enabled.  It is provided
// as an example.
//#define ZERO_BANK_CONFLICTS

// 16 banks on G80
#define NUM_BANKS 16
#define LOG_NUM_BANKS 4

#ifdef ZERO_BANK_CONFLICTS
#define CONFLICT_FREE_OFFSET(index) ((index) >> LOG_NUM_BANKS + (index) >> (2*LOG_NUM_BANKS))
#else
#define CONFLICT_FREE_OFFSET(index) ((index) >> LOG_NUM_BANKS)
#endif

///////////////////////////////////////////////////////////////////////////////
// Work-efficient compute implementation of scan, one thread per 2 elements
// Work-efficient: O(log(n)) steps, and O(n) adds.
// Also shared storage efficient: Uses n + n/NUM_BANKS shared memory -- no ping-ponging
// Also avoids most bank conflicts using single-element offsets every NUM_BANKS elements.
//
// In addition, If ZERO_BANK_CONFLICTS is defined, uses
//     n + n/NUM_BANKS + n/(NUM_BANKS*NUM_BANKS)
// shared memory. If ZERO_BANK_CONFLICTS is defined, avoids ALL bank conflicts using
// single-element offsets every NUM_BANKS elements, plus additional single-element offsets
// after every NUM_BANKS^2 elements.
//
// Uses a balanced tree type algorithm.  See Blelloch, 1990 "Prefix Sums
// and Their Applications", or Prins and Chatterjee PRAM course notes:
// https://www.cs.unc.edu/~prins/Classes/633/Handouts/pram.pdf
//
// This work-efficient version is based on the algorithm presented in Guy Blelloch's
// excellent paper "Prefix sums and their applications".
// http://www.cs.cmu.edu/~blelloch/papers/Ble93.pdf
//
// Pro: Work Efficient, very few bank conflicts (or zero if ZERO_BANK_CONFLICTS is defined)
// Con: More instructions to compute bank-conflict-free shared memory addressing,
// and slightly more shared memory storage used.
//

template <bool isNP2>
__device__ void loadSharedChunkFromMem(float *s_data,
                                       const float *g_idata,
                                       int n, int baseIndex,
                                       int& ai, int& bi,
                                       int& mem_ai, int& mem_bi,
                                       int& bankOffsetA, int& bankOffsetB)
{
    int thid = threadIdx.x;
    mem_ai = baseIndex + threadIdx.x;
    mem_bi = mem_ai + blockDim.x;
    
    ai = thid;
    bi = thid + blockDim.x;
    
    // compute spacing to avoid bank conflicts
    bankOffsetA = CONFLICT_FREE_OFFSET(ai);
    bankOffsetB = CONFLICT_FREE_OFFSET(bi);
    
    // Cache the computational window in shared memory
    // pad values beyond n with zeros
    s_data[ai + bankOffsetA] = g_idata[mem_ai];
    
    if (isNP2) // compile-time decision
    {
        s_data[bi + bankOffsetB] = (bi < n) ? g_idata[mem_bi] : 0;
    }
    else
    {
        s_data[bi + bankOffsetB] = g_idata[mem_bi];
    }
}

template <bool isNP2>
__device__ void storeSharedChunkToMem(float* g_odata,
                                      const float* s_data,
                                      int n,
                                      int ai, int bi,
                                      int mem_ai, int mem_bi,
                                      int bankOffsetA, int bankOffsetB)
{
    __syncthreads();
    
    // write results to global memory
    g_odata[mem_ai] = s_data[ai + bankOffsetA];
    if (isNP2) // compile-time decision
    {
        if (bi < n)
            g_odata[mem_bi] = s_data[bi + bankOffsetB];
    }
    else
    {
        g_odata[mem_bi] = s_data[bi + bankOffsetB];
    }
}

template <bool storeSum>
__device__ void clearLastElement(float* s_data,
                                 float *g_blockSums,
                                 int blockIndex)
{
    if (threadIdx.x == 0)
    {
        int index = (blockDim.x << 1) - 1;
        index += CONFLICT_FREE_OFFSET(index);
        
        if (storeSum) // compile-time decision
        {
            // write this block's total sum to the corresponding index in the blockSums array
            g_blockSums[blockIndex] = s_data[index];
        }
        
        // zero the last element in the scan so it will propagate back to the front
        s_data[index] = 0;
    }
}



__device__ unsigned int buildSum(float *s_data)
{
    unsigned int thid = threadIdx.x;
    unsigned int stride = 1;
    
    // build the sum in place up the tree
    for (int d = blockDim.x; d > 0; d >>= 1)
    {
        __syncthreads();
        
        if (thid < d)
        {
            int i  = __mul24(__mul24(2, stride), thid);
            int ai = i + stride - 1;
            int bi = ai + stride;
            
            ai += CONFLICT_FREE_OFFSET(ai);
            bi += CONFLICT_FREE_OFFSET(bi);
            
            s_data[bi] += s_data[ai];
        }
        
        stride *= 2;
    }
    
    return stride;
}

__device__ void scanRootToLeaves(float *s_data, unsigned int stride)
{
    unsigned int thid = threadIdx.x;
    
    // traverse down the tree building the scan in place
    for (int d = 1; d <= blockDim.x; d *= 2)
    {
        stride >>= 1;
        
        __syncthreads();
        
        if (thid < d)
        {
            int i  = __mul24(__mul24(2, stride), thid);
            int ai = i + stride - 1;
            int bi = ai + stride;
            
            ai += CONFLICT_FREE_OFFSET(ai);
            bi += CONFLICT_FREE_OFFSET(bi);
            
            float t  = s_data[ai];
            s_data[ai] = s_data[bi];
            s_data[bi] += t;
        }
    }
}

template <bool storeSum>
__device__ void prescanBlock(float *data, int blockIndex, float *blockSums)
{
    int stride = buildSum(data);               // build the sum in place up the tree
    clearLastElement<storeSum>(data, blockSums,
                               (blockIndex == 0) ? blockIdx.x : blockIndex);
    scanRootToLeaves(data, stride);            // traverse down tree to build the scan
}

template <bool storeSum, bool isNP2>
__global__ void prescan(float *g_odata,
                        const float *g_idata,
                        float *g_blockSums,
                        int n,
                        int blockIndex,
                        int baseIndex)
{
    int ai, bi, mem_ai, mem_bi, bankOffsetA, bankOffsetB;
    extern __shared__ float s_data[];
    
    // load data into shared memory
    loadSharedChunkFromMem<isNP2>(s_data, g_idata, n,
                                  (baseIndex == 0) ?
                                  __mul24(blockIdx.x, (blockDim.x << 1)):baseIndex,
                                  ai, bi, mem_ai, mem_bi,
                                  bankOffsetA, bankOffsetB);
    // scan the data in each block
    prescanBlock<storeSum>(s_data, blockIndex, g_blockSums);
    // write results to device memory
    storeSharedChunkToMem<isNP2>(g_odata, s_data, n,
                                 ai, bi, mem_ai, mem_bi,
                                 bankOffsetA, bankOffsetB);
}


__global__ void uniformAdd(float *g_data,
                           float *uniforms,
                           int n,
                           int blockOffset,
                           int baseIndex)
{
    __shared__ float uni;
    if (threadIdx.x == 0)
        uni = uniforms[blockIdx.x + blockOffset];
    
    unsigned int address = __mul24(blockIdx.x, (blockDim.x << 1)) + baseIndex + threadIdx.x;
    
    __syncthreads();
    
    // note two adds per thread
    g_data[address]              += uni;
    g_data[address + blockDim.x] += (threadIdx.x + blockDim.x < n) * uni;
}


#endif // #ifndef _SCAN_BEST_KERNEL_CU_

/*
 * Copyright 1993-2009 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation and
 * any modifications thereto.  Any use, reproduction, disclosure, or distribution
 * of this software and related documentation without an express license
 * agreement from NVIDIA Corporation is strictly prohibited.
 *
 */

#ifdef _WIN32
#  define NOMINMAX
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cutil_inline.h>

// includes, kernels
#include <scan.cu>  // defines prescanArray()

////////////////////////////////////////////////////////////////////////////////
// declaration, forward
void runTest( int argc, char** argv);

// regression test functionality
extern "C"
unsigned int compare( const float* reference, const float* data,
                     const unsigned int len);
extern "C"
void computeGold( float* reference, float* idata, const unsigned int len);

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int
main( int argc, char** argv)
{
    runTest( argc, argv);
    cutilExit(argc, argv);
}

////////////////////////////////////////////////////////////////////////////////
//! Run a scan test for CUDA
////////////////////////////////////////////////////////////////////////////////
void
runTest( int argc, char** argv)
{
    // use command-line specified CUDA device, otherwise use device with highest Gflops/s
    if( cutCheckCmdLineFlag(argc, (const char**)argv, "device") )
        cutilDeviceInit(argc, argv);
    else
        cudaSetDevice( cutGetMaxGflopsDeviceId() );
    
#ifndef __DEVICE_EMULATION__
    unsigned int num_test_iterations = 100;
    unsigned int num_elements = 1000000; // can support large, non-power-of-2 arrays!
#else
    unsigned int num_test_iterations = 1;
    unsigned int num_elements = 10000; // can support large, non-power-of-2 arrays!
#endif
    
    cutGetCmdLineArgumenti( argc, (const char**) argv, "n", (int*)&num_elements);
    cutGetCmdLineArgumenti( argc, (const char**) argv, "i", (int*)&num_test_iterations);
    
    unsigned int mem_size = sizeof( float) * num_elements;
    
    unsigned int timerGPU, timerCPU;
    cutilCheckError(cutCreateTimer(&timerCPU));
    cutilCheckError(cutCreateTimer(&timerGPU));
    
    // allocate host memory to store the input data
    float* h_data = (float*) malloc( mem_size);
    
    // initialize the input data on the host
    for( unsigned int i = 0; i < num_elements; ++i)
    {
        h_data[i] = 1.0f;//(int)(10 * rand()/32768.f);
    }
    
    // compute reference solution
    float* reference = (float*) malloc( mem_size);
    cutStartTimer(timerCPU);
    for (unsigned int i = 0; i < num_test_iterations; i++)
    {
        computeGold( reference, h_data, num_elements);
    }
    cutStopTimer(timerCPU);
    
    // allocate device memory input and output arrays
    float* d_idata = NULL;
    float* d_odata = NULL;
    
    cutilSafeCall( cudaMalloc( (void**) &d_idata, mem_size));
    cutilSafeCall( cudaMalloc( (void**) &d_odata, mem_size));
    
    // copy host memory to device input array
    cutilSafeCall( cudaMemcpy( d_idata, h_data, mem_size, cudaMemcpyHostToDevice) );
    // initialize all the other device arrays to be safe
    cutilSafeCall( cudaMemcpy( d_odata, h_data, mem_size, cudaMemcpyHostToDevice) );
    
    printf("Running parallel prefix sum (prescan) of %d elements\n", num_elements);
    printf("This version is work efficient (O(n) adds)\n");
    printf("and has very few shared memory bank conflicts\n\n");
    
    preallocBlockSums(num_elements);
    
    // run once to remove startup overhead
    prescanArray(d_odata, d_idata, num_elements);
    
    
    // Run the prescan
    cutStartTimer(timerGPU);
    for (unsigned int i = 0; i < num_test_iterations; i++)
    {
        //printf("prescanArray\n");
        prescanArray(d_odata, d_idata, num_elements);
    }
    cutStopTimer(timerGPU);
    
    deallocBlockSums();
    
    // copy result from device to host
    cutilSafeCall(cudaMemcpy( h_data, d_odata, sizeof(float) * num_elements,
                             cudaMemcpyDeviceToHost));
    
    // If this is a regression test write the results to a file
    if( cutCheckCmdLineFlag( argc, (const char**) argv, "regression"))
    {
        // write file for regression test
        cutWriteFilef( "./data/result.dat", h_data, num_elements, 0.0);
    }
    else
    {
        // custom output handling when no regression test running
        // in this case check if the result is equivalent to the expected soluion
        unsigned int result_regtest = cutComparef( reference, h_data, num_elements);
        printf( "Test %s\n", (1 == result_regtest) ? "PASSED" : "FAILED");
        printf( "Average GPU execution time: %f ms\n", cutGetTimerValue(timerGPU) / num_test_iterations);
        printf( "CPU execution time:         %f ms\n", cutGetTimerValue(timerCPU) / num_test_iterations);
    }
    
    printf("\nCheck out the CUDA Data Parallel Primitives Library for more on scan.\n");
    printf("http://www.gpgpu.org/developer/cudpp\n");
    
    // cleanup memory
    cutDeleteTimer(timerCPU);
    cutDeleteTimer(timerGPU);
    free( h_data);
    free( reference);
    cudaFree( d_odata);
    cudaFree( d_idata);
    
    cudaThreadExit();
}


#endif /* defined(__test__MP5__) */