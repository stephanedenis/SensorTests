/**
* To use with TCRT5000 Reflective Optical Sensor
*
* Build a paper laser printed optical disc generated by 
* http://www.dgkelectronics.com/inkscape-extension-for-creating-optical-rotary-encoder-discs
*
* Build a standard Arduino sensor, to use on digital pins.
* use 300 ohm for led current limitor (gives 2mm proximity at 5V)
* use 20K ohm for phototransistor external pullup
* hysterisis is done by switching internal 20K pullup (managed by this program)
*
*/
const int ledPin = 13;        // built-in arduino uno LED
const int sensorLedPin = 3;
const int sensorPhotoPin = 2;  // Phototransistor

int ledBright=127;            // IR sensor led brightness

int pulseCount=0;
int pulseVal=0;

void setup(){
  //start serial connection
  Serial.begin(9600);

  //configure pin2 as an input and enable the internal pull-up resistor
  pinMode(sensorPhotoPin, INPUT_PULLUP);
  analogWrite(sensorLedPin,ledBright);
        
  pinMode(ledPin, OUTPUT); // monitor  
}

void loop()
{
  if(Serial.available()){
    char val = Serial.read();
    if(val != -1)
    {
      switch(val)
      {
        
      case '8':
        ledBright++;
        if(ledBright>255)ledBright=255;

        Serial.println("+");  
        break;
      case '2':
        ledBright--;
        if(ledBright<0)ledBright=0;
        
        Serial.println("-");   
        break;
      }
      analogWrite(sensorLedPin,ledBright);
    }
  }

  int sensorVal = digitalRead(2);
  
  if(sensorVal != pulseVal) pulseCount++;
  {
    pulseVal=sensorVal;
    pinMode(sensorPhotoPin, (sensorVal?INPUT_PULLUP:INPUT));  // Hysteresis effect22222222222
  }

  Serial.print(ledBright);
  Serial.print("    logic=");  
  
  Serial.print(pulseVal);
  Serial.print("    count=");
  Serial.println(pulseCount);
  
  
  digitalWrite(ledPin,pulseVal);
}


