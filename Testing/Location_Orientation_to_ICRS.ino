#include <stdint.h>

//placeholder test values to verify algorithm
int32_t yr = 2025; //raw year
int32_t mo = 5;   //raw month
int32_t day = 27;   //raw day
int32_t hr = 3;    //raw hour
int32_t min = 20;  //raw minute
int32_t sec = 0;  //raw second
double longitude = -111.7487;

//converts raw time data to Local Siderial Time using longitude and time data
double LST(int32_t yr, int32_t mo, int32_t day, int32_t hr, int32_t min, int32_t sec, double longitude)
{
  float JD0 = (367*yr) - int32_t((7*(yr + int32_t((mo+9)/12)))/4) + int32_t((275*mo)/9) + day + 1721013.5;

  double Tut1 = (JD0-2451545.0)/36525; //calculating centures since start of julian date tracking

  double ThetaGST00 = 100.4606184 + (36000.77005361 * Tut1) +  (0.00038793*pow(Tut1,2)); // + (negligible_term*pow(Tut1,3)) //error of about 0.0023 degrees, SEE REFERENCE 1, PAGE 5
  double ThetaGST = ThetaGST00 + (double(0.25068447733746215)*((hr*60)+min+(sec/60.0))); //calculating current siderial time at greenwhich

  while (ThetaGST > 360) { //normalizing to 0-360 degree range
    ThetaGST = ThetaGST -360;
  }

  return ThetaGST + longitude; //using longitudinal difference to convert to local time
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  double localSidereal = LST(yr,mo,day,hr,min,sec,longitude);
  Serial.println(localSidereal,7);


}

void loop() {
  // put your main code here, to run repeatedly:

}

