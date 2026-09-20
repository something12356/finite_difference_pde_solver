#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "Eigen/Dense"
#include "finite_difference.h"
using namespace std;

struct Grid {
    int grid_size;
    std::vector<double> grid_distances;
};

// Assumes square (or cube, hypercube, etc) grid with length grid_size
// Converts to a linearly indexed set of coordinates: 0, ..., N-1, N where N is number of points in grid
// (So N = pow(grid_size, dim))
int linear_indexing(const std::vector<int>& idxs, int dim, int grid_size, int phase_size){
    int lin_idx {0};
    for (int i {}; i < dim; i++){
        lin_idx += idxs[i]*pow(grid_size, i);
    }
    
    return lin_idx;
}

std::vector<int> normal_indexing(int lin_idx, int dim, int grid_size){
    std::vector<int> idxs(dim);
    for (int i {}; i < dim; i++) {
        idxs[i] = lin_idx % grid_size;
        lin_idx = lin_idx / grid_size;
    }

    return idxs;
}

bool chk_bdry_pt(int i, int dim, int grid_size){
    bool bdry {false};
    std::vector<int> idxs(normal_indexing(i, dim, grid_size));
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
Eigen::MatrixXd construct_laplacian(int dim, int grid_size, int phase_size){
    std::cout << "Phase size: " << phase_size;
    Eigen::MatrixXd laplacian(phase_size, phase_size);
    
    // Construct the laplacian row by row
    // It will be an NxN matrix where N = grid_size*grid_size
    // Future improvement: Make it MxN where M = number of free points
    for (int i {}; i < phase_size; i++){
        if (!chk_bdry_pt(i, dim, grid_size)) { // Ensures we won't be trying to access points outside the grid
            std::vector<int> idxs = normal_indexing(i, dim, grid_size); // The coordinates of the grid point for this row
            laplacian(i, i) = -4.0; // Set the diagonal entry to -4

            for (int j {}; j < dim; j++) {
                std::vector<int> adj_id(idxs);
                adj_id[j]++; // A node that is adjacent to a grid point has exactly one index changed from it
                laplacian(i, linear_indexing(adj_id, dim, grid_size, phase_size)) = 1.0;

                adj_id[j] = adj_id[j] - 2; // Also need to consider the same index but -1
                laplacian(i, linear_indexing(adj_id, dim, grid_size, phase_size)) = 1.0;
            }
        }
    }

    return laplacian;
}

// Takes in a rectangle with limits (x_lim, y_lim, z_lim, ...) and creates a square grid for it given the resolution
// The resolution is the largest distance that we're okay with between grid points along any axis
struct Grid construct_grid(int dim, double resolution, std::vector<double> limits){
    int grid_size = ceil(*max_element(limits.begin(), limits.end())/resolution);

    std::vector<double> grid_distances(limits);
    for (double i: grid_distances) {
        i = i/grid_size;
    }

    struct Grid grid = {grid_size, grid_distances};

    return grid;
}

// Takes in a square grid with distances (h_x, h_y, h_z, ...) between points in each dimension
// Returns Cartesian coordinates
std::vector<double> grid_to_cartesian(std::vector<int> indices, std::vector<double> grid_distances){
    std::vector<double> coords(indices.size());
    for (int i {}; i < indices.size(); i++) {
        coords[i] = indices[i]*grid_distances[i];
    }

    return coords;
}

Eigen::VectorXd init_solution(double (*bdry_fn)(std::vector<double>), int dim, int grid_size, std::vector<double> grid_distances, int phase_size){
    cout << phase_size;
    Eigen::VectorXd soln = Eigen::VectorXd::Zero(phase_size);
    for (int i {}; i < phase_size; i++){
        if (chk_bdry_pt(i, dim, grid_size)){
            soln(i) = bdry_fn(grid_to_cartesian(normal_indexing(i, dim, grid_size), grid_distances));
        }
    }

    return soln;
}

// Eigen wants a list of positions for slicing matrices
// This creates a list of positions of the "free" nodes (ones not fixed by boundary conditions)
std::vector<int> find_free_node_pos(int dim, int grid_size, int phase_size) {
    std::vector<int> idxs;
    for (int i = 0; i < phase_size; ++i) {
        if (!chk_bdry_pt(i, dim, grid_size)) idxs.push_back(i);
    }
    return idxs;
}

Eigen::MatrixXd solver(double (*bdry_fn)(std::vector<double>), double (*source)(std::vector<double>), int dim, double resolution, std::vector<double> limits){
    struct Grid grid = construct_grid(dim, resolution, limits);
    int phase_size = pow(grid.grid_size, dim);

    Eigen::VectorXd soln = init_solution(bdry_fn, dim, grid.grid_size, grid.grid_distances, phase_size);
    Eigen::MatrixXd laplacian = construct_laplacian(dim, grid.grid_size, phase_size);

    Eigen::VectorXd source_vec(phase_size);
    for (int i {}; i < phase_size; i++) {
        source_vec(i) = source(grid_to_cartesian(normal_indexing(i, dim, grid.grid_size), grid.grid_distances));
    }
    source_vec = source_vec - laplacian * soln;

    std::vector<int> free_nodes = find_free_node_pos(dim, grid.grid_size, phase_size);

    Eigen::MatrixXd lap_free = laplacian(free_nodes, free_nodes);
    
    soln(free_nodes) = lap_free.inverse() * source_vec(free_nodes);

    return soln;
}