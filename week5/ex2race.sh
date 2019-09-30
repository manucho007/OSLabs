#!/bin/bash 
                                                                      
if test ! -f 258_numbers
then
    #create the numbers file                                                   
    echo 0 > 258_numbers
fi

#Repeat 100 times to see fun
for i in `seq 1 100`;
do
	#Read and increase last number
	LASTNUMBER=`tail -1 258_numbers`
	LASTNUMBER=$((LASTNUMBER+1))

	echo $LASTNUMBER >> 258_numbers
done