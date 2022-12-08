import numpy as np

with open('input.txt') as f:
    # # each line is 100 characters long
    # print(len(f.readline()))
    trees_grid = np.zeros((99, 99), dtype=np.int64)
    for i in range(99):
        trees_grid[i] = list(map(int, list(f.readline().strip())))
    n = 0
    for i, row in enumerate(trees_grid, ):
        for j, col in enumerate(row):
            tree = trees_grid[i, j]
            n1 = j if np.argwhere((trees_grid[i, :j] < tree) == 0).size == 0\
                else j - np.argwhere((trees_grid[i, :j] < tree) == 0)[-1][0]
            n2 = 98 - j if np.argwhere((trees_grid[i, j + 1:] < tree) == 0).size == 0\
                else np.argwhere((trees_grid[i, j + 1:] < tree) == 0)[0][0]+1
            n3 = i if np.argwhere((trees_grid[:i, j] < tree) == 0).size == 0\
                else i - np.argwhere((trees_grid[:i, j] < tree) == 0)[-1][0]
            n4 = 98 - i if np.argwhere((trees_grid[i + 1:, j] < tree) == 0).size == 0\
                else np.argwhere((trees_grid[i + 1:, j] < tree) == 0)[0][0]+1
            n = max(n, n1*n2*n3*n4)
    #         # part 1
    #         n += ((trees_grid[i, :j] < tree).all() or (trees_grid[i, j + 1:] < tree).all()
    #               or (trees_grid[:i, j] < tree).all() or (trees_grid[i + 1:, j] < tree).all())
    print(n)
