#!/bin/bash

nbins=9
nfits=20
nBootstraps=500
nprocess=1
low_t=0.15
high_t=1.0
fit_name=$nbins'bins_'$high_t't'
plotter_name='phi1020_plotter'
trees='/d/grid15/gabyrod7/analysis/ksmisskl_gabyrod_gluex1_PhiSDME/sdme/fits/sdme_dir/trees/'

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

setup_trees () { root -l -q -b setup_trees.C; }
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
draw_variation () { 
	python3 read_variation.py $fit_name $nbins
	root -l -b -q "drawsdme.C($nbins, $low_t, $high_t)"
	cp sdme.root sdme_variation.root
	cp sdme.pdf sdme_variation.pdf
	cp sdme.csv sdme_variation.csv
}
variation () { 
	python3 variation.py $fit_name $nbins $nprocess
	draw_variation
}

TEMP=`getopt -a -o n:dfrpt --long nthread:divide,fit,read,draw,run_plotter,plotter,bootstrap,read_bootstrap,all,variation,draw_variation,setupTrees -- "$@"`
eval set -- "$TEMP"

while true; do
	case "$1" in 
		-n | --nthread) nprocess=$2; shift 2;;
		-t | --setupTrees) setup_trees; shift;;
		-d | --divide) divide_data; shift;;
		-f | --fit) amptools_fit; shift;;
		--read) read_amptools_fit; shift;;
		-r | --draw) draw_amptools_fit; shift;;
		--run_plotter) run_plotter; shift;;
		-p | --plotter) root -l -b -q "plotter.C(\"$fit_name\", 3, 3)"; shift;;
		--bootstrap) bootstrap; shift;;
		--read_bootstrap) read_bootstrap; shift;;
		--all) setup_trees; divide_data; amptools_fit; draw_amptools_fit; run_plotter; shift;;
		--variation) variation; shift;;
		--draw_variation) draw_variation; shift;;
		--) shift; break;;
	esac
done