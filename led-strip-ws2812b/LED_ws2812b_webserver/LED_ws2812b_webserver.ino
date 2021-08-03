/*
  WS2812FX Webinterface.
  
  João Pedro Doimo Torrezan

  
  FEATURES
    * Webinterface with mode, color, speed and brightness selectors
    * Alexa integration with effects selection
    * ESP32 and ESP8266 compatibility

    
  CHANGELOG
  2021-06-22 initial version
    
*/

#ifdef ESP32
  #include <WiFi.h>
  #include <WebServer.h>
  #define WEBSERVER WebServer

#else
  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
  #define WEBSERVER ESP8266WebServer
#endif
//led-control library
#include <WS2812FX.h>
//wifi controll library
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

//libraries for alexa integration
//#include <ESPAsyncWebServer.h>
//#include "fauxmoESP.h"

extern const char index_html[];
extern const char main_js[];

//===========================================
// Serial comunication config
//===========================================

  #define SERIAL_BAUDRATE     115200

//===========================================
//Wifi configuration
//===========================================

  WiFiManager wifiManager;
  
  
  #define WIFI_TIMEOUT 30000              // checks WiFi every ...ms. Reset after this time, if WiFi cannot reconnect.
  
  
  #define STATIC_IP                       // uncomment for static IP, set IP below
  #ifdef STATIC_IP
    IPAddress ip(192,168,1,6);
    IPAddress gateway(192,168,1,1);
    IPAddress subnet(255,255,255,0);
  #endif

//============================================================
//LED Controll
//============================================================
  #define LED_PIN 2                       // 0 = GPIO0, 2=GPIO2
  #define LED_COUNT 145
  
  // ws2812fx QUICKFIX...See https://github.com/esp8266/Arduino/issues/263
  #define min(a,b) ((a)<(b)?(a):(b))
  #define max(a,b) ((a)>(b)?(a):(b))
  
  //default led state {Mode : Rainbow, color : RED, brightness : 128, speed : 2500 (10 - 5000) }
  #define DEFAULT_COLOR 0xFF0000        //default color red
  #define DEFAULT_BRIGHTNESS 128
  //  
  #define DEFAULT_SPEED 100            //
  #define DEFAULT_MODE FX_MODE_RAINBOW_CYCLE
  
  unsigned long auto_last_change = 0;
  unsigned long last_wifi_check_time = 0;
  
  String modes = "";
  uint8_t myModes[] = {}; // *** optionally create a custom list of effect/mode numbers
  bool auto_cycle = false;
  
  WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); //object controll led

//============================================================
//HTTP_SERVER config
//============================================================
  
  #define HTTP_PORT 80
  WEBSERVER server(HTTP_PORT);
  

//============================================================

void setup(){

  Serial.begin(SERIAL_BAUDRATE);
  delay(500);
  Serial.println("\n\nStarting...");

  modes.reserve(5000);
  modes_setup();

  Serial.println("WS2812FX setup");
  ws2812fx.init();
  ws2812fx.setMode(DEFAULT_MODE);
  ws2812fx.setColor(DEFAULT_COLOR);
  ws2812fx.setSpeed(DEFAULT_SPEED);
  ws2812fx.setBrightness(DEFAULT_BRIGHTNESS);
  ws2812fx.start();

  //reset settings - wipe credentials for testing
  //wifiManager.resetSettings();
  Serial.println("Wifi setup");
  wifi_setup();
 
  Serial.println("HTTP server setup");
  server.on("/", srv_handle_index_html);
  server.on("/main.js", srv_handle_main_js);
  server.on("/modes", srv_handle_modes);
  server.on("/set", srv_handle_set);
  server.onNotFound(srv_handle_not_found);
  server.begin();
  Serial.println("HTTP server started.");

  Serial.println("ready!");
  
  
}


void loop() {
  unsigned long now = millis();

  server.handleClient();
  ws2812fx.service();

  if(now - last_wifi_check_time > WIFI_TIMEOUT) {
    Serial.print("Checking WiFi... ");
    if(WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi connection lost. Reconnecting...");
      wifi_setup();
    } else {
      Serial.println("OK");
    }
    last_wifi_check_time = now;
  }

  if(auto_cycle && (now - auto_last_change > 10000)) { // cycle effect mode every 10 seconds
    uint8_t next_mode = (ws2812fx.getMode() + 1) % ws2812fx.getModeCount();
    if(sizeof(myModes) > 0) { // if custom list of modes exists
      for(uint8_t i=0; i < sizeof(myModes); i++) {
        if(myModes[i] == ws2812fx.getMode()) {
          next_mode = ((i + 1) < sizeof(myModes)) ? myModes[i + 1] : myModes[0];
          break;
        }
      }
    }
    ws2812fx.setMode(next_mode);
    Serial.print("mode is "); Serial.println(ws2812fx.getModeName(ws2812fx.getMode()));
    auto_last_change = now;
  }
}



/*
 * Connect to WiFi. If no connection is made within WIFI_TIMEOUT, ESP gets resettet.
 */
void wifi_setup() {

  Serial.println();
  //Serial.print("Connecting to ");
  //Serial.println(WIFI_SSID);
  
  #ifdef STATIC_IP  
    wifiManager.setSTAStaticIPConfig(ip, gateway, subnet);
  #endif
  
  // wifiManager.resetSettings() ;
  if (!wifiManager.autoConnect("LED_CONFIG")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.restart();
    delay(5000);
  }

/*
  unsigned long connect_start = millis();
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    if(millis() - connect_start > WIFI_TIMEOUT) {
      Serial.println();
      Serial.print("Tried ");
      Serial.print(WIFI_TIMEOUT);
      Serial.print("ms. Resetting ESP now.");
      ESP.reset();
    }
  }
*/
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}


/*
 * Build <li> string for all modes.
 */
void modes_setup() {
  modes = "";
  uint8_t num_modes = sizeof(myModes) > 0 ? sizeof(myModes) : ws2812fx.getModeCount();
  for(uint8_t i=0; i < num_modes; i++) {
    uint8_t m = sizeof(myModes) > 0 ? myModes[i] : i;
    modes += "<li><a href='#'>";
    modes += ws2812fx.getModeName(m);
    modes += "</a></li>";
  }
}

/* #####################################################
#  Webserver Functions
##################################################### */

void srv_handle_not_found() {
  server.send(404, "text/plain", "File Not Found");
}

void srv_handle_index_html() {
  server.send_P(200,"text/html", index_html);
}


void srv_handle_main_js() {
  server.send_P(200,"application/javascript", main_js);
}

void srv_handle_modes() {
  server.send(200,"text/plain", modes);
}

void srv_handle_set() {
  for (uint8_t i=0; i < server.args(); i++){
    if(server.argName(i) == "c") {
      uint32_t tmp = (uint32_t) strtol(server.arg(i).c_str(), NULL, 10);
      if(tmp >= 0x000000 && tmp <= 0xFFFFFF) {
        ws2812fx.setColor(tmp);
      }
    }

    if(server.argName(i) == "m") {
      uint8_t tmp = (uint8_t) strtol(server.arg(i).c_str(), NULL, 10);
      uint8_t new_mode = sizeof(myModes) > 0 ? myModes[tmp % sizeof(myModes)] : tmp % ws2812fx.getModeCount();
      ws2812fx.setMode(new_mode);
      Serial.print("mode is "); Serial.println(ws2812fx.getModeName(ws2812fx.getMode()));
    }

    if(server.argName(i) == "b") {
      if(server.arg(i)[0] == '-') {
        ws2812fx.setBrightness(ws2812fx.getBrightness() * 0.8);
      } else if(server.arg(i)[0] == ' ') {
        ws2812fx.setBrightness(min(max(ws2812fx.getBrightness(), 5) * 1.2, 255));
      } else { // set brightness directly
        uint8_t tmp = (uint8_t) strtol(server.arg(i).c_str(), NULL, 10);
        ws2812fx.setBrightness(tmp);
      }
      Serial.print("brightness is "); Serial.println(ws2812fx.getBrightness());
    }

    if(server.argName(i) == "s") {
      if(server.arg(i)[0] == '-') {
        ws2812fx.setSpeed(max(ws2812fx.getSpeed(), 5) * 1.2);
      } else if(server.arg(i)[0] == ' ') {
        ws2812fx.setSpeed(ws2812fx.getSpeed() * 0.8);
      } else {
        uint16_t tmp = (uint16_t) strtol(server.arg(i).c_str(), NULL, 10);
        ws2812fx.setSpeed(tmp);
      }
      Serial.print("speed is "); Serial.println(ws2812fx.getSpeed());
    }

    if(server.argName(i) == "a") {
      if(server.arg(i)[0] == '-') {
        auto_cycle = false;
      } else {
        auto_cycle = true;
        auto_last_change = 0;
      }
    }
  }
  server.send(200, "text/plain", "OK");
}
