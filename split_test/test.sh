#!/bin/bash

flag="1"

while [ $flag == "1" ] ; do
    echo "Running at `date` " >> test.txt
    caget hcCOINRunInProgress >> test.txt
    echo "  " >> test.txt
    sleep 5
done

# screen -S caget_test

# ./test.sh 30 a 180 b
# /net/cdaqfs1/cdaqfs-coda-home/coda/coda/scripts/EPICS_logging

# time=$1
# file=$2
# evtag=$3
# DICT=$4

# input_file="epics_30.results"
# output_dir="split_files"
# lines_per_split=190
# split_suffix="results"
# split_files_first=
# evtag_split=$((evtag + 2))


# if [ $time == "30" ]; then
#     mkdir -p "$output_dir"
#     rm -f "$output_dir"/*
#     split -d -l "$lines_per_split" "$input_file" "$output_dir/epics_30_split_$split_suffix" >> /dev/null  2>&1
#     split_files=("$output_dir"/*)
#     if [ "${#split_files[@]}" -gt 0 ]; then
#         split_files_first="${split_files[0]}" 
#     fi

#     ## start looping with specified period
#     echo "EPICS Logging started at $time second interval..."
#     # while $FILETOEVENT $split_files_first ER1 $evtag ; do
#     while [ $time == "30" ] ; do
#         evtag_split=$((evtag + 2))
#         echo "$split_files_first"
#         echo "$evtag_split"
#         for file in "${split_files[@]}"; do
#             if [ "$file" != "$split_files_first" ]; then
#                 evtag_split=$((evtag_split + 1))
#                 # $FILETOEVENT $$file ER1 $evtag_split
#                 echo "$file"
#                 echo "$evtag_split"
#             fi
#         done

#         sleep 2
#         # get_epics

#         mkdir -p "$output_dir"
#         rm -f "$output_dir"/*
#         split -d -l "$lines_per_split" "$input_file" "$output_dir/epics_30_split_$split_suffix" >> /dev/null  2>&1
#         split_files=("$output_dir"/*)
#         if [ "${#split_files[@]}" -gt 0 ]; then
#             split_files_first="${split_files[0]}" 
#         fi
#     done
#     exit 0
# fi

    
    

    