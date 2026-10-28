//Self adjusting solar panel to get maximum efficiency

#include<Servo.h>
Servo H , V;
int vang = 90, hang = 90;
int t,b,l,r;
int c = 20;

void setup()
{
  Serial.begin(9600);
  H.attach(9);
  V.attach(3);
  H.write(hang);
  V.write(vang);
}

void loop()
{
  l = analogRead(A0);
  t = analogRead(A1);
  b = analogRead(A2);
  r = analogRead(A3);
  
  int dh = l-r;
  int dv = t-b;
  
  if(abs(dv)>c){ 
    if(dv>0 && vang<170) vang+=1;
    else if(dv<0 && vang>10) vang-=1;
    V.write(vang);
  }
  
  if(abs(dh)>c){
    if(dh>0 && hang<170) hang+=1;
    else if(dh<0 && hang>10) hang-=1;
    H.write(hang);
  }
  
  delay(50);
}