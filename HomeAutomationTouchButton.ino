
#include <Bridge.h>
#include <CapacitiveSensor.h>
#include <HttpClient.h>
#include <Console.h>


//HA API Setup
String ha_api_server = "192.168.1.17";
String ha_api_port = "8123";
String ha_api_password = "password";

//Sensor 1 API path
String touch_1_ha_api_path = "/api/events/touched_left_ball/";

//Sensor 2 API Path
String touch_2_ha_api_path = "/api/events/touched_left_ball/";

// Touch Sensitivity 
long touchvalue_1 = 25;  // adjust value depending on capacitive sensor reading
long touchvalue_2 = 35;  // adjust value depending on capacitive sensor reading


// Inital Capacitiv Sensors
CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_6_13 = CapacitiveSensor(6,13);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired





// LED Setup
int red = 9;
int white = 10;
int green = 11;

// Misc Varibles 
String httpcode;
int quickflashdelay = 100;
int longflashdelay = 600;
String api_url_1 = ha_api_server + ":"+ ha_api_port + touch_1_ha_api_path;
String api_url_2 = ha_api_server + ":"+ ha_api_port + touch_2_ha_api_path;
String curlcmd_1 = "curl -X POST --header \"X-HA-Access: "+ ha_api_password +"\" -s -o /dev/null -I -w \"%{http_code} \" " + api_url_1;
String curlcmd_2 = "curl -X POST --header \"X-HA-Access: "+ ha_api_password +"\" -s -o /dev/null -I -w \"%{http_code} \" " + api_url_2;           



void setup()                    
{
   Serial.begin(9600);
   Bridge.begin();
   Console.begin(); 
  
   Console.println("Watching for Touches");
  
  //Setup LED Pins
  pinMode(red, OUTPUT);
  pinMode(white, OUTPUT);
  pinMode(green, OUTPUT);
   
 
  // Starup Light Show  
   digitalWrite(green, HIGH);
   digitalWrite(red, HIGH);
   digitalWrite(white, HIGH);
   delay(1000);
   digitalWrite(green, LOW);
   digitalWrite(red, LOW);
   digitalWrite(white, LOW);
 
   
}


void loop()                    
{
    //Get Cap sensor readings 

     long capsense1 =  cs_4_2.capacitiveSensor(500);
     long capsense2 =  cs_6_13.capacitiveSensor(500);

    // Print cap redings to serial 
    Serial.print(capsense1);                  
    Serial.print("\t");
    Serial.print(capsense2);                 
    Serial.print("\n");
    
    // Print cap redings to console 
    Console.print(capsense1);
    Console.print("\t");
    Console.print(capsense2);               
    Console.print("\n"); 

   
    // What to do if sensor 1 is touched 
    if (capsense1 > touchvalue_1)  
        {
           int sensor = 1;
           TouchDetected(sensor);
         
           // Run Curl command in a shell and get a response code
           httpcode = HitApi(curlcmd_1, api_url_1);
           
    
           // If the response code is not 200 flash the red light
           if ( httpcode != "200 " ) 
              {
              QuickFlashLed(red);
              }
          
          // If the response code is 200 flash the green light
           if ( httpcode == "200 " ) 
             {
             QuickFlashLed(green);
             }

      }
      
       // What to do if sensor 2 is touched 
     if (capsense2 > touchvalue_2)  
        {
           int sensor = 2;
           TouchDetected(sensor);
         
           // Run Curl command in a shell and get a response code
           httpcode = HitApi(curlcmd_2, api_url_2);
           
    
           // If the response code is not 200 flash the red light
           if ( httpcode != "200 " ) 
              {
              QuickFlashLed(red);
              }
          
          // If the response code is 200 flash the green light
           if ( httpcode == "200 " ) 
             {
             QuickFlashLed(green);
             }

      }




   
  }


 int QuickFlashLed(int led) 
     {
       
        digitalWrite(led, HIGH);   
        delay(quickflashdelay);              
        digitalWrite(led, LOW);
        delay(quickflashdelay);  
        digitalWrite(led, HIGH); 
        delay(quickflashdelay);             
        digitalWrite(led, LOW);
        delay(quickflashdelay);  
        digitalWrite(led, HIGH);  
        delay(quickflashdelay);              
        digitalWrite(led, LOW);  

    }

String HitApi(String curlcmd, String api_url)
    {
      String httpcode;   
      
       Process p;
       p.runShellCommand(curlcmd);
           
       Serial.print("\n");
       Serial.print("Hitting api at: " + api_url);
       Serial.print("\n");
       Serial.print("Using Curl command: " + curlcmd);
       Serial.print("\n");
       
       Console.print("\n");
       Console.print("Hitting api at: " + api_url);
       Console.print("\n");
       Console.print("Using Curl command: " + curlcmd);
       Console.print("\n");
      
           
       //While the shell is open get the HTTP response code from the curl command
       while (p.available())
           {
             char c = p.read();
             httpcode = httpcode + c;
             Serial.write(c);
             }     
        p.close();
        
        Serial.print("HTTP Response: ");
        Serial.print(httpcode);
        Serial.print("\n");
        
        Console.print("HTTP Response: ");
        Console.print(httpcode);
        Console.print("\n");
        
        
        return httpcode;
    }





int TouchDetected (int sensor)
    {
      //print to serial that touch was detected
      Serial.print("<--------------------------TOUCH DETECTED-------------------------->");
      Serial.print("\n");
      Serial.print("<-----------------------------Sensor " + String(sensor) + " ---------------------------->");                 
      Serial.print("\n");
      Serial.print("<------------------------------------------------------------------>");
      
      Console.print("<--------------------------TOUCH DETECTED-------------------------->");
      Console.print("\n");
      Console.print("<-----------------------------Sensor " + String(sensor) + " ---------------------------->");                 
      Console.print("\n");
      Console.print("<------------------------------------------------------------------>");
   
   
       // Flash a light 
       digitalWrite(white, HIGH); 
       delay(longflashdelay);  
       digitalWrite(white, LOW);
    }
