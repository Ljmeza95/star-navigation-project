#include <stdint.h>

//placeholder test values to verify algorithm
int32_t yr = 2025; //raw year
int mo = 5;   //raw month
int day = 21;   //raw day
int hr = 2;    //raw hour
int min = 47;  //raw minute
int sec = 0;  //raw second

//converts raw time data to midnight of the current julian day
float rawToJulianMidnight(int32_t yr, int mo, int day){
  float JD0 = (367*yr) - int((7*(yr + int((mo+9)/12)))/4) + int((275*mo)/9) + day + 1721013.5;
  return JD0;
}

double rawToMeanSiderial(float JD0, int hr, int min, int sec) { //converts julian day and time of day to find siderial time in angular terms (degrees for now)

  double Tut1 = (JD0-2451545.0)/36525;

  double ThetaGST00 = 100.4606184 + (36000.77005361 * Tut1) +  (0.00038793*pow(Tut1,2)); // + (negligible_term*pow(Tut1,3)) //error of about 0.0023 degrees, SEE REFERENCE 1, PAGE 5
  double ThetaGST = ThetaGST00 + (double(0.25068447733746215)*((hr*60)+min+(sec/60.0)));

  while (ThetaGST > 360) {
    ThetaGST = ThetaGST -360;
  }

  return ThetaGST;
  
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  float JD0 = rawToJulianMidnight(yr,mo,day);
  Serial.println(JD0);

  double ThetaGST = rawToMeanSiderial(JD0,hr,min,sec);
  Serial.println(ThetaGST,7);


}

void loop() {
  // put your main code here, to run repeatedly:

}

