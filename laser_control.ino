// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h>
#include <CheapStepper.h>
#include <Servo.h>
Servo myservo;
CheapStepper Main (9,10,11,12);
int pos = 10;


// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "RemoteXY"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 61 bytes
  { 255,4,0,0,0,54,0,16,8,1,1,1,23,33,12,12,2,31,85,112,
  0,1,1,20,66,19,12,2,31,68,111,119,110,0,1,1,3,50,16,12,
  2,31,76,101,102,116,0,1,1,39,49,18,12,2,31,82,105,103,104,116,
  0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t up_btn; // =1 if button pressed, else =0 
  uint8_t down_btn; // =1 if button pressed, else =0 
  uint8_t left_btn; // =1 if button pressed, else =0 
  uint8_t right_btn; // =1 if button pressed, else =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)


void setup() {
  // put your setup code here, to run once:
  RemoteXY_Init ();
Main.setRpm(3);
myservo.attach(3);  
myservo.write(10);
}


void loop() {
  RemoteXY_Handler ();
   if (RemoteXY.up_btn)
      up();
   else if (RemoteXY.left_btn)   
      lift();
   else if(RemoteXY.right_btn)
      right();
   else if(RemoteXY.down_btn)   
      down();
}


void right()
{
 Main.moveDegreesCCW(30);
}
void lift()
{
 Main.moveDegreesCW(30);
}
void down(){
  int p = 3;
  while(p != 0){
    pos--;
    p--;
    myservo.write(pos);
    delay(35);
  }
}
void up(){
  int p = 0;
  while(p != 3){
    pos++;
    p++;
    myservo.write(pos);
    delay(35);
  }
}
