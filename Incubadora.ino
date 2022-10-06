
// importando las libreias:
#include <LiquidCrystal.h>
#include "DHT.h"
// inicializar la biblioteca asociando cualquier pin de interfaz LCD necesario
// con el número de pin arduino al que está conectado
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define DHTPIN A2   //a que pin estamos conectados
#define Ventilador 7
#define Bombillo 8
#define DHTTYPE DHT11   // DHT 22  (AM2302)

// Conecte el pin 1 (a la izquierda) del sensor a + 5V
// Conecte el pin 2 del sensor a DHTPIN
// Conecte el pin 4 (a la derecha) del sensor a TIERRA
// Conecte una resistencia de 1K desde el pin 2 (datos) al pin 1 (potencia) del sensor


DHT dht(DHTPIN, DHTTYPE);
void setup() {
  pinMode(Ventilador, OUTPUT);
  pinMode(Bombillo, OUTPUT);
  // Configura el número de columnas y filas de la LCD:
  lcd.begin(16, 2);
  // Imprime el mensaje al monitor serial.
  Serial.begin(9600);
  lcd.setCursor(1, 0);
  lcd.println("Iniciando      ");
  lcd.setCursor(0, 1);
  lcd.println("      incubadora");
  delay(2000);
  lcd.clear();
  dht.begin();
}

void loop() {
  
  float h = dht.readHumidity();
  // Factor de calibrado
  float t = dht.readTemperature() * 0.949382716;


  // Verifica si las devoluciones son válidas, si son NaN (no un número) algo salió mal
  if (isnan(t) || isnan(h)) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.println(" Fallo en la   ");
    lcd.setCursor(0, 1);
    lcd.println("    lectora.    ");
    delay(2000);

  } else {
    lcd.setCursor(0, 1);
    lcd.print("Humedad: ");
    lcd.print(h);

    Serial.print("Humedad: ");
    Serial.print(h);

    lcd.print(" %\t");
    lcd.setCursor(1, 0);
    lcd.print("Temp: ");
    lcd.println(t);

    Serial.print("Temp: ");
    Serial.println(t);
    lcd.println(" C  ");
    //manejo del ventilador (5 v)
    
    if (h >= 85 || t >=37.9)
    {
      digitalWrite(Ventilador, HIGH);
    } else
    {
      digitalWrite(Ventilador, LOW);
    }
    //Manejo del bombillo(25 w 120 v @60 Hz) mediante un relevador
    if (t <= 37.6)
    {
      digitalWrite(Bombillo, HIGH);
    } else
    {
      digitalWrite(Bombillo, LOW);
    }
    delay(2000);

  }
}
