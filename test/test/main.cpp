#include "stdio.h"
#include "string.h"
#include "stdlib.h"


// char*replace(char*src, char*sub, char*dst)
// {
// 	//��¼��ǰָ��λ��
// 	int pos =0;
// 	//��¼ƫ��
// 
// 	int offset =0;
// 	//�ַ�������
// 	int srcLen, subLen, dstLen;
// 	//��������
// 
// 	char*pRet = NULL;
// 
// 
// 	//��ø��ַ�������
// 
// 	srcLen = strlen(src);
// 	subLen = strlen(sub);
// 	dstLen = strlen(dst);
// 	//�����滻����ַ�������������dst�滻sub������Ӧ����srclen-sublen+dstlen��+1����'\0'λ��
// 	pRet = (char*)malloc(srcLen + dstLen - subLen +1);//(�ⲿ�Ƿ�ÿռ�)if (NULL != pRet)
// 	{
// 		//strstr����sub�ַ������ֵ�ָ�롣��ָ���ȥsrc��ַ���õ����λ��
// 		pos = strstr(src, sub) - src;
// 		//����src�ַ��������׵�ַ��ʼ��pos���ַ���
// 		memcpy(pRet, src, pos);
// 		//����ƫ��λ�õ�pos
// 		offset += pos;
// 		//����dst�����������С�
// 		memcpy(pRet + offset, dst, dstLen);
// 		//���¶�λƫ��
// 		offset += dstLen;
// 		//����src�У�sub�ַ���������ַ�����pRet��
// 		memcpy(pRet + offset, src + pos + subLen, srcLen - pos - subLen);
// 		//���¶�λƫ��
// 		offset += srcLen - pos - subLen;
// 		//�������ַ�����β���'\0'
// 		*(pRet + offset) ='\0';
// 	}
// 	//�����¹�����ַ���
// 	return pRet;
// }

#define MAX_MSG_LENGTH 512

// �滻�ַ����������ַ���Ϊָ���ַ���
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

		// ������һ���滻�����һ���滻���м���ַ���  
		nLen = p1 - psource;  
		memcpy(presult, psource, nLen);  

		// ������Ҫ�滻���ַ���  
		memcpy(presult + nLen,p_repstr,repstr_leng);  

		psource = p1 + searchstr_leng;  
		presult = presult + nLen + repstr_leng;  
	}while(p1);  

	return 0;  
}

int main(void){
	char str[]="12345'ab'cd'e";
	if(strchr(str,'\''))//Ҫ��\����д��'\''������д��'''
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