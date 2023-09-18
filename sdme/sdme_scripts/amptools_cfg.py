import os
import random

class amptools_cfg:
	def __init__(self):
		self.data = []
		self.wave_set = ''
		self.fname = 'amptools.cfg'
		self.particles = 'particle1 particle2 particle3 particle4'
		self.fit_name = 'fit_name'
		self.ROOTDataReader = 'ROOTDataReader'
		self.reaction_name = 'REACTION'
		self.ext = ''
		self.include_bkg = True
		self.parRange = False
		self.polarization = 'hist'
		self.pol_hist_location = '/d/grid15/gabyrod7/analysis/ksmisskl_gabyrod_gluex1_PhiSDME/polarization_fraction/'
		self.costum_polInfo = 'polInfo.cfg'
		self.amplitudes = ''

	def set_data(self, data):
		self.data = data
	
	def set_particles(self, particles):
		self.particles = particles

	def set_ROOTDataReader(self, reader):
		self.ROOTDataReader = reader

	def set_fit_name(self, name):
		self.fit_name = name

	def set_reaction_name(self, name):
		self.reaction_name = name

	def set_wave_set(self, wave_set):
		self.wave_set = wave_set
	# 	self.fname = wave_set+'.cfg'

	def set_fname(self, fname):
		self.fname = fname

	def set_ext(self, ext):
		self.ext = ext

	def set_include_bkg(self, include_bkg):
		self.include_bkg = include_bkg

	def set_parRange(self, parRange):
		self.parRange = parRange
  
	def set_polarization(self, polarization):
		self.polarization = polarization
  
	def set_pol_hist_location(self, pol_hist_location):
		self.pol_hist_location = pol_hist_location
  
	def set_costum_polInfo(self, costum_polInfo):
		self.costum_polInfo = costum_polInfo

	def set_amplitudes(self, amplitudes):
		self.amplitudes = amplitudes

	# Write the polarization information to the config file for the case of fixed average polarization
	def write_pol_average(self, f):
		polAngle = {'sp17_000' : 1.8, 'sp17_045' : 47.9, 'sp17_090' : 94.5, 'sp17_135' : -41.6, 
	      			'sp18_000' : 4.1, 'sp18_045' : 48.5, 'sp18_090' : 94.2, 'sp18_135' : -42.4, 
					'fa18_000' : 3.3, 'fa18_045' : 48.3, 'fa18_090' : 92.9, 'fa18_135' : -42.1,
					'gluex1_000' : 3.4, 'gluex1_045' : 48.3, 'gluex1_090' : 93.8, 'gluex1_135' : -42.2}
		
		polFrac	 = {'sp17_000' : 0.3537, 'sp17_045' : 0.3484, 'sp17_090' : 0.3472, 'sp17_135' : 0.3512, 
	      			'sp18_000' : 0.3420, 'sp18_045' : 0.3474, 'sp18_090' : 0.3478, 'sp18_135' : 0.3517, 
					'fa18_000' : 0.3563, 'fa18_045' : 0.3403, 'fa18_090' : 0.3430, 'fa18_135' : 0.3523,
					'gluex1_000' : 0.3486, 'gluex1_045' : 0.3452, 'gluex1_090' : 0.3461, 'gluex1_135' : 0.3518}

		for dat in self.data:
			f.write('define pol_{0} {1:.1f} {2:.4f}\n'.format(dat, polAngle[dat], polFrac[dat]))
		f.write('\n')

	# Write the polarization information to the config file for the case of polarization histograms
	def write_pol_hist(self, f):
		polAngle = {'sp17_000' : 1.8, 'sp17_045' : 47.9, 'sp17_090' : 94.5, 'sp17_135' : -41.6, 
	      			'sp18_000' : 4.1, 'sp18_045' : 48.5, 'sp18_090' : 94.2, 'sp18_135' : -42.4, 
					'fa18_000' : 3.3, 'fa18_045' : 48.3, 'fa18_090' : 92.9, 'fa18_135' : -42.1,
     				'gluex1_000' : 3.3, 'gluex1_045' : 48.3, 'gluex1_090' : 92.9, 'gluex1_135' : -42.1}

		polFrac  = {'sp17_000' : self.pol_hist_location+'sp17TPol.root hPol0', 'sp17_045' : self.pol_hist_location+'sp17TPol.root hPol45', 
	     			'sp17_090' : self.pol_hist_location+'sp17TPol.root hPol90', 'sp17_135' : self.pol_hist_location+'sp17TPol.root hPol135',

	     			'sp18_000' : self.pol_hist_location+'sp18TPol75.root hPol0', 'sp18_045' : self.pol_hist_location+'sp18TPol75.root hPol45', 
					'sp18_090' : self.pol_hist_location+'sp18TPol75.root hPol90', 'sp18_135' : self.pol_hist_location+'sp18TPol75.root hPol135',
					
					'fa18_000' : self.pol_hist_location+'fa18TPol.root hPol0', 'fa18_045' : self.pol_hist_location+'fa18TPol.root hPol45',
					'fa18_090' : self.pol_hist_location+'fa18TPol.root hPol90', 'fa18_135' : self.pol_hist_location+'fa18TPol.root hPol135',

	     			'gluex1_000' : self.pol_hist_location+'gluex1Tpol.root hPol0', 'gluex1_045' : self.pol_hist_location+'gluex1Tpol.root hPol45', 
					'gluex1_090' : self.pol_hist_location+'gluex1Tpol.root hPol90', 'gluex1_135' : self.pol_hist_location+'gluex1Tpol.root hPol135'}

		for dat in self.data:
			f.write('define pol_{0} {1:.1f} {2}\n'.format(dat, polAngle[dat], polFrac[dat]))
		f.write('\n')

	# Write the polarization information to the config file for the case of custom polarization information
	# The information is read from the file polInfo.cfg by default but may be changed by the user
	# The contents in the polInfo.cfg file will be written to the config file as is
	def write_pol_custom(self, f):
		f.write('# Custom polarization information \n')
		with open(self.costum_polInfo, 'r') as polInfo:
			for line in polInfo:
				f.write(line)
		f.write('\n')

	def write_twopsZlm(self, f):
		# The convention for the wave names is as follows:
		# Wave, orbital angular momentum (note so keep all strings the same length we 0+ rather than just 0), reflectivity (p/m = +/-)
		# Example: Sp0+ = S-wave, 0 orbital angular momentum, positive reflectivity
		wave_dictionary = { 'Sp0+' : ['Pos', 'Sp0+', 0, 0, True],
                            'Sp0-' : ['Neg', 'Sp0-', 0, 0, True],

                            'Pm1+': ['Pos', 'Pm1+', 1, -1, False],
                            'Pm1-': ['Neg', 'Pm1-', 1, -1, False],
                            'Pp0+': ['Pos', 'Pp0+', 1, 0, False],
                            'Pp0-': ['Neg', 'Pp0-', 1, 0, False],
                            'Pp1+': ['Pos', 'Pp1+', 1, 1, False],
                            'Pp1-': ['Neg', 'Pp1-', 1, 1, False],

                            'Dm2+': ['Pos', 'Dm2+', 2, -2, False],
                            'Dm2-': ['Neg', 'Dm2-', 2, -2, False],
                            'Dm1+': ['Pos', 'Dm1+', 2, -1, False],
                            'Dm1-': ['Neg', 'Dm1-', 2, -1, False],
                            'Dp0+': ['Pos', 'Dp0+', 2, 0, False],
                            'Dp0-': ['Neg', 'Dp0-', 2, 0, False],
                            'Dp1+': ['Pos', 'Dp1+', 2, 1, False],
                            'Dp1-': ['Neg', 'Dp1-', 2, 1, False],
                            'Dp2+': ['Pos', 'Dp2+', 2, 2, False],
                            'Dp2-': ['Neg', 'Dp2-', 2, 2, False],

                            'Fm3+': ['Pos', 'Fm3+', 3, -3, False],
                            'Fm3-': ['Neg', 'Fm3-', 3, -3, False],
                            'Fm2+': ['Pos', 'Fm2+', 3, -2, False],
                            'Fm2-': ['Neg', 'Fm2-', 3, -2, False],
                            'Fm1+': ['Pos', 'Fm1+', 3, -1, False],
                            'Fm1-': ['Neg', 'Fm1-', 3, -1, False],
                            'Fp0+': ['Pos', 'Fp0+', 3, 0, False],
                            'Fp0-': ['Neg', 'Fp0-', 3, 0, False],
                            'Fp1+': ['Pos', 'Fp1+', 3, 1, False],
                            'Fp1-': ['Neg', 'Fp1-', 3, 1, False],
                            'Fp2+': ['Pos', 'Fp2+', 3, 2, False],
                            'Fp2-': ['Neg', 'Fp2-', 3, 2, False],
                            'Fp3+': ['Pos', 'Fp3+', 3, 3, False],
                            'Fp3-': ['Neg', 'Fp3-', 3, 3, False] }
                           
		f.write('# Create sums\n')
		for dat in self.data:
			'''
			Posititve reflectivity amplitudes go in the PosRe and PosIm sums
			Negative reflectivity amplitudes go in the NegRe and NegIm sums
			'''
			if '+' in  self.wave_set:
				f.write('sum {0}_{1} PosRe\n'.format(self.reaction_name, dat))
				f.write('sum {0}_{1} PosIm\n'.format(self.reaction_name, dat))
			if '-' in  self.wave_set:
				f.write('sum {0}_{1} NegRe\n'.format(self.reaction_name, dat))
				f.write('sum {0}_{1} NegIm\n'.format(self.reaction_name, dat))
			f.write('\n')

		if len(self.data) > 1:
			for dat in self.data:
				if dat == self.data[0]:
					f.write('parameter par_scale_{0} 1.0 fixed \n'.format(dat))
					continue
				f.write('parameter par_scale_{0} 1.0 \n'.format(dat))
			f.write('\n')

		waves = self.wave_set.split('_')
		for wave in waves:
			for dat in self.data:
				f.write('# Amplitude for wave {0} and polarization angle {1} \n'.format(wave, dat))
				if wave[-1] == '+':
					f.write('amplitude {0}_{1}::PosRe::{2} Zlm {3} {4} +1 +1 pol_{1}\n'.format(self.reaction_name, dat, wave, wave_dictionary[wave][2], wave_dictionary[wave][3]))
					f.write('amplitude {0}_{1}::PosIm::{2} Zlm {3} {4} -1 -1 pol_{1}\n'.format(self.reaction_name, dat, wave, wave_dictionary[wave][2], wave_dictionary[wave][3]))

					if wave_dictionary[wave][4]:
						f.write('initialize {0}_{1}::PosRe::{2} cartesian {3} 0.0 real\n'.format(self.reaction_name, dat, wave, random.uniform(0, 100)))
					else:
						f.write('initialize {0}_{1}::PosRe::{2} cartesian {3} {4} \n'.format(self.reaction_name, dat, wave, random.uniform(-100, 100), random.uniform(-100, 100)))

					f.write('constrain {0}_{1}::PosRe::{2} {0}_{1}::PosIm::{2}\n'.format(self.reaction_name, dat, wave))
					
				if wave[-1] == '-':
					f.write('amplitude {0}_{1}::NegRe::{2} Zlm {3} {4} +1 -1 pol_{1}\n'.format(self.reaction_name, dat, wave, wave_dictionary[wave][2], wave_dictionary[wave][3]))
					f.write('amplitude {0}_{1}::NegIm::{2} Zlm {3} {4} -1 +1 pol_{1}\n'.format(self.reaction_name, dat, wave, wave_dictionary[wave][2], wave_dictionary[wave][3]))

					if wave_dictionary[wave][4]:
						f.write('initialize {0}_{1}::NegRe::{2} cartesian {3} 0.0 real\n'.format(self.reaction_name, dat, wave, random.uniform(0, 100)))
					else:
						f.write('initialize {0}_{1}::NegIm::{2} cartesian {3} {4} \n'.format(self.reaction_name, dat, wave, random.uniform(-100, 100), random.uniform(-100, 100)))

					f.write('constrain {0}_{1}::NegRe::{2} {0}_{1}::NegIm::{2} \n'.format(self.reaction_name, dat, wave))
				f.write('\n')

			if len(self.data) > 1:
				f.write('# Constrain parameters across datasets \n')
				for dat in self.data:
					if dat == self.data[0]:
						if wave[-1] == '+':
							f.write('scale {0}_{1}::PosRe::{2} [par_scale_{1}] \n'.format(self.reaction_name, dat, wave))
						if wave [-1] == '-' :
							f.write('scale {0}_{1}::NegRe::{2} [par_scale_{1}] \n'.format(self.reaction_name, dat, wave))
						continue
					if wave[-1] == '+':
						f.write('constrain {0}_{1}::PosRe::{3} {0}_{2}::PosRe::{3} \n'.format(self.reaction_name, self.data[0], dat, wave))
						f.write('scale {0}_{1}::PosRe::{2} [par_scale_{1}] \n'.format(self.reaction_name, dat, wave))
					if wave[-1] == '-':
						f.write('constrain {0}_{1}::NegRe::{3} {0}_{2}::NegRe::{3} \n'.format(self.reaction_name, self.data[0], dat, wave))
						f.write('scale {0}_{1}::NegRe::{2} [par_scale_{1}] \n'.format(self.reaction_name, dat, wave))
			f.write('\n')

	def write_sdme(self, f):
		f.write('# Create sums\n')
		for dat in self.data:
			f.write('sum {0}_{1} sum_{1}\n'.format(self.reaction_name, dat))
		f.write('\n')

		f.write('parameter rho000  0.01\n')
		f.write('parameter rho100  0.01\n')
		f.write('parameter rho1m10 0.01\n')
		f.write('parameter rho111  0.01\n')
		f.write('parameter rho001  0.01\n')
		f.write('parameter rho101  0.01\n')
		f.write('parameter rho1m11 0.5\n')
		f.write('parameter rho102  -0.01\n')
		f.write('parameter rho1m12 -0.5\n\n')

		if self.parRange:
			f.write('keyword parRange 3 3\n')
			f.write('parRange rho000  -0.01 0.01\n')
			f.write('parRange rho100  -0.01 0.01\n')
			f.write('parRange rho1m10 -0.01 0.01\n')
			f.write('parRange rho111  -0.01 0.01\n')
			f.write('parRange rho001  -0.01 0.01\n')
			f.write('parRange rho101  -0.01 0.01\n')
			f.write('parRange rho1m11 0.45 0.55\n')
			f.write('parRange rho102  -0.01 0.01\n')
			f.write('parRange rho1m12 -0.55 -0.45\n\n')

		for dat in self.data:
			line = 'amplitude {0}_{1}::sum_{1}::SDME TwoPiAngles [rho000] [rho100] [rho1m10] [rho111] [rho001] [rho101] [rho1m11] [rho102] [rho1m12] pol_{1}\n'.format(self.reaction_name, dat)
			f.write(line)
			line = 'initialize {0}_{1}::sum_{1}::SDME cartesian {2:.2f} 0.0 real \n'.format(self.reaction_name, dat, random.uniform(0, 100))
			f.write(line)

	def write_amptools_config(self):
		print('Generating config file '+self.fname)
		
		with open(self.fname, 'w') as f:
			f.write('# Writting AmpTools config file with amptools_cfg class\n')
			if self.amplitudes == 'sdme':
				f.write('# Write SDME amplitudes \n')
			f.write('fit '+self.fit_name+'\n\n')

			for dat in self.data:
				f.write('reaction {0}_{1} {2}\n'.format(self.reaction_name, dat, self.particles))
			f.write('\n')

			for dat in self.data:
				f.write('normintfile {0}_{1} {2}_{1}.ni\n'.format(self.reaction_name, dat, self.fit_name))
			f.write('\n')

			f.write('# Load data\n')
			for dat in self.data:
				f.write('data {0}_{1} {2} {3}/dat_{1}{4}.root\n'.format(self.reaction_name, dat, self.ROOTDataReader, os.getcwd(), self.ext))
				f.write('accmc {0}_{1} {2} {3}/acc_{1}{4}.root\n'.format(self.reaction_name, dat, self.ROOTDataReader, os.getcwd(), self.ext))
				f.write('genmc {0}_{1} {2} {3}/gen_{1}{4}.root\n'.format(self.reaction_name, dat, self.ROOTDataReader, os.getcwd(), self.ext))
				if self.include_bkg:
					f.write('bkgnd {0}_{1} {2} {3}/bkg_{1}{4}.root\n\n'.format(self.reaction_name, dat, self.ROOTDataReader, os.getcwd(), self.ext))
				else:
					f.write('\n')
			
			f.write('# Define polarization information\n')
			write_pol = {'hist' : self.write_pol_hist, 'average' : self.write_pol_average, 'custom' : self.write_pol_custom}
			write_pol[self.polarization](f)

			write_amplitude = {'sdme' : self.write_sdme, 'twopsZlm' : self.write_twopsZlm}
			write_amplitude[self.amplitudes](f)

if __name__ == '__main__':
	z = [runPeriod+'_'+polAngle for runPeriod in ['sp17', 'sp18', 'fa18'] for polAngle in ['000', '045', '090', '135']]
	x = amptools_cfg()
	x.set_data(z)
	x.set_particles('Beam Proton KShort KLong')
	x.write_amptools_config()
