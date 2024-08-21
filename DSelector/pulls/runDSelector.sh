#!/bin/bash

function runDSelector() {

root -l -b << EOF
TTree::SetMaxTreeSize(2000000000000LL); // 2TB
.x $ROOT_ANALYSIS_HOME/scripts/Load_DSelector.C
TChain *chain = new TChain("$reaction_filter");
chain->Add("$data");
DPROOFLiteManager::Process_Chain(chain,"$DSelector++", $nthreads, "$hist", "$tree"); 
EOF

mv $hist hists/$hist
mv ftree.root ftrees/$ftree
mv $tree trees/$tree
}

nthreads=16

## Spring 2017 data
DSelector="DSelector_pulls.C"
reaction_filter="ksmisskl__B3_M16_Tree"
data="/d/grid17/gabyrod7/gluex_data/RunPeriod-2017-01/ver60/tree_ksmisskl__B3_M16/tree_ksmisskl__B3_M16_0309*"
# data="/d/grid17/gabyrod7/gluex_data/RunPeriod-2017-01/ver60/tree_ksmisskl__B3_M16/tree*"
# data="trees/tree_dat_sp17.root"
hist="hist_dat_sp17.root"
tree="tree_dat_sp17.root"
ftree="ftree_dat_sp17.root"
runDSelector

## Spring 2017 reconstructed phi MC
DSelector="DSelector_pulls.C"
reaction_filter="ksmisskl__B3_M16_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_sp17_18M_3406/root/trees/t*"
hist="hist_acc_sp17.root"
tree="tree_acc_sp17.root"
ftree="ftree_acc_sp17.root"
# runDSelector

# Spring 2018 data
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
# data="/d/grid17/gabyrod7/gluex_data/RunPeriod-2018-01/tree_ksmisskl__B3_M16/reduced/tree_ksmisskl__B3_M16_04255*"
# data="/d/grid17/gabyrod7/gluex_data/RunPeriod-2018-01/tree_ksmisskl__B3_M16/reduced/t*"
# data="trees/tree_dat_sp18.root"
data="/d/grid17/gabyrod7/gluex_data/RunPeriod-2018-01/ver22/tree_ksmisskl__B3_M16/t*"
hist="hist_dat_sp18.root"
tree="tree_dat_sp18.root"
ftree="ftree_dat_sp18.root"
# runDSelector

# Fall 2018 data
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
# data="/d/grid17/gabyrod7/gluex_data/RunPeriod-2018-08/tree_ksmisskl__B3_M16/reduced/t*"
data="/d/grid17/gabyrod7/gluex_data/RunPeriod-2018-08/ver20/tree_ksmisskl__B3_M16/t*"
# data="trees/tree_dat_fa18.root"
hist="hist_dat_fa18.root"
tree="tree_dat_fa18.root"
ftree="ftree_dat_fa18.root"
# runDSelector

# Spring 2020 data
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
data="/d/grid17/gabyrod7/gluex_data/RunPeriod-2019-11/ver09/tree_ksmisskl__B3_M16/t*"
hist="hist_dat_sp20.root"
tree="tree_dat_sp20.root"
ftree="ftree_dat_sp20.root"
# runDSelector

rm -r 0.*
