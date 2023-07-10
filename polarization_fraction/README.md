# Polarization Fraction

Here we combine the different polarization fraction vs. beam energy plots.
These plots were made with code sent by Mike Dugger in an email to halld-physics@jlab.org on February 25, 2021.
The makePolValsV9.tar was sent in that email.
These plots are used in the SDME analysis.
Since each run period has differnt amount of statistics we use the luminosity in the coherent peak as the weight factor.
The luminosity for each GlueX-I run period can be found at https://halldweb.jlab.org/wiki-private/index.php/GlueX_Phase-I_Dataset_Summary.
Here is a table the luminosity for each run period, what fraction of GlueX-I data each run period corresponds to and the average polarization for each diamond orientation:

| run | luminosity | fraction of total | 0 | 45 | 90 | -45 |
| --- | --- | --- | ---|---|---|---|
| Spring 2017 | 21.8 | 0.175 | 0.3537 | 0.3484 | 0.3472 | 0.3512 | 
| Spring 2018 | 63.0 | 0.504 | 0.3420 | 0.3474 | 0.3478 | 0.3517 | 
| Fall 2018 | 40.1   | 0.321 | 0.3563 | 0.3403 | 0.3430 | 0.3523 | 
| GlueX-I   | 124.9  | 1.000 | 0.3486 | 0.3452 | 0.3461 | 0.3518 |


The combine.C script will create a gluex1Tpol.root file which has the weighted polarization fraction vs. beam energy.

# Polarization angle 

The diamond used to convert the electrom beam from CEBAF into a linearly polarized photon beam is oriented so the the 
linear polarization is at 0, 45, 90 and 135 (or -45) degrees with respect to the floor (double check this is correct).
However the actual orientation of the beam is shifted from these angles by a small amount. This offset has been 
measured using the $\rho$(770) -> $\pi$<sup>+</sup>$\pi$<sup>-</sup> decays. The results of this analysis can be found in [DocDb:3977](https://halldweb.jlab.org/DocDB/0039/003977/006/note.pdf).
For easy reference we also write the values here (in degrees) here:

| Nominal | Spring 2017 | Spring 2018 | Fall 2018 | GlueX-I | Spring 2020 |
| ---     | ---         | ---         | ---       | ---         | ---     |
| 0   | 1.8 | 4.1 | 3.3 | 3.4 | 1.4 |
| 90  | 94.5 | 94.2 | 92.9 | 93.8 | 93.4 |
| -45 | -41.6 | -42.4 | -42.1 | -42.2 | -42.2 |
| 45  | 47.9 | 48.5 | 48.3 | 48.3 | 47.1 | 
