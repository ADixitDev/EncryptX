#include "cryptoAlgo.hpp"
#include "../Processes/TaskStruct.hpp"
#include "../fileHandling/ReadEnv.cpp"
using namespace std ; 

//Simple Substitution Algorithm: Caesar Cipher
//Encrypted_char=(Plaintext_char+Key)mod256
//--------------------------------------------------------
//Decryption with Caesar Cipher
//To decrypt the message, the formula is:
//Decrypted_char=(Encrypted_char−Key+256)mod 256
//Decrypted_char=(Encrypted_char−Key+256)mod256
//------------------------------------------------------
int executeCryption(const string& taskData){
   TaskStruct  task = TaskStruct :: fromstring (taskData) ; 
   ReadEnv  env ;
   string envKey = env.getenv();
   
   int key = stoi(envKey) ;

   if (task.action == Action::ENCRYPT) {
        char ch ;
        while (task.file_stream.get(ch)) {
            ch = (ch + key) % 256;
            task.file_stream.seekp(-1, ios::cur);
            task.file_stream.put(ch);
        }
        task.file_stream.close();
    } else {
        char ch;
        while (task.file_stream.get(ch)) {
            ch = (ch - key + 256) % 256;
            task.file_stream.seekp(-1, ios::cur);
            task.file_stream.put(ch);
        }
        task.file_stream.close();
    }
    return 0;
}
