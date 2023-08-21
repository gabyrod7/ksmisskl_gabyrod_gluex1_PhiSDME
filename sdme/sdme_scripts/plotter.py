import os
import sys

def run_plotter(fit_name, nbins, plotter):
    base_directory = os.getcwd()
    
    for i in range(nbins):
        path = '{}/{}/bin_{}/'.format(base_directory, fit_name, i)
        os.chdir(path)
        
        if os.path.exists('nominal.fit'):
            cmd = plotter+' nominal.fit'
            print('run '+cmd+" in "+path)
            os.system(cmd)
        else:
            print('no nominal.fit in '+path)

if __name__ == '__main__':
    fit_name = sys.argv[1]
    nbins = int(sys.argv[2])
    plotter = sys.argv[3]
 
    run_plotter(fit_name, nbins, plotter)