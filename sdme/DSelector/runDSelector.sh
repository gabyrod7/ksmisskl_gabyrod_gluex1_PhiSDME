#!/bin/bash

function runDSelector() {

root -l -b << EOF
TTree::SetMaxTreeSize(2000000000000LL); // 2TB
.x $ROOT_ANALYSIS_HOME/scripts/Load_DSelector.C
TChain *chain = new TChain("$reaction_filter");
chain->Add("$data");
DPROOFLiteManager::Process_Chain(chain,"$DSelector++", $nthreads, "$hist", "$tree"); 
EOF

mv ftree.root $ftree
rm $tree
rm $hist
}

nthreads=16

## Spring 2017 data
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
#data="/d/grid17/gabyrod7/gluex_data/RunPeriod-2017-01/ver60/tree_ksmisskl__B3_M16/reduced/tree_ksmisskl__B3_M16_03099*"
data="/d/grid17/gabyrod7/gluex_data/RunPeriod-2017-01/ver60/tree_ksmisskl__B3_M16/tree*"
hist="hist_dat_sp17.root"
tree="tree_dat_sp17.root"
ftree="ftree_dat_sp17.root"
# runDSelector

# Spring 2018 data
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
data="/d/grid17/gabyrod7/gluex_data/RunPeriod-2018-01/ver22/tree_ksmisskl__B3_M16/t*"
hist="hist_dat_sp18.root"
tree="tree_dat_sp18.root"
ftree="ftree_dat_sp18.root"
# runDSelector

# Fall 2018 data
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
data="/d/grid17/gabyrod7/gluex_data/RunPeriod-2018-08/ver20/tree_ksmisskl__B3_M16/t*"
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

## Spring 2017 reconstructed phi MC
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_sp17_18M_3876/trees/tree_ksmisskl__B3_M16_gen_amp/t*"
hist="hist_acc_sp17.root"
tree="tree_acc_sp17.root"
ftree="ftree_acc_sp17.root"
runDSelector

## Spring 2017 thrown phi MC
DSelector="DSelector_thrown.C"
reaction_filter="Thrown_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_sp17_18M_3876/thrown/t*"
hist="hist_gen_sp17.root"
tree="tree_gen_sp17.root"
ftree="ftree_gen_sp17.root"
# runDSelector

## Spring 2018 reconstructed phi MC
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_sp18_50M_3877/root/trees/t*"
hist="hist_acc_sp18.root"
tree="tree_acc_sp18.root"
ftree="ftree_acc_sp18.root"
runDSelector

## Spring 2018 thrown phi MC
DSelector="DSelector_thrown.C"
reaction_filter="Thrown_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_sp18_50M_3877/root/thrown/t*"
hist="hist_gen_sp18.root"
tree="tree_gen_sp18.root"
ftree="ftree_gen_sp18.root"
# runDSelector

## Fall 2018 reconstructed phi MC
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_fa18_32M_3880/trees/tree_ksmisskl__B3_M16_gen_amp/t*"
hist="hist_acc_fa18.root"
tree="tree_acc_fa18.root"
ftree="ftree_acc_fa18.root"
runDSelector

## Fall 2018 thrown phi MC
DSelector="DSelector_thrown.C"
reaction_filter="Thrown_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_fa18_32M_3880/thrown/t*"
hist="hist_gen_fa18.root"
tree="tree_gen_fa18.root"
ftree="ftree_gen_fa18.root"
# runDSelector

## SDME input-output test with only SDME components in generated model
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_sdme1_sp17_20M_3463/trees/tree_ksmisskl__B3_M16_gen_amp/t*"
hist="hist_acc_sdme_test.root"
tree="tree_acc_sdme_test.root"
ftree="ftree_acc_sdme_test.root"
# runDSelector

## SDME input-output test with SDME and background components in generated model
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_sdme_uniform_sp17_20M_3866/trees/tree_ksmisskl__B3_M16_gen_amp/t*"
hist="hist_acc_sdme_uniform.root"
tree="tree_acc_sdme_uniform.root"
ftree="ftree_acc_sdme_uniform.root"
# runDSelector

## SDME input-output test now save the thrown 4-vectors
## Note: which 4-vector is being saved for AmpTools is set by commenting out the appropriate line in DSelector_phi.C
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_sdme1_sp17_20M_3463/trees/tree_ksmisskl__B3_M16_gen_amp/t*"
hist="hist_acc_sdme_test_thrown4vector.root"
tree="tree_acc_sdme_test_thrown4vector.root"
ftree="ftree_acc_sdme_test_thrown4vector.root"
# runDSelector

## SDME input-output test now save the thrown 4-vectors
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_sdme1_sp17_20M_3463/trees/tree_ksmisskl__B3_M16_gen_amp/t*"
hist="hist_acc_sdme_test_noAccidentals.root"
tree="tree_acc_sdme_test_noAccidentals.root"
ftree="ftree_acc_sdme_test_noAccidentals.root"
# runDSelector

## SDME input-output test now save the thrown 4-vectors
DSelector="DSelector_recon.C"
reaction_filter="ksmisskl__B3_M16_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_sp17_18M_3406/root/trees/t*"
hist="hist_acc_noAccidentals.root"
tree="tree_acc_noAccidentals.root"
ftree="ftree_acc_noAccidentals.root"
# runDSelector

## Spring 2020 reconstructed phi MC
DSelector="DSelector_phi.C"
reaction_filter="ksmisskl__B3_M16_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_sp20_40M_3469/root/trees/t*"
hist="hist_acc_sp20.root"
tree="tree_acc_sp20.root"
ftree="ftree_acc_sp20.root"
runDSelector

## Spring 2020 thrown phi MC
DSelector="DSelector_thrown.C"
reaction_filter="Thrown_Tree"
data="/d/grid17/gabyrod7/MC/kskl/gen_amp_kskl_phi_sp20_40M_3469/root/thrown/t*"
hist="hist_gen_sp20.root"
tree="tree_gen_sp20.root"
ftree="ftree_gen_sp20.root"
# runDSelector

# root -b -q -l apply_weight_to_acc_data.C

# hadd -f ftree_dat_gluex1.root ftree_dat_sp17.root ftree_dat_sp18.root ftree_dat_fa18.root
hadd -f ftree_acc_gluex1.root ftree_acc_sp17.root ftree_acc_sp18.root ftree_acc_fa18.root
# hadd -f ftree_gen_gluex1.root ftree_gen_sp17.root ftree_gen_sp18.root ftree_gen_fa18.root

rm -r 0.*
