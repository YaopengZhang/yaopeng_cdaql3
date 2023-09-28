#!/bin/bash

time=$1
file=$2
evtag=$3
DICT=$4

input_file="epics_30.results"
output_dir="split_files"
lines_per_split=190
split_suffix="results"

mkdir -p "$output_dir"

rm -f "$output_dir"/*



if [ $time == "HV" ]; then
    echo "EPICS Logging started at $time second interval..."
fi

if [ $time == "30" ]; then
    echo "EPICS Logging started at $time second interval..."
fi


split -d -l "$lines_per_split" "$input_file" "$output_dir/epics_30_split_$split_suffix" >> /dev/null  2>&1



split_files=("$output_dir"/*)

first_file=true
for file in "${split_files[@]}"; do
    if [ "$first_file" = true ]; then
        first_file=false
    else
        # $FILETOEVENT "$file" ER1 "$evtag"
        echo "Transferring $file..."
    fi
done
