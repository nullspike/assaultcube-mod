#pragma once

#include <windows.h>

namespace mem {
	void patchAt(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProc); 
	void nopAt(BYTE* dst, unsigned int size, HANDLE hProc);
}

