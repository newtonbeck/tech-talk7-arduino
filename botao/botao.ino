void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  int botao = digitalRead(2);
  Serial.println(botao);
}
