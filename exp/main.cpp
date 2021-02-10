#define SFTOOLS_NOXML

#include <vector>
#include "sfont.h"
#include "sfont.cpp"
using namespace std;

int main(int argc, char *argv[]){
  const QString &qs = QString("../FluidR3_GM.sf2");

  SfTools::SoundFont *sf = new SfTools::SoundFont(qs);
  sf->read();
  
  printf("=== TYPE SIZES ===\n");
  
  printf("sfVersionTag: %lu\n", sizeof(sfVersionTag));
  printf("Modulator: %lu\n", sizeof(Modulator));
  printf("Generator: %lu\n", sizeof(Generator));
  printf("Transform: %lu\n", sizeof(Transform));
  printf("ModulatorList: %lu\n", sizeof(ModulatorList));
  printf("GeneratorAmount: %lu\n", sizeof(GeneratorAmount));
  printf("GeneratorList: %lu\n", sizeof(GeneratorList));
  printf("Zone: %lu\n", sizeof(Zone));
  printf("Preset: %lu\n", sizeof(Preset));
  printf("Instrument: %lu\n", sizeof(Instrument));
  printf("Sample: %lu\n", sizeof(Sample));
  printf("SoundFont: %lu\n", sizeof(SoundFont));
  printf("QString: %lu\n", sizeof(QString));
  printf("QList: %lu\n", sizeof(QList<SoundFont*>));
  printf("%d\n", sf->presets.size());
  
  return 0;
}
