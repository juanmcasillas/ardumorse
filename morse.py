#!/usr/bin/env python3
# 
# Implement the MORSE alphabet in some way to do anything with it
#
# (c) 2019 Juan M. Casillas <juanm.casillas@gmail.com>
#
# usage: python3 generate_indesign.py <generates output.csv>
#
# International morse code
# 1. The length of a dot is one unit.
# 2. A dash is three units.
# 3. The space between parts of the same letter is one unit.
# 4. The space between letters is three units.
# 5. The space between words is seven units.
#

import re
import os

class Morse:
    def __init__(self):
        "morse code generator. - means -, . dot"
        self.alphabet = {}

    def from_file(self, fname):
        c = 0
        regex=re.compile("\s+", re.IGNORECASE)
        fd = open(fname)
        for l in fd.readlines():
            r = regex.sub("",l)
            if len(r) < 0:
                continue
            letter = r[0].lower()
            dots = r[1:]
            self.alphabet[letter] = dots
            c+=1
        fd.close()
        print("Loaded %d symbols" % c)

    def to_python_dict(self, name="morse"):
        s = [ "%s = {}" % name ]

        for k in self.alphabet.keys():
            v = self.alphabet[k]
            s.append("%s['%s']='%s'" % (name, k,v))
        
        return(os.linesep.join(s))
           
    def to_c(self, name="morse"):
        # const char *morse[] = { "hello", "world"};


        content = "const char *%s[] = {\n%s\n};" 
        s = []

        # build the lookup table based on ASCII.
        for i in range(ord('0'),ord('Z')+1):
            k = chr(i).lower()
            v=""
            if k in self.alphabet.keys():
                # found, store thing
                v = self.alphabet[k]
            s.append('  /* %s */     "%s" ' % (k.upper(),v))
        
        s = ",\n".join(s)

        content = content % (name, s)
        return(content)

    def xlate(self, s, ignore=True):
        r = []
        for l in s.lower():
            if l not in self.alphabet:
                if not ignore:
                    raise ValueError("Symbol '%s' not found" % l)
                else:
                    print("Warning: symbol '%s' not found. Skipping" % l)
                    continue
            r.append( (l,self.alphabet[l]))
        
        return(r)


if __name__ == "__main__":

    m = Morse()
    m.from_file("morse.txt")
    #print(m.to_python_dict())
    print(m.to_c())
    r = m.xlate("hello world")
    print(r)