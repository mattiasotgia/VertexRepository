#!/bin/bash

function usage(){
    echo "Usage: `basename $0` -d <DEFINITION> -e <EXTENSION> -f <FORMAT> [-si]" >&2
    echo " -d <DEFINITION>        SAMWEB definition to look into        (required)"
    echo " -e <EXTENSION>         Extension for the *new* definition    (required)"
    echo " -f <FORMAT>            Format of the files to add to the"
    echo "                        definition                            (required)"
    echo " -s                     Set ENV_VAR for sbn"
    echo "                          (optional, clashes with -i, latest called gets used)"
    echo " -i                     Set ENV_VAR for icarus" 
    echo "                          (optional, clashes with -s, latest called gets used)"
    echo ""
    echo " -h                     Show this help page and exit"
}

function env_vars(){
   echo "Set ENV_VARS..."
   echo "    \$SAM_GROUP:      $SAM_GROUP"
   echo "    \$SAM_EXPERIMENT: $SAM_EXPERIMENT"
   echo "    \$EXPERIMENT:     $EXPERIMENT"
}

while getopts "hd:e:f:is" opt; do
    case $opt in
	h)
	    usage
	    exit 0
	    ;;
	d) 
        defname="$OPTARG" 
        ;;
# 	e) event="$OPTARG" ;;
	e)
	    extension="$OPTARG"
	    ;;
	f)
		format_string="$OPTARG"
		;;
	s) 
	    export SAM_GROUP=sbn
	    export SAM_EXPERIMENT=sbn
	    export EXPERIMENT=sbn
	    env_vars
	    ;;
	i)
	    unset SAM_GROUP
	    export SAM_EXPERIMENT=icarus
	    export EXPERIMENT=icarus
	    env_vars
	    ;;
	\?)
	    echo "Invalid option: -$OPTARG"
	    usage
	    exit 1
	    ;;
    esac
done

if [[ -z $defname ]]; then
    echo "Option -d <DEFINITION> is required!"
    usage
    exit 1
fi

if [[ -z $extension ]]; then
    echo "Option -e <EXTENSION> is required!"
    usage
    exit 1
fi

if [[ -z $format_string ]]; then
    echo "Option -f <FORMAT>  is required!"
    usage
    exit 1
fi

shift $((OPTIND - 1))

echo "Selecting from $defname, with format $format_string"
samweb list-files "defname:$defname and file_name like $format_string" | head

while true; do
    read -r -p "Do you want to continue? [y/n] " choice
    case "$choice" in
      n|N) break ;;
      y|Y)
        newdef="${defname}_${extension}"
        echo "Creating $newdef with $format_string"
        samweb create-definition "$newdef" "defname:$defname and file_name like $format_string"
        break
        ;;
      *) echo "Please answer y or n." ;;
    esac
done
