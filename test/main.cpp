//
//  main.cpp
//  AES
//
//  Created by Madhuri Motoori on 12/14/16.
//  Copyright © 2016 Madhuri Motoori. All rights reserved.
//

#include <iostream>
#include "../AESEncrytionSequential/aesencryption.cpp"
#include "../AESDecryptionSequential/aesdecryption.cpp"
#include <omp.h>
/*

int main(int argc, const char * argv[]) {
    double time_initial = omp_get_wtime();
    unsigned char* encrypt_result;
    FILE *fw = fopen("decrypted.txt","w");
    keyLength=128;
    //calculating the number of words from key length
    totalWords = keyLength/32;
    //calculating the number of rounds
    totalRounds = totalWords + 6;
    //get the plain text from user (for testing purpose taking readymade values) - 128 bit
    unsigned char keyTemp[16] = {0x00  ,0x01  ,0x02  ,0x03  ,0x04  ,0x05  ,0x06  ,0x07  ,0x08  ,0x09  ,0x0a  ,0x0b  ,0x0c  ,0x0d  ,0x0e  ,0x0f};
    unsigned char output[16];
    
    int filesize,fcount = 0;
    FILE *ft = fopen("data.txt","r"); //Input file data
    fseek(ft,0L,SEEK_END);
    filesize = ftell(ft);
    rewind(ft);
    unsigned char textTemp[16];
    
    for(;fcount < filesize-1; fcount += 16) {
        int count =0;
        unsigned char c=0x00000000;
        void *t = &c;
        int sz;
        
        for (int cn=0;cn<16;cn++) {
            sz = fread(t,1,1,ft);
            unsigned char temp = sz?c:0x00;
            textTemp[count] = temp;
            count++;
            printf(" %c ", temp);
            c=0x00000000;
        }
        
        
        encrypt_result = encrypt_block(keyTemp, textTemp, output);
        result = decrypt_block(keyTemp, encrypt_result, output);

        void* l;
        for(int i=0;i<16;i++) {
            l = &result[i];
            fwrite(l,1,1,fw);
        }
        printf("Out of the for loop");
    }
    printf("FileSize %d", filesize);
    
    fclose(ft);
    fclose(fw);
    double time_final = omp_get_wtime();
    printf("\nTime taken is: (%f)\n" , time_final - time_initial);

    return 0;
}
*/

