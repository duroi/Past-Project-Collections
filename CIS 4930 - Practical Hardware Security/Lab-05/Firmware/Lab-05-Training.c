/*
    This file is part of the ChipWhisperer Example Targets
    Copyright (C) 2012-2017 NewAE Technology Inc.
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "hal.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "simpleserial.h"

static void delay_2_ms(void);

void my_print(char *c)
{
    uint8_t resp[16] = {0};
    for(int i = 0; i < 16; i++)
    {
        resp[i] = (uint8_t)c[i];
    }
    simpleserial_put('r', 16, resp);
}

void my_puts(char *c)
{
  do {
    putch(*c);
  } while (*++c);
}
static void delay_2_ms()
{
  for (volatile unsigned int i=0; i < 0xfff; i++ ){
    ;
  }
}
void my_read(char *buf, int len)
{
  for(int i = 0; i < len; i++) {
    while (buf[i] = getch(), buf[i] == '\0');
    if (buf[i] == '\n') {
      buf[i] = '\0';
      return;
    }
  }
  buf[len - 1] = '\0';
}
uint8_t reset(uint8_t* x, uint8_t len)
{
    // Reset key here if needed
    return 0x00;
}
uint8_t password_checker_v1(uint8_t * test_password, uint8_t len){
    char real_password[] = "USFCSE";
//     int pass_len = 6;//sizeof(real_password)/sizeof(real_password[0]);
    int password_wrong = 0;
    trigger_high();
    for (int i = 0; i < sizeof(real_password) - 1; i++)
    {
        if (real_password[i] != test_password[i])
        {
            password_wrong = 1;
            break;
        }
    }
    
    trigger_low();
    
    if (password_wrong)
        //my_puts("WRONG PASSWORD!\n");
        my_print("WRONG PASSWORD\n");
    else
        //my_puts("ACCESS GRANTED!\n");
        my_print("ACCESS GRANTED\n");

    return 0x00;
}
uint8_t password_checker_v2(uint8_t * test_password, uint8_t len){
    char real_password[] = "USFCSE";
    int password_wrong = 0;
    trigger_high();
    for (uint8_t i = 0; i < sizeof(real_password) - 1; i++)
    {
        if (real_password[i] != test_password[i])
        {
            password_wrong = 1;
            break;
        }
    }
    if (password_wrong)
    {
        int wait = rand() % 12345;
        for(volatile int delay = 0; delay < wait; delay++){
            ;
        }
        my_print("WRONG PASSWORD\n");   
    }
    else
        my_print("ACCESS GRANTED\n");
    trigger_low();
    return 0x00;
}
int main(void)
{
    platform_init();
    init_uart();
    trigger_setup();
    my_puts("*****Safe-o-matic 3000 Booting...\n");
    //Print some fancy-sounding stuff so that attackers
    //will get scared and leave us alone
    my_puts("Aligning bits........[DONE]\n");
    delay_2_ms();
    my_puts("Checking Cesium RNG..[DONE]\n");
    delay_2_ms();
    my_puts("Masquerading flash...[DONE]\n");
    delay_2_ms();
    my_puts("Decrypting database..[DONE]\n");
    delay_2_ms();
    my_puts("\n\n");
    //Give them one last warning
    my_puts("WARNING: UNAUTHORIZED ACCESS WILL BE PUNISHED\n");
    trigger_low();
    //Get password
    my_puts("Please enter password to continue: ");
    simpleserial_init();
    simpleserial_addcmd('a', 16, password_checker_v1);
    simpleserial_addcmd('b', 16, password_checker_v2);
#if SS_VER != SS_VER_2_0
//  simpleserial_addcmd('k', 16, get_key);
    simpleserial_addcmd('x', 0, reset);
#endif
    while(1)
        simpleserial_get();
}