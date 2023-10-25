import os
import sys
from multiprocessing import Pool
import random

fit_name = sys.argv[1]
nBins = int(sys.argv[2]) 
nBootstraps = int(sys.argv[3])
nprocess = int(sys.argv[4]) 
reaction_name = 'NAME_'
seed_file = 'param_init.cfg'
cfg_file_name = 'amptools.cfg'
data_dir = fit_name
base_directory = os.getcwd()

def bootstrap_setup(nBins, base_directory):
	paths = []

	for i in range(nBins):
		path = base_directory+'/'+data_dir+'/bin_'+str(i)

		# check that there is a nomianl.fit file, this is the best fit  
		if os.path.exists(path+'/nominal.fit'):
			print(f'nominal fit exists in {path}')
			paths.append(path)

			os.chdir(path)

			SDMEs = {}
			# get SDMEs from converged fit
			with open('nominal.fit', 'r') as f:
				for line in f: # skip lines until we reach the parameters section
					if(line == '+++ Parameter Values and Errors +++\n'):
						break
				line = f.readline() # skip number of parameters

				for line in f:
					arr = line.strip().split('\t')
					SDMEs[arr[0]] = arr[1]
					if arr[0] == 'rho1m12':
						break # rho1m12 is the last SDME, we have what we want from this file

			with open('amptools.cfg', 'r') as nominal:
				with open('bootstrap.cfg', 'w') as bootstrap:
					for line in nominal:
						if line[0:4] == 'data':
							line = line.replace('ROOTDataReader', 'ROOTDataReaderBootstrap')
							line = line.replace('\n', ' XXXX \n')
						elif line[0:9] == 'parameter':
							arr = line.strip().split(' ')
							line = f'parameter {arr[1]} {SDMEs[arr[1]]} \n'
						elif line[0:10] == 'initialize':
							arr = line.strip().split(' ')
							amp_real = arr[1]+"_re"
							amp_imag = arr[1]+"_im"
							line = f'initialize {arr[1]} {arr[2]} {SDMEs[amp_real]} {SDMEs[amp_imag]} real \n'
						bootstrap.write(line)
						
			for j in range(nBootstraps):
				cmd = f'cp bootstrap.cfg bootstrap_{j}.cfg'
				os.system(cmd)

				cmd = f'sed -i s/fit\ {fit_name}/fit\ bootstrap_{j}/g bootstrap_{j}.cfg'
				os.system(cmd)

				cmd = f'sed -i s/XXXX/{random.randint(1, 10000)}/g bootstrap_{j}.cfg'
				os.system(cmd)

	return paths

def run_fit(path):
	print('Move to directory '+path)
	os.chdir(path)

	print(f'Perform {nBootstraps} bootstraps in {path}')
	for i in range(nBootstraps):
		cmd = f'fit -c bootstrap_{i}.cfg > bootstrap_{i}.log'
		os.system(cmd)

		if i%10 == 0:
			print(f'{i} of {nBootstraps} fits complete in directory {path}')
	print(f'Bootstap complete in {path}')

if __name__ == '__main__':
	paths = bootstrap_setup(nBins, base_directory)

	if nprocess == 1:
		for path in paths:
			run_fit(path)
	else:
		p = Pool(nprocess)
		p.map(run_fit, paths)
