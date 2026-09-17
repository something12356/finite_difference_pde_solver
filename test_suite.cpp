#include <iostream>
#include "finite_difference.h"
using namespace std;

// Check laplacian constructor produces correct matrix

// Test linear_indexing function
void test_lin_idx(){
    std::vector<size_t> idxs {2, 1};
    cout << "Testing (2,1) on 3x3 grid\n" << linear_indexing(idxs, 2, 3) << '\n';

    std::vector<size_t> idxs2 {1, 3, 4};
    cout << "Testing (1, 3, 4) on 5x5x5 grid\n" << linear_indexing(idxs2, 3, 5) << '\n';
}

void test_norm_idx(){
    cout << "Testing lin_idx=5 on 3x3 grid\n";
    std::vector<size_t> idxs(normal_indexing(5, 2, 3));
    for (int i {}; i < 2; i++){
        cout << idxs[i] << ',';
    }
    cout << '\n';

    cout << "Testing lin_idx=116 on 5x5x5 grid\n";
    std::vector<size_t> idxs2(normal_indexing(116, 3, 5));
    for (int i {}; i < 3; i++){
        cout << idxs2[i] << ',';
    }
    cout << '\n';
}

void test_laplacian_constructor(){
    vector<vector<int>> L(laplacian_constructor(2, 4));
    for (vector<int> row: L) {
        for (int x: row) {
            cout << x << ',';
        }
        cout << '\n';
    }

}

void run_all_tests(){
    test_lin_idx();
    test_norm_idx();
    test_laplacian_constructor();
}