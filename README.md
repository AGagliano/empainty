# empainty
A watercolor palette for collaborative painting

The following are instructions for getting Empainty up and running. 


## Step 1: Build the Empainty palette box


* `palette_box_12x24.ai` has a laser cut template for constructing the box. 
* Attach 6 servos (we used sub-micro servos) to the inside back panel. We suggest velcro to make taking the lids on and off easier (for constructing and debugging purposes). Note, due to unidentifiable electronics issues we could only get 4 servos working, but left the middle 2 as placeholders.

<img src="https://github.com/AGagliano/empainty/blob/master/box_dimensions/palette_box_12x24.JPG" width=300>


* Schematic for the servos attached to Computer A:

<img src="https://github.com/AGagliano/empainty/blob/master/schematics/servos.png" width=300>


## Step 2: Set up the paint brushes


* With two paint brushes, attached an accelerometer (we used [MMA8452Q](https://www.sparkfun.com/products/12756)) to the top of the handle for each brush. Note, the accelerometers have to be at the same orientation so mark on the paint brush handles the orientation to hold them at. 


* Schematic for the accelerometer electronics. One accelerometer connected to Computer B; another accelerometer connected to Computer C.

<img src="https://github.com/AGagliano/empainty/blob/master/schematics/brush_accelerometer.png" width=300>


## Step 3: Setting up the code


On all computers place the libraries from this github in your Documents/Arduino/libraries folder


**Computer A:**
* Replace `Servo.h` and `Servo.cpp` in your computer in the following folder with the ones here: `Applications/Arduino.app/Contents/Java/libraries/Servo/src/` and `...src/avr`, respectively
* Open `empainty.ino`
* Open `Brushes_to_Arduino.pde` (make sure the port for myPort is set to the port your Arduino is connected to. Something like: "/dev/cu.usbmodem1441").
* Look up your IP address. This will be used in code on Computer B and Computer C to set up a TCP server for gestures that are recognized on computers B and C to then be sent to Computer A. 


**Computer B:** 
* Follow the instructions to install ESP by David Mellis: https://github.com/damellis/ESP (you can run ESP in Xcode or Processing)
* Open `user_accelerometer_gestures.cpp` from ESP examples
* Change the `TcpOStream oStream(“localhost”, 5204)` to `TcpOStream oStream(“IP address of Computer A”, <b>5203</b>)`
This will send the detected gestures over a TCP server to the Processing sketch on Computer A.
* Open `brush_accel.ino`


**Computer C:** 
* Follow the instructions to install ESP by David Mellis: https://github.com/damellis/ESP (you can run ESP in Xcode or Processing). If you want to train your own gestures later, you’ll want to follow the instructions in his tutorial.
* Open `user_accelerometer_gestures.cpp` from ESP examples
* Change the 
`TcpOStream oStream(“localhost”, 5204)` 
to 
`TcpOStream oStream(“IP address of Computer A”, 5204)`
This will send the detected gestures over a TCP server to the Processing sketch on Computer A.
* Open `brush_accel.ino`


## Step 4: Going live


* Computer A: upload `empainty.ino`
* Computer A: run `Brushes_to_Arduino.pde`
* Computer B and Computer C: run `user_accelerometer_gestures.cpp`
* Computer B and Computer C: in the GUI, select the port that your arduino is connected to
* Computer B and Computer C: Load up the `ESP_trained_gestures` folder from the GUI
* You should now have pre-trained brush strokes
* As you move the paintbrush around you should see predicted gesture numbers in the raw data. Computer A should see these numbers coming in their Processing console. 
* As the gestures come in, the palette box lids should move towards the ‘warmer’ or ‘cooler’ colors depending how similar/different the brush strokes are. 

<img src="https://github.com/AGagliano/empainty/blob/master/box_dimensions/IMG_0156.PNG" width=300>


Three computers need to be used because of limits on data flowing on Serial ports, Processing sketches that can be open, and Arduino sketches that can be open. Here's a schematic for the flow of information:

<img src="https://github.com/AGagliano/empainty/blob/master/communication_flow/communication.png" width=300>


*Debugging tips:* 
* You can set up a TCP Client on Computer A or Computer B to communicate with the TCP server set up by Processing sketch on Computer A. In the terminal on Computer A or Computer B: 
```nc ComputerAIPaddress port#```
* You can use the Pin 13 LED built into the arduino to debug from Computer A. Computer communicates over the Serial Port from Processing to Arduino, so you can’t open the Serial Monitor to debug with print statements because the port is in use. 
