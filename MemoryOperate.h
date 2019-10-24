/*******************************************************/
/*****************�ڴ���ز���***************************/
/*******************************************************/

#include<list>
#include <string>
#include "Utility.h"
using namespace std;



/*
 *	��ȡ�ڴ�����
 *	proHandle		[IN]���̾������OpenProcess���
 *	baseAddr		[IN]32λ�ڴ��ַ
 *	offSetList		[IN]ƫ�����б�offSetList[0] ��ʾ��һ��ƫ�ƣ�offSetList[1]��ʾ�ڶ���ƫ��....
 *	readLen			[IN]��Ҫ��ȡ���ڴ泤��
 *  OutBuffer		[OUT]���������
 *  BufferLen		[IN,OUT] �����ʾ ��������С�������ʾʵ�ʶ��������ݳ���
 *	��ע:  offSetListֱ����DWORD�ǲ��Ǹ�����Щ��
 */
int mem_ReadBlock(IN HANDLE proHandle,IN DWORD baseAddr,IN list<DWORD> &offSetList,IN DWORD readLen, OUT BYTE *OutBuffer,IN OUT ULONG* BufferLen);


/*
 *	��ȡ�ڴ�����
 *	proHandle		[IN]���̾������OpenProcess���
 *	baseAddr		[IN]32λ�ڴ��ַ
 *	offSetList		[IN]ƫ�����б�offSetList[0] ��ʾ��һ��ƫ�ƣ�offSetList[1]��ʾ�ڶ���ƫ��....
 *	WriteLen		[IN]��Ҫд����ڴ泤��
 *  InBuffer		[OUT]���������
 *  WrittenLen		[OUT]��ʾʵ��д������ݳ���
 *	��ע: 
 */
int mem_WriteBlock(IN HANDLE proHandle,IN DWORD baseAddr,IN list<DWORD> &offSetList,IN DWORD WriteLen, IN BYTE *InBuffer,OUT ULONG* WrittenLen);



int  mem_GetProcessAddr(DWORD dwPID, DWORD& baseAddr);