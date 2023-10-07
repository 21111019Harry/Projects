#include<sys/types.h>
#include<sys/stat.h>
#include<iostream>
#include<string.h>
#include<windows.h>
#include<tlhelp32.h>
#include<stdio.h>
#include<io.h>

using namespace std;
#pragma warning(disable : 4996)

typedef unsigned int UINT;

// structure to create LogFile with desired information
typedef struct tagLOGFILE
{
	char ProcessName[100];
	UINT pid;
	UINT ppid;
	UINT thread_cnt;
}LOGFILE;

class ThreadInfo
{
private:
	DWORD PID;
	HANDLE hThreadSnap;
	THREADENTRY32 te32;
public:
	ThreadInfo(DWORD);
	bool ThreadDisplay(DWORD);
};

/////////////////////////////////////////////////////////////////////////////////////////////
//Name				:ThreadInfo(constructor)
//Input				:DWORD
//Description		:Initialise resources for ThreadInfo class such as tacking snapshot
//					 of all threads of Process passesed as Parameter
//Author			:Harshal Nikam
//Date				:28 March 2022
/////////////////////////////////////////////////////////////////////////////////////////////
ThreadInfo::ThreadInfo(DWORD no)
{
	PID = no;
	// Take a snapshot of all Threads in the system by giving PID of Process.
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, PID);

	if (hThreadSnap == INVALID_HANDLE_VALUE)
	{
		cout << "Unable to create the snapshot thread pool" << endl;
		return;
	}
	//  Set the size of the structure before using it. 
	te32.dwSize = sizeof(THREADENTRY32);
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Name				:ThreadDisplay
//Input				:DWORD
//Output			:bool
//Description		:Displays all thread's PID associated with Process
//Author			:Harshal Nikam
//Date				:28 March 2022
/////////////////////////////////////////////////////////////////////////////////////////////
bool ThreadInfo::ThreadDisplay(DWORD tcnt)
{
	//  Retrieve information about the first thread of process , 
	//  and exit if unsuccessful 
	if (!Thread32First(hThreadSnap, &te32))
	{
		cout << "Error:In Getting the First Thread" << endl;
		CloseHandle(hThreadSnap);
		return FALSE;
	}
	cout << "\nTHREAD OF THIS PROCESS" << endl;
	//  Now walk the Thread list of the process, 
	//  and display ThreadID each Process 
	do
	{
		if (te32.th32OwnerProcessID == PID)
		{
			cout << "\tTHREAD ID:" << te32.th32ThreadID << endl;
			tcnt--;
		}
	} while (Thread32Next(hThreadSnap, &te32) && tcnt != 0);
	CloseHandle(hThreadSnap);
	return TRUE;
}

class DLLInfo
{
private:
	DWORD PID;
	MODULEENTRY32 me32;
	HANDLE hProcessSnap;
public:
	DLLInfo(DWORD);
	bool DependentDLLDisplay();
};

/////////////////////////////////////////////////////////////////////////////////////////////
//Name				:DLLInfo(constructor)
//Input				:DWORD
//Output			:-
//Description		:Take snapshot of all DLL of passed process
//Author			:Harshal Nikam
//Date				:28 March 2022
/////////////////////////////////////////////////////////////////////////////////////////////
DLLInfo::DLLInfo(DWORD no)
{
	PID = no;
	// Take a snapshot of all DLL in the system by giving PID of process.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		cout << "ERROR:Unable to create the snapshot of current thread Pool" << endl;
		return;
	}
	//  Set the size of the structure before using it. 
	me32.dwSize = sizeof(MODULEENTRY32);
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Name				:DependentDLLDisplay
//Input				:void
//Output			:bool
//Description		:Displays all DLL associated with Process
//Author			:Harshal Nikam
//Date				:28 March 2022
/////////////////////////////////////////////////////////////////////////////////////////////
bool DLLInfo::DependentDLLDisplay()
{
	char arr[100];
	//  Retrieve information about the first module, 
	//  and exit if unsuccessful 
	if (!Module32First(hProcessSnap, &me32))
	{
		cout << "FAILED to get DLL information" << endl;
		CloseHandle(hProcessSnap); //clean the snapshot object
		return FALSE;
	}
	cout << "\nDEPENDENT DLL OF THIS PROCESS" << endl;
	//  Now walk the DLL list of the process, 
	//  and display each DLL
	do
	{
		wcstombs_s(NULL, arr, 100, me32.szModule, 100);
		cout << "\t" << arr << endl;
	} while (Module32Next(hProcessSnap, &me32));
	CloseHandle(hProcessSnap); //clean the snapshot object
	return TRUE;
}

class ProcessInfo
{
private:
	DWORD PID;
	DLLInfo* pdobj;
	ThreadInfo* ptobj;
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;
public:
	ProcessInfo();
	bool ProcessDisplay(const char*);
	bool ProcessLog();
	bool ReadLog(DWORD, DWORD, DWORD, DWORD);
	bool ProcessSearch(char*);
	bool KillProcess(char*);
};

/////////////////////////////////////////////////////////////////////////////////////////////
//Name				:ProcessInfo(constructor)
//Input				:void
//Output			:-
//Description		:Take snapshot of all processes run at time of execution
//Author			:Harshal Nikam
//Date				:28 March 2022
/////////////////////////////////////////////////////////////////////////////////////////////
ProcessInfo::ProcessInfo()
{
	ptobj = NULL;
	pdobj = NULL;
	// Take a snapshot of all processes in the system by giving secon parameter as 0.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		cout << "Error:UNABLE to creatr the Snapshot of running process" << endl;
		return;
	}
	//  Set the size of the structure before using it. 
	pe32.dwSize = sizeof(PROCESSENTRY32);
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Name				:ProcessDisplay
//Input				:const char*
//Output			:bool
//Description		:Displays all Process executing in RAM
//Author			:Harshal Nikam
//Date				:28 March 2022
/////////////////////////////////////////////////////////////////////////////////////////////
bool ProcessInfo::ProcessDisplay(const char* option)
{
	char arr[100];
	//  Retrieve information about the first process, 
	//  and exit if unsuccessful 
	if (!Process32First(hProcessSnap, &pe32))
	{
		cout << "Error: In Finding the first process." << endl;
		CloseHandle(hProcessSnap); //clean the snapshot object
		return FALSE;
	}
	//  Now walk the Process list, 
	//  and display information about each process
	do
	{
		cout << "\n-------------------------------------------";
		wcstombs_s(NULL, arr, 100, pe32.szExeFile, 100);
		cout << "\nPROCESS NAME:" << arr;
		cout << "\nPID:" << pe32.th32ProcessID;
		cout << "\nPARENT PID:" << pe32.th32ParentProcessID;
		cout << "\nNo OF Threads:" << pe32.cntThreads;

		if ((_stricmp(option, "-a") == 0) || (_stricmp(option, "-d") == 0) || (_stricmp(option, "-t") == 0))
		{
			if ((_stricmp(option, "-t")) == 0 || (_stricmp(option, "-a") == 0))
			{
				ptobj = new ThreadInfo(pe32.th32ProcessID);
				ptobj->ThreadDisplay(pe32.cntThreads);
				delete ptobj;
			}
			if ((_stricmp(option, "-d")) == 0 || (_stricmp(option, "-a") == 0))
			{
				pdobj = new DLLInfo(pe32.th32ProcessID);
				pdobj->DependentDLLDisplay();
				delete pdobj;
			}
		}
	} while (Process32Next(hProcessSnap, &pe32));
	CloseHandle(hProcessSnap); //clean the snapshot object
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Name				:ProcessLog
//Input				:void
//Output			:bool
//Description		:Create a Log File of Process with Time stamp
//Author			:Harshal Nikam
//Date				:28 March 2022
/////////////////////////////////////////////////////////////////////////////////////////////
bool ProcessInfo::ProcessLog()
{
	const char* month[] = { "JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEPT","OCT","NOV","DEC" };
	char FileName[50], arr[512];
	int i = 0;
	SYSTEMTIME It;
	LOGFILE* fobj;
	FILE* fp;
	GetLocalTime(&It);
	sprintf_s(FileName, "E:\\ProcMonLogFiles\\ProcMonLog %02d_%02d_%02d%s.txt", It.wHour, It.wMinute, It.wDay, month[It.wMonth - 1]);
	fp = fopen(FileName, "wb");
	if (fp == NULL)
	{
		cout << "Unable to create Log File fp == NULL" << endl;
		return FALSE;
	}
	else
	{
		cout << "\nLog File Successfully gets creted as:" << FileName << endl;
		cout << "\nTime of Log file Creation is->" << It.wHour << ":" << It.wMinute << ":" << It.wDay << "th" << month[It.wMonth - 1] << endl;
	}
	//  Retrieve information about the first process, 
	//  and exit if unsuccessful 
	if (!Process32First(hProcessSnap, &pe32))
	{
		cout << "Error:In Finding the First Process." << endl;
		CloseHandle(hProcessSnap); //clean the snapshot object
		return FALSE;
	}
	int x = 0;
	do
	{
		x++;
	} while (Process32Next(hProcessSnap, &pe32));
	fobj = (LOGFILE*)malloc(sizeof(LOGFILE) * x);
	Process32First(hProcessSnap, &pe32);
	//  Now walk the Process list, 
	//  and display information about each process	
	do
	{
		wcstombs_s(NULL, arr, 100, pe32.szExeFile, 100);
		strcpy_s((fobj[i].ProcessName), arr);
		fobj[i].pid = pe32.th32ProcessID;
		fobj[i].ppid = pe32.th32ParentProcessID;
		fobj[i].thread_cnt = pe32.cntThreads;
		i++;
	} while (Process32Next(hProcessSnap, &pe32) && i <= x);
	fwrite(fobj, i, sizeof(LOGFILE), fp);
	CloseHandle(hProcessSnap); //clean the snapshot object
	fclose(fp);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Name				:ReadLog
//Input				:DWORD,DWORD,DWORD,DWORD
//Output			:bool
//Description		:Reads Logfile's contents and display them to user
//Author			:Harshal Nikam
//Date				:28 March 2022
/////////////////////////////////////////////////////////////////////////////////////////////
bool ProcessInfo::ReadLog(DWORD hr, DWORD min, DWORD date, DWORD month)
{
	char FileName[50];
	const char* montharr[] = { "JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEPT","OCT","NOV","DEC" };
	int ret = 0, count = 0;
	LOGFILE fobj;
	FILE* fp;
	sprintf_s(FileName, "E:\\ProcMonLogFiles\\ProcMonLog %02d_%02d_%02d%s.txt", hr, min, date, montharr[month - 1]);
	fp = fopen(FileName, "rb");
	if (fp == NULL)
	{
		cout << "Error :Unable to open log file named as:" << FileName << endl;
		return FALSE;
	}
	while (ret = fread(&fobj, 1, sizeof(fobj), fp) != 0)
	{
		cout << "\n--------------------------------------------\n";
		cout << "Process Name:" << fobj.ProcessName << endl;
		cout << "PID of current process:" << fobj.pid << endl;
		cout << "Parent process PID:" << fobj.ppid << endl;
		cout << "Thread count of process:" << fobj.thread_cnt << endl;
	}
	fclose(fp);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Name				:ProcessSearch
//Input				:char*
//Output			:Search Particular Process with desired name
//Author			:Harshal Nikam
//Date				:28 March 2022
/////////////////////////////////////////////////////////////////////////////////////////////
bool ProcessInfo::ProcessSearch(char* name)
{
	char arr[100];
	bool flag = FALSE;
	//  Retrieve information about the first process, 
	//  and exit if unsuccessful 
	if (!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap); //clean the snapshot object
		return FALSE;
	}
	//  Now walk the Process list, 
	//  and display information about desired process
	do
	{
		wcstombs_s(NULL, arr, 100, pe32.szExeFile, 100);
		if (_stricmp(arr, name) == 0)
		{
			cout << endl << "PROCESS NAME:" << arr;
			cout << endl << "PID:" << pe32.th32ProcessID;
			cout << endl << "Parent PID:" << pe32.th32ParentProcessID;
			cout << endl << "No   of Thread:" << pe32.cntThreads;
			flag = TRUE;
			break;
		}
	} while (Process32Next(hProcessSnap, &pe32));
	CloseHandle(hProcessSnap); //clean the snapshot object
	return flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Name				:KillProcess
//Input				:char*
//Output			:bool
//Description		:Kill Particular Process with desired name
//Author			:Harshal Nikam
//Date				:28 March 2022
/////////////////////////////////////////////////////////////////////////////////////////////
bool ProcessInfo::KillProcess(char* name)
{
	char arr[100];
	int pid = -1;
	bool bret;
	HANDLE hprocess;
	//  Retrieve information about the first process, 
	//  and exit if unsuccessful 
	if (!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap); //clean the snapshot object
		return FALSE;
	}
	//  Now walk the Process list, 
	//  and find desired process to kill
	do
	{
		wcstombs_s(NULL, arr, 100, pe32.szExeFile, 100);
		if (_stricmp(arr, name) == 0)
		{
			pid = pe32.th32ProcessID;
			break;
		}
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap); //clean the snapshot object
	if (pid == -1)
	{
		cout << "ERROR: There is no such Process" << endl;
		return FALSE;
	}
	//API for open process for desired purpose
	hprocess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
	if (hprocess == NULL)
	{
		cout << "ERROR: THERE is no access to terminate" << endl;
		return FALSE;
	}
	//terminate process API
	bret = TerminateProcess(hprocess, 0);
	if (bret == FALSE)
	{
		cout << "Error :Unable to terminate process";
		return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Name				:HardwareDisplay
//Input				:void
//Output			:bool
//Description		:Displays all Information of hardware
//Author			:Harshal Nikam
//Date				:28 March 2022
/////////////////////////////////////////////////////////////////////////////////////////////
bool HardwareInfo()
{
	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo);

	cout << "Hardware Information of current system is:" << endl;
	cout << "\n----------------------------------------------" << endl;
	cout << "OEM ID:" << siSysInfo.dwOemId << endl;
	cout << "Number Of Processors:" << siSysInfo.dwNumberOfProcessors << endl;
	cout << "Page Size:" << siSysInfo.dwPageSize << endl;
	cout << "Processor Type:" << siSysInfo.dwProcessorType << endl;
	cout << "Minimum Application Address:" << siSysInfo.lpMinimumApplicationAddress << endl;
	cout << "Maximum Application Address:" << siSysInfo.lpMaximumApplicationAddress << endl;
	cout << "Active Processor Mask:" << siSysInfo.dwActiveProcessorMask << endl;
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////////////////////
//Name				:DisplayHelp
//Input				:void
//Output			:void
//Description		:Displays Help option to user
//Author			:Harshal Nikam
//Date				:28 March 2022
/////////////////////////////////////////////////////////////////////////////////////////////
void DisplayHelp()
{
	cout << "Developed and Maintained By Harshal Nikam" << endl;
	cout << "ps\t:Display all information of process" << endl;
	cout << "ps -t\t:-t flag Displays all information about threads" << endl;
	cout << "ps -d\t:-d flag Displays all information about DLL" << endl;
	cout << "cls\t:Clear the contents of console" << endl;
	cout << "log\t:Creates log of current runinng process on C drive" << endl;
	cout << "readlog\t:Display the information from specified log file" << endl;
	cout << "sysinfo\t:Display the current hardware configuration" << endl;
	cout << "search\t:Search and Display information of specific running process" << endl;
	cout << "kill\t:Terminate the specific process" << endl;
	cout << "exit\t:Terminate  ProcMon" << endl;
	cout << "help\t:Display Commands for ProcMon" << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Name				:manpage
//Input				:char*
//Output			:void
//Description		:displays how to execute particular command
//Author			:Harshal Nikam
//Date				:28 March 2022
/////////////////////////////////////////////////////////////////////////////////////////////
void man(char* cname)
{
	if (cname == NULL)return;
	if (strcmpi(cname, "ps") == 0)
	{
		cout << "DESCRIPTION:\n\t Process status\n";
		cout << "USAGE:\n\tps,\tDisplays information about process\n";
		cout << "\tps -t,\tDisplays Threads associated with processes\n";
		cout << "\tps -d,\tDisplays DLLs associated with processes\n";
	}
	else if (strcmpi(cname, "log") == 0)
	{
		cout << "DESCRIPTION:\n\t Creates log file\n";
		cout << "USAGE:\n\t log\n";
	}
	else if (strcmpi(cname, "readlog") == 0)
	{
		cout << "DESCRIPTION:\n\t reads log file and display its contents\n";
		cout << "USAGE:\n\t readlog\n";
	}
	else if (strcmpi(cname, "search") == 0)
	{
		cout << "DESCRIPTION:\n\t searches particular process \n";
		cout << "USAGE:\n\t search Process_Name\n";
	}
	else if (strcmpi(cname, "kill") == 0)
	{
		cout << "DESCRIPTION:\n\t kills particular process\n";
		cout << "USAGE:\n\t kill Process_Name\n";
	}
	else if (strcmpi(cname, "cls") == 0)
	{
		cout << "DESCRIPTION:\n\t clears konsole\n";
		cout << "USAGE:\n\t cls\n";
	}
	else if (strcmpi(cname, "exit") == 0)
	{
		cout << "DESCRIPTION:\n\t terminates from shell\n";
		cout << "USAGE:\n\t exit\n";
	}
	else if (strcmpi(cname, "help") == 0)
	{
		cout << "DESCRIPTION:\n\t displays help menu\n";
		cout << "USAGE:\n\t help\n";
	}
	else if (strcmpi(cname, "sysinfo") == 0)
	{
		cout << "DESCRIPTION:\n\t displays hardware information of running system\n";
		cout << "USAGE:\n\t sysinfo\n";
	}
	else
	{
		cout << "ERROR : Manual entry not found!!!\n";
	}

}
//Entry Point Function
int main(int argc, char* argv[])
{
	bool bret;
	char* ptr = NULL;
	ProcessInfo* ppobj = NULL;
	char command[4][80], str[80];
	int count, min, date, month, hr;
	int running = 1;		/* to make loop running*/

	while (running)
	{
		fflush(stdin);
		strcpy_s(str, "");
		cout << "\nProcMon : >";
		fgets(str, 80, stdin);

		count = sscanf(str, "%s %s %s %s", command[0], command[1], command[2], command[3]);
		if (count == 1)
		{
			if (_stricmp(command[0], "ps") == 0)
			{
				ppobj = new ProcessInfo();
				bret = ppobj->ProcessDisplay("-a");
				if (bret == FALSE)
				{
					cout << "ERROR:Unable to Display process" << endl;
				}
				delete ppobj;
			}
			else if (_stricmp(command[0], "sysinfo") == 0)
			{
				bret = HardwareInfo();
				if (bret == FALSE)
				{
					cout << "ERROR:Unable to get Hardware Information" << endl;
				}
			}
			else if (_stricmp(command[0], "log") == 0)
			{
				ppobj = new ProcessInfo();
				bret = ppobj->ProcessLog();
				if (bret == FALSE)
				{
					cout << "ERROR:Unable to create Log File" << endl;
				}
				delete ppobj;
			}
			else if (_stricmp(command[0], "readLog") == 0)
			{
				ppobj = new ProcessInfo();
				cout << "Enter Log file details as:" << endl;
				cout << "Hour\t\t:"; cin >> hr;
				cout << "Minute\t\t:"; cin >> min;
				cout << "Date\t\t:"; cin >> date;
				cout << "Month(In Numbers)\t:"; cin >> month;
				while ((getchar()) != '\n');
				bret = ppobj->ReadLog(hr, min, date, month);
				if (bret == FALSE)
				{
					cout << "ERROR : Unable to read specified Log file" << endl;
				}
				delete ppobj;
			}
			else if (_stricmp(command[0], "cls") == 0)
			{
				system("cls");
				continue;
			}
			else if (_stricmp(command[0], "help") == 0)
			{
				DisplayHelp();
				continue;
			}
			else if (_stricmp(command[0], "exit") == 0)
			{
				cout << endl << "Terminating  ProcMon" << endl;
				running = 0;
			}
			else
			{
				cout << endl << "ERROR :Command not Found !!" << endl;
				continue;
			}
		}
		else if (count == 2)
		{
			if (_stricmp(command[0], "ps") == 0)
			{
				if ((_stricmp("-t", command[1]) == 0) || (_stricmp("-d", command[1])) == 0)
				{
					ppobj = new ProcessInfo();
					bret = ppobj->ProcessDisplay(command[1]);
					if (bret == FALSE)
					{
						cout << "ERROR :Unable to display process information" << endl;
					}
					delete ppobj;
					continue;
				}
				else
				{
					cout << "Please Enter Valid flag(-d,-t)" << endl;
				}
			}
			else if (_stricmp(command[0], "search") == 0)
			{
				ppobj = new ProcessInfo();
				bret = ppobj->ProcessSearch(command[1]);
				if (bret == FALSE)
				{
					cout << "ERROR : There is no such process" << endl;
				}
				delete ppobj;
				continue;
			}
			else if (_stricmp(command[0], "kill") == 0)
			{
				ppobj = new ProcessInfo();
				bret = ppobj->KillProcess(command[1]);
				if (bret == FALSE)
				{
					cout << "ERROR : There is no such process" << endl;
				}
				else
				{
					cout << command[1] << "\tTerminated Successfully" << endl;
				}
				delete ppobj;
				continue;
			}
			else if (_stricmp(command[0], "man") == 0)
			{
				man(command[1]);
			}
		}
		else if (count != -1)
		{
			cout << endl << "ERROR: Command not Found !!!" << endl;
			continue;
		}
	}
	return 0;
}
