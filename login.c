#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int data_size = atoi(getenv("CONTENT_LENGTH"));
	char *data = (char *)malloc(data_size+1);

	fgets(data, data_size+1, stdin);
	*(data+data_size+1) = '\0'; 	//end of string

	printf("Content-type: text/html\n\n");
	printf("<HTML>\n\n<HEAD>\n<TITLE>Logged in</TITLE>\n</HEAD>\n\n");

	printf("<BODY>\nI recieved string of size %d: %s.\n</BODY>\n\n", data_size, data);
	printf("</HTML>");

	free(data);

	return 0;
}
