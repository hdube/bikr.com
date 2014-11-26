#!/usr/bin/env python

# Import modules for CGI handling
import cgi,cgitb

# Create instance of FieldStorage
form = cgi.FieldStorage()

bike1_buy = form.getvalue('bike_1')
bike2_buy = form.getvalue('bike_2')
bike3_buy = form.getvalue('bike_3')

bike1_quantity = form.getvalue('quantity_1')
bike2_quantity = form.getvalue('quantity_2')
bike3_quantity = form.getvalue('quantity_3')

if bike1_buy:
	bike1 = int (bike1_buy)
else:
	bike1 = 0

if bike2_buy:
	bike2 = int (bike2_buy)
else:
	bike2 = 0

if bike3_buy:
	bike3 = int (bike3_buy)
else:
	bike3 = 0

if bike1_quantity:
	quantity1 = int (bike1_quantity)
else:
	quantity1 = 0

if bike2_quantity:
	quantity2 = int (bike2_quantity)
else:
	quantity2 = 0

if bike3_quantity:
	quantity3 = int (bike3_quantity)
else:
	quantity3 = 0

total = bike1 * quantity1 + bike2 * quantity2 + bike3 * quantity3


print "Content-type:text/html\n\n"
print "<html>"
print "<head>"
print "</head>"
print "<body>"
print "<h1>Bill </h1>"
if bike1 != 0 and quantity != 0:
	print "<h2>You have bought %s model 1, $1 each </h2>" % str (bike1)
if bike2 != 0 and quantity != 0:
	print "<h2>You have bought %s model 2, $5 each </h2>" % str (bike2)
if bike3 != 0 and quantity != 0:
	print "<h2>You have bought %s model 3, $12 each </h2>" % str (bike3)
print "<h2>Your total is $%s </h1>" % str (total)
print "</body>"
print "</html>"



