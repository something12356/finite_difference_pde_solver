#include <vector>
#include <Eigen/Dense>

#ifndef FINITE_DIFFERENCE
#define FINITE_DIFFERENCE
Eigen::MatrixXd laplacian_constructor(int dim, int grid_size);

int linear_indexing(const std::vector<size_t>& idxs, int dim, int grid_size);

std::vector<size_t> normal_indexing(int lin_idx, int dim, int grid_size);

bool chk_bdry_pt(int i, int dim, int grid_size);

#endif