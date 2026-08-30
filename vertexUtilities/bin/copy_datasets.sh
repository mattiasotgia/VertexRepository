#!/usr/bin/env bash

source_path=""
target_path=""
depth=""

usage () {
    echo "USAGE: merge_productions.sh -s <SOURCE_PATH> -t <TARGET_PATH> [-h] [-d <SEARCH_DEPTH>]"
    echo " -s <SOURCE_PATH>     Path where the input files live"
    echo " -t <TARGET_PATH>     Target path where to copy datasets"
    echo " -d <SEARCH_DEPTH>    OPTIONAL: Min/max search path for the source input"
    echo " -h                   Show this help page and exit"
}

while getopts "hs:t:d:" opt; do
    case $opt in
	h)
	    usage
	    exit 0
	    ;;
	s) source_path="$OPTARG" ;;
	t) target_path="$OPTARG" ;;
    d) depth="$OPTARG"       ;;
	\?)
	    echo "Invalid option: -$OPTARG"
	    exit 1
	    ;;
    esac
done

if [[ -z $source_path ]]; then
    echo "Option -s <SOURCE_PATH> is required!"
    usage
    exit 1
fi

if [[ -z $target_path ]]; then
    echo "Option -t <TARGET_PATH> is required!"
    usage
    exit 1
fi

if [[ -z $depth ]]; then
    echo "Option -d <SEARCH_DEPTH> not enered, using default (3)"
    depth="3"
fi

shift $((OPTIND - 1))

# Ensure target directory exists
mkdir -p "$target_path"

echo "Counting files (min/max-depth = $depth) in"
echo "source_path = $source_path"
echo " * counted $(find "$source_path" -mindepth $depth -maxdepth $depth -name "*.csv" | wc -l) file(s)"

echo "Copying files (min/max-depth = $depth)"
echo " * from source_path = $source_path"
echo " * to   target_path = $target_path"
find "$source_path" -mindepth $depth -maxdepth $depth -name "*.csv" -print0 | xargs -0 -r cp -t $target_path


echo "Finished copy, counting files in"
echo "target_path = $target_path"
echo " * counted $(find "$target_path" -name "*.csv" | wc -l) file(s)"
