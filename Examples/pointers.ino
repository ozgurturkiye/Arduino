// Pointers example

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  int *p;       // declare a pointer to an int data type
  int i = 5;
  int result = 0;
  p = &i;       // now 'p' contains the address of 'i'
  result = *p;  // 'result' gets the value at the address pointed by 'p'
                // i.e., it gets the value of 'i' which is 5

  Serial.print("pointer location address(lvalue): ");
  Serial.println((long) &p);
  Serial.print("pointer register address(rvalue): ");
  Serial.println((long) p);
  Serial.print("pointer pointed address value(i rvalue): ");
  Serial.println(*p);
  Serial.println("-----------------------");
  
  int myVar = 10;
  
  Serial.print("myVar's lvalue: ");
  Serial.println((long) &myVar, DEC);
  Serial.print("myVar's rvalue: ");
  Serial.println(myVar, DEC);
  Serial.println();
  
  int *myPointer;
  myPointer = &myVar;
  
  Serial.print("myPointer's lvalue: ");
  Serial.println((long) &myPointer, DEC);
  Serial.print("myPointer's rvalue: ");
  Serial.println((long) myPointer, DEC);
  Serial.println();

  *myPointer = 5;  //THIS IS OUR DEREFRENCING ADDITION.
  Serial.println("-----------------------");
  Serial.println("Updating *myPointer = 5");
  Serial.println();

  Serial.print("myPointer's lvalue: ");
  Serial.println((long) &myPointer, DEC);
  Serial.print("myPointer's rvalue: ");
  Serial.println((long) myPointer, DEC);
  Serial.println();

  Serial.print("myVar's lvalue: ");
  Serial.println((long) &myVar, DEC);
  Serial.print("myVar's rvalue: ");
  Serial.println(myVar, DEC);
  Serial.println();
}

void loop() {
}
