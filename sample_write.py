from sfont import *
sf = sfont.read_sound_font(b"FluidR3_GM.sf2").contents
sfont.write_sound_font(sf, b"test_output.sf2")
print("finished!")