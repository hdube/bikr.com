#!/usr/bin/python

# Import modules for CGI handling
import cgi, cgitb

# Create instance of FieldStorage
form = cgi.FieldStorage()

# Get data from fields
bike1_buy = form.getvalue('bike_1')
bike2_buy = form.getvalue('bike_2')
bike3_buy = form.getvalue('bike_3')

bike1_quantity = form.getvalue('quantity_1')
bike2_quantity = form.getvalue('quantity_2')
bike3_quantity = form.getvalue('quantity_3')

