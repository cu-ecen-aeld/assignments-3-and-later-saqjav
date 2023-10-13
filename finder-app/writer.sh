#!/bin/sh
# Script for assignment 1 and assignment 2
# Author: Saqib Javed

if [ $# -lt 2 ]
then
	echo "Incomplete Parameters."
	exit 1
fi

FILE=$1
FILE_Dir=${FILE%/*}/
STRING=$2
Sum=0
files_count=0

mkdir -p ${FILE_Dir}

echo ${STRING} > ${FILE}