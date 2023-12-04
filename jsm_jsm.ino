#include <SoftwareSerial.h> //Create software serial object to communicate with SIM800L
SoftwareSerial GSM(2, 3);   //SIM800L Tx & Rx is connected to Arduino #2 & #3

char *phone_no = "03239815053"; //change +92 with country code and 3378655465 with phone number to sms

unsigned long currentTime;
unsigned long loopTime1;
unsigned long loopTime2;

#define enA 5 //Enable1 L298 Pin enA
#define in1 6 //Motor1  L298 Pin in1 
#define in2 7 //Motor1  L298 Pin in1 
#define in3 8 //Motor2  L298 Pin in1 
#define in4 9 //Motor2  L298 Pin in1 
#define enB 10//Enable2 L298 Pin enB 

int Speed = 110;  
int bt_data; // variable to receive data from the serial port
int s1;

#define e_s1 A0 //echo pin
#define t_s1 A1 //Trigger pin

void setup() {// put your setup code here, to run once

pinMode(enA, OUTPUT); // declare as output for L298 Pin enA 
pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 
pinMode(enB, OUTPUT); // declare as output for L298 Pin enB 

pinMode(e_s1,INPUT);  pinMode(t_s1,OUTPUT);

Serial.begin(9600);//Begin serial communication with Arduino and Arduino IDE (Serial Monitor)  
GSM.begin(9600);   //Begin serial communication with Arduino and SIM800L

Serial.println("Initializing....");
initModule("AT","OK",500);          //Scan for GSM Module
initModule("ATE0","OK",500);
initModule("AT+CPIN?","READY",500);
initModule("AT+CLIP=1","OK",500);  
initModule("AT+DDET=1","OK",500);
Serial.println("Initialized Successfully"); 
}

void loop(){

s1= ultra_read(t_s1,e_s1);

if(Serial.available() >0){  //if some date is sent, reads it and saves in state     
bt_data = Serial.read();      
if(bt_data>5){Speed = bt_data;}      
}

if(bt_data==1){ // if the bt_data is '1' the DC motor will fast
if(s1>40){forword();}
else{turnLeft();}
} 

else if(bt_data == 8){backword();}  // if the bt_data is '2' the motor will Reverse
else if(bt_data == 4){turnLeft();}  // if the bt_data is '3' the motor will turn left
else if(bt_data == 3){turnRight();}
 
else if(bt_data == 5){Stop(); }     // if the bt_data '5' the motor will Stop
else if(bt_data == 7){turnLeft();  delay(400);  bt_data = 5;}
else if(bt_data == 6){turnRight(); delay(400);  bt_data = 5;}
//===============================================================================
//                          Voice Control Command
//===============================================================================    


currentTime = millis(); 
if(currentTime >= (loopTime1 + 2000)){
initModule("AT","OK",300); 
loopTime1 = currentTime;   
}
  
if(GSM.find("CLIP:")) {
 Serial.println("RING!");
 delay(200);
    
while(1){     
if(GSM.find(phone_no)){ 
initModule("ATA","OK",300);      
delay(1500);
loopTime2 = currentTime; 
while (1){   
   currentTime = millis();  
if(currentTime >= (loopTime2 + 20000)){
  Serial.println("Call End");
  loopTime2 = currentTime;
  bt_data=5;
  Stop(); 
  break;
} 

s1= ultra_read(t_s1,e_s1);

if(bt_data==1){ // if the bt_data is '1' the DC motor increase the speed
if(s1>40){forword();}
else{turnLeft();}
}
 
else if(bt_data == 2){backword();}  // if the bt_data is '2' the motor will forward
else if(bt_data == 3){turnLeft();}  // if the bt_data is '3' the motor will slow
else if(bt_data == 4){turnRight();} // if the bt_data is '4' the motor will turn left
else if(bt_data == 5){Stop();}     // if the bt_data '5' the motor will Stop

motor_speed(); 

if(GSM.find("+DTMF:")){
  int Data = GSM.parseInt();
  switch(Data){                                

case 1: { 
if(Speed<240){Speed=Speed+10;}  
loopTime2 = currentTime;
   break;}

case 2: { 
bt_data = 1; 
loopTime2 = currentTime;   
   break;}

case 3: { 
if(Speed>40){Speed=Speed-10;}      
loopTime2 = currentTime;   
   break;}

case 4: {
bt_data = 4;   
loopTime2 = currentTime;   
   break;}

case 5: {
bt_data = 5; 
loopTime2 = currentTime;   
   break;}

case 6: {
bt_data = 3;   
loopTime2 = currentTime;   
   break;}

case 8: { 
bt_data = 2; 
loopTime2 = currentTime;  
   break;}

case 9: {  
loopTime2 = currentTime+20000;   
break;}

    } 
   }
  }   
 } 
else {
initModule("AT","OK",300); 
break;            
 } 
}
 initModule("AT+CHUP;","OK",300); 
 }

 motor_speed(); 
}

void motor_speed(){
analogWrite(enA, Speed); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
analogWrite(enB, Speed); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed  
}

void forword(){  //forword
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 
}

void backword(){ //backword
digitalWrite(in1, LOW);  //Right Motor forword Pin 
digitalWrite(in2, HIGH); //Right Motor backword Pin 
digitalWrite(in3, HIGH); //Left Motor backword Pin 
digitalWrite(in4, LOW);  //Left Motor forword Pin 
}

void turnRight(){ //turnRight
digitalWrite(in1, LOW);  //Right Motor forword Pin 
digitalWrite(in2, HIGH); //Right Motor backword Pin  
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 
}

void turnLeft(){ //turnLeft
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, HIGH); //Left Motor backword Pin 
digitalWrite(in4, LOW);  //Left Motor forword Pin 
}

void Stop(){ //stop
digitalWrite(in1, LOW); //Right Motor forword Pin 
digitalWrite(in2, LOW); //Right Motor backword Pin 
digitalWrite(in3, LOW); //Left Motor backword Pin 
digitalWrite(in4, LOW); //Left Motor forword Pin 
}

//*******ultra_read*********
int ultra_read(int pin_t,int pin_e){
digitalWrite(pin_t,LOW);
delayMicroseconds(2);
digitalWrite(pin_t,HIGH);
delayMicroseconds(10);
long time=pulseIn (pin_e,HIGH);
int ultra_time =  time / 29 / 2; 
delay(1);
return ultra_time;
}


 // Init GSM Module 
void initModule(String cmd, char *res, int t){
while(1){
    Serial.println(cmd);
    GSM.println(cmd);
    delay(100);
    while(GSM.available()>0){
       if(GSM.find(res)){
        Serial.println(res);
        delay(t);
        return;
       }else{Serial.println("Error");}}
    delay(t);
  }
}
