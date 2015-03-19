/*
 * MCP4725 driver for wiringPi:
 *    https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 * March 2015 John Whittington http://www.jbrengineering.co.uk @j_whittington
 *
*==============================================================*/

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "mcp4725.h"

/* MCP4725 analogWrite function:
 *    value is 12bit data to be writen.
 *    pin is a mask for write type:
 *    pinBase + 0 - DAC standard
 *    pinBase + 1 - EEROM write DAC
*===================================*/

static void myAnalogWrite(struct wiringPiNodeStruct *node, int pin, int value) {
  // 2 byte array to hold 12bit data chunks
  int data[2];
  // pin is a mask for DAC set to EEROM
  int persist = pin - node->pinBase;

  // limit check value
  value = (value > 4095) ? 4095 : value;

  // MCP4725 expects a 12bit data stream in two bytes (2nd & 3rd of transmission)
  data[0] = (value >> 8) & 0xFF; // [0 0 0 0 D12 D11 D10 D9 D8] (first bits are modes for our use 0 is fine)
  data[1] = value; // [D7 D6 D5 D4 D3 D2 D1 D0]

  // 1st byte is the register
  if (persist) {
    wiringPiI2CWrite(node->fd, WRITEDACEEPROM);
  } else {
    wiringPiI2CWrite(node->fd, WRITEDAC);
  }
  
  // send our data using the register parameter as our first data byte
  // this ensures the data stream is as the MCP4725 expects
  wiringPiI2CWriteReg8(node->fd, data[0], data[1]);
}

/* MCP4725 DAC setup:
 *    create MC4725 device.
 *    id is the address of the chip (0x62 default)
*===============================================*/

int mcp4725Setup(const int pinBase, int id) {
  struct wiringPiNodeStruct *node;

  node = wiringPiNewNode(pinBase,2);

  node->fd = wiringPiI2CSetup(id);
  node->analogWrite = myAnalogWrite;

  if (node->fd < 0) {
    return -1;
  } else {
    return 0;
  }
}
