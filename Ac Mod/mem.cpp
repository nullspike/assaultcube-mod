#include "mem.h"

void mem::patchAt(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProc) {
	DWORD oldPermissions;
	VirtualProtectEx(hProc, dst, size, PAGE_EXECUTE_READWRITE, &oldPermissions);
	WriteProcessMemory(hProc, dst, src, size, nullptr); 
	VirtualProtectEx(hProc, dst, size, oldPermissions, &oldPermissions);
}


void mem::nopAt(BYTE* dst, unsigned int size, HANDLE hProc) {
	DWORD oldPermissions;
	VirtualProtectEx(hProc, dst, size, PAGE_EXECUTE_READWRITE, &oldPermissions);
	BYTE* nops = new BYTE[size]; 
	memset(nops, 0x90, size);
	WriteProcessMemory(hProc, dst, nops, size, nullptr);
	VirtualProtectEx(hProc, dst, size, oldPermissions, &oldPermissions);
}