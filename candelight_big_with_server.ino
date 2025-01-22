#include <WiFi.h>
#include <Servo.h>

const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD?";

WiFiServer server(80);

String header;
String output12State = "off";
String output15State = "off";

const int output12 = 12;
const int output15 = 15;

Servo servo1 = Servo();       //servo config
Servo servo2 = Servo();
Servo servo3 = Servo();
Servo servo4 = Servo();
const int servo1Pin = 33;
const int servo2Pin = 35;
const int servo3Pin = 37;
const int servo4Pin = 6;

unsigned long currentTime = millis();

unsigned long previousTime = 0;

const long timeoutTime = 8000;

void setup() {
  Serial.begin(115200);

  pinMode(33, OUTPUT);  // buse servo 1
  pinMode(35, OUTPUT);  // buse servo 2
  pinMode(37, OUTPUT);  // buse servo 3
  pinMode(6, OUTPUT);  // gas servo
  pinMode(5, OUTPUT);   // plasma relay
  pinMode(output15, OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(output12, LOW);
  digitalWrite(output15, LOW);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            // turns the GPIOs on and off
            if (header.indexOf("GET /12/on") >= 0) {
              Serial.println("GPIO 12 on");
              output12State = "on";
                    servo4.write(servo4Pin, 10);
                    delay(100);
                    servo4.write(servo4Pin, 10);    //gas closing
                    delay(100);
                    //servo1.write(servo1Pin, 0);    //buses opening
                    //servo2.write(servo2Pin, 0);
                    //servo3.write(servo3Pin, 0);
                    delay(600);
                    digitalWrite(5, HIGH);
                    delay(600);            
                    digitalWrite(5, LOW);  
                    delay(100);
                    digitalWrite(5, HIGH);
                    delay(600);            
                    digitalWrite(5, LOW);
                    delay(100);
            } else if (header.indexOf("GET /12/off") >= 0) {
              Serial.println("GPIO 12 off");
              output12State = "off";
                    //servo1.write(servo1Pin, 0);    //buses opening
                    //servo2.write(servo2Pin, 0);
                    //servo3.write(servo3Pin, 0);
                    //delay(400);
                    servo4.write(servo4Pin, 250);  //gas opening
                    delay(100);
                    servo4.write(servo4Pin, 250);
            } else if (header.indexOf("GET /14/on") >= 0) {
              Serial.println("GPIO 14 on");
              output15State = "on";
              digitalWrite(output15, HIGH);
            } else if (header.indexOf("GET /14/off") >= 0) {
              Serial.println("GPIO 14 off");
              output15State = "off";
              digitalWrite(output15, LOW);
            }
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            // Display current state, and ON/OFF buttons for GPIO 12  
            client.println("<p>GPIO 12 - State " + output12State + "</p>");
            // If the output12State is off, it displays the ON button      
            if (output12State=="off") {
              client.println("<p><a href=\"/12/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/12/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            // Display current state, and ON/OFF buttons for GPIO 14  
            client.println("<p>GPIO 14 - State " + output15State + "</p>");
            // If the output15State is off, it displays the ON button      
            if (output15State=="off") {
              client.println("<p><a href=\"/14/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/14/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
