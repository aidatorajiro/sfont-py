#define SFTOOLS_NOXML

#include <vector>
#include "sfont.h"
#include "sfont.cpp"
#include "xml.h"
#include "xml.cpp"
using namespace std;

bool smallSf = false;

int main(int argc, char *argv[]){
  const QString &qs = QString("FluidR3_GS.sf2");

  SoundFont *sf = new SoundFont(qs);
  sf->read();

  const QString &qs2 = QString("test_output.sf2");
  QFile f(qs2);
  if (!f.open(QIODevice::ReadWrite)) {
      fprintf(stderr, "cannot open %s\n", f.fileName().toLocal8Bit().data());
      return 1;
  }
  if (!sf->write(&f, 0, 0, 0)) {
      fprintf(stderr, "cannot write successfully\n");
      f.close();
      return 1;
  }
  f.close();
  
  return 0;
}
