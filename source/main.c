#include "aes.h"
#include "fatfs/ff.h"
#include "hid.h"
#include "draw.h"
#include "firm.h"
/*
	u8 key0[0x10] = { 0xC1, 0xAA, 0xF9, 0x0B, 0x61, 0xC5, 0x7A, 0x1E, 0xEE, 0x6B, 0x19, 0x51, 0x51, 0x1C, 0x9A, 0x90 };
	u8 key1[0x10] = { 0x0F, 0x4D, 0x21, 0xA0, 0x51, 0x05, 0x77, 0xB0, 0x6B, 0x65, 0xEC, 0xB2, 0xD3, 0xB0, 0xC0, 0x63 };
*/
u8 keyX[16] = { 0xCE, 0xE7, 0xD8, 0xAB, 0x30, 0xC0, 0x0D, 0xAE, 0x85, 0x0E, 0xF5, 0xE3, 0x82, 0xAC, 0x5A, 0xF3 };
u8 AESKey2[0x10] = { 0x42, 0x3F, 0x81, 0x7A, 0x23, 0x52, 0x58, 0x31, 0x6E, 0x75, 0x8E, 0x3A, 0x39, 0x43, 0x2E, 0xD0 };
u8 keyXBuf[0x10] = { 0xDD, 0xDA, 0xA4, 0xC6, 0x2C, 0xC4, 0x50, 0xE9, 0xDA, 0xB6, 0x9B, 0x0D, 0x9D, 0x2A, 0x21, 0x98 };

void _start(void){
	/*
		u8 keyX[0x10];
		for (int i = 0; i < 0x10; i++) keyX[i] = key0[i] ^ key1[i];
	*/
	set_keyX(0x25, &keyX);
	
	set_normalKey(0x11, AESKey2);
	u8 outbuf[0x10];
	for (int i = 0x19; i < 0x20; i++){
		set_keyslot(0x11);
		aes(keyXBuf, outbuf, NULL, 1, AES_ECB_DECRYPT);
		set_keyX(i, outbuf);
		keyXBuf[0xF]++;
	}
	
	FATFS sdmc;
	if (f_mount(&sdmc, "0:", 0) == FR_OK){
		FIL firm;
		unsigned int * br = 0;
		if (f_open(&firm, "firm.bin", FA_READ | FA_OPEN_EXISTING) == FR_OK){
			f_read(&firm, (void*)0x24000000, f_size(&firm), br);
			f_close(&firm);
		}
	}
	f_mount(NULL, "0:", 0);
	
	firmlaunch((void*)0x24000000);
}