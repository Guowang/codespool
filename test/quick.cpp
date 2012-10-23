//#include <iostream>
//#include <stdlib.h>
//#include <math.h>
//#include <time.h>
//
//using namespace std;
//
//
//int RANDOM (int p, int r){
//	if (p==r){
//		return p;
//	}
//	if (p<r){
//		srand(time(0));
//		int i=rand()%(r-p);
//		return p+i;
//	}
//	else 
//		return 0;
//}
//
//
//int PARTITION (double A[],int p,int r){
//	int i,j;
//	double pivot,temp;
//	pivot=A[r];
//	i=p-1;
//	for (j=p;j<r;j++){
//		if (A[j]<=pivot){
//			i++;
//			if (i!=j){
//				temp=A[i];
//				A[i]=A[j];
//				A[j]=temp;
//			}
//		}
//	}
//	temp=A[i+1];
//	A[i+1]=A[r];
//	A[r]=temp;
//	return i+1;
//}
//
//int RANDOM_PARTITION (double A[],int p, int r){
//	int pivot=RANDOM(p,r);
//	double temp;
//	temp=A[r];
//	A[r]=A[pivot];
//	A[pivot]=temp;
//	return PARTITION(A,p,r);
//}
//
//void QUICKSORT (double A[],int p,int r){
//	if (p<r){
//		int q;
//		q=RANDOM_PARTITION(A,p,r);
//		QUICKSORT(A,p,q-1);
//		QUICKSORT(A,q+1,r);
//	}
//}
//
//void TAIL_RECURSIVE_QUICKSORT (double A[],int p,int r){
//	int q;
//	while (p<r){
//		q=RANDOM_PARTITION(A,p,r);
//		TAIL_RECURSIVE_QUICKSORT(A,p,q-1);
//		p=q+1;
//	}
//		
//
//}
//
//double RANDOMIZED_SELECT (double A[],int p,int r,int i){
//	int q, k;
//	if (p == r)
//		return A[p];
//	q = RANDOM_PARTITION(A,p,r);
//	k = q - p + 1;
//	if (k == i){
//		return A[q];
//	}
//	else if (k < i){
//		return RANDOMIZED_SELECT(A,q+1,r,i-k);
//	}
//	else
//		return RANDOMIZED_SELECT(A,p,q-1,i);
//}
//
//int main(){
//	double A[]={4,1,3,2,5,8,9,7,6,0};
//	double output;
//	int size=sizeof(A)/sizeof(A[0]), i=0;
////	
////	TAIL_RECURSIVE_QUICKSORT(A,0,size-1);
////
////	for (i=0;i<size;i++){
////		cout<<A[i]<<"\t";
////	}
//
//	output = RANDOMIZED_SELECT (A,0,size-1,4);
//	cout<<output<<endl;
//	return 0;
//}