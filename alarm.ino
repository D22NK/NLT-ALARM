


#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "Alarm";
const char* password = "alarm123";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";
String output3State = "off";
// Assign output variables to GPIO pins
const int output5 = 2;
const int output4 = 1;
const int trilled = 14;
const int power = 15;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
  #include <Fonts\FreeMono24pt7b.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000, 
  B00000000, B00110000 };


void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
    pinMode(trilled, OUTPUT);
      pinMode(power, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(trilled, LOW);
    digitalWrite(power, HIGH);
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
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(2000); 
  display.clearDisplay();
  display.drawPixel(10, 10, SSD1306_WHITE);
  display.display();
  delay(2000);
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);

   display.clearDisplay();
}
void brand(){
  digitalWrite(trilled, HIGH);
  
   display.clearDisplay();
    display.display(); 
              display.setTextColor(BLACK, WHITE);
  display.setTextSize(2);
  display.setCursor(0, 10);

  display.println("__Brand__");
   display.display(); 
  display.setTextColor(WHITE);
   display.setTextSize(2);
  display.setCursor(0, 30);
   display.println("Groot");
   display.println("Diamant 9");
    
  display.display(); 
}
void overstroming(){
  digitalWrite(trilled, HIGH);
   display.clearDisplay();
    display.display(); 
              display.setTextColor(BLACK, WHITE);
  display.setTextSize(2);
  display.setCursor(0, 10);

  display.println("Water");
display.setCursor(0, 25);
  display.println("Overlast");
   display.display(); 
  display.setTextColor(WHITE);
   display.setTextSize(1);
  display.setCursor(0, 43);
   display.println("Afsluitdijk");
  
   display.println("Zoek een hoge plaats!");
    
  display.display(); 
}

void luchtalarm(){
  digitalWrite(trilled, HIGH);
   display.clearDisplay();
    display.display(); 
              display.setTextColor(BLACK, WHITE);
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.println("Luchtalarm");
   display.display(); 
  display.setTextColor(WHITE);
   display.setTextSize(1);
  display.setCursor(0, 30);
   display.println("Giftige stoffen");
  
   display.println("Sluit ramen & deuren!");
    
  display.display(); 
}
void loop(){
    digitalWrite(power, HIGH);
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
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

             if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output5, HIGH);
overstroming();
            } 
            if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
                digitalWrite(trilled, LOW);
                  display.clearDisplay();
    display.display(); 
            }
            // turns the GPIOs on and off
            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
               
brand();

            }  if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW);
               digitalWrite(trilled, LOW);
                  display.clearDisplay();
    display.display(); 
            } 
            
            if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("GPIO 3 on");
              output3State = "on";
              digitalWrite(output4, HIGH);
              luchtalarm();
            } 
            if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("GPIO 3 off");
              output3State = "off";
              digitalWrite(output4, LOW);
                digitalWrite(trilled, LOW);
                display.clearDisplay();
    display.display(); 
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>h1 { margin-top:0;  padding-top: 10px; padding-bottom: 0px;}  body {margin: 0px; padding: 0px; padding-top: 0px;} html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button {border: none; color: white; padding: 16px 40px; width: 75%; box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".buttondisabled {background-color: #CCD1D1;}");
            client.println(".button2 {background-color: #E74C3C;}");
            client.println(".button3 {background-color: #EF6C00;}");
            client.println(".button4 {background-color: #03A9F4;}");
            client.println(".hoofd {box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19); color: white; background-color: #27AE60; width: 100%; heigth: 15%; margin: 0px; padding: 0px; border-bottom: 3px solid #1E8449; text-align: center; }");
            client.println(".button5 {background-color: #7E57C2;}</style></head>");
            // Web Page Heading
            client.println("<body><div class=\"hoofd\"><h1>NLT Alarm</h1><h5>Het alarm voor slechthorende.</h5></div>");
            if(output5State=="on") {
            client.println("<h4>Huidig alarm: Brand</h4>");
            } if(output4State=="on") {
              client.println("<h4>Huidig alarm: Overstroming</h4>");
            }
              if(output3State=="on") {
               client.println("<h4>Huidig alarm: Luchtalarm</h4>");             
              }
              if(output3State=="off" && output4State=="off" && output5State=="off") {client.println("<h4>Geen alarmen ingeschakelt</h4>");}
             // If the output4State is off, it displays the ON button       
            if(output3State=="on" || output4State=="on") {
              client.println("<p>Brand - Disabled</p>");
              client.println("<p><a href=\"/5/off\"><button class=\"button buttondisabled\" disabled>Disabled</button></a></p>");
            }
           else 
            if (output5State=="off") {
              client.println("<p>Brand - " + output5State + "</p>");
              client.println("<p><a href=\"/5/on\"><button class=\"button button3\">Brand</button></a></p>");
            } 
            else {
              client.println("<p>Brand - " + output5State + "</p>");
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

         
            // If the output4State is off, it displays the ON button       
            if(output3State=="on" || output5State=="on") {
              client.println("<p>Overstroming - Disabled</p>");
              client.println("<p><a href=\"/4/off\"><button class=\"button buttondisabled\" disabled>Disabled</button></a></p>");
            }
           else 
            if (output4State=="off") {
              client.println("<p>Overstroming - " + output4State + "</p>");
              client.println("<p><a href=\"/4/on\"><button class=\"button button4\">Overstroming</button></a></p>");
            } 
            else {
              client.println("<p>Overstroming - " + output4State + "</p>");
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

           // If the output4State is off, it displays the ON button       
            if(output4State=="on" || output5State=="on") {
              client.println("<p>Luchtalarm - Disabled</p>");
              client.println("<p><a href=\"/3/off\"><button class=\"button buttondisabled\" disabled>Disabled</button></a></p>");
            }
           else 
            if (output3State=="off") {
              client.println("<p>Luchtalarm - " + output3State + "</p>");
              client.println("<p><a href=\"/3/on\"><button class=\"button button5\">Luchtalarm</button></a></p>");
            } 
            else {
              client.println("<p>Luchtalarm - " + output3State + "</p>");
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
client.println("<h5 style=\"color:black; position: absolute; right: 10px; bottom: 3px;\">Daan Kentrop | 2020</h5>");
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
