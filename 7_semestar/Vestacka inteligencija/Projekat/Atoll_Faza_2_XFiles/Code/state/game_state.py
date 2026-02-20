from config import game_config 
from gameplay import game_moves
import queue

#
# Funkcije za stanja
#



# Definisanje stanja
#
# Stanje - graf
# Kljucevi su tuple objekti sa koordinatama tog polja u tabli (A, 1) je na primer u koloni A prvo polje za igru
# Polja koja su hardcode ostrva su recimo (A, 0), (B, 0)... ali i cela LEFT i RIGHT kolona
# Od sredisnjeg slova (ako su slova od A do I, to je slovo E, pogledaj sliku na slajdovima) krece drugacije indeksiranje
# svako slovo posle sredisnjeg ima pocetni indeks za 1 veci od prethodnog
# pa tako F ima prvo polje (F, 2), G ima (G, 3) - ovo su polja na kojima korisnik ima pravo da satavi kamen
# a polja koja su hardcode ostrva su idalje na vrhu kolone (open, bolje se vidi sa slike) -  (F, 1), (G, 2) ... 
#
# Svaki kljuc ima tuple sa 2 stvari -> prva je stanje polja, GREEN RED ili None (None je slobodno)
# druga stvar je lista suseda tog polja, bice nam lakse za search kasnije, verovatno A*
#
# mockup:
#
# graph = {
#     ('A',1): ('RED', [('A', 0), ('A', 2), ('B', 1), ('B', 2), ('LEFT', 1)]),
#     ('A',2): (None, [('A', 1), ('A', 3), ('B', 2), ('B', 3), ('LEFT', 2)]),
#     ...
#     ('B', 1) : (None, [...])
# }

current_player = "GREEN"

islands = dict()

def set_current_player(player):
    global current_player
    current_player = player

def get_current_player():
    return current_player

def toggle_current_player():
    global current_player
    current_player = "RED" if current_player == "GREEN" else "GREEN"
    return current_player

# Funkcija za kreiranje inicijalnog stanja
def create_initial_state(board_size: int):

    # Ovo nam odredjuje broj kolona i broj "vrsta"
    board_diameter = 2 * board_size - 1
    column_letters = [chr(ord('A') + i) for i in range(board_diameter)]
    column_letters = ['LEFT'] + column_letters + ['RIGHT']

    #Odredjivanje opsega svake od kolona
    limits = calculate_column_ranges(column_letters=column_letters, board_size=board_size)
    cells = [(let, num) for let in column_letters for num in range(limits[let][0], limits[let][1] + 1)]

    cells_with_neighbors = calculate_cell_neighbors(cells=cells, column_letters=column_letters)

    # Inicijalizacija ostrva
    cells_with_islands = initialize_islands(cells_with_neighbors,board_size=board_size)
    
    return cells_with_islands


# Pomocna funkcija za odredjivanje opsega indeksa za svaku od kolona
def calculate_column_ranges(column_letters: list, board_size:int):
    limits = dict()
    for column_letter in column_letters:
        if column_letter == "LEFT":
            limits['LEFT'] = (1, board_size - 1)
        elif column_letter == "RIGHT":
            limits['RIGHT'] = (board_size + 1, 2*(board_size) - 1)
        elif ord(column_letter) - ord('A') == (board_size-1): # Ovo je za sredisnje slovo
            limits[column_letter] = (1, 2* board_size - 1)
        elif ord(column_letter) - ord('A') < (board_size - 1): # Za slova levo od srednjeg
            limits[column_letter] = (0, board_size + 1 + ord(column_letter) - ord('A'))
        elif ord(column_letter) - ord('A') > (board_size - 1): # Za slova desno od srednjeg
            limits[column_letter] = (ord(column_letter) - (ord('A') + board_size - 1), 2*board_size)
    return limits


# Pomocna funkcija za odredjivanje suseda polja
def calculate_cell_neighbors(cells : list, column_letters: list):
    cells_with_neighbors = { cell : [None, []] for cell in cells}
    for cell in cells:
        cell_letter = cell[0]
        cell_letter_index = column_letters.index(cell_letter)
        cell_index = cell[1]

        letter_to_the_left = column_letters[cell_letter_index - 1] if (cell_letter_index - 1) in range(len(column_letters)) else None
        letter_to_the_right = column_letters[cell_letter_index + 1] if (cell_letter_index + 1) in range(len(column_letters)) else None
        
        neighbors = [
            (cell_letter, cell_index + 1), # polje iznad
            (cell_letter, cell_index - 1), # polje ispod
            (letter_to_the_left, cell_index - 1), # polje gore levo
            (letter_to_the_left, cell_index), # polje dole levo
            (letter_to_the_right, cell_index), # polje gore desno
            (letter_to_the_right, cell_index + 1), # polje dole desno
        ]

        neighbors = [n for n in neighbors if n in cells]
        cells_with_neighbors[cell][1] = neighbors
    return cells_with_neighbors


# Pomocna funckija za inicijalizaciju ostrva
def initialize_islands(cells: dict, board_size: int):
    island_size = (board_size-1)//2
    red_cells = []
    green_cells = []

    #Slova
    letters = [chr(ord('A') + i) for i in range(2*board_size - 1)]
    middle_letter = ord('A') + (board_size-1)

    limits = calculate_column_ranges(letters, board_size)

    for letter in letters:
        if ord(letter) < middle_letter: # Za slova koja su levo od srednjeg slova
            red_cells += [(letter, limits[letter][0]) if (middle_letter - ord(letter) > island_size) else (letter, limits[letter][1])]
            green_cells += [(letter, limits[letter][1]) if (middle_letter - ord(letter) > island_size) else (letter, limits[letter][0])]
        elif ord(letter) > middle_letter: # Za slova desno od srednjeg
            red_cells += [(letter, limits[letter][1]) if (ord(letter) - middle_letter > island_size) else (letter, limits[letter][0])]
            green_cells += [(letter, limits[letter][0]) if (ord(letter) - middle_letter > island_size) else (letter, limits[letter][1])]

    # Leva kolona
    green_cells += [('LEFT', num) for num in range(1, island_size + 1)]
    green_cells += [('RIGHT', num) for num in range(board_size + 1 + island_size, 2*board_size)]
    #Desna kolona
    red_cells += [('LEFT', num) for num in range(1 + island_size, board_size)]
    red_cells += [('RIGHT', num) for num in range(board_size + 1, board_size + 1 + island_size)]

    for cell in green_cells:
        cells[cell][0] = "GREEN"
    for cell in red_cells:
        cells[cell][0] = "RED"

    return cells

# Funkcija za kreiranje proizvoljnog stanja   
def create_arbitrary_state(green_cells:list, red_cells:list):
    arbitrary_state = create_initial_state(game_config.game_config["board_size"])
    for cell in green_cells:
        if(game_moves.is_move_valid(arbitrary_state,cell)):
            arbitrary_state[cell][0] = "GREEN"
    for cell in red_cells:
        if(game_moves.is_move_valid(arbitrary_state,cell)):    
            arbitrary_state[cell][0] = "RED"
    return arbitrary_state

#
# FAZA 2 :
#

# Pomocna funkcija za odredjivanje koja vraca ostrva sa table
#
# Ova pomocna struktura ima sledeci izgled:
# {
#     ('GREEN', 0) : {
#         'NEIGHBORS' : ["Koja ostrva su susedi ovom ostrvu"],
#         'CELLS': ["Koje celije pripadaju datom ostrvu"]
#     },
#     ...
# }
#
def get_all_islands(board_size: int):
    
    islands = {
        (color, num) :  {
                            'NEIGHBORS' : [('RED',num),('RED', (num+1)%6)] 
                            if color == 'GREEN' 
                            else [('GREEN', (num-1)%6),('GREEN', num)],
                            'CELLS' : []
                        } 
                        for color in ['RED', 'GREEN'] for num in range(6)
    }

    island_size = (board_size-1)//2

    #Slova
    letters = [chr(ord('A') + i) for i in range(2*board_size - 1)]
    middle_letter = ord('A') + (board_size-1)

    limits = calculate_column_ranges(letters, board_size)

    for letter in letters:
        if ord(letter) < middle_letter: # Za slova koja su levo od srednjeg slova
            if (middle_letter - ord(letter) > island_size):
                islands[('RED', 0)]['CELLS'].append((letter, limits[letter][0]))
                islands[('GREEN', 4)]['CELLS'].append((letter, limits[letter][1]))             
            else:
                islands[('RED', 4)]['CELLS'].append((letter, limits[letter][1]))
                islands[('GREEN', 0)]['CELLS'].append((letter, limits[letter][0])) 
        elif ord(letter) > middle_letter: # Za slova koja su desno od srednjeg slova
            if (ord(letter) - middle_letter > island_size):
                islands[('RED', 3)]['CELLS'].append((letter, limits[letter][1]))
                islands[('GREEN', 1)]['CELLS'].append((letter, limits[letter][0]))             
            else:
                islands[('RED', 1)]['CELLS'].append((letter, limits[letter][0]))
                islands[('GREEN', 3)]['CELLS'].append((letter, limits[letter][1]))

    # Leva kolona
    islands[('GREEN', 5)]['CELLS'] += [('LEFT', num) for num in range(1, island_size + 1)]
    islands[('RED', 5)]['CELLS'] += [('LEFT', num) for num in range(1 + island_size, board_size)]
    #Desna kolona
    islands[('GREEN', 2)]['CELLS'] += [('RIGHT', num) for num in range(board_size + 1 + island_size, 2*board_size)]
    islands[('RED', 2)]['CELLS'] += [('RIGHT', num) for num in range(board_size + 1, board_size + 1 + island_size)]

    return islands

# Pomocna funkcija za mapiranje koja celija pripada kom ostrvu ako ijednom
def map_cells_to_islands(islands):
    cells_to_island = {}
    for island, data in islands.items():
        for cell in data['CELLS']:
            cells_to_island[cell] = island
    return cells_to_island

# Funkcija BFS koja pronalazi koja su ostrva (obodna) medjusobno povezana
def find_connected_islands(state, islands):
    cell_to_island = map_cells_to_islands(islands)

    # Graf povezanosti ostrva iste boje
    # Struktura je:
    # {
    #     ('GREEN', 0): {"Koja sva GREEN ostrva su jos povezana sa ovim"},
    #     ('RED', 0): {"Isto, samo za RED"},
    #     ...
    # }
    island_connections = {i: set() for i in islands}

    for island, data in islands.items():
        color = island[0]

        # BFS startuje potragu za povezanim ostrvima pocevsi od svih celija koja su deo nekog od ostrva
        visited = set()
        q = queue.Queue()

        for cell in data['CELLS']:
            q.put(cell)
            visited.add(cell)

        while not q.empty():
            cell = q.get()

            # Ako smo dosli do druge celije koja pripada ostrvu iste boje
            if cell in cell_to_island:
                other = cell_to_island[cell]
                if other != island and other[0] == color:
                    island_connections[island].add(other)

            # Siri se samo kroz celije iste boje
            for neighbor in state[cell][1]:
                if state[neighbor][0] == color and neighbor not in visited:
                    q.put(neighbor)
                    visited.add(neighbor)

    return island_connections

# Pomocna funkcija koja odredjuje komponente ostrva koje su medjusobno povezane
def get_island_components(connections, start):
    visited = set()
    q = queue.Queue()
    q.put(start)
    visited.add(start)

    while not q.empty():
        current = q.get()
        for neighbor in connections[current]:
            if neighbor not in visited:
                visited.add(neighbor)
                q.put(neighbor)

    return visited

# Pomocna funkcija koja odredjuje distancu izmedju 2 povezana ostrva, u oba smera, i clockwise i anti-clockwise
def island_distance(islands, start, target):
    if start == target:
        return 1

    # Anti-clockwise smer
    steps = 1
    curr = start
    while True:
        curr = islands[curr]['NEIGHBORS'][0]
        steps += 1
        if curr == target:
            ccw = steps
            break

    # Clockwise smer
    steps = 1
    curr = start
    while True:
        curr = islands[curr]['NEIGHBORS'][1]
        steps += 1
        if curr == target:
            cw = steps
            break

    return min(cw, ccw)


# Funkcija za proveru kraja igre
def check_win_condition(state, board_size):
    islands = get_all_islands(board_size)
    connections = find_connected_islands(state, islands)

    total_islands = len(islands)
    threshold = total_islands // 2 + 1  # 7 za 12 ostrva, ovo je svakako hardcodirano za nasu igru i uvek ce biti 7 bez obzira na dimenziju table

    for island in islands:
        component = get_island_components(connections, island)

        if len(component) < 2:
            continue

        for other in component:
            if island == other:
                continue

            dist = island_distance(islands, island, other)

            if dist >= threshold:
                return island[0]  # "GREEN" ili "RED" pobednik

    return None
