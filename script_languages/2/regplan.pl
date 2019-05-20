#!/usr/bin/perl

my $content;
open(my $fh, '<', $ARGV[0]) or die "cannot open file $ARGV[0]";
{
	local $/;
	$content = <$fh>;
}

my @date_start = ($content =~ m/DTSTART;TZID.*/g);
my @date_end = ($content =~ m/DTEND;TZID.*/g);
#print @date_start; T.*?(T).*


my $time_start;
my $time_end;

my $bhours;
my $bminutes;
my $bseconds;

my $ehours;
my $eminutes;
my $eseconds;

my $totalhours = 0;
my $totalminutes;

for($loop_index = 0; $loop_index <= $#date_start; $loop_index++) {
    $time_start = ( split('T', $date_start[$loop_index]) )[4 .. 5] ;
	if ($time_start =~ /(\d\d)(\d\d)(\d\d)/)
	{    # match hh:mm:ss format
		$bhours = $1;
		$bminutes = $2;
		$bseconds = $3;
	}
	
	$time_end = ( split('T', $date_end[$loop_index]) )[2 .. 3] ;
	if ($time_end =~ /(\d\d)(\d\d)(\d\d)/)
	{    # match hh:mm:ss format
		$ehours = $1;
		$eminutes = $2;
		$eseconds = $3;
	}
	
	#print "time = $ehours:$eminutes\t-\t$bhours:$bminutes\t";
	$bhours = ($ehours - $bhours) * 60;
	$bminutes = ($eminutes - $bminutes);
	$bhours = $bhours + $bminutes;
	#print "diff = $bhours\n";
	$totalhours += $bhours - 15;
}

{
	use integer;
	$totalminutes = $totalhours % 60;
	$totalhours = $totalhours / 45;
	print "total = $totalhours:$totalminutes\n";
}
#na 3

#my @lessons = ($content =~ /BEGIN:VEVENT(.*?)END:VEVENT/g);
my @lessons = split /BEGIN:VEVENT/, $content;
$lessons = join('', @lessons);
@lessons = split /END:VEVENT/, $lessons;


# Historia informatyki 
# Programowanie 2 
# Programowanie kart graficznych 
# Programowanie sieciowe 
# Programowanie wizualne 
# Programowanie w językach skryptowych 
# Systemy operacyjne II 


#foreach my $i (@lessons)

my $lesson_start;
my $lesson_end;
my $lesson_time;
my $lesson_name;

my @csv_name;
my @csv_begin;
my @csv_end;

for($loop_index = 1; $loop_index <= $#lessons -1; $loop_index++)
{
	$lessons[$loop_index];
	$lesson_start = ( split('\n', $lessons[$loop_index]))[1..2];
	$lesson_end = ( split('\n', $lessons[$loop_index]))[1..3];
	$lesson_name = ( split('\n', $lessons[$loop_index]))[1..6];
	$lesson_name = ( split(':', $lesson_name))[1..1];
	chomp $lesson_name;
	$lesson_name = substr($lesson_name, 0, index($lesson_name, '-'));
	#chomp $lessons[$loop_index];
	#($lesson_start) = ($lessons[$loop_index] =~ /DTSTART;TZID\*/);


	#print "$lessons[$loop_index]\n";
	#print "\t$lesson_start";


	$time_start = ( split('T', $lesson_start) )[4 .. 5] ;
	if ($time_start =~ /(\d\d)(\d\d)(\d\d)/)
	{    # match hh:mm:ss format
		$bhours = $1;
		$bminutes = $2;
		$bseconds = $3;
	}
	
	$time_end = ( split('T', $lesson_end) )[2 .. 3] ;
	if ($time_end =~ /(\d\d)(\d\d)(\d\d)/)
	{    # match hh:mm:ss format
		$ehours = $1;
		$eminutes = $2;
		$eseconds = $3;
	}
	#print "$lesson_name:\t$bhours:$bminutes - $ehours:$eminutes\n";
	chomp $lesson_name;
	push(@csv_name, $lesson_name);
	push(@csv_begin, "$bhours:$bminutes");
	push(@csv_end, "$ehours:$eminutes");
}
close($fh);

my $wfilename = 'report.csv';
open(my $fwh, '>', $wfilename) or die "Could not open file '$wfilename' $!";
print $fwh "nazwa;godzina_rozpoczecia;godzina_konca\n";
for($loop_index = 0; $loop_index <= $#csv_name; $loop_index++)
{
	print $fwh "$csv_name[$loop_index];$csv_begin[$loop_index];$csv_end[$loop_index]\n";
}
close $fwh;
