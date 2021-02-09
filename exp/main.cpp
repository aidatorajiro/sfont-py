#define SFTOOLS_NOXML

#include "sfont.h"
#include "sfont.cpp"

int main(int argc, char *argv[]){
  const QString &qs = QString("../FluidR3_GM.sf2");

  SfTools::SoundFont *sf = new SfTools::SoundFont(qs);
  sf->read();
  
  printf("=== TYPE SIZES ===\n");
  
  printf("sfVersionTag: %d\n", sizeof(sfVersionTag));
  printf("Modulator: %d\n", sizeof(Modulator));
  printf("Generator: %d\n", sizeof(Generator));
  printf("Transform: %d\n", sizeof(Transform));
  printf("ModulatorList: %d\n", sizeof(ModulatorList));
  printf("GeneratorAmount: %d\n", sizeof(GeneratorAmount));
  printf("GeneratorList: %d\n", sizeof(GeneratorList));
  printf("Zone: %d\n", sizeof(Zone));
  printf("Preset: %d\n", sizeof(Preset));
  printf("Instrument: %d\n", sizeof(Instrument));
  printf("Sample: %d\n", sizeof(Sample));
  printf("SoundFont: %d\n", sizeof(SoundFont));
  printf("QString: %d\n", sizeof(QString));
  printf("QList: %d\n", sizeof(QList<QString>));
  
  return 0;
}
