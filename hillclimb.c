//
//  hillclimb.c
//  hillclimb
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hillclimb.h"


char *bestinitkey;
char *K;
char *bestkey;

static inline int c2n(char c)
{
    return c == ' ' ? 0 : c-'a'+1;
}


static inline char n2c(int n)
{
    return n == 0 ? ' ' : n+'a'-1;
}

//Creates a bigram, which contains the matrix, frequency, and putative key
Bigram * bigram_construct(char *ciphertext, int key_length, char *p_key){
    int i,j;
    Bigram *B = malloc(sizeof(Bigram));
    if (!B) {
        perror("failed to malloc memory");
        return NULL;
    }
    //initialize everything in the matrix to 0
    for (i=0; i<27; i++) {
        for (j=0; j<27; j++) {
            B->bigram_array[i][j]=0;
        }
    }
    
    int cipher_in_int [strlen(ciphertext)]; //holds cipher in int representation
    
    for (int m =0; m<strlen(ciphertext); m++) {
        cipher_in_int[m]=c2n(ciphertext[m]);
    }

    
    for (i=0; i<strlen(ciphertext);i++) {
        j=i+1;
        B->bigram_array[cipher_in_int[i]][cipher_in_int[j]]++; //Add 1 to the bigram matrix
    }
    
    int frequency = 0;
    for (i=0; i<strlen(ciphertext);i++) {
        B->letter_frequency[i]=0;
        for (j=0; j<strlen(ciphertext);j++) {
            if (cipher_in_int[i]==cipher_in_int[j]) {
                frequency++;
            }
            
        }
        B->letter_frequency[cipher_in_int[i]]=frequency;
        frequency=0;
    }
    
    
    if (!p_key) {                           // need to take care of outerhill climb caller, this way the struct has some portion unitialized
        return B;
    }
    else {
    
    B->putative_key=malloc(sizeof(int)*key_length);
    if (!B->putative_key) {
        perror("can't malloc memory for keys");
        return NULL;
    }
    
    for (i=0; i<strlen(p_key); i++) {
        B->putative_key[i]=c2n(p_key[i]);
    }
    
    return B;
        
    }
}
//Destroy everything
void bigram_destroy(Collection c){
    for (int i = 0; i<c.count; i++) {
        free(c.ptr_to_bigram_list[i]);
    }
}

//print the bigram matrix
void bigram_display(Bigram *B){
    int i,j;
    printf("\n");
    for (i=0; i<27; i++) {
        for (j=0; j<27; j++) {
            if (j==26) {
                printf(" %d\n",B->bigram_array[i][j]);
                break;
            }
            printf(" %d",B->bigram_array[i][j]);
        }
    }
}

int innerhill_climb(Bigram *B){
    int innerscore = d(B,english_bigram);
    int *round_key;
    Bigram *round_D=NULL;
    for (int i=0; i<27; i++) {
        for (int j=0; j<27-i; j++) {
            round_key = B->putative_key;
            key_swap(round_key,j,i);
            Bigram *DD =NULL;
            DD = bigram_construct(decryptedtext, key_length, round_key);
            if (d(DD, english_bigram)<innerscore) {
                innerscore = d(DD, english_bigram);
                DD->putative_key=round_key;
                B=DD;
                
            }
        }
    }
    
    
    return innerscore;
}

//This function calculates how close a putative bigram matrix is to the expected english bigram matrix
//an be augmented to fit our dictionary better
//d(X, Y ) = Sum (i,j |xij − yij |)
//score == 0 is a perfect match, and the smaller the better
int d(Bigram *B, int **english_bigram){
    int i,j;
    int sum_total;
    for (i=1; i<27; i++) {
        for (j=0; j<26; j++) {
            sum_total = sum_total + abs(B->bigram_array[i][j+1]-english_bigram[i-1][j]);
        }
    }
    return sum_total;
}

//swap key elements kj and kj+i every round
void key_swap(int *round_key, int j, int i){
    int a,b;
    a = *(round_key+j*sizeof(int));
    b = *(round_key+(j+i)*sizeof(int));
    round_key[j]=b;
    round_key[j+i]=a;
}




int random_init_key(int *freq_distribution, char *ciphertext){
    int bestinitscore = 100000;
    int *cipher_alphabet=NULL;
    int i,j;
    int r = 0;
    int initscore;
    bestinitkey=NULL;
    char *putative_key=NULL;
    cipher_alphabet = malloc(sizeof(char)*27);              //free this
    if (!cipher_alphabet) {
        printf("can't allocate memory for cipher alphabet");
        return bestinitscore;
    }
    for (i=0; i<27; i++) {
        cipher_alphabet[i]=i;
    }
    while (r<500) {
        putative_key=create_key(freq_distribution);   //create initial putative key
        Bigram *Dp=NULL;
        Dp = bigram_construct(ciphertext, 27, putative_key);   // Needs to check the keylength!!!!!!!!!!!!!
        
        if (!Dp) {
            return bestinitscore;
        }
        initscore = innerhill_climb(Dp);
        if (initscore < bestinitscore) {
            bestinitscore = initscore;
            bestinitkey = putative_key;
        }
    
    }
    return bestinitscore;
}


//Borrowed from https://github.com/alimony/homophonic-cipher-attack/blob/master/homophonic_cipher_matrix.cpp
//modify later
char * create_key(int *freq_distribution){
    int i = 0;
    int j = 0;
    int k = 0;
    int m = 0;
    int temp_freq = 0;
    int no_repetitions = 0;
    int no_symbols = 0;
    char ch;
    char *putative_key=NULL;
    
    putative_key = malloc(sizeof(char)*27);  // this needs to be changed later !!!!!
    if (!putative_key) {
        perror("can't allocate memory for putative key");
        exit(EXIT_FAILURE);
    }
    
    no_symbols = freq_distribution[26];
    j = no_symbols;
    k = 0;
 
    while ((i < 27) && (j < 26)) {
        if (no_symbols > 0 && k <= 26) {
            if (freq_distribution[k] < 1) {
                k++;
            }
            no_repetitions = freq_distribution[k];
            temp_freq = eng_frequency[k] / no_repetitions;
            
            if (eng_frequency[i] < temp_freq) {
                for (m = 0; ((m < no_repetitions) && (i <27)); m++, i++) {
                    ch = 'a' + eng_rank[k];
                    if (ch >= 'a' && ch <= 'z') {
                        putative_key[i] = ch - 'a';
                    }
                }
                no_symbols--;
                k++;
                continue;
            }
        }
        ch = 'a' + eng_rank[j];
        if (ch >= 'a' && ch <= 'z') {
            putative_key[i] = ch - 'a';
        }
        i++;
        j++;
    }
    
    while ((i <27) && (no_symbols > 0)) {
        no_repetitions = freq_distribution[k];
        for (m = 0; ((m < no_repetitions) && (i < 27)); m++, i++) {
            ch = 'a' + eng_rank[k];
            if (ch >= 'a' && ch <= 'z') {
                putative_key[i] = ch - 'a';
            }
        }
        no_symbols--;
        k++;
    }
    
    return putative_key;
}
    
    
    
    
    


char * outerhill_climb(char *ciphertext, int key_length){
    int freq_distribution_index = 0;
    int freq_distribution[27];
    int score,bestscore;
    int i,j;
    
    Bigram *Dc = bigram_construct(ciphertext,key_length,NULL);
    for (i = 0; i < 27; i++) {
        freq_distribution[i] = initial_frequency_distribution[freq_distribution_index][i];
    }
    
    printf("inital frequency distribution:\n");
    for (i = 0; i < 27; i++) {
        printf("%d ",freq_distribution[i]);
    }
    
    bestscore = random_init_key(freq_distribution, ciphertext);
    bestkey = bestinitkey;
    for (i=0; i<25; i++) {
        for (j=0; j<26-i; j++) {
            if (freq_distribution[i] > 0) { //clumsy way to do outerswap
                freq_distribution[i]--;
                freq_distribution[j]++;
            }
            
            score = random_init_key(freq_distribution, ciphertext);
              if(score<bestscore){
                  bestscore = score;
                  bestkey=bestinitkey;
                  }
                  
            else
                freq_distribution[i]++;
                freq_distribution[j]--;
                //uterswap()
                 score = random_init_key(freq_distribution,ciphertext);
                 if(score<bestscore){
                        bestscore = score;
                        bestkey= bestinitkey;
                     
                 }
                     
                     
        }
                     }
    
                     
    return bestkey;
    
    
}


















/*

void bigram_update();
int *create_initial_key(){
    
    
    
    
    
    
    
}
void modify_putative_key();
int innerhill_clime();
int random_init_key();
int outerhill_climb();

*/
