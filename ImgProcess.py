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
        img = np.array(PIL.Image.open(f"assets/{file}"))
       # img.setflags(write=1)
        for i in range(img.shape[0]):
            for j in range(img.shape[1]):
                row = img[i, j]
                img[i, j] = np.array((row[2], row[1], row[0], row[3]))
        sprite_name = file.split(".png")[0]
        look.writelines([f"{sprite_name},{img.shape[0]},{img.shape[1]}"])

        raw = img.tobytes()
        with open(f"assets/{sprite_name}.dat", "wb") as data:
            data.write(raw)
