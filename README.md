# ICARUS DL vertex creation algorithm

This repository holds all the code/utilities/analyses relative to the implementation of the DL-based vertex creation algorithm in the ICARUS Pandora-based reconstruction chain. 

To start, follow the instruction reported below in [the setup section](#setting-the-repository-up-for-developments). 

## Setting the repository up for developments

### Setup for local testing

To use the code on `icarusgpvm*` (which is required to setup analysis jobs/productions) it is required to start the SL7 container

```bash
sh /exp/$(id -ng)/data/users/vito/podman/start_SL7dev_jsl.sh
```

and source the ICARUS setup

```bash
source /cvmfs/icarus.opensciencegrid.org/products/icarus/setup_icarus.sh
setup sam_web_client
```

Once done, the setup of most of the code here is performed with 
```bash
source setup.sh
```

### Setup for 


## Subdirectories


