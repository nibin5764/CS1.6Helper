#include "stdafx.h"
#include "MemoryOperate.h"
#include "Err.h"

int mem_ReadBlock(IN HANDLE proHandle,IN DWORD baseAddr,IN list<DWORD> &offSetList,IN DWORD readLen, OUT BYTE *OutBuffer,IN OUT ULONG* BufferLen){
	if(*BufferLen <readLen){
		return HELPER_ERROR_BUFFER_TOO_SMALL;
	}
	if(offSetList.size()!=0){
// 		DWORD dwOffset = 0,dwOffsetLen = 4;
// 		BYTE beOffset[4]={0};
// 		HexStrTobyte((char*)offSetList.front().c_str(),(unsigned char*)beOffset,(unsigned int*)&dwOffsetLen);
// 		offSetList.pop_front();
// 		Reverse4Byte(beOffset);
// 		memcpy((void*)&dwOffset,beOffset,4);

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
	else{
		int rv = ReadProcessMemory(proHandle,(LPVOID)baseAddr,OutBuffer,readLen,BufferLen);
		if(rv == FALSE){
			return GetLastError();
		}
	}
	return HELPER_ERROR_SUCCESS;
}


int mem_WriteBlock(IN HANDLE proHandle,IN DWORD baseAddr,IN list<DWORD>& offSetList,IN DWORD WriteLen, IN BYTE *InBuffer,OUT ULONG* WrittenLen){

	if(offSetList.size()!=0){
// 		DWORD dwOffset = 0,dwOffsetLen = 4;
// 		BYTE beOffset[4]={0};
// 		HexStrTobyte((char*)offSetList.front().c_str(),(unsigned char*)beOffset,(unsigned int*)&dwOffsetLen);
// 		offSetList.pop_front();
// 		Reverse4Byte(beOffset);
// 		memcpy((void*)&dwOffset,beOffset,4);

		DWORD newBaseAddr,rv,ReadddLen;
		DWORD CurBaseAddr = baseAddr + offSetList.front();
		offSetList.pop_front();
		rv = ReadProcessMemory(proHandle,(LPVOID)CurBaseAddr,(LPVOID)&newBaseAddr,4,&ReadddLen);
		if(rv == FALSE){
			return GetLastError();
		}

		rv = mem_ReadBlock(proHandle,newBaseAddr,offSetList,WriteLen,(BYTE*)InBuffer,WrittenLen);
		return rv;

	}
	else{
		int rv = WriteProcessMemory(proHandle,(LPVOID)baseAddr,InBuffer,WriteLen,WrittenLen);
		if(rv == FALSE){
			return GetLastError();
		}
	}
	return HELPER_ERROR_SUCCESS;
}