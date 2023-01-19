// #include <Wire.h>

// // #include <SoftwareSerial.h>
// // SoftwareSerial mySerial(A4, A5); // RX, TX
// // SoftwareSerial mySerial(12, 13); //?

// #include <SPI.h>

// #include "SparkFun_BNO080_Arduino_Library.h"
// #include <board_pinout.h>
// BNO080 myIMU;

// // Test jig pinouts
// //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// const byte PS0_WAKE = _PS0_WAKE;
// const byte PS1 = _PS1;
// const byte INT = _INT;
// const byte RST = _RST;

// const byte SPI_CS = _SPI_CS;
// const byte ADR_MOSI = _ADR_MOSI;
// const byte SPI_MISO = _SPI_MISO;
// const byte SPI_SCK = _SPI_SCK;

// // const byte TEST_BUTTON = A0;
// // const byte TEST_LED = A1;
// //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// boolean testI2CA = false;
// boolean testI2CB = false;
// boolean testSPI = false;
// boolean testUART = false;
// boolean testINT = false;

// boolean receivePacketSPI(void)
// {
//   // HINT line should be high before we begin
//   if (digitalRead(INT) == LOW)
//   {
//     Serial.println("Int should not be low - SPI failed");
//     testINT = false; // Fail
//     return (false);
//   }

//   digitalWrite(PS0_WAKE, LOW);

//   for (int x = 0; x < 100; x++)
//   {
//     // HINT line should go low indicating sensor is ready for data
//     if (digitalRead(INT) == LOW)
//     {
//       Serial.println("Int low 2 - Good! Int works");
//       testINT = true;
//       break;
//     }
//     delay(1);
//   }
//   digitalWrite(PS0_WAKE, HIGH);

//   digitalWrite(SPI_CS, LOW); // Select sensor

//   byte packetLSB;
//   byte packetMSB;
//   byte channelNumber;
//   byte sequenceNumber;

//   for (int x = 0; x < 1; x++)
//   {
//     // Get the first four bytes, aka the packet header
//     packetLSB = SPI.transfer(0x00);
//     packetMSB = SPI.transfer(0x00);
//     channelNumber = SPI.transfer(0x00);
//     sequenceNumber = SPI.transfer(0x00);

//     uint16_t dataLength = ((uint16_t)packetMSB << 8 | packetLSB);
//     // Serial.print("dataLength: ");
//     // Serial.println(dataLength);
//     Serial.print("packetLSB: 0x");
//     Serial.println(packetLSB, HEX);
//     Serial.print("packetMSB: 0x");
//     Serial.println(packetMSB, HEX);
//     Serial.print("channelNumber: 0x");
//     Serial.println(channelNumber, HEX);
//     Serial.print("sequenceNumber: 0x");
//     Serial.println(sequenceNumber, HEX);
//   }

//   // HINT should release and go back to high
//   if (digitalRead(INT) == LOW)
//   {
//     Serial.println("Int low 3 - Int should not be low here");
//     testINT = false; // INT may be jumpered low
//   }

//   digitalWrite(SPI_CS, HIGH); // Deselect sensor

//   uint16_t dataLength = ((uint16_t)packetMSB << 8 | packetLSB);
//   if (dataLength != 0xFFFF)
//     return (true); // We heard something

//   return (false); // We failed to hear anything
// }

// void setMode(byte mode)
// {
//   // Begin test with unit in reset
//   digitalWrite(RST, LOW);

//   delay(1);

//   if (mode == 0) // I2C
//   {
//     digitalWrite(PS0_WAKE, LOW);
//     digitalWrite(PS1, LOW);
//   }
//   else if (mode == 1) // UART-RVC
//   {
//     digitalWrite(PS0_WAKE, HIGH);
//     digitalWrite(PS1, LOW);
//   }
//   else if (mode == 2) // UART
//   {
//     digitalWrite(PS0_WAKE, LOW);
//     digitalWrite(PS1, HIGH);
//   }
//   else if (mode == 3) // SPI
//   {
//     digitalWrite(PS0_WAKE, HIGH);
//     digitalWrite(PS1, HIGH);
//   }

//   // Then release reset
//   digitalWrite(RST, HIGH);

//   delay(1);
// }

// void setup()
// {
//   // pinMode(PS0_WAKE, OUTPUT);
//   // pinMode(PS1, OUTPUT);
//   pinMode(INT, INPUT_PULLUP);
//   pinMode(RST, OUTPUT);

//   // pinMode(SPI_CS, INPUT); // High impedance for now
//   // pinMode(ADR_MOSI, OUTPUT);
//   // pinMode(SPI_MISO, INPUT); // High impedance for now
//   // pinMode(SPI_SCK, INPUT);  // High impedance for now

//   // pinMode(TEST_BUTTON, INPUT_PULLUP);
//   // pinMode(TEST_LED, OUTPUT);

//   Serial.begin(115200);
//   Serial.println();
//   Serial.println("BNO080 Tester");

//   // Test SPI
//   //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//   pinMode(SPI_CS, OUTPUT);
//   pinMode(ADR_MOSI, OUTPUT);
//   pinMode(SPI_MISO, INPUT);
//   pinMode(SPI_SCK, OUTPUT);

//   SPI.begin();

//   setMode(0b11); // Reset IC and set mode to SPI

//   // The BNO080 comes out of reset with 3 init packet announcements. Look for one.
//   if (receivePacketSPI() == true)
//   {
//     Serial.println("SPI good!");
//     testSPI = true;
//   }
// }

// void loop()
// {
// }

// // Pull WAKE pin low to indicate we are ready to talk to the sensor
// // Wait for sensor to pull INT pin low indicating it's ready for our talking
// void startTransfer()
// {
//   digitalWrite(PS0_WAKE, LOW); // Tell sensor we are ready to talk

//   int counter = 0;
//   while (digitalRead(INT) == HIGH) // Wait for sensor to confirm
//   {
//     delay(1);
//     if (counter++ > 500)
//     {
//       Serial.println(F("Sensor never pulled INT low"));
//       return;
//     }
//   }

//   digitalWrite(PS0_WAKE, HIGH); // Release WAKE

//   Serial.println(F("Sensor is ready to talk!"));
// }

// // Resets the IC and puts it into one of four modes: UART, UART-RVC, SPI, I2C
