char my_char = 0; // for incoming serial data

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // reply only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    my_char = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(my_char);
    if (my_char == 65) {
      Serial.println(my_char, DEC);
      digitalWrite(LED_BUILTIN, HIGH);
    }
    
    if (my_char == 66) {
      Serial.println(my_char, DEC);
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}
