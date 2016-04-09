#include "aes.h"
#include "types.h"

u8 keyX[0x10] = { /*Insert 0x25 keyx here*/ };

u8 keyX0[0x10] = { 0x10, 0xE6, 0x0C, 0x1F, 0x69, 0xFF, 0x6F, 0xA9, 0x7D, 0x3B, 0xBE, 0xA3, 0x88, 0xCC, 0x17, 0x8A };
u8 keyY0[0x10] = { 0x31, 0x69, 0x0D, 0xD4, 0xF1, 0x6A, 0xDB, 0xF0, 0xF3, 0xD0, 0xE4, 0xBF, 0xD6, 0x05, 0xA5, 0x4F };

u8 keyX1[0x10] = { 0x4F, 0x5D, 0xA6, 0x5D, 0xF2, 0x62, 0x3E, 0x10, 0x55, 0x2F, 0x3B, 0xC4, 0x67, 0xA0, 0x70, 0x40 };
u8 keyY1[0x10] = { 0xB9, 0xC0, 0xE0, 0x45, 0xEC, 0x96, 0x88, 0x2B, 0xD0, 0xA4, 0xE1, 0xB9, 0xBF, 0x31, 0xBC, 0xBD };

u8 outbuf[0x10];

int keydata_init(u8 keyslot, u8 sector_key, u32* FIRM){
	u32* arm9bin = FIRM != NULL ? FIRM + FIRM[0xA0/4] : (void*)0x8006800;
	u32 arm9size = FIRM != NULL ? FIRM[0xA8/4] : 0x90000;
	
	switch (keyslot){
		case 0x05:
			for (u32 i = 0; i < (arm9size/4); i++){
				if (arm9bin[i] == 0x4E4F804D){
					set_keyY(0x05, arm9bin+(i*4));
					return 0;
				}
			}
		
		case 0x11:
			switch (sector_key){
				case 0:
					set_keyX(0x11, keyX0);
					set_keyY(0x11, keyY0);
				case 1:
					set_keyX(0x11, keyX1);
					set_keyY(0x11, keyY1);
			}
			return 0;
		
		case 0x25:
			set_keyX(0x25, keyX);
			return 0;
	
		case 0x18:
			set_keyX(0x11, keyX0);
			set_keyY(0x11, keyY0);
			set_keyslot(0x11);
			for (u32 i = 0; i < (arm9size/4); i++){
				if (arm9bin[i] == 0xF1E48DA4){
					aes(arm9bin+(i*4), outbuf, NULL, 1, AES_ECB_DECRYPT);
					set_keyX(0x18, outbuf);
					return 0;
				}
			}
		
		case 0x1B: //0x19 - 0x1F technically
			set_keyX(0x11, keyX1);
			set_keyY(0x11, keyY1);
			set_keyslot(0x11);
			for (u32 i = 0; i < (arm9size/4); i++){
				if (arm9bin[i] == 0xC6A4DADD){
					for (int i = 0x19; i < 0x20; i++){
						aes(arm9bin+(i*4), outbuf, NULL, 1, AES_ECB_DECRYPT);
						set_keyX(i, outbuf);
						*((u8 *)arm9bin+(i*4)+0xF) += 1;
					}
					return 0;
				}
			}
	}
	return 1;
}