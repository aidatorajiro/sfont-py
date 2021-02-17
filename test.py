from sfont import *
import os
import urllib.request
import tarfile
import io

if not os.path.exists("FluidR3_GM.sf2"):
    url = "http://deb.debian.org/debian/pool/main/f/fluid-soundfont/fluid-soundfont_3.1.orig.tar.gz"

    print("downloading " + url + "...")

    with urllib.request.urlopen(url) as f:
        compressed = f.read()
    
    bio = io.BytesIO(compressed)

    tar = tarfile.open(fileobj=bio, mode="r:gz")

    data = tar.extractfile("fluid-soundfont-3.1/FluidR3_GM.sf2").read()

    with open("FluidR3_GM.sf2", "wb") as f:
        f.write(data)

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