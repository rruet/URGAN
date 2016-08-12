#include <RFduinoGZLL.h>

device_t role = DEVICE0; //must be DEVICE0 for a superMARKER

// pin for the Green Led
int green_led = 3;

// id from 0 to 128
int id = 1;

void setup()
{
 RFduinoGZLL.txPowerLevel = 0;
  pinMode(green_led,OUTPUT); 

  // start the GZLL stack
  RFduinoGZLL.begin(role);

  Serial.begin(115200);
}

void loop()
{
  delay(1000);

  // Transmission of the marker id to the host
  RFduinoGZLL.sendToHost(id);
  //Serial.println("requesting...\n");
}

void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len)
{
  // ignore acknowledgement without payload
  if (len > 0)
  {
   printf("%c;%d %d %d %d %d %d %d %d\n",data[0],data[1]-256,data[2]-256,data[3]-256,data[4]-256,data[5]-256,data[6]-256,data[7]-256,data[8]-256);
   digitalWrite(green_led,HIGH); //flashing the green led each time a message is received
   }
   delay(50);
   digitalWrite(green_led,LOW);
}
