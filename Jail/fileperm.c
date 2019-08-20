int main(void)
{
	// setuid() sets the effective user ID of the calling process.
	setuid(1000);
	// setgid() sets the effective group ID of the calling process.
	setgid(1000);
	/*	
	system() is used to invoke an operating system command from a C/C++ program.

    int system(const char *command);
    */
    // kada vac kaze da koristimo pune putanje, da neko ne odradi path hijack
	system("/usr/bin/id");
}