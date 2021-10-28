import tkinter as tk
from tkinter import filedialog
import numpy as np
from PIL import Image

root = tk.Tk()
root.withdraw()

img_path = filedialog.askopenfilename(filetypes=(("Image files", "*.png;*.jpg;*.jpeg;*.bmp"), ("All files", "*.*")))
img = Image.open(img_path)
x, y = img.size
obj = img.load()

raw_rgb333_uint8 = np.zeros((9, 256), dtype=('uint8'))

adr = np.zeros(32, dtype=('uint8'))
adr = [8, 0, 9, 1, 10, 2, 11, 3, 12, 4, 13, 5, 14, 6, 15, 7]

for yi in range(y):
    for xi in range(x):
        r, g, b = obj[xi, yi]
        obj[xi, yi] = (r & 0b11100000, g & 0b11100000, b & 0b11100000)


def WriteByte(xi, yi, int_y):
    r, g, b = obj[xi, yi]
    if ((r & 0b10000000) > 0):
        raw_rgb333_uint8[0][int_y * 8 + (xi // 8)] |= (1 << (xi - 8 * (xi // 8)))
    if ((r & 0b01000000) > 0):
        raw_rgb333_uint8[1][int_y * 8 + (xi // 8)] |= (1 << (xi - 8 * (xi // 8)))
    if ((r & 0b00100000) > 0):
        raw_rgb333_uint8[2][int_y * 8 + (xi // 8)] |= (1 << (xi - 8 * (xi // 8)))
    if ((g & 0b10000000) > 0):
        raw_rgb333_uint8[3][int_y * 8 + (xi // 8)] |= (1 << (xi - 8 * (xi // 8)))
    if ((g & 0b01000000) > 0):
        raw_rgb333_uint8[4][int_y * 8 + (xi // 8)] |= (1 << (xi - 8 * (xi // 8)))
    if ((g & 0b00100000) > 0):
        raw_rgb333_uint8[5][int_y * 8 + (xi // 8)] |= (1 << (xi - 8 * (xi // 8)))
    if ((b & 0b10000000) > 0):
        raw_rgb333_uint8[6][int_y * 8 + (xi // 8)] |= (1 << (xi - 8 * (xi // 8)))
    if ((b & 0b01000000) > 0):
        raw_rgb333_uint8[7][int_y * 8 + (xi // 8)] |= (1 << (xi - 8 * (xi // 8)))
    if ((b & 0b00100000) > 0):
        raw_rgb333_uint8[8][int_y * 8 + (xi // 8)] |= (1 << (xi - 8 * (xi // 8)))

    r, g, b = obj[xi, yi + 16]
    if ((r & 0b10000000) > 0):
        raw_rgb333_uint8[0][int_y * 8 + (xi // 8) + 128] |= (1 << (xi - 8 * (xi // 8)))
    if ((r & 0b01000000) > 0):
        raw_rgb333_uint8[1][int_y * 8 + (xi // 8) + 128] |= (1 << (xi - 8 * (xi // 8)))
    if ((r & 0b00100000) > 0):
        raw_rgb333_uint8[2][int_y * 8 + (xi // 8) + 128] |= (1 << (xi - 8 * (xi // 8)))
    if ((g & 0b10000000) > 0):
        raw_rgb333_uint8[3][int_y * 8 + (xi // 8) + 128] |= (1 << (xi - 8 * (xi // 8)))
    if ((g & 0b01000000) > 0):
        raw_rgb333_uint8[4][int_y * 8 + (xi // 8) + 128] |= (1 << (xi - 8 * (xi // 8)))
    if ((g & 0b00100000) > 0):
        raw_rgb333_uint8[5][int_y * 8 + (xi // 8) + 128] |= (1 << (xi - 8 * (xi // 8)))
    if ((b & 0b10000000) > 0):
        raw_rgb333_uint8[6][int_y * 8 + (xi // 8) + 128] |= (1 << (xi - 8 * (xi // 8)))
    if ((b & 0b01000000) > 0):
        raw_rgb333_uint8[7][int_y * 8 + (xi // 8) + 128] |= (1 << (xi - 8 * (xi // 8)))
    if ((b & 0b00100000) > 0):
        raw_rgb333_uint8[8][int_y * 8 + (xi // 8) + 128] |= (1 << (xi - 8 * (xi // 8)))


int_y = 0
for yi in adr:
    for xi in range(x):
        WriteByte(xi, yi, int_y)
    int_y += 1

img.show()

switcher_color = {
    0: "Color Red1:",
    1: "Color Red2:",
    2: "Color Red3:",
    3: "Color Green1:",
    4: "Color Green2:",
    5: "Color Green3:",
    6: "Color Blue1:",
    7: "Color Blue2:",
    8: "Color Blue3:"
}

raw_path = img_path + '.to_MC_RGB333'
print("Массив rgb333 для MC:")
for i in range(9):
    print('\n' + switcher_color.get(i, "Invalid color"))
    St_bin = ""
    for j in range(256):
        if (j % 8) == 0:
            St_bin += '\n'
        St_bin += str(format(raw_rgb333_uint8[i, j], 'b')).rjust(8, "0")  # + " "
    print(St_bin)

file = open(raw_path, 'w')
for i in range(9):
    for j in range(256):
        if (j == 0) and (i == 0):
            file.write(str(raw_rgb333_uint8[i, j]))
        else:
            file.write(',' + str(raw_rgb333_uint8[i, j]))
file.close()
print("Сохранено в файл: ", raw_path)

input()
