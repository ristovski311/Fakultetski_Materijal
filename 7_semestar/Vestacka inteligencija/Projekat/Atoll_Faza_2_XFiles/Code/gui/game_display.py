import tkinter as tk
import os
from tkinter import messagebox
from PIL import Image, ImageTk, ImageEnhance
from config.game_config import *
from gameplay.game_moves import *
from state.game_state import check_win_condition, get_current_player, toggle_current_player, set_current_player

TITLE = 'Atoll'
RESOLUTION = '800x600'

BUTTON_SPRITESHEET_PATH = 'gui/images'
BUTTON_SPRITESHEET_NAME = 'buttons_aqua.png'
BOARD_TEXTURE_NAME = 'background.png'

RED_BUTTON_COORDS = (220, 46, 360, 190)
GREEN_BUTTON_COORDS = (220, 220, 360, 363)
NONE_BUTTON_COORDS = (398, 46, 540, 190)

original_images = {}
original_board_texture = None

sprites = {"RED": {}, "GREEN": {}, "DARK": {}, None: {}}
sprite_cache = {}

board_texture_sprite = None
cell_items = {}
cell_positions = {}

hovered_cell = None
clicked_cell = None

resize_job = None
click_job = None
last_base_unit = None

label_coords = set()

can_play = True

def darken_image(image, factor):
    enhancer = ImageEnhance.Brightness(image)
    darkened_image = enhancer.enhance(factor)
    return darkened_image

def load_resources():
    global original_images, original_board_texture

    btn_path = os.path.join(BUTTON_SPRITESHEET_PATH, BUTTON_SPRITESHEET_NAME)
    sheet = Image.open(btn_path)

    original_images["RED"] = sheet.crop(RED_BUTTON_COORDS)
    original_images["GREEN"] = sheet.crop(GREEN_BUTTON_COORDS)
    original_images["DARK"] = darken_image(sheet.crop(NONE_BUTTON_COORDS), 0.5)
    original_images[None] = sheet.crop(NONE_BUTTON_COORDS)

    tex_path = os.path.join(BUTTON_SPRITESHEET_PATH, BOARD_TEXTURE_NAME)
    if os.path.exists(tex_path):
        original_board_texture = Image.open(tex_path)

def get_canvas_coords(cell, board_size, canvas_w, canvas_h):
    letter, row = cell

    if letter == "LEFT":
        col_idx = -1
    elif letter == "RIGHT":
        col_idx = 2 * board_size - 1
    else:
        col_idx = ord(letter) - ord('A')

    base_unit = min(canvas_w, canvas_h) / (board_size * 3.0)

    spacing_x = base_unit * 0.866
    spacing_y = base_unit

    x = (col_idx - (board_size - 1)) * spacing_x
    y = (row - board_size - (col_idx - (board_size - 1)) * 0.5) * spacing_y

    return (canvas_w / 2) + x, (canvas_h / 2) + y, base_unit

def update_cell_visual(canvas, cell, state):
    if cell is None or cell not in cell_items:
        return

    item_id = cell_items[cell]
    cell_state = state[cell][0]

    mode = "normal"
    if cell == clicked_cell:
        mode = "click"
    elif cell == hovered_cell:
        mode = "hover"

    canvas.itemconfig(item_id, image=sprites[cell_state][mode])

def on_mouse_move(event, canvas, state):
    global hovered_cell

    items = canvas.find_overlapping(event.x, event.y, event.x, event.y)
    new_hover = None

    for item in items:
        tags = canvas.gettags(item)
        for tag in tags:
            if tag.startswith("coord_"):
                _, l, r = tag.split("_")
                new_hover = (l, int(r))
                break
        if new_hover:
            break

    if new_hover != hovered_cell:
        old = hovered_cell
        hovered_cell = new_hover
        update_cell_visual(canvas, old, state)
        update_cell_visual(canvas, hovered_cell, state)

def handle_click(cell, canvas, state):
    global clicked_cell, click_job, can_play

    if can_play is False:
        return

    clicked_cell = cell
    
    if is_move_valid(state, cell):
        current_player = get_current_player()
        set_a_cell(state, cell, current_player)

        print(f"POTEZ ODIGRAN: {cell} od strane igraca: {current_player}")

        next_player = toggle_current_player()
        print(f"Sledeci igrac: {next_player}")

        preostali_potezi = get_all_possible_moves(state)
        print(f"Preostalo slobodnih polja: {len(preostali_potezi)}")

        if len(preostali_potezi) > 0:
            print(f"Sledeci igrac bi mogao da odigra na: {preostali_potezi}")
        
    else:
        messagebox.showwarning("Greska!", "Polje nije validno! Izaberite drugo!")

    update_cell_visual(canvas, cell, state)


    if click_job:
        canvas.after_cancel(click_job)
    click_job = canvas.after(100, lambda: reset_click(canvas, state))

    # Provera pobede: #Promeniti nacin prikaza pobede#
    winner = check_win_condition(state, game_config["board_size"])    
    if winner:
        can_play = False
        messagebox.showinfo("KRAJ IGRE", f"Čestitamo! Pobednik je: {winner}")
        return
    
def reset_click(canvas, state):
    global clicked_cell
    old = clicked_cell
    clicked_cell = None
    update_cell_visual(canvas, old, state)

def on_resize(event, canvas, state):
    global resize_job
    if resize_job:
        canvas.after_cancel(resize_job)
    resize_job = canvas.after(80, lambda: perform_resize(canvas, state))

def draw_labels_around_board(canvas, board_size, width, height, base_unit):
    font_size = int(base_unit * 0.45)
    font_style = ("Arial", font_size, "bold")
    
    center_x = width / 2
    center_y = height / 2
    
    hex_radius = board_size * base_unit * 0.95
    
    label_offset = base_unit * 1.5
    
    y_top = center_y - hex_radius - label_offset
    
    num_cols = 2 * board_size - 1
    spacing_x = base_unit * 0.866
    start_x = center_x - (num_cols - 1) * spacing_x / 2
    
    for i in range(num_cols):
        letter = chr(ord('A') + i)
        x = start_x + i * spacing_x
        
        canvas.create_image(x, y_top, image=sprites["DARK"]["normal"])
        canvas.create_text(x, y_top, text=letter, fill="white", font=font_style)

    y_bottom = center_y + hex_radius + label_offset
    
    
    for i in range(num_cols):
        letter = chr(ord('A') + i)
        x = start_x + i * spacing_x
        
        canvas.create_image(x, y_bottom, image=sprites["DARK"]["normal"])
        canvas.create_text(x, y_bottom, text=letter, fill="white", font=font_style)

    num_rows = 2 * board_size - 1
    spacing_y = base_unit
    
    left_start_y = center_y - (num_rows / 4.5) * spacing_y / 2

    for i in range((num_rows // 2) + 1):
        number = str(i + 1)
        x = center_x - hex_radius * 1.25
        y = left_start_y + i * spacing_y
        
        canvas.create_image(x, y, image=sprites["DARK"]["normal"])
        canvas.create_text(x, y, text=number, fill="white", font=font_style)

    right_start_y = center_y - (num_rows * 1.6) * spacing_y / 2

    for i in range(num_rows // 2, num_rows):
        number = str(i + 1)
        x = center_x + hex_radius * 1.25
        y = right_start_y + i * spacing_y
        
        canvas.create_image(x, y, image=sprites["DARK"]["normal"])
        canvas.create_text(x, y, text=number, fill="white", font=font_style)
        
def perform_resize(canvas, state):
    global last_base_unit, board_texture_sprite, label_coords

    width = canvas.winfo_width()
    height = canvas.winfo_height()
    if width < 100 or height < 100: return

    board_size = game_config["board_size"]
    _, _, base_unit = get_canvas_coords(('A', 0), board_size, width, height)
    
    sizes = {
        "normal": int(base_unit * 0.92),
        "hover": int(base_unit * 1.05),
        "click": int(base_unit * 1.12),
    }

    for color in ["RED", "GREEN", "DARK", None]:
        for mode, size in sizes.items():
            key = (color, mode, size)
            if key not in sprite_cache:
                img = original_images[color]
                sprite_cache[key] = ImageTk.PhotoImage(
                    img.resize((size, size), Image.Resampling.BILINEAR)
                )
            sprites[color][mode] = sprite_cache[key]

    canvas.delete("all")
    cell_items.clear()

    if original_board_texture:
        board_texture_sprite = ImageTk.PhotoImage(
            original_board_texture.resize((width, height), Image.Resampling.BILINEAR)
        )
        canvas.create_image(0, 0, image=board_texture_sprite, anchor="nw")

    overlay_radius = (board_size + 0.5) * (base_unit * 0.95)
    canvas.create_oval(
        (width / 2) - overlay_radius, (height / 2) - overlay_radius,
        (width / 2) + overlay_radius, (height / 2) + overlay_radius,
        fill="#000000", stipple="gray50", width=2
    )

    draw_labels_around_board(canvas, board_size, width, height, base_unit)

    for cell in state:
        x, y, _ = get_canvas_coords(cell, board_size, width, height)
        tag = f"coord_{cell[0]}_{cell[1]}"
        item_id = canvas.create_image(
            x, y, 
            image=sprites[state[cell][0]]["normal"], 
            tags=("cell", tag)
        )
        cell_items[cell] = item_id
        canvas.tag_bind(
            item_id, 
            "<Button-1>", 
            lambda e, c=cell: handle_click(c, canvas, state)
        )

def draw(state):
    global current_player

    set_current_player("GREEN" if game_config["green_plays_first"] else "RED")

    root = tk.Tk()
    root.title(TITLE)
    root.geometry(RESOLUTION)

    load_resources()

    canvas = tk.Canvas(root, bg="#222", highlightthickness=0)
    canvas.pack(fill="both", expand=True)

    canvas.bind("<Motion>", lambda e: on_mouse_move(e, canvas, state))
    canvas.bind("<Configure>", lambda e: on_resize(e, canvas, state))

    root.after(100, lambda: perform_resize(canvas, state))

    root.mainloop()

def show_setup_menu():
    setup_root = tk.Tk()
    setup_root.title("Atoll - Podesavanja")
    setup_root.geometry("500x500")
    
    size_var = tk.StringVar(value = "5")
    mode_var = tk.StringVar(value = "H")
    symbol_var = tk.StringVar(value = "X")
    
    status = {"confirmed": False}

    tk.Label(setup_root, text="Velicina table:", font=("Arial", 10, "bold")).pack(pady=5)

    for s in [5, 7, 9]:
        tk.Radiobutton(setup_root, text=str(s), variable=size_var, value=str(s)).pack()

    tk.Label(setup_root, text="Režim igre:", font=("Arial", 10, "bold")).pack(pady=5)
    tk.Radiobutton(setup_root, text="Čovek protiv Čoveka", variable=mode_var, value="H").pack()
    tk.Radiobutton(setup_root, text="Čovek protiv Računara", variable=mode_var, value="A").pack()

    tk.Label(setup_root, text="Ko igra prvi?", font=("Arial", 10, "bold")).pack(pady=5)
    tk.Radiobutton(setup_root, text="X (Zeleni)", variable=symbol_var, value="X").pack()
    tk.Radiobutton(setup_root, text="O (Crveni)", variable=symbol_var, value="O").pack()

    def on_button_click():
        start_game(size_var.get(), mode_var.get(), symbol_var.get(), setup_root)
        status["confirmed"] = True

    tk.Button(
        setup_root, 
        text="ZAPOČNI IGRU", 
        command=on_button_click, 
        bg="green", 
        fg="white", 
        font=("Arial", 12, "bold")
    ).pack(pady=20)

    setup_root.mainloop()
    return status["confirmed"]

def start_game(size, mode, symbol, window_to_close):
        choose_board_size(size)
        choose_a_player(mode)
        choose_first_symbol(symbol)
        window_to_close.destroy()
