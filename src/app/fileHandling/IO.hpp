#ifndef IO_HPP
#define IO_HPP
#include <fstream>
#include <string>
using namespace std ;

class IO{
    public :
   IO(const string &filepath) ; 
   ~IO() ;
   fstream getfile_Stream() ;

   private :
     fstream file_stream ;

};
#endif 