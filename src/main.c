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
#include "nm24c17.h"
#include "util.h"

int main(void) {

  // Write out
  nm24c17_msg writemsg = {
    .page = 0x01,
    .addr = 0x22,
    .len = 16,
    .buf = {
      0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
	    0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    }
  };

  printf("Write to EEPROM\n");
  if (!nm24c17_write(&writemsg)) {

    delayForSeconds(1);
    printf("Read from EEPROM\n");

    // now we read this back in
    nm24c17_msg readmsg = {
      .page = 0x01,
      .addr = 0x22,
      .len  = 16
    };

    if (!nm24c17_read(&readmsg)) {
      printf("Page\tAddr\tWrote\tRead\n");
      for (int i = 0; i < readmsg.len; i++) {
       printf("%02x\t%02x\t%02x\t%02x\n", readmsg.page, readmsg.addr+i, writemsg.buf[i], readmsg.buf[i]);
      }
    } else {
      printf("Could not read from the EEPROM\n");
    }
  } else {
    printf("Could not write to the EEPROM\n");
  }

  printf("Exit\n");

  return 0;

}
