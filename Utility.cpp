
#include "stdafx.h"
#include "Utility.h"

int HexStrTobyte(char *str, unsigned char *out, unsigned int *outlen){
	char *p = str;
	char high = 0, low = 0;
	int tmplen = strlen(p), cnt = 0;
	tmplen = strlen(p);
	while(cnt < (tmplen / 2)){
		high = ((*p > '9') && ((*p <= 'F') || (*p <= 'f'))) ? *p - 48 - 7 : *p - 48;
		low = (*(++ p) > '9' && ((*p <= 'F') || (*p <= 'f'))) ? *(p) - 48 - 7 : *(p) - 48;
		out[cnt] = ((high & 0x0f) << 4 | (low & 0x0f));
		p ++;
		cnt ++;
	}
	if(tmplen % 2 != 0) out[cnt] = ((*p > '9') && ((*p <= 'F') || (*p <= 'f'))) ? *p - 48 - 7 : *p - 48;

	if(outlen != NULL) *outlen = tmplen / 2 + tmplen % 2;
	return tmplen / 2 + tmplen % 2;
}



int  byteToHexStr(unsigned char byte_arr[],int arr_len, char* HexStr,int* HexStrLen){
	int  i,index = 0;
	for (i=0;i<arr_len;i++){
		char hex1;
		char hex2;
		int value=byte_arr[i];
		int v1=value/16;
		int v2=value % 16;
		if (v1>=0&&v1<=9)
			hex1=(char)(48+v1);
		else
			hex1=(char)(55+v1);
		if (v2>=0&&v2<=9)
			hex2=(char)(48+v2);
		else
			hex2=(char)(55+v2);
		if(*HexStrLen<=i){
			return -1;
		}
		HexStr[index++] = hex1;
		HexStr[index++] = hex2;
	}
	*HexStrLen = index;
	return 0 ;
}



int Reverse4Byte(BYTE* _4Byte){
	_4Byte[0] ^= _4Byte[3];
	_4Byte[3] ^= _4Byte[0];
	_4Byte[0] ^= _4Byte[3];
	_4Byte[1] ^= _4Byte[2];
	_4Byte[2] ^= _4Byte[1];
	_4Byte[1] ^= _4Byte[2];
	return 0;
}