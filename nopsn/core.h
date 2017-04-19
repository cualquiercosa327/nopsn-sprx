#pragma once

#include "includes.h"
#include "types.h"


int TOC;

int UNK_TEXT_1 = 0x009AAE9C;

struct opd_s
{
	int32_t sub;
	int32_t toc;
};

struct timeval_32 {
	u32 tv_sec;
	s32 tv_usec;
};

int addrTemp[] = {0x00000000};
int memTemp[] = {0x00000000};

char* appName = "";
char* contentID = "";

int contentID_hex[9];

bool isTuneInRadio = false;
bool isYouTube = false;

// Directly Write To Memory
void WriteMemoryDirect(int address, int value);


// Source: http://stackoverflow.com/questions/5100718/integer-to-hex-string-in-c#5100745



