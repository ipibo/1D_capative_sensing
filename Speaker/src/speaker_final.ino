//Deze waardes moeten aangepast worden voor de ATtiny!!!!!!!!!!
//int capIn1 = 2;
//int capIn2 = 4;
int capIn1 = A;
int capIn2 = A0;
int potIn = 3;
//int toneOut = 1;
int toneOut = 10;


//#include <Plaquette.h>
//#include <PqExtra.h>
#include <Average.h>
#include <CapacitiveSensor.h>

CapacitiveSensor cap = CapacitiveSensor(capIn1, capIn2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

int threshold = 200;
int maxVal = 8000;
int waarde = 4;

#define STDDEV_THRESHOLD 0.9 //.0

Average<float> av(5);
Average<float> tresholdAv(10);

//AdaptiveNormalizer normalizer(0, 1);
//Thresholder peakDetector(STDDEV_THRESHOLD, THRESHOLD_HIGH);
//
//AdaptiveNormalizer normalizerThreshold(0, 1);
//Thresholder peakDetectorThreshold(STDDEV_THRESHOLD, THRESHOLD_HIGH);



void setup() {
  Serial.begin(9600);
  pinMode(potIn, INPUT);
  pinMode(toneOut, OUTPUT);

}

void loop() {
  long reading = cap.capacitiveSensor(30);
  av.push(reading);
  threshold = analogRead(potIn);
//  tresholdAv.push(threshold);
  int t = threshold;
  float mappedThreshold = map(t, 0, 1023 , 0, 20);
  float normData = normalizedData(reading);


  //    Serial.print(mappedThreshold); Serial.print("\t");
  //    Serial.print(normData);

  Serial.print(reading);
  Serial.println();
  float maxReading = min(reading, 1000); // assigns sensVal to the larger of sensVal or 20


  maxReading = 100;
  if(reading < 1){
//  tone(toneOut, 10, 100);
//  delay(50);
  }
  else{tone(toneOut, reading, 100);
  delay(50);
  }

  if (normData > mappedThreshold) {
    tone(toneOut, maxReading, 100);
    delay(50);
  }
}

int maxSoundValue = 1000;

float normalizedData(float nD) {
  float normalizeD = 0;
  normalizeD = map(nD, 0, 1000, 0, 20);
  return normalizeD;
}
