#!/bin/bash

##### No PROOF #####
# root -l /d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_sdme1_sp17_20M_3463/trees/tree_ksmisskl__B3_M16_gen_amp/tree_ksmisskl__B3_M16_gen_amp_031057.root << EOF
# root -l /d/grid17/gabyrod7/gluex_data/RunPeriod-2017-01/ver60/tree_ksmisskl__B3_M16/tree_ksmisskl__B3_M16_031052.root << EOF
root -l /d/grid17/gabyrod7/gluex_data/RunPeriod-2017-01/ver60/tree_ksmisskl__B3_M16/tree_ksmisskl__B3_M16_03105*.root << EOF
.x $ROOT_ANALYSIS_HOME/scripts/Load_DSelector.C
// ksmisskl__B3_M16_Tree->Process("DSelector_pulls.C+","",2,1); // run over two events
ksmisskl__B3_M16_Tree->Process("DSelector_pulls.C+","");
EOF

