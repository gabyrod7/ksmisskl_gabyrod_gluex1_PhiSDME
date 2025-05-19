#!/bin/bash

# tree="/d/grid17/gabyrod7/gluex_data/RunPeriod-2017-01/ver60/tree_ksmisskl__B3_M16/tree_ksmisskl__B3_M16_030994.root"
# tree="/d/grid17/gabyrod7/gluex_data/RunPeriod-2017-01/ver60/tree_ksmisskl__B3_M16/tree_ksmisskl__B3_M16_03099*.root"
tree="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_sp17_18M_3406/root/trees/tree_ksmisskl__B3_M16_gen_amp_031054_000.root"

##### No PROOF #####
root -l $tree << EOF
.x $ROOT_ANALYSIS_HOME/scripts/Load_DSelector.C
ksmisskl__B3_M16_Tree->Process("DSelector_phi.C+","hist.root");
EOF

