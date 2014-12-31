#include <SPIDevice.h>

// Array to store the SPI bus devices - easy access by index.

SPIBus spiBusses[4] = {
#ifdef _DSPI0_BASE
    SPIBus(_DSPI0_BASE),
#else
    NULL,
#endif

#ifdef _DSPI1_BASE
    SPIBus(_DSPI2_BASE),
#else
    NULL,
#endif

#ifdef _DSPI2_BASE
    SPIBus(_DSPI2_BASE),
#else
    NULL,
#endif

#ifdef _DSPI3_BASE
    SPIBus(_DSPI3_BASE),
#else
    NULL,
#endif
};


SPIBus::SPIBus(uint32_t base) {
    _dev = (volatile p32_spi *)base;
    _active = NULL;
    _opens = 0;
}

void SPIBus::begin() {
    _opens++;
    if (_opens == 1) {
    }
}

void SPIBus::end() {
    if (_opens == 0) {
        return;
    }
    _opens--;
    if (_opens == 0) {
    }
}

void SPIBus::write(uint8_t data) {
    transfer(data);
}

uint8_t SPIBus::read() {
    return transfer(0xFF);
}

uint8_t SPIBus::peek() {
    return transfer(0xFF);
}

void SPIBus::flush() {
}

        void end();
        void setMode(uint32_t);
        uint32_t transfer(uint32_t);
};

uint32_t SPIBus::transfer(uint32_t data) {
    uint32_t out;
    _spi->sxBuf.reg = data;
    while ((_spi->sxStat.reg & (1 << _SPISTAT_SPIRBF)) == 0) {
        continue;
    }
    out = _spi->sxBuf.reg;
    return out;
}
