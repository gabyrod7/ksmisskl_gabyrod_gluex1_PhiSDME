#!/bin/bash

### Produce histograms to be analyzed with RDataFrames
#root -l -b -q 'rdf_ana.C(20, "/d/grid15/gabyrod7/analysis/kskl/DSelector/mc/ftree_acc_flat.root", "hist.root", 0)'
#root -l -b -q 'rdf_ana.C(20, "/d/grid15/gabyrod7/analysis/kskl/DSelector/gluex/ftree_M16.root", "hist_sp17.root", 0)'
#root -l -b -q 'rdf_ana.C(20, "/d/grid15/gabyrod7/analysis/kskl/DSelector/s18/ftree.root", "hist_sp18.root", 0)'

root -l -b -q 'RDF_ana.C(20, "../DSelector/ftree_dat_sp17.root", "hist_dat.root", 0)'
#root -l -b -q 'RDF_ana.C(20, "../DSelector/ftree_dat_gluex1.root", "hist_dat.root", 0)'
root -l -b -q 'RDF_ana.C(20, "../DSelector/ftree_acc_gluex1.root", "hist_acc.root", 0)'
root -l -b -q 'RDF_ana.C(20, "../DSelector/ftree_acc_sdme1.root", "hist_acc_sdme.root", 0)'

