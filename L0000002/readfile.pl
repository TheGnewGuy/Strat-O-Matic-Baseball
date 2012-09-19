open (MYFILE, "< tp000017.dat") 
	or die "Can not Open file";
#binmode MYFILE, ":raw";

open (MYOUTFILE, "> test.dat");
#binmode MYOUTFILE, ":raw";

while(read MYFILE, $myIn, 1)
{
#	printf("%2x - %s - %2u\n",myIn,$myIn,$myIn);
	print (sprintf "%x\n", myIn);
	print MYOUTFILE $myIn;
}
close MYFILE;
close MYOUTFILE;

