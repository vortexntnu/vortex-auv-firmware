

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
}



void loop()
{
  float ESC1_VLM = analogRead(A4);
  float ESC2_VLM = analogRead(A3);

  ESC1_VLM = map(ESC1_VLM, 0, 1023, 0, 5);
  ESC2_VLM = map(ESC2_VLM, 0, 1023, 0, 5);

  float XAVI_VLM = analogRead(A2);
  float PDB_VLM = analogRead(A5);

  int F_STATE = digitalRead(7);

  XAVI_VLM = map(XAVI_VLM, 0, 1023, 0, 5);
  PDB_VLM = map(PDB_VLM, 0, 1023, 0, 5);

  if(F_STATE) {
    digitalWrite(8, LOW);
  } else {
    digitalWrite(8, HIGH);
  }

  if(XAVI_VLM >= 4.75) {
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }

  if(PDB_VLM >= 4.75) {
    digitalWrite(9, HIGH);
  } else {
    digitalWrite(9, LOW);
  }

  if(ESC1_VLM >= 2.4) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }

  if(ESC2_VLM >= 2.4) {
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(4, LOW);
  }
}