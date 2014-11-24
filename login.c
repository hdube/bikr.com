#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 64
#define NAME_SIZE 64
#define LINE_SIZE (2+NAME_SIZE+2*INPUT_SIZE)

typedef struct {
	char *realname;
	char *username;
	char *password;
} USER;

void  getInput(char *,int *, int);
USER *checkUser(char *,char *,char *);

int main(int argc, char *argv[])
{
	//////////////////
	// CGI
	//////////////////
	/*getting CGI data size*/
	int data_size = atoi(getenv("CONTENT_LENGTH"));

	/*parsing*/
	char *username = (char *)malloc(INPUT_SIZE+1),
	     *password = (char *)malloc(INPUT_SIZE+1);	//extra char for '\0'
	int count=0; 	//num of bytes parsed

	getInput(username, &count, data_size);
	getInput(password, &count, data_size);

	//////////////////
	// Checking
	//////////////////
	/*checking against members.csv*/
	FILE *file_ptr = fopen("members.csv","rt");
	char *line = (char *)malloc(LINE_SIZE+1);
	USER *user;

	if (file_ptr == NULL) {
		return EXIT_FAILURE;
	}

	for (fgets(line, LINE_SIZE, file_ptr); !feof(file_ptr);
				fgets(line, LINE_SIZE, file_ptr)) {
		if((user = checkUser(username, password, line)) != NULL)
			break;
	}
	fclose(file_ptr);

	//////////////////
	// Logging in
	//////////////////
	file_ptr = fopen("loggedIn.csv", "wt");
    fprintf(file_ptr,"%s\n",username);
	fclose(file_ptr);

	//////////////////
	// Display page
	//////////////////
	/*
	file_ptr = fopen(REDIRECT_PAGE, "rt");
	char *page_line  = (char *)malloc(256);
	*(page_line+255) = '\0';
	int counter;

	printf("Content-type: text/html\n\n");

	for (counter=0; counter<12; counter++)
		printf("%s",fgets(page_line,255,file_ptr));
	printf("<input type=\"hidden\" name=\"user\" value=\"%s\">\n",
			user->username);
	for (; counter<15; counter++)
		printf("%s",fgets(page_line,255,file_ptr));
	fclose(file_ptr);
	free(page_line);
	*/

	//////////////////
	// Testing
	//////////////////
	/*printing for testing purposes*/
	
	printf("Content-type: text/html\n\n");
	printf("<HTML>\n\n<HEAD>\n<TITLE>Logged in</TITLE>\n</HEAD>\n\n");

	printf("<BODY>\nI recieved string of size %d: %s AND %s.\n",
						data_size, username, password);
	if (user != NULL) {
		printf("<p>\nI made structure USER as:");
		printf("<br>realname: %s", user->realname);
		printf("<br>username: %s", user->username);
		printf("<br>password: %s</p>\n</BODY>\n", user->password);
		printf("</HTML>");
	}
	else printf("<br>Nothing got done...\n");
	printf("</HTML>");
		

	free(username);
	free(password);
	//printf("Location:http://cs.mcgill.ca/~hdube1/public.html");

	return EXIT_SUCCESS;
}


/*
 * getInput function:
 * This method retrieves information from the CGI input, up to max bytes
 * and puts it in the str string.
 * It keeps track of number of bytes traversed with count.
 */
void getInput(char *str, int *count, int max)
{
	int c, index=0; 	//c is a char
	char *escChar = (char *)malloc(3);
	escChar[2]='\0';

	//go to next variable
	for (;(c=getchar())!='='; (*count)++);
	//get variable
	while ((c=getchar())!='&' && c!= EOF && *count<=max) {
		if (c=='%') {
			//esc chars are in hex (00-7F)
			escChar[0]=getchar();
			escChar[1]=getchar();
			str[index]=(char)strtol(escChar,NULL,16);
		}
		else if (c=='+') str[index]=' ';
		else str[index]=c;
		(*count)++;
		index++;
	}
	//add end-of-string char and free escChar
	str[index+1]='\0';
	free(escChar);
}


/*
 * checkUser function:
 * This method returns NULL if the username/password doesn't match
 * with the line string provided (from the members.csv).
 * It returns a pointer to a USER struct containing the user info otherwise.
 */
USER *checkUser(char *username, char *password, char *line)
{
	//int name_length, user_length, pass_length, index;
	int index;
	char *file_name = line, *file_user, *file_pass;

	for (index=0; *(file_name+index)!=','; index++);
	*(file_name+index)='\0';
	file_user = file_name+index+1;
	for (index=0; *(file_user+index)!=','; index++);
	*(file_user+index)='\0';
	file_pass = file_user+index+1;
	for (index=0; *(file_pass+index)!='\n'
			&&*(file_pass+index)!=EOF; index++);
	*(file_pass+index)='\0';

	if (strcmp(username,file_user)!=0 || strcmp(password,file_pass)!=0)
		return NULL;

	//creating USER
	USER *retUser = (USER *)malloc(sizeof(USER));
	retUser->realname = file_name;
	retUser->username = file_user;
	retUser->password = file_pass;

	return retUser;
}
