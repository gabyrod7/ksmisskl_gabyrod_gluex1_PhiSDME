#!/bin/bash

# for a few runs
#python /d/grid13/gluex/gluex_top/hd_utilities/hd_utilities-1.37/psflux/plot_flux_ccdb.py --begin-run 30730 --end-run 30788 --num-bins 600 --energy-min 8.20 --energy-max 8.80 --rest-ver=3 --rcdb-query='@is_production and @status_approved'

# For all Spring 2017
python /d/grid13/gluex/gluex_top/hd_utilities/hd_utilities-1.37/psflux/plot_flux_ccdb.py --begin-run 30274 --end-run 31057 --num-bins 600 --energy-min 8.20 --energy-max 8.80 --rest-ver=3 --rcdb-query='@is_production and @status_approved'

# For all Spring 2018
python /d/grid13/gluex/gluex_top/hd_utilities/hd_utilities-1.37/psflux/plot_flux_ccdb.py --begin-run 40856 --end-run 42559 --num-bins 600 --energy-min 8.20 --energy-max 8.80 --rest-ver=2 --rcdb-query='@is_2018production and @status_approved'

# For all Fall 2018
python /d/grid13/gluex/gluex_top/hd_utilities/hd_utilities-1.37/psflux/plot_flux_ccdb.py --begin-run 50685 --end-run 51768 --num-bins 600 --energy-min 8.20 --energy-max 8.80 --rest-ver=2 --rcdb-query='@is_2018production and @status_approved and beam_on_current>49'

hadd flux_gluex1.root flux_30274_31057.root flux_40856_42559.root flux_50685_51768.root
