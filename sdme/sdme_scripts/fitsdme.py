import os
import sys
from multiprocessing import Pool
import amptools_cfg

fit_name = sys.argv[1]
nbins = int(sys.argv[2]) 
nfits = int(sys.argv[3])
nprocess = int(sys.argv[4])  
seed_file = 'param_init.cfg'
cfg_file_name = 'amptools.cfg'
data_dir = fit_name
base_directory = os.getcwd()

# setup config file settings
cfg_file = amptools_cfg.amptools_cfg()
cfg_file.set_data([runPeriod+'_'+polAngle for runPeriod in ['gluex1'] for polAngle in ['000', '045', '090', '135']])
# cfg_file.set_data([runPeriod+'_'+polAngle for runPeriod in ['sp17', 'sp18', 'fa18'] for polAngle in ['000', '045', '090', '135']])
cfg_file.set_particles('Beam Proton KShort KLong')
cfg_file.set_fname(cfg_file_name)
cfg_file.set_fit_name(fit_name)
cfg_file.set_amplitudes('sdme')
# cfg_file.set_bkgAmplitude('uniform')
#cfg_file.set_pol_info([[1.77, 0.38], [47.85, 0.38], [94.50, 0.38], [138.43, 0.38]])
# cfg_file.set_include_bkg(False)

def pwa_setup(nbins, base_directory):
	paths = []

	for i in range(nbins):
		path = base_directory+'/'+data_dir+'/bin_'+str(i)

		if not os.path.exists(f'{path}/fits_results/'):
			os.mkdir(path+"/fits_results/")

		if os.path.exists(f'{path}/nominal.fit'):
			print(f'removing {path}/nominal.fit')
			os.system(f'rm {path}/nominal.fit')

		if os.path.exists(path+'/fit.log'):
			print(f'removing {path}/fit.log')
			os.system(f'rm {path}/fit.log')

		if nfits > 1:
			cfg_file.set_parRange(True)

		os.chdir(path)
		if not os.path.exists(f'{path}/amptools.cfg'):
			cfg_file.set_ext(f'_{i}')
			cfg_file.write_amptools_config()

		paths.append(path)

	return paths

def run_fit(path):
	print(f'Move to directory {path}')
	os.chdir(path)

	cmd = f'fit -c amptools.cfg -s {seed_file} -r {nfits} > fit.log'
	print(cmd)
	os.system(cmd)

	print('done fitting in '+path)

	cmd = f'cp {fit_name}.fit nominal.fit'
	os.system(cmd)

	cmd = f'mv {fit_name}*.fit fits_results/'
	os.system(cmd)

if __name__ == '__main__':
	paths = pwa_setup(nbins, base_directory)

	if nprocess == 1:
		for path in paths:
			run_fit(path)
	else:
		p = Pool(nprocess)
		p.map(run_fit, paths)
