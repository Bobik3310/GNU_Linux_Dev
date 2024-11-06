#!/bin/bash

echo "How test program?"
echo -e "\"Error injection\"? Enter 1"
echo -e "\"LD_PRELOAD\"? Enter 2"

read type

make -s clean all

# КАК ОТЛАЖИВАТЬ printf?
# ПОЧЕМУ write ПЕРЕД close, А НЕ ПОСЛЕ read?

if [ "$type" -eq 1 ]; then
	echo -e "\n++++++++++++++++++++\n"

	echo "Inject while open outfile:"
	make | strace -y -e trace=openat -e fault=openat:when=3 ./move infile outfile

	echo -e "\n++++++++++++++++++++\n"
	
	echo "Inject read from infile:"
	make | strace -y -e trace=read -e fault=read:when=2 ./move infile outfile
	
	echo -e "\n++++++++++++++++++++\n"

	echo "Inject while write to outfile:"
	make | strace -y -e trace=write -e fault=write:when=1 ./move infile outfile

	echo -e "\n++++++++++++++++++++\n"

elif [ "$type" -eq 2 ]; then 
	echo -e "With LD_PRELOAD: \"LD_PRELOAD=`pwd`/remove_custom.so ./move PROTECT_infile outfile\"? Enter 1"
	echo -e "Origin program: \"./move infile outfile\"? Enter 2"
	echo -e "Origin program with PROTECT_infile: \"./move PROTECT_infile outfile\"? Enter 3"

	read type

	if [ "$type" -eq 1 ]; then
		LD_PRELOAD=`pwd`/remove_custom.so ./move PROTECT_infile outfile
	elif [ "$type" -eq 2 ]; then
		./move infile outfile
	elif [ "$type" -eq 3 ]; then
		./move PROTECT_infile outfile
	else
		echo "Incorrect input"
	fi
fi
