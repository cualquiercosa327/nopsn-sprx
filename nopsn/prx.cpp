// Original code reference: http://www.nextgenupdate.com/forums/ps3-mods-cheats/749680-how-make-sprx-read-write-memory.html


// NoPSN SPRX

// esc0rtd3w 2017

// http://www.psx-place.com/threads/tutorial-psn-bypass-techniques-and-setting-up-development-debugging-environment.13287



#include "stdafx.h"

#include <cellstatus.h>
#include <sys/prx.h>

#include "cell.h"
#include "core.h"
//#include "dialog.h"
#include "patches.h"
#include "timer.h"

//using namespace Dialog;




sys_ppu_thread_t id;
sys_ppu_thread_t create_thread(void (*entry)(uint64_t), int priority, size_t stacksize, const char* threadname)
{	
	if(sys_ppu_thread_create(&id, entry, 0, priority , stacksize, 0, threadname) != CELL_OK)
	{
		console_write("Thread creation failed\n");	
	}
	else
	{
		console_write("Thread created\n");	
	}	
    return id;
}


SYS_MODULE_INFO( nopsn, 0, 1, 1);
SYS_MODULE_START( _nopsn_prx_entry );

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );
SYS_LIB_EXPORT( _nopsn_export_function, LIBNAME );


// An exported function is needed to generate the project's PRX stub export library
extern "C" int _nopsn_export_function(void)
{
    return CELL_OK;
}


void thread_entry(uint64_t arg)
{		
	
	// Writing To Memory
	// 1 byte - *(char*)0x0000000 = 0x01; //Yes this is literately how you write the memory in C++.
	// 2 bytes - *(short*)0x00000000 = 0x01;
	// 3 bytes - *(float*)0x00000000 = 0x01;
	// 4 bytes - *(int*)0x00000000 = 0x01;
	// 8 bytes - *(double*)0x00000000 = 0x01;

	for (;;)
	{
      if (isTimerReady())
      {
           sleep(5000);
           
		   // YouTube
		   Patch(NPUP10028);
		   Patch(NPEB01229);
		   Patch(NPJB00286);

		   // TuneIn Radio
		   //Patch(NPUP10042);
      }
	}
	


	/* 
	// Reading From Memory
	// 1 byte - *(char*)0x0000000;
	// 2 bytes - *(short*)0x00000000;
	// 3 bytes - *(float*)0x00000000;
	// 4 bytes - *(int*)0x00000000;
	// 8 bytes - *(double*)0x00000000;

	for (;;)
	{
      if (InGame())
      {
           sleep(5000);

           if (*(char*)0x1786418 == 63)
           {
				*(char*)0x1786418 = 0x40;
           }
           else 
           { 
			   *(char*)0x1786418 = 0x3F; //Obviously this wouldn't work because it would turn it on and off every 5 seconds
		   }
      }
	}
	*/

	sleep(200);
		   
    


}





extern "C" int _nopsn_prx_entry(void)
{

	//cellMsgDialogOpen2(0, "This Is A Test", 0, 0, 0);

	create_thread(thread_entry, 0x4AA, 0x6000, "NoPSN_SPRX");
	return 0;

    return SYS_PRX_RESIDENT;
}