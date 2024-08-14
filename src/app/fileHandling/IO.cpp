#include <iostream>
#include <IO.hpp>
using namespace std; 

IO:: IO(const string &filepath){
  file_stream.open(filepath  , ios::in  | ios:: out | ios :: binary) ;
  if(!filepath.is_open()){
    cout << "Unable to open file: " << file_path << endl ;
  } 
}

fstream IO ::  getFile_Stream(){
  return move(file_stream) ; 
}

IO::~IO(){
    if(filepath.is_open()){
        file_stream.close(filepath) ; 
    }
}
