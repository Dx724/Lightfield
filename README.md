# Lightfield <!-- omit in toc -->
## Unvisualized data in the world around us

Our universe is filled with data. Every raindrop that falls, star that twinkles, or car that moves represents another rich datapoint in our vast and awe-inspiring world. Yet, to the average human onlooker, it's just "random".

Lightfield aims to emphasize this point by presenting artwork stretched along the temporal dimension. A light moves around and changes colors rapidly, following paths with beautiful swirls, arcs, and lines. To a human audience, this looks like a mix between a gracefully choreographed dance and the flashing lights of an airplane passing overhead -- cool and abstract, but not very meaningful.

Yet, from a computational point of view, each infintesimal slice of this movement holds substantial information. By taking a long exposure photograph of the sculpture, one can view the patterns that emerge. What was once some wooden sticks on a can of mixed nuts becomes _Mona Lisa_, or perhaps _The Starry Night_.

# Setup
## Hardware
The sculpture contains an ESP32 microcontroller which polls an [external API](https://github.com/mbennett12/kinetic-sculpture-webapi) for a start signal, translates from abstract image representations to physical paths, orchestrates motor movements, and varies the emitted colors. Specifically, a FreeNove ESP32-WROVER-DEV module was used here.

The device also contained a stepper motor driven by a ULN2003 IC, a 9g micro servo, and an RGB LED.

## Mechanical Structure
The enclosure of this device was based on a large cylindrical can, paralleling the radial canvas of the system. However, any hollow container which can be opened will suffice.
1. Drill a hole into the top surface of the container at the center large enough to fit the stepper motor.
2. Insert the stepper motor and drill two additional holes for the mounting points.
3. Thread M3 bolts through the two mounting holes and secure with nuts on the other side.
4. Drill two holes along the "long" axis of a popsicle stick near on end so that the shaft of the stepper motor can be friction fit within.
5. Using the [Servo_Test sketch](Test%20Programs/Servo_Test/Servo_Test.ino), rotate the servo to 180°.
6. Attach a four-pronged servo arm to the servo, but before screwing it in, drill a hole near the end of another popsicle stick and thread the screw through that hole and then into the servo. The stick should be attached so that if it points "down" at 180°, it will point "left" at 90° (the Servo_Test sketch can be modified to validate this).
7. Mount the servo to the unconnnected end of the stepper motor popsicle stick so that at 180°, the popscicle stick of the servo points directly towards the stepper motor shaft.
8. Mount the RGB LED at the unconnected end of the servo motor popsicle stick so that it points upwards. This can be achieved by bending the LED's pins at a 90° angle.
9. Cut a small hole at any point along the upper edge of the cylindrical enclosure to allow wires (for the stepper motor, servo motor, and RGB LED) to pass through.
10. Place a smaller can (or other object) inside of the larger can and place the ESP32 inside the larger can, supported by the smaller can, so that it is oriented vertically.
11. Drill a hole on the side surface near the bottom of the larger can. Pass a USB cable through this hole and connect it to the ESP32.
12. Wire up the electronics as described in [ESP32 Wiring](#esp32-wiring) and then close the enclosure.
   
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

_Note that sufficiently long wires (on the order of two popsicle stick lengths) should be used to connect the servo motor and the RGB LED to the ESP32 so as to allow connections to remain intact at the furthest extent of the movement range._
1. Connect the servo's VCC line to a 5V source.
2. Connect the servo's GND line to that source's GND (common with the ESP32's supply).
3. Connect the servo's Signal line to GPIO 15 on the ESP32.

__RGB LED__

_Note that a common anode RGB LED was used. See [Common Cathode LEDs](#common-cathode-leds) below for common cathode LED usage instructions._
1. Connect the common anode to a 3.3V supply.
2. Connect the red LED cathode to GPIO 33 through a 220 Ω resistor.
3. Connect the green LED cathode to GPIO 32 through a 220 Ω resistor.
4. Connect the blue LED cathode to GPIO 4 through a 220 Ω resistor.