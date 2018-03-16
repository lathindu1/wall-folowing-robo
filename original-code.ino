
#include <QTRSensors.h>
#include <Encoder.h>
#include <Servo.h>

//--------------------------------------pololu----------------loop-----------------------------------------------------------------------------------------------------------------------------
#define NUM_SENSORS   8      // number of sensors used
#define TIMEOUT       2500    // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   A7    // emitter is controlled by digital pin 2
#define IR_TRIGGER_LIMIT 350  // infraRed panel trigger point

//-------------------------------------COLOUR----SENSORS---------------------------------------------------------------------------------------------------------------------------------------
#define S0_A     46
#define S1_A     44
#define S2_A     50
#define S3_A     48
#define OUT_A    52
#define LED_A    42

#define S0_B     47
#define S1_B     45
#define S2_B     51
#define S3_B     49
#define OUT_B    53
#define LED_B    43


//------------------------------------MOTOR-------DRIVE----------------------------------------------------------------------------------------------------------------------------------------
#define rgtA 4
#define rgtB 5
#define lftB 6
#define lftA 7

//------------------------------------variable---declayr---------------------------------------------------------------------------------------------------------------------------------------
int fq-A;
int fq-B;
int red-A;
int blue-A;
int green-A;
int red-B;
int blue-B;
int green-B;

//-------------------------------------INSTANCES-----------------------------------------------------------------------------------------------------------------------------------------------
Encoder left(18, 19);      //Encoder of Left Motor
Encoder right(21, 20);      //Encoder of Right Motor
QTRSensorsRC Irpanel((unsigned char[]) {A8,A9,A10,A11,A12,A13,A14,A15},  NUM_SENSORS, TIMEOUT, EMITTER_PIN); 
Servo spring_servo;




void setup() 
{

calibrateSensorPanel();
for(;;)
{

fwd(spd,num);
stoprun();
Arrow_Color_find(r1,r2,l1,l2,spd1,enval1,spd2,y,enval2);
/* r1=encoder value for go left
 *  r2=encoder value for go back left
 *  l1=encoder value for go right
 *  l2=encoder value for go back left
 *  spd1=speed for forward
 *  enval1=encoder value for go forward
 *  spd2=speed for right or left 
 *  enval2=encoder value for right or left 
 */
 for(;;)
 {
arrow_follow();
 }

  
}



}
//---------------------------------initialize-------------colour---------------sencers-------------------------------------------------------------------------------------------------------
public void init_colors()
{
//---------------------------------Senser---A----for--object--detect---------------------------------------------------------------------------------
  pinMode(S0_A, OUTPUT);
  pinMode(S1_A, OUTPUT);
  pinMode(S2_A, OUTPUT);
  pinMode(S3_A, OUTPUT);
  pinMode(OUT_A, INPUT);
//--------------------------------senser---B-----for--Arrow-Line---detect----------------------------------------------------------------------------
  pinMode(S0_B, OUTPUT);
  pinMode(S1_B, OUTPUT);
  pinMode(S2_B, OUTPUT);
  pinMode(S3_B, OUTPUT);
  pinMode(OUT_B, INPUT);
  
  digitalWrite(S0_A, LOW);  // frequency scale 100%
  digitalWrite(S1_A, HIGH);
  
  digitalWrite(S0_B, LOW);  // frequency scale 100%
  digitalWrite(S1_B, HIGH);
}
//-------------------------------------------Senser---A----colour-Fq------------Analizing------------------------------------------------------------------------------------------------------
char sensor_A(char color)
{
  if (color == 'r')
  {
    digitalWrite(S2_A, LOW);
    digitalWrite(S3_A, LOW);
  }
  else if (color == 'g')
  {
    digitalWrite(S2_A, HIGH);
    digitalWrite(S3_A, HIGH);
  }
  else if (color == 'b')
  {
    digitalWrite(S2_A, LOW);
    digitalWrite(S3_A, HIGH);
  }
}
//----------------------------------------------Senser---B------Colour----fq------Analizing---------------------------------------------------------------------------------------------------
char sensor-B(char color)
{
  if (color == 'r') 
  {
    digitalWrite(S2_B, LOW);
    digitalWrite(S3_B, LOW);
  }
  else if (color == 'g') 
  {digitalWrite(S2_B, HIGH);
  digitalWrite(S3_B, HIGH);
  }
  else if (color == 'b') 
  {
    digitalWrite(S2_B, LOW);
    digitalWrite(S3_B, HIGH);
  }
  
}
//----------------------------function-------for-----------------------check---color----frequency----of----object------------------------
int read_freq_A() {             
  fq-A = pulseIn(OUT_A, LOW);
  return fq-A;
}
//-----------------------------function-------for---------------------------check--color--frequency--of--arrow-line----------------------------
int read_freq_B() {             
  fq-B = pulseIn(OUT_B, LOW);
  return fq-B;
}
//-------------------------function------------for----------------------find--------color-----------of------------object----from--senser-A---------------
char object_color()
{
 
  select_sensor_A('r');
  red_A = read_freq_A();    //------------read RED-----value--of----fq----------------------
  
  select_sensor_A('g');
  green_A = read_freq_A(); //-------------read GREEN----value--of----fq---------------------
  
  select_sensor_A('b');
  blue_A = read_freq_A();  //-------------read BLUE-----value---of----fq--------------------
  
  if ( (red_A < green_A) && (red_A < blue_A)) 
  {
    return 'R'; //----------------return-------colour----red
  }
  else if ((blue_A < green_A) && (blue_A < red_A))
  {
    return 'B'; //----------------return-------colour----blue
  }
  else
  {
    return 'G'; //-----------------return-------colour----green
  }
  
  return 'U';    //  return nothing if exceed the threshold... *******
}
char Arrow_color()
{
 
  select_sensor_B('r');
  red_B = read_freq_B();    //------------read RED-----value--of----fq----------------------
  
  select_sensor_B('g');
  green_B = read_freq_B(); //-------------read GREEN----value--of----fq---------------------
  
  select_sensor_B('b');
  blue_B = read_freq_B();  //-------------read BLUE-----value---of----fq--------------------
  
  if ( (red_B < green_B) && (red_B< blue_B)) 
  {
    return 'R'; //----------------return-------colour----red
  }
  else if ((blue_B < green_B) && (blue_B < red_B))
  {
    return 'B'; //----------------return-------colour----blue
  }
  else
  {
    return 'G'; //-----------------return-------colour----green
  }
  
  return 'U';    //  return nothing if exceed the threshold... *******
}
//-----------------------------------------------function--for---find--arrow--color--from--object-color------
void Arrow_Color_find(int r1,int r2,int l1,int l2,byte spd1, int enval1,byte spd2,int y,int enval2)
{
  int count1=0;
  outer : for(;;)
  {
    inner1 : for(;;)
    {
    if(count1<=r1)
    {
      if(object_color()==Arrow_color())
      {
        fwd(spd1,enval1);
        break outer;
      }
       turn_right_2f(spd2,y,enval2);
      count1+=enval2;
    }
    else
    {
      count1=0;
      break inner1;
    }
    }
   inner2 :  for(;;)
    {
    if(count1<=r2)
    {
      if(object_color()==Arrow_color())
      {
        fwd(spd1,enval1);
        break outer;
      }
       turn_right_2b(spd2,y,enval2);
      count1+=enval2;
    }
    else
    {
      count1=0;
      break inner2;
    }
    }
    inner3 :  for(;;)
    {
    if(count1<=l1)
    {
      if(object_color()==Arrow_color())
      {
        fwd(spd1,enval1);
        break outer;
      }
       turn_left_2f(spd2,y,enval2);
      count1+=enval2;
    }
    else
    {
      count1=0;
      break inner3;
    }
    }
    inne4 :  for(;;)
    {
    if(count1<=l2)
    {
      if(object_color()==Arrow_color())
      {
        fwd(spd1,enval1);
        break outer;
      }
      turn_left_2b(spd2,y,enval2);
      count1+=enval2;
    }
    else
    {
      count1=0;
      break inner4;
    }
    }
  }

}


//-----------------------------function--------for--------------forward---------------robo-----------------
void fwd(byte spd,int num)
{
  left.write(0);
  right.write(0);
  double spd_left=spd;
  double spd_right=spd;

  analogWrite(rgtA, spd_right); //--editing----finish
  analogWrite(lftA, spd_left);
  analogWrite(rgtB, 0);
  analogWrite(lftB, 0);


//------------------encoder--values---for----stop-------------
  while(true)
  {
    if((left.read() >= num)&&(right.read()>=num))
    {
      analogWrite(rgtA, 0);
      analogWrite(lftA, 0);
      break; 
    }
 
  }

  
}
//-----------------------------function--------for--------------backwoard------------robo------------------
void backw(byte spd,int num)
{
  left.write(0);
  right.write(0);
  double spd_left=spd;
  double spd_right=spd;

  analogWrite(rgtA, 0); //--editing----finish
  analogWrite(lftA, 0);
  analogWrite(rgtB, spd_right);
  analogWrite(lftB, spd_left);


  //------------------encoder--values---for----stop-------------
  while(true)
  {
    if((left.read() >= num)&&(right.read()>=num))
    {
      analogWrite(rgtA, 0);
      analogWrite(lftA, 0);
      break; 
    }

  }
  
  
}
//-----------------------------function--------for-------------turn-right---with---forwarding---robo-------
void right_wf(byte spd,double x,double y,int num)
{
  //--------------------------------------------------------------------------important--------------------------------------
  //---------------------------------------------------in this function allways (speed of left > speed of right)
  // x  amount for increase speed by presentage (ex-:1.5)----
  // y  amount for discrease speed by presentage (ex-:0.5)----
  double spd_left=spd*x;
  double spd_right=spd*y;
  left.write(0);
  right.write(0);
  
  analogWrite(rgtA, spd_right); //--editing---
  analogWrite(lftA, spd_left);
  analogWrite(rgtB, 0);
  analogWrite(lftB, 0);

  //------------------encoder--values---for----stop-------------
  while(true)
  {
    if((left.read() >= num)&&(right.read()>=num))
    {
      analogWrite(rgtA, 0);
      analogWrite(lftA, 0);
      break; 
    }
  //  Serial.println(right.read());
  }


  

  
}
//----------------------------function---------for-------------turn-left----with---forwarding---robo-------
void left_wf(byte spd,double x,double y,int num)
{
   //--------------------------------------------------------------------------important--------------------------------------
  //---------------------------------------------------in this function allways (speed of right > speed of left)
  // x amount for descrease speed by presentage(ex-:0.5)----
  // y amount for increase speed by presentage(ex-:1.5)----
  double spd_left=spd*x;
  double spd_right=spd*y;
  left.write(0);
  right.write(0);
  
  analogWrite(rgtA, spd_right); //--editing---
  analogWrite(lftA, spd_left);
  analogWrite(rgtB, 0);
  analogWrite(lftB, 0);

  //------------------encoder--values---for----stop-------------

    while(true)
  {
    if((left.read() >= num)&&(right.read()>=num))
    {
      analogWrite(rgtA, 0);
      analogWrite(lftA, 0);
      break; 
    }
   // Serial.println(right.read());
  }
  


  
}
//--------------------------function------for-----------turn right---->45 deggrees--------on---stop
void turn_right(byte spd,double x,double y,int num)
{
  // x amount of descreese speeed (ex-:0.7)-----
  // y amount of descreese speed (ex-:0.7)------
  double spd_left=spd*x;
  double spd_right=spd*y; 
  left.write(0);
  right.write(0);
  
  analogWrite(rgtA, 0);
  analogWrite(lftA, spd_left);
  analogWrite(rgtB, spd_right);
  analogWrite(lftB, 0);


  //------------------encoder--values---for----stop-------------

    while(true)
  {
    if((left.read() >= num)&&(right.read()>=num))
    {
      analogWrite(rgtA, 0);
      analogWrite(lftA, 0);
      break; 
    }
  //  Serial.println(right.read());
  }
  


  
}
//-------------------------function--------for------------turn left----->45 deggrees------on---stop
void turn_left(byte spd,double x,double y,int num)
{
   //x amount of descreese speeed (ex-:0.7)-----
  // y amount of descreese speed (ex-:0.7)------
  double spd_left=spd*x;
  double spd_right=spd*y; 
  left.write(0);
  right.write(0);
  
  analogWrite(rgtA, spd_right);
  analogWrite(lftA, 0);
  analogWrite(rgtB, 0);
  analogWrite(lftB, spd_left);


    //------------------encoder--values---for----stop-------------

    while(true)
  {
    if((left.read() >= num)&&(right.read()>=num))
    {
      analogWrite(rgtA, 0);
      analogWrite(lftA, 0);
      break; 
    }
  //  Serial.println(right.read());
  }
  


  
}


void turn_right_2f(byte spd,double x,int num)
{
  // x  amount for increase speed by presentage (ex-:1.5)----
  double spd_left=spd*x;
  left.write(0);
  
  analogWrite(rgtA, 0);
  analogWrite(lftA, spd_left);
  analogWrite(rgtB, 0);
  analogWrite(lftB, 0);

  //------------------encoder--values---for----stop-------------
  while(true)
  {
    if((left.read() >= num))
    {
      analogWrite(lftA, 0);
      break; 
    }

  }
}
void turn_right_2b(byte spd,double x,int num)
{
  // x  amount for increase speed by presentage (ex-:1.5)----
  double spd_left=spd*x;
  left.write(0);
  
  analogWrite(rgtA, 0);
  analogWrite(lftA, 0);
  analogWrite(rgtB, 0);
  analogWrite(lftB, spd_left);

  //------------------encoder--values---for----stop-------------
  while(true)
  {
    if((left.read() >= num))
    {
      analogWrite(lftB, 0);
      break; 
    }

  }
}

void turn_left_2f(byte spd,double y,int num)
{
  // y  amount for increase speed by presentage (ex-:1.5)----
  double spd_right=spd*y;
  right.write(0);
  
  analogWrite(rgtA, spd_right);
  analogWrite(lftA, 0);
  analogWrite(rgtB, 0);
  analogWrite(lftB, 0);

  //------------------encoder--values---for----stop-------------
  while(true)
  {
    if((right.read() >= num))
    {
      analogWrite(rgtA, 0);
      break; 
    }

  }
}
void turn_left_2b(byte spd,double y,int num)
{
  // y  amount for increase speed by presentage (ex-:1.5)----
  double spd_right=spd*y;
  right.write(0);
  
  analogWrite(rgtA, 0);
  analogWrite(lftA, 0);
  analogWrite(rgtB, spd_right);
  analogWrite(lftB, 0);

  //------------------encoder--values---for----stop-------------
  while(true)
  {
    if((right.read() >= num))
    {
      analogWrite(rgtB, 0);
      break; 
    }

  }
}

//-----------------------------function--------for---------------stop--------------robo-------------------
void Stoprun()
{
  left.write(0);
  right.write(0);
  
  analogWrite(rgtA, 0);
  analogWrite(lftA, 0);
  analogWrite(rgtB, 0);
  analogWrite(lftB, 0);
}
//----------------------------------function-------for---------sensor-------panel
byte Irpanel(){                                
  byte x=0;
  position=Irpanel.readLine(sensorValues);
  for(int i=0;i<8;i++){
    if(sensorValues[i]>IR_TRIGGER_LIMIT)
    {
      bitWrite(x, i, 1);
      //Serial.print("1");
      }
      else
      {
      //Serial.print("0");
      }
  }
 // Serial.println();
  return x;
}

char onesInByte(byte val){                      
  byte bits=0;
  for(int i=0;i<8;i++){
    if(bitRead(val, i)==1)
    bits++;
  }
  return bits;
}
//----------------------------------------------function-----for-------------------calibrate-----------------------------------------------------
void calibrateSensorPanel()
{                    //Required Part for calibrate senser panel
  pinMode(13,HIGH);
  digitalWrite(13,HIGH);

  for (int i = 0; i < 400; i++)
  {                                  
    Irpanel.calibrate();        //about 10 seconds
  }

  digitalWrite(13,LOW);
}
//------------------------------function--for---Arrow---followin--------------------
void arrow_follow()
{
  byte value=Irpanel();      //-------------under----edditing---------------------
  switch(value){

    case B00111100:
           fwd(spd,envalue);
           break;
    case B00111000:
           right_wf(spd,x,y,envalue);
           break;
    case B01111000:
           right_wf(spd,x,y,envalue);
           break;
    case B01110000:
            right_wf(spd,x,y,envalue);
            break;
    case B11110000:
            right_wf(spd,x,y,envalue);
            break;
    case B11100000:
            right_wf(spd,x,y,envalue);
            break;
    case B11000000:
            right_wf(spd,x,y,envalue);
            break;
    case B10000000:
            right_wf(spd,x,y,envalue);
            break;
    case B00011100:
            left_wf(spd,x,y,envalue);
            break;
    case B00011110:
            left_wf(spd,x,y,envalue);
            break;
    case B00001110:
            left_wf(spd,x,y,envalue);
            break;
    case B00001111:
            left_wf(spd,x,y,envalue);
            break;
    case B00000111:
            left_wf(spd,x,y,envalue);
            break;
    case B00000011:
            left_wf(spd,x,y,envalue);
            break;
    case B00000001:
            left_wf(spd,x,y,envalue);
            break;
    case B01111110:
           fwd(spd,envalue);
           break;
    case B01111100:
           fwd(spd,envalue);
           break;
    case B11111100:
           fwd(spd,envalue);
           break;
    case B11111000:
           fwd(spd,envalue);
           break;
    case B00111110:
           fwd(spd,envalue);
           break;
    case B00111111:
           right_wf(spd,x,y,envalue);
           break;
           fwd(spd,envalue);
           break;
    case B00011111:
           right_wf(spd,x,y,envalue);
           break;
           fwd(spd,envalue);
           break;
    case B00000000:
            fwd(spd,envalue);
            //check
             break;
  }
}


void loop() {
  // put your main code here, to run repeatedly:

}


