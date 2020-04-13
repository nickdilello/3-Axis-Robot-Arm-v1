# 3-Axis-Robot-Arm-v1
Designed, constructed, and programmed a 3-axis robot arm for my PHYS 319 final project.

Designed in Solidworks; all parts 3D printed; the .stl files can be found on Thingiverse here: https://www.thingiverse.com/thing:4273165


Programmed in C for TI MSP430 Launchpad (MSP430G2553).

-controls three servos independently; used Timer_A0 (channel 1) and Timer_A1 (channel 1 & 2)

-used three pushbuttons wired in pull-down resistor configuration on GPIOs

-three preprogrammed motion paths that correspond to the three pushbuttons

-used RGB LED; no PWM just used red, green, blue


Hardware

-Texas Instruments MSP430G2553

-Breadboard/protoboard and various jumper wires

-servo 1 for base     --> Futaba FP S148

-servo 2 for arm      --> GWS S03N 2BB

-servo 3 for gripper  --> SM S2309S

-standard pushbuttons

-common cathode RGB LED

-various electrical components: 10kΩ resistors (x3), 560Ω resistors (x3), male header pins, etc.

Wiring

-servo 1 for base     --> P1.6 (TA0.1; Timer_A0, channel 1)

-servo 2 for arm      --> P2.2 (TA1.1; Timer_A1, channel 1)

-servo 3 for gripper  --> P2.4 (TA1.2; Timer_A1, channel 2)

-pushbutton 1         --> P2.0 (pull-down resistor config)

-pushbutton 2         --> P2.1 (pull-down resistor config)

-pushbutton 3         --> P2.3 (pull-down resistor config)

-Red pin on RGB LED   --> P1.4

-Blue pin on RGB LED  --> P1.5

-Green pin on RGB LED --> P1.7


If you have an questions or suggestions, let me know! Thanks!

