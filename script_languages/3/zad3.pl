#!/usr/bin/perl

#use strict;
#use warnings;

use HTML::TableExtract;
use HTML::Element;

my $content;
my $contentinput;
my @inputnicknames;
my $inputfileflag = 0;
open(my $fh, '<', $ARGV[0]) or die "cannot open file $ARGV[0]";
{
	local $/;
	$content = <$fh>;
}


if($#ARGV >= 1)
{
    open(my $fh, '<', $ARGV[1]) or die "cannot open file $ARGV[1]";
    {
        local $/;
        $contentinput = <$fh>;
    }
    #print $contentinput;
    $inputfileflag = 1;
    @inputnicknames = split /\n/, $contentinput;
}
#$str !~ s/[^[:ascii:]]//g;
#$content = (tr -cs '[:print:]' ' ');

my $te = HTML::TableExtract->new();
$te->parse($content);
my @rowz;
foreach my $ts ( $te->tables() )
{
    foreach my $row ( $ts->rows() )
    {
        #print join ( " ", @$row ), "\n";
        push(@rowz, join ( " ", @$row ));
        #print join( " ", $ts->row(0), $ts->row(-1)), "\n";
        
    }
}

my @filenicknames;
my @scores;

foreach my $ts ( $te->tables() )
{
    my @row = $ts->rows();
    my @col = $ts->columns();

    foreach my $row ( 1 .. $#row)
    {
        #print $ts->cell($row, 1), "\n";
        
        
        push(@filenicknames, $ts->cell($row, 1));
        my $str = "";
        foreach my $col ( 2 .. $#col)
        {
            if($ts->cell($row, $col) != '-')
            {
                $str.= $ts->cell($row, $col);
            }
            else
            {
                $str.= "0.0";
            }
            $str.= " ";
            $str !~ s/[^[:ascii:]]//g;
            
            #push(@scores, $ts->cell($row, $col));
        }
        $str =~ tr/-/0\.0/;
        #$str.= "\n";
        push(@scores, $str);
        
    }
}



my $loop_index;
for($loop_index = 0; $loop_index <= $#filenicknames; $loop_index++)
{
    if($filenicknames[$loop_index])
    {
        if ($inputfileflag)
        {
            if ( grep( /^$filenicknames[$loop_index]$/, @inputnicknames ) )
            {
                print $filenicknames[$loop_index], "\t\t\t", $scores[$loop_index], "\n";
            }
        }
        else
        {
            print $filenicknames[$loop_index], "\t\t\t", $scores[$loop_index], "\n";
        }
    }
}

# for($loop_index = 0; $loop_index <= $#rowz; $loop_index++)
# {
#     #print $te->tables()[$loop_index];
#     if (my ($match) = $rowz[$loop_index] =~ /^.*?(\d+)/)
#     {
#         if ($rowz[$loop_index] !~ /WIPING/ || $rowz[$loop_index] !~ /SCORE/)
#         {
#             if(grep { $rowz[$loop_index] =~ /\Q$_\E\z/ } @{$filenicknames})
#             {
#                 print $rowz[$loop_index], "\n"
#             }
#             $rowz[$loop_index] =~ (tr/\x20-\x7f//cd);
#             #print $rowz[$loop_index], "\n"
#         }

    
#         #print $rowz[$loop_index], "\n";
#     }
#     else
#     {
#         #print "no match\n";
#     }
# }
close($fh);