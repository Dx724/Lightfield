# Lightfield <!-- omit in toc -->
## Unvisualized data in the world around us

Our universe is filled with data. Every raindrop that falls, star that twinkles, or car that moves represents another rich datapoint in our vast and awe-inspiring world. Yet, to the average human onlooker, it's just "random".

Lightfield aims to emphasize this point by presenting artwork stretched along the temporal dimension. A light moves around and changes colors rapidly, following paths with beautiful swirls, arcs, and lines. To a human audience, this looks like a mix between a gracefully choreographed dance and the flashing lights of an airplane passing overhead -- cool and abstract, but not very meaningful.

Yet, from a computational point of view, each infintesimal slice of this movement holds substantial information. By taking a long exposure photograph of the sculpture, one can view the patterns that emerge. What was once some wooden sticks on a can of mixed nuts becomes _Mona Lisa_, or perhaps _The Starry Night_.

# Setup
## Hardware
The sculpture contains an ESP32 microcontroller which polls an [external API](https://github.com/mbennett12/kinetic-sculpture-webapi) for a start signal, translates from abstract image representations to physical paths, orchestrates motor movements, and varies the emitted colors. Specifically, a FreeNove ESP32-WROVER-DEV module was used here.

The device also contained a stepper motor driven by a ULN2003 IC, a 9g micro servo, and an RGB LED.

## ESP32 Wiring
__Stepper Motor__
1. Connect the motor driver's pin IN1 to GPIO 14.
2. Connect the motor driver's pin IN2 to GPIO 27.
3. Connect the motor driver's pin IN3 to GPIO 26.
4. Connect the motor driver's pin IN4 to GPIO 25.
5. Connect the stepper's pins A-D to the motor driver's pins A-D, matching the respective letters.
6. Connect the stepper's PWR pin to the motor driver's PWR output pin.
7. Connect the motor driver's GND to the ESP32's GND.
8. Connect the motor driver's VCC and PWR input pins to a 5V source (with common ground between that source and the ESP32).

__Servo Motor__
1. Connect the servo's VCC line to a 5V source.
2. Connect the servo's GND line to that source's GND (common with the ESP32's supply).
3. Connect the servo's Signal line to GPIO 15 on the ESP32.