#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x26, 16, 2); // Endereço I2C do LCD

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(A0, INPUT); // Pino do sensor de umidade

  // Configura os pinos dos LEDs como saída
  for (int pin = 8; pin <= 12; pin++) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  int valorBruto = analogRead(A0); // Leitura do sensor
  int umidadePercentual = map(valorBruto, 1023, 0, 0, 100);
  umidadePercentual = constrain(100 - umidadePercentual, 0, 100); // Inverte a lógica

  // Exibe no monitor serial
  Serial.print("Valor bruto: ");
  Serial.print(valorBruto);
  Serial.print(" | Umidade: ");
  Serial.print(umidadePercentual);
  Serial.println("%");

  // Exibe no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("UMIDADE DO SOLO");
  lcd.setCursor(0, 1);
  lcd.print("Nivel: ");
  lcd.print(umidadePercentual);
  lcd.print("%");

  
  for (int pin = 8; pin <= 12; pin++) {
    digitalWrite(pin, LOW);
  }
  
  if (umidadePercentual <= 25) {
    digitalWrite(8, HIGH); 
  } else if (umidadePercentual <= 50) {
    digitalWrite(9, HIGH); 
  } else if (umidadePercentual <= 75) {
    digitalWrite(10, HIGH); 
  } else if (umidadePercentual <= 90) {
    digitalWrite(11, HIGH); 
  } else {
    digitalWrite(12, HIGH);
  }

  delay(1000); // Aguarda 1 segundo
}
