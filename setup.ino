void setup()
{
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00
  WiFi.softAP("shittyConnection");
  
  
  
   pinMode(res, OUTPUT); // reset
  pinMode(strobe, OUTPUT); // strobe
  digitalWrite(res, LOW); // reset low
  digitalWrite(strobe, HIGH); //pin 5 is RESET on the shield

  clearColors();

  
  //WiFiMulti.config(ip,gateway,subnet);
//WiFiMulti.addAP(ssid, password);
  
  oled("verbinding maken");
  delay(500);
  
  
  Serial.println(WiFi.softAPIP());
   
  oled("77.172.10.200");

  server.on("/", handleRoot);
  server.on("/hackerman", handleHackerMan);
  server.onNotFound(handleNotFound);
  
  server.begin();
  
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  
  strip.begin();

  for(int i =0;i<5;i++){
    lastSound[i] = 0;  //set lastsound to zero
  }
 
}



void oled(String i) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(i);
  display.display();
}

