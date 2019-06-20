// -----------------------------------------
// Ultrasonic Range Finder driver code
// -----------------------------------------
// Code to take distance reading (30cm- 5m) from Mb7630 ultrasonic sensor and output variable data to particle console
// RX pin5 on ultrasound sensor for rs232 serial communication
#include <math.h>
#define RANGE D2

unsigned long last_time = 0;
unsigned long sleep_time = 60; // either sample once a min or sample once every 10m tells us how long we sleep for

int success = 0;      // sensor status
int sleep_enable = 1; //default to sleeping
int serial_value = 0; // sensoring reading value

FuelGauge fuel; // to monitor battery

void setup()
{
    Particle.function("sleep_time", change_Ts); //function to change sample freq ie sleep time
    Particle.publish("status", "entering loop", 60, PRIVATE);
    delay(4000);

    pinMode(RANGE, OUTPUT);   // analog reading pin set up
    digitalWrite(RANGE, LOW); //sensor real time reads!

    Serial.begin(9600);
    Serial1.begin(9600, SERIAL_8N1); // serial 8 bit no parity 1 stop bit
    //    Serial.println("entering loop");
}

// Next is the loop function...
void loop()
{
    int j = 0;
    float sensor_avg = 0;
    
    // take up to ten samples 
    for (int i = 0; i < 10; i++)
    {
        success = read_sensor();
        if (success)
        {
            sensor_avg += serial_value;
            j++;
        }
    }

    //if sensor was read take average of number of samples read publish sensor, battery level, and sleep status
    if (j > 0)
    {
        sensor_avg = sensor_avg / j;
        float bp = (fuel.getSoC() / 88) * 100; // Battery State of Charge, where 81.24 is max value
        // Format string for submission to CHORDS
        String data = String::format(
            "{"
            "\"gauge\":%.2f,"
            "\"bat_soc\":%.2f,"
            "\"sleep_stat\":%d"
            "}",
            sensor_avg,
            bp,
            sleep_enable);
        Particle.publish("gauge", data);
        delay(4000);

        if (sleep_enable)
        {
            Particle.publish("status","sleeping");
            delay(5000);
            nap_time();
        }
    }
}

// message format in asci R start 4 ascii digits cr (13) terminate
int read_sensor()
{
    int serial_reading = 0;
    serial_value = 0;          //reset last reading
    digitalWrite(RANGE, HIGH); //trigger real time reading
    delay(1);
    digitalWrite(RANGE, LOW); //sensor needs to be reset to take new reading before serial data send completed

    // read first bit
    if (Serial1.available() > 0)
    {
        serial_reading = Serial1.read();
        delay(3);
    }

    if (serial_reading == 82)
    {
        for (int i = 0; i < 4; i++)
        {
            if (Serial1.available() > 0)
            {
                // read the incoming byte:
                serial_reading = Serial1.read();
                delay(3);
            }
            serial_reading = serial_reading - 48; //  ascii to dec
            //single digit expected
            if (serial_reading > 9)
            {
                return 0;
            }
            serial_value += serial_reading * pow(10, (3 - i)); //  place value calc.
        }

    //    Serial.println(serial_value);
        // Read data end bit
        if (Serial1.available() > 0)
        {
            serial_reading = Serial1.read();
            delay(3);
        }
        if (serial_reading == 13)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //start bit missed
    else
    {
        return 0;
    }
}

// Sleep for 10m-sensor read time
void nap_time()
{
    digitalWrite(RANGE, LOW); //turn off sensor so no current
    //Serial.println("going to sleep now timer triggered to start!");
    System.sleep(D8, RISING, SLEEP_NETWORK_STANDBY, sleep_time); //10s sleep
}

int change_Ts(String command)
{
    //Serial.println("sample rate changing");
    sleep_time = command.toInt();
    if (sleep_time)
    {
        return 1;
    }
    else
    {
        sleep_enable = 0;
        return 0;
    }
}
