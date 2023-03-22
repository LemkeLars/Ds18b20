#ifndef Ds18b20_h
#define Ds18b20_h
#include "mbed.h"

#define SKIP_ROM 0xCC
#define CONVERT_T 0x44
#define READ_SCRATCHPAD 0xBE

class Ds18b20
{
    public:
        Ds18b20(PinName pin);
        void start();
        float readTemperature();
    private:
        DigitalInOut pin;
        int reset();
        void writeBit(int bit);
        int readBit();
        void writeByte(int byte);
        int readByte();

};
#endif