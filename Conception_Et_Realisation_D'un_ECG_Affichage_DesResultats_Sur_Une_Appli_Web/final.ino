 #include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
 
/* Set these to your desired credentials. */
const char *ssid ="AndroidAP";  //ENTER YOUR WIFI SETTINGS
const char *password = "khadija21";

//Global Var zone
String Name ;
String Ref ;
String Stat ;
//Web/Server address to read/write from 
String host = "192.168.43.75";  // database IP 
String Users_table = "patients";


String get_input(String what_to_get){
  /* this function return String from the stdin of the serial and ask dynamicly for the desired input */
  Serial.println("Enter "+what_to_get+" : ");
  while(true){
    String temp ;
    while(Serial.available()) {
        temp = Serial.readString();// read the incoming data as string
      if (temp.length() > 0){
          Serial.print("You Entred "+what_to_get+" : ");
          //Trinming last caracter \n
          temp.trim() ;
          Serial.println(temp);
          return temp;
        }
    }
  }
}
void send_data(String PHPpage ,String Data){
  HTTPClient http;    //Declare object of class HTTPClient
  String link = "http://"+host+"/projet.php/"+PHPpage+"?"+Data ;//arduino write or pass argument  in the link after that we will found all  this informations in the page 
  http.begin(link);    
  int httpCode = http.GET();            //Send the request
//  String payload = http.getString();    //Get the response payload
  // Serial.print("link  :  ");Serial.println(link);   //Print HTTP return code
 // Serial.print("Result :  ");Serial.println(payload);   //Print HTTP return code
   //Serial.print("httpCode :  "); Serial.println(httpCode);    //Print request response payload
  http.end();  //Close connection
 
}

void setup() { 
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
 
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
   Serial.print(".");
  }
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid); 
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

  
  //---------------------------------------------------------------------------
  Name = get_input("Name");
  Ref = get_input("reference");
  Stat = get_input("Status");
  //---------------------------------------------------------------------------
  
  //AddUser.php?c=patient1&n=bob&ref=11&a=alive
  String  Data = "c="+Users_table+"&n="+Name+"&ref="+Ref+"&a="+Stat;
  send_data("AddUser.php",Data);// file  already created name AddUser 
  
}
 
//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {

    int sensorValue = analogRead(A0);
  //  Serial.print(sensorValue);
    Serial.println("Sending "+String(sensorValue)+" to   :  "+Name); 
   // String v = String (random(0,1024));
    String Data = "graph=graph_"+Name+"_"+Ref+"&v="+sensorValue;
    send_data("Add_UserData.php",Data);
    delay(500);
    
    }
//=======================================================================*/
