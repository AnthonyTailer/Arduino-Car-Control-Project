#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "ESP_TAILER";
const char* password = "";
const int GPIO2 = 2; //UP
const int GPIO0 = 0; //DOWN
const int GPIO3 = 3; //RIGHT
const int GPIO1 = 1; //LEFT

String site = "";

ESP8266WebServer server(80);

void geraSite() {
  site = "<html>\n";
  site += "<head><title> ESP8266 CarControl</title></head>\n";
  site += "<body>\n";
  site += "<h5>UP</h5><br>\n";
  site += "<center><a href=\"/up?state=on\"><button style=\"font-size: 34px;\">UP ON</button></a></center>\n";
  site += "<br><center><a href=\"/up?state=off\"><button style=\"font-size: 34px;\">UP OFF</button></a></center>";
  site += "<hr>\n";
  site += "<h5>DOWN</h5><br>\n";
  site += "<center><a href=\"/down?state=on\"><button style=\"font-size: 34px;\">DOWN ON</button></a></center>\n";
  site += "<br><center><a href=\"/down?state=off\"><button style=\"font-size: 34px;\">DOWN OFF</button></a></center>";
  site += "<hr>\n";
  site += "<h5>LEFT</h5><br>\n";
  site += "<center><a href=\"/left?state=on\"><button style=\"font-size: 34px;\">LEFT ON</button></a></center>\n";
  site += "<br><center><a href=\"/left?state=off\"><button style=\"font-size: 34px;\">LEFT OFF</button></a></center>";
  site += "<hr>\n";
  site += "<h5>RIGHT</h5><br>\n";
  site += "<center><a href=\"/right?state=on\"><button style=\"font-size: 34px;\">RIGHT ON</button></a></center>\n";
  site += "<br><center><a href=\"/right?state=off\"><button style=\"font-size: 34px;\">RIGHT OFF</button></a></center>";
  site += "<h5>STOP ALL</h5><br>\n";
  site += "<center><a href=\"/stop\"><button style=\"font-size: 34px;\">STOP ALL</button></a></center>\n";
  site += "</body>\n";
  site += "</html>";

  server.send(200, "text/html", site);

  site = "";
}

void stop_all(){
   digitalWrite(GPIO2, LOW);
   digitalWrite(GPIO0, LOW);
   digitalWrite(GPIO1, LOW);
   digitalWrite(GPIO3, LOW);
}

void setup() {
 Serial.begin(115200);
 delay(10);
 
 // preparar GPIO's para mandar suas saidas para o Arduino
 pinMode(GPIO2, OUTPUT);
 pinMode(GPIO0, OUTPUT);
 pinMode(GPIO1, OUTPUT);
 pinMode(GPIO3, OUTPUT);
 
 stop_all();
 
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);
 
 //ESP.restart();
 WiFi.mode(WIFI_AP);
 WiFi.softAP(ssid);
 IPAddress mvIP = WiFi.softAPIP();
 Serial.println(mvIP);
 server.on("/", geraSite);
 
 server.on("/up", []() { //Quando o direcional pra cima for clicado 
  String state = server.arg("state");
  if (state == "on"){
     digitalWrite(GPIO2, HIGH);
  }else if (state == "off"){
     stop_all();
  }
  geraSite();
});

server.on("/down", []() {
  String state = server.arg("state");
  if (state == "on"){
     digitalWrite(GPIO0, HIGH);
  }else if (state == "off"){
     stop_all();
  }
  geraSite();
});

server.on("/left", []() {
  String state = server.arg("state");
  if (state == "on"){
     digitalWrite(GPIO1, HIGH);
  }else if (state == "off"){
     stop_all();
  }
  geraSite();
});

server.on("/right", []() {
  String state = server.arg("state");
  if (state == "on"){
    digitalWrite(GPIO3, HIGH);
  }else if (state == "off"){
     stop_all();
  }
  geraSite();
});

server.on("/stop", []() {
  stop_all();
  geraSite();
});

 server.begin();
}

void loop() {
 server.handleClient();
}
