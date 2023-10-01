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

}

uintptr_t proc::findDMA(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets) {

}
