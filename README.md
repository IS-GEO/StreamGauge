# StreamGauge
## Boron Board layout: 
D2 - Ultrasonic sensor Range start/stop <br />
D3 - Timer done not used but availble incase deep sleep is used instead <br />
RX - Inverted serial circuit (mosfet inverter) to Serial output on Ultra Sonic sensor <br />
A0 - not used but available incase serial goes down and firmware is updated over the air <br />
D8 - not used but available incase deep sleep is used instead <br />
<br />
## Particle Functions
sleep_time - takes in a time in seconds and updates the sleep time timer with it if anything other than a number or 0 is entered sleep will be disabled <br />
<br />
Board name: boulder_creek1 <br />
## OTA programming
1. [Set up CLI tools](https://docs.particle.io/reference/developer-tools/cli/) and login to particle account (see google doc) <br />
2. Compile code: particle compile boron “your_file.ino” <br />
3. Refer to console to turn off sleep state <br />
4. Flashing: particle flash boulder_creek1 “your_bin_file.bin” <br />
5. Refer to [console](console.particle.io) for success or failure logging <br />

