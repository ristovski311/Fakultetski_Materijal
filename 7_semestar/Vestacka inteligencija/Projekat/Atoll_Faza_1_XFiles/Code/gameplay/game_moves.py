#
# Funkcije za poteze
#



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
    state[position][0] = "GREEN" if current_player in ['x', "X"] else "RED"
    return state

### !!! 
# Nije potrebno praviti funkcije za odigravanje poteza.
# Unos poteza i odigravanje je razlicita stvar
# To je deo faze 2 !!!
