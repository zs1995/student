#include "stdio.h"
#include "string.h"
#include "stdlib.h"


// char*replace(char*src, char*sub, char*dst)
// {
// 	//记录当前指针位置
// 	int pos =0;
// 	//记录偏移
// 
// 	int offset =0;
// 	//字符串长度
// 	int srcLen, subLen, dstLen;
// 	//返回内容
// 
// 	char*pRet = NULL;
// 
// 
// 	//求得各字符串长度
// 
// 	srcLen = strlen(src);
// 	subLen = strlen(sub);
// 	dstLen = strlen(dst);
// 	//申请替换后的字符串缓冲区。用dst替换sub，所以应该是srclen-sublen+dstlen，+1流出'\0'位置
// 	pRet = (char*)malloc(srcLen + dstLen - subLen +1);//(外部是否该空间)if (NULL != pRet)
// 	{
// 		//strstr查找sub字符串出现的指针。该指针减去src地址。得到相对位置
// 		pos = strstr(src, sub) - src;
// 		//拷贝src字符串，从首地址开始，pos个字符。
// 		memcpy(pRet, src, pos);
// 		//增加偏移位置到pos
// 		offset += pos;
// 		//拷贝dst到返回内容中。
// 		memcpy(pRet + offset, dst, dstLen);
// 		//重新定位偏移
// 		offset += dstLen;
// 		//拷贝src中，sub字符串后面的字符串到pRet中
// 		memcpy(pRet + offset, src + pos + subLen, srcLen - pos - subLen);
// 		//重新定位偏移
// 		offset += srcLen - pos - subLen;
// 		//最后添加字符串结尾标记'\0'
// 		*(pRet + offset) ='\0';
// 	}
// 	//返回新构造的字符串
// 	return pRet;
// }

#define MAX_MSG_LENGTH 512

// 替换字符串中特征字符串为指定字符串
// int ReplaceStr(char *sSrc, char *sMatchStr, char *sReplaceStr)
// {
// 	int  StringLen;
// 	char caNewString[MAX_MSG_LENGTH];
// 
// 	char *FindPos = strstr(sSrc, sMatchStr);
// 	if( (!FindPos) || (!sMatchStr) )
// 		return -1;
// 
// 	while(FindPos)
// 	{
// 		memset(caNewString, 0, sizeof(caNewString));
// 		StringLen = FindPos - sSrc;
// 		strncpy(caNewString, sSrc, StringLen);
// 		strcat(caNewString, sReplaceStr);
// 		strcat(caNewString, FindPos + strlen(sMatchStr));
// 		strcpy(sSrc, caNewString);
// 
// 		FindPos = strstr(sSrc, sMatchStr);
// 	}
// 
// 	return 0;
// } 


int str_replace(char *p_result,char* p_source,char* p_seach,char *p_repstr)  
{  
	int c = 0;  
	int repstr_leng = 0;  
	int searchstr_leng = 0;  

	char *p1;  
	char *presult = p_result;  
	char *psource = p_source;  
	char *prep = p_repstr;  
	char *pseach = p_seach;  
	int nLen = 0;  

	repstr_leng = strlen(prep);  
	searchstr_leng = strlen(pseach);  

	do{   
		p1 = strstr(psource,p_seach);  

		if (p1 == 0)  
		{  
			strcpy(presult,psource);  
			return -1;  
		}  

		// 拷贝上一个替换点和下一个替换点中间的字符串  
		nLen = p1 - psource;  
		memcpy(presult, psource, nLen);  

		// 拷贝需要替换的字符串  
		memcpy(presult + nLen,p_repstr,repstr_leng);  

		psource = p1 + searchstr_leng;  
		presult = presult + nLen + repstr_leng;  
	}while(p1);  

	return 0;  
}

int main(void){
	char str[]="12345'ab'cd'e";
	if(strchr(str,'\''))//要用\引导写成'\''而不能写成'''
	{
		printf("There is a '\'' in the \"str\".\n");
		int n = 0;
		char aa[1024];
		memset(aa,0,1024);
		char b[2] = "'";
		char b1[3] = "''";
		n = str_replace(aa,str,b,b1);
		printf("%s\n",aa);
	}
	else 
		printf("There is not any '\'' in the \"str\".\n");
	getchar();
	return 0;
}