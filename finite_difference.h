#include <vector>
#include "Eigen/Dense"

#ifndef FINITE_DIFFERENCE
#define FINITE_DIFFERENCE
Eigen::MatrixXd construct_laplacian(int dim, int grid_size);

int linear_indexing(const std::vector<int>& idxs, int dim, int grid_size);

std::vector<int> normal_indexing(int lin_idx, int dim, int grid_size);

bool chk_bdry_pt(int i, int dim, int grid_size);

Eigen::MatrixXd solver(double (*bdry_fn)(std::vector<double>), double (*source)(std::vector<double>), int dim, double resolution, std::vector<double> limits);

#endif