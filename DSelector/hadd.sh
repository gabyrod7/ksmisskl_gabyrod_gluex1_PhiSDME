#!/bin/bash

hadd -f hists/hist_dat_gluex1.root hists/hist_dat_sp17.root hists/hist_dat_sp18.root hists/hist_dat_fa18.root 
hadd -f ftrees/ftree_dat_gluex1.root ftrees/ftree_dat_sp17.root ftrees/ftree_dat_sp18.root ftrees/ftree_dat_fa18.root

hadd -f ftrees/ftree_acc_gluex1.root ftrees/ftree_acc_sp17.root ftrees/ftree_acc_sp18.root ftrees/ftree_acc_fa18.root
hadd -f ftrees/ftree_gen_gluex1.root ftrees/ftree_gen_sp17.root ftrees/ftree_gen_sp18.root ftrees/ftree_gen_fa18.root
