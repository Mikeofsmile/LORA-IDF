#include <SPI.h>
#include <LoRa.h>

#ifdef ARDUINO_SAMD_MKRWAN1300
#error "This example is not compatible with the Arduino MKR WAN 1300 board!"
#endif

/*
 * VCC    3V3
 * GND    GND
 * SCK    D13
 * MISO   D12
 * MOSI   D11
 * NSS    D10
 * RST    D9
 * DIO0   D2
 */

long frequency = 433E6;
//long frequency = 915E6;
 
void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Receiver Callback");

  if (!LoRa.begin(frequency)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // Uncomment the next line to disable the default AGC and set LNA gain, values between 1 - 6 are supported
  // LoRa.setGain(6);
  
  // register the receive callback
  LoRa.onReceive(onReceive);

  // put the radio into receive mode
  LoRa.receive();
}

void loop() {
  // do nothing
}

void onReceive(int packetSize) {
  // received a packet
  Serial.print("Received packet '");

  // read packet
  for (int i = 0; i < packetSize; i++) {
    Serial.print((char)LoRa.read());
  }

  // print RSSI of packet
  Serial.print("' with RSSI ");
  Serial.println(LoRa.packetRssi());
}
