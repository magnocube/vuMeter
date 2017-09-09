void handleEvent(String data, String Command) {
  if (Command == "powerOnOff") {
    toggleDevice(data);
    lastCommandLed = Command + ":" + data;
  } else if (Command == "color1") {
    setColor1(data);
    lastCommandColor1 = Command + ":" + data;
  } else if (Command == "color2") {
    setColor2(data);
    lastCommandColor2 = Command + ":" + data;
  } else if (Command == "color3") {
    setColor3(data);
    lastCommandColor3 = Command + ":" + data;
  } else if (Command  == "text") {
    handleText(data);
    lastCommandText = Command + ":" + data;
  } else if (Command  == "sensitivity") {
    setSensitivity(data);
    lastCommandSensitivity = Command + ":" + data;
  } else if (Command  == "ledMode") {
    setLedMode(data);
    lastCommandLedMode = Command + ":" + data;
  } else if (Command  == "backMode") {
    setBackMode(data);
    lastCommandLedMode = Command + ":" + data;
  }
}

void toggleDevice(String data) {
  if (data == "ledon") {
    oled("device turned on");
    ledOnOff = true;
  }
  else if (data == "ledoff") {
    oled("device turned off");
    ledOnOff = false;
  }
}
void setSensitivity(String data){
  sensitivity = data.toInt();
}
void setLedMode(String data){
  ledMode = data;
  updateColors(); 
  
  oled("mode changed to: " +ledMode);
} 
void setBackMode(String data){
  backMode = data;
  oled("back changed to: " +backMode);
}
void setColor1(String data) {
  String redValue = data.substring(data.indexOf("R") + 1, data.indexOf("G"));
  String greenValue = data.substring(data.indexOf("G") + 1, data.indexOf("B"));
  String blueValue = data.substring(data.indexOf("B") + 1, data.length());
  oled(redValue + " "  + greenValue +  " " + blueValue);
  color1[0] = redValue.toInt();
  color1[1] = greenValue.toInt();
  color1[2] = blueValue.toInt();
  updateColors(); 

}
void setColor2(String data) {
  String redValue = data.substring(data.indexOf("R") + 1, data.indexOf("G"));
  String greenValue = data.substring(data.indexOf("G") + 1, data.indexOf("B"));
  String blueValue = data.substring(data.indexOf("B") + 1, data.length());
  oled(redValue + " "  + greenValue +  " " + blueValue);
  color2[0] = redValue.toInt();
  color2[1] = greenValue.toInt();
  color2[2] = blueValue.toInt();
  updateColors(); 
 
}
void setColor3(String data) {
  String redValue = data.substring(data.indexOf("R") + 1, data.indexOf("G"));
  String greenValue = data.substring(data.indexOf("G") + 1, data.indexOf("B"));
  String blueValue = data.substring(data.indexOf("B") + 1, data.length());
  oled(redValue + " "  + greenValue +  " " + blueValue);
  color3[0] = redValue.toInt();
  color3[1] = greenValue.toInt();
  color3[2] = blueValue.toInt();

}
void handleText(String data) {
  oled(data);
}


