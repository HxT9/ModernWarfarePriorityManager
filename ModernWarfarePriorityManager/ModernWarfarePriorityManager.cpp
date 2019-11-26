#include <Windows.h>
#include <Tlhelp32.h>

using namespace std;

void SetProcessPriority(LPWSTR ProcessName, int Priority);

LPWSTR ProcessName = (LPWSTR)L"ModernWarfare.exe";

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show)
{
	while (true) {
		SetProcessPriority(ProcessName, NORMAL_PRIORITY_CLASS);
		Sleep(10000);
	}
	return 0;
}

void SetProcessPriority(LPWSTR ProcessName, int Priority)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (wcscmp(entry.szExeFile, ProcessName) == 0)
			{
				HANDLE h = OpenProcess(PROCESS_SET_INFORMATION, TRUE, entry.th32ProcessID);
				SetPriorityClass(h, Priority);
				CloseHandle(h);
			}
		}
	}
	CloseHandle(snapshot);
}