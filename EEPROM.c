#define SetBit(x,y) (x|=(1<<y)) 
#define ClrBit(x,y) (x&=~(1<<y))
#define ToggleBit(x,y) (x^=(1<<y)) 
#define TestBit(x,y) (x & (1<<y))


#define SCL_PORT 		PORTB
#define SCL_PINREAD 	PINB
#define SCL_DIRECTION 	DDRB
#define SCL_PIN  		0

#define SDA_PORT 		PORTB
#define SDA_PINREAD		PINB
#define SDA_DIRECTION 	DDRB
#define SDA_PIN  		1


#define SCL_OUTPUT  	SetBit(SCL_DIRECTION, SCL_PIN)
#define SCL_HIGH  		SetBit(SCL_PORT, SCL_PIN)
#define SCL_LOW    		ClrBit(SCL_PORT, SCL_PIN)

#define SDA_OUTPUT  	SetBit(SDA_DIRECTION, SDA_PIN)
#define SDA_INPUT  	    ClrBit(SDA_DIRECTION, SDA_PIN)
#define SDA_HIGH  		SetBit(SDA_PORT, SDA_PIN)
#define SDA_LOW    		ClrBit(SDA_PORT, SDA_PIN)
#define SDA_VAL    		TestBit(SDA_PINREAD, SDA_PIN)


uint8_t i2cread(void)
{

uint8_t i2cdata,i;
i2cdata = 0;

SCL_OUTPUT;
SDA_INPUT;

for(i=0;i<8;i++)
{
i2cdata = i2cdata <<1;

SCL_HIGH;
if(SDA_VAL != 0)
i2cdata |= 1;
_delay_us(10);
SCL_LOW;
_delay_us(10);

}

return(i2cdata);

}


void clock(void)
{
SCL_HIGH;
_delay_us(10);
SCL_LOW;
_delay_us(10);
}


void i2cwrite(uint8_t i2cdata)
{
uint8_t i;
SCL_OUTPUT;
SDA_OUTPUT;

for(i=0;i<8;i++)
{
if(i2cdata & 0x80)
SDA_HIGH;
else 
SDA_LOW;
clock();
i2cdata = i2cdata << 1;
}

}



void i2cstart(void)
{
SCL_OUTPUT;
SDA_OUTPUT;

SCL_HIGH;
_delay_us(10);
SDA_HIGH;
_delay_us(10);
SDA_LOW;
_delay_us(10);
SCL_LOW;
_delay_us(10);
}


void i2cstop(void)
{
SCL_OUTPUT;
SDA_OUTPUT;

SCL_HIGH;
_delay_us(10);
SDA_LOW;
_delay_us(10);
SDA_HIGH;
_delay_us(10);

SCL_LOW;
_delay_us(10);
}

void ack(void)
{
SCL_OUTPUT;
SDA_OUTPUT;

SDA_LOW;
_delay_us(10);
SCL_HIGH;
_delay_us(10);
SCL_LOW;
_delay_us(10);
}


void nack(void)
{
SCL_OUTPUT;
SDA_OUTPUT;

SDA_HIGH;
_delay_us(10);
SCL_HIGH;
_delay_us(10);
SCL_LOW;
_delay_us(10);
}

void eepromwriteadd(void)
{
i2cwrite(0xa0);
}

void eepromreadadd(void)
{
i2cwrite(0xa1);
}

void EEPROM_WRITE(uint8_t addr,uint8_t data)     
{
i2cstart();
eepromwriteadd();
ack();
i2cwrite(addr);
ack();
i2cwrite(data);
ack();
i2cstop();
_delay_ms(10);
}
      
        
uint8_t EEPROM_READ(uint8_t addr)
{
uint8_t dfg;
i2cstart();
eepromwriteadd();
ack();
i2cwrite(addr);
ack();
i2cstart();
eepromreadadd();
ack();
dfg = i2cread();
nack();
i2cstop();
_delay_ms(10);
return(dfg);
}

void rtcwriteadd(void)
{
i2cwrite(0xd0);
}

void rtcreadadd(void)
{
i2cwrite(0xd1);
}

void RTC_WRITE(uint8_t addr,uint8_t data)     
{
i2cstart();
rtcwriteadd();
ack();
i2cwrite(addr);
ack();
i2cwrite(data);
ack();
i2cstop();
_delay_ms(10);
}
      
        
uint8_t RTC_READ(uint8_t addr)
{
uint8_t dfg;
i2cstart();
rtcwriteadd();
ack();
i2cwrite(addr);
ack();
i2cstart();
rtcreadadd();
ack();
dfg = i2cread();
nack();
i2cstop();
_delay_ms(10);
return(dfg);
}
        
       
        
        
        
        
