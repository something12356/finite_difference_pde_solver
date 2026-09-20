#include <iostream>
#include "../Eigen/Dense"
#include "finite_difference.h"
using namespace std;

// Check laplacian constructor produces correct matrix

// Test linear_indexing function
void test_lin_idx(){
    std::vector<int> idxs {2, 1};
    int phase = pow(3, 2);
    cout << "Testing (2,1) on 3x3 grid\n" << linear_indexing(idxs, 2, 3, phase) << '\n';

    std::vector<int> idxs2 {1, 3, 4};
    phase = pow(5, 3);
    cout << "Testing (1, 3, 4) on 5x5x5 grid\n" << linear_indexing(idxs2, 3, 5, phase) << '\n';
}

void test_norm_idx(){
    cout << "Testing lin_idx=5 on 3x3 grid\n";
    std::vector<int> idxs(normal_indexing(5, 2, 3));
    for (int i {}; i < 2; i++){
        cout << idxs[i] << ',';
    }
    cout << '\n';

    cout << "Testing lin_idx=116 on 5x5x5 grid\n";
    std::vector<int> idxs2(normal_indexing(116, 3, 5));
    for (int i {}; i < 3; i++){
        cout << idxs2[i] << ',';
    }
    cout << '\n';
}

void test_laplacian_constructor(){
    int phase = pow(4, 2);
    Eigen::MatrixXd L(construct_laplacian(2, 4, phase));
    std::cout << "Hi?\n";
    for (int i {0}; i < 16; i++){
        for (int j {0}; j < 16; j++){
            cout << L(i, j);
        }
        std:cout << '\n';
    }

}

void run_all_tests(){
    test_lin_idx();
    test_norm_idx();
    test_laplacian_constructor();
}