
#define ASSERT_EQUAL_REG(p,val) if((p)==val) \
{ \
	MessageBox("×¢²á¿ì½Ý·½Ê½Ê§°Ü£¡",NULL,MB_OK|MB_ICONERROR); \
	return FALSE; \
} 

int HexStrTobyte(char *str, unsigned char *out, unsigned int *outlen);

int  byteToHexStr(unsigned char byte_arr[],int arr_len, char* HexStr,int* HexStrLen);

int Reverse4Byte(BYTE* _4Byte);