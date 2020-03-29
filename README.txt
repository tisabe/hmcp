THERMODYNAMICS OF PHONONS WITH THE HYBRID MONTECARLO ALGORITHM

Please use 'main.c' to generate an executable that simulates phonons in an one-dimensional crystal.
Precompiled executables can be found in the folder 'executables'. For compiling new executables please use the 'Makefile'.



To start a simulation provide the main.exe file with the following inputs via the command shell:
time_max	Number of MC (Montecarlo) time steps to calculate
N		Number of atoms in the one-dimensional crystal
P		Number of discretisation points in momentum-space
M		= 1/tau : Number of MD (Molecular Dynamics) steps per MC step*
v0		= lim_{k->0} omega_ph(k) : Speed of sound in the crystal
beta		= 1/(k_B T) : Inserve Temperature of the system

*If M = 0 a bisection algorithm with time_max = 10000 will be started to find a good M for a specified acceptance rate.