/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 iAchieved.it
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef __NM24C17_H__
#define __NM24C17_H__

#include <stdint.h>

typedef struct nm24c17_msg {
  uint8_t page;    // Page within NM24C17
  uint8_t len;     // Length of the buffer
  uint8_t addr;    // EEPROM address within page
  uint8_t buf[16]; // Data
} nm24c17_msg;

// Write to the NM24C17
int nm24c17_write(nm24c17_msg* msg);

// Read from the NM24C17
int nm24c17_read(nm24c17_msg* msg);

#endif
