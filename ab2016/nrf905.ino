// Pin definitions

#define TX_EN 2 // Transmitter mode
#define TRX_CE 3 // Transmitter or receiver mode (not standby, sleep etc.)
#define CSN 5 // SPI chip clelect (active low)
#define PWR 6 // In case of use power made down mode (0 is power down, 1 is power up), spi starys open during all of these.
#define CD 6

  pinMode(TX_EN, OUTPUT);
  pinMode(TRX_CE, OUTPUT);
  pinMode(CSN, OUTPUT);
  pinMode(DR, INPUT);
