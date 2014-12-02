coptions = -Wall -g -ggdb

login.cgi : login.c
	gcc ${coptions} cgi-bin/login.c -o cgi-bin/login.cgi

perm :
	chmod 700 cgi-bin/*
	chmod 644 *.html
	chmod 711 Images cgi-bin
	chmod 644 Images/* *.css
	
