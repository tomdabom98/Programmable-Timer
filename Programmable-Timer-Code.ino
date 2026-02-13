#include <TM1638plus.h>

// Define TM1638 module connections
const int stb=7;
const int clk=4;
const int dio=2;
TM1638plus tm(stb, clk, dio);

// Define buzzer pin
 const int Buzzer=12;
unsigned int users = 1; bool timeset=false;
int initialTime=0;
int seconds = 0; int seconds2 = 0; int seconds3 = 0; int seconds4=0;
unsigned int minutes = seconds/60;
int flag01=2; int flag02=2; int flag03=2; int flag04=2;


void SetUsers(bool userset){
  Serial.println();
  Serial.println("Press S1 for 2 users, S2 for 3 users or S3 for 4 users.");
  flag01=flag02=flag03=flag04=0;
  while(userset==false){
    if(tm.readButtons()==0x01){
      users=2;userset=true;
    }
    if(tm.readButtons()==0x02){
      users=3;userset=true;
    }
    if(tm.readButtons()==0x04){
      users=4;userset=true;
    }
  } 
}
 void SetTime(bool timeset){
  int seconds=0;
  while (timeset=false){
    tm.displayIntNum(seconds,true,TMAlignTextLeft);
    if (tm.readButtons()==1){
      seconds++;      
      delay(200);
    }
    if (tm.readButtons()==0x02){
    seconds--;
    delay(200);
    }
    if (tm.readButtons()==0x80){
      seconds2= seconds3= seconds4 = seconds = initialTime;
      timeset=true;
      flag01=1;
      break;
    }
  }
 }

  ISR(TIMER1_COMPA_vect){
  OCR1A += 62500;
  if(flag01==1){
    seconds--; // Advance The COMPA Register
  // Handle The Timer Interrupt
  //...
  }
  if(flag02==1){
    seconds2--;
  }
  if(flag03==1){
    seconds3--; // Advance The COMPA Register
  // Handle The Timer Interrupt
  //...
  }
  if(flag04==1){
    seconds4--;
  }

}

void setup () {
  Serial.begin(9600);
  TCCR1A = 0;           // Init Timer1A
  TCCR1B = 0;           // Init Timer1B
  TCCR1B |= B00000100;  // Prescaler = 256
  OCR1A = 62500;        // Timer Compare1A Register
  TIMSK1 |= B00000010;  // Enable Timer COMPA Interrupt
  //Serial.println("Press S4 to set iterative time increment.");
  Serial.println();
  Serial.println("Press S8 to set time for multiple users.");//max time??
  Serial.println("Press S7 to set time for one user.");
  Serial.println("After proceding to the set time process, press S1 to increase time by 1sec or S2 to decrease time by 1sec. The time will be the same for all users.");
  Serial.println("Press S8 when finished");

  tm.displayBegin();
  tm.displayText("Begin");
  delay(2000);
}

void loop() {
  Serial.println(tm.readButtons());
  if (tm.readButtons()==0x40){
  flag01=0;flag02=0;flag03=0;flag04=0;
  SetTime(false); 
  if (tm.readButtons()==0x80){
  SetUsers(false);
  SetTime(false);
  }
  if(timeset==true) {
  while(flag02=flag03=flag04){//User1 display and interface with pause and resume buttons at S5 and S6
  tm.displayIntNum(seconds,true,TMAlignTextLeft);
  tm.setLED(0,1);
  }
  if(tm.readButtons()==0x02){//switch to user 2 if S2 is pressed
  flag01=0;flag02=1;flag03=0;flag04=0;
  }
  if(tm.readButtons()==0x04){//switch to user 3 if S3 is pressed
  flag01=0;flag02=0;flag03=1;flag04=0;
  }
  if(tm.readButtons()==0x08){//switch to user 4 if S4 is pressed
  flag01=0;flag02=0;flag03=0;flag04=1;
  }
  if(tm.readButtons()==0x16){ //pause the timer if S5 is pressed
    flag01=0;
  }
  if(tm.readButtons()==0x32){ //Resume the timer if S6 is pressed
    flag01=1;
  }
  if(seconds|seconds2|seconds3|seconds4==0){ 
     flag01=0;
    digitalWrite(Buzzer,HIGH);
    delay(3000);
    digitalWrite(Buzzer,LOW);
  } 
  } 
    while(flag01=flag03=flag04){//User2 display and interface with pause and resume buttons at S5 and S6
  tm.displayIntNum(seconds2,true,TMAlignTextLeft);
  tm.setLED(1,1);
  }
  if(tm.readButtons()==0x01){//switch to user 1 if S1 is pressed
  flag01=1;flag02=0;flag03=0;flag04=0;
  }
  if(tm.readButtons()==0x04){//switch to user 3 if S3 is pressed
  flag01=0;flag02=0;flag03=1;flag04=0;
  }
  if(tm.readButtons()==0x08){//switch to user 4 if S4 is pressed
  flag01=0;flag02=0;flag03=0;flag04=1;
  }
  if(tm.readButtons()==0x16){ //pause the timer if S5 is pressed
  flag01=0;
  }
  if(tm.readButtons()==0x32){ //Resume the timer if S6 is pressed
  flag01=1;
  }
  if(seconds|seconds2|seconds3|seconds4==0){ 
  flag01=0;
    digitalWrite(Buzzer,HIGH);
    delay(3000);
    digitalWrite(Buzzer,LOW);
  }
    while(flag01=flag02=flag04){//User2 display and interface with pause and resume buttons at S5 and S6
  tm.displayIntNum(seconds3,true,TMAlignTextLeft);
  tm.setLED(2,1);
  }
  if(tm.readButtons()==0x01){//switch to user 1 if S1 is pressed
  flag01=1;flag02=0;flag03=0;flag04=0;
  }
  if(tm.readButtons()==0x04){//switch to user 2 if S3 is pressed
  flag01=0;flag02=1;flag03=0;flag04=0;
  }
  if(tm.readButtons()==0x08){//switch to user 4 if S4 is pressed
  flag01=0;flag02=0;flag03=0;flag04=1;
  }
  if(tm.readButtons()==0x16){ //pause the timer if S5 is pressed
  flag01=0;
  }
  if(tm.readButtons()==0x32){ //Resume the timer if S6 is pressed
  flag01=1;
  }
  if(seconds|seconds2|seconds3|seconds4==0){ 
  flag01=0;
    digitalWrite(Buzzer,HIGH);
    delay(3000);
    digitalWrite(Buzzer,LOW);
  }
    while(flag01=flag03=flag04){//User2 display and interface with pause and resume buttons at S5 and S6
  tm.displayIntNum(seconds4,true,TMAlignTextLeft);
  tm.setLED(3,1);
  }
  if(tm.readButtons()==0x01){//switch to user 1 if S1 is pressed
  flag01=1;flag02=0;flag03=0;flag04=0;
  }
  if(tm.readButtons()==0x04){//switch to user 3 if S2 is pressed
  flag01=0;flag02=1;flag03=0;flag04=0;
  }
  if(tm.readButtons()==0x08){//switch to user 4 if S3 is pressed
  flag01=0;flag02=0;flag03=1;flag04=0;
  }
  if(tm.readButtons()==0x16){ //pause the timer if S5 is pressed
  flag01=0;
  }
  if(tm.readButtons()==0x32){ //Resume the timer if S6 is pressed
  flag01=1;
  }
  if(seconds|seconds2|seconds3|seconds4==0){ 
  flag01=0;
    digitalWrite(Buzzer,HIGH);
    delay(3000);
    digitalWrite(Buzzer,LOW);
  }
  }
}

