import os
import random

class amptools_cfg:
	def __init__(self):
		self.data = ''
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
					'gluex1_000' : 0.3486, 'gluex1' : 0.3452, 'gluex1_090' : 0.3461, 'gluex1_135' : 0.3518}

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

	def write_zlm(self, f, sum, amp, l, m, fix):
		wave_dictionary = { 'Sp0+' : ['Positive', 'Sp0+', 0, 0, True],
                            'Sp0-' : ['Negative', 'Sp0-', 0, 0, True],

                            'Pm1+': ['Positive', 'Pm1+', 1, -1, False],
                            'Pm1-': ['Negative', 'Pm1-', 1, -1, False],
                            'Pp0+': ['Positive', 'Pp0+', 1, 0, False],
                            'Pp0-': ['Negative', 'Pp0-', 1, 0, False],
                            'Pp1+': ['Positive', 'Pp1+', 1, 1, False],
                            'Pp1-': ['Negative', 'Pp1-', 1, 1, False],

                            'Dm2+': ['Positive', 'Dm2+', 2, -2, False],
                            'Dm2-': ['Negative', 'Dm2-', 2, -2, False],
                            'Dm1+': ['Positive', 'Dm1+', 2, -1, False],
                            'Dm1-': ['Negative', 'Dm1-', 2, -1, False],
                            'Dp0+': ['Positive', 'Dp0+', 2, 0, False],
                            'Dp0-': ['Negative', 'Dp0-', 2, 0, False],
                            'Dp1+': ['Positive', 'Dp1+', 2, 1, False],
                            'Dp1-': ['Negative', 'Dp1-', 2, 1, False],
                            'Dp2+': ['Positive', 'Dp2+', 2, 2, False],
                            'Dp2-': ['Negative', 'Dp2-', 2, 2, False],

                            'Fm3+': ['Positive', 'Fm3+', 3, -3, False],
                            'Fm3-': ['Negative', 'Fm3-', 3, -3, False],
                            'Fm2+': ['Positive', 'Fm2+', 3, -2, False],
                            'Fm2-': ['Negative', 'Fm2-', 3, -2, False],
                            'Fm1+': ['Positive', 'Fm1+', 3, -1, False],
                            'Fm1-': ['Negative', 'Fm1-', 3, -1, False],
                            'Fp0+': ['Positive', 'Fp0+', 3, 0, False],
                            'Fp0-': ['Negative', 'Fp0-', 3, 0, False],
                            'Fp1+': ['Positive', 'Fp1+', 3, 1, False],
                            'Fp1-': ['Negative', 'Fp1-', 3, 1, False],
                            'Fp2+': ['Positive', 'Fp2+', 3, 2, False],
                            'Fp2-': ['Negative', 'Fp2-', 3, 2, False],
                            'Fp3+': ['Positive', 'Fp3+', 3, 3, False],
                            'Fp3-': ['Negative', 'Fp3-', 3, 3, False] }
                           
		for pol_angle, pol_frac in self.pol_info:
			f.write('# Amplitude %s and polarization angle %d \n' % (amp, pol_angle))
			if sum == 'Positive':
				line = 'amplitude %s::%sRe::%s Zlm %d %d +1 +1 %.1f %.3f \n' % (self.reaction_name+self.pols_map[pol_angle], sum, amp, l, m, pol_angle, pol_frac) # real term
				f.write(line)
				line = 'amplitude %s::%sIm::%s Zlm %d %d -1 -1 %.1f %.3f \n' % (self.reaction_name+self.pols_map[pol_angle], sum, amp, l, m, pol_angle, pol_frac) # imeginary term
				f.write(line)
			if sum == 'Negative':
				line = 'amplitude %s::%sRe::%s Zlm %d %d +1 -1 %.1f %.3f \n' % (self.reaction_name+self.pols_map[pol_angle], sum, amp, l, m, pol_angle, pol_frac) # real term
				f.write(line)
				line = 'amplitude %s::%sIm::%s Zlm %d %d -1 +1 %.1f %.3f \n' % (self.reaction_name+self.pols_map[pol_angle], sum, amp, l, m, pol_angle, pol_frac) # imeginary term
				f.write(line)

			if fix:
				num1 = random.uniform(-100, 100)
				line = 'initialize %s::%sRe::%s cartesian %.2f 0.0 real \n' % (self.reaction_name+self.pols_map[pol_angle], sum, amp, num1)
				f.write(line)
			else:
				num1, num2 = (random.uniform(-100, 100) , random.uniform(-100, 100))
				line = 'initialize %s::%sRe::%s cartesian %.2f %.2f \n' % (self.reaction_name+self.pols_map[pol_angle], sum, amp, num1, num2)
				f.write(line)

			line = 'constrain %s::%sRe::%s %s::%sIm::%s \n' % (self.reaction_name+self.pols_map[pol_angle], sum, amp, self.reaction_name+self.pols_map[pol_angle], sum, amp)
			f.write(line)

		if len(self.pol_info) > 1:
			f.write('# Constrain parameters across datasets \n')
			for pol_angle, pol_frac in self.pol_info:
				line = 'constrain %s::%sRe::%s %s::%sRe::%s \n' % (self.reaction_name+self.pols_map[self.pol_info[0][0]], sum, amp, self.reaction_name+self.pols_map[pol_angle], sum, amp)
				f.write(line)
				#line = 'scale %s::%sRe::%s [par_scale_%s] \n' % (self.reaction_name+self.pols_map[self.pol_info[0][0]], sum, amp, self.pols_map[pol_angle])
				#line = 'scale %s::%sRe::%s [par_scale_%s] \n' % (self.reaction_name+self.pols_map[pol_angle], sum, amp, self.pols_map[pol_angle])
				f.write(line)
				line = 'constrain %s::%sIm::%s %s::%sIm::%s \n' % (self.reaction_name+self.pols_map[self.pol_info[0][0]], sum, amp, self.reaction_name+self.pols_map[self.pol_info[0][0]], sum, amp)
				f.write(line)

	def write_sdme(self, f):
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
			
			f.write('# Create sums\n')
			for dat in self.data:
				f.write('sum {0}_{1} sum_{1}\n'.format(self.reaction_name, dat))
			f.write('\n')

			f.write('# Define polarization information\n')
			write_pol = {'hist' : self.write_pol_hist, 'average' : self.write_pol_average, 'custom' : self.write_pol_custom}
			write_pol[self.polarization](f)

			# self.write_sdme(f)
			write_amplitude = {'sdme' : self.write_sdme, 'zlm' : self.write_zlm}
			write_amplitude[self.amplitudes](f)

if __name__ == '__main__':
	z = [runPeriod+'_'+polAngle for runPeriod in ['sp17', 'sp18', 'fa18'] for polAngle in ['000', '045', '090', '135']]
	x = amptools_cfg()
	x.set_data(z)
	x.set_particles('Beam Proton KShort KLong')
	# x.set_ext('_0')
	x.write_amptools_config()
