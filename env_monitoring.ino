#include <DHT.h>
#include <ESP8266WiFi.h>
 
#define DHTPIN 2          //DHT11 is connected to GPIO Pin 2
#define SENSOR_PIN A0

String apiKey = "LMS8RNVNN0RB3DJR";     //  Enter your Write API key from ThingSpeak
const char* ssid =  "raju";     // Enter your WiFi Network's SSID
const char* pass =  "123456789"; // Enter your WiFi Network's Password
const char* server = "api.thingspeak.com";
 
float humi;
float temp;
unsigned int sample;
const int sampleWindow = 50; 
 
DHT dht(DHTPIN, DHT11);
WiFiClient client;
 
void setup() 
{
       pinMode (SENSOR_PIN, INPUT);
       Serial.begin(115200);
       delay(10);
       dht.begin();
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(100);
            Serial.print("*");
     }
      Serial.println("");
      Serial.println("***WiFi connected***");
 
}
 
void loop() 
{
  
      humi = dht.readHumidity();
      temp = dht.readTemperature();
      unsigned long startMillis= millis();                   // Start of sample window
   float peakToPeak = 0;                                  // peak-to-peak level
 
   unsigned int signalMax = 0;                            //minimum value
   unsigned int signalMin = 1024;                         //maximum value
 
                                                          // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(SENSOR_PIN);                    //get reading from microphone
      if (sample < 1024)                                  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;                           // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;                           // save just the min levels
         }
      }
   }
 
   peakToPeak = signalMax - signalMin;                    // max - min = peak-peak amplitude
   int db = map(peakToPeak,20,900,49.5,90);
 
      if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
      {  
       String sendData = apiKey+"&field1="+String(temp)+"&field2="+String(humi)+"&field3="+String(db); 
       
       //Serial.println(sendData);

       client.print("POST /update HTTP/1.1\n");
       client.print("Host: api.thingspeak.com\n");
       client.print("Connection: close\n");
       client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
       client.print("Content-Type: application/x-www-form-urlencoded\n");
       client.print("Content-Length: ");
       client.print(sendData.length());
       client.print("\n\n");
       client.print(sendData);

       Serial.print("Temperature: ");
       Serial.print(temp);
       Serial.print("deg C. Humidity: ");
       Serial.print(humi);
       Serial.print("%. Noise: ");
       Serial.print(db);
       Serial.println(" db Connecting to Thingspeak.");
       }
      
      client.stop();

      Serial.println("Sending....");
  
 delay(10000);
}
