# MiniGPS Tracking System

The MiniGPS Tracking System is a sophisticated project that enables users to track their distance between two locations based on GPS coordinates using the TM4C123G LaunchPad. In addition, the system provides visual cues to the user through built-in LEDs, indicating their proximity to the desired destination or when they have arrived. Users can choose from a list of available destinations to track their progress, and the project includes an LCD screen to display trajectory information.

## Real-time Trial Video

Here is a link to the real-time trial video of the MiniGPS Tracking System:

[insert link to video here]


## Features

The MiniGPS Tracking System offers the following features:

- Locating the starting coordinates of the user.
- Storing the coordinates of multiple destinations and displaying them on an LCD screen for the user to choose from.
- Allowing the user to navigate through the destinations using the buttons on the Tiva C LaunchPad.
- Displaying the moved distance and remaining displacement to the selected destination on the LCD screen when the user starts moving towards it.
- Providing visual feedback to the user using built-in LEDs:
  - Stage 1: Turning on the red LED when the target destination is far away by more than 5 meters.
  - Stage 2: Turning on the yellow LED when the target destination is about to be reached (less than 5 meters away).
  - Stage 3: Turning on the green LED when the target destination is reached.
  - In case of the signal is lost, the white LED will be turned on

The trajectory of the distance traveled should satisfy the following criteria:

- The total distance between the start and end point should be greater than 100 meters.
- The path from the start point to the end point should form a non-straight line similar to the provided baseline path.
- The calculated distance should be compared with the distance obtained from Google Maps, and the error margin should be less than or equal to 5%.

## How to Use

To use the MiniGPS Tracking System, you need to follow these steps:

1. Connect the TM4C123G LaunchPad to a GPS module and configure it to receive GPS coordinates.
2. Select the desired destination from the list of available destinations displayed on the LCD screen.
3. Navigate through the destinations using the buttons on the Tiva C LaunchPad.
4. Observe the visual feedback provided by the built-in LEDs:
   - Red LED: The target destination is far away by more than 5 meters.
   - Yellow LED: The target destination is about to be reached (less than 5 meters away).
   - Green LED: The target destination is reached.
5. Track your distance traveled and receive visual feedback using the built-in LEDs.

## Tools Used
<div style="display: flex; align-items: center;">
  <img src="https://www.ti.com/diagrams/ccstudio_ccs_256.jpg" alt="CCS" title="CCS" width="70" height="70">
  <h3 style="margin-left: 10px; color: #2596be;">CCS</h3>
</div>

<div style="display: flex; align-items: center;">
  <img src="https://www.theiconadvantage.com/wp-content/uploads/2014/08/ti-logo.png" alt="Tiva C LaunchPad" title="Tiva C LaunchPad" width="70" height="70">
  
  <h3 style="margin-left: 10px; color: #2596be;">Tiva C LaunchPad</h3>
</div>
<div style="display: flex; align-items: center;">
  <img src="https://downloadly.ir/wp-content/uploads/2018/08/Keil.png" alt="Keil" title="Keil" width="70" height="70">
  <h3 style="margin-left: 10px; color: #2596be;">Keil</h3>
</div>

## Programming Languages 

<div style="display: flex; align-items: center;"> <img src="https://www.chetu.com/img/on-demand-developers/embedded-c/logo/embeded-c.png" alt="Embedded C" title="[Embedded C](poe://www.poe.com/_api/key_phrase?phrase=Embedded%20C&prompt=Tell%20me%20more%20about%20Embedded%20C.)" width="70" height="70"> <h3 style="margin-left: 10px; color: #00aef0;">Embedded C</h3> </div>

## Credits

This Team project is part of the requiremtents of "Introduction to Embedded Systems" course.


## Contributers


## Real-time Trial Video

Here is a link to the real-time trial video of the MiniGPS Tracking System:

[insert link to video here]



































