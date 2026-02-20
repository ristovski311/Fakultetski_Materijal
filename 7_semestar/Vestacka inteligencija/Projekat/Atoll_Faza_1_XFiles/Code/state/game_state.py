from config import game_config 
from gameplay import game_moves

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




# Funkcija za kreiranje inicijalnog stanja
def create_initial_state(board_size: int):
    global game_state

    # Ovo nam odredjuje broj kolona i broj "vrsta"
    board_diameter = 2 * board_size - 1
    column_letters = [chr(ord('A') + i) for i in range(board_diameter)]
    column_letters = ['LEFT'] + column_letters + ['RIGHT']

    #Odredjivanje opsega svake od kolona
    limits = calculate_column_ranges(column_letters=column_letters, board_size=board_size)
    cells = [(let, num) for let in column_letters for num in range(limits[let][0], limits[let][1] + 1)]

    cells_with_neighbors = calculate_cell_neighbors(cells=cells, column_letters=column_letters)

    # Inicijalizacija ostrva
    cells_with_islands = initialize_islands(cells_with_neighbors,board_size=board_size, limits=limits)
    
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
def initialize_islands(cells: dict, board_size: int, limits: dict):
    island_size = (board_size-1)//2
    red_cells = []
    green_cells = []

    #Slova
    letters = [chr(ord('A') + i) for i in range(2*board_size - 1)]
    middle_letter = ord('A') + (board_size-1)
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