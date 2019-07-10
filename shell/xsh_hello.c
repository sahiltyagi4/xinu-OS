# include <xinu.h>

shellcmd xsh_hello(int argc, char** argv)
{
	printf("Hello %s, Welcome to the world of Xinu!!\n", argv[1]);

	return 0;
}
