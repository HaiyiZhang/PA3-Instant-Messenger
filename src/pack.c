#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "serialize.h"

#define UBITname "haiyizha"

/* Pack the user input provided in input into the appropriate message
 * type in the space provided by packed.  You can assume that input is a
 * NUL-terminated string, and that packed is a buffer of size
 * PACKET_SIZE.
 *
 * Returns the packet type for valid input, or -1 for invalid input.
 */
int pack(void *packed, char *input) {
    void *a = packed;
    int length = 0;
    for(int i=0; input[i]!='\0';i++){
        length = length + 1;
    }

    if(length == 0){
        return -1;
    }
    //STATUS
    if(input[0] == '/'&& input[1]=='m'&&input[2]=='e'&&input[3]==' '){
        int nonspace = 0;
        int count = 0;
        int Slength = 0;
        for(int i = 4; input[i]!='\0';i++){
            if(input[i] != ' '){
                nonspace++;
            }
        }
        if(nonspace == 0){
            return -1;
        }
        for(int i = 4;input[i]!='\0';i++){
            count++;
            if(input[i] != ' '){
                break;
            }
        }
        
        for(int i=count+3;input[i] != '\0';i++){
            Slength++;
        }
        
        *(int *)packed = STATUS;

        packed = packed + 4;
        for(int i = 0;i<8;i++){
            *(char *)packed = UBITname[i];
            packed++;
        }
        for(int i = 0;i<8;i++){
            *(char *)packed = '\0';
            packed++;
        }

        *(size_t *)packed = Slength;
        packed = packed + 8;

        *(size_t *)packed = 0;
        packed = packed + 8;

        for(int i = count+3;input[i]!='\0';i++){
            *(char *)packed = input[i];
            packed++;
        }

        packed = a;
        return STATUS;
    }

    //LABELED
    else if(input[0] == '@'){
        int namelength = 0;
        int messagelength = 0;
        int nonspace = 0;
        for(int i =0; input[i]!='\0';i++){
            if(input[i] != ' '){
                nonspace++;
            }
        }
        if(nonspace == 0){
            return -1;
        }
        for(int i=1;input[i] != ' ';i++){
            namelength++;
        }
        for(int i=2+namelength;input[i] != '\0';i++){
            messagelength++;
        }

        *(int *)packed = LABELED;

        packed = packed+4;
        for(int i=0;i<8;i++){
            *(char *)packed = UBITname[i];
            packed++;
        }
        for(int i=0;i<8;i++){
            *(char *)packed = '\0';
            packed++;
        }

        *(size_t *)packed = messagelength;
        packed = packed + 8;

        *(size_t *)packed = namelength;
        packed = packed + 8;

        *(size_t *)packed = 0;
        packed = packed + 8;
        
        for(int i=2+namelength;input[i] != '\0';i++){
            *(char *)packed = input[i];
            packed++;
        }

        for(int i=1;input[i] != ' ';i++){
            *(char *)packed = input[i];
            packed++;
        }

        packed = a;
        return LABELED;
    }

    //STATISTICS
    else if(input[0] == '/'&& input[1]=='s'&&input[2]=='t'&&input[3]=='a'&& input[4]=='t'&&input[5]=='s'&&length==6){
        *(int *)packed = STATISTICS;
        packed = packed + 4;

        for(int i = 0;i<8;i++){
            *(char *)packed = UBITname[i];
            packed++;
        }
        for(int i = 0;i<8;i++){
            *(char *)packed = '\0';
            packed++;
        }

        packed = a;
        return STATISTICS;
    }
    //MESSAGE
    else{
        int nonspace = 0;
        for(int i =0; input[i]!='\0';i++){
            if(input[i] != ' '){
                nonspace++;
            }
        }
        if(nonspace == 0){
            return -1;
        }
        *(int *)packed = MESSAGE;
        
        packed = packed + 4;
        for(int i = 0;i<8;i++){
            *(char *)packed = UBITname[i];
            packed++;
        }
        for(int i = 0;i<8;i++){
            *(char *)packed = '\0';
            packed++;
        }
        
        


        *(size_t *)packed = length;
        packed = packed + 8;
        
        *(size_t *)packed = 0;
        packed = packed + 8;
        
        for(int i = 0;i<length;i++){
            *(char *)packed = input[i];
            packed++;
        }

        packed = a;
        return MESSAGE;
    }
}

/* Create a refresh packet for the given message ID.  You can assume
 * that packed is a buffer of size PACKET_SIZE.
 *
 * You should start by implementing this method!
 *
 * Returns the packet type.
 */

//REFRESH
int pack_refresh(void *packed, int message_id) {
    *(int *)packed = REFRESH;
    
    packed = packed + 4;
    for(int i = 0;i<8;i++){
        *(char *)packed = UBITname[i];
        packed++;
    }
    for(int i = 0;i<8;i++){
        *(char *)packed = '\0';
        packed++;
    }
    *(int *)packed = message_id;
    return REFRESH;
}
