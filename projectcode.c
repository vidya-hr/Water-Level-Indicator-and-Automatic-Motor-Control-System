 #include<LiquidCrystal_I2C.h>

//declaration of pins

int trigPin = 10;
int echoPin = 9;
int motor = 5;
int rled = 2;
int yled = 3;
int gled = 4;



//declaration of variables
long time;
float distance;

//function for ultrasonic
void ultrasonic(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);

  // transmitting sound for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  time=pulseIn(echoPin , HIGH);
  distance = time * 0.0343/2;
}


void lcd_start(){
    LiquidCrystal_I2C lcd(0x26, 16, 2);
    lcd.init();					
    lcd.backlight();
 }

void led_driver(){
  if (distance >= 300){
    digitalWrite(rled,HIGH);//tank low
    digitalWrite(yled,LOW);
    digitalWrite(gled,LOW);
    digitalWrite(motor,HIGH);
  }
  else if (distance >= 150){
    digitalWrite(yled,HIGH);//tank med
    digitalWrite(rled,LOW);
    digitalWrite(gled,LOW);
    digitalWrite(motor,HIGH);
  }
  else{
    digitalWrite(gled,HIGH);//tank full
    digitalWrite(yled,LOW);
    digitalWrite(rled,LOW);
    digitalWrite(motor,LOW);
  }
}

//setup peripherals
void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motor, OUTPUT);
  pinMode(rled, OUTPUT);
  pinMode(yled, OUTPUT);
  pinMode(gled, OUTPUT);
    lcd_start();
  
}

void loop()
{
  LiquidCrystal_I2C lcd(0x26, 16, 2);
  lcd.backlight();
   lcd.setCursor(0,0);
   lcd.print("Water Level:");
   lcd.print(distance);
   ultrasonic();
   led_driver();
  
}
