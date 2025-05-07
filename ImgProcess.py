import PIL
import PIL.Image
import numpy as np
import os

'''
    DOBrien
    SDLDoom PNG to Sprite Utility

    Converts PNG images in this directory
    to raw bytes

    Stores metadata for each sprite in the 
    lookup table "lookup.txt"
'''


files = [i for i in os.listdir("assets/") if ".png" in i]
with open("assets/lookup.txt", "w") as look:
    for file in files:
        img = np.asarray(PIL.Image.open(f"assets/{file}"))
        sprite_name = file.split(".png")[0]
        look.writelines([f"{sprite_name},{img.shape[0]},{img.shape[1]}"])

        raw = img.tobytes()
        with open(f"assets/{sprite_name}.dat", "wb") as data:
            data.write(raw)
