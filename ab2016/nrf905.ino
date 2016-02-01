    // Library import
    #include <SPI.h>
     
    // Pin definitions
    #define TX_EN 2 // Transmitter mode
    #define TRX_CE 3 // Transmitter or receiver mode(not standby, sleep etc.)
    #define DR 4 // Data ready
    #define CSN 5 // SPI chip select(active low)
    #define PWR 6 // In case of use power down mode (0 is power down, 1 is power up), spi stays open during all of these.
    #define CD 6
     
    // Operation modes can be found at Table 11 on Product Specification
     
    // Data Packet => Preamble | Address | Payload | CRC
     
    /*
       Rx address is set here, 4 byte format is used.
       Example address is: 0xCC 0xCC 0xCC 0xCC
    */
    #define RX_ADDR1 161
    #define RX_ADDR2 213
    #define RX_ADDR3 148
    #define RX_ADDR4 181
     
     
    // Maximum output power(10dbm)
    #define PA_PWR 0b00001100
    // Frequency range selection
    #define HFREQ_PLL 0b00000010 // It will make frequency resolution from 100KHz to 200KHz
    #define CONF1 PA_PWR
     
     
    // Channel selection: Refer to Table 24 at Product Specification
    // Note that CONF1's 0. bit is also used for selecting channel ~900MHz
    #define CHANNEL_433_1 0x6B // 433.1 MHz
    #define FREQUENCY_CHANNEL CHANNEL_433_1
     
     
    // Tx and Rx addess widths set here
    #define TX_AFW_1 0b00010000
    #define TX_AFW_2 0b00100000
    #define TX_AFW_3 0b00110000
    #define TX_AFW_4 0b01000000
     
    #define RX_AFW_1 0b00000001
    #define RX_AFW_2 0b00000010
    #define RX_AFW_3 0b00000011
    #define RX_AFW_4 0b00000100
     
     
    // Make 4 byte addressing both rx and tx
    #define ADDRESS_WIDTH TX_AFW_4 | RX_AFW_4
     
     
    // Tranceiving 32 bytes every time(set it between 1 and 32)
    #define TX_PAYLOAD_WIDTH 32
    #define RX_PAYLOAD_WIDTH 32
     
     
    // Additional configuration
    // 8 bit or 16 bit CRC
    #define CRC_MODE_8  0b00000000
    #define CRC_MODE_16 0b10000000
    // CRC will be used or not
    #define CRC_EN_0    0b00000000
    #define CRC_EN_1    0b01000000
     
    // Crystal Frequency
    #define XOF_20 0b00100000
    #define XOF_16 0b00011000
    #define XOF_12 0b00010000
    #define XOF_8  0b00001000
    #define XOF_4  0b00000000
     
    #define UP_CLK_FREQ 0 // Output clock frequency and its configuration may put here.
     
    #define ADDITIONAL CRC_MODE_16 | CRC_EN_1 | XOF_16 | UP_CLK_FREQ
     
     
     
    // Default: 107,12,68,32,32,161,213,148,181,88
    unsigned const char configArray[] = {
      FREQUENCY_CHANNEL, CONF1, ADDRESS_WIDTH, RX_PAYLOAD_WIDTH, TX_PAYLOAD_WIDTH,
      RX_ADDR1, RX_ADDR2, RX_ADDR3, RX_ADDR4, 0x58
    };
     
     
    // Chip definitions
    #define W_CONFIG 0x00
    #define R_CONFIG 0x10
    #define W_TX_PAYLOAD 0x20
    #define R_TX_PAYLOAD 0x21
    #define W_TX_ADDRESS 0x22
    #define R_TX_ADDRESS 0x23
    #define R_RX_PAYLOAD 0x24
    #define CHANNEL_CONFIG 0x80 // Add other data to this
     
     
     
    // Test data
    unsigned char tx_data[32] = "Merhaba";
     
    unsigned char tx_address[4] = {161,213,148,181};
     
     
    void setup() {
     
      // SPI Configuration
      SPI.setBitOrder(MSBFIRST);
      SPI.setDataMode(SPI_MODE0);
      SPI.begin();
     
      // Serial port for debug
      Serial.begin(115200);
     
      // Input and output pin definitions
      pinMode(TX_EN, OUTPUT);
      pinMode(TRX_CE, OUTPUT);
      pinMode(CSN, OUTPUT);
     
     
      pinMode(DR, INPUT);
     
    }
     
    void loop() {
      Serial.println("Registers at startup: ");
      // Read config
      digitalWrite(CSN, LOW);
      SPI.transfer(R_CONFIG);
      for (int i = 0; i < 10; i++) {
        char x = SPI.transfer(NULL);
        Serial.print((unsigned char)x);
        Serial.print(",");
      }
      digitalWrite(CSN, HIGH);
      Serial.println();
     
     
      Serial.println("Okuma basliyor...");
     
      delay(5);
      // Write config
      digitalWrite(TRX_CE, LOW);
     
      digitalWrite(CSN, LOW);
      SPI.transfer(W_CONFIG);
      for (int i = 0; i < 10; i++) {
        SPI.transfer(configArray[i]);
      }
      digitalWrite(CSN, HIGH);
     
      //delayMicroseconds(10);
     
     
      // Read config
      digitalWrite(CSN, LOW);
      SPI.transfer(R_CONFIG);
      for (int i = 0; i < 10; i++) {
        char x = SPI.transfer(NULL);
        Serial.print((unsigned char)x);
        Serial.print(",");
      }
      digitalWrite(CSN, HIGH);
      Serial.println();
     
      Serial.print("Sending data...");
     
      // Send data to air
      digitalWrite(CSN, LOW);
      // TODO: SET TX ADDRESS
      SPI.transfer(W_TX_ADDRESS);
      for (int i = 0; i < 4; i++) {
        SPI.transfer(tx_address[i]);
      }  
      digitalWrite(CSN, HIGH);
      digitalWrite(CSN, LOW);
      // TODO: SET DATA THROUGH SPI
      SPI.transfer(W_TX_PAYLOAD);
      for (int i = 0; i < 32; i++) {
        SPI.transfer(tx_data[i]);
      }
      digitalWrite(CSN, HIGH);
     
      // Wait if a carrier signal detected on air
      while(digitalRead(CD));
      // Start transmission
      digitalWrite(TRX_CE, HIGH);
      // Enter TX mode
      digitalWrite(TX_EN, HIGH);
     
      // Wait until complete
      while (digitalRead(DR) == LOW);
     
      // Exit TX mode and go to RX mode
      digitalWrite(TX_EN, LOW);
      delayMicroseconds(550); // 550 us is the maximum transition time between tx and rx
     
     
      Serial.println("Data sent.");
     
     
      // Read tx data
      Serial.print("TX registers are:");
      digitalWrite(CSN, LOW);
      SPI.transfer(R_TX_PAYLOAD);
      for (int i = 0; i < 32; i++) {
        char x = SPI.transfer(NULL);
        Serial.print((unsigned char)x);
        Serial.print(",");
      }
      digitalWrite(CSN, HIGH);
      Serial.println();
      // Read address
      Serial.print("TX address is:");
      digitalWrite(CSN, LOW);
      SPI.transfer(R_TX_ADDRESS);
      for (int i = 0; i < 4; i++) {
        char x = SPI.transfer(NULL);
        Serial.print((unsigned char)x);
        Serial.print(",");
      }
      digitalWrite(CSN, HIGH);
      Serial.println();
     
      // Listen
      digitalWrite(TRX_CE, HIGH);
      digitalWrite(TX_EN, LOW);
      delay(2);
      Serial.println("listening...");
      while (digitalRead(DR) == LOW);
      Serial.println("data came!");
      digitalWrite(TRX_CE, LOW);
      digitalWrite(CSN, LOW);

      SPI.transfer(R_RX_PAYLOAD);
      for (int i = 0; i < 32; i++) {
        char x = SPI.transfer(NULL);
        Serial.write(x);
        Serial.print(",");
      }

      digitalWrite(CSN, HIGH);
     
     
      SPI.endTransaction();
    }
