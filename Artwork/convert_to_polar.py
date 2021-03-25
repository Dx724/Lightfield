from PIL import Image
import math

p = Image.open("mona_lisa.png")

w = p.width
h = p.height

center = (w/2, h/2)

NUM_POINTS = 500

dist = 0.95
print("led_off();")
is_first = True
while dist > 0.05:
    for ang in range(-180, 181, 5):
        polar_coord = (dist, ang)
        px = round(dist * w / 2 * math.cos(math.radians(ang)))
        py = round(dist * w / 2 * math.sin(math.radians(ang)))
        color = p.getpixel((px, py))
        print("do_arc({:.2f}, {}, {}, {}, {});".format(*polar_coord, *color))
        if is_first:
            print("led_on();")
            is_first = False
        dist -= (1/NUM_POINTS)*(0.95 - 0.05)
        if dist <= 0.05:
            break
    
