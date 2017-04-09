#pragma once

#include "nopsn.h"


// A few basic instructions
int nop = 0x60000000;


// List of Regions
enum Region
{
	US,
	EU,
	JP,
};

// List of all PSN Apps by NAME
enum Name
{
	TuneInRadio,
	YouTube,
};


// List of all PSN Apps by CONTENT_ID
enum ContentID
{
	NPUP10028,// YouTube
	NPUP10042,// TuneIn Radio
	NPEB01831,// TuneIn Radio
	NPEB01229,// YouTube
	NPJB00286,// YouTube
};




// NoPSN Main Patch Function
void Patch(int cid)
{
	// Check App Name
	switch (cid) {

		// YouTube
		case NPUP10028:
			WriteMemoryDirect(NPUP10028_a[0], NPUP10028_v[0]);
			break;
		case NPEB01229:
			WriteMemoryDirect(NPEB01229_a[0], NPEB01229_v[0]);
			break;
		case NPJB00286:
			WriteMemoryDirect(NPJB00286_a[0], NPJB00286_v[0]);
			break;

		// TuneIn Radio
		case NPUP10042:
			WriteMemoryDirect(NPUP10042_a[0], NPUP10042_v[0]);
			WriteMemoryDirect(NPUP10042_a[1], NPUP10042_v[1]);
			WriteMemoryDirect(NPUP10042_a[2], NPUP10042_v[2]);
			break;

		default:
			break;
	};

}




