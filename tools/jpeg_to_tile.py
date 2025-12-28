from PIL import Image
import sys
import os

TILE_SIZE = 16


def xterm_palette():
    palette = []

    # 0–15: system colors (approximate)
    system = [
        (0,0,0),(128,0,0),(0,128,0),(128,128,0),
        (0,0,128),(128,0,128),(0,128,128),(192,192,192),
        (128,128,128),(255,0,0),(0,255,0),(255,255,0),
        (0,0,255),(255,0,255),(0,255,255),(255,255,255)
    ]
    palette.extend(system)

    # 16–231: 6×6×6 RGB cube
    steps = [0, 95, 135, 175, 215, 255]
    for r in steps:
        for g in steps:
            for b in steps:
                palette.append((r, g, b))

    # 232–255: grayscale
    for i in range(24):
        v = 8 + i * 10
        palette.append((v, v, v))

    return palette


def color_distance(c1, c2):
    # perceptual weighting
    dr = c1[0] - c2[0]
    dg = c1[1] - c2[1]
    db = c1[2] - c2[2]
    return 0.2126*dr*dr + 0.7152*dg*dg + 0.0722*db*db

PALETTE = xterm_palette()
def rgb_to_xterm256(r, g, b):
    best_index = 0
    best_dist = float("inf")

    for i, (pr, pg, pb) in enumerate(PALETTE):
        d = color_distance((r,g,b), (pr,pg,pb))
        if d < best_dist:
            best_dist = d
            best_index = i

    return best_index


def convert_image(input_path, output_path):
    img = Image.open(input_path).convert("RGB")
    img = img.resize((TILE_SIZE, TILE_SIZE), Image.BILINEAR)

    pixels = img.load()

    with open(output_path, "w") as f:
        f.write(f"{TILE_SIZE} {TILE_SIZE}\n")
        for y in range(TILE_SIZE):
            for x in range(TILE_SIZE):
                r, g, b = pixels[x, y]
                color = rgb_to_xterm256(r, g, b)
                f.write(f"{color:3d} ")
            f.write("\n")

    print(f"Converted {input_path} -> {output_path}")


def convert_folder(input_dir, output_dir):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    for filename in os.listdir(input_dir):
        if not filename.lower().endswith(".png"):
            continue

        input_path = os.path.join(input_dir, filename)
        name, _ = os.path.splitext(filename)
        output_path = os.path.join(output_dir, name + ".tile")

        convert_image(input_path, output_path)
        print(f"Converted: {filename} → {name}.tile")


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: jpg_to_tile.py input.jpg output.tile")
        sys.exit(1)

    convert_folder(sys.argv[1], sys.argv[2])