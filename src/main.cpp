// routing: "update", parameter: "switch" / "slider", value: int

#include <analogWrite.h>
#include <ESP32Servo.h>

#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>


Servo servo4;
Servo servo27;
Servo servo13;

// Network credentials
const char* ssid     = "Telia-15286F";
const char* password = "88F186ACC0";

const char* PARAM_INPUT_1 = "switch";

const char* PARAM_INPUT_2 = "slider";
const char* PARAM_INPUT_27 = "slider27";
const char* PARAM_INPUT_13 = "slider13";

const int output2 = 2; //output LED (blue)
const int output4 = 4; //Servo 2
const int output27 = 27; //Servo 27
const int output13 = 13; //Servo13

int ledState2 = LOW; //the current state of the output pin 2
int ledState4 = LOW; //the current state of the output pin 4
int ledState27 = LOW; //the current state of the output pin 4
int ledState13 = LOW; //the current state of the output pin 4


String sliderValue = "0"; //initial slider value
String sliderValue27 = "0"; //initial slider value
String sliderValue13 = "0"; //initial slider value


int dutyCycle4;
int dutyCycle27;
int dutyCycle13;



// AsyncWebServer object on port 80
AsyncWebServer server(80);

// kinda implementeing a weirdo toggle here by reading the output state
String outputState(){
  if(digitalRead(output2)){
    return "checked";
  }
  else {
    return "";
  }
  return "";
}


// Replaces placeholders with button section
String processor(const String& var){
  if(var == "BUTTONPLACEHOLDER"){
    String buttons ="";
    String outputStateValue = outputState();
    buttons+= "<h4> Output - GPIO 2 - State <span id=\"outputState\"></span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"output\" " + outputStateValue + "><span class=\"switchswitchswitchswitchSlider\"></span></label>";
    return buttons;
  }

  if (var == "SLIDERVALUE"){
    return sliderValue;
  }
  return String();
}



void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  pinMode(output2, OUTPUT);
  
  servo4.attach(output4);
  servo27.attach(output27);
  servo13.attach(output13);
  
  digitalWrite(output2, LOW);
  
  servo4.write(0);
  servo27.write(0);
  servo13.write(0);

  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
request->send(200, "index/html", "index_html");
});

  // Send a GET request to <ESP_IP>/update?state=<inputMessage>
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/update?state=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      digitalWrite(output2, inputMessage.toInt());
      ledState2 = !ledState2;
      
    } else if (request->hasParam(PARAM_INPUT_2)) {
      inputMessage = request->getParam(PARAM_INPUT_2)->value();
      sliderValue = inputMessage;
      ledState4 = sliderValue.toInt();
      dutyCycle4 = map(ledState4, 0, 1023, 0, 180);
      ledState4 = dutyCycle4;
      
    } else if (request->hasParam(PARAM_INPUT_27)) {
      inputMessage = request->getParam(PARAM_INPUT_27)->value();
      sliderValue27 = inputMessage;
      ledState27 = sliderValue27.toInt();
      dutyCycle27 = map(ledState27, 0, 1023, 0, 180);
      ledState27 = dutyCycle27;  

    } else if (request->hasParam(PARAM_INPUT_13)) {
      inputMessage = request->getParam(PARAM_INPUT_13)->value();
      sliderValue13 = inputMessage;
      ledState13 = sliderValue13.toInt();
      dutyCycle13 = map(ledState13, 0, 1023, 0, 180);
      ledState13 = dutyCycle13;
    }
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.println(inputMessage);
    Serial.println(inputParam);
    request->send(200, "text/plain", "OK");
  });

  
  // Start server
  server.begin();
}
  
void loop() {
  // set the LED:
  servo4.write(ledState4);
  servo27.write(ledState27);
  servo13.write(ledState13);
      
  digitalWrite(output2, ledState2);
  //analogWrite(output4, ledState4);
  //analogWrite(output27, ledState27);
  //analogWrite(output13, ledState13);

}