/* emacs should treat this as -*- c++ -*-  */

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

#ifndef MCP23017_H
#define MCP23017_H

#include <Arduino.h>

class MCP23017
{
private:
	uint8_t					_address;
	
public:
	typedef enum
	{
		IODIR	= 0x00,
		IPOL	= 0x02,
		GPINTEN	= 0x04,
		DEFVAL	= 0x06,
		INTCON	= 0x08,
		IOCON	= 0x0A,
		GPPU	= 0x0C,
		INTF	= 0x0D,
		INTCAP	= 0x10,
		GPIO	= 0x12,
		OLAT	= 0x14
	} Register;
	
	typedef enum
	{
		PORT_A	= 0,
		PORT_B	= 1
	} Port;
	
	typedef enum
	{
		Output					= 0,
		Input					= 1,
		Input_PullUp			= 2,
		Input_Inverted			= 3,
		Input_PullUp_Inverted	= 4
	} PinMode;

public:
	MCP23017(uint8_t address);

	uint8_t				address() const;
	bool				exists() const;
	bool				setMode(MCP23017::Port port, MCP23017::PinMode mode, uint8_t bit) const;
	bool				setMode(MCP23017::Port port, MCP23017::PinMode mode) const;
	int					getGPIO(MCP23017::Port port, uint8_t bit) const;									// Return 0 or 1
	int					getGPIO(MCP23017::Port port) const;													// Return 0-255 (0 or 1 for each of the 8 bits)
	bool				setGPIO(MCP23017::Port port, uint8_t bit, bool value) const;						// Set 0 or 1
	bool				setGPIO(MCP23017::Port port, uint8_t value) const;									// Set 0-255 (0 or 1 for each of the 8 bits)
	int					readRegister(MCP23017::Port port, MCP23017::Register reg) const;					// Read a given register from the MCP23017 device
	bool				writeRegister(MCP23017::Port port, MCP23017::Register reg, uint8_t value) const;	// Write a given register to the MCP23017 device
	void				debugDump() const;
	
protected:
	void				dumpValue(const char* name, uint8_t addr, uint8_t v1, uint8_t v2) const;
};

#endif
