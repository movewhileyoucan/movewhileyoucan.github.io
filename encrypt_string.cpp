#include <iostream>
#include <string>
using namespace std;

//encrypt direction. Default is 1 = encrypt, to decrypt: -1
string encryptDecrypt(string toEncrypt, string key, int encryptDirection = 1) {
string output = toEncrypt;
  if(!key.empty()){
    for (unsigned i = 0; i < toEncrypt.size(); i++){
      output[i] = (toEncrypt[i]-33+encryptDirection*key[i%key.size()]+2*95)%95+33; // add 2*95 to avoid mod of negtive number
    }
  }
  else {
    output=toEncrypt;
  }
return output;

}

int main()
{
  string key;
  string toEncrypt;
  std::cout << "Enter encryption key:";
  std::getline (std::cin,key);
  std::cout << "Enter string to encrypt:";
  std::getline (std::cin,toEncrypt);
  string encrypted = encryptDecrypt(toEncrypt,key);
    cout << "Encrypted:" << encrypted << "\n";

    string decrypted = encryptDecrypt(encrypted,key,-1);
    cout << "Decrypted:" << decrypted << "\n";
    return 0;
}





