/*
  React! 
  Game Logic
  Spark Design Club
  
  v1 (Nov 10)
  Game has two two states: idle and active.
  in idle, it keeps flashing the SPARK and looks for a swipe of the sign.
  once SPARK is swiped, game goes into active mode.
  the game randomly flashes a button, and waits for a predetermined time for a button press. if
  it detects it within the timespan, the next button is flashed. the game becomes progressively harder,
  as the time within which the button has to be pressed reduces.
  
  TODO: decide what the minimum distance should a hand from the sensor to be considered a "swipe"?
        testing
*/

int spark1_led = 13, spark2_led = 12, spark3_led = 11, spark4_led = 10, spark5_led = 9;

int spark1_sensor = 1, spark2_sensor = 2, spark3_sensor = 3, spark4_sensor = 4, spark5_sensor = 5;
int spark1_sensorVal, spark2_sensorVal, spark3_sensorVal, spark4_sensorVal, spark5_sensorVal;

int but[] = {8, 7, 6}; /* buttons: 8=tri, 7=sq, 6=hex */

int but_led[] = {5, 4, 3}; /* leds on the button: 6=tri, 5=sq, 4=hex */


int state = 0; /* 0: idle, 1: active */

long sequenceDelay = 2500; /* need to experiment with this number */
long flashDelay = 1000;    /* need to experiment with this number */
long waitUntils1 = 0;
long waitUntils2 = sequenceDelay;
long waitUntils3 = sequenceDelay*2;
long waitUntils4 = sequenceDelay*3;
long waitUntils5 = sequenceDelay*4;

boolean s1_ledstate = false;
boolean s2_ledstate = false;
boolean s3_ledstate = false;
boolean s4_ledstate = false;
boolean s5_ledstate = false;
boolean correct_swipe = false;

void setup() {
   pinMode(spark1_led, OUTPUT);
   pinMode(spark2_led, OUTPUT);
   pinMode(spark3_led, OUTPUT);  
   pinMode(spark4_led, OUTPUT);
   pinMode(spark5_led, OUTPUT);
   
   //set up the three buttons
   for (int p = 0; p < 3;  p++) {
       pinMode(but[p], INPUT);
   }
   
   //set up the three leds on the buttons
   for (int p = 0; p < 3;  p++) {
       pinMode(but_led[p], OUTPUT);
   }
}

void loop() {
  if (!state) {
     digitalWrite(spark1_led, s1_ledstate);
     digitalWrite(spark2_led, s2_ledstate);
     digitalWrite(spark3_led, s3_ledstate);
     digitalWrite(spark4_led, s4_ledstate);
     digitalWrite(spark5_led, s5_ledstate);
     
     if (millis() >= waitUntils1) {
         s1_ledstate = !(s1_ledstate);
         waitUntils1 += flashDelay;
     }  
     if (millis() >= waitUntils2) {
         s2_ledstate = !(s2_ledstate);
         waitUntils2 += flashDelay;
     }
     if (millis() >= waitUntils3) {
         s3_ledstate = !(s3_ledstate);
         waitUntils3 += flashDelay;
     }
     if (millis() >= waitUntils4) {
         s4_ledstate = !(s4_ledstate);
         waitUntils4 += flashDelay;
     }
     if (millis() >= waitUntils5) {
         s5_ledstate = !(s5_ledstate);
         waitUntils5 += flashDelay;
     }
     
     state = check_swipe();
  }  

  if (state) {
     //we are starting the game. turn the SPARK sign on for 2 seconds to signify the start. 
     digitalWrite(spark1_led, HIGH);
     digitalWrite(spark2_led, HIGH);
     digitalWrite(spark3_led, HIGH);
     digitalWrite(spark4_led, HIGH);
     digitalWrite(spark5_led, HIGH);
     delay(2000);
     digitalWrite(spark1_led, LOW);
     digitalWrite(spark2_led, LOW);
     digitalWrite(spark3_led, LOW);
     digitalWrite(spark4_led, LOW);
     digitalWrite(spark5_led, LOW);  
  
     int lost = 0;
     float hardFactor = 0.95; /* how quickly the "level" of the game ramps up */
     int button_delay = 1000;    
     int maxPressDelay = 150;
     int elapsedTime = 0;
     int butVal = 0;
     int whichButton = 0;
     while (1) {
         //first button
         whichButton = random(0, 100) % 3;     
         digitalWrite(but_led[whichButton], HIGH);
         while (elapsedTime <= maxPressDelay && butVal != 1){
             butVal = digitalRead(but[whichButton]);  
             delay(1);
             elapsedTime++;
         }         
         if (butVal != 1){
             break;
         }   
         
         //second button    
         whichButton = random(0, 100) % 3;     
         digitalWrite(but_led[whichButton], HIGH);
         while (elapsedTime <= maxPressDelay && butVal != 1){
             butVal = digitalRead(but[whichButton]);  
             delay(1);
             elapsedTime++;
         }
         if (butVal != 1){
             break;
         }    
         
         //third button
         whichButton = random(0, 100) % 3;     
         digitalWrite(but_led[whichButton], HIGH);
         while (elapsedTime <= maxPressDelay && butVal != 1){
             butVal = digitalRead(but[whichButton]);  
             delay(1);
             elapsedTime++;
         }
         if (butVal != 1){
             break;
         }      
         
         maxPressDelay *= hardFactor;    
     } 
    
  }  
    
}

int check_swipe(){
     spark1_sensorVal = analogRead(spark1_sensor); 
     spark2_sensorVal = analogRead(spark2_sensor); 
     spark3_sensorVal = analogRead(spark3_sensor); 
     spark4_sensorVal = analogRead(spark4_sensor); 
     spark5_sensorVal = analogRead(spark5_sensor);
     
     if (spark1_sensorVal == 1 && spark1_sensorVal && spark1_sensorVal && spark1_sensorVal && spark1_sensorVal){
       return 1;
     }
     else {
       return 0;
     }      
}
  


