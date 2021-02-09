//=============================================================================
//  MuseScore
//  Linux Music Score Editor
//  $Id:$
//
//  Copyright (C) 2010 Werner Schweer and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//=============================================================================

#include <vector>
#include <string>
#include <fstream>
using namespace std;

#ifndef SFONT_H
#define SFONT_H

#include <QtCore/QFile>

class Xml;
class QFile;

namespace SfTools {

//---------------------------------------------------------
//   sfVersionTag
//---------------------------------------------------------

struct sfVersionTag {
      int major;
      int minor;
      };

enum Modulator {
      };
enum Generator {
      Gen_StartAddrOfs, Gen_EndAddrOfs, Gen_StartLoopAddrOfs,
      Gen_EndLoopAddrOfs, Gen_StartAddrCoarseOfs, Gen_ModLFO2Pitch,
      Gen_VibLFO2Pitch, Gen_ModEnv2Pitch, Gen_FilterFc, Gen_FilterQ,
      Gen_ModLFO2FilterFc, Gen_ModEnv2FilterFc, Gen_EndAddrCoarseOfs,
      Gen_ModLFO2Vol, Gen_Unused1, Gen_ChorusSend, Gen_ReverbSend, Gen_Pan,
      Gen_Unused2, Gen_Unused3, Gen_Unused4,
      Gen_ModLFODelay, Gen_ModLFOFreq, Gen_VibLFODelay, Gen_VibLFOFreq,
      Gen_ModEnvDelay, Gen_ModEnvAttack, Gen_ModEnvHold, Gen_ModEnvDecay,
      Gen_ModEnvSustain, Gen_ModEnvRelease, Gen_Key2ModEnvHold,
      Gen_Key2ModEnvDecay, Gen_VolEnvDelay, Gen_VolEnvAttack,
      Gen_VolEnvHold, Gen_VolEnvDecay, Gen_VolEnvSustain, Gen_VolEnvRelease,
      Gen_Key2VolEnvHold, Gen_Key2VolEnvDecay, Gen_Instrument,
      Gen_Reserved1, Gen_KeyRange, Gen_VelRange,
      Gen_StartLoopAddrCoarseOfs, Gen_Keynum, Gen_Velocity,
      Gen_Attenuation, Gen_Reserved2, Gen_EndLoopAddrCoarseOfs,
      Gen_CoarseTune, Gen_FineTune, Gen_SampleId, Gen_SampleModes,
      Gen_Reserved3, Gen_ScaleTune, Gen_ExclusiveClass, Gen_OverrideRootKey,
      Gen_Dummy
      };

enum Transform { Linear };

//---------------------------------------------------------
//   ModulatorList
//---------------------------------------------------------

struct ModulatorList {
      Modulator src;
      Generator dst;
      int amount;
      Modulator amtSrc;
      Transform transform;
      };

//---------------------------------------------------------
//   GeneratorList
//---------------------------------------------------------

union GeneratorAmount {
      short sword;
      ushort uword;
      struct {
            uchar lo, hi;
            };
      };

struct GeneratorList {
      Generator gen;
      GeneratorAmount amount;
      };

//---------------------------------------------------------
//   Zone
//---------------------------------------------------------

struct Zone {
      vector<GeneratorList*> generators;
      vector<ModulatorList*> modulators;
      int instrumentIndex;
      };

//---------------------------------------------------------
//   Preset
//---------------------------------------------------------

struct Preset {
      char* name;
      int preset;
      int bank;
      int presetBagNdx; // used only for read
      int library;
      int genre;
      int morphology;
      vector<Zone*> zones;

      Preset():name(nullptr), preset(0), bank(0), presetBagNdx(0), library(0), genre(0), morphology(0) {}
      };

//---------------------------------------------------------
//   Instrument
//---------------------------------------------------------

struct Instrument {
      char* name;
      int index;        // used only for read
      vector<Zone*> zones;

      Instrument();
      ~Instrument();
      };

//---------------------------------------------------------
//   Sample
//---------------------------------------------------------

struct Sample {
      char* name;
      uint start;
      uint end;
      uint loopstart;
      uint loopend;
      uint samplerate;

      int origpitch;
      int pitchadj;
      int sampleLink;
      int sampletype;

      Sample();
      ~Sample();
      };

//---------------------------------------------------------
//   SoundFont
//---------------------------------------------------------

class SoundFont {
      string path;
      sfVersionTag version;
      char* engine;
      char* name;
      char* date;
      char* comment;
      char* tools;
      char* creator;
      char* product;
      char* copyright;
      char* irom;
      sfVersionTag iver;

      int samplePos;
      int sampleLen;

      vector<Preset*> presets;
      vector<Instrument*> instruments;

      vector<Zone*> pZones;
      vector<Zone*> iZones;
      vector<Sample*> samples;

      fstream file;
      fstream f;

      bool _compress;
      double _oggQuality;
      double _oggAmp;
      qint64 _oggSerial;

      // Extra option
      bool _smallSf;

      unsigned readDword();
      int readWord();
      int readShort();
      int readByte();
      int readChar();
      int readFourcc(const char*);
      int readFourcc(char*);
      void readSignature(const char* signature);
      void readSignature(char* signature);
      void skip(int);
      void readSection(const char* fourcc, int len);
      void readVersion(sfVersionTag* v);
      char* readString(int);
      void readPhdr(int);
      void readBag(int, vector<Zone*>*);
      void readMod(int, vector<Zone*>*);
      void readGen(int, vector<Zone*>*);
      void readInst(int);
      void readShdr(int);

      void writeDword(int);
      void writeWord(unsigned short int);
      void writeByte(unsigned char);
      void writeChar(char);
      void writeShort(short);
      void write(const char* p, int n);
      void writeSample(const Sample*);
      void writeStringSection(const char* fourcc, char* s);
      void writePreset(int zoneIdx, const Preset*);
      void writeModulator(const ModulatorList*);
      void writeGenerator(const GeneratorList*);
      void writeInstrument(int zoneIdx, const Instrument*);

      void writeIfil();
      void writeIver();
      void writeSmpl();
      void writePhdr();
      void writeBag(const char* fourcc, vector<Zone*>*);
      void writeMod(const char* fourcc, const vector<Zone*>*);
      void writeGen(const char* fourcc, vector<Zone*>*);
      void writeInst();
      void writeShdr();

      int writeCompressedSample(Sample*);
      int writeUncompressedSample(Sample* s);
      bool writeCSample(Sample*, int);
      bool write();

   public:
      SoundFont(const string&);
      ~SoundFont();
      bool read();
      bool compress(fstream f, double oggQuality, double oggAmp, qint64 oggSerial = rand());
      bool uncompress(fstream f);
      bool writeCode(vector<int>);
      bool writeCode();
      void dumpPresets();

#ifndef SFTOOLS_NOXML
    private:
      void write(Xml&, Zone*);
      bool writeSampleFile(Sample*, string);

    public:
      bool readXml(fstream);
      bool writeXml(fstream);
#endif
};
}
#endif

