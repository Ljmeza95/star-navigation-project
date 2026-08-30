#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_LIS2MDL.h>
#include <math.h>

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(00001);
Adafruit_LIS2MDL mag = Adafruit_LIS2MDL(00002);

const float g = 9.81;
const float pi = 3.14159;

//Serial monitor commands to display cartesian values of acceleration 
void cartesianAccDisplay(float xA,float yA, float zA){

  Serial.print(" x: ");
  Serial.print(xA);
  Serial.print(" y: ");
  Serial.print(yA);
  Serial.print(" z: ");
  Serial.print(zA);

}

//Serial monitor commands to display cartesian values of magnetic field 
void cartesianMagDisplay(float xM, float yM, float zM){

  Serial.print(" x: ");
  Serial.print(xM);
  Serial.print(" y: ");
  Serial.print(yM);
  Serial.print(" z: ");
  Serial.print(zM);

}
//Serial monitor commands to display azimuth value of device from accelerometer
void azDisplay(float az){

  Serial.print("    azimuth: ");
  Serial.print(az);
  Serial.print(" Degrees");   

}

//Serial monitor commands to display altitude value of device from accelerometer
void altDisplay(float alt){

  Serial.print("    altitude: ");
  Serial.print(alt);
  Serial.print(" Degrees");   
  
}

void setup(void) {

  #ifndef ESP8266
  while (!Serial)
    ; // will pause Zero, Leonardo, etc until serial console opens
  #endif



  /* Initialise the acc sensor */
  if (!accel.begin()) {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("no LSM303 detected ... Check your wiring!");
    while (1)
      ;
  }

  /* Initialise the mag sensor */
  if (!mag.begin()) {  // I2C mode
  //if (! lis2mdl.begin_SPI(LIS2MDL_CS)) {  // hardware SPI mode
  //if (! lis2mdl.begin_SPI(LIS2MDL_CS, LIS2MDL_CLK, LIS2MDL_MISO, LIS2MDL_MOSI)) { // soft SPI
    /* There was a problem detecting the LIS2MDL ... check your connections */
    Serial.println("no LIS2MDL detected ... Check your wiring!");
    while (1) delay(10);
  }

  /* Starting Serial Monitor */
  Serial.begin(9600);
  Serial.println("Orientation Test");
  Serial.println("");

  pinMode(LED_BUILTIN,OUTPUT);

}

void loop() {
  
  sensors_event_t acc_event;
  sensors_event_t mag_event;
  float alt;
  float az;

  //storing acceleration readings
  float xA = acc_event.acceleration.x;
  float yA = acc_event.acceleration.y;
  float zA = acc_event.acceleration.z;

  //calculating altitude from acceleration readings
  accel.getEvent(&acc_event);
  alt = acos(zA/g)*(180/pi);

  //checking for error putting zA above g, indicating altitude close to zero assuming no outside acceleration
  if(zA > g) { 
    alt = 0;
  }
  //using orientation of x acceleration to correct acos() quadrant error
  if(xA < 0){ 
    alt = -alt;
  }

  //storing magnetometer readings
  float xM = mag_event.magnetic.x;
  float yM = mag_event.magnetic.y;
  float zM = mag_event.magnetic.z;
  
  //calculating azimuth from magnetometer readings
  mag.getEvent(&mag_event);
  az = (atan2(yM,xM)*(180/pi));
  if(az < 0){ //normalizes values to 0-360, since atan2() returns q3 and q4 angles as negative
    az = az + 360;
  }

  Serial.print("yM/xM: ");
  Serial.print(yM/xM);
  Serial.print(" ");

  //cartesianMagDisplay(xM,yM,zM);
  //cartesianAccDisplay(xA,yA,zA);
  altDisplay(alt);
  azDisplay(az);

  Serial.println("");
  delay(100);
}
