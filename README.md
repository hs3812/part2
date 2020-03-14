# part2




Decrypt Linear is decryption for part 2 based on the assumption that the key scheduler j(i) is non random, and linear. So 
any form of scheduler j(i) = xxxxx mod key_length,   will work.
However, for this file, the following still needs to be done:
      1. precompute a bigram for our dictionary, this would be more customized than a standard english bigram
      2. write a function that takes as input the ciphertext, return the key length(key length will not be given i asked TA)This can
      be accomphished by Kasiski or index of coincidence.
      3. Code clean up, examine the math. Augment some of the algorithm. (See comments in the file) Check memory leak etc.
      
      
      
      
Decrypt edite distance is a decryption method for part 2. It is the same as Decrypt linear, the only difference is that it has a 
additional edit distance function, and a bad implementation of a brute force algorithm. The decryptio idea is as the following:
      1. Read the ciphertext, use cipher text - key for key in range 0-26. 
      2. There must be a key that leaks information(like frequency of letter, bigram distribution)
      3. Calculate those scores, store them in a collection, use Qsort to sort and choose the most likely keys = key length
      4. For example, if the key[8] = [1,2,3,4,5,6,7,8]. The key scheduler j(i) might not be random and choose 3 more often. If we 
      use cipher - 3, we can get a closer frequency score, closer to the precomputed score, than cipher - 8. 
      5. After we get a list of likely keys, we create a permutation of it. If key length = 5, for a word length = 5, there are 
      5*5*5*5*5  permutations. The correct plaintext hides within them.
      6.So we read the ciphertext by 5 char. (permute key do cipher -key again. Brute force). The the result is a putative "plaintext"
      = length 5. Check the edit distance of it against our 40 word dictionary. Print out if edit distance is small.
      7. If not found, assume the word is of length 6, so on and so on till 13. (the maximum length is 13 in our dictionary)
      
      This file needs a function to determine key length as well. And some clean up/ memory check
      
      
      
      
      
      
Hill climb. h and Hill climb . C is based on the paper "homophonic cipher" can be found here: http://www.cs.sjsu.edu/faculty/stamp/RUA/homophonic.pdf
It is done partially since morning. Still a lot of the functions need to be done. Please read the paper, and this seems like the best solution. At least 
it is an interesting solution worth points. 
    1. For these files, please implement functions according to the paper. 
    2. An implementation example can be found https://github.com/alimony/homophonic-cipher-attack
    3. After adding functions, need to clean up and make sure its coherent
    
    
    
Thank you guys for reading this. These are what I can find of this moment. Although these might not work 100 percent on part 2,
it should be interesting enough for extra points. 

(The part 2 seems like it can only be broken using choosen plaintext attack. We need access to oracle to generate cipher/plaintext
pairs lol) 


      
      
      
      
