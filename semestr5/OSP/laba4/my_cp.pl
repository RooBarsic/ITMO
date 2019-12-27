#!/usr/bin/perl
use strict;
use warnings qw(FATAL all);
use Getopt::Long; 

my $vFlag = 0;
my $nFlag = 0;
my $hFlag = 0;

GetOptions('v' => \$vFlag, 'n' => \$nFlag, 'h' => \$hFlag);

if($hFlag == 1){
	print "=================  Name  ===================== \n",
           "cp - Use this command to copy files \n",
           "================= Syntax  ==================== \n",
           "cp [-vn ] [source_file1 ...] [target_file] \n",
           "================= Keys  ====================== \n",
           "-n -- do not rewrite target file if it's exist. \n",
           "-v -- show comments during the process (verbose mode). \n",
           "-h -- help \n",
           "============================================== \n \n";
}

if(@ARGV >= 2){
	my $outputFileName = pop @ARGV;
	if((-s $outputFileName) && ($nFlag == 1)){
		if($vFlag == 1){
			die "File $outputFileName already exist \n";
		}
		exit;
	}
	my $resultStr = "";
	foreach my $intputFileName (@ARGV){
		if($intputFileName eq '-'){
			while(<STDIN>){
				last if /^finish$/;
				$resultStr .= $_;
			}
		}
		else {
			open(my $inputFile, "<:encoding(UTF-8)", $intputFileName) or die "Can't open file $intputFileName";
			while(my $row = <$inputFile>){
				$resultStr .= $row;
			}
			close $inputFile;
			if($vFlag == 1){
				print "copying $intputFileName -> $outputFileName \n";
			}
		}
	}
	open(my $outputFile, ">:encoding(UTF-8)", $outputFileName);
	print $outputFile $resultStr;
	close $outputFile;
}
exit;
