/** @file dumpf.cpp
  @brief A brief, one sentence description.

  A more detailed multiline description...

  @author Peter Drysdale, 
*/

#include<iomanip>
using std::scientific;
#include<cstdlib>
using std::setw;
#include<iostream>
using std::cout;
using std::cerr;
using std::endl;
#include"dumpf.h"

Dumpf::Dumpf() {
}

Dumpf::~Dumpf() {
  file.close();
}

void Dumpf::outputConfig( Configf& configf ) {
  int sp = configf.tellg();
  configf.seekg(0,std::ios::beg);
  configf.read(configf.buffer,configf.filesize);
  configf.seekg(sp);
  s->write(configf.buffer,configf.filesize);
  *this<<endl<<"============================================="<<endl<<endl;
}

void Dumpf::open( const string& filename ) {
  this->filename = filename;
  if( !file.is_open() ) {
    file.open( filename.c_str() );
    if( !file ) {
      cerr<<"Error, cannot open file'"<<filename.c_str()<<"' for output."
          <<endl;
      exit(EXIT_FAILURE);
    }
    s = &file;
    file.precision(14);
    file<<scientific;
  } else {
    cerr<<"Attempting to dump into two files."<<endl;
    exit(EXIT_FAILURE);
  }
}

void Dumpf::verbose() {
  if( file.is_open() ) {
    file.close();
  }
  s = &cout;
  s->precision(14);
  cout<<scientific;
}

Dumpf& Dumpf::operator<< ( double f ) {
  if( f>=0 ) {
    *s<<" ";

  }*s<<f;
  return *this;
}

Dumpf& Dumpf::operator<< ( const string& str ) {
  *s<<setw(20)<<str.c_str();
  return *this;
}

Dumpf& Dumpf::operator<< ( int i ) {
  *s<<i;
  return *this;
}

Dumpf& Dumpf::operator<< ( ostream& (*pf)(ostream&) ) {
  *s<<pf;
  return *this;
}

ostream& septor( ostream& os ) {
  //os<<"|";
  return os;
}

ostream& space( ostream& os ) {
  os<<" ";
  return os;
}

ostream& setw( ostream& os ) {
  os<<setw(20);
  return os;
}
