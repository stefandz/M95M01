/*******************************************************************************

 M95M01 SPI EEPROM library
 -------------------------
 
 M95M01.h - M95M01 class header file
 
 Code written by Stefan Dzisiewski-Smith.
 
 This work is licensed under a MIT license https://opensource.org/licenses/MIT
 
 Copyright (c) 2016, Stefan Dzisiewski-Smith
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

*******************************************************************************/

#ifndef M95M01_H
#define M95M01_H

#include <SPI.h>


class M95M01_t
{		
	public:
		M95M01_t();
		void begin(uint8_t CS_pin, uint32_t speed_Hz);
		uint8_t write_byte(uint32_t address, uint8_t value);
		uint8_t read_byte(uint32_t address);
		uint8_t write_array(uint32_t address, uint8_t value_array[], const uint32_t array_length);
		uint8_t read_array(uint32_t address, uint8_t value_array[], const uint32_t array_length);
		static const uint16_t page_size = 256;  // bytes per page
		static const uint16_t num_pages = 512;
		static const uint32_t num_bytes = (uint32_t)page_size*(uint32_t)num_pages;


	// functions / variables internal to the M95M01_t class - you cannot access these externally

	private:
		// internal helper functions and variables
		// not exposed externally to the user
		uint8_t CS_pin;
		uint32_t page(uint32_t address);
		uint8_t page_address(uint32_t address);


};

extern M95M01_t M95M01;

#endif // M95M01_H