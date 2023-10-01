#include "proc.h"

DWORD proc::getProcessId(const wchar_t* name) {

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (INVALID_HANDLE_VALUE == hSnap) return 0;

	DWORD pid = 0;

	BOOL hResult;
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	hResult = Process32First(hSnap, &pe);

	if (!hResult) return 0;

	while (hResult) {
		if (!_wcsicmp(name, pe.szExeFile)) {
			pid = pe.th32ProcessID;
			break;
		}

		hResult = Process32Next(hSnap, &pe);
	}

	CloseHandle(hSnap);
	return pid;
}

uintptr_t proc::getModuleBaseAddr(DWORD pid, const wchar_t* module) {

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);

	if (INVALID_HANDLE_VALUE == hSnap) return 0;

	uintptr_t address = NULL;
	MODULEENTRY32 me; 
	me.dwSize = sizeof(MODULEENTRY32); 
	DWORD hResult = Module32First(hSnap, &me); 

	if (!hResult) return NULL;

	while (hResult) {
		if (!_wcsicmp(module, me.szModule)) {
			address = (uintptr_t)me.modBaseAddr;
			break;
		}

		hResult = Module32Next(hSnap, &me);
	}

	CloseHandle(hSnap);
	return address;
}

uintptr_t proc::findDMA(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets) {
	uintptr_t address = ptr;

	for (int i = 0; i < offsets.size(); i++) {
		ReadProcessMemory(hProc, (BYTE*)address, &address, sizeof(address), 0);
		address += offsets[i];
	}

	return address;
}
