/* 
 * Base connectivity code by Adafruit;
 * extended by S. Thorn. & C. Rawls
 * Synthesis, AME, ASU December 2019
 */


/*
 * TO CHANGE WIFI CONNECTIVITY SETTINGS,
 * MODIFY Connection_Variables.h with your settings
 * DO NOT MODIFY THIS FILE, ALL CHANGES SHOULD BE MADE
 * IN ACCOMPANYING HEADER FILE
 */


//-----LIBRARIES-----


#include <SPI.h>
#include <Adafruit_WINC1500.h>
#include <Adafruit_WINC1500Udp.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_MQTT.h>
#include <utility/imumaths.h>
#include "Connection_Variables.h" //Modify contents of file to change connection settings



//-----CONSTANTS-----

//WINC1500 Pins
const int WINC_EN  = 2;
const int WINC_RST = 4;
const int WINC_IRQ = 7;
const int WINC_CS  = 8;

const int BATTERY  = 7;

const int NUMBER_OF_INCOMING_VALUES = 8; //How many elements in the list you're sending from Max?

//-----VARIABLES-----

int status = WL_IDLE_STATUS;                          // the wifi status
char packetIn[128];                                   // incoming udp packets
int receivedValues[NUMBER_OF_INCOMING_VALUES] = {0};  // array for storing incoming integers



/* Set the delay between fresh samples */

uint16_t BNO055_SAMPLERATE_DELAY_MS = 1000 / ((SENSOR_SAMPLE_RATE <= 0) ? 1 : ((SENSOR_SAMPLE_RATE > 100) ? 100 : SENSOR_SAMPLE_RATE));

//-----CONSTRUCTORS-----

Adafruit_WINC1500 WiFi(WINC_CS, WINC_IRQ, WINC_RST);
Adafruit_WINC1500UDP Udp;
Adafruit_BNO055 bno = Adafruit_BNO055(42, 0x28);


void setup() {

  Serial.begin(115200);
  pinMode(WINC_EN, OUTPUT);
  digitalWrite(WINC_EN, HIGH);

  if (!bno.begin()) {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
  }


  Serial.println(DST_PORT);
  
  status = WiFi.begin(WIFI_SSID, WIFI_PWD); //connect to network

  uint8_t timeout = 10; //wait for connection (10 secs):
  while (timeout && (WiFi.status() != WL_CONNECTED)) {
    timeout--;
    delay(1000);
  }


  Udp.begin(RETURN_PORT); //listen to port
  delay(1000); //let things settle

}

void loop() {

  Serial.println(DST_PORT);
  Serial.println(myhostIP);
  Serial.println(WIFI_SSID);
  Serial.println(WIFI_PWD);

  //declare sensor data containers
  sensors_event_t orientData , velData , accelData;

  //get sensor data
  bno.getEvent(&orientData, Adafruit_BNO055::VECTOR_EULER);
  bno.getEvent(&velData, Adafruit_BNO055::VECTOR_GYROSCOPE);
  bno.getEvent(&accelData, Adafruit_BNO055::VECTOR_ACCELEROMETER);

  //break data out into floats
  float ox = -10000, oy = -10000, oz = -10000, gx = -10000, gy = -10000, gz = -10000, ax = -10000, ay = -10000, az = -10000;

  ox = (float)orientData.orientation.x;
  oy = (float)orientData.orientation.y;
  oz = (float)orientData.orientation.z;

  gx = (float)velData.gyro.x;
  gy = (float)velData.gyro.y;
  gz = (float)velData.gyro.z;  

  ax = (float)accelData.acceleration.x;
  ay = (float)accelData.acceleration.y;
  az = (float)accelData.acceleration.z;
  
  
  uint8_t data[60] = {0};

  uint8_t* temp = data;

  char* taddr = "/sensor1";

  memcpy(temp, taddr, 8);
  temp += 12;
  *temp = ',';
  temp++;
  *temp = 'f';
  temp++;
  *temp = 'f';
  temp++;
  *temp = 'f';
  temp++;
  *temp = 'f';
  temp++;
  *temp = 'f';
  temp++;
  *temp = 'f';
  temp++;
  *temp = 'f';
  temp++;
  *temp = 'f';
  temp++;
  *temp = 'f';
  temp += 3;
/*
  char* content = "hello";
  int oxint = (int)(ox * 100);
  int* data = &oxint;
  *temp = (oxint >> 24) & 0xFF;
  temp++;
  *temp = (oxint >> 16) & 0xFF;
  temp++;
  *temp = (oxint >> 8) & 0xFF;
  temp++;
  *temp = oxint & 0xFF;
*/
  char fdata[4];

  memcpy(&fdata, &ox, 4);
  *temp = fdata[3];
  temp++;
  *temp = fdata[2];
  temp++;
  *temp = fdata[1];
  temp++;
  *temp = fdata[0];
  temp++;

  memcpy(&fdata, &oy, 4);
  *temp = fdata[3];
  temp++;
  *temp = fdata[2];
  temp++;
  *temp = fdata[1];
  temp++;
  *temp = fdata[0];
  temp++;

  memcpy(&fdata, &oz, 4);
  *temp = fdata[3];
  temp++;
  *temp = fdata[2];
  temp++;
  *temp = fdata[1];
  temp++;
  *temp = fdata[0];
  temp++;

  memcpy(&fdata, &gx, 4);
  *temp = fdata[3];
  temp++;
  *temp = fdata[2];
  temp++;
  *temp = fdata[1];
  temp++;
  *temp = fdata[0];
  temp++;

  memcpy(&fdata, &gy, 4);
  *temp = fdata[3];
  temp++;
  *temp = fdata[2];
  temp++;
  *temp = fdata[1];
  temp++;
  *temp = fdata[0];
  temp++;

  memcpy(&fdata, &gz, 4);
  *temp = fdata[3];
  temp++;
  *temp = fdata[2];
  temp++;
  *temp = fdata[1];
  temp++;
  *temp = fdata[0];
  temp++;

  memcpy(&fdata, &ax, 4);
  *temp = fdata[3];
  temp++;
  *temp = fdata[2];
  temp++;
  *temp = fdata[1];
  temp++;
  *temp = fdata[0];
  temp++;

  memcpy(&fdata, &ay, 4);
  *temp = fdata[3];
  temp++;
  *temp = fdata[2];
  temp++;
  *temp = fdata[1];
  temp++;
  *temp = fdata[0];
  temp++;

  memcpy(&fdata, &az, 4);
  *temp = fdata[3];
  temp++;
  *temp = fdata[2];
  temp++;
  *temp = fdata[1];
  temp++;
  *temp = fdata[0];
  temp++;
 
  
  Udp.beginPacket(hostIP, DST_PORT);
  Udp.write(data, 60);
  Udp.endPacket();
  Udp.flush();
  
  delay(BNO055_SAMPLERATE_DELAY_MS);

/*

//------send sensor data------
char packetOut[128] = {0}; //init to NULL

 
  Udp.beginPacket(hostIP, HOST_PORT);
  Udp.write(packetOut, 128);
  Udp.endPacket();
  Udp.flush();

  delay(5);

//------read incoming packets------
  int packetSize = Udp.parsePacket();
  char *string;
  
  if (packetSize) {
  
    int len = Udp.read(packetIn, 128); // read packet
    if (len > 0) packetIn[len] = 0;
    string = packetIn;  // pointer on the packet

    for(int i=0;i<NUMBER_OF_INCOMING_VALUES;i++) {
    receivedValues[i] = atoi ( strsep(&string," ") ); //read off all values
    }
  }

  */

  
}

void printEvent(imu::Vector<3> vec, String type) {
  Serial.println();
  Serial.print(type);
  double x = -1000000, y = -1000000 , z = -1000000; //dumb values, easy to spot problem

  if(type == "Orientation") {
    vec.toDegrees();
  }
  
  x = vec.x();
  y = vec.y();
  z = vec.z();

  Serial.print(": x= ");
  Serial.print(x);
  Serial.print(" | y= ");
  Serial.print(y);
  Serial.print(" | z= ");
  Serial.println(z);
}

