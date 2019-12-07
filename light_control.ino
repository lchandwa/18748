void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  int switchValue1 = digitalRead(3);
  int switchValue2 = digitalRead(2);
  int switchValue3 = digitalRead(4);
  int sv1 = digitalRead(8);
  int sv2 = digitalRead(9);
  int sv3 = digitalRead(10);
  int pir = digitalRead(A0);
  int pir2 = digitalRead(A1);
  if (pir == 1) {
    if ((switchValue1 == 0) && (switchValue2 == 0) && (switchValue3 == 0)) {
      analogWrite(7, 255);
      analogWrite(6, 50);
      analogWrite(5, 0);
    }
    else if ((switchValue1 == 1) && (switchValue2 == 0) && (switchValue3 == 0)) {
      analogWrite(7, 255);
      analogWrite(6, 100);
      analogWrite(5, 50);
    }
    else if ((switchValue1 == 0) && (switchValue2 == 1) && (switchValue3 == 0)) {
      analogWrite(7, 255);
      analogWrite(6, 50);
      analogWrite(5, 0); 
    }
    else if ((switchValue1 == 0) && (switchValue2 == 0) && (switchValue3 == 1)) {
      analogWrite(7, 255);
      analogWrite(6, 0);
      analogWrite(5, 100);
    }
    else {
      analogWrite(7, 255);
      analogWrite(6, 50);
      analogWrite(5, 0);
    }
  }
  else {
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
  }
  if (pir2 == 1) {
    if ((sv1 == 0) && (sv2 == 0) && (sv3 == 0)) {
      analogWrite(11, 255);
      analogWrite(12, 128);
      analogWrite(13, 0);
    }
    else if ((sv1 == 1) && (sv2 == 0) && (sv3 == 0)) {
      analogWrite(11, 255);
      analogWrite(12, 128);
      analogWrite(13, 0);
    }
    else if ((sv1 == 0) && (sv2 == 1) && (sv3 == 0)) {
      analogWrite(11, 255);
      analogWrite(12, 0);
      analogWrite(13, 128); 
    }
    else if ((sv1 == 0) && (sv2 == 0) && (sv3 == 1)) {
      analogWrite(11, 255);
      analogWrite(12, 128);
      analogWrite(13, 255);
    }
    else {
      analogWrite(11, 255);
      analogWrite(12, 128);
      analogWrite(13, 0);
    }
  }
  else {
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
}
