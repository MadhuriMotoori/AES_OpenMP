//
//  main.cpp
//  AESDecrytionSequential
//
//  Copyright (c) 2016 TusharaSankaranArakkan. All rights reserved.
//

#include <iostream>
#include <sys/time.h>
struct timeval start, end;

int getSBoxInvert(int num)
{
    int rsbox[256] =
    { 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb
        , 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb
        , 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e
        , 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25
        , 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92
        , 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84
        , 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06
        , 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b
        , 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73
        , 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e
        , 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b
        , 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4
        , 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f
        , 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef
        , 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61
        , 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };
    
    return rsbox[num];
}


void addRoundKeyInverse(int roundNo,unsigned char inputStateArray[4][4]) {
    int val = roundNo * totalColumn * 4;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            int indexVal = val + i * totalColumn + j;
            inputStateArray[j][i] = inputStateArray[j][i] ^ roundKey[indexVal] ;
        }
    }
    
}
void byteSubstitutionInverse(unsigned char inputStateArray[4][4]) {
    for(int i=0;i<totalWords;i++) {
        for(int j=0;j<4;j++) {
            inputStateArray[i][j] = getSBoxInvert(inputStateArray[i][j]);
        }
    }
    
}
void rowShiftingInverse(unsigned char inputStateArray[4][4]) {
    
    //no changes to first row
    
    //circularly shifting second row by 1 bytes to right
    char temp=inputStateArray[1][3];
    inputStateArray[1][3]=inputStateArray[1][2];
    inputStateArray[1][2]=inputStateArray[1][1];
    inputStateArray[1][1]=inputStateArray[1][0];
    inputStateArray[1][0]=temp;
    
    //circularly shifting third row by 2 bytes to right
    temp=inputStateArray[2][0];
    inputStateArray[2][0]=inputStateArray[2][2];
    inputStateArray[2][2]=temp;
    temp=inputStateArray[2][1];
    inputStateArray[2][1]=inputStateArray[2][3];
    inputStateArray[2][3]=temp;
    
    //circularly shifting fourth row by 3 bytes to right
    temp=inputStateArray[3][0];
    inputStateArray[3][0]=inputStateArray[3][1];
    inputStateArray[3][1]=inputStateArray[3][2];
    inputStateArray[3][2]=inputStateArray[3][3];
    inputStateArray[3][3]=temp;
}

// xtime is a macro that finds the product of {02} and the argument to xtime modulo {1b}
#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))
// Multiplty is a macro used to multiply numbers in the field GF(2^8)
#define Multiply(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * xtime(x)) ^ ((y>>2 & 1) * xtime(xtime(x))) ^ ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^ ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))


void columnMixingInverse(unsigned char inputStateArray[4][4]) {
    int i;
    unsigned char a,b,c,d;
    for(i=0;i<4;i++)
    {
        a = inputStateArray[0][i];
        b = inputStateArray[1][i];
        c = inputStateArray[2][i];
        d = inputStateArray[3][i];
        inputStateArray[0][i] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09);
        inputStateArray[1][i] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
        inputStateArray[2][i] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
        inputStateArray[3][i] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e);
    }
    
}

void decrypt(unsigned char inputStateArray[4][4]) {

    //first step is to perform key expansion
    keyExpansion();
    //second step is the xor the input and last 4 words of the key schedule
    addRoundKeyInverse(totalRounds, inputStateArray);
    //third step is to start 10 rounds
    for(int i=totalRounds-1;i>=0;i--) {
        rowShiftingInverse(inputStateArray);
        byteSubstitutionInverse(inputStateArray);
        addRoundKeyInverse(i, inputStateArray);
        if(i!=0)
        columnMixingInverse(inputStateArray);
        
    }
    
}
/*
unsigned char* decrypt_block(unsigned char keyTemp[], unsigned char textTemp[], unsigned char output[], int blockcount){
    int blockcounter = blockcount * 16;
    for (int i=0;i< totalWords*4;++i)
    {
        key[i] = keyTemp[i];
        input[i] = textTemp[i];
    }
    
    //convert the 1D input to 2D input state array
    for(int i=0;i<totalWords;i++) {
        for(int j=0;j<4;j++) {
            inputStateArray[j][i] = textTemp[blockcounter];
            blockcounter++;
        }
    }
    
    
    printf("\nCipher Text U -------------------------\n");
    
    for(int i=0;i<totalWords;i++) {
        for(int j=0;j<4;j++) {
            
            printf("%02x ",  inputStateArray[j][i] );
            
        }
        
        printf("\n");
    }
    

    decrypt();
    
    printf("\nCipher Text U -------------------------\n");
    
    for(int i=0;i<totalWords;i++) {
        for(int j=0;j<4;j++) {
            
            printf("%02x ",  inputStateArray[j][i] );
            
        }
        
        printf("\n");
    }
    blockcounter = blockcount * 16;
    //converting the result into 1D
    for(int i=0;i<totalWords;i++) {
        for(int j=0;j<4;j++) {
            output[blockcounter] = inputStateArray[j][i] ;
        }
    }    
    return output;
}


int main(int argc, const char * argv[]) {
    FILE *fw = fopen("decrypted.txt","w");
    double time_initial = omp_get_wtime();
    unsigned char* decrypt_result;
    keyLength=128;
    //calculating the number of words from key length
    totalWords = keyLength/32;
    //calculating the number of rounds
    totalRounds = totalWords + 6;
    //get the plain text from user (for testing purpose taking readymade values) - 128 bit
    
    int filesize;
    FILE *ft = fopen("cipher.txt","r"); //Input file data
    fseek(ft,0L,SEEK_END);
    filesize = ftell(ft) - 1;
    rewind(ft);
    printf("FileSize %d", filesize);
    unsigned char textTemp[filesize];
    
    for(int fcount = 0;fcount < filesize; fcount += 1) {
        unsigned char c=0x00000000;
        void *t = &c;
        int sz;
        sz = fread(t,1,1,ft);
        unsigned char temp = sz?c:0x00;
        textTemp[fcount] = temp;
        // printf(" %c ", temp);
        c=0x00000000;
        
    }
    
    int total_blocks = (filesize / 16);
    printf("Total blocks %d", total_blocks);
    int block_count = 0;
    int blockcounter;
    int tid, tids;
    omp_set_num_threads(4);
    printf("Number of threads %d", omp_get_num_threads);
    unsigned char output[total_blocks][16];
    //input state array
    unsigned char inputStateArray[4][4];
    unsigned char result_final[total_blocks][16];
    int j;
    #pragma omp parallel private(inputStateArray, block_count, tid,tids, output) shared(textTemp, filesize, total_blocks, result_final)
    {
        block_count = tid = omp_get_thread_num();
        tids = omp_get_num_threads();
        
        printf("Number of thread %d %d", tids, tid);
        double begin_time = omp_get_wtime();
        //  printf("\nTime taken is: (%f)\n" , time_final);
        
        for(block_count = omp_get_thread_num(); block_count < total_blocks; block_count+=tids) {
            //blockcounter  = block_count * 16;
            
            createStateArray(block_count, filesize, textTemp, inputStateArray);
            decrypt(inputStateArray);
            createOutputArray(block_count, filesize, output, inputStateArray);
            // block_count += tids;
            
            //#pragma omp single
            //for(int i=0;i<total_blocks;i++) {
            for(int j=0;j<16;j++) {
                
                result_final[block_count][j] = output[block_count][j];
                //printf("%02x ",  output[block_count][j] );
                
            }
            
            // printf("\n");
        }
        
        
        double time_final = omp_get_wtime();
        printf("\nTime taken before(%f) after: (%f) sub: (%f)\n" , begin_time, time_final, time_final - begin_time);
    }
    fclose(ft);
    double over_time_final = omp_get_wtime();
    printf("\nTime taken is: (%f)\n" , over_time_final - time_initial);
    
    printf("\nOutput Text Outside -------------------------\n");
    void* l;
    for(int i=0;i<total_blocks;i++) {
        for(int j=0;j<16;j++) {
            
            //result_final[block_count][j] = output[block_count][j];
            // printf(" %02x ",  result_final[i][j] );
            
            l = &result_final[i][j];
            fwrite(l,1,1,fw);
            
        }
        
        printf("\n");
    }
    
    
    
    /*
     printf("\nCipher Text -------------------------\n");
     for(int i=0;i< filesize ;i++)
     {
     printf("%02x ",result[i]);
     }
     printf("\n");
     
     printf("\nCipher Text -------------------------\n");
     for(int i=16;i< 32 ;i++)
     {
     printf("%02x ",result[i]);
     }
     printf("\n");
     
     fclose(ft);
     double time_final = omp_get_wtime();
     printf("\nTime taken is: (%f)\n" , time_final - time_initial);
     //    result = decrypt_block(keyTemp, encrypt_result, output);
     /*  unsigned char decrypt_output[filesize];
     unsigned char* decrypt_result;
     block_count = 0;
     while(block_count < total_blocks) {
     //blockcounter  = block_count * 16;
     decrypt_result = decrypt_block(key, result, decrypt_output, block_count);
     block_count ++;
     }
     
     printf("\nNormal Text -------------------------\n");
     for(int i=0;i< filesize ;i++)
     {
     printf("%02x ",decrypt_result[i]);
     }
     printf("\n");
     
     void* l;
     for(int i=0;i<filesize;i++) {
     l = &decrypt_result[i];
     fwrite(l,1,1,fw);
     }
     printf("Out of the for loop");
    fclose(fw);
    
    return 0;
}
*/




