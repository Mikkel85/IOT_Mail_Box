// This #include statement was automatically added by the Particle IDE.
#include <SparkJson.h>

// include if serial debuf infor is needed.
#define DEBUG

//mail counter to see how many mails has bene sent
int count = 1;
// We will be using D0 to control our LED
int LED = D0;
// Our button wired to D1
int buttonPin = D1;
// variable to count.
int i = 0;
// variable to storre converted temperature (celcius)
float tempC = 0;
// variable for the weather summary
String summary = "test";

void setup() 
{
    #ifdef DEBUG
        Serial.begin(9600); // for debug purpose
        while (!Serial) {
        // wait serial port initialization
        }
        Serial.println("Serial Ready");
    #endif

    pinMode( buttonPin , INPUT_PULLUP); // sets pin as input
    // We also want to use the LED
    pinMode( LED , OUTPUT ); // sets pin as output
}

void myHandler(const char *event, const char *data)
        {
        DynamicJsonBuffer jsonBuffer;
        
        JsonObject& root = jsonBuffer.parseObject((char*)data);
        
        if (!root.success()) {
            #ifdef DEBUG
            Serial.println("Parse Failed");
            #endif
        return;
        }
        else
        {
            // get weather summary from the API
            summary = root["currently"]["summary"].asString();
            // get current temp in farenheight from the API 
            float tempF = root["currently"]["temperature"];
            // convert temp to celcius
            tempC = (tempF-32)/1,8;
        }

        /*
        i++;
        Serial.print(i);
        Serial.print(event);
        Serial.print(", data: ");
        if (data)
            Serial.println(data);
        else
        Serial.println("NULL");
        */
}

void loop() 
{
    while (1) // while loop to keep the program running
    {
        // wait for button pres to wake up (lid opens)
        // Put the device into stop mode with wakeup using RISING edge 
        //interrupt on D1 pin
        System.sleep(D1,FALLING,0);
        // The device LED will shut off during sleep
        //CHANGE to trigger the interrupt whenever the pin changes value,
        //RISING to trigger when the pin goes from low to high,
        //FALLING for when the pin goes from high to low
        // wakeup after the specified number of seconds (0 = no alarm is set)
        #ifdef DEBUG
            Serial.println("Avaking from sleep");
        #endif
        // wait for wifi conection
        //waitUntil(Particle.connected); // wait until 
        waitUntil(WiFi.ready); // wait until it has connected to wifi
        #ifdef DEBUG
            Serial.println("Wifi Connected");
        #endif


        // retrieve information from API
        Particle.subscribe("hook-response/darkSkyWeather", myHandler, MY_DEVICES);

        // Send mail to user with API information and mailbox status
        Particle.publish("Weather_Mail", String (summary), float (tempC), PRIVATE);
            
        // Send a Email whit the "Text" and the variable.
        #ifdef DEBUG
            Serial.println("Mail sent");
        #endif

        // loop to catch program under development
        while (1) 
        {
            digitalWrite(LED,HIGH);
            delay(1000);
            digitalWrite(LED,LOW);
            delay(1000);
        }
    }
}