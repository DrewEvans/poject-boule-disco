// Define Pins
const int analogInPin = A0; // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0; // value read from the pot
int outputValue = 0; // value output to the PWM (analog out)

// LED Pin Ports
#define BLUE 3
#define GREEN 5
#define RED 6

void setup()
{
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

// main loop
void loop()
{
  trafficLightDetection();
}

void trafficLightDetection()
{
#define delayTime 2000
  int redValue;
  int greenValue;
  int blueValue;
  static int currentColor;

  sensorValue = analogRead(analogInPin);           // read the analog in value:
  outputValue = map(sensorValue, 0, 1023, 0, 255); // map it to the range of the analog out:
  analogWrite(analogOutPin, outputValue);          // change the analog out value:

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // Green color Config
  redValue = 255; // choose a value between 1 and 255 to change the color.
  greenValue = 0;
  blueValue = 0;

  currentColor = 1;
  analogWrite(RED, redValue);
  analogWrite(GREEN, greenValue);
  analogWrite(BLUE, blueValue);

  delay(delayTime);

  // Yellow color Config
  redValue = 255; // choose a value between 1 and 255 to change the color.
  greenValue = 255;
  blueValue = 0;

  currentColor = 2;
  analogWrite(RED, redValue);
  analogWrite(GREEN, greenValue);
  analogWrite(BLUE, blueValue);

  delay(delayTime);

  // Red Color Config
  redValue = 0;
  greenValue = 255;
  blueValue = 0;

  currentColor = 3;
  analogWrite(RED, redValue);
  analogWrite(GREEN, greenValue);
  analogWrite(BLUE, blueValue);
  sensorValue = analogRead(analogInPin);

  if (sensorValue > 900)
  {
    Serial.println("I'm parked at a red light");
  }

  delay(delayTime);
}
