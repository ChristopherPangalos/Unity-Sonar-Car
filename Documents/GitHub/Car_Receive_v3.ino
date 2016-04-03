#include<Servo.h>

int msg[15];//data array received from serial
int accel;
int turn;
int panposition=90;//center servo at start
int tiltposition=90;//center servo
int panpin=7;
int tiltpin=6;
int pingpin=8;
int DStraight=2;//IA2 Yellow  BIA
int SStraight = 5; //IB2 Gray BIB
int STurn = 9;  //IA1 Brown
int DTurn = 4; //IB1 Purple



Servo pan;
Servo tilt;

void setup(){
 Serial.begin(9600);
 pan.attach(panpin);
 tilt.attach(tiltpin);
 pinMode(pingpin,OUTPUT);
 pinMode(DStraight, OUTPUT);
 pinMode(SStraight, OUTPUT);
 pinMode(DTurn, OUTPUT);
 pinMode(STurn, OUTPUT);
 digitalWrite(DStraight,LOW);
 digitalWrite(SStraight,LOW);
 digitalWrite(DTurn,LOW);
 digitalWrite(STurn,LOW);
 

}

void loop(){
 if (Serial.available()){
  delay(1);
     for(int x=0; x<7; x++)//read serial characters
     {if(Serial.available())
      msg[x]=Serial.read();//
     // Serial.println(msg[x]);
     if (msg[x]==' ')
     x=7;}
     //Serial.print(msg[0]);
     //Serial.print('1');
     pan.write(panposition);
     tilt.write(tiltposition);




     if(msg[2]=='r')
     {//Serial.println("Turn Right ");
     turn=msg[3];
     //Serial.println(turn);
  //   digitalWrite(STurn,LOW);
    // digitalWrite(DTurn,LOW);
  digitalWrite(DTurn,LOW); 
     analogWrite(STurn,255);
     //delay( 100 );
     }
     else if (msg[2]=='l')
     {//Serial.println("Turn Left ");
     turn=msg[3];
     //Serial.println(turn);
     //digitalWrite(STurn,LOW);
     //digitalWrite(DTurn,LOW);
    
     digitalWrite(DTurn,HIGH); 
     analogWrite(STurn,1);
     //delay( 100 );
     }
     else
     {//Serial.println("No Turn");
     turn=0;
     digitalWrite(DTurn,LOW);
     digitalWrite(STurn,LOW);
     }








     
     if(msg[0]=='1')
     {//Serial.println("Accel Forward ");
     //accel=msg[1];
     digitalWrite(DStraight,LOW);
     digitalWrite(SStraight,LOW);
     
     accel=255;
     //Serial.print("works");
     //Serial.println(accel);
     digitalWrite(DStraight,LOW);
     analogWrite(SStraight,accel);     
     delay( 100 );
     
     //analogWrite(SStraight,accel);
     //analogWrite(forward, accel);    //set both motors to run at (100/255 = 39)% duty cycle
     }
     else if (msg[0]=='2')
     {//Serial.println("Accel Reverse ");    
     accel=msg[1];
     accel=254;
     //Serial.println(accel);
       digitalWrite(DStraight,LOW);
     digitalWrite(SStraight,LOW);
     // delay( 100 );
     //Serial.println(accel);

     digitalWrite(DStraight,HIGH); 
     analogWrite(SStraight,255-accel);
     delay( 100 );
     //analogWrite(SStraight,accel);
     }
     else
     {//Serial.println("Accel Neutral ");
     accel=0;       
     digitalWrite(SStraight,LOW);
     digitalWrite(DStraight,LOW);
     
     }
 
;

// if(msg[6]>150) {
  if(msg[4]=='x')
    {if(panposition<180)
    panposition=panposition+2;
    }
  else if(msg[4]=='w')
    {if(panposition>0)
      panposition=panposition-2;
    }
    
  if(msg[5]=='z')
  {if(tiltposition<180)
    tiltposition=tiltposition+2;
  }
  else if(msg[5]=='y')
    {if(tiltposition>0)
      tiltposition=tiltposition-2;
    }
    
  
  //}
if(msg[0]=='s'){
  Serial.println(getdistance());
}

if(msg[0]=='p'){
Serial.println(panposition);
}

if(msg[0]=='t'){
Serial.println(tiltposition);
}

 
 }
 
 else{//serial not available stop vehicle
// Serial.println(getdistance());
if (Serial.available()==0){
 digitalWrite(SStraight,LOW);
 digitalWrite(DStraight,LOW);
 digitalWrite(STurn,LOW);
digitalWrite(DTurn,LOW);
 }}}



long getdistance(){

 pinMode(pingpin, OUTPUT);
  digitalWrite(pingpin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingpin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingpin, LOW);//preperation pulses
  
pinMode(pingpin,INPUT);
long dist;
dist=pulseIn(pingpin,HIGH);
return (dist/74/2);//conv to inches
}


