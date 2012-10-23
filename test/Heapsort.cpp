//#include <iostream>
//#include <stdlib.h>
//
//using namespace std;
//
//int PARENT(int i){
//	if (i!=0){
//		int parent;
//		parent=(i+1)/2-1;
//		return parent;
//	}
//}
//
//int LEFT(int i){
//	int left;
//	left=2*i+1;
//	return left;
//}
//
//int RIGHT(int i){
//	int right;
//	right=2*i+2;
//	return right;
//}
//
//void MAX_HEAPIFY(double A[],int i, int heap_size){
//	int l=LEFT(i),r=RIGHT(i),largest;
//	double temp;
//	
//	largest=i;
//
//	if (l<heap_size){
//		if (A[l]>A[i])
//			largest=l;
//	}
//	
//	if (r<heap_size){
//		if (A[r]>A[largest])
//			largest=r;
//	}
//
//	if (largest!=i){
//		temp=A[i];
//		A[i]=A[largest];
//		A[largest]=temp;
//		MAX_HEAPIFY(A,largest,heap_size);
//	}
//}
//
//void BUILD_MAX_HEAP (double A[],int heap_size){
//	int leaf=heap_size/2,i;
//
//	for (i=leaf-1;i>=0;i--){
//		MAX_HEAPIFY(A,i,heap_size);
//	}
//}
//
//double HEAP_MAXIMUM (double A[]){
//	return A[0];
//}
//
//int main(){
//	double A[]={4,1,3,2,16,9,10,14,8,7},temp;
//	int n=sizeof(A)/sizeof(A[0]), i=0,leaf;
//	long double size, two, h;
//	int height,heap_size=n;
//	size=sizeof(A)/sizeof(A[0]);
//	
//	two=2;
//	h=log(size)/log(two);
//	height=h+1;
//
//	BUILD_MAX_HEAP(A,n);
//
//	for (i=n-1;i>0;i--){
//		temp=A[i];
//		A[i]=A[0];
//		A[0]=temp;
//		heap_size--;
//		MAX_HEAPIFY(A,0,heap_size);
//	}
//
//	for (i=0;i<n;i++){
//		cout<<A[i]<<"\t";
//	}
//	cout<<endl;
//	return 0;
//}