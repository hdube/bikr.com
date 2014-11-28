#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 64
#define NAME_SIZE 64
#define LINE_SIZE (2+NAME_SIZE+2*INPUT_SIZE)
#define LINE_NUMBER 36

void  getInput(char *,int *, int);
int searchUser(char *,char *,char *);
void printError(char *);

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
    int check;

	if (file_ptr == NULL) {
		return EXIT_FAILURE;
	}
    
    else {
        fgets(line, LINE_SIZE, file_ptr);
	    for (fgets(line, LINE_SIZE, file_ptr); !feof(file_ptr);
	    			fgets(line, LINE_SIZE, file_ptr)) {
            if ((check = searchUser(username,password,line)) >= 0)
                break;
        }
	}
	fclose(file_ptr);

    //error pages
    if (check == -1) printError("The username does not exist. Please try again.");
    if (check == 0 ) printError("The password entered did not match the username. Please try again.");
    if (check < 1  ) return EXIT_FAILURE;

    free(password);

	//////////////////
	// Logging in
	//////////////////
	file_ptr = fopen("loggedIn.csv", "r+wt");
    int logged_in = 0;  //assume false

    if (file_ptr == NULL) {
        return EXIT_FAILURE;
    }

    else {
        int user_length = 0;
        for (;*(username+user_length)!='\0';user_length++);
        for (fgets(line, LINE_SIZE, file_ptr); !feof(file_ptr);
                    fgets(line, LINE_SIZE, file_ptr)) {
            if (strncmp(username,line,user_length)==0) {
                logged_in = 1;
                break;
            }
        }
        if (logged_in == 0) {
            fprintf(file_ptr,"%s\n",username);
        }
    }
	fclose(file_ptr);

	//////////////////
	// Display page
	//////////////////
	file_ptr = fopen("Catalogue.html", "rt");
	char *page_line  = (char *)malloc(256);
	*(page_line+255) = '\0';
	int counter;

	printf("Content-type: text/html\n\n");

    //copy beginning of page
	for (counter=0; counter<LINE_NUMBER-1; counter++)
		printf("%s",fgets(page_line,255,file_ptr));
    //we replace the hidden field with a new one with non-empty value
	printf("\t\t<input type=\"hidden\" name=\"user\" value=\"%s\">\n", username);
    //ignore the hidden field previously there
    fgets(page_line,255,file_ptr);
    //copy rest of page
    while (!feof(file_ptr)) {
		printf("%s",fgets(page_line,255,file_ptr));
    }
	fclose(file_ptr);
	free(page_line);

	//////////////////
	// Testing
	//////////////////
	/*printing for testing purposes*/
	/*
	printf("Content-type: text/html\n\n");
	printf("<HTML>\n\n<HEAD>\n<TITLE>Logged in</TITLE>\n</HEAD>\n\n");

	printf("<BODY>\nI recieved string of size %d: %s AND <b>PASSWORD FORGOTTEN</b>.\n",
						data_size, username);
    printf("The search returned %d.\n", check);
	printf("</BODY>\n</HTML>");*/
		
	free(username);

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
 * searchUser function:
 * This method returns 1 if the username and password matched the line.
 */
int searchUser(char *username, char *password, char *line)
{
    char *token;

    token = strtok(line,",");
    token = strtok(NULL,",");
    if (strcmp(token,username)!=0) return -1;   //User was not found
    token = strtok(NULL,"\n");
    char EOF_delim[2] = {EOF,'\0'};
    token = strtok(token,EOF_delim);
    if (strcmp(token,password)!=0) return 0;   //User was found but did not match
    else return 1;  //User was found and matched
}


/*
 *
 */
void wrongUsername()
{
	printf("Content-type: text/html\n\n");
	printf("<HTML>\n\n<HEAD>\n<TITLE>Logging in error</TITLE>\n</HEAD>\n\n");

	printf("<BODY>\nThe username recieved could not be traced back in our databases: please try again.\n");
    printf("\n");
	printf("</BODY>\n</HTML>");
}


/*
 *
 */
void wrongPassword()
{
	printf("Content-type: text/html\n\n");
	printf("<HTML>\n\n<HEAD>\n<TITLE>Logging in error</TITLE>\n</HEAD>\n\n");

	printf("<BODY>\nThe password and username did not match our databases: please try again.\n");
    printf("\n");
	printf("</BODY>\n</HTML>");
}


/*
 *
 */
void printError(char *error_message)
{
    printf("Content-type: text/html\n\n");
    printf("<html>\n\n");
    printf("<head>\n");
    printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"mystyle.css\"\n");
    printf("</head>\n\n<body>\n\n");
    printf("<header>\n");
    printf("<img style=\"float:center;width:230px;height:160px\" src=\"Images/logo-2.jpg\">\n");
    printf("</header>\n\n");
    
    printf("<nav>\n<table>\n\t<tr>\n\t\t<td> </td>\n");
    printf("\t\t<td><a href=\"public.html\">Home</a></td>\n");
    printf("\t\t<td><a href=\"login.html\"><b>Login</b></a></td>\n");
    printf("\t</tr>\n</table>\n</nav>\n<br>\n\n");

    printf("<section>\n%s\n</section>\n\n>",error_message);

    printf("<footer>\nCopyright *** bikr.com\n</footer>\n\n");
    printf("</body>\n</html>");
}
