#!/user/local/bin/perl
use strict;
use CGI ':standard';


#my $fullname = "Jessica Dorval";
#my $username = "jess.dorval";
#my $password1 = "test";
#my $password2 = "test";
my $newUser = "TRUE";

my $fullname = param('fullname');
my $username = param('username');
my $password1 = param('password1');
my $password2 = param('password2');

print"Content-Type:text/html\n\n";
print"<html>";


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
			print"<p>The user exists</p>";
			$newUser = "FALSE";
			last;
		}
	}
	close(INPUT);

	#if it was a new user, append the information to the file
	open(my $fh, '>>', $filename) or die "Cannot open $filename";
	print $newUser;
	if($newUser eq "TRUE"){
		say $fh "\n$fullname,$username,$password1";
	}
	
	
