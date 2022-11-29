/* COP3331
 * IGLI DURO
 * U33766202 */

/* In this lab, you will implement classes capable of encoding and decoding messages according to the Vigenere cipher.  
 * Your classes, VigenereEncrypt and VigenereDecrypt, should inherit from the provided EncryptedFileWriter and EncryptedFileReader classes, respectively, 
 * and override the encrypt function of EncryptedFileWriter and decrypt function of EncryptedFileReader to accomplish this.
 * 
 * Constructors:  In addition to encrypt and decrypt, you will need to implement a constructor for each class.  Both constructors should accept two strings, a file name and a code.  
 * The file name should be used to initialize the superclass (EncryptedFileWriter or EncryptedFileReader), while the code should be stored.
 * 
 * Encrypt:  the Vigenere cipher works by "shifting" the characters of the plain text based on the code.  
 * A code letter "A" will not change the text, while code letter "B" encrypts "A" as "B", "B" as "C", etc., "Y" as "Z", and "Z" as "A", shifting all letters by 1.  
 * Code letter "C" would shift by 2, and so forth, and code letter "Z" shifts by 25 (same as shifting 1 backwards).  
 * After using the first letter of the code to encrypt the first letter of the text, the cipher uses the second letter of the code for the second letter of the text, 
 * and so forth, starting over with the first letter of the code if the text is longer than the code.
 * 
 * For example, if we encrypt the text "HELLO" using the code "AB", the result will be "HFLMO", 
 * as we use the "A" to encode "H", the first "L", and "O" and "B" to encode "E" and the second "L".
 * 
 * Your encrypt() function should return the encrypted string, in all caps.  Note that non-letter characters in the input should appear unchanged in the output.
 * 
 * Decrypt:  To decrypt an encrypted message, you should use the same code but shift characters in the opposite direction.  
 * For example, code letter "B" would decrypt "B" as "A", "C" as "B", etc., and "A" as "Z".  
 * Put another way, "B" would shift the input letter by 25 (or 1 backwards), "C" would shift by 24 (2 backwards), etc., and "Z" shifts by 1 (25 backwards).
 * 
 * Your decrypt() function should return the decrypted string, in all lowercase.  As with encrypt, non-letter characters in the input should appear unchanged in the output.
 * 
 * For both VigenereEncrypt and VigenereDecrypt, you may assume that the code word consists entirely of letters, but the text will contain non-letter characters.  
 * Ideally, you would edit the code word to eliminate non-letter characters, but this behavior will not be tested.  
 * Both the code word and the text could contain capital or lowercase letters.  You may find the isalpha(), toupper(), and tolower() functions of the <cctype> library useful.
 * 
 * Hint:  the modulus operator (%) is very helpful for encryption and decryption.  
 * If you convert the characters A-Z into numbers 0-25, you can add the numbers for the text and code (or shift amount), 
 * then take mod 26 to get the number for the shifted character.  
 * Also, you can take (letter count) mod (code length) to find which character of the code word to use.
 * 
 * The provided EncryptedFileWriter::encrypt() function will capitalize all letters in the input, and EncryptedFileReader::decrypt() will make them lowercase.  
 * You may call these functions in your code if you like.  
 * You're encouraged to examine the EncryptedFileWriter and EncryptedFileReader to see how they work, but they should work even if you do not.
 * 
 * Driver instructions: the driver prints a prompt and expects 1 of 3 commands.  "quit" ends the program.  "encrypt" and "decrypt" both require 3 arguments:  
 * an input file, an output file, and the code.  They will call the VigenereEncrypt and VigenereDecrypt functions appropriately to read the input file, 
 * encrypt or decrypt its contents according to the code, and write the result to the output file.  The driver will not stop until you enter the command "quit" or use <ctrl>-c.
*/



#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

#include "encryption.h"
#include "vigenere.h"



//g++ -g encryption-driver.cpp encryption.cpp vigenere.cpp


//====================================================NEED TO FIX====================================================
//Logic for encrypt and decrypt works on paper and when testing in its own program by feeding it text and codewords. 
//Issues arose when trying to accommodate it with the provided files. 
//===================================================================================================================


//Encrypt function, will take a string of the file contents and encrypt the text according to the codeword.
string VigenereEncrypt::encrypt(string fileContents)
{
    //string to return
    string ret;

    //Loop control
    int i, j = 0;

    //Hold current letter in string.
    char letter;
    //Hold respective alphabetical value of letter.
    int alphaVal;
    //Hold respective alphabetical value of code according to cypher.
    int codeVal;
    //Length of codeword will be used with % to repeat through the codeword again.
    int codeLength = codeword.size();

    //Hold respective alphabetical value of alphaVal + codeVal.
    int cypherVal;
    
    //Loop through every element of string to find alphabetical characters and encypt them according to cypher.
    for (int i = 0; i < fileContents.size(); i++)
    {
        //Check if element is a elphabetical character.
        if (isalpha(fileContents[i])) {
            //Test
            //cout << text[i] << endl;
            
            //Hold current letter in UPPERCASE.
            letter = toupper(fileContents[i]);
            //Test
            //cout << letter << endl;

            //Switch statement. Assign alphaVal with 0 if letter is A...assign alphaVal with 25 if letter is Z.
            switch(letter) {
            case 'A':
                alphaVal = 0;
                break;
            case 'B':
                alphaVal = 1;
                break;
            case 'C':
                alphaVal = 2;
                break;
            case 'D':
                alphaVal = 3;
                break;
            case 'E':
                alphaVal = 4;
                break;
            case 'F':
                alphaVal = 5;
                break;
            case 'G':
                alphaVal = 6;
                break;
            case 'H':
                alphaVal = 7;
                break;
            case 'I':
                alphaVal = 8;
                break;
            case 'J':
                alphaVal = 9;
                break;
            case 'K':
                alphaVal = 10;
                break;
            case 'L':
                alphaVal = 11;
                break;
            case 'M':
                alphaVal = 12;
                break;
            case 'N':
                alphaVal = 13;
                break;
            case 'O':
                alphaVal = 14;
                break;
            case 'P':
                alphaVal = 15;
            case 'Q':
                alphaVal = 16;
                break;
            case 'R':
                alphaVal = 17;
                break;
            case 'S':
                alphaVal = 18;
                break;
            case 'T':
                alphaVal = 19;
                break;
            case 'U':
                alphaVal = 20;
                break;
            case 'V':
                alphaVal = 21;
                break;
            case 'W':
                alphaVal = 22;
                break;
            case 'X':
                alphaVal = 23;
                break;
            case 'Y':
                alphaVal = 24;
                break;
            case 'Z':
                alphaVal = 25;
                break;
        }

        //Switch statement, similar logic as above. However j is increased every time an alpha character is found. 
        //Essentially iterating through the codeword whenever used and % with the size of the codeword.
        switch(toupper(codeword[j % codeLength])) {
            case 'A':
                codeVal = 0;
                break;
            case 'B':
                codeVal = 1;
                break;
            case 'C':
                codeVal = 2;
                break;
            case 'D':
                codeVal = 3;
                break;
            case 'E':
                codeVal = 4;
                break;
            case 'F':
                codeVal = 5;
                break;
            case 'G':
                codeVal = 6;
                break;
            case 'H':
                codeVal = 7;
                break;
            case 'I':
                codeVal = 8;
                break;
            case 'J':
                codeVal = 9;
                break;
            case 'K':
                codeVal = 10;
                break;
            case 'L':
                codeVal = 11;
                break;
            case 'M':
                codeVal = 12;
                break;
            case 'N':
                codeVal = 13;
                break;
            case 'O':
                codeVal = 14;
                break;
            case 'P':
                codeVal = 15;
                break;
            case 'Q':
                codeVal = 16;
                break;
            case 'R':
                codeVal = 17;
                break;
            case 'S':
                codeVal = 18;
                break;
            case 'T':
                codeVal = 19;
                break;
            case 'U':
                codeVal = 20;
                break;
            case 'V':
                codeVal = 21;
                break;
            case 'W':
                codeVal = 22;
                break;
            case 'X':
                codeVal = 23;
                break;
            case 'Y':
                codeVal = 24;
                break;
            case 'Z':
                codeVal = 25;
                break;
        }

        //Add alphaVal and codeVal, % with 26 
        int cypherVal = (alphaVal + codeVal) % 26;
        
        //Test 
        //cout << letter << " has a value of: " << alphaVal << " the code value is: " << codeVal << " and the cypherVal is: " << cypherVal << endl;

        //Switch statement, essentially reversing the logic compared to the previous statements above. Match numerical value and add the encrypted letter to ret.
        switch (cypherVal)
        {
            case 0:
                ret += 'A';
                break;
            case 1:
                ret += 'B';
                break;
            case 2:
                ret += 'C';
                break;
            case 3:
                ret += 'D';
                break;
            case 4:
                ret += 'E';
                break;
            case 5:
                ret += 'F';
                break;
            case 6:
                ret += 'G';
                break;
            case 7:
                ret += 'H';
                break;
            case 8:
                ret += 'I';
                break;
            case 9:
                ret += 'J';
                break;
            case 10:
                ret += 'K';
                break;
            case 11:
                ret += 'L';
                break;
            case 12:
                ret += 'M';
                break;
            case 13:
                ret += 'N';
                break;
            case 14:
                ret += 'O';
                break;
            case 15:
                ret += 'P';
                break;
            case 16:
                ret += 'Q';
                break;
            case 17:
                ret += 'R';
                break;
            case 18:
                ret += 'S';
                break;
            case 19:
                ret += 'T';
                break;
            case 20:
                ret += 'U';
                break;
            case 21:
                ret += 'V';
                break;
            case 22:
                ret += 'W';
                break;
            case 23:
                ret += 'X';
                break;
            case 24:
                ret += 'Y';
                break;
            case 25:
                ret += 'Z';
                break;
        }
        j++;
    }
    //If non-alpha character is found. Add current element to string. ie: " ", !, 2, \",   
    else {
        ret += fileContents[i];
    }
    }

    //Test
    //cout << ret;
    return ret;
}


//Decrypt function, will take a string of the file contents and decrypt the text according to the codeword. Similar logic as encrypt function. Comments will outline differences.
string VigenereDecrypt::decrypt(string fileContents)
{
   string ret;
    int i, j = 0;

    char letter;
    int alphaVal;

    int codeVal;
    int codeLength = codeword.size();


    int cypherVal;
    
    for (int i = 0; i < fileContents.size(); i++)
    {
        if (isalpha(fileContents[i])) {
            //cout << text[i] << endl;
            letter = toupper(fileContents[i]);
            //cout << letter << endl;

            switch(letter) {
            case 'A':
                alphaVal = 0;
                break;
            case 'B':
                alphaVal = 1;
                break;
            case 'C':
                alphaVal = 2;
                break;
            case 'D':
                alphaVal = 3;
                break;
            case 'E':
                alphaVal = 4;
                break;
            case 'F':
                alphaVal = 5;
                break;
            case 'G':
                alphaVal = 6;
                break;
            case 'H':
                alphaVal = 7;
                break;
            case 'I':
                alphaVal = 8;
                break;
            case 'J':
                alphaVal = 9;
                break;
            case 'K':
                alphaVal = 10;
                break;
            case 'L':
                alphaVal = 11;
                break;
            case 'M':
                alphaVal = 12;
                break;
            case 'N':
                alphaVal = 13;
                break;
            case 'O':
                alphaVal = 14;
                break;
            case 'P':
                alphaVal = 15;
            case 'Q':
                alphaVal = 16;
                break;
            case 'R':
                alphaVal = 17;
                break;
            case 'S':
                alphaVal = 18;
                break;
            case 'T':
                alphaVal = 19;
                break;
            case 'U':
                alphaVal = 20;
                break;
            case 'V':
                alphaVal = 21;
                break;
            case 'W':
                alphaVal = 22;
                break;
            case 'X':
                alphaVal = 23;
                break;
            case 'Y':
                alphaVal = 24;
                break;
            case 'Z':
                alphaVal = 25;
                break;
        }

        //Switch statement. Similar as above, however since we are decrypting we are "shifting backwards".
        //However addition is easier than subtraction with the logic setup previously so the codeVal for cases B-Z are reversed.
        switch(toupper(codeword[j % codeLength])) {
            case 'A':
                codeVal = 0;
                break;
            case 'B':
                codeVal = 25;
                break;
            case 'C':
                codeVal = 24;
                break;
            case 'D':
                codeVal = 23;
                break;
            case 'E':
                codeVal = 22;
                break;
            case 'F':
                codeVal = 21;
                break;
            case 'G':
                codeVal = 20;
                break;
            case 'H':
                codeVal = 19;
                break;
            case 'I':
                codeVal = 18;
                break;
            case 'J':
                codeVal = 17;
                break;
            case 'K':
                codeVal = 16;
                break;
            case 'L':
                codeVal = 15;
                break;
            case 'M':
                codeVal = 14;
                break;
            case 'N':
                codeVal = 13;
                break;
            case 'O':
                codeVal = 12;
                break;
            case 'P':
                codeVal = 11;
                break;
            case 'Q':
                codeVal = 10;
                break;
            case 'R':
                codeVal = 9;
                break;
            case 'S':
                codeVal = 8;
                break;
            case 'T':
                codeVal = 7;
                break;
            case 'U':
                codeVal = 6;
                break;
            case 'V':
                codeVal = 5;
                break;
            case 'W':
                codeVal = 4;
                break;
            case 'X':
                codeVal = 3;
                break;
            case 'Y':
                codeVal = 2;
                break;
            case 'Z':
                codeVal = 1;
                break;
        }


        int cypherVal = (alphaVal + codeVal) % 26;
        //Test
        //cout << letter << " has a value of: " << alphaVal << " the code value is: " << codeVal << " and the cypherVal is: " << cypherVal << endl;

        //Switch statement. Decrypt should be lowercase as apposed to UPPERCASe for encrypt.
        switch (cypherVal)
        {
            case 0:
                ret += 'a';
                break;
            case 1:
                ret += 'b';
                break;
            case 2:
                ret += 'c';
                break;
            case 3:
                ret += 'd';
                break;
            case 4:
                ret += 'e';
                break;
            case 5:
                ret += 'f';
                break;
            case 6:
                ret += 'g';
                break;
            case 7:
                ret += 'h';
                break;
            case 8:
                ret += 'i';
                break;
            case 9:
                ret += 'j';
                break;
            case 10:
                ret += 'k';
                break;
            case 11:
                ret += 'l';
                break;
            case 12:
                ret += 'm';
                break;
            case 13:
                ret += 'n';
                break;
            case 14:
                ret += 'o';
                break;
            case 15:
                ret += 'p';
                break;
            case 16:
                ret += 'q';
                break;
            case 17:
                ret += 'r';
                break;
            case 18:
                ret += 's';
                break;
            case 19:
                ret += 't';
                break;
            case 20:
                ret += 'u';
                break;
            case 21:
                ret += 'v';
                break;
            case 22:
                ret += 'w';
                break;
            case 23:
                ret += 'x';
                break;
            case 24:
                ret += 'y';
                break;
            case 25:
                ret += 'z';
                break;
        }
        j++;
    }
    else {
        ret += fileContents[i];
    }
    }

    //Test
    //cout << ret << endl;
    return ret;
}

