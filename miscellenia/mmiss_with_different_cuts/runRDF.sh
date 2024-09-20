#!/bin/bash

### Produce histograms to be analyzed with RDataFrames
root -l -b -q 'RDF_ana.C(16, "/d/grid15/gabyrod7/analysis/ksmisskl_gabyrod_gluex1_PhiSDME/DSelector/ftrees/ftree_dat_gluex1.root", "hist_dat_gluex1.root", 0)'
root -l -b -q 'RDF_ana.C(16, "/d/grid15/gabyrod7/analysis/ksmisskl_gabyrod_gluex1_PhiSDME/DSelector/ftrees/ftree_acc_gluex1.root", "hist_acc_gluex1.root", 0)'
# root -l -b -q 'RDF_thrown.C(16, "../DSelector/ftrees/ftree_gen_gluex1.root", "hist_gen_gluex1.root", 0)'

# root -l -b -q 'RDF_ana.C(16, "../DSelector/ftrees/ftree_dat_sp20.root", "hist_dat_sp20.root", 0)'
# root -l -b -q 'RDF_ana.C(16, "../DSelector/ftrees/ftree_acc_sp20.root", "hist_acc_sp20.root", 0)'

# root -l -b -q 'RDF_ana.C(16, "../DSelector/ftrees/ftree_dat_sp17.root", "hist_dat_sp17.root", 0)'
# root -l -b -q 'RDF_ana.C(16, "../DSelector/ftrees/ftree_dat_sp18.root", "hist_dat_sp18.root", 0)'
# root -l -b -q 'RDF_ana.C(16, "../DSelector/ftrees/ftree_dat_fa18.root", "hist_dat_fa18.root", 0)'
