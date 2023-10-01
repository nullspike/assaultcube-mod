// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include "proc.h"
#include "mem.h"
#include <iostream>
#include <vector>

int main()
{

    DWORD pid = proc::getProcessId(L"ac_client.exe");

    if (0 == pid) {
        std::cout << "[-] process not found\n"; 
        return 0;
    }

    uintptr_t baseAddr = proc::getModuleBaseAddr(pid, L"ac_client.exe");
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, pid);

    if (!hProc) {
        std::cout << "[-] an error had occured when opening the process"; 
        return 0;
    }

    uintptr_t entityPtr = baseAddr + 0x17E0A8;
    std::vector<unsigned int> arAmmoOffsets = { 0x140 };
    std::vector<unsigned int> pistolAmmoOffsets = { 0x12c };
    std::vector<unsigned int> healthOffsets = { 0xec };
    uintptr_t arAmmoAddr = proc::findDMA(hProc, entityPtr, pistolAmmoOffsets);
    uintptr_t pistolAmmoAddr = proc::findDMA(hProc, entityPtr, pistolAmmoOffsets);
    uintptr_t healthAddr = proc::findDMA(hProc, entityPtr, pistolAmmoOffsets);

}
