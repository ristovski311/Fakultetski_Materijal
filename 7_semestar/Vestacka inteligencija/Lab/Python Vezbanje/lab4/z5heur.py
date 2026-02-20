import queue
import random

color_number = {
    0 : "R",
    1 : "G",
    2 : "B"
}

def create_initial_state():
    kuglice = [color_number[x // 4] for x in range(12)]
    while check_4_consecutive(kuglice)[0] == True:
        random.shuffle(kuglice)
    return kuglice
    
def check_4_consecutive(state : list):
    four_cons = [True if (state[i] == state[i + 1] == state[i + 2] == state[i + 3]) else False for i in range(len(state) - 3)]
    return (True in four_cons, four_cons) 

def input_exchange(state:list):
    print("Unesite 2 indexa za zamenu kuglica [0-11]")
    index1 = int(input("Index1: "))
    index2 = int(input("Index2: "))
    new_state = exchange(state, index1, index2)
    return new_state

def is_exchange_valid(state:list,index1, index2):
    index1, index2 = min(index1,index2), max(index1,index2)
    if index1 < 0:
        print("Index ne sme biti manji od 0!")
        return False
    if index2 >= len(state):
        print("Index ne sme biti veci od duzine liste kuglica!")
        return False
    if index2-index1 != 1:
        print("Igrac sme da promeni samo susedne kuglice!")
        return False
    return True

def exchange(state : list, index1, index2):
    if not is_exchange_valid(state,index1,index2):
        return state
    #print(f"Menjamo pozicije: {index1} i {index2}\n")
    new_state = state.copy()
    new_state[index1], new_state[index2] = new_state[index2], new_state[index1]
    return new_state
    
def winning_condition_check(state:list):
    _, res = check_4_consecutive(state)
    if res[0] == res[4] == res[8] == True: # True False False False True False False False True False False False
                                           #  R    R     R     R      B   B     B     B      G   G     G     G
        return True
    else:
        return False

def generate_next_states(state:list):
    next_states = [(exchange(state, i, i+1), i, i+1) for i in range(len(state)-1)]
    return next_states
                
def calc_heur(state: list):
    colors = {
        'R': [],
        'G': [],
        'B': []
    }
    for i in range(len(state)):
        colors[state[i]].append(i)
    return sum(sum(b - a - 1 for a, b in zip(indeksi, indeksi[1:])) for indeksi in colors.values())
    # R [1 ,4 ,6, 8] -> [2, 1, 1] -> 4
    # R [0, 1, 2, 3] -> [0, 0, 0] -> 0
          
def astar(initial_state):
    start_node = tuple(initial_state)
    
    open_set = set()
    open_set.add(start_node)
    closed_set = set()
    
    g = dict()
    g[start_node] = 0
    
    f = dict()
    f[start_node] = g[start_node] + calc_heur(initial_state)
    
    parents = dict()
    parents[start_node] = (None, None)

    while len(open_set) > 0:
        current_node = min(open_set, key=lambda x: f[x])
        current_list = list(current_node)

        if winning_condition_check(current_list):
            print(f"Pobeda:\n{current_list}")
            return reconstruct_path(parents, current_node)

        for next_state, i1, i2 in generate_next_states(current_list):
            neighbor = tuple(next_state)
            novi_g = g[current_node] + 1
            
            if neighbor not in open_set and neighbor not in closed_set:
                g[neighbor] = novi_g
                f[neighbor] = g[neighbor] + calc_heur(next_state)
                parents[neighbor] = (current_node, (i1, i2))
                open_set.add(neighbor)
            else:
                if g[neighbor] > novi_g:
                    g[neighbor] = novi_g
                    f[neighbor] = g[neighbor] + calc_heur(next_state)
                    parents[neighbor] = (current_node, (i1, i2))
                    
                    if neighbor in closed_set:
                        closed_set.remove(neighbor)
                        open_set.add(neighbor)

        closed_set.add(current_node)
        open_set.remove(current_node)
    
    print("Gubitak")
    return None

def reconstruct_path(parents, current):
    path = []
    while current in parents:
        prev_node, move = parents[current]
        if move is None: break
        path.append(move)
        current = prev_node
    path.reverse()
    return path
         
def bfs(state):
    q = queue.Queue()
    q.put((state, [])) #[] sadrzi istoriju exchange-ova
    visited = set()
    visited.add(str(state))
    
    while not q.empty():
        curr_state, curr_path = q.get()
        
        #Slucaj kad smo pronasli sredjene kuglice
        if winning_condition_check(curr_state):
            print("Pobeda")
            return curr_path
        
        #Sve moguce zamene susednih kuglica trenutnog stanja
        for next_state, ind1, ind2 in generate_next_states(curr_state):
            calc_heur(next_state)
            if str(next_state) not in visited:
                visited.add(str(next_state))
                q.put((next_state, curr_path + [(ind1,ind2)]))
    
    print("Gubitak") 
    return None

state = create_initial_state()
print("Stanje:")
print(state)

res_path = astar(state)
print("Redosled menjanja:")
print(res_path)