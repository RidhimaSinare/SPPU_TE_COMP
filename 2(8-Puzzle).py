import copy

infinity = 1e+10

class Puzzle:

    def __init__(self, elements) -> None:
        assert(len(elements)==len(elements[0]))
        self.board = elements
        self.ndims = len(elements)

        for i in range(self.ndims):
            for j in range(self.ndims):
                if(self.board[i][j] == 0):
                    self.pos = (i,j)
                    break



    def display(self):
        for i in range(self.ndims):
            for j in range(self.ndims):
                print(self.board[i][j], end=" ")
            print()


def move(puzzle: Puzzle):

    x, y = puzzle.pos[0], puzzle.pos[1]
    possiblepos = []
    dim = puzzle.ndims

    if x+1<dim and y<dim:
        possiblepos.append((x+1, y))
    if x<dim and y+1<dim:
        possiblepos.append((x, y+1))
    if x>=1 and y>=0:
        possiblepos.append((x-1, y))
    if x>=0 and y>=1:
        possiblepos.append((x, y-1))
    
    new_states = []

    for positions in possiblepos:
        posx, posy = positions[0], positions[1]
        new_board = copy.deepcopy(puzzle.board)
        new_board[x][y], new_board[posx][posy] = new_board[posx][posy], new_board[x][y]
        new_states.append(Puzzle(new_board))

    return new_states


def heuristic(initial: Puzzle, goal: Puzzle):

    cnt = 0

    assert(initial.ndims==goal.ndims)
    dims = initial.ndims

    for i in range(dims):
        for j in range(dims):
            if(initial.board[i][j] != goal.board[i][j]):
                cnt+=1
    return cnt

def is_goal(curr: Puzzle, goal:Puzzle):

    assert(curr.ndims==goal.ndims)
    dims = curr.ndims

    for i in range(dims):
        for j in range(dims):
            if(curr.board[i][j] != goal.board[i][j]):
                return False
    return True


init_puzzle = Puzzle( [ [ 1 , 2 , 3 ] , [ 0 , 4 , 6 ] , [ 7 , 5 , 8 ] ] )
print( "Initial state:" )
init_puzzle.display()

goal_puzzle = Puzzle( [ [ 1 , 2 , 3 ] , [ 4 , 5 , 6 ] , [ 7 , 8 , 0 ] ] )
print( "Goal state:" )
goal_puzzle.display()

openset : list[Puzzle] = [init_puzzle]

gscore: dict[Puzzle, int] = {}
gscore[init_puzzle] = 0

fscore: dict[Puzzle, int] = {}
fscore[init_puzzle] = gscore[init_puzzle] + heuristic(init_puzzle, goal_puzzle)

num_step = 1

while len(openset) !=0:

    print("Step: ", num_step)

    minnode = openset[0]
    minscore = fscore.get(minnode, infinity)
    for node in openset:
        score = fscore.get(node, infinity)
        if(score<minscore):
            minscore = score
            minnode = node
    
    print(">> Selected state from Frontier: ")    
    current = minnode
    current.display()
    print()
    num_step += 1

    if is_goal(current, goal_puzzle):
        print("Done")
        break

    openset.remove(current)

    for neigh in move(current):

        tentg = gscore.get(current, infinity) + 1

        if tentg < gscore.get(neigh, infinity):
            gscore[neigh] = tentg
            fscore[neigh] = tentg + heuristic(neigh, goal_puzzle)

            if neigh not in openset:
                openset.append(neigh)
                neigh.display()
                print(f"h(n) for above state is {heuristic(neigh, goal_puzzle)}")
                print(f"g(n) for above state is {gscore[neigh]}")
                print(f"f(n) for above state is {fscore[neigh]}")
                print()
    print()
    print("-------------------------")
    print()




