//
//  main.c
//
//
//
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
// Currently we have a bigram matrix for English, we can build a bigram based on our dictionary, which is more customized
int english_bigram[26][26] = {
    // Source: http://norvig.com/mayzner.html and https://github.com/alimony/homophonic-cipher-attack/blob/master/e_hardcoded_values.h
    // Matrix is read by row and then column to get digram, e.g. row 'h' and column 'a' is the bigram 'ha'
    //Bigram / 100 will get the percentage. For example, th is very common and is 3.56% of all bigrams
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



char *dictionary[40]={
    "awesomeness",
    "hearkened",
    "aloneness",
    "beheld",
    "courtship",
    "swoops",
    "memphis",
    "attentional",
    "pintsized",
    "rustics",
    "hermeneutics",
    "dismissive",
    "delimiting",
    "proposes",
    "between",
    "postilion",
    "repress",
    "racecourse",
    "matures",
    "directions",
    "pressed",
    "miserabilia",
    "indelicacy",
    "faultlessly",
    "chuted",
    "shorelines",
    "irony",
    "intuitiveness",
    "cadgy",
    "ferries",
    "catcher",
    "wobbly",
    "protruded",
    "combusting",
    "unconvertible",
    "successors",
    "footfalls",
    "bursary",
    "myrtle",
    "photocompose"
    
};


typedef struct cipher{
    int key;
    int bigram_array[26][26];  //not including space here, because the actual cipher is randomly chosen, not sure how many spaces
    float letter_frequency[27];
    float score;
    char *ciphertext;
}Cipher;
//This collection is used to temporarily hold cipher struct, and to qsort them
typedef struct collection_of_cipher{
    Cipher *ptr[27];
}Collection;


// Dict_freq is letter frequency distribution of our dictionary file
//'e' appears 12% of the time
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



//copied from decrypt.c
static inline int c2n(char c)
{
    return c == ' ' ? 0 : c-'a'+1;
}


static inline char n2c(int n)
{
    return n == 0 ? ' ' : n+'a'-1;
}


//This function takes some ciphertext at 1 instance, and calcalte frequency & bigram distribution
//It returns a ptr
Cipher * calculate_score(int putative_cipher[], int key, int array_len, int round){
    float score=0.0;
    float frequency = 0.0;
    char tmp_array[array_len+1];            //clubmsy needs to change
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
    
    
    for (int i=0; i<array_len;i++) {
        int j=i+1;
        if (j==array_len-1) {
            break;
        }
        if (putative_cipher[i]==0 || putative_cipher[j]==0 ) { //I am skipping space, because i dont know how many spaces are in the string
            continue;
        }
        
        ptr->bigram_array[putative_cipher[i]-1][putative_cipher[j]-1]++; //Add 1 to the bigram matrix. -1 because space is excluded so a maps to 0
    }
    
    
    
    
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
        //can check if this array is full, if it is it means every letter's frequency is counted, so can finish faster
        //Can be augmented
        ptr->letter_frequency[putative_cipher[i]]=frequency/array_len;
        frequency=0.0;
    }
    for (int i =0; i<array_len; i++) {
        tmp_array[i]=n2c(putative_cipher[i]);
    }
    tmp_array[array_len]='\0'; //adding null terminator for safer strlcpy, otherwise C sucks and read beyond buffer
    
    
    ptr->ciphertext =NULL;
    ptr->ciphertext = (char*)malloc(sizeof(char)*array_len+1);
    if (!ptr->ciphertext) {
        perror("");
        return NULL;
    }
    strlcpy(ptr->ciphertext, tmp_array, array_len+1);
    
    for (int i=0; i<27; i++) {
        if (round == 0) {           //This is used to tune, see which gives a better accuracy.
            score=score+fabs(ptr->letter_frequency[i]-dict_freq[i]);
        }
        else{
            score = score + powf((fabs(ptr->letter_frequency[i]-dict_freq[i])),2)/dict_freq[i];  //This we can toggle between eng_freq or dict_freq
        }
    }
    
    
    for (int i=0; i<26; i++) {
        for (int j=0; j<26; j++) {
            total_num_of_bigram = total_num_of_bigram+ptr->bigram_array[i][j];
        }
    }
    
    
    
    
    
    double sum_total=0;
    for (int i=0; i<26; i++) {
        for (int j=0; j<26; j++) {
            sum_total = sum_total + fabs((double)ptr->bigram_array[i][j]/(double)total_num_of_bigram-(double)(english_bigram[i][j])/100.0);
            
        }
    }
    
    ptr->score=score+(double)sum_total;
    return ptr;
}
//This displays a collection struct
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
//I haven't checked because i am in a rush
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

//This function determines likely keys, by sorting ptr->lowest score
int *determine_likely_key(Collection *collection, int key_length){   //parameter should include key length, to be added later
    int *keys = calloc(key_length, sizeof(int)); // The first parameter should be key length
    if (!keys) {
        return NULL;
    }
    qsort(collection->ptr, 27, sizeof(Cipher*), comparefun);
    
    for (int i =0; i<key_length; i++) {   // change to i<key_length later
        *(keys+i)=collection->ptr[i]->key;
    }
    
    
    return keys;
}

//This function breaks ciphertext into segments, and just like how you break vigenere cipher
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
        memset(dptr[i], 0, sizeof(char) * cipher_length);//Set 0 so strlen works,kind of clumbsy can be changed later
        
    }
    
    for (int j = 0; j < cipher_length; j++) {
        dptr[j % key_length][index[j % key_length]] = ciphertext[j];
        index[j % key_length]++;
    }
    return dptr;
}




void decryption(int *keys, char ciphertext[], int key_length, int cipher_length) {
    
    char temp[cipher_length+1];
    
    for (int i = 0; i <cipher_length-1; i++) {
        //Any of these two works in some cases, i am dizzy at this point and can't figure out which is correct
        //So sort of hard coded
        temp[i] = n2c((c2n(ciphertext[i]) +(27-keys[i % key_length]))%27);
        //temp[i] = n2c(abs((c2n(ciphertext[i]) - keys[i % key_length]))%27);
        
    }
    temp[cipher_length]='\0';
    printf("The plaintext is:%s",temp);
}
//Reference https://www.lemoda.net/c/levenshtein/
static int distance (const char * word1,int len1,const char * word2,int len2){
    int matrix[len1 + 1][len2 + 1];
    int i;
    for (i = 0; i <= len1; i++) {
        matrix[i][0] = i;
    }
    for (i = 0; i <= len2; i++) {
        matrix[0][i] = i;
    }
    for (i = 1; i <= len1; i++) {
        int j;
        char c1;
        
        c1 = word1[i-1];
        for (j = 1; j <= len2; j++) {
            char c2;
            
            c2 = word2[j-1];
            if (c1 == c2) {
                matrix[i][j] = matrix[i-1][j-1];
            }
            else {
                int delete;
                int insert;
                int substitute;
                int minimum;
                
                delete = matrix[i-1][j] + 1;
                insert = matrix[i][j-1] + 1;
                substitute = matrix[i-1][j-1] + 1;
                minimum = delete;
                if (insert < minimum) {
                    minimum = insert;
                }
                if (substitute < minimum) {
                    minimum = substitute;
                }
                matrix[i][j] = minimum;
            }
        }
    }
    return matrix[len1][len2];
}

int found = 0;
int brute_force(char ciphertext[], int *keys, int key_length, int start, int end){
    typedef struct min_score {
        int distance;
        int index;
    }SCORE;
    SCORE *array[key_length];
    for (int i =0; i<key_length; i++) {
        array[i]=NULL;
    
    }

    int i = 0;
    int temp[15];
    char temp1[15];
    int tmp_str=start;
    
    while (i<key_length) {
        memset(temp,0, sizeof(temp));
        memset(temp1, 0, sizeof(temp1));
        for (int j =0; j<=end-start; j++) {
            temp[j]=c2n(ciphertext[tmp_str]);
            tmp_str++;
            if (temp[j]-keys[i] <0) {
                
                temp[j]=(temp[j]-keys[i])+27;
                
            }
            else{
                temp[j]=temp[j]-keys[i];
        }
            temp1[j]=n2c(temp[j]);
      }
    
    
        temp1[end-start+1]='\0';
        int min =10,d,index;
        for (int j = 0; j<40; j++) {
            d=distance(dictionary[j], strlen(dictionary[j]), temp, strlen(temp1));
            if (d<min) {
                min=d;
                index=j;
            }
            
        }
        SCORE *ptr = malloc(sizeof(SCORE));
        if (!ptr) {
            printf("\nno memory for SCORE!\n");
        }
        ptr->distance=min;
        ptr->index=index;
        array[i]=ptr;
        i++;
}
    int min=10;
    int index;
    for (int i=0; i<key_length; i++) {
        if (array[i]->distance<min) {
            min = array[i]->distance;
            index = array[i]->index;
        }
    }
    
    if (min<=4) {
        printf("\n %s ",dictionary[index]);
        for (int i=0; i<key_length; i++) {
            free(array[i]);
        }
        found =1;
        return 1;
        
    }
    for (int i=0; i<key_length; i++) {
        free(array[i]);
    }
    found = 0;
    return 0;


}


int main(int argc, const char * argv[]) {
    
    int key=0;
    char ciphertext[501];
    int key_length=8;
   
    if (argc <3) {
        printf("Usage:./program -t [NUM]\n");
        printf("num is the length of the key!\n");
        return 0;
    }
    
    
    if (strcmp(argv[1], "-t")!=0) {
        printf("option not valid");
        return 0;
    }
    
    key_length = atoi(argv[2]);
    if (key_length<0 || key_length>24) {
        printf("key length is between 0-24");
        return EXIT_FAILURE;
    }
    
    printf("Enter the ciphertext:");
    if(fgets(ciphertext,501,stdin)==NULL){
        printf("reading failed");
        return EXIT_FAILURE;
    }
    
    if (strlen(ciphertext)!=500) {
        printf("Please enter 500 characters\n");
        return EXIT_FAILURE;
    }
    
    
    Collection *collection = malloc(sizeof(Collection));
    if (!collection) {
        perror("");
        return EXIT_FAILURE;
    }
    for (int i=0; i<27; i++) {
        collection->ptr[i]=NULL;
    }
    
    
    
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
    
    
    printf("\nThe likely keys of the first round are:");
    printf("\nNote:this is more accuract when dealing with complext key scheduler\n");
    
    
    for (int i =0; i<key_length; i++) {
        printf(" %d ",*(keys+i));
    }
    printf("\n");
    destroy_everything(collection);
    
    int start = 0;
    int end = 4;
    
    while (start+end<strlen(ciphertext)-8) {//bad way to implement, need to change later
        while (!brute_force(ciphertext,keys,key_length, start, end) && end<13) {
            end++;
        }
        if (found) {
            start = (end-start)+start+1;
            end=start+4;
            found=0;
            
        }
        else{
        start +=13;
        end=start+4;
        }
        
    }
   
    
    return 0;
    
}
