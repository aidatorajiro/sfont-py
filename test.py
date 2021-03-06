import unittest
from sfont import *
import os
import urllib.request
import tarfile
import io

if not os.path.exists("FluidR3_GS.sf2"):
    url = "http://deb.debian.org/debian/pool/main/f/fluid-soundfont/fluid-soundfont_3.1.orig.tar.gz"

    print("Downloading " + url + "...")

    with urllib.request.urlopen(url) as f:
        compressed = f.read()

    bio = io.BytesIO(compressed)

    tar = tarfile.open(fileobj=bio, mode="r:gz")

    data = tar.extractfile("fluid-soundfont-3.1/FluidR3_GS.sf2").read()

    print("Writing to FluidR3_GS.sf2...")

    with open("FluidR3_GS.sf2", "wb") as f:
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
        self.assertEqual(ctypes.sizeof(Sample), 40)
        self.assertEqual(ctypes.sizeof(SoundFont), 128)

    def test_data(self):
        sf = sfont.read_sound_font(b"FluidR3_GS.sf2").contents
        self.assertEqual(sf.presets.size(), 33)
        self.assertEqual(sf.presets[10].name, b'Screaming')
    
    def test_qlist_new(self):
        num = 114514
        size = 13
        orig_lst = (POINTER(c_int64) * size)(*map(lambda x: pointer(c_int64(x)), [num] * size))
        qlist = cast(sfont.qlist_new(size, cast(pointer(orig_lst), POINTER(c_void_p))),
                     POINTER(QList(c_int64))).contents
        self.assertEqual(qlist.size(), size)
        self.assertEqual(qlist[5], num)
    
    def test_mkList(self):
        qlist = mkList([c_int64(1),c_int64(2),c_int64(3)])
        self.assertEqual(qlist.size(), 3)
        self.assertEqual(qlist[1], 2)

if __name__ == '__main__':
    unittest.main()