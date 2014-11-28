coptions = -Wall -g -ggdb

login.cgi : login.c
	gcc ${coptions} login.c -o login.cgi

perm :
	chmod 700 cgi-bin/*
	chmod 644 *.html
	chmod 711 Images
	chmod 644 Images/* *.css
	
