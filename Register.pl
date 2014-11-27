#!/usr/bin/perl
use strict;
use CGI ':standard';


#my $fullname = "Jessica Dorval";
#my $username = "jess.dorval";
#my $password1 = "test";
#my $password2 = "test";
my $newUser = 1;

my $fullname = param('fullname');
my $username = param('username');
my $password1 = param('password1');
my $password2 = param('password2');

print"Content-Type:text/html\n\n";
print"<html>";

	#check if the two passwords entered are the same. If they are not print error
	if($password1 ne $password2){
				 print qq(<head>);
	                        print qq(<link rel="stylesheet" type="text/css" href="mystyle.css">);
	                        print qq(</head>);

	                        print qq(<body>);

	                        print qq(<header>);
	                        print qq(<img style="float:center;width:230px;height:160px" src="Images/logo-2.jpg">);
	                        print qq(<h1 style="float:right;color:white;padding:5px">Call Us: 1-888-245-0000</h1>);
	                        print qq(</header>);

	                        print qq(<!--make sure to change the size of the header of the current page-->);
	                        print qq(<nav>);
	                        print qq(<table>);
	                            print qq(<tr>);
	                                print qq(<td> </td>);
	                                print qq(<td><a href="public.html">Home</a></td>);
									print qq(<td><a href="Catalogue.html">Catalogue</a></td>);
	                                print qq(<td><a href="login.html">Login</a></td>);
	                                print qq(<td><a href="Registration.html"><b>Registration</a></td>);
				   				print qq(</tr>);
	                        print qq(</table>);
	                        print qq(</nav>);
	                        print qq(<br>);

	                        print qq(<section>);
	                        print qq(The two passwords did not match! Please use the navigation bar to return);
	                        print qq(</section>);

	                        print qq(<footer>);
	                        print qq(Copyright *** bikr.com);
	                        print qq(</footer>);

	                        print qq(</body>);
	                        print qq(</html>);

	}
	#check if the user entered a comma in the fields
	elsif((index($fullname, ",") != -1) || (index($username, ",")!= -1) || (index($password1, ",")!= -1)) {
 							print qq(<head>);
	                        print qq(<link rel="stylesheet" type="text/css" href="mystyle.css">);
	                        print qq(</head>);

	                        print qq(<body>);

	                        print qq(<header>);
	                        print qq(<img style="float:center;width:230px;height:160px" src="Images/logo-2.jpg">);
	                        print qq(<h1 style="float:right;color:white;padding:5px">Call Us: 1-888-245-0000</h1>);
	                        print qq(</header>);

	                        print qq(<!--make sure to change the size of the header of the current page-->);
	                        print qq(<nav>);
	                        print qq(<table>);
	                            print qq(<tr>);
	                                print qq(<td> </td>);
	                                print qq(<td><a href="public.html">Home</a></td>);
									print qq(<td><a href="Catalogue.html">Catalogue</a></td>);
	                                print qq(<td><a href="login.html">Login</a></td>);
	                                print qq(<td><a href="Registration.html"><b>Registration</a></td>);
				   				print qq(</tr>);
	                        print qq(</table>);
	                        print qq(</nav>);
	                        print qq(<br>);

	                        print qq(<section>);
	                        print qq(The fields cannot contain a comma! Please use the navigation bar to return try again.);
	                        print qq(</section>);

	                        print qq(<footer>);
	                        print qq(Copyright *** bikr.com);
	                        print qq(</footer>);

	                        print qq(</body>);
	                        print qq(</html>);
	} 
	#check if the fields are the correct length
	elsif((length($fullname) > 64) || (length($username) > 64) || (length($password1) > 64)){
							print qq(<head>);
	                        print qq(<link rel="stylesheet" type="text/css" href="mystyle.css">);
	                        print qq(</head>);

	                        print qq(<body>);

	                        print qq(<header>);
	                        print qq(<img style="float:center;width:230px;height:160px" src="Images/logo-2.jpg">);
	                        print qq(<h1 style="float:right;color:white;padding:5px">Call Us: 1-888-245-0000</h1>);
	                        print qq(</header>);

	                        print qq(<!--make sure to change the size of the header of the current page-->);
	                        print qq(<nav>);
	                        print qq(<table>);
	                            print qq(<tr>);
	                                print qq(<td> </td>);
	                                print qq(<td><a href="public.html">Home</a></td>);
									print qq(<td><a href="Catalogue.html">Catalogue</a></td>);
	                                print qq(<td><a href="login.html">Login</a></td>);
	                                print qq(<td><a href="Registration.html"><b>Registration</a></td>);
				   				print qq(</tr>);
	                        print qq(</table>);
	                        print qq(</nav>);
	                        print qq(<br>);

	                        print qq(<section>);
	                        print qq(One of your fields was too long! The maximum character is 64 for each field. Use the navigation bar to return and try again.);
	                        print qq(</section>);

	                        print qq(<footer>);
	                        print qq(Copyright *** bikr.com);
	                        print qq(</footer>);

	                        print qq(</body>);
	                        print qq(</html>);
	}
	#add the new user
	else{
		#open the database of members
		my $filename = "members.csv"; 
		
		open(INPUT, $filename) or die "Cannot open $filename";
		
		# Read the header line.
		my $line = <INPUT>;
		
		# Read the lines one by one. and check if the user exists
		while($line = <INPUT>)
		{
			chomp($line);
			my ($currentFullname, $currentUsername, $currentPassword) = split(',', $line);
			#print "$currentFullname wants to be called $currentUsername and his password is $currentPassword\n";
			
			#if the user exists, quit reading and set newUser to False
			if($currentUsername eq $username){
				$newUser = 0;
				print qq(<head>);
				print qq(<link rel="stylesheet" type="text/css" href="mystyle.css">);
				print qq(</head>);

				print qq(<body>);

				print qq(<header>);
				print qq(<img style="float:center;width:230px;height:160px" src="Images/logo-2.jpg">);
				print qq(<h1 style="float:right;color:white;padding:5px">Call Us: 1-888-245-0000</h1>);
				print qq(</header>);

				print qq(<!--make sure to change the size of the header of the current page-->);
				print qq(<nav>);
				print qq(<table>);
				    print qq(<tr>);
				        print qq(<td> </td>);
				        print qq(<td><a href="public.html">Home</a></td>);
				        print qq(<td><a href="Registration.html"><b>Registration</a></td>);
				    print qq(</tr>);
				print qq(</table>);
				print qq(</nav>);
				print qq(<br>);

				print qq(<section>);
				print qq(This user already exists! Please use the navigation bar to return to home or registration);
				print qq(</section>);

				print qq(<footer>);
				print qq(Copyright *** bikr.com);
				print qq(</footer>);

				print qq(</body>);
				print qq(</html>);

				last;
			}
		}
		close(INPUT);

		#if it was a new user, append the information to the file
		open(my $fh, '>>', $filename) or die "Cannot open $filename";
		if($newUser){
			print $fh "$fullname,$username,$password1\n";
				 print qq(<head>);
	                        print qq(<link rel="stylesheet" type="text/css" href="mystyle.css">);
	                        print qq(</head>);

	                        print qq(<body>);

	                        print qq(<header>);
	                        print qq(<img style="float:center;width:230px;height:160px" src="Images/logo-2.jpg">);
	                        print qq(<h1 style="float:right;color:white;padding:5px">Call Us: 1-888-245-0000</h1>);
	                        print qq(</header>);

	                        print qq(<!--make sure to change the size of the header of the current page-->);
	                        print qq(<nav>);
	                        print qq(<table>);
	                            print qq(<tr>);
	                                print qq(<td> </td>);
	                                print qq(<td><a href="public.html">Home</a></td>);
									print qq(<td><a href="Catalogue.html">Catalogue</a></td>);
	                                print qq(<td><a href="login.html">Login</a></td>);
	                                print qq(<td><a href="Registration.html"><b>Registration</a></td>);
				   			print qq(</tr>);
	                        print qq(</table>);
	                        print qq(</nav>);
	                        print qq(<br>);

	                        print qq(<section>);
	                        print qq(User succesfully added! Please use the navigation bar to return);
	                        print qq(</section>);

	                        print qq(<footer>);
	                        print qq(Copyright *** bikr.com);
	                        print qq(</footer>);

	                        print qq(</body>);
	                        print qq(</html>);

		}
	}
	
	
