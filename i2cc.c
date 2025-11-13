#include"types.h"
#include<LPC21XX.h>
#include"pin_connect_block.h"
#include"i2cc_defines.h"
void Init_i2c(void)
{
	cfgportpinFunc(0,2,SCL_PIN_0_2);
	cfgportpinFunc(0,3,SDA_PIN_0_3);
	I2SCLL=BITRATE;
	I2SCLH=BITRATE;
	I2CONSET=1<<I2EN_BIT;
}
void i2c_start(void)
{
	I2CONSET=1<<STA_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	I2CONCLR=1<<STAC_BIT;
}
void i2c_restart(void)
{
	I2CONSET=1<<STA_BIT;
	I2CONCLR=1<<SIC_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	I2CONCLR=1<<STAC_BIT;
}
void i2c_stop(void)
{
	I2CONSET=1<<STO_BIT;
	I2CONCLR=1<<SIC_BIT;
}
void i2c_write(u8 sDat)
{
	I2DAT=sDat;
	I2CONCLR=1<<SIC_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
}
u8 i2c_nack(void)
{
	I2CONCLR=1<<SIC_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	return I2DAT;
}
u8 i2c_mack(void)
{
	I2CONSET=1<<AA_BIT;
	I2CONCLR=1<<SIC_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	I2CONCLR=1<<AAC_BIT;
	return I2DAT;
}
