import numpy as np
from more_itertools import pairwise

with open('input.txt') as f:
    coords = [[list(map(int, x_y.split(','))) for x_y in line.strip().split(' -> ')] for line in f.read().split('\n') if line]
    max_x = max([coord[1] for line in coords for coord in line])
    max_y = max([coord[0] for line in coords for coord in line])

    # part 2: change max_x+1 to max_x+3, max_y to 10000
    sand_grid = np.zeros((max_x+3, 10000))

    for line in coords:
        for b, e in pairwise(line):
            y1, x1 = b[0], b[1]
            y2, x2 = e[0], e[1]
            if x1 == x2:
                for j in range(min(y1, y2), max(y1, y2)+1):
                    sand_grid[x1, j] = 1
            elif y1 == y2:
                for i in range(min(x1, x2), max(x1, x2)+1):
                    sand_grid[i, y1] = 1

    y, x = 500, 0
    n_rows = sand_grid.shape[0]

    def falling_sand(x, y, sand_grid):
        # part 2: change n_rows-1 to n_rows-2
        if x == n_rows-2:
            # part 2: add the cell change and change False to True
            sand_grid[x, y] = 2
            return True
        elif sand_grid[x+1, y] == 0:
            return falling_sand(x+1, y, sand_grid)
        elif sand_grid[x+1, y-1] == 0:
            return falling_sand(x+1, y-1, sand_grid)
        elif sand_grid[x+1, y+1] == 0:
            return falling_sand(x+1, y+1, sand_grid)
        else:
            sand_grid[x, y] = 2
            return [x, y] != [0, 500]

    while falling_sand(0, 500, sand_grid):
        falling_sand(0, 500, sand_grid)

    print(np.count_nonzero(sand_grid==2))
