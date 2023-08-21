#!/bin/bash

source /d/home/gabyrod7/gluex_top/gluex_env_boot_gabriel.sh
gxenv /d/home/gabyrod7/gluex_top/version.xml

name=$(basename "$PWD")
nbins=9
nfits=10
nBootstraps=500
nprocess=$nbins
low_t=0.15
high_t=1.50
fit_name=$nbins'bins_'$high_t't'
plotter_name='phi1020_plotter'
trees='/d/grid15/gabyrod7/analysis/ksmisskl_gabyrod_gluex1_PhiSDME/sdme/trees/sdme_dir/'

divide_data () { ./divideData.pl $fit_name $nbins $low_t $high_t $trees; }
amptools_fit () { python3 fitsdme.py $fit_name $nbins $nfits; }
bootstrap () {
	source /d/home/gabyrod7/python/python-3.6.8/bin/activate
	python bootstrap.py $fit_name $nbins $nBootstraps
	python read_bootstrap.py $fit_name $nbins $nBootstraps
}
read_amptools_fit () { python3 read_nominal.py $fit_name $nbins; }
draw_amptools_fit() {
	root -l -b -q "drawsdme.C($nbins, $low_t, $high_t)"
	mv sdme.csv $fit_name'.csv'
	mv sdmee.png $fit_name'.png'
	cp sdme.root $fit_name'.root'
}
run_plotter () {
	python3 plotter.py $fit_name $nbins $plotter_name
	root -l -b -q "plotter.C(\"$fit_name\", 3, 3)"
}

for i in $@
do 
	if [[ "$i" == "-screen" ]]
	then
		if [ -f "analysis.log" ]; then
			rm 'analysis.log'
		fi

		screen -dmS $name bash -c './cmd.sh -all > analysis.log'
	fi

	if [[ "$i" == "-divide" ]]
	then
		divide_data
	fi

	if [[ "$i" == "-fit" ]]
	then
		amptools_fit
	fi

	if [[ "$i" == "-bootstrap" ]]
	then
		bootstrap
	fi

	if [[ "$i" == "-read" ]]
	then
		read_amptools_fit
	fi

	if [[ "$i" == "-draw" ]]
	then
		draw_amptools_fit
	fi

	if [[ "$i" == "-plotter" ]]
	then
		root -l -b -q "plotter.C(\"$fit_name\", 3, 3)"
	fi
	if [[ "$i" == "-run_plotter" ]]
	then
		run_plotter
	fi
	if [[ "$i" == "-all" ]]
	then
		divide_data
		amptools_fit
		read_amptools_fit
		draw_amptools_fit
		run_plotter

#		bootstrap
	fi
done
