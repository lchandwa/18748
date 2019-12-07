#include <Key.h>
#include <Keypad.h>
#include <DHT.h>
#include <Wire.h> 
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

//Constants
#define DHTPIN 13     
#define DHTTYPE DHT22   
#define TEMPERATURE_LENGTH 3 
DHT dht(DHTPIN, DHTTYPE); 

const byte ROWS = 4;
const byte COLS = 3;
float User_set = 0;
int temp_diff = 0;

char hexaKeys[ROWS][COLS] =  {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {8, 7, 6, 5}; 
byte colPins[COLS] = {4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

#define I2C_ADDR 0x27
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

//Variables
int chk;
float temp; //Stores temperature value
char customKey;
byte data_count = 0;
int FAN = 10;
int HEATER = 11;
int motorPin = 9;
int sensorVal;
int PWMVal;
char User_Data[TEMPERATURE_LENGTH];

void setup()
{
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  pinMode(FAN, OUTPUT);
  pinMode(HEATER, OUTPUT);
  pinMode(motorPin, OUTPUT);
}

void loop()
{
  // Read data and store it to variables hum and temp
  temp = dht.readTemperature();
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");

  analogWrite(motorPin, PWMVal);
  
  //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" ");
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("User set:");

  customKey = customKeypad.getKey();
  if(customKey) {
    User_Data[data_count] = customKey;
    lcd.setCursor(9+data_count,1);
    lcd.print(User_Data[data_count]);
    data_count++;
  }

  if(data_count == 2) {
    User_set = (((int)User_Data[0])-48)*10 + (((int)User_Data[1])-48);
    Serial.println(User_set);
    temp_diff = temp - User_set;
  }
  
  if(data_count == (TEMPERATURE_LENGTH)) {
    data_count = 0;
    delay(5000);
    lcd.clear();
  }  

  if(temp_diff > 16) {
    temp_diff = 16;
  }

  if (temp_diff > 0) {
    PWMVal = map(temp_diff, 0, 16, 30, 255);
    analogWrite(FAN, PWMVal);
    digitalWrite(HEATER, LOW);
  } else if (temp_diff == 0) {
    PWMVal = 0;
    analogWrite(FAN, 0);
    digitalWrite(HEATER, LOW);
  } else {
    analogWrite(FAN, 0);
    digitalWrite(HEATER, HIGH); 
  }
}
