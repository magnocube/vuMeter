void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
  //Serial.printf("webSocketEvent(%d, %d, ...)\r\n", num, type);
  switch(type) {
    case WStype_DISCONNECTED:
   
      Serial.printf("[%u] Disconnected!\r\n", num);
      oled("client disconnected");
     // webSocket.broadcastTXT("a client disconnected");
      
    
      handleEvent("ledoff","powerOnOff"); // command used to turn off the device.. if the device(void loop) is not turned off
      // when noone is on the webpage,, the device is not visible (idk how)
      break;
    
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\r\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        oled("new client");

        if(lastCommandLed != ""){
          webSocket.sendTXT(num, lastCommandLed);
        }
        if(lastCommandText != ""){
          webSocket.sendTXT(num, lastCommandText);
        }
        if(lastCommandColor1 != ""){
          webSocket.sendTXT(num, lastCommandColor1);
        }
        if(lastCommandColor2 != ""){
          webSocket.sendTXT(num, lastCommandColor2);
        } 
        if(lastCommandColor3 != ""){
          webSocket.sendTXT(num, lastCommandColor3);
        } 
        if(lastCommandSensitivity != ""){
          webSocket.sendTXT(num, lastCommandSensitivity);
        }
        if(lastCommandLedMode != ""){
          webSocket.sendTXT(num, lastCommandLedMode);
        }
        if(lastCommandBackMode != ""){
          webSocket.sendTXT(num, lastCommandBackMode);
        }
        if(lastCommandDrop != ""){
          webSocket.sendTXT(num, lastCommandDrop);
        }
          
            break;
  }
      
    case WStype_TEXT:
    {
      Serial.printf("[%u] said: %s\r\n", num, payload);
      String data = (char*)payload;
      String command = data.substring(0,data.indexOf(":"));
      data = data.substring(data.indexOf(":")+1,data.length());
      oled(data+" "+command);
      webSocket.broadcastTXT(command+":"+data);
      handleEvent(data,command);
     
       
      
      
      break;
    }
  
  }
}
