#include <vector>
#include <cmath>
#include <iostream>
#include "finite_difference.h"
#include "test_suite.h"
using namespace std;

double bdry_fn(std::vector<double> x) {
    return sin(x[0])+cos(x[1]);
}

double source(std::vector<double>) {
    return 0.0;
}

int main(){
    bool test = false; // TODO: Change into command line arg
    if (test) run_all_tests();

    std::vector<int> limits {1, 1};
    cout << solver(bdry_fn, source, 2, 0.1, {1, 1});

    return 0;
}