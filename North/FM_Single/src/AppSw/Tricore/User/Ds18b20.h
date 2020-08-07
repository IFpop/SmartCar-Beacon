/*
 * Ds18b20.h
 *
 *  Created on: 2020Äê8ÔÂ2ÈÕ
 *      Author: pengs
 */

#ifndef SRC_APPSW_TRICORE_USER_DS18B20_H_
#define SRC_APPSW_TRICORE_USER_DS18B20_H_

#include "stdint.h"

#define DSPORT P13_0

#define DQ_INIT   PIN_InitConfig(DSPORT, PIN_MODE_OUTPUT, 0)
#define DQ_H      PIN_Write(DSPORT, 1)
#define DQ_L      PIN_Write(DSPORT, 0)

#define DQ_READ   PIN_Read(DSPORT)


void datapros(int);
unsigned char Ds18b20Init();
void Ds18b20WriteByte(unsigned char);
unsigned char Ds18b20ReadByte(void);
void  Ds18b20ChangTemp(void);
void  Ds18b20ReadTempCom(void);
int Ds18b20ReadTemp(void);


#endif /* SRC_APPSW_TRICORE_USER_DS18B20_H_ */
