from ctypes import *

sfont = cdll.LoadLibrary("sfont.dylib")

sfont.read_sound_font.argtypes = [c_char_p]

sf = sfont.read_sound_font(b"FluidR3_GM.sf2")

