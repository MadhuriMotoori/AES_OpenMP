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

int main(int argc, const char * argv[]) {
 //   FILE *fw = fopen("cipher.txt","w");
    double time_initial = omp_get_wtime();
    unsigned char* encrypt_result;
    keyLength=128;
    //calculating the number of words from key length
    totalWords = keyLength/32;
    //calculating the number of rounds
    totalRounds = totalWords + 6;
    //get the plain text from user (for testing purpose taking readymade values) - 128 bit
    
    int filesize;
    FILE *ft = fopen("data.txt","r"); //Input file data
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
    int block_count = 0;
    int blockcounter;
    int tid, tids;
    omp_set_num_threads(1);
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
            encrypt(inputStateArray);
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
        
        
       // double time_final = omp_get_wtime();
        //printf("\nTime taken before(%f) after: (%f) sub: (%f)\n" , begin_time, time_final, time_final - begin_time);
    }
    fclose(ft);
   // double over_time_final = omp_get_wtime();
    //printf("\nTime taken is: (%f)\n" , over_time_final - time_initial);
    
   // printf("\nOutput Text Outside -------------------------\n");

    for(int i=0;i<total_blocks;i++) {
        for(int j=0;j<16;j++) {
            
            //result_final[block_count][j] = output[block_count][j];
        //    printf(" %02x ",  result_final[i][j] );
            textTemp[16*i + j] = result_final[i][j];
      //      l = &result_final[i][j];
       //     fwrite(l,1,1,fw);
            
        }
        
      //  printf("\n");
    }
    
    
    

    unsigned char* decrypt_result;

    block_count = 0;

    unsigned char output_D[total_blocks][16];
    //input state array
   // unsigned char inputStateArray_D[4][4];
    unsigned char result_final_D[total_blocks][16];
    
    #pragma omp parallel private(inputStateArray, block_count, tid,tids, output_D) shared(textTemp, filesize, total_blocks, result_final_D)
    {
        block_count = tid = omp_get_thread_num();
        tids = omp_get_num_threads();
        
        printf("Number of thread %d %d", tids, tid);
       // double begin_time = omp_get_wtime();
        //  printf("\nTime taken is: (%f)\n" , time_final);
        
        for(block_count = omp_get_thread_num(); block_count < total_blocks; block_count+=tids) {
            
            createStateArray(block_count, filesize, textTemp, inputStateArray);
            decrypt(inputStateArray);
            createOutputArray(block_count, filesize, output_D, inputStateArray);
            
            //for(int i=0;i<total_blocks;i++) {
            for(int j=0;j<16;j++) {
                
                result_final_D[block_count][j] = output_D[block_count][j];
                //printf("%02x ",  output[block_count][j] );
                
            }
            
            // printf("\n");
        }
        
        
       // double time_final = omp_get_wtime();
        //printf("\nTime taken before(%f) after: (%f) sub: (%f)\n" , begin_time, time_final, time_final - begin_time);
    }
    fclose(ft);
    double over_time_final_D = omp_get_wtime();
    printf("\nTime taken is: (%f)\n" , over_time_final_D - time_initial);
    
   // printf("\nOutput Textfff Outside -------------------------\n");
    FILE *fw = fopen("decrypted.txt","w");
    void* m;
    for(int i=0;i<total_blocks;i++) {
        for(int j=0;j<16;j++) {
            
            //result_final[block_count][j] = output[block_count][j];
             //printf(" %02x ",  result_final_D[i][j] );
            
            m = &result_final_D[i][j];
            fwrite(m,1,1,fw);
            
        }
        
        //printf("\n");
    }
    
    fclose(fw);
     
     return 0;
     }
     


