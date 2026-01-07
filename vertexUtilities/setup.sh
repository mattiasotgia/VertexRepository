
echo "Working directory is ${PWD}\nSetting up env..."

name=$0
base="${name%/setup.sh}"

savedPathToBin="$PWD/$base"
echo "--> /bin lives in $savedPathToBin/bin"

if [[ ! -f "$savedPathToBin/bin/merge_productions.sh" ]]; then
    echo "Not able to source /bin"
fi

# CSV merging
merge_productions.sh () {
    sh $savedPathToBin/bin/merge_productions.sh $@
}

