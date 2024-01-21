# RGBLed_controller
RGB Led controller from IR remote

Inspired from the projet https://www.engineersgarage.com/how-to-build-an-ir-remote-operated-rgb-led-strip-using-arduino/

## In comparison to the classical chinese controller, this one 
- starts with leds off
- stores the current state of the led strip and uses this stored state with the led strip is plugged in.


## Controller made with :
- An arduino uno
- A TSPO1738 IR receiver
- A ULN2003A chip to control the leds (R, G, and B outputs)

![Alt text](img/IR-RGB-LED-Arduino-Circuit.png?raw=true "Diagram")
