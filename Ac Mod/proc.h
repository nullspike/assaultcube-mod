#pragma once

#include <TlHelp32.h>
#include <windows.h>
#include <vector>

namespace proc {
	DWORD getProcessId(const wchar_t* name);
	uintptr_t getModuleBaseAddr(DWORD pid, const wchar_t* module);
	uintptr_t findDMA(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);
}


