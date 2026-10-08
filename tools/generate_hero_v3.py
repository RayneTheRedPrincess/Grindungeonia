from PIL import Image, ImageDraw
from pathlib import Path
import json
out=Path(__file__).resolve().parents[1]/'graphics'
palette=['#000000','#151b29','#253449','#36485b','#536477','#89969a','#b9b9a5','#d9c7a4','#efddba','#493742','#7e4b4b','#b36e55','#d89a6d','#2c5b60','#498d84','#f7f2d8']
pal=[]
for c in palette:pal.extend(bytes.fromhex(c[1:]))
pal += [0]*(768-len(pal))
sheet=Image.new('P',(32,192),0)
for direction in range(3):
 for phase in range(2):
  im=Image.new('P',(32,32),0);d=ImageDraw.Draw(im)
  shift=phase
  d.ellipse((7,27,26,30),fill=1)
  d.polygon([(12,13),(22,13),(27,27),(8,27)],fill=1)
  d.polygon([(13,14),(21,14),(24,25),(10,25)],fill=13)
  d.line((17,16,17,25),fill=3,width=2)
  d.rectangle((12+shift,25,15+shift,29),fill=2)
  d.rectangle((19-shift,25,22-shift,29),fill=2)
  d.rectangle((11+shift,28,16+shift,30),fill=1)
  d.rectangle((18-shift,28,23-shift,30),fill=1)
  d.polygon([(11,13),(22,13),(24,22),(10,22)],fill=1)
  d.polygon([(12,14),(21,14),(22,21),(12,21)],fill=4)
  d.line((13,17,21,17),fill=5)
  d.rectangle((15,20,19,22),fill=11)
  d.rectangle((7,15+shift,11,23+shift),fill=1)
  d.rectangle((8,16+shift,10,22+shift),fill=10)
  d.rectangle((23,15-shift,27,23-shift),fill=1)
  d.rectangle((24,16-shift,26,22-shift),fill=10)
  d.rectangle((14,11,20,15),fill=1)
  d.ellipse((10,2,24,16),fill=1)
  d.ellipse((12,3,22,14),fill=5)
  d.polygon([(12,8),(13,4),(17,2),(22,4),(23,9)],fill=3)
  d.line((12,8,23,8),fill=6,width=2)
  d.line((16,3,16,8),fill=7)
  if direction==0:
   d.rectangle((13,10,21,14),fill=11)
   d.point((14,11),fill=15);d.point((20,11),fill=15)
   d.line((15,14,19,14),fill=1)
   d.rectangle((14,17,20,18),fill=6)
  elif direction==1:
   d.polygon([(12,9),(22,9),(22,14),(12,14)],fill=3)
   d.line((13,12,21,12),fill=5)
   d.rectangle((14,17,20,20),fill=13)
  else:
   d.rectangle((18,10,22,13),fill=11)
   d.point((21,11),fill=15)
   d.line((22,8,23,12),fill=7)
   d.line((10,18,10,24),fill=6)
  d.point((17,16),fill=15)
  sheet.paste(im,(0,(direction*2+phase)*32))
sheet.putpalette(pal)
sheet.save(out/'hero_anim.bmp')
(out/'hero_anim.json').write_text(json.dumps({'type':'sprite','height':32},indent=2)+'\n')
print('Generated 32x32 hero with 6 directional/walk frames')
