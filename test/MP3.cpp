#define __test__MP3
#ifndef __test__MP3
// MP 3: Due Sunday, Dec 30, 2012 at 11:59 p.m. PST
#include    <wb.h>

#define wbCheck(stmt) do {                                 \
cudaError_t err = stmt;                            \
if (err != cudaSuccess) {                          \
wbLog(ERROR, "Failed to run stmt ", #stmt);    \
return -1;                                     \
}                                                  \
} while(0)
#define TILE_WIDTH 16
#define WIDTH 16
// Compute C = A * B
__global__ void matrixMultiply(float * A, float * B, float * C,
                               int numARows, int numAColumns,
                               int numBRows, int numBColumns,
                               int numCRows, int numCColumns) {
    //@@ Insert code to implement matrix multiplication here
    __shared__ float ds_M[TILE_WIDTH][TILE_WIDTH];
    __shared__ float ds_N[TILE_WIDTH][TILE_WIDTH];
    
    int bx = blockIdx.x;  int by = blockIdx.y;
    int tx = threadIdx.x; int ty = threadIdx.y;
    
    int Row = by * TILE_WIDTH + ty;
    int Col = bx * TILE_WIDTH + tx;
    float Pvalue = 0;
    
  	for (int m = 0; m < (numAColumns - 1) / (float)TILE_WIDTH + 1; ++m) {
    	int i_M = m * TILE_WIDTH + tx;
        int i_N = m * TILE_WIDTH + ty;
        
        if (Row < numARows && i_M < numAColumns)
            ds_M[ty][tx] = A[Row * numAColumns + i_M];
        else
            ds_M[ty][tx] = 0.0;
        
        if (i_N < numBRows && Col < numBColumns)
            ds_N[ty][tx] = B[i_N * numBColumns + Col];
        else
            ds_N[ty][tx] = 0.0;
        
        __syncthreads();
        for (int k = 0; k < TILE_WIDTH; ++k) {
            Pvalue += ds_M[ty][k] * ds_N[k][tx];
        }
        __syncthreads();
  	}
    if (Row < numCRows && Col < numCColumns) {
        C[Row * numCColumns + Col] = Pvalue;
    }
}

int main(int argc, char ** argv) {
    wbArg_t args;
    float * hostA; // The A matrix
    float * hostB; // The B matrix
    float * hostC; // The output C matrix
    float * deviceA;
    float * deviceB;
    float * deviceC;
    int numARows; // number of rows in the matrix A
    int numAColumns; // number of columns in the matrix A
    int numBRows; // number of rows in the matrix B
    int numBColumns; // number of columns in the matrix B
    int numCRows; // number of rows in the matrix C (you have to set this)
    int numCColumns; // number of columns in the matrix C (you have to set this)
    
    args = wbArg_read(argc, argv);
    
    wbTime_start(Generic, "Importing data and creating memory on host");
    hostA = (float *) wbImport(wbArg_getInputFile(args, 0), &numARows, &numAColumns);
    hostB = (float *) wbImport(wbArg_getInputFile(args, 1), &numBRows, &numBColumns);
    //@@ Set numCRows and numCColumns
    numCRows = numARows;
    numCColumns = numBColumns;
    //@@ Allocate the hostC matrix
    hostC = (float *) malloc(numCRows * numCColumns * sizeof(float));
    wbTime_stop(Generic, "Importing data and creating memory on host");
    
    wbLog(TRACE, "The dimensions of A are ", numARows, " x ", numAColumns);
    wbLog(TRACE, "The dimensions of B are ", numBRows, " x ", numBColumns);
    
    wbTime_start(GPU, "Allocating GPU memory.");
    //@@ Allocate GPU memory here
    int n_A = numARows * numAColumns * sizeof(float);
    int n_B = numBRows * numBColumns * sizeof(float);
    int n_C = numCRows * numCColumns * sizeof(float);
  	cudaMalloc((void**) &deviceA, n_A);
  	cudaMalloc((void**) &deviceB, n_B);
  	cudaMalloc((void**) &deviceC, n_C);
    wbTime_stop(GPU, "Allocating GPU memory.");
    
    wbTime_start(GPU, "Copying input memory to the GPU.");
    //@@ Copy memory to the GPU here
	cudaMemcpy(deviceA, hostA, n_A, cudaMemcpyHostToDevice);
    cudaMemcpy(deviceB, hostB, n_B, cudaMemcpyHostToDevice);
    wbTime_stop(GPU, "Copying input memory to the GPU.");
    
    //@@ Initialize the grid and block dimensions here
    dim3 DimGrid((numCColumns - 1) / (float)WIDTH + 1, (numCRows - 1) / (float)WIDTH + 1, 1);
  	dim3 DimBlock(WIDTH, WIDTH, 1);
    wbTime_start(Compute, "Performing CUDA computation");
    //@@ Launch the GPU Kernel here
	matrixMultiply<<<DimGrid, DimBlock>>>(deviceA, deviceB, deviceC,
                                          numARows, numAColumns,
                                          numBRows, numBColumns,
                                          numCRows, numCColumns);
    cudaThreadSynchronize();
    wbTime_stop(Compute, "Performing CUDA computation");
    
    wbTime_start(Copy, "Copying output memory to the CPU");
    //@@ Copy the GPU memory back to the CPU here
	cudaMemcpy(hostC, deviceC, n_C, cudaMemcpyDeviceToHost);
    wbTime_stop(Copy, "Copying output memory to the CPU");
    
    wbTime_start(GPU, "Freeing GPU Memory");
    //@@ Free the GPU memory here
	cudaFree(deviceA);
  	cudaFree(deviceB);
    cudaFree(deviceC);
    wbTime_stop(GPU, "Freeing GPU Memory");
    
    wbSolution(args, hostC, numCRows, numCColumns);
    
    free(hostA);
    free(hostB);
    free(hostC);
    
    return 0;
}



// MP 3: Due Sunday, Dec 30, 2012 at 11:59 p.m. PST
#include    <wb.h>

#define wbCheck(stmt) do {                                 \
cudaError_t err = stmt;                            \
if (err != cudaSuccess) {                          \
wbLog(ERROR, "Failed to run stmt ", #stmt);    \
return -1;                                     \
}                                                  \
} while(0)
#define TILE_WIDTH 16
#define WIDTH 16
// Compute C = A * B
__global__ void matrixMultiply(float * A, float * B, float * C,
                               int numARows, int numAColumns,
                               int numBRows, int numBColumns,
                               int numCRows, int numCColumns) {
    //@@ Insert code to implement matrix multiplication here
    __shared__ float ds_M[TILE_WIDTH][TILE_WIDTH];
    __shared__ float ds_N[TILE_WIDTH][TILE_WIDTH];
    
    int bx = blockIdx.x;  int by = blockIdx.y;
    int tx = threadIdx.x; int ty = threadIdx.y;
    
    int Row = by * TILE_WIDTH + ty;
    int Col = bx * TILE_WIDTH + tx;
    float Pvalue = 0;
    
  	for (int m = 0; m < (numAColumns - 1) / (float)TILE_WIDTH + 1; ++m) {
    	int i_M = m * TILE_WIDTH + tx;
        int i_N = m * TILE_WIDTH + ty;
        
        if (Row < numARows && i_M < numAColumns)
            ds_M[ty][tx] = A[Row * numAColumns + i_M];
        else
            ds_M[ty][tx] = 0.0;
        
        if (i_N < numBRows && Col < numBColumns)
            ds_N[ty][tx] = B[i_N * numBColumns + Col];
        else
            ds_N[ty][tx] = 0.0;
        
        __syncthreads();
        for (int k = 0; k < TILE_WIDTH; ++k) {
            Pvalue += ds_M[ty][k] * ds_N[k][tx];
        }
        __syncthreads();
  	}
    if (Row < numCRows && Col < numCColumns) {
        C[Row * numCColumns + Col] = Pvalue;
    }
}

int main(int argc, char ** argv) {
    wbArg_t args;
    float * hostA; // The A matrix
    float * hostB; // The B matrix
    float * hostC; // The output C matrix
    float * deviceA;
    float * deviceB;
    float * deviceC;
    int numARows; // number of rows in the matrix A
    int numAColumns; // number of columns in the matrix A
    int numBRows; // number of rows in the matrix B
    int numBColumns; // number of columns in the matrix B
    int numCRows; // number of rows in the matrix C (you have to set this)
    int numCColumns; // number of columns in the matrix C (you have to set this)
    
    args = wbArg_read(argc, argv);
    
    wbTime_start(Generic, "Importing data and creating memory on host");
    hostA = (float *) wbImport(wbArg_getInputFile(args, 0), &numARows, &numAColumns);
    hostB = (float *) wbImport(wbArg_getInputFile(args, 1), &numBRows, &numBColumns);
    //@@ Set numCRows and numCColumns
    numCRows = numARows;
    numCColumns = numBColumns;
    //@@ Allocate the hostC matrix
    hostC = (float *) malloc(numCRows * numCColumns * sizeof(float));
    wbTime_stop(Generic, "Importing data and creating memory on host");
    
    wbLog(TRACE, "The dimensions of A are ", numARows, " x ", numAColumns);
    wbLog(TRACE, "The dimensions of B are ", numBRows, " x ", numBColumns);
    
    wbTime_start(GPU, "Allocating GPU memory.");
    //@@ Allocate GPU memory here
    int n_A = numARows * numAColumns * sizeof(float);
    int n_B = numBRows * numBColumns * sizeof(float);
    int n_C = numCRows * numCColumns * sizeof(float);
  	cudaMalloc((void**) &deviceA, n_A);
  	cudaMalloc((void**) &deviceB, n_B);
  	cudaMalloc((void**) &deviceC, n_C);
    wbTime_stop(GPU, "Allocating GPU memory.");
    
    wbTime_start(GPU, "Copying input memory to the GPU.");
    //@@ Copy memory to the GPU here
	cudaMemcpy(deviceA, hostA, n_A, cudaMemcpyHostToDevice);
    cudaMemcpy(deviceB, hostB, n_B, cudaMemcpyHostToDevice);
    wbTime_stop(GPU, "Copying input memory to the GPU.");
    
    //@@ Initialize the grid and block dimensions here
    dim3 DimGrid((numCColumns - 1) / (float)WIDTH + 1, (numCRows - 1) / (float)WIDTH + 1, 1);
  	dim3 DimBlock(WIDTH, WIDTH, 1);
    wbTime_start(Compute, "Performing CUDA computation");
    //@@ Launch the GPU Kernel here
	matrixMultiply<<<DimGrid, DimBlock>>>(deviceA, deviceB, deviceC,
                                          numARows, numAColumns,
                                          numBRows, numBColumns,
                                          numCRows, numCColumns);
    cudaThreadSynchronize();
    wbTime_stop(Compute, "Performing CUDA computation");
    
    wbTime_start(Copy, "Copying output memory to the CPU");
    //@@ Copy the GPU memory back to the CPU here
	cudaMemcpy(hostC, deviceC, n_C, cudaMemcpyDeviceToHost);
    wbTime_stop(Copy, "Copying output memory to the CPU");
    
    wbTime_start(GPU, "Freeing GPU Memory");
    //@@ Free the GPU memory here
	cudaFree(deviceA);
  	cudaFree(deviceB);
    cudaFree(deviceC);
    wbTime_stop(GPU, "Freeing GPU Memory");
    
    wbSolution(args, hostC, numCRows, numCColumns);
    
    free(hostA);
    free(hostB);
    free(hostC);
    
    return 0;
}
#endif