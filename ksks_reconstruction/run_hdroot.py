import os
import glob
import sys
from multiprocessing import Pool

new_dir = 'ksks_D2_pref_m1525_w086_r2017_01_2M'
mc_dir = 'gen_amp_ksks_D2_pref_m1525_w086_r2017_01_2M'

def run_over_rest_files(run_number):
	os.chdir('/d/grid15/gabyrod7/analysis/kskl/ksks_miss_recon/'+new_dir)

	if os.path.exists(run_number) == False:
		os.mkdir(run_number)
	os.chdir(run_number)

	fnames = glob.glob( '/d/grid17/gabyrod7/MC/ksks/%s/hddm/dana_rest_gen_amp_%s_???.hddm'%(mc_dir, run_number) )
	print(fnames)

	for fname in fnames:
		cmd = "hd_root --nthreads=1 -PPLUGINS=ReactionFilter -PReaction1=1_14__m10_16_14 -PReaction1:Flags=B4_M16 %s"%(fname)
		print(cmd)
		os.system(cmd)

		cmd = 'mv tree_ksmisskl__B4_M16.root ../tree_ksmisskl__B4_M16_%s_%s.root' % (run_number, str(fname[-8:-5]))
		print(cmd)
		os.system(cmd)
	
if __name__ == '__main__':
	processes=20 # number of process to spawn

	fnames = glob.glob('/d/grid17/gabyrod7/MC/ksks/'+mc_dir+'/hddm/dana_rest*.hddm')
	tmp = [(tree.split('/')[-1])[18:24] for tree in fnames]
	run_numbers = []
	[run_numbers.append(x) for x in tmp if x not in run_numbers]

	if os.path.exists(new_dir) == False:
		os.mkdir(new_dir)

	#for n in run_numbers:
	#	print(n)
	p=Pool(processes)
	p.map(run_over_rest_files, run_numbers)
	p.terminate()

	#print(run_numbers[0:40])

