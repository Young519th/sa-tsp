//
//  SA_TSP.h
//  SA_TSP
//
//  Created by Young on 6/24/16.
//  Copyright © 2016 杨言. All rights reserved.
//

#ifndef SA_TSP_h
#define SA_TSP_h

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <ctime>
using namespace std;

class SA_TSP{
private:
    int n;
    double* x;
    double* y;
    double** distance;
    int* i0;
    double t0;
    int l0;
    double tf;
    double alpha;
    double beta;
    double getEuclideanDistance(int, int);
    void disturb(int*, int);
    void move_2_Swap(int*, int, double);
    void move_2_Reverse(int*, int, double);
    double adapt;
    double best;
public:
    SA_TSP()
    {
        n = -1;
        t0 = 10000;
        l0 = 15000;
        tf = 0.1;
        alpha = 0.95; //refer to the argument of decreasing temperature
        beta = 1; //refer to the argument of the length of Marcov chains
        adapt = best = 0;
    }
    ~SA_TSP()
    {
        delete[] x;
        delete[] y;
        for (int i = 0 ; i < n ; i ++)
            delete[] distance[i];
        delete[] distance;
    }
    void initTSP();
    void solve();
};

#endif /* SA_TSP_h */
