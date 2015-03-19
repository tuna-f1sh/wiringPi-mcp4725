/*
 * MCP4725 driver for wiringPi:
 *    https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 * March 2015 John Whittington http://www.jbrengineering.co.uk @j_whittington
 *
*==============================================================*/

#ifdef __cplusplus
extern "c" {
#endif

#define WRITEDAC 0x40
#define WRITEDACEEPROM 0x60
#define MCP4725 0x62

//void setVoltage(int fd, int voltage, int persist);
extern int mcp4725Setup(int pinBase, int id);

#ifdef __cplusplus
}
#endif
