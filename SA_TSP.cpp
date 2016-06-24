//
//  SA_TSP.cpp
//  SA_TSP
//
//  Created by Young on 6/24/16.
//  Copyright © 2016 杨言. All rights reserved.
//

#include "SA_TSP.h"

double SA_TSP::getEuclideanDistance(int i, int j)
{
    //to get the distance between city i and j
    return sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
}

void SA_TSP::disturb(int* i, int n)
{
    //to random the order of the solution
    for (int k = 0 ; k < n ; k ++)
    {
        int t = rand() % (n - k) + k;
        int temp = i[k];
        i[k] = i[t];
        i[t] = temp;
    }
}

void SA_TSP::move_2_Swap(int * i, int n, double t)
{
    //to choose x and y, exchange their positions directly
    int x = rand() % n;
    int y = rand() % n;
    int xl = x - 1;
    int xr = x + 1;
    int yl = y - 1;
    int yr = y + 1;
    if (xl < 0)
        xl = n - 1;
    if (yl < 0)
        yl = n - 1;
    if (xr > n - 1)
        xr = 0;
    if (yr > n - 1)
        yr = 0;
    double newAdapt = 0;
    int tmp = i[x];
    i[x] = i[y];
    i[y] = tmp;
    for (int t = 0 ; t < n - 1 ;  t ++)
        newAdapt += distance[i[t]][i[t + 1]];
    newAdapt += distance[n - 1][0];
    if (newAdapt <= adapt)
    {
        adapt = newAdapt;
        if (adapt < best)
            best = adapt;
    }
    else
    {
        if (exp((adapt - newAdapt) / t) > ((double)rand() / RAND_MAX))
        {
            adapt = newAdapt;
        }
        else
        {
            int tmp = i[x];
            i[x] = i[y];
            i[y] = tmp;
        }
    }
}

void SA_TSP::move_2_Reverse(int * i, int n, double t)
{
    //to choose x and y, reverse all the link between x and y
    int x = rand() % n;
    int y = rand() % n;
    if (x >= y)
    {
        //make sure that x < y
        int tmp = x;
        x = y;
        y = tmp;
    }
    double newAdapt = 0;
    int* tmp = new int[y - x + 1];
    for (int t = 0 ; t < y - x + 1 ; t ++)
        tmp[t] = i[y - t];
    for (int t = 0 ; t < y - x + 1 ; t ++)
        i[x + t] = tmp[t];
    delete[] tmp;
    for (int t = 0 ; t < n - 1 ; t ++)
        newAdapt += distance[i[t]][i[t + 1]];
    newAdapt += distance[i[n - 1]][i[0]];
    if (newAdapt <= adapt)
    {
        adapt = newAdapt;
        if (adapt < best)
            best = adapt;
    }
    else
    {
        if (exp((adapt - newAdapt) / t) > ((double)rand() / RAND_MAX))
        {
            adapt = newAdapt;
        }
        else
        {
            int* tmp = new int[y - x + 1];
            for (int t = 0 ; t < y - x + 1 ; t ++)
                tmp[t] = i[y - t];
            for (int t = 0 ; t < y - x + 1 ; t ++)
                i[x + t] = tmp[t];
            delete[] tmp;
        }
    }
}

void SA_TSP::initTSP()
{
    //configure the TSP problem, must run once and only once
    if (n != -1)
        return;
    srand((unsigned)time(0));
    cout << "The total number of cities:";
    cin >> n;
    if (n <= 0)
        return;
    x = new double[n];
    y = new double[n];
    distance = new double* [n];
    for (int i = 0 ; i < n ; i ++)
        distance[i] = new double[n];
    for (int i = 0 ; i < n ; i ++)
    {
        cout << "CITY " << i << " :";
        cin >> x[i] >> y[i];
    }
    for (int i = 0 ; i < n ; i ++)
        for (int j = 0 ; j < n ; j ++)
        {
            distance[i][j] = getEuclideanDistance(i, j);
        }
    cout << "TSP start!" << endl;
}

void SA_TSP::solve()
{
    //solve the TSP problem with configured model
    i0 = new int[n];
    for (int i = 0 ; i < n ; i ++)
        i0[i] = i;
    disturb(i0, n);
    for (int i = 0 ; i < n - 1 ; i ++)
        adapt += distance[i0[i]][i0[i + 1]];
    adapt += distance[i0[n - 1]][i0[0]];
    best = adapt;
    double t = t0;
    int l = l0;
    while (t > tf)
    {
        for (int k = 0 ; k < l ; k ++)
        {
            move_2_Reverse(i0, n, t);//you can choose the neighbor function you want, for example, move_2_Swap
        }
        l = l * beta;
        t = t * alpha;
    }
    cout << "The path is ";
    for (int i = 0 ; i < n - 1 ; i ++)
    {
        cout << i0[i] << "-";
    }
    cout << i0[n - 1] << endl;
    cout << "The cost is " << adapt << endl;
    cout << "The least cost appeared in the process is " << best << endl;
    delete[] i0;
}