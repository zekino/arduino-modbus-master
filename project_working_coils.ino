/*

  RS485_HalfDuplex.pde - example using ModbusMaster library to communicate
  with EPSolar LS2024B controller using a half-duplex RS485 transceiver.

  This example is tested against an EPSolar LS2024B solar charge controller.
  See here for protocol specs:
  http://www.solar-elektro.cz/data/dokumenty/1733_modbus_protocol.pdf

  Library:: ModbusMaster
  Author:: Marius Kintel <marius at kintel dot net>

  Copyright:: 2009-2016 Doc Walker

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

*/

#include <ModbusMaster.h>

/*!
  We're using a MAX485-compatible RS485 Transceiver.
  Rx/Tx is hooked up to the hardware serial port at 'Serial'.
  The Data Enable and Receiver Enable pins are hooked up as follows:
*/
#define MAX485_DE      3
#define MAX485_RE_NEG  2

// instantiate ModbusMaster object
ModbusMaster node;

void preTransmission()
{
  digitalWrite(MAX485_RE_NEG, 1);
  digitalWrite(MAX485_DE, 1);
}

void postTransmission()
{
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
}

void setup()
{
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  // Init in receive mode
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);

  // Modbus communication runs at 115200 baud
  Serial.begin(19200);
  Serial1.begin(19200);
  Serial.println("lel");
//Serial.begin(19200);
  // Modbus slave ID 1
  node.begin(1, Serial1);
  
  // Callbacks allow us to configure the RS485 transceiver correctly
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

bool state = true;

void loop()
{
  uint8_t result;
  uint8_t coils;

  coils = node.writeMultipleCoils(0,3); // <==== this, I need to enable output LEDs 1-4

  
  if (coils == node.ku8MBSuccess)
  {
    Serial.println("registers");
    Serial.print("R1: ");
    Serial.println(node.getResponseBuffer(0));
    Serial.print("R2: ");
    Serial.println(node.getResponseBuffer(1));
    Serial.print("R3: ");
    Serial.println(node.getResponseBuffer(2));
    Serial.print("R4: ");
    Serial.println(node.getResponseBuffer(3));
    Serial.print("R5: ");
    Serial.println(node.getResponseBuffer(4));
    Serial.print("R6: ");
    Serial.println(node.getResponseBuffer(5));
    Serial.print("R7: ");
    Serial.println(node.getResponseBuffer(6));
    Serial.print("R8: ");
    Serial.println(node.getResponseBuffer(7));
  }

  delay(1000);
}
