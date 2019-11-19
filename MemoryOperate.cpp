#include "stdafx.h"
#include "MemoryOperate.h"
#include "Err.h"
#include <tlhelp32.h>
int mem_ReadBlock(IN HANDLE proHandle,IN DWORD baseAddr,IN list<DWORD> &offSetList,IN DWORD readLen, OUT BYTE *OutBuffer,IN OUT ULONG* BufferLen){
	if(*BufferLen <readLen){
		return HELPER_ERROR_BUFFER_TOO_SMALL;
	}
	if(offSetList.size()> 1){

		DWORD newBaseAddr,rv,ReadddLen;
		DWORD CurBaseAddr = baseAddr + offSetList.front();
		offSetList.pop_front();
		rv = ReadProcessMemory(proHandle,(LPVOID)CurBaseAddr,(LPVOID)&newBaseAddr,4,&ReadddLen);
		if(rv == FALSE){
			return GetLastError();
		}

		rv = mem_ReadBlock(proHandle,newBaseAddr,offSetList,readLen,(BYTE*)OutBuffer,BufferLen);
		return rv;

	}
	else if(offSetList.size() == 1){
		DWORD CurBaseAddr = baseAddr + offSetList.front();
		int rv = ReadProcessMemory(proHandle,(LPVOID)CurBaseAddr,OutBuffer,readLen,BufferLen);
		if(rv == FALSE){
			return GetLastError();
		}
	}
	else{
		return  HELPER_ERROR_OFFSET_INVALID;
	}
	return HELPER_ERROR_SUCCESS;
}


int mem_WriteBlock(IN HANDLE proHandle,IN DWORD baseAddr,IN list<DWORD>& offSetList,IN DWORD WriteLen, IN BYTE *InBuffer,OUT ULONG* WrittenLen){

	if(offSetList.size()> 1){

		DWORD newBaseAddr,rv,ReadddLen;
		DWORD CurBaseAddr = baseAddr + offSetList.front();
		offSetList.pop_front();
		rv = ReadProcessMemory(proHandle,(LPVOID)CurBaseAddr,(LPVOID)&newBaseAddr,4,&ReadddLen);
		if(rv == FALSE){
			return GetLastError();
		}

		rv = mem_WriteBlock(proHandle,newBaseAddr,offSetList,WriteLen,(BYTE*)InBuffer,WrittenLen);
		return rv;

	}
	else if(offSetList.size() == 1){
		DWORD CurBaseAddr = baseAddr + offSetList.front();
		int rv = WriteProcessMemory(proHandle,(LPVOID)CurBaseAddr,InBuffer,WriteLen,WrittenLen);
		if(rv == FALSE){
			return GetLastError();
		}
	}
	else{
		return  HELPER_ERROR_OFFSET_INVALID;
	}
	return HELPER_ERROR_SUCCESS;
}




//��ȡĿ������׵�ַ
int  mem_GetProcessAddr(DWORD dwPID, DWORD& baseAddr)
{
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;

	// ��Ŀ������л�ȡ���н��̵�snapshot
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{	
		return HELPER_ERROR_NOTFIND_PROADDR;
	}

	// ����MODULEENTRY32���ݽṹ��С�ֶ�
	me32.dwSize = sizeof(MODULEENTRY32);

	//������һ��ģ�����Ϣ�����ɹ��򷵻�
	if (!Module32First(hModuleSnap, &me32))
	{
		CloseHandle(hModuleSnap);    // ����������
		return HELPER_ERROR_NOTFIND_PROADDR;
	}

	// ��me32�еõ���ַ
	baseAddr = (DWORD)me32.modBaseAddr;

	// ������������ģ��������
	CloseHandle(hModuleSnap);
	return  HELPER_ERROR_SUCCESS;
}


//��Ȩ����

BOOL mem_SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege){
	TOKEN_PRIVILEGES tp;
	HANDLE hToken;
	LUID luid;
	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
		&hToken)){
			printf("OpenProcessToken error: %u\n", GetLastError());
			return FALSE;
	}

	if (!LookupPrivilegeValue(NULL,           // lookup privilege on local system
		lpszPrivilege,  // privilege to lookup
		&luid))        // receives LUID of privilege
	{
		printf("LookupPrivilegeValue error: %u\n", GetLastError());
		return FALSE;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	if (bEnablePrivilege)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else{
		tp.Privileges[0].Attributes = 0;
	}

	// Enable the privilege or disable all privileges.
	if (!AdjustTokenPrivileges(hToken,
		FALSE,
		&tp,
		sizeof(TOKEN_PRIVILEGES),
		(PTOKEN_PRIVILEGES)NULL,
		(PDWORD)NULL)){
			printf("AdjustTokenPrivileges error: %u\n", GetLastError());
			return FALSE;
	}

	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED){
		printf("The token does not have the specified privilege. \n");
		return FALSE;
	}
	return TRUE;
}