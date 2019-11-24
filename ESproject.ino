#define REMOTEXY_MODE__ESP8266_HARDSERIAL_CLOUD
#include <RemoteXY.h>
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "manohar"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "69cd38e571ce4273eaf4f2b91df6a8c7"
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,1,0,3,0,40,0,8,31,1,
  2,1,14,52,39,16,6,26,31,31,
  70,69,69,68,73,78,71,0,70,69,
  69,68,0,66,68,8,12,13,17,6,
  24,65,14,38,14,13,13 };
struct {
  uint8_t FEED;
  int8_t pos; 
  uint8_t led_r; 
  uint8_t led_g; 
  uint8_t connect_flag; 
  } RemoteXY;
#pragma pack(pop)
#include <Servo.h>
Servo servo; 
int pos = 0; 
void setup() 
{
   RemoteXY_Init ();  
   RemoteXY_Handler ();
   RemoteXY.led_r=255;
   RemoteXY.led_g=0;
}

void loop() 
{ 
  RemoteXY_Handler ();    
  if(RemoteXY.FEED==1)
  {    
   if(pos<140){    
    servo.attach(9);
       for (pos = 20; pos <140; pos += 1) { 
            servo.write(pos);
             delay(10); 
             RemoteXY_Handler (); 
             RemoteXY.led_r=0;
             RemoteXY.led_g=255;
             RemoteXY.pos=pos-20; 
       }
       }
       else {
         servo.write(140); servo.detach();                               
  }
  }
  else{
  for ( ; pos >= 20; pos -= 1) {
    servo.attach(9);
    servo.write(pos);
    RemoteXY_Handler ();
    RemoteXY.led_r=255;
    RemoteXY.led_g=0;  
    RemoteXY.pos=pos-20; 
     delay(10); 
    }
   servo.detach();
}
}
