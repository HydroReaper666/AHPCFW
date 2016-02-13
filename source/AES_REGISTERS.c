#include "types.h"
#include "AES_REGISTERS.h"

void SET_AES_CNT(u32 cnt){
	*((u32*)0x10009000) = cnt;
}

void SET_AES_BLKCNT(u32 cnt){
	*((u32*)0x10009004) = cnt;
}

void SET_AES_WRFIFO(u32 in){
	*((u32*)0x10009008) = in;
}

void GET_AES_RDFIFO(u32 out){
	out = *((u32*)0x1000900C);
}

void SET_AES_KEYSEL(u8 keyslot){
	*((u8*)0x10009010) = keyslot;
}

void SET_AES_KEYCNT(u8 keyslot){
	*((u8*)0x10009011) = keyslot | 0x80;
}

void SET_AES_CTR(u32 *ctr){
	u32* AES_CTR = (u32*)0x10009020;
	for (int i = 0; i < 4; i++) AES_CTR[i] = ctr[i];
}

void SET_AES_MAC(u32 *mac){
	u32* AES_MAC = (u32*)0x10009030;
	for (int i = 0; i < 4; i++) AES_MAC[i] = mac[i];
}

void SET_AES_KEY0(u8 keyslot, u32* key){
	u32* AES_KEY0 = (u32*)0x10009040;
	for (int i = 0; i < 0xC; i++) AES_KEY0[i+(keyslot*0xC)] = key[i];
}

void SET_AES_KEY1(u8 keyslot, u32* key){
	u32* AES_KEY1 = (u32*)0x10009070;
	for (int i = 0; i < 0xC; i++) AES_KEY1[i+(keyslot*0xC)] = key[i];
}

void SET_AES_KEY2(u8 keyslot, u32* key){
	u32* AES_KEY2 = (u32*)0x100090A0;
	for (int i = 0; i < 0xC; i++) AES_KEY2[i+(keyslot*0xC)] = key[i];
}

void SET_AES_KEY3(u8 keyslot, u32* key){
	u32* AES_KEY3 = (u32*)0x100090D0;
	for (int i = 0; i < 0xC; i++) AES_KEY3[i+(keyslot*0xC)] = key[i];
}

void SET_AES_KEYFIFO(u32* key){
	for (int i = 0; i < 4; i++) *((u32*)0x10009100) = key[i];
}

void SET_AES_KEYYFIFO(u32* key){
	for (int i = 0; i < 4; i++) *((u32*)0x10009108) = key[i];
}

void SET_AES_KEYXFIFO(u32* key){
	for (int i = 0; i < 4; i++) *((u32*)0x10009104) = key[i];
}