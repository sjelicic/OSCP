nbits = 1024


#open()
# The open() function returns a file object which can used to read, write and modify file.

# If the file is not found, it raises FileNotFoundError exception.

# open(file, mode='r', buffering=-1, encoding=None, errors=None, newline=None, closefd=True, opener=None)

# open() Parameters

# file - path-like object (representing a file system path) giving the pathname
# mode (optional) - mode while opening a file. If not provided, it defaults to 'r' (open for reading in text mode). Available file modes are:

# Mode			Description
# 'r'				Open a file for reading. (default)
# 'w'				Open a file for writing. Creates a new file if it does not 
# 				exist or truncates the file if it exists.
# 'x'				Open a file for exclusive creation. If the file already 
# 				exists, the operation fails.
# 'a'				Open for appending at the end of the file without 
# 				truncating it. Creates a new file if it does not exist.
# 't'				Open in text mode. (default)
# 'b'				Open in binary mode.
# '+'				Open a file for updating (reading and writing)

# buffering (optional) - used for setting buffering policy
# encoding (optional) - name of the encoding to encode or decode the file
# errors (optional) - string specifying how to handle encoding/decoding errors
# newline​ (optional) - how newlines mode works (available values: None, ' ', '\n', 'r', and '\r\n'
# closefd (optional) - must be True (default) if given otherwise an exception will be raised
# opener (optional) - a custom opener; must return an open file descripto


#read()
# The method read() reads at most size bytes from the file. If the read hits EOF before obtaining size bytes, then it reads only available bytes.

# fileObject.read( size );

# Parameters
# size − This is the number of bytes to be read from the file.


#strip()
# The strip() removes characters from both left and right based on the argument (a string specifying the set of characters to be removed).

# The syntax of strip() is:

# string.strip([chars])

# strip() Parameters
# chars (optional) - a string specifying the set of characters to be removed.
# If the chars argument is not provided, all leading and trailing whitespaces are removed from the string.

password = open("/root/root.txt").read().strip()
enc_pass = open("output.txt","w")
debug = open("debug.txt","w")

#encode()
# Since Python 3.0, strings are stored as Unicode, i.e. each character in the string is represented by a code point. So, each string is just a sequence of Unicode code points.

# For efficient storage of these strings, the sequence of code points are converted into set of bytes. The process is known as encoding.

# There are various encodings present which treats a string differently. 
# Using string's encode() method, you can convert unicoded strings into any encodings supported by Python. By default, Python uses utf-8 encoding.

# The syntax of encode() method is:
# string.encode(encoding='UTF-8',errors='strict')

#https://docs.python.org/3/library/codecs.html#standard-encodings
# Codec 			Aliases 		Purpose 				Encoder / decoder
# hex_codec       hex 			Convert operand to 		binascii.b2a_hex() 													/ binascii.a2b_hex()
# 								hexadecimal 
# 								epresentation, 
# 								with two digits 
# 								per byte


#int()
# The int() method returns an integer object from any number or string.

# The syntax of int() method is:
# int(x=0, base=10)

# int() Parameters
# x - Number or string to be converted to integer object.
# Default argument is zero.
# base - Base of the number in x.
# Can be 0 (code literal) or 2-36.

# Return value from int()

# an integer object from the given number or string, treats default base as 10
# (No parameters) returns 0
# (If base given) treats the string in the given base (0, 2, 8, 10, 16)

#ovaj program koristi SageMath biblioteku
# http://www.sagemath.org/

# The Python types int and long are used to represent integers of limited 
# size. To handle arbitrary large integers with exact arithmetic, Sage uses its own type named Integer.

m = Integer(int(password.encode('hex'),16))

# floor()
# floor() method in Python returns floor of x i.e., the largest integer not greater than x.

# http://doc.sagemath.org/html/en/reference/rings_standard/sage/arith/misc.html?highlight=random_prime
# sage.arith.misc.random_prime(n, proof=None, lbound=2)
# Return a random prime p between lbound and n.

#n je 2 na floor(1024/2) - 1
#lbound je 2 na najveci integer manji od 1024/2 - 1
p = random_prime(2^floor(nbits/2)-1, lbound=2^floor(nbits/2-1), proof=False)
q = random_prime(2^floor(nbits/2)-1, lbound=2^floor(nbits/2-1), proof=False)
n = p*q
phi = (p-1)*(q-1)

# http://doc.sagemath.org/html/en/reference/rings_standard/sage/rings/integer_ring.html
# random_element(x=None, y=None, distribution=None)¶
# Return a random integer.
# If only one integer x is given, return an integer between 0 and x−1.

e = ZZ.random_element(phi)

#http://doc.sagemath.org/html/en/reference/categories/sage/categories/fields.html
#gcd(other)
#Greatest common divisor.

while gcd(e, phi) != 1:
    e = ZZ.random_element(phi)

#The pow() method returns x to the power of y. If the third argument (z) is given, it returns x to the power of y modulus z, i.e. pow(x, y) % z.

c = pow(m, e, n)

enc_pass.write('Encrypted Password: '+str(c)+'\n')
debug.write(str(p)+'\n')
debug.write(str(q)+'\n')
debug.write(str(e)+'\n')



# 1) otovri fajl root.txt, procitaj ga i ukloni sve leading i trailing whitespaces - password promenljiva
# 2) otvori output.txt za upisivanje - enc_pass promenljiva
# 3) otvori debug.txt za upisivanje - debug promenljiva
# 4) konvertovao password promenljivu u Integer promenljivu
# 	konvertovao root.txt u jedan veliki integer
# 5) enkodovao password promenljivu u heksdecimalnu vrednost oa zetim pretvorio tu vrednost u integer sa osnovom 16 i konvertovao u SageMath promenljivu Integer
# 6) kreiramo nasumicni prime broj p
# 7) kreiramo nasumicni prime broj q
# 8) n promenljiva = p * q
# 9) phi promenljiva = (p-1)*(q-1)
# 10) e promenljiva je nasumicni integer izmedju 0 i phi-1 vrednosti
#     e ce menjati sve dok najveci zajednicki delilac ne bude isti za e i phi
# 11) m na e modulus n - c promenljiva
# 12) upisujemo c u output.txt fajl kao string 
# 13) promenljive p, q, e upisane u debug fajl 
