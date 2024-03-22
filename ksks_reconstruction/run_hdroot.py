'''
The reconstruction of KsKlp in our analysis has a missing Kl in the final state.
To study the reconstruction efficiency of KsKs, I take MC used to study KsKsp 
and reconstruct it as KsKlp by running hd_root with the appropriate KsKlp reaction filter.
'''

import os
import glob
from multiprocessing import Pool

new_dir = '/d/grid15/gabyrod7/analysis/ksmisskl_gabyrod_gluex1_PhiSDME/ksks_reconstruction/trees'
mc_dir = '/d/grid17/gabyrod7/MC/ksks/gen_amp_ksks_f_r2017_01_20M'

def run_over_rest_files(run_number):
	os.chdir(new_dir)

	if os.path.exists(run_number) == False:
		os.mkdir(run_number)
	os.chdir(run_number)

	fnames = glob.glob( mc_dir+'/hddm/dana_rest_gen_amp_'+run_number+'_???.hddm' )
	print(fnames)

	for fname in fnames:
		cmd = "hd_root --nthreads=1 -PPLUGINS=ReactionFilter -PReaction1=1_14__m10_16_14 -PReaction1:Flags=B3_M16 %s"%(fname)
		print(cmd)
		os.system(cmd)

		cmd = 'mv tree_ksmisskl__B3_M16.root ../tree_ksmisskl__B3_M16_%s_%s.root' % (run_number, str(fname[-8:-5]))
		print(cmd)
		os.system(cmd)
	
if __name__ == '__main__':
	processes=16 # number of process to spawn

	fnames = glob.glob(mc_dir+'/hddm/dana_rest*.hddm')
	tmp = [(tree.split('/')[-1])[18:24] for tree in fnames]
	run_numbers = []
	[run_numbers.append(x) for x in tmp if x not in run_numbers]

	if os.path.exists(new_dir) == False:
		os.mkdir(new_dir)

	# for run_number in run_numbers:
	# 	print(run_number)
	# 	run_over_rest_files(run_number)
	p=Pool(processes)
	p.map(run_over_rest_files, run_numbers)
	p.terminate()

	#print(run_numbers[0:40])

