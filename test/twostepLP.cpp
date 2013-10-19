#define twostepLP
#ifndef twostepLP
#include <iostream>
#include <vector>
#include <climits>
 
using namespace std;
/*
100 10
1 11 5
10 21 5
20 31 5
30 41 5
40 51 5
50 61 5
60 71 5
70 81 5
80 91 5
90 100 5
12 3
1 5 3
4 8 3
7 12 3
*/

double max_simplex_LP(vector<vector<double> >& matrix, vector<int>& cval, int N, int M);
double min_two_step_LP(vector<vector<double> >& matrix, int N, int M);

int main(){
    int N, M;
    cin >> N >> M;
    vector<vector<double> > minM(M + N + 1, vector<double>(3*N + M + 1, 0)), maxM(M + N, vector<double>(3*N + M + 1, 0));
    vector<int> maxC(3*N + M, 0);
    int a, b, c;
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> c;
        a -= 1;
        b -= 1;
        for (int m = a; m <= b; m++) {
            maxM[i][m] = 1;
            minM[i][m] = 1;
        }
        maxM[i][3*N + M] = c;
        maxM[i][i + 2*N] = 1;
        minM[i][3*N + M] = c;
        minM[i][i + 2*N] = 1;
    }
    for (int i = M; i < N + M; i++) {
        maxC[i - M] = 1;
        maxM[i][i - M] = 1;
        maxM[i][i - M + N] = 1;
        maxM[i][3*N + M] = 1;
    }
    for (int i = 0; i < N; i++) {
        minM[i + M][i] = 1;
        minM[i + M][i + N] = 1;
        minM[i + M][i + 2*N + M] = 1;
        minM[i + M][3*N + M] = 1;
        minM[N + M][i] = 1;
    }
    /*
    cout<<"\nminM"<<endl;
    for (int i = 0; i <= M + N; i++) {
        for (int j = 0; j <= 3*N + M; j++) {
            cout<<minM[i][j]<<"  ";
        }
        cout<<endl;
    }
    cout<<endl;
    */
    cout<<static_cast<int>(min_two_step_LP(minM, N, M)) << " " ;
    cout<< static_cast<int>(max_simplex_LP(maxM, maxC, N, M)) <<endl;
    /*
    cout<<"\nminM"<<endl;
    for (int i = 0; i <= M+N; i++) {
        for (int j = 0; j <= 3*N + M; j++) {
            cout<<minM[i][j]<<"'";
        }
        cout<<endl;
    }
    */
    return 0;
}
 
double max_simplex_LP(vector<vector<double> >& matrix, vector<int>& cval, int N, int M){
    vector<double> r(3*N + M, 0);
    vector<double> c(3*N + M, 0);
    vector<int> basis(N + M), nonbasis(2*N);
    for (int i = 0; i < N + M; i++) {
        basis[i] = i + 2*N;
        c[i + 2*N] = 1;
    }
    for (int i = 0; i < 2*N; i++)
        nonbasis[i] = i;
    bool flag = true, allpositive = true;
    int enterindex, leaveindex;
    double entermin;
    while (flag) {
        flag = false;
        //calc zj and rj and set flag
        allpositive = true;
        for (int j = 0; j < 2*N; j++) {
            double zj = 0;
            int jindex = nonbasis[j];
            for (int k = 0; k < N + M; k++) {
                int kindex = basis[k];
                zj += c[kindex] * matrix[k][jindex];
            }
            r[jindex] = c[jindex] - zj;
            //calc which to enter basis
            if (r[jindex] < 0 && allpositive) {
                enterindex = j;
                entermin = r[jindex];
                allpositive = false;
            }
            if(r[jindex] < 0 && entermin > r[jindex]) {
                enterindex = j;
                entermin = r[jindex];
            }
        }
        if (allpositive) {
            break;
        }
        else
            flag = true;
        //calc which to leave basis
        bool unbounded = true;
        double rmin;
        for (int k = 0; k < N + M; k++) {
            int enteri = nonbasis[enterindex];
            if (matrix[k][enteri] > 0) {
                double div = matrix[k][3*N + M] / matrix[k][enteri];
                if (unbounded) {
                    rmin = div;
                    leaveindex = k;
                }
                else if (rmin > div) {
                    rmin = div;
                    leaveindex = k;
                }
                else if (rmin == div && leaveindex > k) {
                    leaveindex = k;
                }
                unbounded = false;
            }
        }
        if (!unbounded) {
            //Gaussian elimination
            int enteri = nonbasis[enterindex];
            double d = matrix[leaveindex][enteri];
            for (int i = 0; i <= 3*N + M; i++)
                matrix[leaveindex][i] /= d;
            for (int i = 0; i < N + M; i++) {
                if (i != leaveindex && matrix[i][enteri] != 0) {
                    double pivot = matrix[i][enteri];
                    for (int j = 0; j <= 3*N + M; j++) {
                        matrix[i][j] -= pivot * matrix[leaveindex][j];
                    }
                }
            }
            //update basis and nonbasis
            int newbasis = nonbasis[enterindex], newnonbasis = basis[leaveindex];
            nonbasis[enterindex] = newnonbasis;
            basis[leaveindex] = newbasis;
        }
        else
            break;
    }
    //calc z0
    double z0 = 0;
    for (int k = 0; k < N + M; k++) {
        z0 += cval[basis[k]] * matrix[k][3*N + M];
    }
    return z0;
}

///*
double min_two_step_LP(vector<vector<double> >& matrix, int N, int M){
    vector<double> r(3*N + M, 0);
    vector<double> c(3*N + M, 0);
    vector<int> basis(M + N), nonbasis(2*N);
    for (int i = 0; i < M + N; i++) {
        basis[i] = i + 2*N;
        c[i + 2*N] = 1;
    }
    for (int i = 0; i < 2*N; i++)
        nonbasis[i] = i;
    //Phase I: get r non negative
    bool rpositive = false, unbounded = true;
    while (!rpositive) {
        int enterindex, leaveindex;
        double entermin;
        rpositive = true;
        //calc zj and rj
        for (int j = 0; j < 2*N; j++) {
            double zj = 0;
            int jindex = nonbasis[j];
            for (int k = 0; k < M + N; k++) {
                int kindex = basis[k];
                zj += c[kindex] * matrix[k][jindex];
            }
            r[jindex] = c[jindex] - zj;
            //calc which to enter basis
            if (r[jindex] < 0 && rpositive) {
                enterindex = j;
                entermin = r[jindex];
                rpositive = false;
            }
            if(!rpositive && r[jindex] < 0 && entermin > r[jindex]) {
                enterindex = j;
                entermin = r[jindex];
            }
        }
        if (rpositive)
            break;
        //calc which to leave basis
        unbounded = true;
        double rmin;
        for (int k = 0; k < M + N; k++) {
            int enteri = nonbasis[enterindex];
            if (matrix[k][enteri] > 0) {
                double div = matrix[k][3*N + M] / matrix[k][enteri];
                if (unbounded) {
                    rmin = div;
                    leaveindex = k;
                }
                if (!unbounded && rmin > div) {
                    rmin = div;
                    leaveindex = k;
                }
                if (!unbounded && rmin == div && leaveindex > k) {
                    leaveindex = k;
                }
                unbounded = false;
            }
        }
        if (!unbounded) {
            //Gaussian elimination
            int enteri = nonbasis[enterindex];
            double d = matrix[leaveindex][enteri];
            for (int i = 0; i <= 3*N + M; i++)
                matrix[leaveindex][i] /= d;
            for (int i = 0; i <= M + N; i++) {
                if (i != leaveindex && matrix[i][enteri] != 0) {
                    double pivot = matrix[i][enteri];
                    for (int j = 0; j <= 3*N + M; j++) {
                        matrix[i][j] -= pivot * matrix[leaveindex][j];
                    }
                }
            }
            //update basis and nonbasis
            int newbasis = nonbasis[enterindex], newnonbasis = basis[leaveindex];
            nonbasis[enterindex] = newnonbasis;
            basis[leaveindex] = newbasis;
        }
        else
            break;
    }
    /*
    cout<<"\nphase I minM: "<<endl;
    for (int i = 0; i <= M+N; i++) {
        for (int j = 0; j <= 3*N + M; j++) {
            cout<<matrix[i][j]<<"'";
        }
        cout<<endl;
    }
    cout<<"\nbasis: ";
    for (int i = 0; i < 2*N; i++) {
        cout<<basis[i]<<" ";
    }
    cout<<"\nr: ";
    for (int i = 0; i < 2*N; i++) {
        cout<<r[i]<<" ";
    }
    cout<<"\nphase I: "<< -matrix[N + M][3*N + M]<<endl;
    */
    //Phase II:
    vector<int> cval(2*N, 0);
    for (int i = 0; i < N; i++) {
        cval[i] = 1;
    }
    rpositive = false, unbounded = true;
    while (!rpositive) {
        int enterindex, leaveindex;
        double entermin;
        rpositive = true;
        //calc zj and rj
        for (int j = 0; j < 2*N; j++) {
            double zj = 0;
            int jindex = nonbasis[j];
            for (int k = 0; k < M + N; k++) {
                int kindex = basis[k];
                if (jindex < 2*N && kindex < 2*N) {
                    zj += cval[kindex] * matrix[k][jindex];
                }
            }
            if (jindex < 2*N)
                r[jindex] = cval[jindex] - zj;
            //calc which to enter basis
            if (jindex < 2*N && r[jindex] < 0 && rpositive) {
                enterindex = j;
                entermin = r[jindex];
                rpositive = false;
            }
            if(!rpositive && jindex < 2*N && r[jindex] < 0 && entermin > r[jindex]) {
                enterindex = j;
                entermin = r[jindex];
            }
        }
        if (rpositive)
            break;
        //calc which to leave basis
        unbounded = true;
        double rmin;
        for (int k = 0; k < M + N; k++) {
            int enteri = nonbasis[enterindex];
            if (enteri < 2*N && matrix[k][enteri] > 0) {
                double div = matrix[k][3*N + M] / matrix[k][enteri];
                if (unbounded) {
                    rmin = div;
                    leaveindex = k;
                }
                if (!unbounded && rmin > div) {
                    rmin = div;
                    leaveindex = k;
                }
                if (!unbounded && rmin == div && leaveindex > k) {
                    leaveindex = k;
                }
                unbounded = false;
            }
        }
        if (!unbounded) {
            //Gaussian elimination
            int enteri = nonbasis[enterindex];
            double d = matrix[leaveindex][enteri];
            for (int i = 0; i <= 3*N + M; i++)
                matrix[leaveindex][i] /= d;
            for (int i = 0; i <= M + N; i++) {
                if (i != leaveindex && matrix[i][enteri] != 0) {
                    double pivot = matrix[i][enteri];
                    for (int j = 0; j <= 3*N + M; j++) {
                        matrix[i][j] -= pivot * matrix[leaveindex][j];
                    }
                }
            }
            //update basis and nonbasis
            int newbasis = nonbasis[enterindex], newnonbasis = basis[leaveindex];
            nonbasis[enterindex] = newnonbasis;
            basis[leaveindex] = newbasis;
        }
        else
            break;
    }
    //calc z0
    double z0 = 0;
    for (int k = 0; k < N + M; k++) {
        z0 += cval[basis[k]] * matrix[k][3*N + M];
    }
    return z0;
}
#endif