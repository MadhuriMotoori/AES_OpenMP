//
//  main.cpp
//  AES
//
//  
//  Copyright © 2016 . All rights reserved.
//

#include <iostream>
#include "../AESEncrytionSequential/aesencryption.cpp"
#include "../AESDecryptionSequential/aesdecryption.cpp"
#include <omp.h>
//#include <fstream>
//using namespace std;

static void generateTestData();
int main(int argc, const char * argv[]) {

//    generateTestData();

    double time_initial = omp_get_wtime();
    keyLength=128;
    //calculating the number of words from key length
    totalWords = keyLength/32;
    //calculating the number of rounds
    totalRounds = totalWords + 6;

    
    int filesize;
    FILE *ft = fopen(argv[1],"r"); //Input file data
    fseek(ft,0L,SEEK_END);
    filesize = ftell(ft) - 1;
    rewind(ft);
    unsigned char textTemp[filesize];
    
    for(int fcount = 0;fcount < filesize; fcount += 1) {
        unsigned char c=0x00000000;
        void *t = &c;
        int sz;
        sz = fread(t,1,1,ft);
        unsigned char temp = sz?c:0x00;
        textTemp[fcount] = temp;
        c=0x00000000;
        
    }
    
    int total_blocks = (filesize / 16);
    int block_count = 0;
    int blockcounter;
    int id, nids;
    omp_set_num_threads(atoi(argv[2]));
    unsigned char output[total_blocks][16];
    //input state array
    unsigned char inputStateArray[4][4];
    unsigned char result_final[total_blocks][16];
    int j;
    #pragma omp parallel private(inputStateArray, block_count, id, nids, output) shared(textTemp, filesize, total_blocks, result_final)
    {
        block_count = id = omp_get_thread_num();
        nids = omp_get_num_threads();
        
        for(block_count = omp_get_thread_num(); block_count < total_blocks; block_count+=nids) {
            createStateArray(block_count, filesize, textTemp, inputStateArray);
            encrypt(inputStateArray);
            createOutputArray(block_count, filesize, output, inputStateArray);

            for(int j=0;j<16;j++) {
                result_final[block_count][j] = output[block_count][j];
            }

        }
    }
    fclose(ft);

    //Adding cipher text to textTemp to decrypt
    for(int i=0;i<total_blocks;i++) {
        for(int j=0;j<16;j++) {
            textTemp[16*i + j] = result_final[i][j];
        }
    }

    block_count = 0;

    unsigned char output_decrypt[total_blocks][16];
    unsigned char result_final_decrypt[total_blocks][16];
    
    #pragma omp parallel private(inputStateArray, block_count, id,nids, output_decrypt) shared(textTemp, filesize, total_blocks, result_final_decrypt)
    {
        block_count = id = omp_get_thread_num();
        nids = omp_get_num_threads();
        
        for(block_count = omp_get_thread_num(); block_count < total_blocks; block_count+=nids) {
            
            createStateArray(block_count, filesize, textTemp, inputStateArray);
            decrypt(inputStateArray);
            createOutputArray(block_count, filesize, output_decrypt, inputStateArray);
            
            for(int j=0;j<16;j++) {
                result_final_decrypt[block_count][j] = output_decrypt[block_count][j];
            }
        }
    }

    double over_time_final = omp_get_wtime();
    printf("\nTime taken is: (%f)\n" , over_time_final - time_initial);
    
    //Writing output to decrypted file
    FILE *fw = fopen("decrypted.txt","w");
    void* m;
    for(int i=0;i<total_blocks;i++) {
        for(int j=0;j<16;j++) {
            m = &result_final_decrypt[i][j];
            fwrite(m,1,1,fw);
            
        }
    }
    
    fclose(fw);
    return 0;
}
/*
void generateTestData(){
    char testinputs[][5] = {"tush", "madh", "jaya", "abcd", "efgh", "tmmr", "baga", "umbe", "jita", "gaut"};
    
    ofstream myfile;
    myfile.open ("data_800KB.txt");
    
    int n = 50000 * 4;
    
    for(int i =0; i < n; i++ ){
        myfile << testinputs[(rand() % 10)];
    }
    
    myfile.close();
}
     */


