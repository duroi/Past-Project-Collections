#include <iostream>
#include <fstream>

using namespace std;

#include "encryption.h"


class VigenereEncrypt: public EncryptedFileWriter {
    public:
        VigenereEncrypt(string filename, string code)
        {
            EncryptedFileWriter writer(filename);
            codeword = code;
        }

        string encrypt(string text);
    private:
        string codeword;
};

class VigenereDecrypt: public EncryptedFileReader {
    public:
        VigenereDecrypt(string filename, string code)
        {
            EncryptedFileReader reader(filename);
            codeword = code;
        }
        string decrypt(string text);
    private:
        string codeword;
};      