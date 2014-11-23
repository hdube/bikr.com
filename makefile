coptions = -Wall -g -ggdb

login.cgi : login.c
	gcc ${coptions} login.c -o login.cgi
