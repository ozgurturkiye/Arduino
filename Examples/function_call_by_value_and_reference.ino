// Example of Function Call by value and reference

int a = 1;
int b = 2;
int c = 3;

int call_by_value(int x, int y, int z) {
  x = 500;
  y = 600;
  z = 700;  
}

int call_by_reference(int x, int y, int &z) {
  x = 101;
  y = 102;
  z = 103;
}

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  Serial.println("Call by value:");
  call_by_value(a, b, c);
  Serial.println(a);
  Serial.println(b);
  Serial.println(c);
  Serial.println("Call by reference:");
  call_by_reference(a, b, c);
  Serial.println(a);
  Serial.println(b);
  Serial.println(c);
  while(1);
}
