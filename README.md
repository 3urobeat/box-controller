# box-controller
Firmware for my portable PA system with an Arduino Nano & LCD display  

&nbsp;

This firmare pulls the power consumption and current case air temperature every 10ms.  
Sensors used:  
- L01Z100S05 measures power draw of both amplifiers
- Dallas 18B20 measures air temp between amplifiers at the top

&nbsp;

The values are displayed every 250ms on a 4x20 LCD display on the side.  
Display Content:  
- Title and Uptime
- Divider row, empty
- Current temperature (with 2 step high temp warning system)
- Current power draw, average power draw (10 seconds), peak power/watt hours since poweron (flips every 5 seconds)

&nbsp;

Furthermore the title and divider row cycle through a few simple animations:
- Title displayed in lowercase with one character capitalized, moving left to right
- Bar of dashes moving through divider row, left to right
- Title replaced by underscores, title is moving in from right to left

&nbsp;

## Pictures:
Display and side with controls:  
<div>
  <img width=45% height:auto src="https://raw.githubusercontent.com/3urobeat/box-controller/main/.github/img/display.JPG">  
  <img align="right" width=45% height:auto src="https://raw.githubusercontent.com/3urobeat/box-controller/main/.github/img/side.JPG">  
</div>

&nbsp;

Front and back (open, without backplate):  
<div>
  <img width=45% height:auto src="https://raw.githubusercontent.com/3urobeat/box-controller/main/.github/img/front.JPG">  
  <img align="right" width=45% height:auto src="https://raw.githubusercontent.com/3urobeat/box-controller/main/.github/img/back.JPG">  
</div>