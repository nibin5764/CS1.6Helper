/*******************************************************/
/*****************�ڴ���ز���***************************/
/*******************************************************/

#include<list>
#include <string>
using namespace std;



/*
 *	��ȡ�ڴ�����
 *	proHandle		[IN]���̾������OpenProcess���
 *	baseAddr		[IN]32λ�ڴ��ַ
 *	offSetList		[IN]ƫ�����б�offSetList[0] ��ʾ��һ��ƫ�ƣ�offSetList[1]��ʾ�ڶ���ƫ��....
 *	readLen			[IN]��Ҫ��ȡ���ڴ泤��
 *  OutBuffer		[OUT]���������
 *  BufferLen		[IN,OUT] �����ʾ ��������С�������ʾʵ�ʶ��������ݳ���
 *	��ע: 
 */
int mem_ReadBlock(IN HANDLE proHandle,IN DWORD baseAddr,IN list<string> offSetList,IN DWORD readLen, OUT BYTE *OutBuffer,IN ULONG* BufferLen);


