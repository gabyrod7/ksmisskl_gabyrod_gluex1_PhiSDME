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

nthreads=32

## Spring 2017 data
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
#data="/d/grid17/gabyrod7/gluex_data/RunPeriod-2017-01/ver60/tree_ksmisskl__B3_M16/reduced/tree_ksmisskl__B3_M16_03099*"
# data="/d/grid17/gabyrod7/gluex_data/RunPeriod-2017-01/ver60/tree_ksmisskl__B3_M16/reduced/tree*"
data="trees/tree_dat_sp17.root"
hist="hist_dat_sp17.root"
tree="tree_dat_sp17.root"
ftree="ftree_dat_sp17.root"
runDSelector

# Spring 2018 data
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
# data="/d/grid17/gabyrod7/gluex_data/RunPeriod-2018-01/tree_ksmisskl__B3_M16/reduced/tree_ksmisskl__B3_M16_04255*"
# data="/d/grid17/gabyrod7/gluex_data/RunPeriod-2018-01/tree_ksmisskl__B3_M16/reduced/t*"
data="trees/tree_dat_sp18.root"
hist="hist_dat_sp18.root"
tree="tree_dat_sp18.root"
ftree="ftree_dat_sp18.root"
runDSelector

# Fall 2018 data
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
# data="/d/grid17/gabyrod7/gluex_data/RunPeriod-2018-08/tree_ksmisskl__B3_M16/reduced/t*"
data="trees/tree_dat_fa18.root"
hist="hist_dat_fa18.root"
tree="tree_dat_fa18.root"
ftree="ftree_dat_fa18.root"
runDSelector

## Spring 2017 reconstructed phi MC
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_sp17_18M_3406/root/trees/t*"
hist="hist_acc_sp17.root"
tree="tree_acc_sp17.root"
ftree="ftree_acc_sp17.root"
# runDSelector

## Spring 2017 thrown phi MC
DSelector="DSelector_thrown.C"
reaction_filter="Thrown_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_sp17_18M_3406/root/thrown/t*"
hist="hist_gen_sp17.root"
tree="tree_gen_sp17.root"
ftree="ftree_gen_sp17.root"
# runDSelector

## Spring 2018 reconstructed phi MC
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_sp18_50M_3407/root/trees/t*"
hist="hist_acc_sp18.root"
tree="tree_acc_sp18.root"
ftree="ftree_acc_sp18.root"
# runDSelector

## Spring 2018 thrown phi MC
DSelector="DSelector_thrown.C"
reaction_filter="Thrown_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_sp18_50M_3407/root/thrown/t*"
hist="hist_gen_sp18.root"
tree="tree_gen_sp18.root"
ftree="ftree_gen_sp18.root"
# runDSelector

## Fall 2018 reconstructed phi MC
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_fa18_32M_3408/root/trees/t*"
hist="hist_acc_fa18.root"
tree="tree_acc_fa18.root"
ftree="ftree_acc_fa18.root"
# runDSelector

## Fall 2018 thrown phi MC
DSelector="DSelector_thrown.C"
reaction_filter="Thrown_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_fa18_32M_3408/root/thrown/t*"
hist="hist_gen_fa18.root"
tree="tree_gen_fa18.root"
ftree="ftree_gen_fa18.root"
# runDSelector

# ## phi MC shifted mass
# DSelector="DSelector_phi.C"
# reaction_filter="ksmisskl__B3_M16_Tree"
# data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_shifted_10M/root/trees/tree_ksmisskl__B3_M16_gen_amp/t*"
# hist="hist_acc_shifted.root"
# tree=""
# ftree="ftree_acc_shifted.root"
# # runDSelector

# ## Fall 2018 reconstructed phi MC with shifted mass
# DSelector="DSelector_phi.C"
# reaction_filter="ksmisskl__B3_M16_Tree"
# data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_fa18_15M_shifted_mass_3379/root/trees/tree_ksmisskl__B3_M16_gen_amp/t*"
# hist="hist_acc_fa18_shifted_v2.root"
# tree=""
# ftree="ftree_acc_fa18_shifted_v2.root"
# runDSelector

# ## Fall 2018 thrown phi MC with shifted mass
# DSelector="DSelector_thrown.C"
# reaction_filter="Thrown_Tree"
# data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_fa18_15M_shifted_mass_3379/root/thrown/t*"
# hist="hist_gen_fa18_shifted_v2.root"
# tree=""
# ftree="ftree_gen_fa18_shifted_v2.root"
# runDSelector

./hadd.sh

rm -r 0.*
