#!/bin/bash

#Trevor Brooks
#Based on script designed by Kendall Schmit

#General precondition
	#If script will not run, make sure to run "chmod 744 ssRandomTest.sh"
	#Change the initials and names variables below to match the initials of the student run being performed
	#Testing is ran by putting the following into the shell "./ssRandomTestBTL.sh"
	
#Code file requirements
	#Code file should be named serviceStationLFM.cpp where LFM matches the variable initials below.
	#Code file should be a valid cpp file and should not require any other files to compile
	
#Test file requirements
	#Test files are generated by executable version of ./testGenerator/SSrandomTestBTL.cpp
	
	
#Output of this script
	#Input test files are generated into 
	#My test results are saved to myRandomTestResultsBTL.txt
	#Michael Fryer's results are saved to otherRandomTestResults
	
#Change these vars/functions as tests change
initials=BTL
name="Trevor Brooks"
otherInitials=FMD
otherName="Michael Fryer"
exe=./serviceStation$initials
other_exe=./serviceStation$otherInitials
file_prefix="testGenerator/ss"$initials
test_count=9
my_out_file="myRandomTestResults"$initials".txt"
other_out_file="otherRandomTestResults"$initials".txt"

in_file_name(){
    echo "$file_prefix"$(printf "%02d" $1)"in.txt"
}

#Main procedure:
#Compile my program
g++ -std=c++11 -c serviceStation$initials.cpp
g++ -o serviceStation$initials serviceStation$initials.o

#Compile test generator
g++ -std=c++11 -c testGenerator/SSrandomTest$initials.cpp
g++ -o testGenerator/SSrandomTest$initials SSrandomTest$initials.o

#Compile Michael's program
g++ -std=c++11 -c serviceStation$otherInitials.cpp
g++ -o serviceStation$otherInitials serviceStation$otherInitials.o

#for ((i = 1; i <= test_count; i++))
#do
#    rm $(in_file_name $i)
#done

#./testGenerator/SSrandomTest$initials
#mv ssBTL* testGenerator/

rm serviceStation$initials.o
rm $my_out_file
echo "+++ServiceStation"$initials" Random Test Run+++" >> $my_out_file
echo "Testing the file serviceStation"$initials".cpp by "$name >> $my_out_file
echo "" >> $my_out_file

for ((i = 1; i <= test_count; i++))
do
    echo "Input File: "$(in_file_name $i) >> $my_out_file
    result=$($exe <$(in_file_name $i))
    echo "Number of service stations: "$result >> $my_out_file
	echo "" >> $my_out_file
done

echo "---ServiceStation"$initials" Random Test Run---" >> $my_out_file


#Run tests for Michael's code
rm serviceStation$otherInitials.o
rm $other_out_file
echo "+++ServiceStation"$initials" Random Test Run+++" >> $other_out_file
echo "Testing the file serviceStation"$otherInitials".cpp by "$otherName >> $other_out_file
echo "" >> $other_out_file

for ((i = 1; i <= test_count; i++))
do
    echo "Input File: "$(in_file_name $i) >> $other_out_file
    result=$($other_exe <$(in_file_name $i))
    echo "Number of service stations: "$result >> $other_out_file
	echo "" >> $other_out_file
done

echo "---ServiceStation"$initials" Random Test Run---" >> $other_out_file

