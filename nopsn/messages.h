#pragma once

#include "core.h"
#include "dialog.h"
#include "includes.h"
#include "natives.h"
#include "patches.h"
#include "system.h"

using namespace Dialog;


void PrintToXMB(char* text)
{
	msgdialog_mode = MODE_STRING_OK;
	Show(text);
}


void PrintDebugStats()
{
	char debug_stats[400];
	sprintf(debug_stats, "---[ NoPSN SPRX Debug Stats Output ]---\n\n\nCurrent App: %s [%s]\n\nStatus [%X]\n\nTOC: %X\n\nProcess ID: %X     On Stack?: [%X]\n\nParent Process ID: %X     On Stack?: [%X]\n\nPPU GUID: %X\n\nPARAM.SFO: [%X]\n\nCell Temp: [%i C]     RSX Temp [%i C]\n\n", appName, GetCID(), sys_process_get_status(sys_process_getpid()), GetTOC(NPUP10028), sys_process_getpid(), sys_process_is_stack((const void*)sys_process_getpid()), sys_process_getppid(), sys_process_is_stack((const void*)sys_process_getppid()), sys_process_get_ppu_guid(), sys_process_get_paramsfo(), GetTempCell(0), GetTempRSX(0));
	PrintToXMB(debug_stats);
}
