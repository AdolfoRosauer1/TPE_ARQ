#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <idtLoader.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	ncStart();

	char buffer[10];

	ncPrint(0,"[x64BareBones]");
	ncNewline(0);

	ncPrint(0,"CPU Vendor:");
	ncPrint(0,cpuVendor(buffer));
	ncNewline(0);

	ncPrint(0,"[Loading modules]");
	ncNewline(0);
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint(0,"[Done]");
	ncNewline(0);
	ncNewline(0);

	ncPrint(0,"[Initializing kernel's binary]");
	ncNewline(0);

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint(0,"  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline(0);
	ncPrint(0,"  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline(0);
	ncPrint(0,"  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline(0);
	ncPrint(0,"  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline(0);

	ncPrint(0,"[Done]");
	ncNewline(0);
	ncNewline(0);
	return getStackBase();
}

int main()
{	
	load_idt();
	ncPrint(0,"[Kernel Main]");
	ncNewline(0);
	ncPrint(0,"  Sample code module at 0x");
	ncPrintHex((uint64_t)sampleCodeModuleAddress);
	ncNewline(0);
	ncPrint(0,"  Calling the sample code module returned: ");
	ncPrintHex(((EntryPoint)sampleCodeModuleAddress)());
	ncNewline(0);
	ncNewline(0);

	ncPrint(0,"  Sample data module at 0x");
	ncPrintHex((uint64_t)sampleDataModuleAddress);
	ncNewline(0);
	ncPrint(0,"  Sample data module contents: ");
	ncPrint(0,(char*)sampleDataModuleAddress);
	ncNewline(0);

	ncPrint(0,"[Finished]");
	return 0;
}
