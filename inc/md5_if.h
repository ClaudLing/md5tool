/*******************************************************************************
 *               Copyright (C) 2016, Huawei Tech. Co., Ltd.
 *                      ALL RIGHTS RESERVED
 *******************************************************************************/

/** @defgroup md5_if.h

 *  @author  Claud
 *  @version 1.0
 *  @date    2016/9/12 \n

 *  history:\n
 *          1. 2016/9/12, Claud, create this file\n\n
 *
 *
 * @{
 */


#ifndef __MD5_IF_H__ 
#define __MD5_IF_H__ 



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */

#define MODE_UNDEF		0
#define MODE_FILE		1
#define MODE_TEXT		2
#define MODE_CIPHER		3

char *md5_file (char *path, int md5_size);
char *md5_text (char *buf, int md5_size);
int get_string_cipher(char *instr, int inlen, char *outstr, int *outlen);


#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


#endif  /* __MD5_IF_H__ */

/** @}*/
