#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "serialize.h"

/* Unpack the given packet into the buffer unpacked.  You can assume
 * that packed points to a packet buffer large enough to hold the
 * packet described therein, but you cannot assume that the packet is
 * otherwise valid.  You can assume that unpacked points to a character
 * buffer large enough to store the unpacked packet, if it is a valid
 * packet.
 *
 * Returns the packet type that was unpacked, or -1 if it is invalid.
 */
int unpack(char *unpacked, void *packed) {
    if(*(int*)packed == STATUS){
         packed = packed + 4;
        int count = 0;
        while(*(char *)packed != '\0'){
            unpacked[count] = *(char *)packed;
            count++;
            packed++;
        }
        int padding = 16 - count;
        packed = packed + padding;
        unpacked[count] = ' ';
        count++;

        
        int a = *(int *)packed;

        packed = packed + 8;
        packed = packed + 8;
        
        for(int i = 0; i!=a;i++){
            unpacked[count] = *(char *)packed;
            packed++;
            count++;
        }
        unpacked[count] = '\0';
    }
    if(*(int*)packed == LABELED){
        packed = packed + 4;
        int count = 0;
        while(*(char *)packed != '\0'){
            unpacked[count] = *(char *)packed;
            count++;
            packed++;
        }
        int padding = 16 - count;
        packed = packed + padding;
        unpacked[count] = ':';
        count++;
        unpacked[count] = ' ';
        count++;
        unpacked[count] = '@';
        count++;

        int m = *(int *)packed;
        packed = packed +8;
        int t = *(int *)packed;
        packed = packed + 8;
        packed = packed + 8;

        for(int i = 0; i!=m;i++){
            packed++;
        }
        for(int i = 0; i!=t;i++){
            unpacked[count] = *(char *)packed;
            packed++;
            count++;
        }
        unpacked[count] = ' ';
        count++;
        
        for(int i = 0; i!=t;i++){
            packed--;
        }
        for(int i = 0; i!=m;i++){
            packed--;
        }
        for(int i = 0; i!=m;i++){
            unpacked[count] = *(char *)packed;
            packed++;
            count++;
        }
        unpacked[count] = '\0';
    }

    if(*(int*)packed == MESSAGE){
        packed = packed + 4;
        int count = 0;
        while(*(char *)packed != '\0'){
            unpacked[count] = *(char *)packed;
            count++;
            packed++;
        }
        int padding = 16 - count;
        packed = packed + padding;
        unpacked[count] = ':';
        count++;
        unpacked[count] = ' ';
        count++;

        
        int a = *(int *)packed;

        packed = packed + 8;
        packed = packed + 8;
        
        for(int i = 0; i!=a;i++){
            unpacked[count] = *(char *)packed;
            packed++;
            count++;
        }
        unpacked[count] = '\0';
    }
    return 0;
}

/* Unpack the given packed packet into the given statistics structure.
 * You can assume that packed points to a packet buffer large enough to
 * hold the statistics packet, but you cannot assume that it is
 * otherwise valid.  You can assume that statistics points to a
 * statistics structure.
 *
 * Returns the packet type that was unpacked, or -1 if it is invalid.
 */
int unpack_statistics(struct statistics *statistics, void *packed) {
    if(*(int *)packed != STATISTICS){
        return -1;
    }
    packed = packed + 4;
    for(int i=0;i<16;i++){
        statistics->sender[i] = *(char *)packed;
        packed++;
    }
    statistics->sender[16]='\0';
    int pd2 = 0;
    int count2 = 0;
    while(*(char *)packed != '\0'){
        statistics->most_active[count2] = *(char *)packed;
        count2++;
        pd2++;
        packed++;
    }
    statistics->most_active[count2] = '\0';
    int padding2 = 16 - pd2;
    packed = packed + padding2;

    statistics->most_active_count = *(int *)packed;
    if(statistics->most_active_count<0){
        return -1;
    }

    packed = packed + 4;

    statistics->invalid_count = *(long *)packed;
    if(statistics->invalid_count<0){
        return -1;
    }
    packed = packed + 4;
    
    statistics->refresh_count = *(long *)packed;
    if(statistics->refresh_count<0){
        return -1;
    }
    packed = packed + 4;
    
    statistics->messages_count = *(int *)packed;
    if(statistics->messages_count<0){
        return -1;
    }

    return STATISTICS;
}
