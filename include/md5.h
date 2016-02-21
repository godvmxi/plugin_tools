/*
 * Copyright (c) 2004,��ɽKSG
 * All rights reserved.
 * 
 * �ļ����: mysocket.h
 * �ļ���ʶ:
 * ժ    Ҫ: ����md5����
 * ��ǰ�汾: 1.0
 * ��    ��: chen.qian.jiang
 * ��ʼ����: 2004-08-13
 * �������: 
 * ����˵���� 
 * �޸�����        �汾��     �޸���          �޸�����
 * -----------------------------------------------
 * 2004/08/13      V1.0       ��ǭ��          ����
 */ 

#ifndef _MY_MD5__H
#define _MY_MD5__H

#ifdef _WIN32
#pragma pack(push, 1)
#else
#pragma pack(1)
#endif

#ifdef __cplusplus
extern "C" {
#endif




#pragma pack()

void md5_calc(unsigned char *output, unsigned char * input , int len);

#endif

#ifdef __cplusplus
}
#endif
