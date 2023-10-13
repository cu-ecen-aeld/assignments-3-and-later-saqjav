#!/bin/sh
# Script for assignment 1 and assignment 2
# Author: Saqib Javed

if [ $# -lt 2 ]
then
	echo "Incomplete Parameters."
	exit 1
fi

DIR=$1
STRING=$2
Sum=0
files_count=0

if [ ! -d ${DIR} ]; then
   echo "Warning: ${DIR} NOT found."
fi

files_count=$(grep -lr ${STRING} ${DIR} | wc -l)

for file in ${DIR}/*; do
   tempsum=$(grep -c ${STRING} ${file})
   Sum=$((Sum + tempsum))
done

echo "The number of files are ${files_count} and the number of matching lines are ${Sum}"