#! /bin/bash

echo -n "Si o no chee?: "
read ans

if [ $ans == "si" ]
then
	echo "Dijo si"
else
	echo "Dijo no"
fi
