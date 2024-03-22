#!/bin/bash

# root -l -b -q 'RDF_miss_recon.C(20, "/d/grid15/gabyrod7/analysis/kskl/DSelector/ksks_miss_recon/ftree_ksks_miss_recon_fp2.root", "hist_ksks_miss_recon_fp2.root", 0)'
# root -l -b -q 'RDF_miss_recon.C(20, "DSelector/ftree_acc_ksks_miss_recon.root", "hist_ksks_miss_recon.root", 0)'
root -l -b -q 'RDF_kskl.C(20, "../DSelector/ftrees/ftree_acc_sp17.root", "hist_kskl.root", 0)'
