#!/bin/bash

nthreads=4

DSelector="DSelector_kskl.C"
reaction_filter="ksmisskl__B3_M16_Tree"
#data="/volatile/halld/home/gabyrod/bggen/tree_ksmisskl__B3_M16/merged/tree_ksmisskl__B3_M16_03099*"
data="/volatile/halld/home/gabyrod/bggen/tree_ksmisskl__B3_M16/merged/tree*"
hist="hist_bggen.root"
tree="tree_bggen_sp17.root"
ftree=""
#runDSelector

root  -l -b << EOF
TTree::SetMaxTreeSize(2000000000000LL); // 2TB
//gEnv->SetValue("ProofLite.Sandbox", "tmp");
.x $ROOT_ANALYSIS_HOME/scripts/Load_DSelector.C
TChain *chain = new TChain("$reaction_filter");

//chain->Add("tree_bggen_sp17.root");

//chain->Add("/volatile/halld/home/gabyrod/bggen/batch1/tree_ksmisskl__B3_M16/merged/tree_ksmisskl__B3_M16_03099*");

chain->Add("/volatile/halld/home/gabyrod/bggen/batch1/tree_ksmisskl__B3_M16/merged/tree*");
chain->Add("/volatile/halld/home/gabyrod/bggen/batch2/tree_ksmisskl__B3_M16/merged/tree*");
chain->Add("/volatile/halld/home/gabyrod/bggen/batch3/tree_ksmisskl__B3_M16/merged/tree*");
chain->Add("/volatile/halld/home/gabyrod/bggen/batch4/tree_ksmisskl__B3_M16/merged/tree*");
DPROOFLiteManager::Process_Chain(chain,"$DSelector++", $nthreads, "$hist", "$tree"); 
EOF

#hist="hist_bggen_2.root"
#root  -l -b << EOF
#TTree::SetMaxTreeSize(2000000000000LL); // 2TB
#//gEnv->SetValue("ProofLite.Sandbox", "tmp");
#.x $ROOT_ANALYSIS_HOME/scripts/Load_DSelector.C
#TChain *chain = new TChain("$reaction_filter");
#chain->Add("tree_bggen_sp17.root");
#DPROOFLiteManager::Process_Chain(chain,"$DSelector++", $nthreads, "$hist", "$tree"); 
#EOF

#mv ftree.root $ftree
rm -r 0.*

#function runDSelector() {
#
#root  -l -b << EOF
#TTree::SetMaxTreeSize(2000000000000LL); // 2TB
#//gEnv->SetValue("ProofLite.Sandbox", "tmp");
#.x $ROOT_ANALYSIS_HOME/scripts/Load_DSelector.C
#TChain *chain = new TChain("$reaction_filter");
#chain->Add("$data");
#DPROOFLiteManager::Process_Chain(chain,"$DSelector++", $nthreads, "$hist", "$tree"); 
#EOF
#}
#
#rm DSelector_kskl_C_ACLiC_dict_rdict.pcm DSelector_kskl_C.d DSelector_kskl_C.so
#
#DSelector="DSelector_kskl.C"
#reaction_filter="ksmisskl__B3_M16_Tree"
#ftree=""
#
#data="/volatile/halld/home/gabyrod/bggen/batch1/tree_ksmisskl__B3_M16/merged/tree_ksmisskl__B3_M16_03099*"
#hist="hist_bggen4.root"
#tree="tree_bggen_sp17_3.root"
#runDSelector
#
#rm DSelector_kskl_C_ACLiC_dict01b9c41b9c_dictUmbrella.h DSelector_kskl_C_ACLiC_dict6a43fd920c_dictContent.h DSelector_kskl_C_ACLiC_dict_rdict.pcm DSelector_kskl_C.d DSelector_kskl_C.so
#
#data="tree_bggen_sp17_3.root"
#hist="hist_bggen5.root"
#tree="tree_bggen_sp17_4.root"
#runDSelector
#
#rm -r 0.*

