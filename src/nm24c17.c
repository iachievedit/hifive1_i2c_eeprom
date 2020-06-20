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

#include <stdio.h>
#include <metal/i2c.h>

#include "nm24c17.h"

#define I2C_BAUDRATE 100000
#define NM24C17_BASE_ADDR 0x50

struct metal_i2c* i2c_setup() {
	struct metal_i2c* i2c = metal_i2c_get_device(0);
	if (!i2c) {
		printf("I2C not available\n");
	}	else {
		metal_i2c_init(i2c, I2C_BAUDRATE, METAL_I2C_MASTER);
	}
	return i2c;
}

int nm24c17_write(nm24c17_msg* msg) {
	struct metal_i2c* i2c = i2c_setup();
	if (!i2c) return -1;

	unsigned int device_addr = NM24C17_BASE_ADDR | msg->page;
	uint8_t              len = 1 + msg->len;

	return metal_i2c_write(i2c, device_addr,
											   len, &msg->addr,
												 METAL_I2C_STOP_ENABLE);
}

int nm24c17_read(nm24c17_msg* msg) {

	struct metal_i2c* i2c = i2c_setup();
	if (!i2c) return -1;

	unsigned int device_addr = NM24C17_BASE_ADDR | msg->page;

	printf("Length = %d\n", msg->len);

	if (!metal_i2c_write(i2c, device_addr, 1, &msg->addr, METAL_I2C_STOP_DISABLE)) {
	  return metal_i2c_read(i2c,  device_addr, msg->len, msg->buf, METAL_I2C_STOP_ENABLE);
	}
  return -1;

}