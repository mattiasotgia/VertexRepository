#!/usr/bin/env bash

echo "This is $USER@$HOSTNAME:$PWD"
echo "Setting up required code and utilities"

script="${BASH_SOURCE[0]}"
name="$(readlink -f "$script")"   # optional but recommended
base="$(dirname "$name")"

echo "[INFO] Executing $name"
echo "[INFO] Base dir in $base"

sourcing the 

echo "Importing fcl files in $base/fcl"
export FHICL_FILE_PATH=$base/fcl:$FHICL_FILE_PATH

echo "Importing Pandora's XML configuration files in $base/configurations/pandora"
export FW_SEARCH_PATH=$base/configurations/pandora:$FW_SEARCH_PATH

echo "Importing Pandora's DL weights files in $base/data/weights"
export FW_SEARCH_PATH=$base/data/weights:$FW_SEARCH_PATH

echo "Exporting bin in $base/bin to \$PATH"
export PATH=$base/bin/:$PATH


if [[ ! -f "$base/bin/merge_productions.sh" ]]; then
    echo "Not able to source /bin"
fi

merge_productions.sh () {
    sh $savedPathToBin/bin/merge_productions.sh $@
}

echo "Setting up directories"
mkdir -p plots tmp


tag="Validation"

VERTEX_DATA_PATH=/exp/icarus/data/users/$USER/VertexDL/$tag/

mkdir -p $VERTEX_DATA_PATH
echo "Created \$VERTEX_DATA_PATH in $VERTEX_DATA_PATH"