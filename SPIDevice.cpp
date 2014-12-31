#include <SPIDevice.h>

extern SPIBus *spiBusses;

SPIDevice::SPIDevice(uint8_t channel, uint8_t cs, uint8_t mode, uint32_t speed) : _channel(channel), _cs(cs), _mode(mode), _speed(speed) {
    if (channel >= 4) {
        return;
    }
    _spi = &spiBusses[channel];
}

void SPIDevice::begin() {
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH);
}

void SPIDevice::write(uint8_t val) {
    transfer8(val);
}

void SPIDevice::open() {
    if (_spi->_active) {
        _spi->_active->close();
    }
    _spi->_active = this;

    _spi->setMode(_mode);

    _spi->sxCon.clr = SPI_CON_ON;
    _spi->sxBrg.reg = (F_CPU / _speed + 1) / 2 - 1;
    _spi->sxCon.reg = SPI_CON_MSTEN;

/*
    switch (_mode) {
        case 0:
            _spi->sxCon.set = SPI_MODE0;
            break;
        case 1:
            _spi->sxCon.set = SPI_MODE1;
            break;
        case 2:
            _spi->sxCon.set = SPI_MODE2;
            break;
        case 3:
            _spi->sxCon.set = SPI_MODE3;
            break;

    }
    switch (_bits) {
        case 8:
            _spi->sxCon.set = SPI_CON_MODE8;
            break;
        case 16:
            _spi->sxCon.set = SPI_CON_MODE16;
            break;
        case 32:
            _spi->sxCon.set = SPI_CON_MODE32;
            break;
    }
    _spi->sxCon.set = SPI_CON_ON;
    */
    digitalWrite(_cs, LOW);
}

void SPIDevice::close() {
    digitalWrite(_cs, LOW);
    _spi->_active = NULL;
}

uint32_t SPIDevice::transfer(uint32_t data) {
    return _spi->transfer(data);
}

void SPIDevice::setMode(uint8_t mode) {
}

void SPIDevice::setSpeed(uint32_t speed) {
    _speed = speed;
}

