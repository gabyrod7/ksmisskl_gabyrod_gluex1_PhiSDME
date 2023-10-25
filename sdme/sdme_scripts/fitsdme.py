import os
import sys
from multiprocessing import Pool
import amptools_cfg

fit_name = sys.argv[1]
nbins = int(sys.argv[2]) 
nfits = int(sys.argv[3])
nprocess = int(sys.argv[4])  
# reaction_name = 'NAME_'
seed_file = 'param_init.cfg'
cfg_file_name = 'amptools.cfg'
data_dir = fit_name
#keep_log = True
base_directory = os.getcwd()

# setup config file settings
cfg_file = amptools_cfg.amptools_cfg()
cfg_file.set_data([runPeriod+'_'+polAngle for runPeriod in ['gluex1'] for polAngle in ['000', '045', '090', '135']])
#cfg_file.set_data([runPeriod+'_'+polAngle for runPeriod in ['sp17', 'sp18', 'fa18'] for polAngle in ['000', '045', '090', '135']])
cfg_file.set_particles('Beam Proton KShort KLong')
cfg_file.set_fname(cfg_file_name)
cfg_file.set_fit_name(fit_name)
cfg_file.set_amplitudes('sdme')
# cfg_file.set_reaction_name(reaction_name)
#cfg_file.set_pol_info([[45, 0.35]])
# cfg_file.set_pol_info([[1.77, 0.35], [47.85, 0.35], [94.50, 0.35], [138.43, 0.35]])
#cfg_file.set_pol_info([[1.77, 0.38], [47.85, 0.38], [94.50, 0.38], [138.43, 0.38]])

def pwa_setup(nbins, base_directory):
	paths = []

	for i in range(nbins):
		path = base_directory+'/'+data_dir+'/bin_'+str(i)

		# check if config file already exists
		# if os.path.exists(path+'/amptools.cfg'):
		# 	print('config file already exists in {} already exists'.format(path))
		# 	paths.append(path)
			# continue

		if os.path.exists(path+'/nominal.fit'):
			print('removing {}/nominal.fit'.format(path))
			os.system('rm '+path+'/nominal.fit')

		if os.path.exists(path+'/fit.log'):
			print('removing {}/fit.log'.format(path))
			os.system('rm '+path+'/fit.log')

		if nfits > 1:
			cfg_file.set_parRange(True)

		os.chdir(path)
		if not os.path.exists(path+'/amptools.cfg'):
			cfg_file.set_ext('_'+str(i))
			cfg_file.write_amptools_config()

		paths.append(path)

	return paths

def run_fit(path):
#	path = '{}/bin_{}/'.format(fit_name, bins)
	print('Move to directory '+path)
	os.chdir(path)

	cmd = 'fit -c amptools.cfg -s {} -r {} > fit.log'.format(seed_file, nfits)
	print(cmd)
	os.system(cmd)

	print('done fitting in '+path)

	# get the fit name so that we can set the fit result to nominal.fit
	# fit_name = ''
	# with open('amptools.cfg', 'r') as f:
	# 	fit_name = f.readline().split()[1]
	cmd = 'cp {}.fit nominal.fit'.format(fit_name)
	os.system(cmd)

if __name__ == '__main__':
	paths = pwa_setup(nbins, base_directory)

	if nprocess == 1:
		for path in paths:
			run_fit(path)
	else:
		p = Pool(nprocess)
		p.map(run_fit, paths)
