#!/usr/bin/env python3

import sys
import os
import math

def read_sdme_fit(fitfilename):
	par_name = []
	par_val = []
	par_err = []

	if not os.path.exists(fitfilename):
		return 0, par_val, par_err 

	with open(fitfilename, 'r') as f:
		for line in f: # skip lines until we reach the parameters section
			if(line == '+++ Parameter Values and Errors +++\n'):
				break

		line = f.readline()
		npar = int(line) # get number of parameters 

		# Now we read the production amplitudes and SDME parameters of the fit
		for nline, line in enumerate(f, start = 0):
			line = line.strip().split('\t')
			par_name.append(line[0])
			par_val.append(line[1])
			if nline == npar-1:
				break # done reading SDME parameter values

		# The errror is the sqrt of the diagonal of the covariance matrix
		# so we read the nth element of the nth line
		for nline, line in enumerate(f, start = 0):
			line = line.strip().split('\t')
			cov = float(line[nline])
			if cov < 0:
				cov = math.fabs(cov)
			par_err.append(math.sqrt(cov))
			if nline == npar-1:
				break # done reading SDME uncertainties 
			
	return npar, par_val, par_err


def main(argv):
	global VERBOSE # so can modify here
	
	if len(sys.argv) < 3:
		print('Usage: python3 readsdme.py fitname nbins')
		exit()
	
	
	fitname = sys.argv[1]      #name of the fit, eg phi_0 where the fit file is phi_0.fit
	nBins = int(sys.argv[2])      # number of bins
	
	par_vals = []
	par_errs = []
	tBins = {}
 
	#Read bin center and width from tBins.txt
	with open(fitname+'/tBins.txt', 'r') as f:
		for line in f:
			line = line.strip().split(',')
			tBins['bin_'+line[0]] = [line[1], line[2]]

	opf = open(f'sdme.csv','w')

	for ibin in range(0,nBins):
		bin_name = "bin_" + str(ibin)
		fitfilename = fitname + "/" + bin_name + "/nominal.fit"
		npar, par_vals, par_errs = read_sdme_fit(fitfilename)

		# line = ''
		line = f'{tBins[bin_name][0]},{tBins[bin_name][1]},'

		if npar == 0:
			line = '1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0\n'
			opf.write(line)
			print(f'Warning: bin number {ibin} did not converge. All SDMEs set to 1 and 0 error')
			continue

		for i in range(npar-9, npar): # Skip production amplitudes
			line += f'{par_vals[i]},{par_errs[i]},'
		opf.write(line[:-1]+'\n')

	print('SDMEs from nominal fit collected')

if __name__ == "__main__":
	main(sys.argv[1:])
