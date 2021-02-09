#define SFTOOLS_NOXML

#include "sfont.h"
#include "sfont.cpp"

int main(int argc, char *argv[]){
  const QString &qs = QString("aaa");

  new SfTools::SoundFont(qs);
  
  return 0;
}
