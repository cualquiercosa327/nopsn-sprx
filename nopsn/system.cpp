#pragma once



#include "includes.h"
#include "system.h"
#include "types.h"




void sleep(usecond_t time) 
{
	sys_timer_usleep(time * 1000);
}

/*
int console_write(const char * s)
{ 
	uint32_t len;
	system_call_4(403, 0, (uint64_t) s, 32, (uint64_t) &len);
	return_to_user_prog(int);
}
*/


int sys_process_get_status(sys_pid_t pid)
{
	system_call_1(4, pid);
	return_to_user_prog(int);
}




// 1=power,2=status or 3=disk
int sys_sm_request_led(int led_id, uint8_t led_action)
{
	system_call_2(385, led_id, led_action);
	return_to_user_prog(int);
}

int sys_sm_control_led(uint8_t led_id, uint8_t led_action)
{ 
	system_call_2(386, led_id, led_action);
	return_to_user_prog(int);
}

// (STATUS),2 (POWER)(red, green, red+green combined: looks like yellow);
// 0,1,2,3 (off,on,blink fast, blink slow) 
int ControlLED(uint8_t led, uint8_t action)
{
	sys_sm_control_led(led, action);
	return 0;
}


uint8_t sfoBuffer[64];
s32 sys_process_get_paramsfo()
{
	system_call_1(30, sfoBuffer[64]);
	return_to_user_prog(int);

}

void GetProcessNumberOfObjects(u32 pid, size_t* count)
{
	sys_process_get_number_of_object(pid, count);
}

/*
int Memcpy(void* destination, const void* source, size_t size)
{
	
	system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)source);
	__dcbst(destination);
	__sync();
	__isync();
	return_to_user_prog(int);
}
*/

bool cstrcmp(const char* s1, const char* s2)
{
	while(*s1 && (*s1==*s2))
		s1++,s2++;
	if(*(const unsigned char*)s1-*(const unsigned char*)s2 == 0)
		return true;
	else
		return false;
}


int sys_ppu_thread_exit()
{
	system_call_1(41, 0);
	return_to_user_prog(int);
}


void printf(int n,...)
{
	void* lol;
	va_list a;
	va_start(a,n);
	lol = va_arg(a,void*);
        uint32_t len;
        system_call_4(403, 0, (uint64_t)lol, 32, (uint64_t) &len); 
	va_end(a);
}

//va (short version of sprintf) :
void* va(int n,...)
{
	void* buff;
	va_list a;
	va_start(a,n);
    buff =  va_arg(a,void*);
	va_end(a);
	return buff;
}


/*
 * Function:		ReadHex()
 * File:			main.c
 * Project:			ArtemisPS3-PRX
 * Description:		Converts a hex string into an array of bytes
 *					In cases where the len is less than 4, it will NOT (unlike ReadHexPartial) shift the value over such that something like "011" will be 0x01100000
 * Arguments:
 *	read:			buffer containing string
 *	start:			start index of conversion within buffer
 *	len:			length of hex string
 *	buf:			buffer that will store the resulting byte/char array after conversion
 *	bufSize:		allocated size of buf
 * Return:			Returns pointer to buf
 */
char * ReadHex(char * read, int start, int len, char * buf, int bufSize)
{
	for (int x = start; x < (len + start); x += 2)
	{
		buf[(x - start)/2] = (unsigned char)((((unsigned char)read[x] < 0x41) ? ((unsigned char)read[x] - 0x30) : ((unsigned char)read[x] - 0x37)) << 4) | (unsigned char)(((unsigned char)read[x+1] < 0x41) ? ((unsigned char)read[x+1] - 0x30) : ((unsigned char)read[x+1] - 0x37));
	}
	
	return buf;
}


// Get Temperatures
// 0=CELL/1=RSX
u64 sys_game_get_temperature(u32 _dev, u32 *_temp)
{
	system_call_2(383, (u64)_dev, (u64)_temp);
	return_to_user_prog(u64);
}


u32 GetTempCell(int unit)
{
	u32 tempCell=0;

	switch (unit)
	{

		// Celcius
		case 0:
			sys_game_get_temperature(0, &tempCell);
			tempCell=tempCell>>24;
			break;
		// Farenheit
		case 1:
			sys_game_get_temperature(0, &tempCell);
			tempCell=tempCell>>24;
			tempCell=int(1.8f*(float)tempCell+32.f);
			break;

		default:
			break;
	}

	return tempCell;
}

u32 GetTempRSX(int unit)
{
	u32 tempRSX=0;

	switch (unit)
	{

		// Celcius
		case 0:
			sys_game_get_temperature(1, &tempRSX);
			tempRSX=tempRSX>>24;
			break;
		// Farenheit
		case 1:
			sys_game_get_temperature(1, &tempRSX);
			tempRSX=tempRSX>>24;
			tempRSX=int(1.8f*(float)tempRSX+32.f);
			break;

		default:
			break;
	}

	return tempRSX;
}













