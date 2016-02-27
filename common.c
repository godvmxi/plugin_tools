#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_LENGTH (400)
#define VALUE_LENGTH (256)
#define KEY_LENGTH (50)
typedef struct item_t {
    char key[KEY_LENGTH];
    char value[VALUE_LENGTH];
}ITEM;

/*
 *去除字符串右端空格
 */
char *strtrimr(char *pstr)
{
    int i;
    i = strlen(pstr) - 1;
    while (isspace(pstr[i]) && (i >= 0))
        pstr[i--] = '\0';
    return pstr;
}
/*
 *去除字符串左端空格
 */
char *strtriml(char *pstr)
{
    int i = 0,j;
    j = strlen(pstr) - 1;
    while (isspace(pstr[i]) && (i <= j))
        i++;
    if (0<i)
        strcpy(pstr, &pstr[i]);
    return pstr;
}
/*
 *去除字符串两端空格
 */
char *strtrim(char *pstr)
{
    char *p;
    p = strtrimr(pstr);
    return strtriml(p);
}

/*
 *从配置文件的一行读出key或value,返回item指针
 *line--从配置文件读出的一行
 */
int  get_item_from_line(char *line,char split, ITEM *item)
{
    char *p = strtrim(line);
    int len = strlen(p);
    if(len <= 0){
        return 1;//空行
    }
    else if(p[0]=='#'){
        return 2;
    }else{
        char *p2 = strchr(p, split);
        *p2++ = '\0';
		memset(item,0,sizeof(ITEM));
        strncpy(item->key,p,KEY_LENGTH - 1);
        strncpy(item->value,p2,VALUE_LENGTH - 1);
    }
    return 0;//查询成功
}

int file_to_items(const char *file,char split, ITEM *items, int *num)
{
    FILE *fp;
    fp = fopen(file,"r");
    if(fp == NULL)
        return 1;
	char line[MAX_LENGTH];
	int i = 0;
	memset(line,0,MAX_LENGTH);
    while(fgets(line, MAX_LENGTH - 1, fp))
	{
		if(items == NULL) //获取有多少条目
		{
			++i;
			memset(line,0,MAX_LENGTH);
			continue;
		}
		if(*num == i) //获取前num条目
		{
			break;
		}
        if(get_item_from_line(line,split,&items[i]) == 0)
		{
			++i;
		}
		memset(line,0,MAX_LENGTH);
    }
    *num = i;
	
    fclose(fp);
	
    return 0;
}

/*
 *读取value
 */
int read_conf_value(const char *key,char *value,const char *file)
{
    char line[MAX_LENGTH];
    FILE *fp = NULL;
	ITEM item;
	int iret = -1;
    fp = fopen(file,"r");
    if(fp == NULL)
        return iret;//文件打开错误
	
	iret = 1;
	memset(line,0,MAX_LENGTH);
    while (fgets(line, MAX_LENGTH - 1, fp))
	{        
	    memset(&item, 0, sizeof(ITEM));
        if(get_item_from_line(line,':',&item) != 0)
		{
			memset(line,0,MAX_LENGTH);
			continue;
		}
		//printf("****%s:%s\n",item.key,item.value);
        if(strcmp(item.key,key) == 0){
			strcpy(value,item.value);
			iret = 0;
            break;
        }
		memset(line,0,MAX_LENGTH);
    }
	
	fclose(fp);
    return iret;//成功
}

int write_conf_value(const char *key,const char *value,const char *file)
{
    int num = 0;//存储从文件读取的有效数目
	ITEM *pitems = NULL;
	FILE *fp = NULL;	
	int i = 0;
	int bret = -1;
	
	file_to_items(file,':', NULL, &num);
	if(num > 0)
	{	
		pitems = (ITEM *)malloc(num * sizeof(ITEM));	
		if(pitems == NULL) return bret;
		memset(pitems,0,num * sizeof(ITEM));
		if(file_to_items(file,':', pitems, &num) != 0) 
		{	
			free(pitems);
			return bret;
		}
	}
	
	printf("read items finish,%d\n",num);
	
    //查找要修改的项
    for( i=0; i < num; ++i)
	{
        if(strcmp(pitems[i].key, key) == 0)
		{
			memcpy(pitems[i].value, value, VALUE_LENGTH);
            break;
        }
    }
		
	printf("read items finish,%d\n",__LINE__);
	
    // 更新配置文件,应该有备份，下面的操作会将文件内容清除
    fp = fopen(file, "w");
    if(fp != NULL)
	{
		for(int j=0;j<num;j++){
			fprintf(fp,"%s:%s\n",pitems[j].key, pitems[j].value);
		}
		//新增项目会到这个地方，如果修改i!=num
		if(i == num)
		{
			fprintf(fp,"%s:%s\n",key, value);
		}
		bret = 0;
		fclose(fp);
	}

    //清除工作
    if(pitems != NULL)
		free(pitems);

    return bret;
}


unsigned char charToData(const char ch)  
{  
    switch(ch)  
    {  
    case '0': return 0;  
    case '1': return 1;  
    case '2': return 2;  
    case '3': return 3;  
    case '4': return 4;  
    case '5': return 5;  
    case '6': return 6;  
    case '7': return 7;  
    case '8': return 8;  
    case '9': return 9;  
    case 'a':   
    case 'A': return 10;  
    case 'b':   
    case 'B': return 11;  
    case 'c':  
    case 'C': return 12;  
    case 'd':   
    case 'D': return 13;  
    case 'e':   
    case 'E': return 14;  
    case 'f':  
    case 'F': return 15;      
    }  
    return 0;  
}  

void StrToMac(const char * szMac, unsigned char * pMac)  
{  
    const char * pTemp = szMac;  
    for (int i = 0;i < 6;++i)  
    {  
        pMac[i] = charToData(*pTemp++) * 16;  
        pMac[i] += charToData(*pTemp++);  
    }     
}

void bzero(void *s, int n)
{
	if(s == NULL || n == 0) return;
	memset(s,0,n);
}