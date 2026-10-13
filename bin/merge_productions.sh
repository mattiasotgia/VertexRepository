#!/usr/bin/env bash

outname=""
view=""

usage () {
    echo "USAGE: merge_productions.sh -o <NAME_OF_FILES> -v <VIEWS> [-h]"
    echo " -o <NAME_OF_FILES>  Base file name"
    echo " -v <VIEWS>          Views to be analysed"
    echo " -h                  Show this help page and exit"
}

while getopts "ho:v:" opt; do
    case $opt in
	h)
	    usage
	    exit 0
	    ;;
	o) outname="$OPTARG" ;;
	v) view="$OPTARG" ;;
	\?)
	    echo "Invalid option: -$OPTARG"
	    exit 1
	    ;;
    esac
done

if [[ -z $outname ]]; then
    echo "Option -o <NAME_OF_FILES> is required!"
    usage
    exit 1
fi

if [[ -z $view ]]; then
    echo "Option -v <VIEWS> is required!"
    usage
    exit 1
fi

shift $((OPTIND - 1))

outfile="${outname}${view}.csv"
> $outfile
viewS=$(echo "$view" | grep -o .)

for v in $viewS; do
    all_files=$(ls ${outname}${v}-*.csv)
    for file in $all_files; do
	echo "Adding $file in $outfile"
	cat $file >> $outfile
    done
done

