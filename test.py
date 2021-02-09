from ctypes import *
import ctypes
from enum import Enum

class sfVersionTag(Structure):
    _fields_ = [
        ("major", c_int),
        ("minor", c_int),
    ]

class Modulator(Enum):
    pass

class Generator(Enum):
    Gen_StartAddrOfs = 0
    Gen_EndAddrOfs = 1
    Gen_StartLoopAddrOfs = 2
    Gen_EndLoopAddrOfs = 3
    Gen_StartAddrCoarseOfs = 4
    Gen_ModLFO2Pitch = 5
    Gen_VibLFO2Pitch = 6
    Gen_ModEnv2Pitch = 7
    Gen_FilterFc = 8
    Gen_FilterQ = 9
    Gen_ModLFO2FilterFc = 10
    Gen_ModEnv2FilterFc = 11
    Gen_EndAddrCoarseOfs = 12
    Gen_ModLFO2Vol = 13
    Gen_Unused1 = 14
    Gen_ChorusSend = 15
    Gen_ReverbSend = 16
    Gen_Pan = 17
    Gen_Unused2 = 18
    Gen_Unused3 = 19
    Gen_Unused4 = 20
    Gen_ModLFODelay = 21
    Gen_ModLFOFreq = 22
    Gen_VibLFODelay = 23
    Gen_VibLFOFreq = 24
    Gen_ModEnvDelay = 25
    Gen_ModEnvAttack = 26
    Gen_ModEnvHold = 27
    Gen_ModEnvDecay = 28
    Gen_ModEnvSustain = 29
    Gen_ModEnvRelease = 30
    Gen_Key2ModEnvHold = 31
    Gen_Key2ModEnvDecay = 32
    Gen_VolEnvDelay = 33
    Gen_VolEnvAttack = 34
    Gen_VolEnvHold = 35
    Gen_VolEnvDecay = 36
    Gen_VolEnvSustain = 37
    Gen_VolEnvRelease = 38
    Gen_Key2VolEnvHold = 39
    Gen_Key2VolEnvDecay = 40
    Gen_Instrument = 41
    Gen_Reserved1 = 42
    Gen_KeyRange = 43
    Gen_VelRange = 44
    Gen_StartLoopAddrCoarseOfs = 45
    Gen_Keynum = 46
    Gen_Velocity = 47
    Gen_Attenuation = 48
    Gen_Reserved2 = 49
    Gen_EndLoopAddrCoarseOfs = 50
    Gen_CoarseTune = 51
    Gen_FineTune = 52
    Gen_SampleId = 53
    Gen_SampleModes = 54
    Gen_Reserved3 = 55
    Gen_ScaleTune = 56
    Gen_ExclusiveClass = 57
    Gen_OverrideRootKey = 58
    Gen_Dummy = 59

class Transform(Enum):
    Linear = 0

class ModulatorList(Structure):
    _fields_ = [
        ("src", c_int), # Modulator
        ("dst", c_int), # Generator
        ("amount", c_int),
        ("amtSrc", c_int), # Modulator
        ("transform", c_int), # Transform
    ]

class GeneratorAmount(Structure):
    _fields_ = [
        ("lo", c_ubyte),
        ("hi", c_ubyte)
    ]

class GeneratorList(Structure):
    _fields_ = [
        ("gen", c_int), # Generator
        ("amount", GeneratorAmount),
    ]

class Zone(Structure):
    _fields_ = [
        ("generators", c_void_p), # QList<GeneratorList*>
        ("modulators", c_void_p), # QList<ModulatorList*>
        ("instrumentIndex", c_int),
    ]

class Preset(Structure):
    _fields_ = [
        ("name", c_char_p),
        ("preset", c_int),
        ("bank", c_int),
        ("presetBagNdx", c_int),
        ("library", c_int),
        ("genre", c_int),
        ("morphology", c_int),
        ("zones", c_void_p), # QList<Zone*>
    ]

class Instrument(Structure):
    _fields_ = [
        ("name", c_char_p),
        ("index", c_int),
        ("zones", c_void_p), # QList<Zone*>
    ]

class Sample(Structure):
    _fields_ = [
        ("name", c_char_p),
        ("start", c_uint),
        ("end", c_uint),
        ("loopstart", c_uint),
        ("loopend", c_uint),
        ("samplerate", c_uint),
        ("origpitch", c_int),
        ("pitchadj", c_int),
        ("sampleLink", c_int),
        ("sampletype", c_int)
    ]

class SoundFont(Structure):
    _fields_ = [
        ("path", c_void_p), # QString
        ("version", sfVersionTag), # sfVersionTag
        ("engine", c_char_p),
        ("name", c_char_p),
        ("date", c_char_p),
        ("comment", c_char_p),
        ("tools", c_char_p),
        ("creator", c_char_p),
        ("product", c_char_p),
        ("copyright", c_char_p),
        ("irom", c_char_p),
        ("iver", sfVersionTag), # sfVersionTag
        ("samplePos", c_int),
        ("sampleLen", c_int),
        ("presets", c_void_p), # QList<Preset*>
        ("instruments", c_void_p), # QList<Instrument*>
        ("pZones", c_void_p), # QList<Zone*>
        ("iZones", c_void_p), # QList<Zone*>
        ("samples", c_void_p), # QList<Sample*>
    ]

sfont = cdll.LoadLibrary("sfont.dylib")

print("sfVersionTag: %d" % ctypes.sizeof(sfVersionTag))
print("ModulatorList: %d" % ctypes.sizeof(ModulatorList))
print("GeneratorAmount: %d" % ctypes.sizeof(GeneratorAmount))
print("GeneratorList: %d" % ctypes.sizeof(GeneratorList))
print("Zone: %d" % ctypes.sizeof(Zone))
print("Preset: %d" % ctypes.sizeof(Preset))
print("Instrument: %d" % ctypes.sizeof(Instrument))
print("Sample: %d" % ctypes.sizeof(Sample))
print("SoundFont: %d" % ctypes.sizeof(SoundFont))

sfont.read_sound_font.argtypes = [c_char_p]
sfont.read_sound_font.restype = POINTER(SoundFont)

sf = sfont.read_sound_font(b"FluidR3_GM.sf2")
