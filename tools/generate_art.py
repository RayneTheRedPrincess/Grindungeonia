from PIL import Image, ImageDraw
from pathlib import Path
import json
p=Path(__file__).resolve().parents[1]/"graphics"
p.mkdir(exist_ok=True)
colors=["#000000","#141b2b","#27364a","#354c57","#566875","#899a99","#b4b7a2","#d4c7a3","#efdbaf","#513b42","#87544e","#c78561","#d9a77a","#36655c","#54a089","#f0f2d5"]
pal=[]
for c in colors: pal.extend(bytes.fromhex(c[1:]))
pal += [0]*(768-len(pal))
def save(name,im,typ="sprite"):
    im.putpalette(pal)
    im.save(p/(name+".bmp"))
    (p/(name+".json")).write_text(json.dumps({"type":typ,"height":im.height} if typ=="sprite" else {"type":typ}))
im=Image.new("P",(16,16),0);d=ImageDraw.Draw(im)
d.ellipse((4,1,11,8),fill=7,outline=2);d.rectangle((5,8,10,13),fill=13,outline=2);d.rectangle((3,9,4,12),fill=5);d.rectangle((11,9,12,12),fill=5);d.rectangle((5,14,6,15),fill=2);d.rectangle((9,14,10,15),fill=2);d.point((6,5),fill=1);d.point((9,5),fill=1);save("hero",im)
im=Image.new("P",(16,16),0);d=ImageDraw.Draw(im);d.ellipse((1,4,14,14),fill=10,outline=2);d.polygon([(3,6),(4,1),(7,5)],fill=9);d.polygon([(9,5),(12,1),(13,7)],fill=9);d.rectangle((4,8,6,9),fill=15);d.rectangle((10,8,12,9),fill=15);save("fiend",im)
im=Image.new("P",(16,16),0);d=ImageDraw.Draw(im);d.line((2,13,13,2),fill=15,width=2);d.line((5,14,14,5),fill=8,width=2);save("slash",im)
im=Image.new("P",(256,256),1);d=ImageDraw.Draw(im)
for y in range(0,256,16):
    for x in range(0,256,16):
        d.rectangle((x,y,x+15,y+15),fill=2 if (x//16+y//16)%3 else 3)
        d.line((x,y,x+15,y),fill=1);d.line((x,y,x,y+15),fill=1)
for i in range(0,256,16):
    d.rectangle((i,48,i+15,63),fill=9);d.rectangle((i,176,i+15,191),fill=9)
for y in range(48,192,16):
    d.rectangle((8,y,23,y+15),fill=9);d.rectangle((232,y,247,y+15),fill=9)
for x,y in [(55,100),(185,124),(112,156)]:
    d.rectangle((x,y,x+15,y+15),fill=4,outline=1);d.rectangle((x+3,y+2,x+12,y+5),fill=5)
save("crypt",im,"regular_bg")
