#include <SoftwareSerial.h>
#include<dht.h>
SoftwareSerialmySerial(9, 10);
dht DHT;
#define DHT11_PIN 3
#define R 2
#define G 7
#define B 5
#define MQ2 A2


intgaslevel;
voidCheckShutDown();
floatCheckTemp();
voidSendTextMessage();

int sensor = A1;
floattemp_read, Temp_alert_val, Temp_shut_val;
intsms_count = 0, Fire_Set;

intFlamePin = 6;  
int Flame = HIGH;  

void setup()
{
pinMode(MQ2, INPUT);
pinMode(R, OUTPUT);
pinMode(G, OUTPUT);
pinMode(B, OUTPUT);

pinMode(FlamePin, INPUT);

pinMode(sensor, INPUT);
mySerial.begin(9600);
Serial.begin(9600);
delay(500);
}

void loop()
{
CheckFire();
CheckShutDown();
}

voidCheckFire()
{
Temp_alert_val = CheckTemp();
Serial.println("Temperature:");
Serial.println(Temp_alert_val);

gaslevel = (analogRead(MQ2));
gaslevel = map(gaslevel, 0, 1023, 0, 255);
Serial.println("Gas Level:");
Serial.println(gaslevel);

  Flame = digitalRead(FlamePin);
Serial.println("Flame Status:");
Serial.println(Flame);

intchk = DHT.read11(DHT11_PIN);
Serial.println("dht_Humidity " );
Serial.println(DHT.humidity, 1);
Serial.println("dht_Temparature ");
Serial.println(DHT.temperature, 1);
if ((Temp_alert_val> 31) && (gaslevel> 65 &&gaslevel<= 90 ) && (Flame == HIGH) && (DHT.temperature>=31) && (DHT.humidity<=50))

  {
digitalWrite(G, LOW); //green led is off
digitalWrite(B, LOW); //blue led is off
    _delay_ms(500);
digitalWrite(R, HIGH); //red led is on

Serial.println("Fire Detected");
Serial.println("HIGH FLAME");
Serial.println("LED on");


Fire_Set = 1;
while (sms_count< 3) //Number of SMS Alerts to be sent
    {
SendTextMessage(); // Function to send AT Commands to GSM module
    }

  }
else if ((gaslevel> 30 &&gaslevel<= 65) && (Flame == LOW))
{ //gaslevel is greater than 30 and less than 60
digitalWrite(R, LOW); //red led is off
digitalWrite(G, LOW); //green led is off
    _delay_ms(500);
digitalWrite(B, HIGH); //blue led is on
Serial.println("No Flame");

  }
}


floatCheckTemp()
{
temp_read = analogRead(sensor); // reads the sensor output (Vout of LM35)
temp_read = temp_read * 5; // converts the sensor reading to temperature
temp_read = temp_read / 10; // adds the decimal point
returntemp_read; // returns temperature value in degree celsius
}



voidCheckShutDown()
{
if (Fire_Set == 1)
  {
Temp_shut_val = CheckTemp();

if ((Temp_shut_val< 28) || (gaslevel> 20 &&gaslevel<= 30))
    {
sms_count = 0;
digitalWrite(R, LOW); //red led is off
digitalWrite(B, LOW); //blue led is off
      _delay_ms(500);//delay
digitalWrite(G, HIGH); //green led is on
      _delay_ms(500);
Fire_Set = 0;
    }
  }
}

voidSendTextMessage()
{
mySerial.println("AT+CMGF=1");    
delay(2000);
mySerial.println("AT+CMGS=\"+918770851950\"\r"); 
delay(2000);
mySerial.println("Fire detected!");
delay(200);
mySerial.println((char)26);
delay(5000);
mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); 
delay(2000);
mySerial.println("Fire detected!");
delay(200);
mySerial.println((char)26);
sms_count++;
}

