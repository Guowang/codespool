//#include <iostream>
//#include <stdlib.h>
//#include <cmath>
//
//using namespace std;
//
//
//void merge(double A[], int p, int q,int r){
//	int nL=q-p+1, nR=r-q, i, j, k;
//	double L[16],R[16];
//	for (i=0;i<nL;i++){
//		L[i]=A[p+i];
//	}
//	for (j=0;j<nR;j++){
//		R[j]=A[q+1+j];
//	}
//	//L[i]=1000;
//	//R[j]=1000;
//	i=0;
//	j=0;
//	for (k=p;k<=r;k++){
//		if (i==nL && j<nR){
//			A[k]=R[j];
//			j++;
//		}
//		if (j==nR && i<nL){
//			A[k]=L[i];
//			i++;
//		}
//		if (i<nL && j<nR){
//			if (L[i]<R[j]){
//				A[k]=L[i];
//				i++;
//			}
//			else {
//				A[k]=R[j];
//				j++;
//			}
//		}
//		
//		
//	}
//}
//
//void sort(double A[], int p, int r){
//	/*if (p==r-1){
//		double temp;
//		if (A[p]>A[r]){
//			temp=A[p];
//			A[p]=A[r];
//			A[r]=temp;
//		}
//	}*/
//
//	if (p<r){
//		int q=(p+r)/2;
//		sort(A,p,q);
//		sort(A,q+1,r);
//		merge(A,p,q,r);
//	}
//}
//
//int main(){
//	double A[]={5,2,8,0,9,3,4,7,1,6,10,12,11,15,14,13};
//	int n=sizeof(A)/sizeof(A[0]);
//	int i=0, j=0, k=0;
//	double key=0, smallest=0;
//
//	/*for (j=1;j<n;j++){
//		key=A[j];
//		k=j-1;
//		while (k>=0  && key>A[k]){
//			A[k+1]=A[k];
//			k--;			
//		}
//		A[k+1]=key;
//	}
//*/
//
//	//for (j=0;j<n-1;j++){
//	//	smallest=A[j];
//	//	i=j;
//	//	for (k=j+1;k<n;k++){
//	//		if (smallest>A[k]){
//	//			smallest=A[k];
//	//			i=k;
//	//		}
//	//	}
//	//	key=A[j];
//	//	A[j]=A[i];
//	//	A[i]=key;
//	//}
//	sort(A,0,n-1);
//	//double B[]={1,0};
//	//sort(B,0,1);
//	//cout<<B[0]<<"  "<<B[1]<<endl;
//
//	for (i=0;i<n;i++){
//		cout<<A[i]<<endl;
//	}
//	
//    return 0;
//}