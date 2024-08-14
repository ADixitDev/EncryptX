#include "IO.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


class ReadEnv{
    string path = .env ;
    IO io(path) ; 
    fstream file_stream = io.getFile_Stream();
    stringstream buffer ; 
    buffer<< file_stream .rdbuf() ; 
    string content = buffer.str() ;
    return content ;
};