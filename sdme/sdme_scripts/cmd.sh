#!/bin/bash

nbins=9
nfits=20
nBootstraps=500
nprocess=1
low_t=0.15
high_t=1.0
fit_name=$nbins'bins_'$high_t't'
plotter_name='phi1020_plotter'
trees='/d/grid15/gabyrod7/analysis/ksmisskl_gabyrod_gluex1_PhiSDME/sdme/trees/sdme_dir/'

# Check if we are on a GPU node at FSU
if [ "$(hostname)" = 'scigrid52.local' ]
then
	export BUILD_SCRIPTS=/group/halld/Software/build_scripts
	source $BUILD_SCRIPTS/gluex_env_boot_jlab.sh
	gxenv /d/home/sdobbs/grid13/src/apptainer-gpumpi/version.xml

	export CUDA_INSTALL_PATH=/usr/local/cuda-12.2
else
	source /d/home/gabyrod7/gluex_top/gluex_env_boot_gabriel.sh
	gxenv /d/home/gabyrod7/gluex_top/version.xml

	nprocess=$nbins
fi

divide_data () { ./divideData.pl $fit_name $nbins $low_t $high_t $trees; }
amptools_fit () { python3 fitsdme.py $fit_name $nbins $nfits $nprocess; }
read_bootstrap () { 
	source /d/home/gabyrod7/python/python-3.6.8/bin/activate
	python3 read_bootstrap.py $fit_name $nbins $nBootstraps
}
bootstrap () {
	source /d/home/gabyrod7/python/python-3.6.8/bin/activate
	python bootstrap.py $fit_name $nbins $nBootstraps $nprocess
	read_bootstrap
}
read_amptools_fit () { python3 read_nominal.py $fit_name $nbins
}
draw_amptools_fit() {
	read_amptools_fit
	root -l -b -q "drawsdme.C($nbins, $low_t, $high_t)"
	mv sdme.csv $fit_name'.csv'
	mv sdmee.png $fit_name'.png'
	cp sdme.root $fit_name'.root'
}
run_plotter () {
	python3 plotter.py $fit_name $nbins $plotter_name
	root -l -b -q "plotter.C(\"$fit_name\", 3, 3)"
}

TEMP=`getopt -a -o n:dfrp --long nthread:divide,fit,read,draw,run_plotter,plotter,bootstrap,read_bootstrap,all -- "$@"`
eval set -- "$TEMP"

while true; do
	case "$1" in 
		-n | --nthread) nprocess=$2; shift 2;;
		-d | --divide) divide_data; shift;;
		-f | --fit) amptools_fit; shift;;
		--read) read_amptools_fit; shift;;
		-r | --draw) draw_amptools_fit; shift;;
		--run_plotter) run_plotter; shift;;
		-p | --plotter) root -l -b -q "plotter.C(\"$fit_name\", 3, 3)"; shift;;
		--bootstrap) bootstrap; shift;;
		--read_bootstrap) read_bootstrap; shift;;
		--all) divide_data; amptools_fit; draw_amptools_fit; run_plotter; shift;;
		--) shift; break;;
	esac
done