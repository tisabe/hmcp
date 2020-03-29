import numpy as np
import matplotlib.pyplot as plt
import scipy.optimize as opt

def importObsData(filepath):                                                #Function to import observables date from the c program
    obsData = []                                                            #Array to save the observable data
    with open(filepath,'r') as obsfile:
        for line in obsfile:
            obsData.append(line.strip().split('\t'))
        parameters = [obsData[0],obsData[1]]                                #Simulation parameters are saved in the first two rows of the file
        del obsData[0:3]                                                    #Exclude simulation parameters from further treatment (type casting)
        for j in range(len(obsData)):                                       #Cast remaining entries from string to float
            obsData[j] = [float(obsData[j][i]) for i in range(len(obsData[0]))]
    return [parameters,np.array(obsData).T]                                 #Return list with simulation parameters and array of observable data

def makePlot(data, y_label):                                                #Function to generate a plot with data = [datax, datay] and a specified y-axis label
    plt.plot(data[0],data[1])
    plt.xlabel("Montecarlo steps")
    plt.ylabel(y_label)
    plt.show()

def auto_corr(obs, N, k, mu):                                               #Calculate the autocorrelation of data point k steps apart in the array obs with mu = mean(obs) and N = len(obs)
    return sum((obs[:N-k] - mu) * (obs[k:] - mu))/(N-k)

def calc_autocorr(data, k_max):                                             #Generate an array with the autocorrelation of the data array with k = 0,1,...,k_max normalised to the variance
    autocorr = []
    k_array = np.arange(k_max)
    energy_expect = np.mean(data)
    for k in k_array:
        autocorr.append(auto_corr(data, len(data), k, energy_expect))
    return autocorr/auto_corr(data, len(data), 0, energy_expect)

exp_fit = lambda x, A, tau : A*np.exp(-x/tau)                               #Exponential fit function for scipy.optimize.curve_fit

integrated_autocorr_time = lambda autocorr : sum(autocorr)                  #Integrated autocorrelation time as sum over all autocorrelations

fit_autocorr_time = lambda autocorr, k_max : opt.curve_fit(exp_fit,np.arange(k_max),autocorr[:],p0=(1,5))[0]
                                                                            #Autocorrelation time from exponential fit

def makeFitPlot(data, k_max, A, tau, plottitle):                                       #Generates a plot from the data array as well as an exponential given by the function in exp_fit
    k_array = np.arange(k_max)                                              #used for comparison of exponential autocorrelation fit with autocorrelation data
    plt.plot(k_array[:k_max],data[:k_max])
    plt.plot(k_array[:k_max], A * np.exp(-k_array[:k_max]/tau))
    plt.xlabel("steps after thermalisation k")
    plt.ylabel("C(k)/C(0)")
    plt.title(plottitle)
    plt.show()
