The make_soft_links.py script will make soft links to the flat trees necesary for the SDME measuremnt.

The split.C script creates a directory and splits the data by polarization angle and with the appropriate cuts.
The idea is that we prepare all files that will be used in the SDME fits here.
Each variation of a SDME fit will have its own directory with a (hopefully) appropriate name.

The plot.C scripts will create histograms of the data in the subdirectories.
This script is meant to be copied into the directory and has to be done by hand.
It is meant to check the data in cases where one want to double check the data
in the subdiratories.

