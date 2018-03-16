#include <Encoder.h>

Encoder rightEnc(20, 21);
Encoder leftEnc(18, 19);

//const int LeftMtrEpinA = 22;
//const int LeftMtrEpinB = 23;
//
//const int RightMtrEpinA = 24;
//const int RightMtrEpinB = 25;

const int echoL = 47;
const int trigL = 46;

const int echoR = 53;
const int trigR = 52;

const int trigLft2 = 32 ;
const int echoLft2 = 30;

const int echoFrntL = 49;
const int trigFrntL = 48;

const int echoFrntR = 51;
const int trigFrntR = 50;

const int inA1 = 36;
const int inA2 = 38;
const int inB1 = 40;
const int inB2 = 42;
const int pwmA = 6;
const int pwmB = 7;

byte spd = 100;

int distanceLft;
int distanceRgt;
long distanceFrontLft;
long distanceFrontRgt;
long distanceFrontMid;
long distanceLft2;
 

//pwmA-->left motor
//pwmB-->right motor



void setup() {

  Serial.begin(9600);

  pinMode(inA1,OUTPUT);
  pinMode(inA2,OUTPUT);
  pinMode(inB1,OUTPUT);
  pinMode(inB2,OUTPUT);
  pinMode(pwmA,OUTPUT);
  pinMode(pwmB,OUTPUT);
//front = 10
//left = 15
//right =15
//
//reverce(200);
//delay(1000);
//stopp();
//left(spd);
//delay(530);
//stopp();
//right90c();
//turnAround();

//turnAround();
//left90c();
//right90c();
//goMaze();
//u();
goStraight2();
}

void loop() {


//Serial.print(leftEnc.read());
//Serial.print('\t');
//Serial.println(rightEnc.read());
readSensors();
//goStraight();
}


/////////Basic movements

void jumpFwd(){
 leftEnc.write(0);
 rightEnc.write(0);

  foward(spd);
  
  while(leftEnc.read() <=18000 && rightEnc.read() <=18000){
    if(leftEnc.read() >=18000 || rightEnc.read() >=18000){
            hardStop();
            return;
    }
    }
}

void hardStop(){
  reverse(spd);
  delay(20);
  stopp();  
}



void foward(int spd){

  digitalWrite(inA1,LOW);
  digitalWrite(inA2,HIGH);
  digitalWrite(inB1,LOW);
  digitalWrite(inB2,HIGH);
  analogWrite(pwmA,spd);
  analogWrite(pwmB,spd);
 
}

void fowardDis(int dis, int spd){
  leftEnc.write(0);
  rightEnc.write(0);
  foward(spd);
while((leftEnc.read() <= dis) && (rightEnc.read() <= dis)){
    if(leftEnc.read() >= dis)  digitalWrite(pwmA, 0);
    if(rightEnc.read() >= dis)  digitalWrite(pwmB, 0);
  }
  digitalWrite(pwmA, 0);
  digitalWrite(pwmB, 0);
  
}

void reverse(int spd){

  digitalWrite(inA2,LOW);
  digitalWrite(inA1,HIGH);
  digitalWrite(inB2,LOW);
  digitalWrite(inB1,HIGH);
  analogWrite(pwmA,spd);
  analogWrite(pwmB,spd);
 
}

void stopp(){
  digitalWrite(inA1,LOW);
  digitalWrite(inA2,LOW);
  digitalWrite(inB2,LOW);
  digitalWrite(inB1,LOW);
  analogWrite(pwmA,0);
  analogWrite(pwmB,0);
  
}

void right(int spd){
     
  digitalWrite(inA1,LOW);
  digitalWrite(inA2,HIGH);
  digitalWrite(inB2,LOW);
  digitalWrite(inB1,HIGH);
  analogWrite(pwmA,spd);
  analogWrite(pwmB,0);
  
}

void closeRight(int spd){
     
  digitalWrite(inA1,LOW);
  digitalWrite(inA2,HIGH);
  digitalWrite(inB2,LOW);
  digitalWrite(inB1,HIGH);
  analogWrite(pwmA,spd);
  analogWrite(pwmB,spd);
  
  readSensors();
}


void left(int spd){
      
  digitalWrite(inA2,LOW);
  digitalWrite(inA1,HIGH);
  digitalWrite(inB1,LOW);
  digitalWrite(inB2,HIGH);
  analogWrite(pwmA,0);
  analogWrite(pwmB,spd);
  
}


void closeLeft(int spd){
      
  digitalWrite(inA2,LOW);
  digitalWrite(inA1,HIGH);
  digitalWrite(inB1,LOW);
  digitalWrite(inB2,HIGH);
  analogWrite(pwmA,spd);
  analogWrite(pwmB,spd);
  
}

void left90c(){
  leftEnc.write(0);
 // right.write(0);

  closeLeft(spd);
    
  while((leftEnc.read() >= -8000)){
    if(leftEnc.read() <= -8000){
      closeRight(spd);
      delay(30);
      stopp();
      return;
    }
  }
}

void right90c(){
  leftEnc.write(0);
  rightEnc.write(0);

  closeRight(spd);
    
  while((leftEnc.read() <= 12000)){
    if(leftEnc.read() >= 12000){
      closeLeft(spd);
      delay(30);
      stopp();
      return;    
    }
  }
}

void turnAround(){
  leftEnc.write(0);
  rightEnc.write(0);
  
  reverse(spd);
  delay(100);
  closeRight(spd);
    
  while((leftEnc.read() <= 14000)){
    if(leftEnc.read() >= 14000){
      stopp();
      foward(spd);
      delay(300);
      stopp();
    }
  }
}



///////Advance movements
void goMaze(){
  
}


void goStraight2(){
  
for(;;){
readSensors();

  if(distanceFrontRgt> 6){
   
  if(distanceLft>=6 && distanceLft<=8 && distanceLft2>=6 && distanceLft<=8){
      foward(spd);
  }
  if(distanceLft<6 || distanceLft2>7){
      right(spd);
      delay(10);
  }
  if(distanceLft>7 || distanceLft2<6){
      left(spd);
      delay(10);
  }   
   
  }else{
      right90c(); 
    }
  }    
} 


void goStraight(){
  
for(;;){
readSensors();
int mid = (distanceLft+distanceRgt)/2;
int midL = mid-1;
int midT = mid+1; 
  if(distanceLft>30){
         fowardDis(5000,spd);
         left90c();
         fowardDis(5000,spd);
  }
  
  if(distanceLft>=midL && distanceLft<=midT && distanceRgt>=midL && distanceRgt<=midT){
      foward(spd);
  }else if(distanceLft>midT || distanceRgt<midL){
      foward(spd);
      left(spd);
  }else if(distanceRgt>midT || distanceLft<midL ){
      right(spd);  
  }       
  }    
} 


void u(){
  digitalWrite(inA1,LOW);
  digitalWrite(inA2,HIGH);
  digitalWrite(inB1,HIGH);
  digitalWrite(inB2,LOW);
  
  analogWrite(pwmA,170);
  analogWrite(pwmB,255);

  leftEnc.write(0);
  rightEnc.write(0);

    while((leftEnc.read() <= 15500)){
    if(leftEnc.read() >= 15500)  
    digitalWrite(pwmA, 0);
    }

  analogWrite(pwmA,255);
  analogWrite(pwmB,255);

   while((leftEnc.read() <= 15500)){
    if(leftEnc.read() >= 15500)  
    digitalWrite(pwmA, 0);
    }

    
  digitalWrite(pwmA, 0);
  digitalWrite(pwmB, 0);

}



void readSensors(){
  
  distanceLft = distanceLeft();
  distanceLft2 = distanceLeft2();
  distanceRgt = distanceRight();
  distanceFrontLft = distanceFrontLeft();
  distanceFrontRgt = distanceFrontRight();
  distanceFrontMid =0;


  Serial.print(distanceLft);
  Serial.print('\t'); 
  Serial.print(distanceLft2);
  Serial.print('\t'); 
  Serial.print(distanceRgt);
  Serial.print('\t');
  Serial.print(distanceFrontLft);
  Serial.print('\t');
  Serial.println(distanceFrontRgt);
} 


long distanceLeft(){
  long duration, cm;
    for(;;){
      pinMode(trigL, OUTPUT);
      digitalWrite(trigL, LOW);
      delayMicroseconds(2);
      digitalWrite(trigL, HIGH);
      delayMicroseconds(5);
      digitalWrite(trigL, LOW);
      pinMode(echoL, INPUT);
      duration = pulseIn(echoL, HIGH); 
      cm = duration / 29 / 2;
      delayMicroseconds(2);
        
        return cm;
  }
}


long distanceRight()
{
  long duration, cm;
    for(;;){
    pinMode(trigR, OUTPUT);
    digitalWrite(trigR, LOW);
    delayMicroseconds(2);
    digitalWrite(trigR, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigR, LOW);
  
    pinMode(echoR, INPUT);
    duration = pulseIn(echoR, HIGH);

  
    cm = duration / 29 / 2;
 
    delayMicroseconds(2);
    return cm;
}
}

long distanceFrontLeft()
{
  long duration, cm;
    for(;;){
    pinMode(trigFrntL, OUTPUT);
    digitalWrite(trigFrntL, LOW);
    delayMicroseconds(2);
    digitalWrite(trigFrntL, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigFrntL, LOW);
  
    pinMode(echoFrntL, INPUT);
    duration = pulseIn(echoFrntL, HIGH);

  
    cm = duration / 29 / 2;
 
    delayMicroseconds(2);
    return cm;
}
}

long distanceFrontRight()
{
  long duration, cm;
    for(;;){
    pinMode(trigFrntR, OUTPUT);
    digitalWrite(trigFrntR, LOW);
    delayMicroseconds(2);
    digitalWrite(trigFrntR, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigFrntR, LOW);
  
    pinMode(echoFrntR, INPUT);
    duration = pulseIn(echoFrntR, HIGH);

  
    cm = duration / 29 / 2;
 
    delayMicroseconds(2);
    return cm;
}
}

long distanceLeft2()
{
  long duration, cm;
    for(;;){
    pinMode(trigLft2, OUTPUT);
    digitalWrite(trigLft2, LOW);
    delayMicroseconds(2);
    digitalWrite(trigLft2, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigLft2, LOW);
  
    pinMode(echoLft2, INPUT);
    duration = pulseIn(echoLft2, HIGH);

  
    cm = duration / 29 / 2;
 
    delayMicroseconds(2);
    return cm;
}
}



