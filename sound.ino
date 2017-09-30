void readMSGEQ7() {  //data is stored in variable sound[]
  int left[5];
  for (int i = 0; i < 5; i++) {
    sound[i] = 0;
  }

  for (int repeat = 0; repeat < 30 ; repeat++) {
    digitalWrite(res, HIGH);
    delayMicroseconds(30);
    digitalWrite(res, LOW);
    delayMicroseconds(30);
    for (int band = 0; band < 5; band++)
    {
      digitalWrite(strobe, LOW); // strobe pin on the shield - kicks the IC up to the next band
      delayMicroseconds(30); //
      left[band] = analogRead(0) - soundFilter[band]; // store left band reading
      if (left[band] < 0 ) {
        left[band] = 0;
      }
//            if(sound[band] < left[band]){
//              sound[band] = left[band];
//            }
      sound[band] += left[band];

      digitalWrite(strobe, HIGH);
      delayMicroseconds(30);
    }
  }
  for (int i = 0; i < 5; i++) {
    sound[i] = (int)sound[i] / 30;
    sound[i] = (int)(sound[i] * (double)((sensitivity/500.0)+1));
    sound[i] = constrain(sound[i],0,1024);
    sound[i] = correctDrop(sound[i],lastSound[i], i);
    sound[i] = map(sound[i],0,1024,0,24);

   
    
  }
}
int correctDrop(int now,int last, int index){
  
//    if(now > last){ TODO
//      return now;
//       lastSound[index] = sound[index];
//    }else{
//      return last - drop;
//    }
return now;
 
}
void printMSGEQ7() {
  for (int band = 0; band < 5; band++)
  {
    Serial.print(sound[band]);
    Serial.print(" ");
  }
  Serial.println();
}
