void setLedStrip() {
  clearLedStrip();
  if (checkValues()) {  //checkValues()
    for (int c = 0; c < 5; c++) {
      for (int v = 0; v <= sound[c]; v++) {
        strip.setPixelColor((24 * c) + v, colorMatrix[v][c][0], colorMatrix[v][c][1], colorMatrix[v][c][2]);
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














