
#define ASSERT_EQUAL_REG(p,val) if((p)==val) \
{ \
	MessageBox("注册快捷方式失败！",NULL,MB_OK|MB_ICONERROR); \
	return FALSE; \
} 


#define ASSERT_HANDLE_NULL(handle) if((handle)==NULL) \
{ \
	MessageBox("连接目标进程失败",NULL,MB_OK|MB_ICONERROR);	\
	return FALSE; \
} 


int HexStrTobyte(char *str, unsigned char *out, unsigned int *outlen);

int  byteToHexStr(unsigned char byte_arr[],int arr_len, char* HexStr,int* HexStrLen);

int Reverse4Byte(BYTE* _4Byte);

int IntTo4Bytes(IN int iValue ,OUT BYTE* _4Byte);

int BytesToInt(IN BYTE* _4Byte ,OUT int &iValue);