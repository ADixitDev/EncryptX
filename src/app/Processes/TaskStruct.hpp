#ifndef TASKSTRUCT_HPP
#define TASKSTRUCT_HPP

#include "../fileHandling/IO.hpp"
#include <fstream>
#include <string>
#include <sstream>
enum class Action {
    ENCRYPT,
    DECRYPT
};

struct TaskStruct{
 // 1. Take the file path 
 //2. take the file stream
 // 3. Action like Encrypt & Decrypt
public :

string filePath ; 
fstream file_stream  ;
Action action ;

TaskStruct(fstream &file_stream , Action act , string Path){
    file_stream =move(file_stream);
    action = act ;
    file_stream = Path ; 
}
// serialize & deserialize 
// Serialize does a object convert into stream 
// deserialize does a reverse stream to object 

// Serialize 
string tostring(){
   ostringstream oss ; 
   oss << filePath <<"," <<(action == Action:: ENCRYPT ? "ENCRYPT" : "DECRYPT") ;
   return oss.str() ; 
}

// Deserialize 
 string fromstring (const string & taskData){
    // filepath , fstream , Action
    istringstream iss(taskData) ;
    string filepath ;
    string file_stream ; 
    string actionstr  ;

    // "text.txt , Encrypct"
 if(getline(iss , filepath ,",") && getline(iss, actionstr)){
    Action action = (actionstr== "ENCRYPT" ?  Action:: ENCRYPT : Action::DECRYPT);
    IO io(filePath);
            fstream file_stream = move(io.getFile_Stream());
            if (file_stream.is_open()) {
                return TaskStruct(move(file_stream), action, filepath);
            } else {
                throw runtime_error("Failed to open file: " + filePath);
            }
        } else {
            throw runtime_error("Invalid task data format");
        }

 }


};
#endif

