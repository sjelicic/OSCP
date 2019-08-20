#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int debugmode; //variable
int handle(int sock); //function, takes an integer sock (socket), returns integer 
int auth(char *username, char *password); //function, takes a pointer to username and password, returns integer

int auth(char *username, char *password) {
    char userpass[16]; //declaring a char array the size of 16 bytes
    char *response; //declaring a char pointer (to what it is pointing we do not know at this point)
    if (debugmode == 1) { //ako je debugmode (prethodno definisna avarijabla) jednako 1 (gde to definisemo)
        /*
        We use printf() function with %d format specifier to display the value of an integer variable.
        Similarly %c is used to display character, %f for float variable, %s for string variable, %lf for double and %x for hexadecimal variable.
        */
        printf("Debug: userpass buffer @ %p\n", userpass); //%p for pointers
        /*        
        fflush() is typically used for output stream only. Its purpose is to clear (or flush) the output buffer and move the buffered data to console 
        (in case of stdout) or disk (in case of file output stream).
        */
        // https://stackoverflow.com/questions/22901901/what-does-fflushstdin-do-in-c-programing
        fflush(stdout);
    }
    /*    
    The strcmp() compares two strings character by character. If the first character of two strings are equal, next character of two strings are compared. This continues until the corresponding characters of two strings are different or a null character '\0' is reached.

    Return Value            Remarks
        0                   if both strings are identical (equal)
    negative                if the ASCII value of first unmatched character is less than second.
    positive integer        if the ASCII value of first unmatched character is greater than second.
    */

    //ako username nije admin vraca 0
    if (strcmp(username, "admin") != 0) return 0; //sta zapravo vrednost 0 znaci
    /*
    Syntax:
    char* strcpy(char* destination, const char* source);

    Paramters: This method accepts following paramters:
    destination: Pointer to the destination array where the content is to be copied.
    source: string which will be copied.

    Return Value: After copying the source string to the destination string, the strcpy() function returns a pointer to the destination string.
    */
    //kopira vrednost password promenljive u userpass promenljivu
    //strcpy kopira password[256] u userpass[16] sto znaci da postoji mogucnost buffer overflow-a
    strcpy(userpass, password);
    // ako je userpass jednak 1974jailbreak! vraca 1
    if (strcmp(userpass, "1974jailbreak!") == 0) {
        return 1;
    } else {
        // ako userpass nije jednak 1974jailbreak!, stampa poruku, vraca 0
        printf("Incorrect username and/or password.\n");
        return 0;
    }
    return 0;
}

int handle(int sock) {
    int n;
    int gotuser = 0;
    int gotpass = 0;
    char buffer[1024];
    char strchr[2] = "\n\x00"; //\new line \hexadecimal null (\x00), cemu ovo sluzi
    char *token;
    char username[256]; //char array, size 256
    char password[256]; //char array, 256 size
    debugmode = 0; //vrednost postavljena na nulu
    /*
    memset() is used to fill a block of memory with a particular value.
    The syntax of memset() function is as follows :
    
    void *memset(void *ptr, int x, size_t n);

    ptr ==> Starting address of memory to be filled
    x   ==> Value to be filled
    n   ==> Number of bytes to be filled starting from ptr to be filled
    
    void *ptr
    A void pointer is a pointer that has no associated data type with it. A void pointer can hold address of any type and can be typcasted to any type.
    */
    // upisuje 256 nula karaktera u memoriju pocevsi od memorijske adrese buffer promenljive
    memset(buffer, 0, 256);
    /*    
    Under normal circumstances every UNIX program has three streams opened for it when it starts up, one for input, one for output, and one for printing diagnostic or error messages.
    The input stream is referred to as "standard input"; the output stream is referred to as "standard output"; and the error stream is referred to as "standard error". These terms are 
    abbreviated to form the symbols used to refer to these files, namely stdin, stdout, and stderr.

    Each of these symbols is a stdio(3) macro of type pointer to FILE, and can be used with functions like fprintf(3) or fread(3).

    Since FILEs are a buffering wrapper around UNIX file descriptors, the same underlying files may also be accessed using the raw UNIX file interface, that is, the functions like read(2)
    and lseek(2).

    On program startup, the integer file descriptors associated with the streams stdin, stdout, and stderr are 0, 1, and 2, respectively. The preprocessor symbols STDIN_FILENO, STDOUT_FILENO,
    and STDERR_FILENO are defined with these values in <unistd.h>.
    */
    /*
    The dup() system call creates a copy of a file descriptor.

    It uses the lowest-numbered unused descriptor for the new descriptor.
    If the copy is successfully created, then the original and copy file descriptors may be used interchangeably.
    They both refer to the same open file description and thus share file offset and file status flags.
    */
    dup2(sock, STDOUT_FILENO); //obe ove komande bi trebalo da redirektuju STDOUT and STDERR to a socket <- ostaje pitanje zasto
    dup2(sock, STDERR_FILENO); //
    printf("OK Ready. Send USER command.\n");
    fflush(stdout);
    // while(1) se uvek izvrsava
    while(1) {
        /*
        read: From the file indicated by the file descriptor fd, the read() function reads cnt bytes of input into the memory area indicated by buf. 
        A successful read() updates the access time for the file.
        
        Syntax in C language 
        size_t read (int fd, void* buf, size_t cnt); 

        Parameters
        fd: file descripter
        buf: buffer to read data from
        cnt: length of buffer

        Returns: How many bytes were actually read
        return Number of bytes read on success
        return 0 on reaching end of file
        return -1 on error
        return -1 on signal interrupt
        
        Important points
        buf needs to point to a valid memory location with length not smaller than the specified size because of overflow.
        fd should be a valid file descriptor returned from open() to perform read operation because if fd is NULL then read should generate error.
        cnt is the requested number of bytes read, while the return value is the actual number of bytes read. Also, some times read system call should read less bytes than cnt.
        */
        //cita 1024 bajta iz sock promenljive i unosi ih u memoriju pocevsi od buffer adrese
        n = read(sock, buffer, 1024);
        // ako nista nije ucitano (dobijamo -1 na errror ili signal interrupt) stampa
        if (n < 0) {
            // https://jameshfisher.com/2016/12/24/perror/
            // A call to perror("foo") will print "foo: " to stderr, then will print a human-readable description of the err in errno (the global error number written to by syscalls and 
            //library functions).
            perror("ERROR reading from socket");
            return 0;
        }
        /*
        C provides two functions strtok() and strtok_r() for splitting a string by some delimiter. Splitting a string is a very common task. For example, we have a comma separated list of items from a file and we want individual items in an array.

        strtok()
        char * strtok(char str[], const char *delims);

        Splits str[] according to given delimiters.
        and returns next token. It needs to be called
        in a loop to get all tokens. It returns NULL
        when there are no more tokens.
        */
        //splits the buffer string according to the delimiters in strchr promenljivoj (char strchr[2] = "\n\x00";   <- ovo je newline NULL)
        token = strtok(buffer, strchr);
        // Parca buffer sve dok ne dodje do kraja stringa (returns NULL when there are no more tokens in the string)
        // ovo je zapravo izvlacenje username iz buffer-a, zato sto ide dok ne dodje do \x00 ili NULL karaktera
        while (token != NULL) {
            //ako je gotuser i gotpass jednako jedan break iz loop-a (gde su te vrednosti postavljene), postavljene dole prilikom unosa username-a i password-a
            if (gotuser == 1 && gotpass == 1) {
                /*
                Break Statement is a loop control statement which is used to terminate the loop. 
                As soon as the break statement is encountered from within a loop, 
                he loop iterations stops there and control returns from the loop immediately to the first statement after the loop.
                */
                break;
            }
            /*
            std::strncmp() function lexicographically compares not more than count characters from the two null-terminated strings and returns an integer based on the outcome.

            This function takes two strings and a number num as arguments and compare at most first num bytes of both the strings.
            num should be at most equal to the length of the longest string. If num is defined greater than the string length than comparison is done till the null-character(‘\0’) of either string.
            This function compares the two strings lexicographically. It starts comparison from the first character of each string. If they are equal to each other, it continues and compare the next character of each string and so on.
            This process of comparison stops until a terminating null-character of either string is reached or num characters of both the strings matches.

            Syntax :
            int strncmp(const char *str1, const char *str2, size_t count);

            Parameters:
            str1 and str2: C string to be compared.
            count: Maximum number of characters to compare.
            size_t is an unsigned integral type.

            Return Value: 
            Value                               Meaning
            Less than zero                      str1 is less than str2.
            Zero                                str1 is equal to str2.
            Greater than zero                   str1 is greater than str2.
            */
            // ako je prvih pet karaktera u token promenljivoj USER
            if (strncmp(token, "USER ", 5) == 0) {
                /*
                 It is a compile time unary operator which can be used to compute the size of its operand. The result of sizeof is of unsigned integral type which is usually denoted 
                 by size_t. sizeof can be applied to any data-type, including primitive types such as integer and floating-point types, pointer types, or compound datatypes 
                 such as Structure, union etc.
                 */
                //kopira sizeof(username) broj karaktera u token+5 (sta ovo plus 5 znaci) u username promenljivu
                strncpy(username, token+5, sizeof(username));
                gotuser=1; //postavlja gotuser na 1
                //ako je gotpass jednak 0 stampa poruku
                if (gotpass == 0) {
                    printf("OK Send PASS command.\n");
                    fflush(stdout);
                }
                //ako je prvih 5 karaktera u token promenljivoj jednako pass
            } else if (strncmp(token, "PASS ", 5) == 0) {
                //kopira sve posle 5 karaktera u tokenu u passwrod promenljivu, narednih sizeof(password) broja karaktera
                strncpy(password, token+5, sizeof(password));
                gotpass=1; //postavlja gotpass na 1
                if (gotuser == 0) {
                    printf("OK Send USER command.\n");
                    fflush(stdout);
                }
                //ako je pvih 5 karaktera token promenljive debug, postavlja vrednost promenljive debug na 1 (ako je prvobitna vrednost 0) ili obrnuto
            } else if (strncmp(token, "DEBUG", 5) == 0) {
                if (debugmode == 0) {
                    debugmode = 1;
                    printf("OK DEBUG mode on.\n");
                    fflush(stdout);
                } else if (debugmode == 1) {
                    debugmode = 0;
                    printf("OK DEBUG mode off.\n");
                    fflush(stdout);
                }
            }
            // zasto bi NULL splitovao sa strchr (koji je takodje NULL)
            token = strtok(NULL, strchr);
        }
        //kada imamo i username i password (gotuser i gotpass promenljive postavljene na 1) break
        if (gotuser == 1 && gotpass == 1) {
            break;
        }
    }
    //ova if petlja ce raditi samo u slucaju da auth funkcija vraca non-zero vrednost
    //if (strcmp(userpass, "1974jailbreak!") == 0) {                    <- vraca 1 samo u ovom slucaju
    //    return 1;
    //username mora biti admin, password mora biti 1974jailbreak!
    if (auth(username, password)) {
        printf("OK Authentication success. Send command.\n");
        fflush(stdout);
        n = read(sock, buffer, 1024);
        //ako nista nije ucitano sa socket-a
        if (n < 0) {
            perror("Socket read error");
            return 0;
        }
        //ako je data komanda OPEN
        if (strncmp(buffer, "OPEN", 4) == 0) {
            printf("OK Jail doors opened.");
            fflush(stdout);
            //ako je data komanda CLOSE
        } else if (strncmp(buffer, "CLOSE", 5) == 0) {
            printf("OK Jail doors closed.");
            fflush(stdout);
        } else {
            // bilo sta drugo uneto
            printf("ERR Invalid command.\n");
            fflush(stdout);
            return 1;
        }
        // ako username i password nisu tacni
    } else {
        printf("ERR Authentication failed.\n");
        fflush(stdout);
        return 0;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int sockfd;
    int newsockfd;
    int port;
    int clientlen;
    char buffer[256];
    // A structure is a user defined data type in C/C++. A structure creates a data type that can be used to group items of possibly different types into a single type.
    // Structures for handling internet addresses
    // https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int n;
    int pid;
    int sockyes;
    sockyes = 1;
    /*  
    https://www.geeksforgeeks.org/socket-programming-cc/
    Socket programming is a way of connecting two nodes on a network to communicate with each other. 
    One socket(node) listens on a particular port at an IP, while other socket reaches out to the other to form a connection. 
    Server forms the listener socket while client reaches out to the server.
    */
    /*
    Socket creation:
    int sockfd = socket(domain, type, protocol)
    
    sockfd: socket descriptor, an integer (like a file-handle)
    domain: integer, communication domain e.g., AF_INET (IPv4 protocol) , AF_INET6 (IPv6 protocol)
    type: communication type
    SOCK_STREAM: TCP(reliable, connection oriented)
    SOCK_DGRAM: UDP(unreliable, connectionless)
    protocol: Protocol value for Internet Protocol(IP), which is 0. This is the same number which appears on protocol field in the IP header of a packet.(man protocols for more details)
    */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //ako nije mogao da kreira socket
    if (sockfd < 0) {
        perror("Socket error");
        exit(1);
    }
    /*
    This helps in manipulating options for the socket referred by the file descriptor sockfd. This is completely optional, but it helps in reuse of address and port. Prevents error such as: “address already in use”.
    
    Setsockopt:
    int setsockopt(int sockfd, int level, int optname,  
                   const void *optval, socklen_t optlen);
    */
    // https://linux.die.net/man/3/setsockopt
    // To set options at the socket level, specify the level argument as SOL_SOCKET
    // SO_REUSEADDR
    // Specifies that the rules used in validating addresses supplied to bind() should allow reuse of local addresses, if this is supported by the protocol. 
    // This option takes an int value. This is a Boolean option.

    // https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/setopt.htm
    // int setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_length);
    /*           
    The option_value and option_length parameters are used to pass data used by the particular set command. 
    The option_value parameter points to a buffer containing the data needed by the set command. 
    The option_value parameter is optional and can be set to the NULL pointer, if data is not needed by the command. 
    The option_length parameter must be set to the size of the data pointed to by option_value.
    */
    //&a; returns the actual address of the variable.
    // &sockeyes he option_value, sizeof(int)) == -1 je option_length (valjda beskonacno)
    // setsockopt vraca 0 ako je sve u redu, -1 ako nije
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &sockyes, sizeof(int)) == -1) {
        perror("Setsockopt error");
        exit(1);
    }
    // char pointer to the address of the server_addr, this being the starting address of memory to be filled, filled with zeroes, for the sizeof(server_addr) number of characters
    memset((char*)&server_addr, 0, sizeof(server_addr));
    port = 7411; // port na kome slusamo, vrlo vazno

    /*
    struct sockaddr_in {
    short            sin_family;   //address family, set to AF_INET
    unsigned short   sin_port;     //the port in network byte order
    struct in_addr   sin_addr;     //the inet address
    };
    */
    //server_addr je sockaddr_in (sock adress input)
    server_addr.sin_family = AF_INET;
    //In this case, only one IP socket may be bound to any given local (address, port) pair. 
    //When INADDR_ANY is specified in the bind call, the socket will be bound to all local interfaces.
    server_addr.sin_addr.s_addr = INADDR_ANY;
    /*
    #include <arpa/inet.h>
    uint32_t htonl(uint32_t hostlong);   // "Host TO Network Long"
    uint16_t htons(uint16_t hostshort);  // "Host TO Network Short"
    These functions “convert values between host and network byte order”, where “Network byte order is big endian, or most significant byte first.”
    There are equivalent inverse functions ntohl and ntohs.
    */
    // konvertovao port u odgovarajuci format
    server_addr.sin_port = htons(port);
    /*
    int bind(int socket, struct sockaddr *address, int address_len);

    General description
    The bind() function binds a unique local name to the socket with descriptor socket. After calling socket(), a descriptor does not have a name associated with it. 
    However, it does belong to a particular address family as specified when socket() is called. The exact format of a name depends on the address family.
    
    Parameter
    Description
    socket
    The socket descriptor returned by a previous socket() call.
    address
    The pointer to a sockaddr structure containing the name that is to be bound to socket.
    address_len
    The size of address in bytes.
    The socket parameter is a socket descriptor of any type created by calling socket().

    The address parameter is a pointer to a buffer containing the name to be bound to socket. The address_len parameter is the size, in bytes, of the buffer pointed to by address. 
    For AF_UNIX, this function creates a file that you later need to unlink besides closing the socket.
    */
    //bind vraca -1 ako nesto nije u redu
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind error");
        exit(1);
    }
    /*
    int listen(int sockfd, int backlog);
    It puts the server socket in a passive mode, where it waits for the client to approach the server to make a connection. 
    The backlog, defines the maximum length to which the queue of pending connections for sockfd may grow. 
    If a connection request arrives when the queue is full, the client may receive an error with an indication of ECONNREFUSED.
    */
    listen(sockfd, 200);
    clientlen = sizeof(client_addr);
    while (1) {
        // int new_socket= accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
        /*
        It extracts the first connection request on the queue of pending connections for the listening socket, sockfd, creates a new connected socket, 
        and returns a new file descriptor referring to that socket. 
        At this point, connection is established between client and server, and they are ready to transfer data.
        */
        newsockfd = accept(sockfd, (struct sockaddr*)&client_addr, &clientlen);
        /*
        On success, these system calls return a nonnegative integer that is a
        file descriptor for the accepted socket.  On error, -1 is returned,
        errno is set appropriately, and addrlen is left unchanged.
        */
        if (newsockfd < 0) {
            perror("Accept error");
            exit(1);
        }
        /*
        Fork system call use for creates a new process, which is called child process, which runs concurrently with process (which process called system call fork) and this process is called parent process. After a new child process created, both processes will execute the next instruction following the fork() system call. A child process uses the same pc(program counter), same CPU registers, same open files which use in the parent process.
        */
        pid = fork(); //zasto smo kreirali novi proces
        /*
        It takes no parameters and returns an integer value. Below are different values returned by fork().

        Negative Value: creation of a child process was unsuccessful.
        Zero: Returned to the newly created child process.
        Positive value: Returned to parent or caller. The value contains process ID of newly created child process.
        */
        if (pid < 0) {
            perror("Fork error");
            exit(1);
        }
        if (pid == 0) {
            close(sockfd); //zatvara socket
            // exit() terminates the calling process without executing the rest code which is after the exit() function.
            // ne znam zasto ovo
            exit(handle(newsockfd)); 
        } else {
            close(newsockfd); //zatvara novo otvoreni socket
        }
    }
}
