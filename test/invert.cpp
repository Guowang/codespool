//#include <math.h>
//#include <iostream>
//#include <stdlib.h>
//#include <iomanip>
//#include <fstream>
//
//using namespace std;
//
//
//void merge(int A[], int p, int q,int r,unsigned long count[]){
//	int nL=q-p+1, nR=r-q, i, j, k;
//	int L[60000],R[60000];
//	for (i=0;i<nL;i++){
//		L[i]=A[p+i];
//	}
//	for (j=0;j<nR;j++){
//		R[j]=A[q+1+j];
//	}
//	i=0;
//	j=0;
//	for (k=p;k<=r;k++){
//
//
//		if ((i<nL)&&(j<nR)){		
//			if (L[i]<R[j]){
//				A[k]=L[i];
//				i++;
//			}
//			else {
//				A[k]=R[j];
//				j++;
//				count[0]+=nL-i;
//			}
//		}
//		else if ((i==nL)&&(j<nR)){
//			A[k]=R[j];
//			j++;
//		}
//		else {
//			A[k]=L[i];
//			i++;
//		}
//
//
//	}
//}
//
//void sort(int A[], int p, int r,unsigned long count[]){
//
//	if (p<r){
//		int q=(p+r)/2;
//		sort(A,p,q,count);
//		sort(A,q+1,r,count);
//		merge(A,p,q,r,count);
//	}
//}
//
//int main(){
//
//	int A[100000]={0},i;
//	unsigned long count[2];
//    count[0] = 0;
//
//	ifstream fin("/Users/zishirs/Documents/workspace/test/test/IntegerArray.txt");
//
//	for (i=0;i<100000;++i){
//		fin>>A[i];
//	}
//
//	fin.close();
//
//
//	/*for (i=0;i<100000;++i){
//	for (j=i+1;j<100000;++j){
//	if (A[i]>A[j])
//	count=count+1;
//	}
//	}
//
//	cout<<count<<endl;*/
//
//	sort(A,0,99999,count);
//	cout<<count[0]<<endl;
//    
//    cout<< sizeof(A)/sizeof(A[0]) << endl;
//
//	return 0;
//}