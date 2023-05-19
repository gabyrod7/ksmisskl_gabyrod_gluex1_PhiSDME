#!/bin/bash

root -l -b /volatile/halld/home/gabyrod/bggen/batch1/tree_ksmisskl__B3_M16/merged/tree_ksmisskl__B3_M16_030992.root << EOF
.x $ROOT_ANALYSIS_HOME/scripts/Load_DSelector.C
ksmisskl__B3_M16_Tree->Process("DSelector_kskl.C++");
EOF


