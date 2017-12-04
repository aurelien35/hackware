/* Interface library for MCP23017 16 bit i2c I/O expander
 *
 * The MCP23017 implements 16 configurable I/O lines via an I2C
 * interface.  This library is designed to make it possible to use
 * this device without specific I2C/Wire commands.
 *
 * Copyright 2013, 2014 by david d zuhn <zoo@whitepineroute.org>
 *
 * This work is licensed under the Creative Commons Attribution-ShareAlike
 * 4.0 International License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-sa/4.0/deed.en_US.
 *
 * You may use this work for any purposes, provided that you make your
 * version available to anyone else.  
 */

#include "MCP23017.h"
#include <Wire.h>

/* common error checking routines, to make sure that we don't act when
 * unreasonable port or bit values are passed in
 */
#define MCP23017_checkAddress(address, error)   { if (address < 0x20 || address > 0x27) { Serial.println("MCP23017 : bad address value"); return error; } }
#define MCP23017_checkPort(port, error)         { if (port!=0 && port!=1) { Serial.println("MCP23017 : bad port value"); return error; } }
#define MCP23017_checkBit(bit, error)           { if (bit<0 || bit>7) { Serial.println("MCP23017 : bad bit value"); return error; } }

    
MCP23017::MCP23017(uint8_t address)
    : _address  (address)
{
}
//
uint8_t MCP23017::address() const
{
    return _address;
}
//
bool MCP23017::exists() const
{
    int config = readRegister(MCP23017::PORT_A, MCP23017::IOCON);

    return (config >= 0);
}
//
bool MCP23017::setMode(MCP23017::Port port, MCP23017::PinMode mode, uint8_t bit) const
{
    MCP23017_checkBit(bit, false);

    int chipMode = readRegister(port, MCP23017::IODIR);
    if (chipMode < 0)
    {
        Serial.println("MCP23017 : Error reading chipMode");
        return false;
    }

    int newMode = chipMode;
    int pullup = -1;
    int polarity = -1;

    switch (mode)
    {
    case PinMode::OUTPUT_MODE :
        bitClear(newMode, bit);
        break;

    case PinMode::INPUT_MODE :
        bitSet(newMode, bit);
        break;

    case PinMode::INPUT_PULL_UP_MODE :
        bitSet(newMode, bit);
        pullup = readRegister(port, MCP23017::GPPU);
        
        if (pullup >= 0)
        {
            bitSet(pullup, bit);
        }
        else
        {
            Serial.println("MCP23017 : Error reading GPPU");
            return false;
        }
        break;

    case PinMode::INPUT_INVERTED_MODE :
        bitSet(newMode, bit);
        polarity = readRegister(port, MCP23017::IPOL);
        
        if (polarity >= 0)
        {
            bitSet(polarity, 1);
        }
        else
        {
            Serial.println("MCP23017 : Error reading IPOL");
            return false;
        }
        break;

    case PinMode::INPUT_PULL_UP_INVERTED_MODE :
        bitSet(newMode, bit);

        pullup = readRegister(port, MCP23017::GPPU);
        
        if (pullup >= 0)
        {
            bitSet(pullup, bit);
        }
        else
        {
            Serial.println("MCP23017 : Error reading GPPU");
            return false;
        }

        polarity = readRegister(port, MCP23017::IPOL);
        if (polarity >= 0)
        {
            bitSet(polarity, 1);
        }
        else
        {
            Serial.println("MCP23017 : Error reading IPOL");
            return false;
        }
        break;

    default:
        Serial.println("MCP23017 : Unknow input mode");
        return false;
    }

    // We write the mode only if it's changed
    if (newMode != chipMode)
    {
        writeRegister(port, MCP23017::IODIR, newMode);
    }
    
    // If we read a pullup value, then write it no matter what
    if (pullup >= 0)
    {
        writeRegister(port, MCP23017::GPPU, pullup);
    }
    
    // If we read a polarity value, then write it no matter what
    if (polarity >= 0)
    {
        writeRegister(port, MCP23017::IPOL, pullup);
    }
}
//
bool MCP23017::setMode(MCP23017::Port port, MCP23017::PinMode mode) const
{
    return setMode(port, mode, 0xFF);
}
//
int MCP23017::getGPIO(MCP23017::Port port, uint8_t bit) const
{
    MCP23017_checkBit(bit, -1);

    int value = readRegister(port, MCP23017::GPIO);
    return bitRead(value, bit);
}
//
int MCP23017::getGPIO(MCP23017::Port port) const
{
    return readRegister(port, MCP23017::GPIO);
}
//
bool MCP23017::setGPIO(MCP23017::Port port, uint8_t bit, bool value) const
{
    MCP23017_checkBit(bit, false);

    int gpioVal = readRegister(port, MCP23017::GPIO);
    if (gpioVal < 0)
    {
        return false;
    }

    uint8_t newVal = gpioVal;
    bitWrite(newVal, bit, value);
    
    if (newVal != gpioVal)
    {
        writeRegister(port, MCP23017::GPIO, newVal);
    }
    
    return true;
}
//
bool MCP23017::setGPIO(MCP23017::Port port, uint8_t value) const
{
    writeRegister(port, MCP23017::GPIO, value);
    return true;
}
//
int MCP23017::readRegister(MCP23017::Port port, MCP23017::Register reg) const
{
    MCP23017_checkAddress(_address, -1);
    MCP23017_checkPort(port, -1);
    
    Wire.beginTransmission(_address);
    Wire.write(reg + port);
    Wire.endTransmission();
    Wire.requestFrom(_address, (uint8_t) 1);

    return Wire.read();
}
//
bool MCP23017::writeRegister(MCP23017::Port port, MCP23017::Register reg, uint8_t value) const
{
    MCP23017_checkAddress(_address, false);
    MCP23017_checkPort(port, false);
    
    Wire.beginTransmission(_address);
    Wire.write(reg + port);
    Wire.write(value);
    Wire.endTransmission();
    
    return true;
}
//
void MCP23017::debugDump() const
{
    uint8_t r[0x16];

    Serial.println("==============================");
    Serial.print("MCP23017 address 0x");
    Serial.print(_address, HEX);

    for (int i = 0; i < 0x16; i += 2)
    {
        int vA = readRegister(MCP23017::PORT_A, (MCP23017::Register) i);
        int vB = readRegister(MCP23017::PORT_B, (MCP23017::Register) i);

        if (vA < 0 || vB < 0)
        {
            Serial.print(" : error reading register ");
            Serial.print(i, HEX);
            Serial.println();
            return;
        }
        r[i]        = (uint8_t) vA;
        r[i + 1]    = (uint8_t) vB;
    }
    Serial.println();
    
    dumpValue("IODIR",      Register::IODIR,    r[0],       r[1]);
    dumpValue("IPOL",       Register::IPOL,     r[2],       r[3]);
    dumpValue("GPINTEN",    Register::GPINTEN,  r[4],       r[5]);
    dumpValue("DEFVAL",     Register::DEFVAL,   r[6],       r[7]);
    dumpValue("INTCON",     Register::INTCON,   r[8],       r[9]);
    dumpValue("IOCON",      Register::IOCON,    r[0xA],     r[0xB]);
    dumpValue("GPPU",       Register::GPPU,     r[0xC],     r[0xD]);
    dumpValue("INTF",       Register::INTF,     r[0xE],     r[0xF]);
    dumpValue("INTCAP",     Register::INTCAP,   r[0x10],    r[0x11]);
    dumpValue("GPIO",       Register::GPIO,     r[0x12],    r[0x13]);
    dumpValue("OLAT",       Register::OLAT,     r[0x14],    r[0x15]);
    Serial.println("==============================");
}
//
void MCP23017::dumpValue(const char* name, uint8_t addr, uint8_t v1, uint8_t v2) const
{
    Serial.print(name);
    Serial.print("A ");
    Serial.print(addr, HEX);
    Serial.print(" ");
    Serial.println(v1, BIN);
    Serial.print(name);
    Serial.print("B ");
    Serial.print(addr + 1, HEX);
    Serial.print(" ");
    Serial.println(v2, BIN);
}
