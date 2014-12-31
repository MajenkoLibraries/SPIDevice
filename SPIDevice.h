#ifndef _SPIDEVICE_H
#define _SPIDEVICE_H

#define OPT_BOARD_INTERNAL

#if (ARDUINO >= 100) 
# include <Arduino.h>
#else
# include <WProgram.h>
#endif

#include <p32_defs.h>

#define SPI_CON_FRMEN       (1<<31)
#define SPI_CON_FRMSYNC     (1<<30)
#define SPI_CON_FRMPOL      (1<<29)
#define SPI_CON_MSSEN       (1<<28)
#define SPI_CON_FRMSYPW     (1<<27)
#define SPI_CON_FRMCNT(X)   (((X) & 0b111) << 24)
#define SPI_CON_MCLKSEL     (1<<23)
#define SPI_CON_SPIFE       (1<<17)
#define SPI_CON_ENHBUF      (1<<16)
#define SPI_CON_ON          (1<<15)
#define SPI_CON_SIDL        (1<<13)
#define SPI_CON_DISSDO      (1<<12)
#define SPI_CON_MODE8       (0b00 << 10)
#define SPI_CON_MODE16      (0b01 << 10)
#define SPI_CON_MODE32      (0b10 << 10)
#define SPI_CON_SMP         (1<<9)
#define SPI_CON_CKE         (1<<8)
#define SPI_CON_SSEN        (1<<7)
#define SPI_CON_CKP         (1<<6)
#define SPI_CON_MSTEN       (1<<5)
#define SPI_CON_DISSDI      (1<<4)
#define SPI_CON_STXISEL(X)  (((X) & 0b11) << 2)
#define SPI_CON_SRXISEL(X)  (((X) & 0b11))

#define SPI_MODE0   SPI_CON_CKE
#define SPI_MODE1   0
#define SPI_MODE2   (SPI_CON_CKP | SPI_CON_CKE)
#define SPI_MODE3   SPI_CON_CKP


class SPIDevice;

class SPIBus : public Stream {
    private:
        volatile p32_spi *_dev;
        uint32_t _opens;
        SPIDevice *_active;
    
    public:
        SPIBus(uint32_t);
        void write(uint8_t);
        uint8_t read();
        uint8_t peek();
        void flush();
        void begin();
        void end();
        void setMode(uint32_t);
        uint32_t transfer(uint32_t);
};

class SPIDevice : public Stream {
    private:
        SPIBus *_bus;
        uint32_t _mode;

    public:
        SPIDevice(uint8_t channel, uint8_t cs, uint8_t mode = 0, uint32_t speed = 10000000UL);
        void begin();
        void end();
        void setMode(uint8_t mode);
        void setSpeed(uint32_t speed);
        void setBits(uint8_t bits);
        void write(uint8_t);
        uint8_t read();
        uint8_t peek();
        uint8_t flush();
        uint32_t transfer(uint32_t data);
        void open();
        void close();
};

#endif
