import copy
"""
Zadatak 6:

Implementirati Backtracking traženje u kombinaciji sa Forward checking tehnikom i LCV
heuristikom za raspoređivanje kraljica na šahovskoj tabli dimenzije 4x4 tako da se ne napadaju.
"""

# Proveravamo da li se 2 kraljice medjusobno napadaju
def is_safe(queen1, col1, queen2, col2):
    return not ((col1 == col2) or (abs(queen1 - queen2) == abs(col1 - col2)))

# Forward checking tehnika - provera da li je nekoj promenljivoj domen postao prazan
def forward_check(board, domains, queen, col):
       
    new_domains = copy.deepcopy(domains)
    new_domains[queen] = [None] # Sa None cemo oznaciti domen kraljice kada kraljica dobije svoju poziciju
    new_board = copy.deepcopy(board)
    new_board[queen][col] = queen+1
    
    for next_queen in range(queen+1, len(board)):
        new_domains[next_queen] = [value for value in domains[next_queen] if is_safe(queen, col, next_queen, value)]
    
    # Prikaz zauzete pozicije i preostalih mogucnosti za ostale kraljice:
    domain_board = [new_board[i] if i <= queen else [new_board[i][j] if j not in new_domains[i] else i+1 for j in range(len(new_board[i]))] for i in range(len(new_board))]
    print(f"\nZa FC proveru: [{queen},{col}]:")
    print_board(domain_board, new_domains)
    
    return (True not in [True if len(new_domains[dom]) == 0 else False for dom in new_domains.keys()], new_board, new_domains) # Da li postoji bilo koji domen od sledece naredne kraljice koji je postao prazan?

# Pomocna funkcija za LCV koja broji preostale vrednosti ostalih domena
def lcv_counter(domains, queen, board, col):
    safe_count = 0
    for next_queen in range(queen+1, len(board)):
        safe_count += len([value for value in domains[next_queen] if is_safe(queen, col, next_queen, value)])
    return safe_count

# LCV heuristika - odredjuje koju sledecu vrednost iz domena treba da uzmemo
def lcv(domains, board, queen):
    return sorted(domains[queen], key = lambda col: lcv_counter(domains, queen, board, col), reverse=True)
        
# Backtracking - trazenje sa vracanjem ukoliko nam to forward check kaze
def backtracking(board, domains, queen):
    # Provera kraja : da li je svim promenljivima dodeljena vrednost
    if queen == len(board):
        return board
    
    lcv_sorted_domain = lcv(domains, board, queen)    
    
    for value in lcv_sorted_domain: #domains[queen]:
        res, new_board, new_domains = forward_check(board, domains, queen, value)
        if res:
           res_boards = backtracking(new_board, new_domains, queen+1)
           if res_boards is not None:
               return res_boards
    return None
        
# Nalazenje resenja
def queen_problem(board_size):
    board = [[0 for i in range(board_size)] for i in range(board_size)]
    domains = {queen : [i for i in range(board_size)] for queen in range(board_size)}
    print("Pocetno stanje:")
    print_board(board,domains)
    result_board = backtracking(board, domains, 0)
    if result_board is not None:
        print("\nResenje:")
        print_board(result_board)
        print_board_chess(result_board)
    else:
        print("Nije uspesno pronadjeno resenje!")

# Prikaz table i domena
def print_board(board, domains = None):
    for queen in range(len(board)): # Kraljica je ekvivalentna redu
        for value in board[queen]:
            print(f"{value:2}", end = " ")
        if domains is not None:
            print(f" | Domen kraljice {queen+1}: {domains[queen]}")
        else:
            print()
    print()
    
# Prikaz table kao chess table
def print_board_chess(board, domains = None):
    for row in range(len(board)): # Kraljica je ekvivalentna redu
        for col in range(len(board[row])):
            print(f"{"♛ " if (board[row][col] != 0) else "⚪" if (row+col)%2 == 0 else "⚫"}", end = " ")
        if domains is not None:
            print(f" | Domen kraljice {row}: {domains[row]}")
        else:
            print()
    print()

# Pokretanje
queen_problem(10)