#
# Funkcije za poteze
#

import copy

# Funkcija za ispravnost unosa poteza
def is_move_valid(game_state,position):
    if position not in game_state:
        return False

    # 2. da li je slobodno
    if game_state[position][0] is not None:
        return False

    return True
    

# Funkcija za unos poteza - ova f-ja se koristi u CLI, ne koristimo je u GUI
def input_a_move(game_state):
    while True:
        user_input = input("Unesi potez (npr. C 3): ").strip().upper()

        try:
            col, row = user_input.split()
            row = int(row)
            position = (col, row)
        except ValueError:
            print("Neispravan format.")
            continue

        if is_move_valid(game_state, position):
            return position
        else:
            print("Potez nije dozvoljen. Polje ne postoji ili je zauzeto.")

# Funkcija za postavljanje polja
def set_a_cell(state, position, current_player):
    state[position][0] = current_player
    return state

# Vraca novo stanje koje je nastalo odigravanjem poteza
def get_next_state(current_state, move, player):
    new_state = copy.deepcopy(current_state)

    if move in new_state:
        new_state[move][0] = player

    return new_state

# Vraca listu koordinata svih slobodnih polja
def get_all_possible_moves(current_state):
    return [coords for coords, info in current_state.items() if info[0] is None]

# Generise listu svih mogucih stanja za sledeci potez
def get_all_possible_states(current_state, player):
    moves = get_all_possible_moves(current_state)
    return [get_next_state(current_state, m, player) for m in moves]
