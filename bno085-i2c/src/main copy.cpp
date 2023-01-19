// #include <Arduino.h>

// #include <Wire.h>
// #include <ESPAsyncWebServer.h>
// #include <ESP8266WiFiMulti.h>
// #include <ESP8266mDNS.h>
// #include "SparkFun_BNO080_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_BNO080
// #include <credentials.h>
// BNO080 myIMU;

// ESP8266WiFiMulti wifiMulti;
// bool rainbow = false; // The rainbow effect is turned off on startup

// AsyncWebServer server(80);
// AsyncWebSocket ws("/ws");

// const char *ssid = APP_SSID;     // The name of the Wi-Fi network that will be created
// const char *password = APP_PSWD; // The password required to connect to it, leave blank for an open network
// const char *mdnsName = "esp8266";

// void startWiFi()
// {                              // Start a Wi-Fi access point, and try to connect to some given access points. Then wait for either an AP or STA connection
//   WiFi.softAP(ssid, password); // Start the access point
//   Serial.print("Access Point \"");
//   Serial.print(ssid);
//   Serial.println("\" started\r\n");

//   wifiMulti.addAP(BEAMLOGIC_SSID, BEAMLOGIC_PSWD); // add Wi-Fi networks you want to connect to
//   wifiMulti.addAP(PROIECT_SCR_SSID, PROIECT_SCR_PSWD);
//   // wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

//   Serial.println("Connecting");
//   while (wifiMulti.run() != WL_CONNECTED && WiFi.softAPgetStationNum() < 1)
//   { // Wait for the Wi-Fi to connect
//     delay(250);
//     Serial.print('.');
//   }
//   Serial.println("\r\n");
//   if (WiFi.softAPgetStationNum() == 0)
//   { // If the ESP is connected to an AP
//     Serial.print("Connected to ");
//     Serial.println(WiFi.SSID()); // Tell us what network we're connected to
//     Serial.print("IP address:\t");
//     Serial.print(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer
//   }
//   else
//   { // If a station is connected to the ESP SoftAP
//     Serial.print("Station connected to ESP8266 AP");
//   }
//   Serial.println("\r\n");
// }

// void startMDNS()
// {                       // Start the mDNS responder
//   MDNS.begin(mdnsName); // start the multicast domain name server
//   Serial.print("mDNS responder started: http://");
//   Serial.print(mdnsName);
//   Serial.println(".local");
// }

// void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
// {
//   AwsFrameInfo *info = (AwsFrameInfo *)arg;
//   if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
//   {
//     data[len] = 0;
//     // if (strcmp((char *)data, "toggle") == 0)
//     // {
//     //   ledState = !ledState;
//     //   notifyClients();
//     // }
//   }
// }

// void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
//              void *arg, uint8_t *data, size_t len)
// {
//   switch (type)
//   {
//   case WS_EVT_CONNECT:
//     Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
//     ws.text(client->id(), "{\"IP\":\"" + WiFi.localIP().toString() + "\"}");
//     break;
//   case WS_EVT_DISCONNECT:
//     Serial.printf("WebSocket client #%u disconnected\n", client->id());
//     break;
//   case WS_EVT_DATA:
//     handleWebSocketMessage(arg, data, len);
//     break;
//   case WS_EVT_PONG:
//   case WS_EVT_ERROR:
//     break;
//   }
// }

// void initWebSocket()
// {
//   ws.onEvent(onEvent);
//   server.addHandler(&ws);
//   server.begin();
// }

// struct ImuData
// {
//   float quatI = 0;
//   float quatJ = 0;
//   float quatK = 0;
//   float quatReal = 0;
//   float quatRadianAccuracy = 0;
//   float roll = 0;
//   float pitch = 0;
//   float yaw = 0;
//   unsigned long date = 0;
//   long refreshRate = 0;
// } imuData;

// String getQuatJsonStringFromData(ImuData imuData)
// {
//   char result[256];
//   char *formatedMessage = "{\"imuData\":{\"quatI\":%f, \"quatJ\":%f, \"quatK\":%f, \"quatReal\":%f, \"quatRadianAccuracy\":%f}}";
//   snprintf(result, sizeof(result), formatedMessage,
//            imuData.quatI, imuData.quatJ, imuData.quatK, imuData.quatReal, imuData.quatRadianAccuracy);

//   return result;
// }

// String getPRYJsonStringFromData(ImuData imuData)
// {
//   char result[256];
//   char *formatedMessage = "{\"imuData\":{\"roll\":%f, \"pitch\":%f, \"yaw\":%f, \"date\":%lu, \"refreshRate\":%d}}";
//   snprintf(result, sizeof(result), formatedMessage,
//            imuData.roll, imuData.pitch, imuData.yaw, imuData.date, imuData.refreshRate);
//   return result;
// }

// void notifyClients()
// {
//   ws.textAll(getPRYJsonStringFromData(imuData));
// }

// void setup()
// {
//   delay(1000); //  Wait for BNO to boot
//   Serial.begin(115200);
//   Serial.println();

//   /************************************************/
//   startWiFi();
//   // startMDNS();
//   initWebSocket();
//   /************************************************/

//   Serial.println("BNO080 Read Example");

//   Wire.begin();

//   // Are you using a ESP? Check this issue for more information: https://github.com/sparkfun/SparkFun_BNO080_Arduino_Library/issues/16
//   //  //=================================
//   delay(100); //  Wait for BNO to boot
//   // Start i2c and BNO080
//   Wire.flush(); // Reset I2C
//   myIMU.begin(0x4B, Wire, D0);
//   Wire.begin(4, 5);
//   Wire.setClockStretchLimit(4000);
//   //  //=================================

//   Wire.setClock(400000); // Increase I2C data rate to 400kHz
//   myIMU.calibrateAll();
//   myIMU.enableRotationVector(50); // Send data update every 50ms
//   Serial.println(F("Rotation vector enabled"));
//   Serial.println(F("Output in form i, j, k, real, accuracy"));
// }

// void loop()
// {

//   // Look for reports from the IMU
//   if (myIMU.dataAvailable() == true)
//   {

//     imuData.quatI = myIMU.getQuatI();
//     imuData.quatJ = myIMU.getQuatJ();
//     imuData.quatK = myIMU.getQuatK();
//     imuData.quatReal = myIMU.getQuatReal();
//     imuData.quatRadianAccuracy = myIMU.getQuatRadianAccuracy();
//     imuData.roll = myIMU.getRoll();
//     imuData.pitch = myIMU.getPitch();
//     imuData.yaw = myIMU.getYaw();
//     unsigned long now = millis();
//     imuData.refreshRate = now - imuData.date;
//     imuData.date = millis();

//     notifyClients();

//     // float quatI = myIMU.getQuatI();
//     // float quatJ = myIMU.getQuatJ();
//     // float quatK = myIMU.getQuatK();
//     // float quatReal = myIMU.getQuatReal();
//     // float quatRadianAccuracy = myIMU.getQuatRadianAccuracy();

//     // Serial.printf("Roll = %f, Pitch = %f, Yaw = %f.\n", myIMU.getRoll(), myIMU.getPitch(), myIMU.getYaw());

//     // Serial.print(quatI, 2);
//     // Serial.print(F(","));
//     // Serial.print(quatJ, 2);
//     // Serial.print(F(","));
//     // Serial.print(quatK, 2);
//     // Serial.print(F(","));
//     // Serial.print(quatReal, 2);
//     // Serial.print(F(","));
//     // Serial.print(quatRadianAccuracy, 2);
//     // Serial.print(F(","));
//     // Serial.println();
//   }
// }