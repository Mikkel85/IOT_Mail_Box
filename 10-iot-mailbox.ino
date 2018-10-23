int count = 0;
// button is connected to D1
// We will be using D0 to control our LED
int LED = D0;

// Our button wired to D1
int buttonPin = D1;


void setup() {

#ifdef DEBUG
    Serial.begin(9600); // for debug purpose
#endif

pinMode( buttonPin , INPUT_PULLUP); // sets pin as input
  // We also want to use the LED
pinMode( LED , OUTPUT ); // sets pin as output
}

void loop() {

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
// retrieve information from API

// Send mail to user with API information and mailbox status

  Particle.publish("Mail_Test", String (count), PRIVATE); // Send a Email whit the "Text" and the variable.
#ifdef DEBUG
    Serial.println("Mail sent");
#endif
// go back to sleep loop. and wait for lid to be opend. 
while (1) {
  digitalWrite(LED,HIGH);
  delay(1000);
  digitalWrite(LED,LOW);
  delay(1000);
  }

}