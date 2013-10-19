#define __test__maxCCMinPQ__
#ifndef __test__maxCCMinPQ__
#include <iostream>
using namespace std;

struct grid {
    int i;
    int j;
};

int maxCC();
bool inBound(int, int, int&, int&);
bool lessH(grid &, grid &, int **);
void exch(grid *, int &,int, int);
void insert(grid *, int &, int, int, bool **, int ** map);
grid delMin(grid *, int &, int **);
void sink(grid *, int &, int, int **);
void swim(grid *, int &, int, int **);

int main() {
    cout << maxCC();
    return 0;
}

int maxCC(){
    int W, H;
    cin >> W >> H;
    int ** map = new int*[H];
    bool ** status = new bool*[H];
    for (int i = 0; i < H; i++) {
        map[i] = new int[W];
        status[i] = new bool[W];
    }
    grid * edgeMinPQ = new grid[H * W + 1];
    int size = 0;
    for (int i = 0; i < H; i++) 
        for (int j = 0; j < W; j++) {
            cin >> map[i][j];
            status[i][j] = false;
        }
    
    for (int i = 0; i < H; i += H - 1)
        for (int j = 0; j < W; j++)
            insert(edgeMinPQ, size, i, j, status, map);
    
    for (int i = 1; i < H - 1; i ++)
        for (int j = 0; j < W; j += W - 1)
            insert(edgeMinPQ, size, i, j, status, map);
    
    int numofProcessed = 0;
    int sum = 0;
    int totalnum = (H - 2) * (W - 2);
    grid localmin;
    int locali, localj, localh;
    while (numofProcessed < totalnum) {
        localmin = delMin(edgeMinPQ, size, map);
        locali = localmin.i;
        localj = localmin.j;
        localh = map[locali][localj];
        if (inBound(locali - 1, localj, H, W))
            if (!status[locali - 1][localj]) {
                if (map[locali - 1][localj] < localh) {
                    sum += localh - map[locali - 1][localj];
                    map[locali - 1][localj] = localh;
                }
                insert(edgeMinPQ, size, locali - 1, localj, status, map);
                numofProcessed++;
            }
        
        if (inBound(locali + 1, localj, H, W))
            if (!status[locali + 1][localj]) {
                if (map[locali + 1][localj] < localh) {
                    sum += localh - map[locali + 1][localj];
                    map[locali + 1][localj] = localh;
                }
                insert(edgeMinPQ, size, locali + 1, localj, status, map);
                numofProcessed++;
            }
        
        if (inBound(locali, localj - 1, H, W))
            if (!status[locali][localj - 1]) {
                if (map[locali][localj - 1] < localh) {
                    sum += localh - map[locali][localj - 1];
                    map[locali][localj - 1] = localh;
                }
                insert(edgeMinPQ, size, locali, localj - 1, status, map);
                numofProcessed++;
            }
        
        if (inBound(locali, localj + 1, H, W))
            if (!status[locali][localj + 1]) {
                if (map[locali][localj + 1] < localh) {
                    sum += localh - map[locali][localj + 1];
                    map[locali][localj + 1] = localh;
                }
                insert(edgeMinPQ, size, locali, localj + 1, status, map);
                numofProcessed++;
            }
    }
    
    for (int i = 0; i < H; i++) {
        delete[] map[i];
        delete[] status[i];
    }
    delete[] map;
    delete[] status;
    return sum;
}

bool inBound(int i, int j, int& H, int& W) {
    if (i < 0 || i >= H)
        return false;
    if (j < 0 || j >= W)
        return false;
    return true;
}

bool lessH(grid & p, grid & q, int ** map) {
    if (map[p.i][p.j] < map[q.i][q.j])
        return true;
    return false;
}

void exch(grid * edgeMinPQ, int & size, int p, int q) {
    grid temp = edgeMinPQ[p];
    edgeMinPQ[p] = edgeMinPQ[q];
    edgeMinPQ[q] = temp;
}

void sink(grid * edgeMinPQ, int & size, int k, int ** map) {
    int j;
    while (2 * k <= size) {
        j = 2 * k;
        if (j + 1 <= size && lessH(edgeMinPQ[j + 1], edgeMinPQ[j], map))
            j++;
        if (lessH(edgeMinPQ[k], edgeMinPQ[j], map))
            break;
        exch(edgeMinPQ, size, k, j);
        k = j;
    }
}

void swim(grid * edgeMinPQ, int & size, int k, int ** map) {
    while (k > 1 && lessH(edgeMinPQ[k], edgeMinPQ[k / 2], map)) {
        exch(edgeMinPQ, size, k, k / 2);
        k = k / 2;
    }
}

void insert(grid * edgeMinPQ, int & size, int i, int j, bool ** status, int ** map) {
    status[i][j] = true;
    grid temp;
    temp.i = i;
    temp.j = j;
    edgeMinPQ[++size] = temp;
    swim(edgeMinPQ, size, size, map);
}

grid delMin(grid * edgeMinPQ, int & size, int ** map) {
    exch(edgeMinPQ, size, 1, size);
    grid temp = edgeMinPQ[size--];
    sink(edgeMinPQ, size, 1, map);
    return temp;
}
#endif