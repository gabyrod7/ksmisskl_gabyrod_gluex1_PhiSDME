# make soft links to flat trees that will be used for SDME fits

import os

data = ['dat', 'acc', 'gen']
runs = ['sp17', 'sp18', 'fa18', 'gluex1']

for dat in data:
	for run in runs:
		cmd = f'ln -s ../../DSelector/ftrees/ftree_{dat}_{run}.root ftree_{dat}_{run}.root'
		print(cmd)
		os.system(cmd)
