#!/bin/bash

#use in linux 
#objdump and readelf installed
if (($# != 2))
then
    echo """
        ERROR!!!
        Usage: ./getoffset.sh libxxx.so func_name
    """
    exit
fi

echo """
    parser offset of function in libxxx.so
    and store this value to .file
    value format is 0x
"""


name=`echo $1 | cut -d. -f1`

objdump -D $1 > ${name}.info

key=\<$2@plt\>\:

line=`cat -n ${name}.info | grep "$key" | awk '{print $1}'`
let line=line+1

num=`cat -n ${name}.info | sed -n "${line}p" | cut -d# -f 2 | awk '{print $1}'`

echo $num > ${name}_$2.file

chmod +r ${name}_$2.file