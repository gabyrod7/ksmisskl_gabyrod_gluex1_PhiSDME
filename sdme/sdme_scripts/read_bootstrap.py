#!/usr/bin/env python3

import sys
import os
import subprocess
import math
import numpy as np
import matplotlib.pyplot as plt

def read_sdme_fit(fitfilename):
	par_name = []
	par_val = []
	par_err = []

	with open(fitfilename, 'r') as f:
		for line in f: # skip lines until we reach the parameters section
			if(line == '+++ Parameter Values and Errors +++\n'):
				break

		line = f.readline()
		npar = int(line) # get number of parameters 

		# Now we read the parameters of the fit
		for nline, line in enumerate(f, start = 0):
			line = line.strip().split('\t')
			par_name.append(line[0])
			par_val.append(float(line[1]))
			if nline == npar-1:
				break # done reading SDME parameter values

		for nline, line in enumerate(f, start = 0):
			line = line.strip().split('\t')
			cov = float(line[nline])
			if cov < 0:
				cov = math.fabs(cov)
			par_err.append(math.sqrt(cov))
			if nline == npar-1:
				break # done reading SDME uncertainties 
			
	return par_val, par_err

def fit_status(fitfilename):
	with open(fitfilename, 'r') as f:
		for line in f: # skip lines until we reach the parameters section
			line = line.strip().split('\t')
			if(line[0] == 'lastMinuitCommandStatus'):
				if line[1] == '0':
					return 0
				else:
					return 1
	


def main(argv):
	global VERBOSE # so can modify here
	
	if len(sys.argv) != 4:
		print('Usage: python3 readsdme.py fitname nBins nBootstraps')
		exit()
	
	
	fitname = sys.argv[1]      #name of the fit, eg phi_0 where the fit file is phi_0.fit
	nBins = int(sys.argv[2])      # number of bins
	nBootstraps = int(sys.argv[3])      # number of bootstraps
	
	read_params = False

	par_names = []
	par_vals = []
	par_errs = []
	par_vals2 = []
	par_errs2 = []

	opf = open('bootstrap.csv','w')

	for iBin in range(0,nBins):
		bin_name = f"bin_{iBin}"

		rho000 = []
		rho100 = []
		rho1m10 = []
		rho111 = []
		rho001 = []
		rho101 = []
		rho1m11 = []
		rho102 = []
		rho1m12 = []

		x_rho000 = []
		x_rho100 = []
		x_rho1m10 = []
		x_rho111 = []
		x_rho001 = []
		x_rho101 = []
		x_rho1m11 = []
		x_rho102 = []
		x_rho1m12 = []
		y = []

		status = []

		par_vals2, par_errs2 = read_sdme_fit(f'{fitname}/{bin_name}/nominal.fit')

		count = 0
		for iBootstrap in range(nBootstraps):
			fitfilename = f'{fitname}/{bin_name}/bootstrap_{iBootstrap}.fit'
			par_vals, par_errs = read_sdme_fit(fitfilename)

			stat = fit_status(fitfilename)
			if stat == 1:
				count += 1
				#print(stat, iBin, iBootstrap)
			if iBootstrap == 500-1:
				print(f'Bin number : {iBin}	 Number of failed fits : {count}')

			rho000.append(float(par_vals[8]))
			rho100.append(float(par_vals[9]))
			rho1m10.append(float(par_vals[10]))
			rho111.append(float(par_vals[11]))
			rho001.append(float(par_vals[12]))
			rho101.append(float(par_vals[13]))
			rho1m11.append(float(par_vals[14]))
			rho102.append(float(par_vals[15]))
			rho1m12.append(float(par_vals[16]))

			if iBootstrap > 50 and iBootstrap % 10 == 0:
				x_rho000.append(np.std(rho000))
				x_rho100.append(np.std(rho100))
				x_rho1m10.append(np.std(rho1m10))
				x_rho111.append(np.std(rho111))
				x_rho001.append(np.std(rho001))
				x_rho101.append(np.std(rho101))
				x_rho1m11.append(np.std(rho1m11))
				x_rho102.append(np.std(rho102))
				x_rho1m12.append(np.std(rho1m12))
				y.append(iBootstrap)

		n = 15
		fig, axs = plt.subplots(3, 3, sharey=True, tight_layout=True)
		axs[0][0].hist(rho000, bins=n, label='bootstrap')
		axs[0][0].axvline(x = np.mean(rho000), color = 'r', label='bootstrap mean')
		axs[0][0].axvline(x = np.mean(rho000) - np.std(rho000), color = 'r', label='bootstrap mean', linestyle='dotted')
		axs[0][0].axvline(x = np.mean(rho000) + np.std(rho000), color = 'r', label='bootstrap mean', linestyle='dotted')
		axs[0][0].axvline(x = par_vals2[8], color = 'm', label='nominal mean')
		axs[0][0].axvspan(par_vals2[8] - par_errs2[8], par_vals2[8] + par_errs2[8], alpha=0.2, color='m', label='#mu #pm #sigma')
		#axs[0][0].legend()
		#axs[0][0].locator_params(axis='x', nbins=3)

		axs[0][1].hist(rho100, bins=n)
		axs[0][1].axvline(x = np.mean(rho100), color = 'r')
		axs[0][1].axvline(x = np.mean(rho100) - np.std(rho100), color = 'r', label='bootstrap mean', linestyle='dotted')
		axs[0][1].axvline(x = np.mean(rho100) + np.std(rho100), color = 'r', label='bootstrap mean', linestyle='dotted')
		axs[0][1].axvline(x = par_vals2[9], color = 'm', label='nominal mean')
		#axs[0][1].axvline(x = par_vals2[9], color = 'g')
		axs[0][1].axvspan(par_vals2[9] - par_errs2[9], par_vals2[9] + par_errs2[9], alpha=0.2, color='m')

		axs[0][2].hist(rho1m10, bins=n)
		axs[0][2].axvline(x = np.mean(rho1m10), color = 'r')
		axs[0][2].axvline(x = np.mean(rho1m10) - np.std(rho1m10), color = 'r', label='bootstrap mean', linestyle='dotted')
		axs[0][2].axvline(x = np.mean(rho1m10) + np.std(rho1m10), color = 'r', label='bootstrap mean', linestyle='dotted')
		axs[0][2].axvline(x = par_vals2[10], color = 'm', label='nominal mean')
		#axs[0][2].axvline(x = par_vals2[10], color = 'g')
		axs[0][2].axvspan(par_vals2[10] - par_errs2[10], par_vals2[10] + par_errs2[10], alpha=0.2, color='m')

		axs[1][0].hist(rho111, bins=n)
		axs[1][0].axvline(x = np.mean(rho111), color = 'r')
		axs[1][0].axvline(x = np.mean(rho111) - np.std(rho111), color = 'r', label='bootstrap mean', linestyle='dotted')
		axs[1][0].axvline(x = np.mean(rho111) + np.std(rho111), color = 'r', label='bootstrap mean', linestyle='dotted')
		axs[1][0].axvline(x = par_vals2[11], color = 'm', label='nominal mean')
		#axs[1][0].axvline(x = par_vals2[11], color = 'g')
		axs[1][0].axvspan(par_vals2[11] - par_errs2[11], par_vals2[11] + par_errs2[11], alpha=0.2, color='m')

		axs[1][1].hist(rho001, bins=n)
		axs[1][1].axvline(x = np.mean(rho001), color = 'r')
		axs[1][1].axvline(x = np.mean(rho001) - np.std(rho001), color = 'r', label='bootstrap mean', linestyle='dotted')
		axs[1][1].axvline(x = np.mean(rho001) + np.std(rho001), color = 'r', label='bootstrap mean', linestyle='dotted')
		axs[1][1].axvline(x = par_vals2[12], color = 'm', label='nominal mean')
		#axs[1][1].axvline(x = par_vals2[12], color = 'g')
		axs[1][1].axvspan(par_vals2[12] - par_errs2[12], par_vals2[12] + par_errs2[12], alpha=0.2, color='m')

		axs[1][2].hist(rho101, bins=n)
		axs[1][2].axvline(x = np.mean(rho101), color = 'r')
		axs[1][2].axvline(x = np.mean(rho101) - np.std(rho101), color = 'r', label='bootstrap mean', linestyle='dotted')
		axs[1][2].axvline(x = np.mean(rho101) + np.std(rho101), color = 'r', label='bootstrap mean', linestyle='dotted')
		axs[1][2].axvline(x = par_vals2[13], color = 'm', label='nominal mean')
		#axs[1][2].axvline(x = par_vals2[13], color = 'g')
		axs[1][2].axvspan(par_vals2[13] - par_errs2[13], par_vals2[13] + par_errs2[13], alpha=0.2, color='m')

		axs[2][0].hist(rho1m11, bins=n)
		axs[2][0].axvline(x = np.mean(rho1m11), color = 'r')
		axs[2][0].axvline(x = np.mean(rho1m11) - np.std(rho1m11), color = 'r', label='bootstrap mean', linestyle='dotted')
		axs[2][0].axvline(x = np.mean(rho1m11) + np.std(rho1m11), color = 'r', label='bootstrap mean', linestyle='dotted')
		axs[2][0].axvline(x = par_vals2[14], color = 'm', label='nominal mean')
		#axs[2][0].axvline(x = par_vals2[14], color = 'g')
		axs[2][0].axvspan(par_vals2[14] - par_errs2[14], par_vals2[14] + par_errs2[14], alpha=0.2, color='m')

		axs[2][1].hist(rho102, bins=n)
		axs[2][1].axvline(x = np.mean(rho102), color = 'r')
		axs[2][1].axvline(x = np.mean(rho102) - np.std(rho102), color = 'r', label='bootstrap mean', linestyle='dotted')
		axs[2][1].axvline(x = np.mean(rho102) + np.std(rho102), color = 'r', label='bootstrap mean', linestyle='dotted')
		axs[2][1].axvline(x = par_vals2[15], color = 'm', label='nominal mean')
		#axs[2][1].axvline(x = par_vals2[15], color = 'g')
		axs[2][1].axvspan(par_vals2[15] - par_errs2[15], par_vals2[15] + par_errs2[15], alpha=0.2, color='m')

		axs[2][2].hist(rho1m12, bins=n)
		axs[2][2].axvline(x = np.mean(rho1m12), color = 'r')
		axs[2][2].axvline(x = np.mean(rho1m12) - np.std(rho1m12), color = 'r', label='bootstrap mean', linestyle='dotted')
		axs[2][2].axvline(x = np.mean(rho1m12) + np.std(rho1m12), color = 'r', label='bootstrap mean', linestyle='dotted')
		axs[2][2].axvline(x = par_vals2[16], color = 'm', label='nominal mean')
		#axs[2][2].axvline(x = par_vals2[16], color = 'g')
		axs[2][2].axvspan(par_vals2[16] - par_errs2[16], par_vals2[16] + par_errs2[16], alpha=0.2, color='m')
		fig.savefig(f'tmp/sdme_bin{iBin}.png')

		fig2, axs2 = plt.subplots(3, 3, sharex=True, tight_layout=True)
		axs2[0][0].scatter(y ,x_rho000)
		axs2[0][0].axhline(y=par_errs2[8], color='red')
		axs2[0][0].set_ylabel('Standard deviation')
		axs2[0][1].scatter(y ,x_rho100)
		axs2[0][1].axhline(y=par_errs2[9], color='red')
		axs2[0][2].scatter(y ,x_rho1m10)
		axs2[0][2].axhline(y=par_errs2[10], color='red')
		axs2[1][0].scatter(y ,x_rho111)
		axs2[1][0].axhline(y=par_errs2[11], color='red')
		axs2[1][0].set_ylabel('Standard deviation')
		axs2[1][1].scatter(y ,x_rho001)
		axs2[1][1].axhline(y=par_errs2[12], color='red')
		axs2[1][2].scatter(y ,x_rho101)
		axs2[1][2].axhline(y=par_errs2[13], color='red')
		axs2[2][0].scatter(y ,x_rho1m11)
		axs2[2][0].axhline(y=par_errs2[14], color='red')
		axs2[2][0].set_xlabel('Number of bootstrap fits')
		axs2[2][0].set_ylabel('Standard deviation')
		axs2[2][1].scatter(y ,x_rho102)
		axs2[2][1].axhline(y=par_errs2[15], color='red')
		axs2[2][1].set_xlabel('Number of bootstrap fits')
		axs2[2][2].scatter(y ,x_rho1m12)
		axs2[2][2].axhline(y=par_errs2[16], color='red')
		axs2[2][2].set_xlabel('Number of bootstrap fits')
		fig2.savefig(f'tmp/std_bin{iBin}.png')
		
		#print(iBin, np.mean(rho1m11), np.std(rho1m11))
		line = f'{par_vals2[8]},{np.std(rho000)},{par_vals2[9]},{np.std(rho100)},{par_vals2[10]},{np.std(rho1m10)},{par_vals2[11]},{np.std(rho111)},{par_vals2[12]},{np.std(rho001)},{par_vals2[13]},{np.std(rho101)},{par_vals2[14]},{np.std(rho1m11)},{par_vals2[15]},{np.std(rho102)},{par_vals2[16]},{np.std(rho1m12)}\n'
		#line = f'{np.mean(rho000)},{np.std(rho000)},{np.mean(rho100)},{np.std(rho100)},{np.mean(rho1m10)},{np.std(rho1m10)},{np.mean(rho111)},{np.std(rho111)},{np.mean(rho001)},{np.std(rho001)},{np.mean(rho101)},{np.std(rho101)},{np.mean(rho1m11)},{np.std(rho1m11)},{np.mean(rho102)},{np.std(rho102)},{np.mean(rho1m12)},{np.std(rho1m12)}\n'
		opf.write(line)

if __name__ == "__main__":
	main(sys.argv[1:])
