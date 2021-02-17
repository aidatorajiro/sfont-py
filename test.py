import unittest
from sfont import *
import os
import urllib.request
import tarfile
import io

if not os.path.exists("FluidR3_GM.sf2"):
    url = "http://deb.debian.org/debian/pool/main/f/fluid-soundfont/fluid-soundfont_3.1.orig.tar.gz"

    print("Downloading " + url + "...")

    with urllib.request.urlopen(url) as f:
        compressed = f.read()

    bio = io.BytesIO(compressed)

    tar = tarfile.open(fileobj=bio, mode="r:gz")

    data = tar.extractfile("fluid-soundfont-3.1/FluidR3_GM.sf2").read()

    print("Writing to FluidR3_GM.sf2...")

    with open("FluidR3_GM.sf2", "wb") as f:
        f.write(data)

class SfontTest(unittest.TestCase):
    def test_type(self):
        self.assertEqual(ctypes.sizeof(sfVersionTag), 8)
        self.assertEqual(ctypes.sizeof(ModulatorList), 20)
        self.assertEqual(ctypes.sizeof(GeneratorAmount), 2)
        self.assertEqual(ctypes.sizeof(GeneratorList), 8)
        self.assertEqual(ctypes.sizeof(Zone), 24)
        self.assertEqual(ctypes.sizeof(Preset), 40)
        self.assertEqual(ctypes.sizeof(Instrument), 24)
        self.assertEqual(ctypes.sizeof(Sample), 48)
        self.assertEqual(ctypes.sizeof(SoundFont), 144)

    def test_data(self):
        sf = sfont.read_sound_font(b"FluidR3_GM.sf2").contents
        self.assertEqual(sf.presets.size(), 189)
        self.assertEqual(sf.presets.array()[10].contents.name, b'Burst Noise')

if __name__ == '__main__':
    unittest.main()