import copy
"""
Indeks : 19347
Zadatak 8 :

Implementirati Backtracking traženje u kombinaciji sa Forward Checking tehnikom i LCV
heuristikom za popunjavanje matrice dimenzija 4x4, brojevima od 1 do 4, tako da isti broj ne
sme da se nađe u istoj vrsti, kao ni u istoj koloni (sudoku).
"""

# Proveravamo da li su 2 ista broja u istoj koloni ili vrsti
def is_safe(pos1, val1, pos2, val2):
    return not (val1 == val2 and ((pos1[0] == pos2[0]) or (pos1[1] == pos2[1])))

# Forward checking tehnika - provera da li je nekoj promenljivoj domen postao prazan
def forward_check(board, domains, pos, val, board_size):
       
    new_domains = copy.deepcopy(domains)
    new_domains[pos] = [None] # Sa None cemo oznaciti domen polja kada polje dobije svoj broj
    new_board = copy.deepcopy(board)
    new_board[pos[0]][pos[1]] = val
    
    for next_pos in domains.keys():
        if new_domains[next_pos] == [None]:
            continue
        new_domains[next_pos] = [value for value in domains[next_pos] if is_safe(pos, val, next_pos, value)]
    
    # Prikaz zauzete pozicije i preostalih mogucnosti za ostale pozicije:
    print(f"\nZa FC proveru: [{pos},{val}]:")
    print_board(new_board, board_size)
    print_domains(new_domains, board_size)
    
    return (True not in [True if len(new_domains[dom]) == 0 else False for dom in new_domains.keys()], new_board, new_domains) # Da li postoji bilo koji domen od narednog polja koji je postao prazan?

# Pomocna funkcija za LCV koja broji preostale vrednosti ostalih domena
def lcv_counter(domains, pos, val):
    safe_count = 0
    for next_cell in domains.keys():
        if domains[next_cell] == [None]:
            continue
        safe_count += len([value for value in domains[next_cell] if is_safe(pos, val, next_cell, value)])
    return safe_count

# LCV heuristika - odredjuje koju sledecu vrednost iz domena treba da uzmemo
def lcv(domains, pos):
    return sorted(domains[pos], key = lambda val: lcv_counter(domains, pos, val), reverse=True)
        
# Backtracking - trazenje sa vracanjem ukoliko nam to forward check kaze
def backtracking(board, domains, pos, board_size):
    # Provera kraja : da li je svim promenljivima dodeljena vrednost
    if pos == (board_size, 0):
        return board
    
    lcv_sorted_domain = lcv(domains, pos)    
    
    for value in lcv_sorted_domain: #domains[pos]:
        res, new_board, new_domains = forward_check(board, domains, pos, value, board_size)
        if res:
            next_j = (pos[1] + 1) % board_size
            next_i = pos[0] if next_j != 0 else pos[0]+1
            res_boards = backtracking(new_board, new_domains, (next_i, next_j), board_size)
            if res_boards is not None:
                return res_boards
    return None
        
# Nalazenje resenja
def sudoku_problem(board_size):
    board = [[0 for i in range(board_size)] for i in range(board_size)]
    domains = {(i,j) : [k for k in range(1, board_size+1)] for i in range(board_size) for j in range(board_size)}
    
    print("Pocetno stanje:")
    print_board(board,board_size)
    print_domains(domains,board_size)
    
    result_board = backtracking(board, domains, (0,0), board_size)
    if result_board is not None:
        print("\nResenje:")
        print_board(result_board, board_size)
    else:
        print("Nije uspesno pronadjeno resenje!")

# Prikaz table:
def print_board(board, board_size):
    for row in range(board_size):
        for col in range(board_size):
            print(f"{board[row][col]:2}", end = " ")
        print()
        
# Prikaz domena:
def print_domains(domains, board_size):
    for row in range(board_size):
        for col in range(board_size):        
            print(f"Domen polja ({row},{col}): {domains[(row,col)]}")

# Pokretanje
sudoku_problem(4)