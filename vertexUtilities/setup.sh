
echo "Working directory is ${PWD}"
echo "Setting up env..."

script="${BASH_SOURCE[0]}"
name="$(readlink -f "$script")"   # optional but recommended
base="$(dirname "$name")"

echo "Executing $name"
echo "Base dir in $base"

export FW_SEARCH_PATH=/exp/icarus/app/users/msotgia/analysis/VertexRepository/vertexUtilities/:$FW_SEARCH_PATH
export FHICL_FILE_PATH=/exp/icarus/app/users/msotgia/analysis/VertexRepository/vertexUtilities/fcl:$FHICL_FILE_PATH

savedPathToBin="$base"
echo "--> /bin lives in $savedPathToBin/bin"

if [[ ! -f "$savedPathToBin/bin/merge_productions.sh" ]]; then
    echo "Not able to source /bin"
fi

# CSV merging
merge_productions.sh () {
    sh $savedPathToBin/bin/merge_productions.sh $@
}

export PATH=$savedPathToBin/bin/:$PATH