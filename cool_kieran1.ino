// C++ code

#include <LiquidCrystal_I2C.h>
int moisture = 0;
int light=0;
int PIR=0;
int analog_value=0;
int tempC=0;
float voltage=0;

LiquidCrystal_I2C lcd_1(32,16,2);


void setup()
{
  pinMode(A0, OUTPUT);// power for soil mosture sensor
  pinMode(A1, INPUT);//soil moisture sensor input 
  pinMode(A3,INPUT);//light sensor input
  pinMode(7, INPUT);// PIR sensor input 
  pinMode(A2,INPUT);// temp sensor input 
  Serial.begin(9600); //serial communication
  pinMode(11, OUTPUT); //led for soil mosture sensor
  pinMode(5,OUTPUT);//led for PIR sensor
  pinMode(9,OUTPUT); //led for light sensor
  pinMode(10,OUTPUT);// led for temperature sensor

  lcd_1.init();
  lcd_1.backlight();
  lcd_1.display();
  lcd_1.clear();
 
  
}

void loop()
{
  
   lcd_1.setCursor(0,0);

  // Apply power to the soil moisture sensor
  digitalWrite(A0, HIGH);
  delay(10); // Wait for 10 millisecond(s)
  moisture = analogRead(A1);
  // Turn off the sensor to reduce metal corrosion
  // over time
  digitalWrite(A0, LOW);
  Serial.println(moisture);
  if (moisture > 100) {
    digitalWrite(11, LOW);
  } else 
    if (moisture < 100) {
      digitalWrite(11, HIGH);
      lcd_1.print("Water your plant");
    } 
   delay(500);
  
// read the value from the light sensor and control the led 

   light=analogRead(A3);
   lcd_1.clear();
   if(light>500){
    digitalWrite(9,HIGH);
     lcd_1.print("It is too bright!");
   }else{
    digitalWrite(9,LOW);
   }
    delay(500);
  

  
  //read the value of the PIR sensor and control the led
  PIR=digitalRead(7);
  lcd_1.clear();
  if (PIR==HIGH){
  digitalWrite(5,HIGH);
   lcd_1.print("Movement detected");
  }else{
    digitalWrite(5,LOW);
  }
   delay(500);
  
  
  
  float voltage = analogRead(A2) * 5.0;  // converting the analog 
  //reading to voltage
  voltage /= 1024.0; 
  float tempC = (voltage - 0.5) * 100 ; //converting the voltage reading
  // to Celcius
  lcd_1.clear();
  if(tempC>28){
  digitalWrite(10,HIGH);
   lcd_1.print("It is too hot!");
  }else{
    digitalWrite(10,LOW);
  }
   delay(500);
     
  
  delay(100); // Wait for 100 millisecond(s)
}

