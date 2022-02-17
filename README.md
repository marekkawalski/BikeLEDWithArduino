<h1>Bike LED light with Arduino</h1>
<p>Arduino based bike led light with dusk sensor, several lighting modes and cree LEDs.
</p>
<h2>Table of contents</h2>
<ul>
  <li>
    <a href="#generalInfo">General info</a>
  </li>
      <li>
    <a href="#schematics">Schematics</a>
  </li>
    <li>
    <a href="#images">Images</a>
  </li>
  <li>
    <a href="#components">Base of components</a>
  </li>
   <li>
    <a href="#environment">Programming environment</a>
  </li>
  <li>
    <a href="#status">Project status</a>
  </li>
  </ul>
  <h2 id="generalInfo">General info</h2>
  <p>The goal of this project was to learn how to build a phisical device and write neccesary software to handle its functions.</p>
  <p>Speaking of the device itself, the purpose was to build a bike LED light which would ensure cyclist great visibility on the road. Due to that fact,
  it consists of two powerful cree LED's. The user of bike light has couple of flashing modes at their disposal. Morover, the light is capable
  of switching between day and night mode based on current environment lighting. In night mode, two diodes shine steady light or blink depending on current mode.
  In day mode, one of the lights is turned off so as to preserve battery. There is one exception to lighting modes, namely the last flashing mode 
  always blinks two LED's in an alternate way disregarding lighting conditions.
</p>
   <h2 id="schematics">Schematics</h2>
   <img src="https://user-images.githubusercontent.com/56251920/154494994-3eaf5bdc-31a2-4cb3-bad3-9e86e6b6eab8.png"></img>
   <img src="https://user-images.githubusercontent.com/56251920/154495173-4d816974-a184-40f9-bb2a-912f796c86f4.png"></img>
  <h2 id="images">Images</h2>
   <img width="300" src="https://user-images.githubusercontent.com/56251920/154498098-3b67fdb8-b456-499d-ada0-c63545bfbb00.jpg"></img>


   
  <h2 id="components">Base of components</h2> 
 <ul>
  <li>
   Arduino nano
  </li>
  <li>
    mosfet, channel n, 800V, 2A, 3.5oHm x2
  </li>
   <li>
   tact switch 12x12mm 
  </li>
   <li>
   battery bucket for four AA(R6) batteries
  </li>
   <li>
  Power LED diode 3W, white with radiator x2
  </li>
   <li>
   fototransistor L-53P3C 5mm 940 mm
  </li>
   <li>
   resistors 4,7k oHm, 22oHm, 1hoHm
  </li>
   <li>
   printed circuit board double sided 30x70mm
  </li>
  </ul>
   <h2 id="environment">Programming environment</h2> 
    <ul>
  <li>
   Visual studio code with platformio extension
  </li>
  </ul>
    <h2 id="status">Project status</h2> 
    <p>Finished</p>
  
  
  
