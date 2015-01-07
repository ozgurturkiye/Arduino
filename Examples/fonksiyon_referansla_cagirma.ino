// Arduino Fonksiyon referansla çağırma kullanımı örneği 

int a = 1;
int b = 2;
int c = 3;

int referanslaCagirmaFonksiyonu(int x, int y, int &z) {
  x = 101;
  y = 102;
  z = 103;
}

void setup() {
  // Seri portu 9600 bps hızına ayarla
  Serial.begin(9600);
}

void loop() {
  Serial.println("Referansla Cagirma Sonucu Degerler:");
  referanslaCagirmaFonksiyonu(a, b, c);
  Serial.println(a);
  Serial.println(b);
  Serial.println(c);
  while(1);
}
