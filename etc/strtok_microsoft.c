#include <stdio.h> 

char * mystrtok(char * string, const char * control) {
	unsigned char *str;
	const unsigned char *ctrl = control; 
	unsigned char map[256];
	static char *nextoken;
 
	for (int count = 0; count < 256; count++) 
		map[count] = 0;
 
	do { 
		map[*ctrl] = 1;
	} while (*ctrl++);
 
	if (string)
		str = string;
	else
		str = nextoken;
 
	//skip leader control char...
	while(map[*str]==1 && *str)
		str++;
 
	string = str;
 
	/* Find the end of the token. If it is not the end of the string,
	 * put a null there. */
	for (; *str; str++)
		if(map[*str]==1) {
			*str++ = '\0';
			break;
		}
 
	nextoken = str;
 
	/* Determine if a token has been found. */
	if (string == str)
		return NULL;
	else
		return string;
}

int main()
{
    char fg[] = "111-222-333";
    char del[] = "-";
    char *pf;
    printf("origin string: %s\n", fg);
    pf = mystrtok(fg, del);
    while (pf)
    {
		printf("%s\n", pf);
        pf = mystrtok(NULL, del);
    }
    //printf("%s\n",fg);
    return 0;
}


