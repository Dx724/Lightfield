from PIL import Image
import math

p = Image.open("The-Starry-Night.jpg")

w = p.width
h = p.height

center = (w/2, h/2)

NUM_POINTS = 1500

data_r = []
data_a = []
data_c = []

with open("artwork.h", "w+") as f:
    dist = 0.95
    f.write("void do_arc(double rad, double ang, byte r, byte g, byte b);\n")
    f.write("void led_off();\n\n")
    f.write("void do_artwork() {\n")
    while dist > 0.05:
        f.write("\tled_off();\n")
        for ang in range(-180, 181, 4):
            polar_coord = (dist, ang)
            px = round(w/2 + dist * w / 2 * math.cos(math.radians(ang)))
            py = round(w/2 + dist * w / 2 * math.sin(math.radians(ang)))
            color = p.getpixel((px, py))
            f.write("\tdo_arc({:.2f}, {}, {}, {}, {});\n".format(*polar_coord, *color))
            data_r.append(dist)
            data_a.append(ang*math.pi/180)
            data_c.append((color[0]/255, color[1]/255, color[2]/255))
            dist -= (1/NUM_POINTS)*(0.95 - 0.05)
            if dist <= 0.05:
                break
    f.write("}\n")

import matplotlib.pyplot as plt

ax = plt.subplot(111, projection='polar')
ax.scatter(data_a, data_r, c=data_c)
plt.show()
