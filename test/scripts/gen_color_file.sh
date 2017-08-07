#!/bin/bash

# this script generates a color file given a directory of .bwtdisk files

OUTPUT=$1/colors.txt

FILES=($(ls $1/*.bwtdisk))

for file in ${FILES[*]}; do
    BARE_FILE=$(basename $file)
    NAME="${BARE_FILE%.*}"
    echo "$NAME $file" >> $OUTPUT
done
