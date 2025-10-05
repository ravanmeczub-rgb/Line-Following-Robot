#define  ir1 A5
#define  ir2 A4 
#define  ir3 A3
#define  ir4 A2
#define  ir5 A1
////
#define ena 3
#define in1a 2
#define in2a 4
#define enb 5
#define in1b 7 
#define in2b 8
///
#define rightspeed 75 //100
#define leftspeed 90 //120

int ir1_s,ir2_s,ir3_s,ir4_s,ir5_s;
int prev_ir1, prev_ir2, prev_ir3, prev_ir4, prev_ir5;
int rightFlag=0 ,leftFlag=0;

void stop(){
  analogWrite(ena,0);
  digitalWrite(in1a,0);
  digitalWrite(in2a,0);
  analogWrite(enb,0);
  digitalWrite(in1b,0);
  digitalWrite(in2b,0);
}
void straight(int speedR, int speedL){
  leftFlag=0;
  rightFlag=0;
  analogWrite(ena,speedR);
  digitalWrite(in1a,1);
  digitalWrite(in2a,0);
  analogWrite(enb,speedL);
  digitalWrite(in1b,1);
  digitalWrite(in2b,0);
}
void back(){
  analogWrite(ena,90);
  digitalWrite(in1a,0);
  digitalWrite(in2a,1);
  analogWrite(enb,110);
  digitalWrite(in1b,0);
  digitalWrite(in2b,1);
}
void turn_right(int speed){
  analogWrite(ena,speed);
  digitalWrite(in1a,1);
  digitalWrite(in2a,0);
  digitalWrite(enb,0);
  digitalWrite(in1b,0);
  digitalWrite(in2b,0);
}
void turn_left(int speed){
  digitalWrite(ena,0);
  digitalWrite(in1a,0);
  digitalWrite(in2a,0);
  analogWrite(enb,speed);
  digitalWrite(in1b,1);
  digitalWrite(in2b,0);
}

void setup() {
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  pinMode(ir3,INPUT);
  pinMode(ir4,INPUT);
  pinMode(ir5,INPUT);
  pinMode(ena,OUTPUT);
  pinMode(in1a,OUTPUT);
  pinMode(in2a,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(in1b,OUTPUT);
  pinMode(in2b,OUTPUT);
}
void loop() {
  ir1_s=digitalRead(ir1);
  ir2_s=digitalRead(ir2);
  ir3_s=digitalRead(ir3);
  ir4_s=digitalRead(ir4);
  ir5_s=digitalRead(ir5);

  if(ir1_s && ir2_s  && !ir3_s && ir4_s&& ir5_s 
  || ir1_s && !ir2_s  && !ir3_s && !ir4_s&& ir5_s 
  || !ir1_s && ir2_s  && ir3_s && ir4_s&& !ir5_s 
  || ir1_s && !ir2_s  && ir3_s && !ir4_s&& ir5_s 
  || !ir1_s && !ir2_s  && ir3_s && !ir4_s&& !ir5_s 
  || !ir1_s && ir2_s  && !ir3_s && ir4_s&& !ir5_s  //ortadaki beyaz + orta üçlü + ucu ignorla
){
    straight(rightspeed,leftspeed);
  }

  if(ir1_s && ir2_s  && ir3_s && ir4_s&& !ir5_s ||
   ir1_s && ir2_s  && ir3_s && !ir4_s&& ir5_s || 
   ir1_s && ir2_s  && ir3_s && !ir4_s&& !ir5_s || 
   ir1_s && ir2_s  && !ir3_s && ir4_s&& !ir5_s|| 
   ir1_s && ir2_s  && !ir3_s && !ir4_s&& ir5_s|| 
   ir1_s && ir2_s  && !ir3_s && !ir4_s&& !ir5_s|| 

   ir1_s && !ir2_s  && ir3_s && !ir4_s&& !ir5_s|| 
   ir1_s && !ir2_s  && !ir3_s && !ir4_s&& !ir5_s|| 
   !ir1_s && ir2_s  && ir3_s && !ir4_s&& ir5_s|| 
   !ir1_s && ir2_s  && ir3_s && !ir4_s&& !ir5_s|| 
   !ir1_s && ir2_s  && !ir3_s && !ir4_s&& ir5_s|| 
   !ir1_s && ir2_s  && !ir3_s && !ir4_s&& !ir5_s){ // sağ taraf
    rightFlag=1;
    leftFlag=0;
  }

if(!ir1_s && ir2_s && !ir3_s && ir4_s&& ir5_s 
  || ir1_s && !ir2_s && !ir3_s && ir4_s&& ir5_s
  || ir1_s && !ir2_s && ir3_s && ir4_s&& ir5_s
  ||!ir1_s && ir2_s && ir3_s && ir4_s&& ir5_s
  ||!ir1_s && !ir2_s && ir3_s && ir4_s&& ir5_s 
  ||!ir1_s && !ir2_s && !ir3_s && ir4_s&& ir5_s
//
  ||!ir1_s && !ir2_s && !ir3_s && ir4_s&& !ir5_s
  ||!ir1_s && !ir2_s && !ir3_s && !ir4_s&& ir5_s
  ||!ir1_s && !ir2_s && ir3_s && ir4_s&& !ir5_s
  ||!ir1_s && !ir2_s && ir3_s && !ir4_s&& ir5_s
  ||ir1_s && !ir2_s && !ir3_s && ir4_s&& !ir5_s
  ||ir1_s && !ir2_s && ir3_s && ir4_s&& !ir5_s){ //sol taraf
    leftFlag=1;
    rightFlag=0; 
    }

  if(ir1_s && ir2_s && ir3_s && ir4_s && ir5_s) { // hepsi beyaz: köşeyi geçti: hatırla || boşluk: ilerle
    if(rightFlag && !leftFlag) {
      turn_right(rightspeed); 
    }
    else if(leftFlag && !rightFlag) {
      turn_left(leftspeed); 
    
    }
    else{
     straight(rightspeed,leftspeed);
    }
  }
  
  if(!ir1_s && !ir2_s && !ir3_s && !ir4_s && !ir5_s){
    straight(rightspeed,leftspeed);
  }
}