import os
import sys
from multiprocessing import Pool

fit_name = sys.argv[1]
nBins = int(sys.argv[2]) 
nprocess = int(sys.argv[3]) 
reaction_name = 'NAME_'
seed_file = 'param_init.cfg'
cfg_file_name = 'variation.cfg'
data_dir = fit_name
base_directory = os.getcwd()
# nominal_sdme_results = '/d/grid15/gabyrod7/analysis/ksmisskl_gabyrod_gluex1_PhiSDME/sdme/fits/gluex1/sdme_nominal.csv'

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

        # for nline, line in enumerate(f, start = 0):
        #     line = line.strip().split('\t')
        #     cov = float(line[nline])
        #     if cov < 0:
        #         cov = math.fabs(cov)
        #     par_err.append(math.sqrt(cov))
        #     if nline == npar-1:
        #         break # done reading SDME uncertainties 

    my_dict = {par_name[i]: par_val[i] for i in range(len(par_name))}
    return my_dict

def variation_setup():
    paths = []
	
    for i in range(nBins):
        path = base_directory+'/'+data_dir+'/bin_'+str(i)

        nominal_results = read_sdme_fit(f'/d/grid15/gabyrod7/analysis/ksmisskl_gabyrod_gluex1_PhiSDME/sdme/fits/gluex1/9bins_1.0t/bin_{i}/nominal.fit')

        if os.path.exists(path+'/amptools.cfg'):
            print(f'nominal fit exists in {path}')
            with open(f'{path}/amptools.cfg', 'r') as inf:
                with open(f'{path}/variation.cfg', 'w') as opf:
                    for line in inf:
                        if line[0:3] == 'fit':
                            line = line.replace(line.split(' ')[1], 'variation\n')
                            opf.write(line)
                            continue

                        if line.split(' ')[0] == 'keyword':
                            continue
                        
                        if line.split(' ')[0] == 'parRange':
                            continue
					
                        if line.split(' ')[0] == 'parameter':
                            opf.write(f'parameter {line.split(" ")[1]} {nominal_results[line.split(" ")[1]]} \n')
                            continue
                        
                        if line.split(' ')[0] == 'initialize':
                            opf.write(f'initialize {line.split(" ")[1]} {line.split(" ")[2]} {nominal_results[line.split(" ")[1]+"_re"]} {nominal_results[line.split(" ")[1]+"_im"]} real \n')
                            continue

                        opf.write(line)
        paths.append(path)
    return paths

def run_fit(path):
    print(f'Move to directory {path}')
    os.chdir(path)

    cmd = f'fit -c variation.cfg > variation.log'
    print(cmd)
    os.system(cmd)

    print('done fitting in '+path)


if __name__ == '__main__':
    paths = variation_setup()

    if nprocess == 1:
        for path in paths:
            run_fit(path)
    else:
        p = Pool(nprocess)
        p.map(run_fit, paths)
