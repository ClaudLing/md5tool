#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "os_def.h"
#include "md5.h"
#include "md5_if.h"

int main(int argc, char *argv[])
{
	char *md5 = NULL;
	s32 opt = 0;
    u8 mode = MODE_UNDEF;
    u8 scv_size = 4;
    s8 input[128] = {0};
    
	while((opt = getopt(argc,argv,"f:t:s:c")) != -1) {
        switch(opt) {
        case 'c':    
            mode = MODE_CIPHER;
            break;
        case 'f':    
            strncpy(input, optarg, strlen(optarg));
            printf("file: %s\n", input);
            mode = MODE_FILE;
            break;
        case 't':    
            strncpy(input, optarg, strlen(optarg));        
        	printf("text: %s %d\n", input, (int)strlen(optarg));
            mode = MODE_TEXT;
            break;
        case 's':    
            scv_size = atol(optarg);
            if ((4 != scv_size) && (8 != scv_size) 
                && (16 != scv_size) && (32 != scv_size)) {
                printf("MD5 size shoule be 4,8,16,32\n");;
				exit(0);
            }
            break;
        default:
			printf("Invalid parameter!\n");;
			exit(0);
        }
    }    
    if (MODE_UNDEF == mode) {
        printf("Invalid parameter!\n");;
		exit(0);
    }  
    if (MODE_FILE == mode) {
		md5 = md5_file(input, scv_size);
		printf("MD5 %d: %s\n", scv_size, md5);
		free(md5);
    }
    else if (MODE_TEXT == mode) {
        md5 = md5_text(input, scv_size);
		printf("MD5 %d: %s\n", scv_size, md5);
		free(md5);
    }
    else if (MODE_CIPHER == mode){
		md5 = get_string_cipher(input);
	    printf("Res: %s\n", md5);
	    free(md5);
    }
	return 0;
}