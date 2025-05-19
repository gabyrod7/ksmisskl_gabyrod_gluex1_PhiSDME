#!/bin/bash

### Produce histograms to be analyzed with RDataFrames
root -l -b -q 'RDF_ana.C(16, "ftree_acc_sp17.root", "hist_acc.root", 0)'
root -l -b -q 'RDF_thrown.C(16, "ftree_gen_sp17.root", "hist_gen.root", 0)'
