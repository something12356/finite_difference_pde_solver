#include <Python.h>

#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "finite_difference.h"
#include "test_suite.h"
using namespace std;

// The functions used to produce the image in the README
double bdry_fn(std::vector<double> x) {
    return -7*sin(M_PI*(x[0]+x[1]));
}

double source(std::vector<double> x) {
    double a = x[0]-1;
    double b = x[1]-1;
    return a/(abs(b)+0.01);
}

int main(){
    bool test = false; // TODO: Change into command line arg
    if (test) run_all_tests();

    // Solves laplacian(phi) = source
    // With Direchlet boundary condition phi = bdry_fn on the boundary of the domain
    int dim = 2;
    double resolution = 0.1;
    vector<double> limits = {2.0, 2.0};

    ofstream solution;
    solution.open("solution.txt");
    solution << dim << endl;

    for (vector<double> vec: solver(bdry_fn, source, dim, resolution, limits)) {
        for (double x: vec)  {
            solution << x << ',';
        }
        solution << endl;
    }
    solution.close();

    FILE* graphing_script = fopen("../plotter/plot.py", "r");
    Py_Initialize();
    PyRun_SimpleFile(graphing_script, "../plotter/plot.py");
    fclose(graphing_script);
    Py_Finalize();


    return 0;
}