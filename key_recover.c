//
//  main.c
//  decryption
//  Author:Hao

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
// Currently we have a bigram matrix for English, we can build a bigram based on our dictionary, which is more customized
int english_bigram[26][26] = {
    // Source: http://norvig.com/mayzner.html and https://github.com/alimony/homophonic-cipher-attack/blob/master/e_hardcoded_values.h
    // Matrix is read by row and then column to get digram, e.g. row 'h' and column 'a' is the bigram 'ha'
    //Bigram / 100 will get the percentage. For example, 'th' is very common and is 3.56% of all bigrams
    //        a   b   c    d    e    f   g    h   i   j   k    l   m    n    o   p  q    r    s    t   u   v   w   x   y  z
    /* a */ { 0, 23, 45,  37,   1,   7, 20,   1,  32, 1, 10, 109, 28, 198,   0, 20, 0, 108,  87, 149, 12, 20,  6,  2, 22, 1},
    /* b */ {15,  1,  0,   0,  58,   0,  0,   0,  11, 2,  0,  23,  0,   0,  20,  0, 0,  11,   5,   2, 18,  0,  0,  0, 18, 0},
    /* c */ {54,  0,  8,   0,  65,   0,  0,  60,  28, 0, 12,  15,  0,   0,  79,  0, 0,  15,   2,  46, 16,  0,  0,  0,  4, 0},
    /* d */ {15,  0,  0,   4,  76,   0,  3,   0,  49, 0,  0,   3,  2,   1,  19,  0, 0,   8,  13,   0, 15,  2,  1,  0,  5, 0},
    /* e */ {69,  3, 48, 117,  38,  16, 12,   3,  18, 0,  2,  53, 37, 145,   7, 17, 6, 205, 134,  41,  3, 26, 12, 21, 14, 0},
    /* f */ {16,  0,  0,   0,  24,  15,  0,   0,  28, 0,  0,   6,  0,   0,  49,  0, 0,  21,   1,   8, 10,  0,  0,  0,  1, 0},
    /* g */ {15,  0,  0,   0,  38,   0,  2,  23,  15, 0,  0,   6,  1,   7,  13,  0, 0,  20,   5,   2,  9,  0,  0,  0,  3, 0},
    /* h */ {93,  0,  0,   0, 308,   0,  0,   0,  76, 0,  0,   1,  1,   3,  48,  0, 0,   8,   2,  13,  7,  0,  0,  0,  5, 0},
    /* i */ {29, 10, 70,  30,  38,  20, 26,   0,   2, 0,  4,  43, 32, 243,  84,  9, 1,  32, 113, 112,  2, 29,  0,  2,  0, 6},
    /* j */ { 3,  0,  0,   0,   5,   0,  0,   0,   0, 0,  0,   0,  0,   0,   5,  0, 0,   0,   0,   0,  6,  0,  0,  0,  0, 0},
    /* k */ { 2,  0,  0,   0,  21,   0,  0,   0,  10, 0,  0,   1,  0,   5,   1,  0, 0,   0,   5,   0,  0,  0,  0,  0,  1, 0},
    /* l */ {53,  1,  1,  25,  83,   5,  1,   0,  62, 0,  2,  58,  2,   1,  39,  2, 0,   1,  14,  12, 14,  4,  1,  0, 42, 0},
    /* m */ {56,  9,  0,   0,  79,   0,  0,   0,  32, 0,  0,   0, 10,   1,  34, 24, 0,   0,   9,   0, 12,  0,  0,  0,  6, 0},
    /* n */ {35,  0, 42, 135,  69,   7, 95,   1,  34, 1,  5,   6,  3,   7,  46,  1, 1,   1,  51, 104,  8,  5,  1,  0, 10, 0},
    /* o */ { 6, 10, 17,  20,   4, 118,  9,   2,   9, 1,  6,  36, 55, 176,  21, 22, 0, 128,  29,  44, 87, 18, 33,  2,  4, 0},
    /* p */ {32,  0,  0,   0,  48,   0,  0,   9,  12, 0,  0,  26,  2,   0,  36, 14, 0,  47,   6,  11, 10,  0,  0,  0,  1, 0},
    /* q */ { 0,  0,  0,   0,   0,   0,  0,   0,   0, 0,  0,   0,  0,   0,   0,  0, 0,   0,   0,   0, 15,  0,  0,  0,  0, 0},
    /* r */ {69,  3, 12,  19, 185,   3, 10,   2,  73, 0, 10,   9, 18,  16,  73,  4, 0,  12,  40,  36, 13,  7,  1,  0, 25, 0},
    /* s */ {22,  1, 16,   0,  93,   2,  0,  32,  55, 0,  4,   6,  6,   1,  40, 19, 1,   1,  40, 105, 31,  0,  2,  0,  6, 0},
    /* t */ {53,  0,  3,   0, 120,   1,  0, 356, 134, 0,  0,  10,  3,   1, 104,  0, 0,  43,  34,  17, 26,  0,  8,  0, 23, 0},
    /* u */ {14,  9, 19,   9,  15,   2, 13,   0,  10, 0,  0,  35, 14,  39,   1, 14, 0,  54,  45,  40,  0,  0,  0,  0,  0, 0},
    /* v */ {14,  0,  0,   0,  82,   0,  0,   0,  27, 0,  0,   0,  0,   0,   7,  0, 0,   0,   0,   0,  0,  0,  0,  0,  0, 0},
    /* w */ {38,  0,  0,   0,  36,   0,  0,  38,  37, 0,  0,   2,  0,   8,  22,  0, 0,   3,   4,   1,  0,  0,  0,  0,  0, 0},
    /* x */ { 3,  0,  3,   0,   2,   0,  0,   0,   4, 0,  0,   0,  0,   0,   0,  7, 0,   0,   0,   5,  0,  0,  0,  0,  0, 0},
    /* y */ { 2,  0,  1,   1,   9,   0,  0,   0,   3, 0,  0,   2,  2,   1,  15,  2, 0,   1,  10,   2,  0,  0,  0,  0,  0, 0},
    /* z */ { 2,  0,  0,   0,   5,   0,  0,   0,   1, 0,  0,   0,  0,   0,   1,  0, 0,   0,   0,   0,  0,  0,  0,  0,  0, 0}
};


//This struct holds the ciphertext - key at 1 instance. This holds the key used at that instance, bigram, letter frequency, score and what the ciphter -key is
typedef struct cipher{
    int key;
    int bigram_array[26][26];          //The size isn't [27][27]. Not including space here, because the actual cipher is randomly chosen, not sure how many spaces
    float letter_frequency[27];         // Letter frequency, [0] = ' ', [1] = 'a' so on.
    float score;
    char *ciphertext;                   //pointer to a string of that instance
}Cipher;

//This collection is used to temporarily hold cipher struct, and to qsort them
//This holds all the ciphertext - key for key = 0 to 26. This keeps all the data then allows for sorting, choosing top [key_length] candidates
typedef struct collection_of_cipher{
    Cipher *ptr[27];                    // This is an array of pointers that store the address of struct Cipher, which holds data of one instace
}Collection;


// Dict_freq is letter frequency distribution of our dictionary file
//'e' appears 12% of the time. [0] = space, [1] is a........[26] is z
//                      ' '       'a'       'b'      'c'       'd'      'e'         'f'     'g'
float dict_freq[27]={0.100775, 0.038759, 0.020671, 0.043927, 0.031007, 0.121447, 0.010335,0.007751,
    0.023255, 0.077519, 0.0001, 0.002583, 0.041343, 0.028423, 0.051679, 0.064599, 0.031007, 0.0001, 0.064599,
    0.108527, 0.059431, 0.033591, 0.007751, 0.010335, 0.0001, 0.018087, 0.002583
};

//http://pi.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html
//This is letter frequency of english, we can toggle between dict freq and this, whichever gives better accuracy
float eng_freq[27]={0.100775, 0.0812, 0.0149, 0.0271, 0.0432, 0.1202, 0.0230, 0.0203, 0.0592, 0.0731, 0.001,
    0.0069, 0.0398, 0.0261, 0.0695, 0.0768, 0.0182, 0.0011, 0.0602, 0.0628, 0.0910,0.0288, 0.0111,0.0209,
    0.0017, 0.0211, 0.0007
};




static inline int c2n(char c)
{
    return c == ' ' ? 0 : c-'a'+1;
}


static inline char n2c(int n)
{
    return n == 0 ? ' ' : n+'a'-1;
}


//This function takes 1 ciphertext - key , for key = 0 - 26.
//Then it calculates scores and return a pointer to the struct
Cipher * calculate_score(int putative_cipher[], int key, int array_len, int round){
    float score=0.0;
    float frequency = 0.0;
    char tmp_array[array_len+1];
    int total_num_of_bigram=0;
    
    
    Cipher *ptr = NULL;
    ptr =malloc(sizeof(Cipher));
    if (!ptr) {
        perror("no memory:");
        return NULL;
    }
    ptr->key=0;
    ptr->key = key;
    
    
    
    for (int row=0; row<26;row++) {
        for (int col=0; col<26; col++) {
            ptr->bigram_array[row][col]=0;      //initialize bigram array here
        }
        
    }
    
    //This loop calculates the number of occurence of bigrams
    for (int i=0; i<array_len;i++) {
        int j=i+1;
        if (j==array_len-1) {
            break;
        }
        if (putative_cipher[i]==0 || putative_cipher[j]==0 ) { //skipping space, because dont know how many spaces are in the string
            continue;
        }
        
        ptr->bigram_array[putative_cipher[i]-1][putative_cipher[j]-1]++; //Add 1 to the bigram matrix. -1 because space is excluded so a maps to 0
    }
    
    
    
    //This loop calculates the numer of occurence of letters
    for (int i=0; i<array_len;i++) {
        if (i<27) {
            ptr->letter_frequency[i]=0;
        }
        else{
            for (int j=0; j<array_len;j++) {
                if (putative_cipher[i]==putative_cipher[j]) {
                    frequency++;
                }
                
            }
            
        }
        
        ptr->letter_frequency[putative_cipher[i]]=frequency/array_len;
        frequency=0.0;
    }
    
    //This loop translate ciphertext from number representation back to charater representation
    for (int i =0; i<array_len; i++) {
        tmp_array[i]=n2c(putative_cipher[i]);
    }
    tmp_array[array_len]='\0'; //adding null terminator for safer strlcpy
    
    
    ptr->ciphertext =NULL;
    ptr->ciphertext = (char*)malloc(sizeof(char)*array_len+1);
    if (!ptr->ciphertext) {
        perror("");
        return NULL;
    }
    //This copies the ciphertext into a struct
    strlcpy(ptr->ciphertext, tmp_array, array_len+1);
    
    
    //This loop calculates frequency. Frequency score = frequency of this ciphertext at this instance - frequency that of the dictionary/standard english
    for (int i=0; i<27; i++) {
        if (round == 0) {           //This is used to tune, see which gives a better accuracy.
            score=score+fabs(ptr->letter_frequency[i]-dict_freq[i]);
        }
        else{
            score = score + powf((fabs(ptr->letter_frequency[i]-dict_freq[i])),2)/dict_freq[i];  //This we can toggle between eng_freq or dict_freq
            //This is a chi square test on how related two frequencies are
        }
    }
    
    //This loop calculates the total number of bigram pairs in the ciphertext at this instance
    for (int i=0; i<26; i++) {
        for (int j=0; j<26; j++) {
            total_num_of_bigram = total_num_of_bigram+ptr->bigram_array[i][j];
        }
    }
    
    
    
    
    //This loop sums up the total score
    double sum_total=0;
    for (int i=0; i<26; i++) {
        for (int j=0; j<26; j++) {
            sum_total = sum_total + fabs((double)ptr->bigram_array[i][j]/(double)total_num_of_bigram-(double)(english_bigram[i][j])/100.0);
            
        }
    }
    
    ptr->score=score+(double)sum_total;
    return ptr;
}


//This displays the content of a collection struct. The struct holds the 27 ciphertext at 27 instance.(key 0 - 26)

void display_cipher(Cipher *ptr, int number){
    printf("\n");
    printf("\n");
    printf("////////////////////////////////////////////////////////////////////////////\n");
    printf("////////////////////////////////////////////////////////////////////////////\n");
    printf("The key of the %dth struct  is %d\n",number,ptr->key);
    printf("the letter frequency is:");
    for (int i =0; i<27; i++) {
        printf("% f ",ptr->letter_frequency[i]);
    }
    printf("\n");
    printf("The score is %f\n",ptr->score);
    printf("the putative shifted cipher is:%s\n",ptr->ciphertext);
    printf("////////////////////////////////////////////////////////////////////////////\n");
    printf("////////////////////////////////////////////////////////////////////////////\n");
    printf("\n");
    printf("\n");
}


//This is to free up memory, needs to check if everything is freed

void destroy_everything(Collection *collection){
    for (int i=0; i<27; i++) {
        if (collection->ptr[i]->ciphertext) {
            free(collection->ptr[i]->ciphertext);
        }
        free(collection->ptr[i]);
    }
    free(collection);
}

//Compare for Qsort
//The smaller the score, the higher the rank.
int comparefun(const void* p1, const void* p2){
    
    Cipher *left_struct = *(Cipher**)p1;
    Cipher *right_struct = *(Cipher**)p2;
    if (left_struct->score<right_struct->score) {
        return -1;
    }
    else if (left_struct->score>right_struct->score){
        return 1;
    }
    else
        return 0;
    
    
}

//This function determines likely keys, by sorting the scores
int *determine_likely_key(Collection *collection, int key_length){
    int *keys = calloc(key_length, sizeof(int));
    if (!keys) {
        return NULL;
    }
    qsort(collection->ptr, 27, sizeof(Cipher*), comparefun);
    
    for (int i =0; i<key_length; i++) {
        *(keys+i)=collection->ptr[i]->key;
    }
    
    
    return keys;
}


//This function breaks ciphertext into a number of segments, and just like how you break vigenere cipher up

char ** segmentation(char ciphertext[], int key_length, int cipher_length  ){
    int index[key_length];
    
    
    for (int i=0; i<key_length; i++) {
        index[i]=0;         //initialize
    }
    
    
    char **dptr = calloc(key_length, sizeof(char *));//pointer to pointer to char,this holds all the segments
    if (!dptr) {
        printf("\nfailed to allocate memory for segmenting ciphertext!!\n");
        return NULL;
    }
    
    for (int i = 0; i < key_length; i++) {
        dptr[i] = malloc(sizeof(char) * cipher_length);
        if (!dptr[i]) {
            printf("memory allocation failed");
            return NULL;
        }
        memset(dptr[i], 0, sizeof(char) * cipher_length);//Set 0 so strlen works
        
    }
    
    //This loop breaks cipher up into segments that look like how you break up vigenere cipher
    for (int j = 0; j < cipher_length; j++) {
        dptr[j % key_length][index[j % key_length]] = ciphertext[j];
        index[j % key_length]++;
    }
    return dptr;
}
//The function does index of coincidence test it returns the most likely key
//formula found at http://alexbarter.com/statistics/index-of-coincidence https://en.wikipedia.org/wiki/Index_of_coincidence
int coin_test(char ciphertext[]){
    int key_len;
    int max_key_len=24;
    int letter_frequency[27];  //holds the num of occurence of letters
    int cipher_length=0;
    int frequency=0;        //counter for loop
    float IOC;
    float starting_IOC = 0.5;    //This is a threshold.
    int bestguess=0;
    cipher_length = strlen(ciphertext);
    
    //This loop goes from keylen=2 to 24
    //For every instance of keylen, calculates ioc, check how close it is to that of standard english
    for (int key_len=2; key_len<=max_key_len; key_len++) {
        char **segment = segmentation(ciphertext,key_len, cipher_length); // creating segments
        float score_holder[key_len];
        for (int i =0; i<key_len; i++) {
             int Ci=0;
             int L=0;
             IOC=0.0;
            
             int segment_length = strlen(segment[i]);
           
             int temp[segment_length];
             int j=0;
             char *segment_instance=segment[i];
            //This loop translates char into int
             for (char c =*segment_instance; c ; c=*(++segment_instance)) {
                temp[j]=c2n(c);
                j++;
            }
            //initialize
             for (int i =0; i<27; i++) {
                letter_frequency[i]=0;
            }
            //This loop count the occurence of letter
             for (int i=0; i<segment_length; i++) {
                 for (int j=0; j<segment_length; j++) {
                    if (temp[i]==temp[j]) {
                        frequency++;
                    }
                }
                letter_frequency[temp[i]]=frequency;
                frequency=0;
            }
            //This is the formula: Summation of (Ci*Ci-1)
            for (int i =0; i<27; i++) {
                Ci = Ci +letter_frequency[i]*(letter_frequency[i]-1);
            }
            //L(L-1)
            L = segment_length*(segment_length-1);
            IOC = (float)Ci/(float)L;
            score_holder[i]=fabs(0.0667-IOC);//0.0667 is the ioc of standard english, and the smaller the score, the closer it is to english
            free(segment[i]);
        }
        IOC=0.0;
        //This loop sums up all the scores of keylen at one instance
        for (int i=0; i<key_len; i++) {
            IOC=IOC+score_holder[i];
        }
        //If the ioc is better than threshold, keep track of it
        if (IOC/key_len<starting_IOC) {
            starting_IOC=IOC/key_len;
            bestguess=key_len;
        }
        //This loop frees memory allocated for segments
      
            free(segment);
        
        
    }
    
    key_len = bestguess;
    return key_len;
    
}



int main(int argc, const char * argv[]) {
    
    int key=0;
    char ciphertext[501];
    int key_length;

    printf("Enter the ciphertext:");
    if(fgets(ciphertext,501,stdin)==NULL){
        printf("reading failed");
        return EXIT_FAILURE;
    }
    
    if (strlen(ciphertext)!=500) {
        printf("Please enter 500 characters\n");
        return EXIT_FAILURE;
    }
    
    //Aloocate memory for the collection, which holds structs that hold data
    Collection *collection = malloc(sizeof(Collection));
    if (!collection) {
        perror("");
        return EXIT_FAILURE;
    }
    for (int i=0; i<27; i++) {
        collection->ptr[i]=NULL;
    }
    
    
    key_length = coin_test(ciphertext);
    printf("\nThe likely length of keys are %d\n",key_length);
    
    
    
    //This loop goes from key = 0 to 26, each round creates an instance of a ciphertext-key. Calculate score
    while (key<27) {
        int temp[500];
        for (int i = 0; i<500; i++) {
            temp[i]=c2n(ciphertext[i]);
            if (temp[i]-key <0) {
                
                temp[i]=(temp[i]-key)+27;
                
            }
            else{
                temp[i]=temp[i]-key;
            }
        }
        
        Cipher *ptr = NULL;
        ptr = calculate_score(temp,key,strlen(ciphertext),0);
        if (ptr) {
            collection->ptr[key]=ptr;
            key++;
        }
        else{
            printf("\nStruct creation failed\n");
        }
        
    }
 
    int *keys = NULL;
    keys = determine_likely_key(collection,key_length);
    
    if (!keys) {
        perror("No memory for storing keys:");
        return EXIT_FAILURE;
    }
    
    
    printf("\nThe likely keys are:");

    
    
    for (int i =0; i<key_length; i++) {
        printf(" %d ",*(keys+i));
    }
    printf("\n");
    destroy_everything(collection);

    free(keys);
    
    return 0;
}


