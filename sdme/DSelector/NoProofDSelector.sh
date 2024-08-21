#!/bin/bash

##### No PROOF #####
root -l /d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_sdme1_sp17_20M_3463/trees/tree_ksmisskl__B3_M16_gen_amp/tree_ksmisskl__B3_M16_gen_amp_031057.root << EOF
.x $ROOT_ANALYSIS_HOME/scripts/Load_DSelector.C
ksmisskl__B3_M16_Tree->Process("DSelector_recon.C+","",2,1);
EOF

