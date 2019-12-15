/*
Morse

 
 Implement the MORSE alphabet in some way to do anything with it

 (c) 2019 Juan M. Casillas <juanm.casillas@gmail.com>

 usage: python3 generate_indesign.py <generates output.csv>

 International morse code
 1. The length of a dot is one unit.
 2. A dash is three units.
 3. The space between parts of the same letter is one unit.
 4. The space between letters is three units.
 5. The space between words is seven units.

Build a table, with 0 offset, so we can store a lookup table based on char
0011 0000	48	30	0
0011 0001	49	31	1
0011 0010	50	32	2
0011 0011	51	33	3
0011 0100	52	34	4
0011 0101	53	35	5
0011 0110	54	36	6
0011 0111	55	37	7
0011 1000	56	38	8
0011 1001	57	39	9
0011 1010	58	3A	XXXX (invalid, zero filled)
0011 1011	59	3B	XXXX (invalid, zero filled)
0011 1100	60	3C	XXXX (invalid, zero filled)
0011 1101	61	3D	XXXX (invalid, zero filled)
0011 1110	62	3E	XXXX (invalid, zero filled)
0011 1111	63	3F	XXXX (invalid, zero filled)
0100 0000	64	40	XXXX (invalid, zero filled)
0100 0001	65	41	A
0100 0010	66	42	B
0100 0011	67	43	C
0100 0100	68	44	D
0100 0101	69	45	E
0100 0110	70	46	F
0100 0111	71	47	G
0100 1000	72	48	H
0100 1001	73	49	I
0100 1010	74	4A	J
0100 1011	75	4B	K
0100 1100	76	4C	L
0100 1101	77	4D	M
0100 1110	78	4E	N
0100 1111	79	4F	O
0101 0000	80	50	P
0101 0001	81	51	Q
0101 0010	82	52	R
0101 0011	83	53	S
0101 0100	84	54	T
0101 0101	85	55	U
0101 0110	86	56	V
0101 0111	87	57	W
0101 1000	88	58	X
0101 1001	89	59	Y
0101 1010	90	5A	Z
*/

const char DOT = '.';
const char DASH = '-';
const char SPACE = ' ';
int UNIT = 500; // 0.5 seconds

const char *MORSE[] = {
  /* 0 */     "-----" ,
  /* 1 */     ".----" ,
  /* 2 */     "..---" ,
  /* 3 */     "...--" ,
  /* 4 */     "....-" ,
  /* 5 */     "....." ,
  /* 6 */     "-...." ,
  /* 7 */     "--..." ,
  /* 8 */     "---.." ,
  /* 9 */     "----." ,
  /* : */     "" ,
  /* ; */     "" ,
  /* < */     "" ,
  /* = */     "" ,
  /* > */     "" ,
  /* ? */     "" ,
  /* @ */     "" ,
  /* A */     ".-" ,
  /* B */     "-..." ,
  /* C */     "-.-." ,
  /* D */     "-.." ,
  /* E */     "." ,
  /* F */     "..-." ,
  /* G */     "--." ,
  /* H */     "...." ,
  /* I */     ".." ,
  /* J */     ".---" ,
  /* K */     "-.-" ,
  /* L */     ".-.." ,
  /* M */     "--" ,
  /* N */     "-." ,
  /* O */     "---" ,
  /* P */     ".--." ,
  /* Q */     "--.-" ,
  /* R */     ".-." ,
  /* S */     "..." ,
  /* T */     "-" ,
  /* U */     "..-" ,
  /* V */     "...-" ,
  /* W */     ".--" ,
  /* X */     "-..-" ,
  /* Y */     "-.--" ,
  /* Z */     "--.." 
};

void wait_units(char c) {

    switch (c) {
        case SPACE:
            delay(7 * UNIT); // The space between words is seven units.
            break;

        case DOT:
            delay(1 * UNIT); // 1. The length of a dot is one unit.
            break;

        case DASH:
            delay(3 * UNIT); // 2. A dash is three units.
            break;
    }

}

void xlate(const char *s) {

int i = 0;
char  b = 0;
const char *r = 0;

    while (s[i] != 0) {
        b = toupper(s[i]); // upper case only
       
        // WORD CHANGE
        if (b == SPACE) {
            // word unit. wait 7
            Serial.println("<space>");
            wait_units(SPACE);
            i++;
            continue;
        }
        Serial.print(b);
        Serial.print(" :");
        
        /* avoid the invalid range 58-64, < 48, > 90 */
        if (strlen(r) > 0 && b >= '0' && b <= 'Z') {
            r = MORSE[b-'0']; // starts on 0
            // r is a string with . and -

            int j = 0;
            while (r[j] != 0) {
                digitalWrite(LED_BUILTIN, HIGH);   
                Serial.print(r[j]);
                wait_units(r[j]);
                digitalWrite(LED_BUILTIN, LOW);   
                wait_units(DOT); // 3. The space between parts of the same letter is one unit.
                j++;
            }
        }
        Serial.println("<endletter>");
        wait_units(DASH);  // 4. The space between letters is three units.
        i++;
    }
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Morse Christmas lights Ready");
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, LOW);   
  xlate("Hello world");

}