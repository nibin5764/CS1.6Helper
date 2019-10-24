/*******************************************************/
/*****************内存相关操作***************************/
/*******************************************************/

#include<list>
#include <string>
#include "Utility.h"
using namespace std;



/*
 *	读取内存数据
 *	proHandle		[IN]进程句柄，由OpenProcess获得
 *	baseAddr		[IN]32位内存基址
 *	offSetList		[IN]偏移量列表，offSetList[0] 表示第一级偏移，offSetList[1]表示第二级偏移....
 *	readLen			[IN]需要读取的内存长度
 *  OutBuffer		[OUT]输出缓冲区
 *  BufferLen		[IN,OUT] 输入表示 缓冲区大小，输出表示实际读出的数据长度
 *	备注:  offSetList直接用DWORD是不是更方便些？
 */
int mem_ReadBlock(IN HANDLE proHandle,IN DWORD baseAddr,IN list<DWORD> &offSetList,IN DWORD readLen, OUT BYTE *OutBuffer,IN OUT ULONG* BufferLen);


/*
 *	读取内存数据
 *	proHandle		[IN]进程句柄，由OpenProcess获得
 *	baseAddr		[IN]32位内存基址
 *	offSetList		[IN]偏移量列表，offSetList[0] 表示第一级偏移，offSetList[1]表示第二级偏移....
 *	WriteLen		[IN]需要写入的内存长度
 *  InBuffer		[OUT]输出缓冲区
 *  WrittenLen		[OUT]表示实际写入的数据长度
 *	备注: 
 */
int mem_WriteBlock(IN HANDLE proHandle,IN DWORD baseAddr,IN list<DWORD> &offSetList,IN DWORD WriteLen, IN BYTE *InBuffer,OUT ULONG* WrittenLen);



int  mem_GetProcessAddr(DWORD dwPID, DWORD& baseAddr);