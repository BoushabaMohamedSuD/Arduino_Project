
//include libraries
// Hello i am Boushaba Chaimaa

#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD


LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display // Change to (0x27,20,4) for 20x4 LCD.
// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distance;


///led rgb

int red_light_pin = 2;
int green_light_pin = 3;
int blue_light_pin = 4;

bool keystop = true;
bool keygo = true;


///// calcule speed
int prevDist = 0;
long speedn = 0;



void setup() {

  /// lcd
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(2, 0); // Set the cursor on the third column and first row.
  lcd.print("Hello Chaimaa!"); // Print the string "Hello World!"



  // put your setup code here, to run once:

  pinMode(13, OUTPUT);

  /// for sensor

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input


  /// led pin
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);

  /// serial
  Serial.begin(9600); // Starts the serial communication
  Serial.print("Hello Chaimaa");
  digitalWrite(13, HIGH); // sets the digital pin 13 on
  delay(3000);
  digitalWrite(13, LOW);


  // led rgb
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance "); // Print the string "Hello World!".
  lcd.setCursor(9, 0);
  lcd.print(0);
  lcd.setCursor(14, 0);
  lcd.print("cm");

}

void loop() {
  // put your main code here, to run repeatedly:
  // Print 'Hello World!' on the first line of the LCD:


  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  //lcd.clear();
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;



  // Prints the distance on the Serial Monitor

  if (prevDist != 0 && prevDist != distance) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm");
    Serial.println("  /////  ");
    lcd.setCursor(9, 0); // Set the cursor on the third column and first row.
    lcd.print("     ");
    lcd.setCursor(9, 0);
    lcd.print(distance); // Print the string "Hello World!"
  }

  if (prevDist == 0) {
    speedn = 0;
  } else {
    speedn = (distance - prevDist) / 0.01;
  }
  speedn = abs(speedn);
  prevDist = distance;

  /* Serial.print("Speed: ");
    Serial.print(speedn);
    Serial.println(" cm/s");*/


  if (distance < 10) {
    digitalWrite(13, HIGH);
    lcd.setCursor(7, 1); // Set the cursor on the third column and first row.
    lcd.print("Stop"); // Print the string "Hello World!"
    tone(11, 200, 500);
    if (keystop) {
      keystop = false;
      keygo = true;
      setColor(0, 255, 255);

    }


  } else {
    digitalWrite(13, LOW);
    lcd.setCursor(7, 1); // Set the cursor on the third column and first row.
    lcd.print("Move"); // Print the string "Hello World!"
    if (keygo) {
      keystop = true;
      keygo = false;
      setColor(0, 255, 0);
    }


  }
}

void setColor(int red, int green, int blue)
{
  Serial.print("color set ");
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(red_light_pin, red);
  analogWrite(green_light_pin, green);
  analogWrite(blue_light_pin, blue);
}
