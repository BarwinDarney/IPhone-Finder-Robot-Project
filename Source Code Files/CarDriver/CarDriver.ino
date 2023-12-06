/* Shivam Patel
   Bonus Project EECS1011
   CarDriver
*/

// define IO pin
#define PWMA 5    // Controls power to right motor
#define PWMB 6    // Controls power to left motor
#define AIN 7     // Controls direction of right motor, HIGH = FORWARD, LOW = REVERSE
#define BIN 8     // Controls direction of right motor, HIGH = FORWARD, LOW = REVERSE
#define STBY 3    // Place H-Bridge in standby if LOW, Run if HIGH
bool isEnd = false;

void setup() {
  Serial.begin(9600);
  pinMode(PWMA, OUTPUT);     //set IO pin mode OUTPUT
  pinMode(PWMB, OUTPUT);
  pinMode(BIN, OUTPUT);
  pinMode(AIN, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);  //Enable Motors to run
  digitalWrite(PWMA, LOW);  // Fully on 
 
}

//main loop
void loop() {
  
  while(Serial.available() > 0){
    //Store data coming through the serial port in a variable
    int readData = Serial.parseInt();
    //If data that came through serial port is 1
    if (readData == 1){
      //Call on driveForward() method
      driveForward();
      //Delay of 5000ms
      delay(5000);
      //Call on checkRssi() method
      checkData();
    }
    //else if data that came through serial port is 2
    else if(readData == 2){
      //Call on turnLeft() method
      turnLeft();
      //Delay of 5000ms
      delay(5000);
      //Call on checkRssi() method
      checkData();
    }
    //else if data that came through serial port is 3
    else if(readData == 3){
      //Call on stop method
      stop();
    }
    else{
      Serial.println("Error");
    }  
  }

}
//Make method to check the data received through serial port
void checkData(){
  int readData = Serial.parseInt();
}
//Make method to drive forwards
void driveForward(){
  digitalWrite(AIN, HIGH); //Turn right motor on in forward direction
  digitalWrite(BIN, HIGH); //Turn right motor on in forward direction
  digitalWrite(PWMA, 1);   // speed of right motor
  digitalWrite(PWMB, 1);   // speed of left motor
  delay(200); //Delay of 200 ms
}
void turnLeft(){
  // Turn Car Left
  digitalWrite(BIN, HIGH);  //Turn left motor and only left motor in forward direction    
  digitalWrite(PWMB, 1); // speed of left motor 
  delay(200); //Delay of 200 ms
    
}
//Method to stop car from moving
void stop(){
  digitalWrite(PWMA, LOW);   // Turn power off on right motor
  digitalWrite(PWMB, LOW);   // Turn power off on left motor

  while(1); //An infinite loop so it is always in a stop state no matter what
}
