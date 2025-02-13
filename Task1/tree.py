class TreeNode:
    data = []
    color = "n"

    def __init__(self, smth):
        self.data = smth
        self.color = "n"
    
    def __lt__(self, other):
        if len(self.data) == 0 and len(other.data) == 0:
            return False
        elif len(self.data) == 0:
            return True
        elif len(other.data) == 0:
            return False
        else:
            return self.data < other.data 
        
    def __eq__(self, other):
        return self.data == other.data
    
    def __str__(self):
        return str(self.data)
    
    def __len__(self):
        return len(self.data)

def correct_int(num: int) -> int:
    if num >= pow(2, 63):
        return -1
    if num < -pow(2, 63):
        return 0
    num =  num % pow(2, 32)
    if num >= pow(2, 31):
        num = num - pow(2, 32)
    return num

class Tree:
    nodes = []
    left = []
    right = []
    parent = []
    capacity = 0
    root_index = 0

    def __init__(self):
        self.nodes = [TreeNode([])]
        self.left = []
        self.right = []
        self.parent = []
        self.capacity = -1

    def factory_reset(self):
        self.nodes = [TreeNode([])]
        self.left = []
        self.right = []
        self.parent = []
        self.capacity = -1

    def rotate_left(self, rght : int):
        self.right[self.parent[rght]] = self.left[rght]
        if self.left[rght] != -1:
            self.parent[self.left[rght]] = self.parent[rght]
        self.left[rght] = self.parent[rght]
        self.parent[rght] = self.parent[self.parent[rght]]
        self.parent[self.left[rght]] = rght
        if self.parent[rght] == -1:
            self.root_index = rght
            return
        elif self.left[self.parent[rght]] == self.left[rght]:
            self.left[self.parent[rght]] = rght
        elif self.right[self.parent[rght]] == self.left[rght]:
            self.right[self.parent[rght]] = rght

    def rotate_right(self, lft : int):
        self.left[self.parent[lft]] = self.right[lft]
        if self.right[lft] != -1:
            self.parent[self.right[lft]] = self.parent[lft]
        self.right[lft] = self.parent[lft]
        self.parent[lft] = self.parent[self.parent[lft]]
        self.parent[self.right[lft]] = lft
        if self.parent[lft] == -1:
            self.root_index = lft
            return
        elif self.left[self.parent[lft]] == self.right[lft]:
            self.left[self.parent[lft]] = lft
        elif self.right[self.parent[lft]] == self.right[lft]:
            self.right[self.parent[lft]] = lft


    def check_colors(self, curr : int):
        #print('colors!')

        while self.nodes[curr].color == "r" and self.parent[curr] != -1 \
            and self.nodes[self.parent[curr]].color == "r":
            
            if self.left[self.parent[self.parent[curr]]] != -1 \
                and self.nodes[self.left[self.parent[self.parent[curr]]]].color == "r" \
                and self.right[self.parent[self.parent[curr]]] != -1 \
                and self.nodes[self.right[self.parent[self.parent[curr]]]].color == "r":
                self.nodes[self.left[self.parent[self.parent[curr]]]].color = "b"
                self.nodes[self.right[self.parent[self.parent[curr]]]].color = "b"
                self.nodes[self.parent[self.parent[curr]]].color = "r"
                curr = self.parent[self.parent[curr]]
                continue
            
            if self.parent[curr] == self.left[self.parent[self.parent[curr]]]:
                if curr == self.right[self.parent[curr]]:
                    self.rotate_left(curr)
                else:
                    curr = self.parent[curr]
                
                self.nodes[curr].color = "b"
                self.nodes[self.parent[curr]].color = "r"

                self.rotate_right(curr)
                return

            if self.parent[curr] == self.right[self.parent[self.parent[curr]]]:
                if curr == self.left[self.parent[curr]]:
                    self.rotate_right(curr)
                else:
                    curr = self.parent[curr]
                
                self.nodes[curr].color = "b"
                self.nodes[self.parent[curr]].color = "r"

                self.rotate_left(curr)
                return
        
        if self.parent[curr] == -1 and self.nodes[curr].color == "r":
            self.nodes[curr].color = "b"

                
    
    def add_node(self, new_value: TreeNode):
        new_index = self.capacity
        self.nodes[-1] = TreeNode(new_value)
        self.nodes += [TreeNode([])]
        self.left += [-1]
        self.right += [-1]
        self.parent += [-1]
        self.capacity += 1

        if new_index == 0:
            self.root_index = 0
            self.nodes[0].color = "b"
            return
        else:
            self.nodes[new_index].color = "r"

        index = self.root_index
        while index < new_index:
            #print(new_value, self.nodes[index].data)
            #print(new_value < self.nodes[index].data, TreeNode(new_value) < self.nodes[index])
            if TreeNode(new_value) < self.nodes[index]:
                if self.left[index] == -1:
                    self.left[index] = new_index
                    self.parent[new_index] = index
                    self.check_colors(new_index)
                    break
                else:
                    index = self.left[index]
                    continue
            else:
                if self.right[index] == -1:
                    self.right[index] = new_index
                    self.parent[new_index] = index
                    self.check_colors(new_index)
                    break
                else:
                    index = self.right[index]
                    continue
        
        
            
    def read_from_file(self, file_name, count = 1):
        file = open(file_name, "r")
        data = file.readlines()
        file.close()

        self.capacity = 0
        for i in range(0, len(data)):
            if len(data[i].split()) < 2:
                self.capacity = -1
                return
            if (data[i].split()[1][0] != "-" and not(data[i].split()[1].isdigit())) or \
                (data[i].split()[1][0] == "-" and not(data[i].split()[1][1:].isdigit())):
                self.capacity = -1
                return

            value = [data[i].split()[0], correct_int(int(data[i].split()[1]))]
            self.add_node(value)
            #print(self.parent, self.left, self.right, self.root_index)
            #self.print_tree()
            #print("-----------")
            

        self.restore()
        #print(self.parent, self.left, self.right)
        #self.print_tree()

    def read_from_db(self, db):
        for elem in db:
            self.add_node(elem)

    # ------------------------

    def restore(self):
        nodes = [self.root_index]
        
        count = 1
        curr = 0
        while count < self.capacity:
            if self.left[nodes[curr]] != -1:
                nodes.append(self.left[nodes[curr]])
                count += 1
            if self.right[nodes[curr]] != -1:
                nodes.append(self.right[nodes[curr]])
                count += 1
            curr += 1

        inverse = [0] * self.capacity
        for i in range(self.capacity):
            inverse[nodes[i]] = i
        inverse += [-1]

        new_nodes = [self.nodes[nodes[i]] for i in range(self.capacity)] + [TreeNode([])]
        new_left = [inverse[self.left[nodes[i]]] for i in range(self.capacity)] + [-1]
        new_right = [inverse[self.right[nodes[i]]] for i in range(self.capacity)] + [-1]
        new_parent = [inverse[self.parent[nodes[i]]] for i in range(self.capacity)] + [-1]

        self.nodes = new_nodes
        self.left = new_left
        self.right = new_right
        self.parent = new_parent
        self.root_index = 0

    # ------------------------

    def print_tree(self):
        self.print_subtree(self.root_index, 0, "r")
    
    def print_subtree(self, index, level, typ):
        if not(self.is_real(index)):
            return
        
        print ("  " * level + typ + ": ", end ="")
        print(self.nodes[index], end=" ")
        print(self.nodes[index].color)
        self.print_subtree(self.left[index], level + 1, "l")
        self.print_subtree(self.right[index], level + 1, "r")

    # ------------------------
            
    def is_real(self, index):
        if index >= self.capacity:
            return False
        if self.nodes[index] == TreeNode([]):
            return False
        return True
    
    def size(self):
        count = 0
        for i in range(self.capacity):
            if self.nodes[i] != TreeNode([]):
                count += 1
        return count

    def children_count(self, index):
        count = 0
        if self.left[index] != -1:
            count += 1
        if self.right[index] != -1:
            count += 1
        return count
    
    # def vertex_children_counts(self) -> int:
    #     return [self.children_count[index] for index in range(self.capacity)]
    
    def subtrees_sizes(self):
        sizes = [0] * (self.capacity + 1)

        for i in range(self.capacity - 1, -1, -1):
            sizes[i] = 1 + sizes[self.left[i]] + sizes[self.right[i]]

        return sizes[:self.capacity]
    
    def subtrees_depths(self):
        depths = [0] * (self.capacity + 1)

        for i in range(self.capacity - 1, -1, -1):
            depths[i] = 1 + max(depths[self.left[i]], depths[self.right[i]])

        return depths[:self.capacity]
    
    def level_decomposition(self):
        levels = []

        if self.capacity == 0:
            return []

        levels = [[0]]
        level = 0
        while levels[level] != []:
            levels += [[]]
            for i in levels[level]:
                if self.left[i] != -1:
                    levels[level + 1].append(self.left[i])
                if self.right[i] != -1:
                    levels[level + 1].append(self.right[i])
            level += 1
            
        return levels[:-1]
    
    def full_level_decomposition(self):
        levels = [[] for i in range(self.capacity + 1)]

        if self.capacity == 0:
            return []
        
        for i in range(self.capacity - 1, -1, -1):
            levels[i] = [0] * (1 + max(len(levels[self.left[i]]), len(levels[self.right[i]])))
            levels[i][0] = 1
            for j in range(len(levels[self.left[i]])):
                levels[i][j + 1] += levels[self.left[i]][j]
            for j in range(len(levels[self.right[i]])):
                levels[i][j + 1] += levels[self.right[i]][j]
        
        return levels[:-1]

    
    # def vertices_levels(self):
    #     level = [0] * self.capacity

    #     for index in range(self.capacity):
    #         for jndex in self.down_links[index]:
    #             level[jndex] = level[index] + 1

    #     return level 

    # def depth(self) -> int:
    #     return self.subtrees_depths()[0]
    
    # def max_level_size(self) -> int:
    #     if self.capacity == 0:
    #         return 0

    #     levels = self.level_decomposition()
    #     return max([len(level) for level in levels])
    
    # ----------------------

    # 1 2
    def sum_small_subtrees(self, k : int):
        sizes = self.subtrees_sizes()
        depths = self.subtrees_depths()
        good = []
        good.append(sum([sizes[i] for i in range(self.capacity) if sizes[i] <= k]))
        good.append(sum([sizes[i] for i in range(self.capacity) if depths[i] <= k]))
        return good
    

    # 3
    def sum_thin_subtrees(self, k : int):
        decomp = self.full_level_decomposition()
        return sum([sum(decomp[i]) for i in range(self.capacity) if max(decomp[i]) <= k])

    # 4 5
    def k_th_level(self, k : int):
        levels = self.level_decomposition()
        good = []
        if k >= len(levels):
            good += [0]
        else:
            good = [len(levels[k])]
        if k == 0 or k - 1 >= len(levels):
            return good + [0]
        good.append(sum([k for node in levels[k - 1] if self.children_count(node) == 0]))
        return good

    
    def summary(self, k : int):
        if self.capacity == -1:
            return []
        
        good12 = self.sum_small_subtrees(k)
        good45 = self.k_th_level(k)

        result = [0] * 5
        result[0] = good12[0]
        result[1] = good12[1]
        result[2] = self.sum_thin_subtrees(k)
        result[3] = good45[0]
        result[4] = good45[1]
        return result