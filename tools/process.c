#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <tchar.h>

unsigned int FindProcessId(const char *processname)
{
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    unsigned int result = 0;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hProcessSnap) return(result);

    pe32.dwSize = sizeof(PROCESSENTRY32); // <----- IMPORTANT

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);          // clean the snapshot object
        printf("!!! Failed to gather information on system processes! \n");
        return result;
    }

    do
    {
        //printf("Checking process %ls\n", pe32.szExeFile);
        if (0 == strcmp(processname, pe32.szExeFile))
        {
            result = pe32.th32ProcessID;
            break;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);

    return result;
}