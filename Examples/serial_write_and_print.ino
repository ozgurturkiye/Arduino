//Serial.write() and Serial.print() example for ASCII table
void setup() {
  Serial.begin(9600);
}

void loop() {
  //Serial.write(65); // send a byte with the value 65

  //int bytesSent = Serial.write("hello");  //send the string "hello" and return the length of the string.
  for (int x=0; x < 128; x++) {
      Serial.print(x);
      Serial.print(": ");
      Serial.print(x, BIN);
      Serial.print(": ");
      Serial.write(x);
      Serial.println();
      delay(50);
  }
}
