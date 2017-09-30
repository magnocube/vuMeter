void clearColors() {
  for (int i = 0; i < 24; i++) {
    for (int i2 = 0; i2 < 5; i2++) {
      for (int i3 = 0; i3 < 3; i3++) {
        colorMatrix[i][i2][i3] = 0;
      }
    }
  }
}
void updateColors() {
  clearColors();
  if (ledMode == "Single-Color") {
    for (int i = 0; i < 24; i++) {
      for (int i2 = 0; i2 < 5; i2++) {
        for (int i3 = 0; i3 < 3; i3++) {
          colorMatrix[i][i2][i3] = color1[i3];
        }
      }
    }
  } else if (ledMode == "Standard") {
    for (int i = 0; i < 24; i++) {
      for (int i2 = 0; i2 < 5; i2++) {

        if (i < 14) {
          colorMatrix[i][i2][1] = 255; // green
        } else if (i < 18) {
          colorMatrix[i][i2][0] = 255;  // red
          colorMatrix[i][i2][1] = 56;  // green
        } else {
          colorMatrix[i][i2][0] = 255;  // red
        }

      }
    }

  } else if (ledMode == "Dual-Color") {
    for (int band = 0; band < 5; band++) {
      for (int colorIndex = 0; colorIndex < 3; colorIndex++) {
        for (int i = 0; i < 24; i++)
        {
          int difference = color2[colorIndex] - color1[colorIndex];
          colorMatrix[i][band][colorIndex] = color1[colorIndex] + (difference / 23.0) * i;
        }

      }

    }
  } else if (ledMode == "Rainbow") {
    for (int i = 0; i < 24; i++) {


      colorMatrix[i][0][0] = 255; // rood

      colorMatrix[i][1][0] = 255; // oranje
      colorMatrix[i][1][1] = 127; //

      colorMatrix[i][2][0] = 255; // geel
      colorMatrix[i][2][1] = 255; //

      colorMatrix[i][3][1] = 255; // groen

      colorMatrix[i][4][2] = 255; // blauw



    }

  } else if (ledMode == "One-Line") {
    for (int i = 0; i < 24; i++) {
      for (int i2 = 0; i2 < 5; i2++) {

        for (int i3 = 0; i3 < 3; i3++) {
          colorMatrix[i][i2][i3] = color1[i3];
        }

      }
    }

  } else if (ledMode == "Epileptic-1") {
    for (int i = 0; i < 24; i++) {
      for (int i2 = 0; i2 < 5; i2++) {
        for (int i3 = 0; i3 < 3; i3++) {
          int randomValue=random(0, 4);
          colorMatrix[i][i2][i3] = randomValue*randomValue*randomValue*randomValue;
        }
      }
    }
  }
  else if (ledMode == "Epileptic-2") {

    for (int i2 = 0; i2 < 5; i2++) {
      for (int i3 = 0; i3 < 3; i3++) {
        int randomValue=random(0, 4);
        for (int i = 0; i < 24; i++) {
          
          colorMatrix[i][i2][i3] = randomValue*randomValue*randomValue*randomValue;
          
        }
      }
    }
  }
  else if (ledMode == "Epileptic-3") {
  for (int i = 0; i < 24; i++) {
    
      for (int i3 = 0; i3 < 3; i3++) {
        int randomValue=random(0, 4);
        for (int i2 = 0; i2 < 5; i2++) {
          colorMatrix[i][i2][i3] = randomValue*randomValue*randomValue*randomValue;
        }
      }
    }
  }
}

