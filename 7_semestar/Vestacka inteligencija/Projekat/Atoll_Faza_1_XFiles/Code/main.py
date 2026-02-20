from state.game_state import *
from config.game_config import *
from gameplay.game_moves import *
from gui.game_display import *
from auxilary.misc import *

#
# GUI
# Pokretanje igre - prikaz setup menija za izbor opcija igre (velicina table i slicno)
#

if show_setup_menu():
    state = create_initial_state(board_size=game_config["board_size"])
    draw(state)




#
# CLI
# Postavljanje konfiguracije igre, a kasnije i prikaz stanja (koriscenjem pomocne f-je display_graph), unos polja, i prikaz nekog proizvoljnog stanja
#


#choose_board_size()
#choose_game_mode()
#if game_config["computer_plays"] == True:
#    choose_first_player()
#choose_first_symbol()
#current_player = "X" if game_config["green_plays_first"] else "O"

# display_graph(state)

#position = input_a_move(state)
#state = set_a_cell(state, position, current_player)

#arb = create_arbitrary_state([('A', 3), ('B', 5), ('I', 100)], [('E', 3), ('I', 5)])
#display_graph(arb)



