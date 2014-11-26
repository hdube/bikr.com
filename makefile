coptions = -Wall -g -ggdb

login.cgi : login.c
	gcc ${coptions} login.c -o login.cgi

perm : Images *.html *.cgi *.py *.pl
	chmod 700 *.cgi *.py *.pl
	chmod 644 *.html
	chmod 711 Images
	chmod 644 Images/*
