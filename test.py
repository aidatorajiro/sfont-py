from sfont import *

print("sfVersionTag: %d" % ctypes.sizeof(sfVersionTag))
print("ModulatorList: %d" % ctypes.sizeof(ModulatorList))
print("GeneratorAmount: %d" % ctypes.sizeof(GeneratorAmount))
print("GeneratorList: %d" % ctypes.sizeof(GeneratorList))
print("Zone: %d" % ctypes.sizeof(Zone))
print("Preset: %d" % ctypes.sizeof(Preset))
print("Instrument: %d" % ctypes.sizeof(Instrument))
print("Sample: %d" % ctypes.sizeof(Sample))
print("SoundFont: %d" % ctypes.sizeof(SoundFont))

sf = sfont.read_sound_font(b"FluidR3_GM.sf2").contents

print(sf.presets.size() == 189)
print(sf.presets.array()[10].contents.name == b'Burst Noise')