from sfont import *
import datetime
import time

sf = sfont.new_sound_font().contents

sf.version = sfVersionTag(2, 1)
sf.engine = b'E-mu 10K1'
sf.name = b'Test SF'
sf.date = time.trftime("%b %d. %Y").encode()
sf.comment = b'A sample soundfont.'
sf.tools = b'sfont.py'
sf.creator = b'Waiwai Gayagaya'
sf.product = b'SBAWE32'
sf.copyright = b'No Copyright'
sf.irom = b''
sf.iver = sfVersionTag(0, 0)
sf.samplePos = 0
sf.sampleLen = 10000000
# sf.presets = 
# sf.instruments = 
# sf.pZones = 
# sf.iZones = 
# sf.samples = 