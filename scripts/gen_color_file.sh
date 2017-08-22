#!/bin/bash

# this script generates a color file given a directory of .bwtdisk files

OUTPUT=$(readlink -m $1)/colors.txt

[ -e $OUTPUT ] && rm $OUTPUT

FILES=($(ls $1/*.bwtdisk))

for file in ${FILES[*]}; do
    BARE_FILE=$(basename $file)
    NAME="${BARE_FILE%.*}"
    echo "$NAME $(readlink -m $file)" >> $OUTPUT
done
