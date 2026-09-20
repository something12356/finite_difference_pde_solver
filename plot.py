import matplotlib
import matplotlib.pyplot as plt
import numpy as np

def load_grid():
    grid = []
    func_vals = []
    with open("solution.txt", "r") as f:
        lines = f.readlines()
        dim = int(lines[0])
        for i in range(1, len(lines)):
            line = lines[i].rstrip(',') # Remove trailing comma
            line = line.split(',')
            grid.append(np.array([float(line[j]) for j in range(dim)]))
            func_vals.append(float(line[dim]))

    return dim, np.array(grid), np.array(func_vals)


def main():
    dim, grid, func_vals = load_grid()
    ax = plt.axes(projection = '3d')
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    ## Plot a 3D surface with the height being the function value
    if dim == 2:
        colours = func_vals

        ax.plot_trisurf(grid[:,0], grid[:,1], func_vals, cmap='Blues')

    ## Plot a heatmap based on the function value at each point
    if dim == 3:
        colours = func_vals*3
        ## Creating the heatmap
        img = ax.scatter(grid[:,0], grid[:,1], grid[:,2], c=colours, s=100, cmap='viridis')

    plt.show()

if __name__ == "__main__":
    main()