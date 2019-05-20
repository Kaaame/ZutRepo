#!/usr/bin/perl
$argsnum = scalar(@ARGV);
my $dirarg = ".";
my $longflag = 0;
my $hiddenflag = 0;
my $largeflag = 0;

for(my $i = 0; $i <= $argsnum; $i++)
{
	if(index($ARGV[$i],"-a")!=-1)	{$hiddenflag = 1;}
	if(index($ARGV[$i],"-l")!=-1)	{$longflag = 1;}
	if(index($ARGV[$i],"-L")!=-1)	{$largeflag = 1;}
	#if(index($ARGV[$i],"-")==-1)	{$dirarg = $ARGV[$i-1];}
}
if($argsnum!=0)
{
	$dirarg = $ARGV[0];
}
#print "$dirarg and number of args = $argsnum\n";
opendir(DIR, $dirarg) || die "Couldn't open directory";

foreach $name (sort readdir(DIR))
{
	if($hiddenflag == 0 && $longflag == 0)
	{
		if(substr($name,0,1) != '.')
		#if(index($name,"%[.]")==-1)
		{
			print("$name\t");
		}
	}
	if($hiddenflag == 1)
	{
		print ("$name\t");
	}
	if($longflag == 1 || $largeflag == 1)
	{
	
		my ($mode,$size,$mtime, $uid)
       	   = (stat "$dirarg/$name")[2, 7, 9, 4];
	
		my ($s, $m, $h, $d, $mo, $yr) = (localtime "$mtime");
		$datestring = sprintf "%4d-%02d-%02d %02d:%02d:%02d",$yr + 1900,$mo + 1,$d,$h,$s,$m;
		
		my $modestr;
		if(-d $name)
		{
			$modestr = 'd';
		}
		else
		{
			$modestr = '-';
		}
	
		for($i = 8; $i >= 0; $i--)
		{
			@rights = ('x', 'w', 'r');
			$position = $i % 3;
			if($mode&(1<<$i))
			{
				$modestr .= $rights[$position];
			}
			else
			{
				$modestr .= '-';
			}
		}
		my $username = getpwuid($uid);
		if($largeflag == 0)
		{
			print "$name\t$size\t$datestring\t$modestr\n";
		}
		else
		{
			print "$name\t$size\t$datestring\t$modestr\t$username\n";
		}
	}
}
print "\n";

closedir(DIR);
#dokonczyc na 5
#form
