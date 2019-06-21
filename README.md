# StreamGauge
Boron Board layout: <br />
D2 - Ultrasonic sensor Range start/stop <br />
D3 - Timer done not used but availble incase deep sleep is used instead <br />
RX - Inverted serial circuit (mosfet inverter) to Serial output on Ultra Sonic sensor <br />
A0 - not used but available incase serial goes down and firmware is updated over the air <br />
D8 - not used but available incase deep sleep is used instead <br />
<br />
Particle Function <br />
sleep_time - takes in a time in seconds and updates the sleep time timer with it if anything other than a number or 0 is entered sleep will be disabled <br />
<br />
Board name: boulder_creek1
