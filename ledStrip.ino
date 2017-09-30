void setLedStrip() {
clearLedStrip();
  if (ledMode == "Single-Color" || ledMode == "Standard" || ledMode == "Dual-Color" || ledMode == "Rainbow") {
    if (checkValues()) {  //checkValues()
      for (int c = 0; c < 5; c++) {
        for (int v = 0; v <= sound[c]; v++) {
          strip.setPixelColor((24 * c) + v, colorMatrix[v][c][0], colorMatrix[v][c][1], colorMatrix[v][c][2]);
        }
      }
    }
  } else if (ledMode == "One-Line") {
    if (checkValues()) { 
       for (int c = 0; c < 5; c++) {
        
          strip.setPixelColor((24 * c) + sound[c], colorMatrix[sound[c]][c][0], colorMatrix[sound[c]][c][1], colorMatrix[sound[c]][c][2]);
        
      }
    }
  } else if(ledMode == "Epileptic-1" || ledMode == "Epileptic-2" || ledMode == "Epileptic-3"){
    updateColors();
     if (checkValues()) {  //checkValues()
      for (int c = 0; c < 5; c++) {
        for (int v = 0; v <= sound[c]; v++) {
          strip.setPixelColor((24 * c) + v, colorMatrix[v][c][0], colorMatrix[v][c][1], colorMatrix[v][c][2]);
        }
      }
    }
  }

}
void clearLedStrip() {
  for (int i = 0; i < 120; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
}
boolean checkValues() {
  if (tcounter < 5) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
      sum += sound[i];
    }
    if (sum < thrashold) {
      tcounter++;
    } else {
      tcounter = 0;
    }
    return true;
  } else {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
      sum += sound[i];
    }
    if (sum > thrashold+3) {
      gcounter ++;
    }
    if (gcounter > 3) {
      tcounter = 0;
      gcounter = 0;
    }
    return false;
  }

}














