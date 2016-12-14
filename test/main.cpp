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

static void test_encrypt();
static void test_decrypt();
int main(int argc, const char * argv[]) {
    test_encrypt();
    test_decrypt();
    
    return 0;
}

void test_encrypt(){
    //Get the block/key length from user
    //Get the block/key length from user
    /*bool check = false;
     while(!check) {
     printf("Enter the key length/block length : ");
     scanf("%d",&keyLength);
     if(keyLength==128||keyLength==192||keyLength==256)
     check = true;
     }*/
    keyLength=128;
    
    //calculating the number of words from key length
    totalWords = keyLength/32;
    //calculating the number of rounds
    totalRounds = totalWords + 6;
    
    //get the plain text from user (for testing purpose taking readymade values) - 128 bit
    unsigned char keyTemp[16] = {0x00  ,0x01  ,0x02  ,0x03  ,0x04  ,0x05  ,0x06  ,0x07  ,0x08  ,0x09  ,0x0a  ,0x0b  ,0x0c  ,0x0d  ,0x0e  ,0x0f};
    unsigned char textTemp[16]= {0x00  ,0x11  ,0x22  ,0x33  ,0x44  ,0x55  ,0x66  ,0x77  ,0x88  ,0x99  ,0xaa  ,0xbb  ,0xcc  ,0xdd  ,0xee  ,0xff};
    unsigned char output[16];
    
    result = encrypt_block(keyTemp, textTemp, output);
    //output the input
    printf("\nPlain Text -------------------------\n");
    for(int i=0;i<totalWords*4;i++)
    {
        printf("%02x ",input[i]);
    }
    printf("\n");
    
    //output the result
    printf("\nEncryted Text -------------------------\n");
    for(int i=0;i<totalWords*4;i++)
    {
        printf("%02x ",result[i]);
    }
    printf("\n");
    
    //output the result
    printf("\nRoundKey -------------------------\n");
    for(int i=0;i<240;i++)
    {
        printf("%02x ",roundKey[i]);
    }
    printf("\n");
}

void test_decrypt(){
    gettimeofday(&start, NULL);
    
    //Get the block/key length from user
    /*bool check = false;
     while(!check) {
     printf("Enter the key length/block length : ");
     scanf("%d",&keyLength);
     if(keyLength==128||keyLength==192||keyLength==256)
     check = true;
     }*/
    keyLength=128;
    
    //calculating the number of words from key length
    totalWords = keyLength/32;
    //calculating the number of rounds
    totalRounds = totalWords + 6;
    
    //get the cipher text (for testing purpose taking readymade values) - 128 bit
    unsigned char keyTemp[16] = {0x00  ,0x01  ,0x02  ,0x03  ,0x04  ,0x05  ,0x06  ,0x07  ,0x08  ,0x09  ,0x0a  ,0x0b  ,0x0c  ,0x0d  ,0x0e  ,0x0f};
    unsigned char textTemp[16]= {0x69  ,0xc4  ,0xe0  ,0xd8  ,0x6a  ,0x7b  ,0x04  ,0x30  ,0xd8  ,0xcd  ,0xb7  ,0x80  ,0x70  ,0xb4  ,0xc5  ,0x5a};
    
    unsigned char output[16];
    
    
    result = decrypt_block(keyTemp, textTemp, output);
    //output the input
    printf("\nCipher Text -------------------------\n");
    for(int i=0;i<totalWords*4;i++)
    {
        printf("%02x ",input[i]);
    }
    printf("\n");
    
    //output the result
    printf("\nDecrypted Text -------------------------\n");
    for(int i=0;i<totalWords*4;i++)
    {
        printf("%02x ",result[i]);
    }
    printf("\n");
    
    //output the result
    printf("\nRoundKey -------------------------\n");
    for(int i=0;i<240;i++)
    {
        printf("%02x ",roundKey[i]);
    }
    printf("\n");
    gettimeofday(&end, NULL);
    float delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
    printf("Total Time: %f",delta);
    printf("\n\n\n");
}
