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

class QString(Structure):
    _fields_ = [
        ("data", c_void_p)
    ]

ALL_QLISTS = {}

def QList(in_type):
    if in_type in ALL_QLISTS:
        return ALL_QLISTS[in_type]
    
    class Insta(Structure):
        _fields_ = [
            ("ptr", c_void_p)
        ]
        
        datatype = POINTER(in_type)
        def __len__(self):
            return self.size()
        def __getitem__(self, key):
            return self.raw_array()[0][key][0]
        def __setitem__(self, key, value):
            self.raw_array()[0][key][0] = value
        def size(self):
            return sfont.qlist_size(pointer(c_void_p(self.ptr)))
        def raw_array(self):
            if self.size() == 0:
                return []
            else:
                return cast(sfont.qlist_first(pointer(c_void_p(self.ptr))), POINTER(self.datatype * self.size()))
    
    Insta.__name__ = "QList_%s" % in_type.__name__
    ALL_QLISTS[in_type] = Insta
    return Insta

def mkList(py_lst, datatype=None):
    if datatype is None:
        datatype = type(py_lst[0])
    size = len(py_lst)
    simple_lst = (c_void_p * size)(*map(lambda x: cast(pointer(x), c_void_p), py_lst))
    qlist = cast(sfont.qlist_new(size, cast(pointer(simple_lst), POINTER(c_void_p))),
                 POINTER(QList(datatype)))[0]
    return qlist

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
        ("generators", QList(GeneratorList)), # QList<GeneratorList*>
        ("modulators", QList(ModulatorList)), # QList<ModulatorList*>
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
        ("zones", QList(Zone)), # QList<Zone*>
    ]

class Instrument(Structure):
    _fields_ = [
        ("name", c_char_p),
        ("index", c_int),
        ("zones", QList(Zone)), # QList<Zone*>
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
        ("sampletype", c_int)
    ]

class SoundFont(Structure):
    _fields_ = [
        ("path", QString), # QString
        ("version", sfVersionTag), # sfVersionTag
        ("engine", c_char_p),
        ("name", c_char_p),
        ("date", c_char_p),
        ("comment", c_char_p),
        ("tools", c_char_p),
        ("creator", c_char_p),
        ("product", c_char_p),
        ("copyright", c_char_p),
        ("samplePos", c_int),
        ("sampleLen", c_int),
        ("presets", QList(Preset)), # QList<Preset*>
        ("instruments", QList(Instrument)), # QList<Instrument*>
        ("pZones", QList(Zone)), # QList<Zone*>
        ("iZones", QList(Zone)), # QList<Zone*>
        ("samples", QList(Sample)), # QList<Sample*>
    ]

sfont = cdll.LoadLibrary("sfont.dylib")

sfont.read_sound_font.argtypes = [c_char_p]
sfont.read_sound_font.restype = POINTER(SoundFont)

sfont.qlist_size.argtypes = [POINTER(c_void_p)]
sfont.qlist_size.restype = c_int

sfont.qlist_first.argtypes = [POINTER(c_void_p)]
sfont.qlist_first.restype = POINTER(c_void_p)

sfont.qlist_new.argtypes = [c_int, POINTER(c_void_p)]
sfont.qlist_new.restype = POINTER(c_void_p)

sfont.new_sound_font.argtypes = []
sfont.new_sound_font.restype = POINTER(SoundFont)

sfont.write_sound_font.argtypes = [POINTER(SoundFont), c_char_p]
sfont.write_sound_font.restype = c_bool