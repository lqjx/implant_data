#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <cstring>

unsigned char payload[] = {
    0x90,		// NOP
    0x90,		// NOP
    0xcc,		// NOP
    0xc3		// RET
};
unsigned int payload_len = 4;

int main()
{
    void* exec_mem;
    BOOL rv;
    HANDLE th;
    DWORD oldprotect = 0;

    exec_mem = VirtualAlloc(0, payload_len, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    std::cout << "Payload address: " << static_cast<void*>(payload) << "\n";
    std::cout << "exec_mem address: " << static_cast<void*>(exec_mem) << "\n";

    RtlMoveMemory(exec_mem, payload, payload_len);

    rv = VirtualProtect(exec_mem, payload_len, PAGE_EXECUTE_READWRITE, &oldprotect);

    std::cout << "LAUNCH BOOM ALLAHU AKBAR\n";
    std::cin.get();

    if (rv != 0) {
        th = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)exec_mem, 0, 0, 0);
    } else {
        std::cout << "Failed to execute\n";
    }

    std::cout << "Press any key to close\n";
    std::cin.get();
}
