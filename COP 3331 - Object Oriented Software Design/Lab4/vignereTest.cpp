#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

//#include "encryption.h"
//#include "vigenere.h"


// string VigenereEncrypt::encrypt(string )

string encrypt(string text, string code)
{
    string ret;
    int i, j = 0;

    char letter;
    int alphaVal;

    int codeVal;
    int codeLength = code.size();


    int cypherVal;
    
    for (int i = 0; i < text.size(); i++)
    {
        if (isalpha(text[i])) {
            //cout << text[i] << endl;
            letter = toupper(text[i]);
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


        switch(toupper(code[j % codeLength])) {
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


        int cypherVal = (alphaVal + codeVal) % 26;
        cout << letter << " has a value of: " << alphaVal << " the code value is: " << codeVal << " and the cypherVal is: " << cypherVal << endl;

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
    else {
        ret += text[i];
    }
    }

    
    cout << ret << endl;
    return ret;
}

string decrypt(string text, string code)
{

 string ret;
    int i, j = 0;

    char letter;
    int alphaVal;

    int codeVal;
    int codeLength = code.size();


    int cypherVal;
    
    for (int i = 0; i < text.size(); i++)
    {
        if (isalpha(text[i])) {
            //cout << text[i] << endl;
            letter = toupper(text[i]);
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


        switch(toupper(code[j % codeLength])) {
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
        cout << letter << " has a value of: " << alphaVal << " the code value is: " << codeVal << " and the cypherVal is: " << cypherVal << endl;

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
        ret += text[i];
    }
    }

    
    cout << ret << endl;
    return ret;
}

int main() {

    string text = "Veni vidi vici";
    string code = "yayaya";

    string text1 = text;
    string code1 = code;

    text1 = encrypt(text, code);
    
   
    decrypt(text1, code1);



    return 0;
}
