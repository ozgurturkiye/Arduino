// Arduino fonksiyon kullanımı örneği

int a = 2;
int b = 3;
int c = 4;

int carpmaFonksiyonu(int x, int y) {
  return x * y;
}
int toplamaFonksiyonu(int x, int y) {
  return x + y;
}
int cikarmaFonksiyonu(int x, int y) {
  return x - y;
}
float ortalamaFonksiyonu(int x, int y, int z) {
  return (x + y + z) / 3.0;
}
void setup() {
  // Seri portu 9600 bps hızına ayarla
  Serial.begin(9600);
}

void loop() {
  Serial.print("Carpma Sonucu:");
  Serial.println(carpmaFonksiyonu(a, b));
  Serial.print("Toplama Sonucu:");
  Serial.println(toplamaFonksiyonu(a, b));
  Serial.print("Cikarma Sonucu:");
  Serial.println(cikarmaFonksiyonu(a, b));
  Serial.print("Ortalama Sonucu:");
  Serial.println(ortalamaFonksiyonu(a, b, c));
  while(1);
}
