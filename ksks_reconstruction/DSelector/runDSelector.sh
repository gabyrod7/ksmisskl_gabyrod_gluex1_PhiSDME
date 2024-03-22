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
}

nthreads=32

DSelector="DSelector_kskl.C"
reaction_filter="ksmisskl__B3_M16_Tree"
data="/d/grid15/gabyrod7/analysis/ksmisskl_gabyrod_gluex1_PhiSDME/ksks_reconstruction/trees/tree*"
hist="hist_acc_ksks_miss_recon.root"
tree=""
ftree="ftree_acc_ksks_miss_recon.root"
runDSelector

rm -r 0.*
