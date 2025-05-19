#!/bin/bash

function runDSelector() {

root -l -b << EOF
TTree::SetMaxTreeSize(2000000000000LL); // 2TB
.x $ROOT_ANALYSIS_HOME/scripts/Load_DSelector.C
TChain *chain = new TChain("$reaction_filter");
chain->Add("$data");
DPROOFLiteManager::Process_Chain(chain,"$DSelector++", $nthreads, "$hist", "$tree"); 
EOF

# mv $hist hists/$hist
mv ftree.root $ftree
# mv $tree trees/$tree
}

nthreads=32

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
runDSelector

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

rm -r 0.*
