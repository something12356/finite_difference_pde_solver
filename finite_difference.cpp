#include <vector>
#include <cmath>
#include <iostream>
#include <Eigen/Dense>
#include "finite_difference.h"
using namespace std;

// Assumes square (or cube, hypercube, etc) grid with length grid_size
// Converts to a linearly indexed set of coordinates: 0, ..., N-1, N where N is number of points in grid
// (So N = pow(grid_size, dim))
int linear_indexing(const std::vector<size_t>& idxs, int dim, int grid_size){
    int lin_idx {0};
    for (int i {}; i < dim; i++){
        lin_idx += idxs[i]*pow(grid_size, i);
    }
    
    return lin_idx;
}

std::vector<size_t> normal_indexing(int lin_idx, int dim, int grid_size){
    std::vector<size_t> idxs(dim);
    for (int i {}; i < dim; i++) {
        idxs[i] = lin_idx % grid_size;
        lin_idx = lin_idx / grid_size;
    }

    return idxs;
}

bool chk_bdry_pt(int i, int dim, int grid_size){
    bool bdry {false};
    std::vector<size_t> idxs(normal_indexing(i, dim, grid_size));
    for (int i: idxs){
        if (i == 0 || i == grid_size - 1) bdry = true;
    }

    return bdry;
}

/*This constructs the Laplacian matrix using a generalised version of the stencil from the 5-point method:
(   1  )
(1 -4 1)
(   1  )
for higher dimensions.
Returns 1 if target is adjacent to centre, and -2*dim if target is the centre, 
where dim is the number of dimensions we're solving Poisson's equation in
Returns 0 otherwise.*/
Eigen::MatrixXd laplacian_constructor(int dim, int grid_size){
    Eigen::MatrixXd laplacian(pow(grid_size, dim), (pow(grid_size, dim)));
    
    // Construct the laplacian row by row
    // It will be an NxN matrix where N = grid_size*grid_size
    // Future improvement: Make it MxN where M = number of free points
    for (int i {}; i < pow(grid_size, dim); i++){
        if (!chk_bdry_pt(i, dim, grid_size)) { // Ensures we won't be trying to access points outside the grid
            std::vector<size_t> idxs = normal_indexing(i, dim, grid_size); // The coordinates of the grid point for this row
            laplacian(i, i) = -4.0; // Set the diagonal entry to -4

            for (int j {}; j < dim; j++) {
                std::vector<size_t> adj_id(idxs);
                adj_id[j]++; // A node that is adjacent to a grid point has exactly one index changed from it
                laplacian(i, linear_indexing(adj_id, dim, grid_size)) = 1.0;

                adj_id[j] = adj_id[j] - 2; // Also need to consider the same index but -1
                laplacian(i, linear_indexing(adj_id, dim, grid_size)) = 1.0;
            }
        }
    }
    // Convert to Eigen matrix


    return laplacian;
}

std::vector<int> solution(std::vector<int> bdry_conds, int dim, int grid_size){
    std::vector<int> soln(pow(grid_size, dim));

    return soln;
}