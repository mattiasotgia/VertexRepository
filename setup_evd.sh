#!/usr/bin/env bash

echo "This is $USER@$HOSTNAME:$PWD"
echo "Setting up required code and utilities"

script="${BASH_SOURCE[0]}"
script_name="$(readlink -f "$script")"   # optional but recommended
script_base="$(dirname "$script_name")"

echo "[INFO] Executing $script_name"
echo "[INFO] Base dir in $script_base"

where="/exp/icarus/app/users/msotgia/devareas/dev_v10_06_00_06p03_codeFreeze/localProducts_icaruscode_v10_06_00_06p03_debug_e26/"

# echo "Sourcing setup for local icaruscode installation"
# source $where/setup
# mrbslp

echo "Setting up TITUS EVD"
source /exp/sbnd/app/users/sbnd/static_evd/setup.sh 

echo "Importing fcl files in $script_base/fcl"
export FHICL_FILE_PATH=$script_base/fcl:$FHICL_FILE_PATH

echo "Importing Pandora's XML configuration files in $script_base/configurations/pandora"
export FW_SEARCH_PATH=$script_base/configurations/pandora:$FW_SEARCH_PATH

echo "Importing Pandora's DL weights files in $script_base/data/weights"
export FW_SEARCH_PATH=$script_base/data/weights:$FW_SEARCH_PATH

echo "Exporting bin in $script_base/bin to \$PATH"
export PATH=$script_base/bin/:$PATH


if [[ ! -f "$script_base/bin/merge_productions.sh" ]]; then
    echo "Not able to source /bin"
fi

merge_productions.sh () {
    sh $script_base/bin/merge_productions.sh $@
}

echo "Setting up directories"
cd $script_base
mkdir -p plots tmp


tag="Validation"

VERTEX_DATA_PATH=/exp/icarus/data/users/$USER/VertexDL/$tag/

mkdir -p $VERTEX_DATA_PATH
echo "Created \$VERTEX_DATA_PATH in $VERTEX_DATA_PATH"

echo "Declaring default \$TEST_FILE_STAGE0_BNB"
TEST_FILE_STAGE0_BNB="/pnfs/sbn/data/sbn_fd/poms_Production/mc/2026_Pandora_DL_Vertex_Variation/BNB_nue/v10_06_00_06p03/stage0/23/a9/simulation_genie_icarus_bnb_volDetEnclosure_nue_stage0_91692338_2-a25ed131-db6d-4056-be35-b6993775da79.root"

TEST_FILE_STAGE0_BNB=$(pnfsToXRootD $TEST_FILE_STAGE0_BNB)

token_shell () {
    httokensh -a htvaultprod.fnal.gov -i icarus -- env TEST_FILE_STAGE0_BNB=$TEST_FILE_STAGE0_BNB /bin/bash
}
