from collections import defaultdict

with open('input.txt') as f:
    cur_tree = []
    dir_files = defaultdict(int)
    entered_new_dir = False
    for line in f:
        line = line.strip()
        if line.startswith('$'):
            if line == '$ cd ..':
                cur_tree.pop()
            elif line.startswith('$ cd '):
                cur_tree.append('/'.join(cur_tree)+line[5:])
            else:
                entered_new_dict = True
        elif not line.startswith('dir'):
            entered_new_dict = False
            size, _ = line.split()
            file_size = int(size)
            for dir in cur_tree:
                dir_files[dir] += file_size
    # part 1
    # print(sum([files for dir, files in dir_files.items() if files <= 100000]))

    # part 2
    space_needed = 30000000 - (70000000 - dir_files['/'])
    print([dir_files[dir] for dir in sorted(dir_files, key=dir_files.get) if dir_files[dir] >= space_needed][0])
