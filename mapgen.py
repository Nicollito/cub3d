#!/usr/bin/env python3
"""
mapgen.py — générateur interactif de map cub3D (42)

- Map fermée bordée de '1'
- Zones praticables majoritaires ('0')
- Trous internes aléatoires (' ') influencés par la densité
- Murs internes aléatoires selon la densité
- Spawn joueur aléatoire (N, S, E, W)
- Aucun '2'
- Fichier .cub avec en-tête textures et couleurs
"""

import random

def ask_int(prompt, default=None, min_val=None, max_val=None):
    while True:
        val = input(f"{prompt} [{default if default is not None else ''}]: ")
        if val.strip() == "":
            if default is not None:
                return default
            continue
        try:
            val = int(val)
            if (min_val is not None and val < min_val) or (max_val is not None and val > max_val):
                print(f"Valeur doit être entre {min_val} et {max_val}")
                continue
            return val
        except ValueError:
            print("Entrez un entier valide.")

def ask_float(prompt, default=None, min_val=None, max_val=None):
    while True:
        val = input(f"{prompt} [{default if default is not None else ''}]: ")
        if val.strip() == "":
            if default is not None:
                return default
            continue
        try:
            val = float(val)
            if (min_val is not None and val < min_val) or (max_val is not None and val > max_val):
                print(f"Valeur doit être entre {min_val} et {max_val}")
                continue
            return val
        except ValueError:
            print("Entrez un nombre valide.")

def generate_map(width, height, hole_density):
    """Génère une map fermée avec zones praticables majoritaires et trous/murs internes influencés par la densité."""
    grid = [['1' for _ in range(width)] for _ in range(height)]

    # Remplissage de base : zones praticables
    for y in range(1, height - 1):
        for x in range(1, width - 1):
            grid[y][x] = '0'

    # Nombre de trous proportionnel à la densité
    num_holes = max(1, int(hole_density * (width * height) / 8))

    for _ in range(num_holes):
        hx = random.randint(1, width - 3)
        hy = random.randint(1, height - 3)

        # Taille des trous dépendante de la densité
        max_size = max(1, int(2 + hole_density * 10))
        w = random.randint(1, max_size)
        h = random.randint(1, max_size)

        for dy in range(h):
            for dx in range(w):
                nx = hx + dx
                ny = hy + dy
                if 1 <= nx < width - 1 and 1 <= ny < height - 1:
                    grid[ny][nx] = ' '

        # Entourer le trou de murs
        for dy in range(-1, h + 1):
            for dx in range(-1, w + 1):
                nx = hx + dx
                ny = hy + dy
                if 0 <= nx < width and 0 <= ny < height:
                    if grid[ny][nx] == '0' and (dx in (-1, w) or dy in (-1, h)):
                        grid[ny][nx] = '1'

    # Ajout de murs internes aléatoires dépendant de la densité
    num_internal_walls = int(hole_density * width * height / 5)
    for _ in range(num_internal_walls):
        if random.random() < 0.5:
            # Mur horizontal
            y = random.randint(2, height - 3)
            x_start = random.randint(2, width - 5)
            length = random.randint(2, int(4 + hole_density * 10))
            for x in range(x_start, min(width - 1, x_start + length)):
                if grid[y][x] == '0':
                    grid[y][x] = '1'
        else:
            # Mur vertical
            x = random.randint(2, width - 3)
            y_start = random.randint(2, height - 5)
            length = random.randint(2, int(4 + hole_density * 10))
            for y in range(y_start, min(height - 1, y_start + length)):
                if grid[y][x] == '0':
                    grid[y][x] = '1'

    # Placement du spawn joueur aléatoire sur une zone praticable
    empty_cells = [(x, y) for y in range(1, height - 1) for x in range(1, width - 1) if grid[y][x] == '0']
    if not empty_cells:
        px, py = width // 2, height // 2
    else:
        px, py = random.choice(empty_cells)
    grid[py][px] = random.choice(['N', 'S', 'E', 'W'])

    return grid

def render_map(grid):
    return "\n".join("".join(row) for row in grid)

def main():
    print("=== Générateur interactif de map cub3D ===")
    width = ask_int("Largeur de la map", default=random.randint(20, 40), min_val=10)
    height = ask_int("Hauteur de la map", default=random.randint(10, 20), min_val=10)
    hole_density = ask_float("Densité de trous/murs internes (0..1)", default=0.15, min_val=0, max_val=0.6)
    filename = input("Nom du fichier de sortie [.cub par défaut]: ").strip()
    if filename == "":
        filename = "random_map.cub"
    elif not filename.endswith(".cub"):
        filename += ".cub"

    grid = generate_map(width, height, hole_density)

    # En-tête cub3D
    header = (
        "C 163, 163, 163\n"
        "F 110, 110, 110\n\n"
        "EA texture_xpm/texture-_1_.xpm\n"
        "SO texture_xpm/texture-_2_.xpm\n"
        "WE texture_xpm/texture-_4_.xpm\n"
        "NO texture_xpm/texture-_5_.xpm\n\n"
    )

    content = header + render_map(grid) + "\n"

    with open(filename, "w") as f:
        f.write(content)

    print(f"\nMap générée et sauvegardée dans '{filename}' !")
    print("Aperçu :\n")
    print(render_map(grid))

if __name__ == "__main__":
    main()
