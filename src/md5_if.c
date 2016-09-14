/*******************************************************************************
 *               Copyright (C) 2016, Huawei Tech. Co., Ltd.
 *                      ALL RIGHTS RESERVED
 *******************************************************************************/

/** @defgroup md5_if.c

 *  @author  Claud
 *  @version 1.0
 *  @date    2016/9/12 \n

 *  history:\n
 *          1. 2016/9/12, Claud, create this file\n\n
 *
 *
 * @{
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "os_def.h"
#include "md5.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#define CIPHER_STRING 	"+86755GYENNO"

static MD5_CTX mdContext;

char *dump_md5(int md5_size)
{
    char *file_md5;
	int i;
    
	file_md5 = (char *)malloc((md5_size + 1) * sizeof(char));
	if (file_md5 == NULL) {
		fprintf(stderr, "malloc failed.\n");
		return NULL;
	}
	memset(file_md5, 0, (md5_size + 1));

	if (md5_size == 4) {
		for (i=7; i<9; i++) {
			sprintf(&file_md5[(i-7)*2], "%02X", mdContext.digest[i]);
		}
	}
	else if (md5_size == 8) {
		for (i=6; i<10; i++) {
			sprintf(&file_md5[(i-6)*2], "%02X", mdContext.digest[i]);
		}
	}
	else if (md5_size == 16) {
		for (i=4; i<12; i++) {
			sprintf(&file_md5[(i-4)*2], "%02X", mdContext.digest[i]);
		}
	}
	else if (md5_size == 32) {
		for(i=0; i<16; i++) {
			sprintf(&file_md5[i*2], "%02X", mdContext.digest[i]);
		}
	}
	else {
		free(file_md5);
		return NULL;
	}

	return file_md5;
}


char *md5_file (char *path, int md5_size)
{
	FILE *fp = NULL;
	int bytes;
	unsigned char data[1024];	
    
	MD5Init (&mdContext); 
    fp = fopen (path, "rb");
	if (fp == NULL) {
		fprintf (stderr, "fopen %s failed\n", path);
		return NULL;
	}
	while ((bytes = fread (data, 1, 1024, fp)) != 0) {
		MD5Update (&mdContext, data, bytes);
	}
	MD5Final (&mdContext);
    fclose (fp);
    return dump_md5(md5_size);
}

char *md5_text (char *buf, int md5_size)
{
    MD5Init (&mdContext); 
	MD5Update (&mdContext, buf, strlen(buf));
	MD5Final (&mdContext);
    return dump_md5(md5_size);
}

char *get_string_cipher(char *string)
{
    #define CIPHER_SIZE 4
    char *md5andcipher = NULL;
    int i;
        
    md5andcipher = (char *)malloc(strlen(string) + (CIPHER_SIZE + 1) * sizeof(char));
    if (md5andcipher == NULL) {
        fprintf(stderr, "malloc failed.\n");
        return NULL;
    }
    memset(md5andcipher, 0, (CIPHER_SIZE + 1));    

    MD5Init (&mdContext); 
	MD5Update (&mdContext, string, strlen(string));
    MD5Update (&mdContext, CIPHER_STRING, strlen(CIPHER_STRING));
	MD5Final (&mdContext);
      
    strncpy(md5andcipher, string, strlen(string));
    for (i=7; i<9; i++) {
		sprintf(&md5andcipher[strlen(string) + (i-7)*2], "%02X", mdContext.digest[i]);
	}    
    return md5andcipher;
}



#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */




/** @}*/
