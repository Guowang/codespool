#define __test__SuffixArray__
#ifndef __test__SuffixArray__

#include <iostream>
#include <string.h>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
#define maxn 200000
char t[maxn], p[maxn];
int WA[maxn],WB[maxn],WV[maxn],WS[maxn], r[maxn];

int cmp(int *r,int a,int b,int l){return r[a]==r[b]&&r[a+l]==r[b+l];}

void da(int *r,int *sa,int n,int m)
{
    int i,j,p,*x=WA,*y=WB,*t;
    for(i=0;i<m;i++) WS[i]=0;
    for(i=0;i<n;i++) WS[x[i]=r[i]]++;
    for(i=1;i<m;i++) WS[i]+=WS[i-1];
    for(i=n-1;i>=0;i--) sa[--WS[x[i]]]=i;
    for(j=1,p=1;p<n;j*=2,m=p)
    {
        for(p=0,i=n-j;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0;i<n;i++) WV[i]=x[y[i]];
        for(i=0;i<m;i++) WS[i]=0;
        for(i=0;i<n;i++) WS[WV[i]]++;
        for(i=1;i<m;i++) WS[i]+=WS[i-1];
        for(i=n-1;i>=0;i--) sa[--WS[WV[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
    return;
}
int sa[maxn],RANK[maxn],height[maxn];
void calheight(int *r,int *sa,int n)
{
    int i,j,k=0;
    for(i=1;i<=n;i++) RANK[sa[i]]=i;
    for(i=0;i<n;height[RANK[i++]]=k)
        for(k?k--:0,j=sa[RANK[i]-1];r[i+k]==r[j+k];k++);
    return;
}
int RMQ[maxn];
int mm[maxn];
int best[30][maxn];
void initRMQ(int n)
{
    int i,j,a,b;
    for(mm[0]=-1,i=1;i<=n;i++)
        mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
    for(i=1;i<=n;i++) best[0][i]=i;
    for(i=1;i<=mm[n];i++)
        for(j=1;j<=n+1-(1<<i);j++)
        {
            a=best[i-1][j];
            b=best[i-1][j+(1<<(i-1))];
            if(RMQ[a]<RMQ[b]) best[i][j]=a;
            else best[i][j]=b;
        }
    return;
}
int askRMQ(int a,int b)
{
    int t;
    t=mm[b-a+1];b-=(1<<t)-1;
    a=best[t][a];b=best[t][b];
    return RMQ[a]<RMQ[b]?a:b;
}
int lcp(int a,int b)
{
    int t;
    a=RANK[a];b=RANK[b];
    if(a>b) {t=a;a=b;b=t;}
    return(height[askRMQ(a+1,b)]);
}

void solve() {
    scanf("%s", t);
    scanf("%s", p);
    string dump;
    getline(cin, dump);
    getline(cin, dump);
    int tlen = strlen(t), plen = strlen(p);
    int n = tlen + plen;
    
    if (plen > tlen)
        printf("\n");
        else if (plen == 1) {
            for (int i = 0; i < n - plen; i++)
                printf("%d ", i);
            printf("\n");
        }
        else {
            for (int i=0;i<plen;i++) r[i]=static_cast<int>(p[i]);
            for (int i=plen;i<n;i++) r[i]=static_cast<int>(t[i-plen]);
            r[n]=0;
            da(r,sa,n+1,256);
            calheight(r,sa,n);
            for(int i=1;i<=n;i++) RMQ[i]=height[i];
            initRMQ(n);
            
//            for (int i = 0; i <= n; ++i)
//                printf ("%d, %d, %d\n", sa[i], RANK[i], height[i]);
            
            for (int i = plen; i <= n - plen; i++) {
                int matched = lcp(0, i);
                if (matched >= plen)
                    printf("%d ",(i-plen));
                else {
                    int index = matched + 1;
                    if (lcp(index, i + index) >= plen - matched - 1)
                        printf("%d ",(i-plen));
                }
            }
            printf("\n");
        }
}

// Begins Suffix Arrays implementation
// O(n log n) - Manber and Myers algorithm
// Refer to "Suffix arrays: A new method for on-line string searches",
// by Udi Manber and Gene Myers

//Usage:
// Fill str with the characters of the string.
// Call SuffixSort(n), where n is the length of the string stored in str.
// That's it!

//Output:
// pos = The suffix array. Contains the n suffixes of str sorted in lexicographical order.
//       Each suffix is represented as a single integer (the position of str where it starts).
// rank = The inverse of the suffix array. rank[i] = the index of the suffix str[i..n)
//        in the pos array. (In other words, pos[i] = k <==> rank[k] = i)
//        With this array, you can compare two suffixes in O(1): Suffix str[i..n) is smaller
//        than str[j..n) if and only if rank[i] < rank[j]

int str[N]; //input
int rank[N], pos[N]; //output
int cnt[N], next[N]; //internal
bool bh[N], b2h[N];

// Compares two suffixes according to their first characters
bool smaller_first_char(int a, int b){
    return str[a] < str[b];
}

void suffixSort(int n){
    //sort suffixes according to their first characters
    for (int i=0; i<n; ++i){
        pos[i] = i;
    }
    sort(pos, pos + n, smaller_first_char);
    //{pos contains the list of suffixes sorted by their first character}
    
    for (int i=0; i<n; ++i){
        bh[i] = i == 0 || str[pos[i]] != str[pos[i-1]];
        b2h[i] = false;
    }
    
    for (int h = 1; h < n; h <<= 1){
        //{bh[i] == false if the first h characters of pos[i-1] == the first h characters of pos[i]}
        int buckets = 0;
        for (int i=0, j; i < n; i = j){
            j = i + 1;
            while (j < n && !bh[j]) j++;
            next[i] = j;
            buckets++;
        }
        if (buckets == n) break; // We are done! Lucky bastards!
        //{suffixes are separted in buckets containing strings starting with the same h characters}
        
        for (int i = 0; i < n; i = next[i]){
            cnt[i] = 0;
            for (int j = i; j < next[i]; ++j){
                rank[pos[j]] = i;
            }
        }
        
        cnt[rank[n - h]]++;
        b2h[rank[n - h]] = true;
        for (int i = 0; i < n; i = next[i]){
            for (int j = i; j < next[i]; ++j){
                int s = pos[j] - h;
                if (s >= 0){
                    int head = rank[s];
                    rank[s] = head + cnt[head]++;
                    b2h[rank[s]] = true;
                }
            }
            for (int j = i; j < next[i]; ++j){
                int s = pos[j] - h;
                if (s >= 0 && b2h[rank[s]]){
                    for (int k = rank[s]+1; !bh[k] && b2h[k]; k++) b2h[k] = false;
                }
            }
        }
        for (int i=0; i<n; ++i){
            pos[rank[i]] = i;
            bh[i] |= b2h[i];
        }
    }
    for (int i=0; i<n; ++i){
        rank[pos[i]] = i;
    }
}
// End of suffix array algorithm


// Begin of the O(n) longest common prefix algorithm
// Refer to "Linear-Time Longest-Common-Prefix Computation in Suffix
// Arrays and Its Applications" by Toru Kasai, Gunho Lee, Hiroki
// Arimura, Setsuo Arikawa, and Kunsoo Park.
int height[N];
// height[i] = length of the longest common prefix of suffix pos[i] and suffix pos[i-1]
// height[0] = 0
void getHeight(int n){
    for (int i=0; i<n; ++i) rank[pos[i]] = i;
    height[0] = 0;
    for (int i=0, h=0; i<n; ++i){
        if (rank[i] > 0){
            int j = pos[rank[i]-1];
            while (i + h < n && j + h < n && str[i+h] == str[j+h]) h++;
            height[rank[i]] = h;
            if (h > 0) h--;
        }
    }
}
// End of longest common prefixes algorithm

int main() {
    /*
     int T;
     cin>>T;
     for (int count = 0; count < T; count++)
     solve();
     */
    
    return 0;
}

#endif