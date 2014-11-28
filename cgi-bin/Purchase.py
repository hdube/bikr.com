#!/usr/bin/env python

# Import modules for CGI handling
import cgi,cgitb
import csv

# Create instance of FieldStorage
form = cgi.FieldStorage()

#Get values in form
bike1_buy = form.getvalue('bike_1')
bike2_buy = form.getvalue('bike_2')
bike3_buy = form.getvalue('bike_3')

bike1_quantity = form.getvalue('quantity_1')
bike2_quantity = form.getvalue('quantity_2')
bike3_quantity = form.getvalue('quantity_3')

user = form.getvalue('user')

#Give value in int or 0 to variables (got as string)
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
########################################
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
########################################

#Calculate total. If bike1 was unchecked, will have value of 0, even if quantity specified
total = bike1 * quantity1 + bike2 * quantity2 + bike3 * quantity3

#Check inside loggedIn.csv if 'user' (from hidden field) is in it
logged = 0

with open('loggedIn.csv','rt') as f:
	loggedList = csv.reader(f,delimiter=',')
	for row in loggedList:
		for field in row:
			if field == user:
				logged = 1

#Check inventory, subtract amount if available, if not, display error

with open('Inventory.csv','rt') as f:
	inventory = list(csv.reader(f,delimiter=','))

insufficient1 = 0
insufficient2 = 0
insufficient3 = 0

for line in inventory[0:3]:
	if line[0] == 'Bike1':
		if int(line[1]) >= quantity1:
			line[1] = int(line[1]) - quantity1
			continue
		else:
			insufficient1 = 1
	if line[0] == 'Bike2':
		if int(line[1]) >= quantity2:
			line[1] = int(line[1]) - quantity2
			continue
		else:
			insufficient2 = 1
	if line[0] == 'Bike3':
		if int(line[1]) >= quantity3:
			line[1] = int(line[1]) - quantity3
			continue
		else:
			insufficient3 = 1

#Display page depending on conditions (logged, inventory sufficient)

if logged == 1:
	if insufficient1 == 0 and insufficient2 == 0 and insufficient3 ==0:
				
		with open('Inventory.csv','wb') as f:
			writer = csv.writer(f)
			for rows in inventory:
				writer.writerow(rows)	

		print "Content-type:text/html\n\n"
		print "<html>"
		print "<head>"
		print "</head>"
		print "<body>"
		print "<h1>Bill </h1>"
		if bike1 != 0 and quantity1 != 0:
			print "<h2>You have bought %s model 1, $1 each </h2>" % str (quantity1)
		if bike2 != 0 and quantity2 != 0:
			print "<h2>You have bought %s model 2, $5 each </h2>" % str (quantity2)
		if bike3 != 0 and quantity3 != 0:
			print "<h2>You have bought %s model 3, $12 each </h2>" % str (quantity3)
		print "<h2>Your total is $%s </h1>" % str (total)
		print "<br>"
		print '<h1><a href="Catalogue.html">Click here to go back to the catalogue</a></h1>'
		print '<h1><a href="public.html">Click here to go back to the home page</a></h1>'
		print "</body>"
		print "</html>"
	else:
		print "Content-type:text/html\n\n"
		print "<html>"
		print "<head>"
		print "</head>"
		print "<body>"
		if insufficient1 == 1:
			print "<p>There are not sufficient model 1 left. Please change your order</p>"
		if insufficient2 == 1:
			print "<p>There are not sufficient model 2 left. Please change your order</p>"
		if insufficient3 == 1:
			print "<p>There are not sufficient model 3 left. Please change your order</p>"
		print "</body>"
		print "</html>" 
else:
	print "Content-type:text/html\n\n"
	print "<html>"
	print "<head>"
	print "</head>"
	print "<body>"
	print "<h1>You are not logged in.<h1>"
	print '<h2><a href="Catalogue.html">Click here to go back to catalogue</a></h2>'
	print "</body>"	
	print "</html>"
