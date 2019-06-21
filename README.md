# StreamGauge
Boron Board layout:
D2 - Ultrasonic sensor Range start/stop
D3 - Timer done not used but availble incase deep sleep is used instead 
RX - Inverted serial circuit (mosfet inverter) to Serial output on Ultra Sonic sensor
A0 - not used but availble incase serial goes down and firmware is updated over the air
D8 - not used but availble incase deep sleep is used instead 

Particle Function:
sleep_time - takes in a time in seconds and updates the sleep time timer with it if anything other than a number or 0 is entered sleep will be disabled

Board name: boulder_creek1
