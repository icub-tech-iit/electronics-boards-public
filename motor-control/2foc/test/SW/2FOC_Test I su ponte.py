import sys

KI = 0.76277

errlist = {1:"VDC too low to perform test",
           2:"VDC too high to perform test",

           10:"MOS closed: YL XH  - read allegro X - too low",
           11:"MOS closed: YL XH  - read allegro X - too high",
           
           12:"MOS closed: XL YH  - read allegro X - too low",
           13:"MOS closed: XL YH  - read allegro X - too high",
           
           14:"MOS closed: ZL YH  - read allegro Z - too low",
           15:"MOS closed: ZL YH  - read allegro Z - too high",

           16:"MOS closed: YL ZH  - read allegro Z - too low",
           17:"MOS closed: YL ZH  - read allegro Z - too high",

           18:"MOS closed: XL ZH  - read allegro X,Z - X too low",
           19:"MOS closed: XL ZH  - read allegro X,Z - X too high",
           20:"MOS closed: XL ZH  - read allegro X,Z - Z too low",
           21:"MOS closed: XL ZH  - read allegro X,Z - Z too high",

           22:"MOS closed: ZL XH  - read allegro X,Z - X too low",
           23:"MOS closed: ZL XH  - read allegro X,Z - X too high",
           24:"MOS closed: ZL XH  - read allegro X,Z - Z too low",
           25:"MOS closed: ZL XH  - read allegro X,Z - Z too high",}
           

string = raw_input ("enter 2FOC I test error string\n")
print ""
hexlist= string.split()

if hexlist[:3] != ["0xfe","0xff","0xff"]:
        print "String is not valid"
        sys.exit(0)


hexlist = hexlist [4:]

#for i in hexlist :
 #       print i

erridx = int(hexlist[0],16)
print "error code " + str(erridx)
print errlist[erridx]

if int(hexlist[1],16) == 0 :
        print "protection is NOT fired"
else:
        print "protection IS fired"

i1_lsb = int(hexlist[2],16);
i1_msb = int(hexlist[3],16);

i2_lsb = int(hexlist[4],16);
i2_msb = int(hexlist[5],16);


i1 = i1_lsb + (i1_msb <<8);
i2 = i2_lsb + (i2_msb <<8);



i1 = i1 * KI
i2 = i2 * KI

print "allegro X read " + str(i1) + " mA"
print "allegro Z read " + str(i2) + " mA"




