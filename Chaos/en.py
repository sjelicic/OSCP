# coding: utf-8
from Crypto.Cipher import AES
from Crypto.Hash import SHA256
from Crypto import Random

# Takes as input a 32-byte key and an arbitrary-length plaintext and returns a
# pair (iv, ciphtertext). "iv" stands for initialization vector.
def encrypt(key, filename):
    chunksize = 64*1024
    outputFile = "en" + filename
    filesize = str(os.path.getsize(filename)).zfill(16)
    # Choose a random, 16-byte IV.
    IV =Random.new().read(16)

    #Ciphertext Block Chaining, defined in NIST SP 800-38A, section 6.2. 
    #It is a mode of operation where each plaintext block gets XOR-ed with the previous ciphertext block prior to encryption.

    #https://pycryptodome.readthedocs.io/en/latest/src/cipher/classic.html#cbc-mode
    # The new() function at the module level under Crypto.Cipher instantiates a new CBC cipher object for the relevant base algorithm. 
    #In the following definition, <algorithm> could be AES:

    # Crypto.Cipher.<algorithm>.new(key, mode, *, iv=None)
    # Create a new CBC object, using <algorithm> as the base block cipher.

    # Parameters: 
    # key (bytes) – the cryptographic key
    # mode – the constant Crypto.Cipher.<algorithm>.MODE_CBC
    # iv (bytes) – the Initialization Vector. A piece of data unpredictable to adversaries. It is as long as the block size (e.g. 16 bytes for AES). If not present, the library creates a random IV value.
    
    # Returns:    
    # a CBC cipher object

    encryptor = AES.new(key, AES.MODE_CBC, IV)

    #https://docs.python.org/2/tutorial/inputoutput.html
    #open() returns a file object, and is most commonly used with two arguments: open(filename, mode).

    # The first argument is a string containing the filename. 
    # The second argument is another string containing a few characters describing the way in which the file will be used. 
    # mode can be 'r' when the file will only be read, 'w' for only writing (an existing file with the same name will be erased), 
    # and 'a' opens the file for appending; any data written to the file is automatically added to the end. 
    # 'r+' opens the file for both reading and writing. The mode argument is optional; 'r' will be assumed if it’s omitted.

    # On Windows, 'b' appended to the mode opens the file in binary mode, so there are also modes like 'rb', 'wb', and 'r+b'. 
    # Python on Windows makes a distinction between text and binary files; 
    # the end-of-line characters in text files are automatically altered slightly when data is read or written. 
    # This behind-the-scenes modification to file data is fine for ASCII text files, 
    # but it’ll corrupt binary data like that in JPEG or EXE files. 
    # Be very careful to use binary mode when reading and writing such files. 
    # On Unix, it doesn’t hurt to append a 'b' to the mode, so you can use it platform-independently for all binary files.

    # class controlled_execution:
    #     def __enter__(self):
    #         set things up
    #         return thing
    #     def __exit__(self, type, value, traceback):
    #         tear things down

    # with controlled_execution() as thing:
    #      some code

    # Now, when the “with” statement is executed, Python evaluates the expression, 
    # calls the __enter__ method on the resulting value (which is called a “context guard”), 
    # and assigns whatever __enter__ returns to the variable given by as. 
    # Python will then execute the code body, and no matter what happens in that code, call the guard object’s __exit__ method.


    with open(filename, 'rb') as infile:
        with open(outputFile, 'wb') as outfile:
            #<16 character filesize><16 character initialization vector><the rest is cipher text> 
            outfile.write(filesize.encode('utf-8'))
            outfile.write(IV)

            while True:
                chunk = infile.read(chunksize)

                if len(chunk) == 0:
                    break
                elif len(chunk) % 16 != 0:
                    chunk += b' ' * (16 - (len(chunk) % 16))

                outfile.write(encryptor.encrypt(chunk))

#zasto bona
#The getKey() function from the script returns the password hashed in SHA256.
def getKey(password):
            hasher = SHA256.new(password.encode('utf-8'))
            return hasher.digest()


def decrypt (key, filename):
    #cita citav fajl, ne moramo da ga chunk-ujemo jer je manji od 64 KB-a
    file = open(filename).read()
    fileSize = file[:16]                #<- prvih 16 bajtova je velicina fajla, onako kako je kreiran fajl
    IV = file[16:32]                    #<- sledecih 16 bajtova je inicijalizaciono vektor
    encrypted_text = file[32:]          #<- ostatak je enkriptovani tekst
    decryptor = AES.new(key, AES.MODE_CBC, IV)
    print decryptor.decrypt(encrypted_text)


#ValueError: AES key must be either 16, 24, or 32 bytes long, ako ne hashujemo key

decrypt(getKey("sahay"), "enim_msg.txt")
