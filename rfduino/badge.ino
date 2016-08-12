/*****************************************/
/**Here is the program to configure your**/
/**********RFDuino as a badge.************/
/***It collects rssis of active markers***/
/***and average it. Then it sends those***/
/*averaged values to all the superMArkers*/
/*****************************************/

#define MAX_DEVICES 10 //including simple and super markers
#define MAX_COUNT 10 //sampling rate
#include <RFduinoGZLL.h>
#include <stdlib.h>

// RSSI total and count for each device for averaging
int rssi_total[MAX_DEVICES];
int rssi_count[MAX_DEVICES];

int rssis[MAX_DEVICES][MAX_COUNT];
int average[MAX_DEVICES];
char data_badge[9];
int first[MAX_DEVICES];
int cpt,i,j,indice=0,nb_devices=0;
int active_markers[MAX_DEVICES];

// collect samples flag
int get_rssi = 0;

void setup()
{
  // write the Device and RSSI values to the Serial Monitor
  Serial.begin(115200);
  // start the GZLL stack in HOST mode
  RFduinoGZLL.begin(HOST);  
  RFduinoGZLL.txPowerLevel=0;

  for (i = 0; i < MAX_DEVICES; i++)
  {
   rssi_count[i] = 0;
   first[i]=1;
   if(i<MAX_DEVICES)
    active_markers[i]=MAX_DEVICES+1; // impossible, permit to know if a device is active or not
  }
}

void loop()
{
  // reset the RSSI averaging for each device
  for (i = 0; i < MAX_DEVICES; i++)
  {
    rssi_total[i] = 0;
  }
  // start collecting RSSI samples
  get_rssi = 1;

  // during one second
  delay(1000);
  
  // stop collecting RSSI samples
  get_rssi = 0;
  
  for(i=0;i<MAX_DEVICES;i++){
    
  // calculate the RSSI averages for each device      
    for(cpt=0;cpt<MAX_COUNT;cpt++){
        rssi_total[i]=rssi_total[i]+rssis[i][cpt];
    }
    // no samples received, set to the lowest RSSI
    // (also prevents divide by zero)
    if (rssi_count[i] == 0)
      average[i] = -128;
    else
      average[i] = rssi_total[i] / MAX_COUNT;

    data_badge[i+1]=average[i]; //rssis come after the badge id   

    printf("%d ",active_markers[i]); //notice on the console which device is active
  }
  printf("\nnb devices : %d\n",nb_devices);
  for(i=0;i<MAX_DEVICES;i++){
    for(j=0;j<MAX_COUNT;j++){
      printf("%d ",rssis[i][j]);
    }
    printf("\n");
  }
  
  
}

void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len)
{
  char id = data[0]; //Collect the id of the device (marker)
    
  // if collecting samples, update the RSSIs for each marker
  if (get_rssi)
  {
    if(first[id]==1){
      rssis[id][0]=rssi;
      first[id]=0;
      nb_devices++;
      active_markers[indice]=id;
      indice++;
    }else{
      for(i=9;i>=0;i--)
        rssis[id][i]=rssis[id][i-1];
      rssis[id][0]=rssi;
    }
    rssi_count[id]++;
   }

  //id badge
  data_badge[0]='b'; //a,b,c, ...
    

 RFduinoGZLL.sendToDevice(DEVICE0,data_badge);
  

}
