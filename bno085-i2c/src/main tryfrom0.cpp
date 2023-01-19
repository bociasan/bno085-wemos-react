// #include <Arduino.h>
// #include <SPI.h>
// #include <board_pinout.h>
// uint8_t buff[2];
// ;

// void setup()
// {
//   buff[0] = 0xF9; // Request the product ID and reset info
//   buff[1] = 0;    // Reserved

//   delay(500);
//   pinMode(_SPI_CS, OUTPUT);
//   pinMode(_PS0_WAKE, OUTPUT);
//   pinMode(_RST, OUTPUT);
//   pinMode(_INT, INPUT);

//   Serial.begin(115200); /* begin serial with 9600 baud */
//   Serial.println("Setup begin.");

//   digitalWrite(_SPI_CS, HIGH); // Deselect BNO080

//   // Configure the BNO080 for SPI communication
//   digitalWrite(_PS0_WAKE, HIGH); // Before boot up the PS0/WAK pin must be high to enter SPI mode
//   digitalWrite(_RST, LOW);       // Reset BNO080
//   delay(2);                      // Min length not specified in datasheet?
//   Serial.println("Wait for INT.");
//   delay(2000);

//   digitalWrite(_RST, HIGH); // Bring out of reset

//   while (!digitalRead(_INT))
//   {
//     delay(3);
//   }
//   Serial.println("Int detected!");
//   Serial.println("Begin SPI!");
//   SPI.begin(); /* begin SPI */
// }

// void loop()
// {
//   EVERY_MS(1000)
//   {
//     digitalWrite(_SPI_CS, LOW);
//     uint8_t channelNumber = 2;
//     uint8_t dataLength = 2;
//     uint8_t packetLength = dataLength + 4; // Add four bytes for the header
//     SPI.transfer(packetLength & 0xFF);     // Packet length LSB
//     SPI.transfer(packetLength >> 8);       // Packet length MSB
//     SPI.transfer(channelNumber);           // Channel number
//     SPI.transfer(0);                       // Send the sequence number, increments with each packet sent, different counter for each channel

//     for (int i = 0; i < sizeof buff; i++) /* transfer buff data per second */
//     {
//       SPI.transfer(buff[i]);
//     }
//     digitalWrite(_SPI_CS, HIGH);
//     delay(1000);
//     digitalWrite(_SPI_CS, LOW);
//     for (int i = 0; i < 10; i++) /* transfer buff data per second */
//     {
//       Serial.println(SPI.transfer(0xFF));
//     }
//     digitalWrite(_SPI_CS, HIGH);
//     delay(1000);
//   }
// }