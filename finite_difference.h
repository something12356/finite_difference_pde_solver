#include <vector>
#include "Eigen/Dense"
using namespace std;

#ifndef FINITE_DIFFERENCE
#define FINITE_DIFFERENCE
Eigen::MatrixXd construct_laplacian(int dim, int grid_size, int phase_size);

int linear_indexing(const std::vector<int>& idxs, int dim, int grid_size, int phase_size);

std::vector<int> normal_indexing(int lin_idx, int dim, int grid_size);

bool chk_bdry_pt(int i, int dim, int grid_size);

vector<vector<double>> solver(double (*bdry_fn)(std::vector<double>), double (*source)(std::vector<double>), int dim, double resolution, std::vector<double> limits);

std::vector<double> grid_to_cartesian(std::vector<int> indices, std::vector<double> grid_distances);

#endif