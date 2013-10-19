#define __test__quartic__
#ifndef __test__quartic__

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define STEP 0.00005
#define GAP 1e-6
#define NUM 10

using namespace std;

struct py {
    double_t x, y1, y2;
};

struct px {
    double_t x1, x2, y;
};

struct node {
    double_t x, y;
};


double_t a, b, x_1, y_1, x_2, y_2, x_3, y_3, x_4, y_4, xstart, xend, ystart, yend;

void process();
void divX();
void divY();
void output(double_t, double_t);
py getY(double_t);
px getX(double_t);
double_t dist(double_t, double_t);
double_t getround(double_t);
bool ncomp(node i, node j);


int main() {
    process();
    return 0;
}

void process() {
    cin >> a >> b >> x_1 >> y_1 >> x_2 >> y_2 >> x_3 >> y_3 >> x_4 >> y_4;
    if (x_1 == x_2 && y_1 == y_2 && x_1 == x_3 && y_1 == y_3 && x_3 == x_4 && y_3 == y_4) {
        output(getround(x_1), getround(y_1));
        return;
    }
    if ((x_1 == x_2 && y_1 == y_2)) {
        if (abs(dist(x_1, y_1)) < GAP)
            output(getround(x_1), getround(y_1));
        else
            cout<<"Impossible!"<<endl;
        return;
    }
    if (x_3 == x_4 && y_3 == y_4) {
        double_t d1 = (x_3 - x_1)*(x_3 - x_1) + (y_3 - y_1)*(y_3 - y_1);
        double_t d2 = (x_3 - x_2)*(x_3 - x_2) + (y_3 - y_2)*(y_3 - y_2);
        double_t d = (d1 - a*a*d2)/d1;
        if (abs(d) < GAP)
            output(getround(x_3), getround(y_3));
        else
            cout<<"Impossible!"<<endl;
        return;
    }
    
    double_t pa = (1 - a*a)*(1 - a*a);
    double_t pb = -2*(1 - a*a)*x_1 + 2*(1 - a*a)*a*a*x_2;
    double_t pc = (1-a*a)*(y_1*y_1-a*a*y_2*y_2)-(a*a*y_2-y_1)*(a*a*y_2-y_1)+(1-a*a)*x_1*x_1-(1-a*a)*a*a*x_2*x_2;
    double_t xdet = sqrt(abs(pb*pb - 4*pa*pc));
    xstart = (-pb - xdet)/2/pa;
    xend = (-pb + xdet)/2/pa;
    if (xstart > xend) {
        double_t temp = xstart;
        xstart = xend;
        xend = temp;
    }
    
    double_t qa = (1 - a*a)*(1 - a*a);
    double_t qb = -2*(1 - a*a)*y_1 + 2*(1 - a*a)*a*a*y_2;
    double_t qc = (1-a*a)*(x_1*x_1-a*a*x_2*x_2)-(a*a*x_2-x_1)*(a*a*x_2-x_1)+(1-a*a)*y_1*y_1-(1-a*a)*a*a*y_2*y_2;
    double_t ydet = sqrt(abs(qb*qb - 4*qa*qc));
    ystart = (-qb - ydet)/2/qa;
    yend = (-qb + ydet)/2/qa;
    if (ystart > yend) {
        double_t temp = ystart;
        ystart = yend;
        yend = temp;
    }
    //cout<<xstart<<":"<<xend<<";"<<ystart<<":"<<yend<<endl;
    if (yend - ystart < xend - xstart)
        divX();
    else
        divY();
}

void divX() {
    double_t x = xstart;
    py ycoor = getY(x);
    py prev = ycoor;
    vector<node> v;
    double_t d1, d2;
    for (x = xstart + STEP; x < xend; x += STEP) {
        ycoor = getY(x);
        d1 = dist(ycoor.x, ycoor.y1);
        d2 = dist(ycoor.x, ycoor.y2);
        if (dist(prev.x, prev.y1)*d1 < 0 || (abs(d1) < GAP)) {
            node n;
            n.x = ycoor.x;
            n.y = ycoor.y1;
            v.push_back(n);
        }
        if (dist(prev.x, prev.y2)*d2 < 0 || (abs(d2) < GAP)) {
            node n;
            n.x = ycoor.x;
            n.y = ycoor.y2;
            v.push_back(n);
        }
        prev = ycoor;
    }
    sort(v.begin(), v.end(), ncomp);
    if (v.empty())
        cout<<"Impossible!"<<endl;
    else
        output(v.begin()->x, v.begin()->y);
}

void output(double_t x, double_t y) {
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    std::cout.precision(2);
    cout<< getround(x) <<" "<<getround(y)<<endl;
}

void divY() {
    double_t y = ystart;
    px xcoor = getX(y);
    px prev = xcoor;
    vector<node> v;
    double_t d1, d2;
    for (y = ystart; y < yend; y += STEP) {
        xcoor = getX(y);
        d1 = dist(xcoor.x1, xcoor.y);
        d2 = dist(xcoor.x2, xcoor.y);
        if (dist(prev.x1, prev.y)*d1 < 0 || (abs(d1) < GAP)) {
            node n;
            n.x = xcoor.x1;
            n.y = xcoor.y;
            v.push_back(n);
        }
        if (dist(prev.x2, prev.y)*d2 < 0 || (abs(d2) < GAP)) {
            node n;
            n.x = xcoor.x2;
            n.y = xcoor.y;
            v.push_back(n);
        }
        prev = xcoor;
    }
    sort(v.begin(), v.end(), ncomp);
    if (v.empty())
        cout<<"Impossible!"<<endl;
    else
        output(v.begin()->x, v.begin()->y);
}


py getY(double_t x) {
    double_t pa, pb, pc, det;
    pa = 1 - a*a;
    pb = 2*(a*a*y_2 - y_1);
    pc = y_1*y_1 - a*a*y_2*y_2 + (x - x_1)*(x - x_1) - a*a*(x - x_2)*(x - x_2);
    det = sqrt(abs(pb*pb - 4*pa*pc));
    py ycoor;
    ycoor.x = x;
    ycoor.y1 = (-pb + det)/2/pa;
    ycoor.y2 = (-pb - det)/2/pa;
    return ycoor;
}

px getX(double_t y) {
    double_t pa, pb, pc, det;
    pa = 1 - a*a;
    pb = 2*(a*a*x_2 - x_1);
    pc = x_1*x_1 - a*a*x_2*x_2 + (y - y_1)*(y - y_1) - a*a*(y - y_2)*(y - y_2);
    det = sqrt(abs(pb*pb - 4*pa*pc));
    px xcoor;
    xcoor.y = y;
    xcoor.x1 = (-pb + det)/2/pa;
    xcoor.x2 = (-pb - det)/2/pa;
    return xcoor;
}

double_t dist(double_t x, double_t y) {
    double_t d3 = (x - x_3)*(x - x_3) + (y - y_3)*(y - y_3);
    double_t d4 = (x - x_4)*(x - x_4) + (y - y_4)*(y - y_4);
    if (d3 == 0)
        return d4 == 0;
    double_t d = (d3 - b*b*d4)/d3;
    return d;
}

double_t getround(double_t x) {
    if (abs(x) < 0.005)
        x = 0;
    bool flag = true;
    if (x < 0)
        flag = false;
    int i = abs(x) * 1000;
    if (i%10 < 5) {
        i /= 10;
        if (flag)
            return ((double_t) i)/100;
        return -((double_t) i)/100;
    }
    i /= 10;
    if (flag)
        return ((double_t) i + 1)/100;
    return -((double_t) i + 1)/100;
}

bool ncomp(node i, node j){
    if (abs(i.x - j.x) > NUM*STEP)
        return i.x < j.x;
    return i.y < j.y;
}


#endif /* defined(__test__quartic__) */