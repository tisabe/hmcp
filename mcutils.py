import numpy as np
import matplotlib.pyplot as plt
import scipy.optimize as opt

def importPlotData(filepath):
    plotData = [] #Array to save the real part of the wave functions
    with open(filepath,'r') as inputfile:
        for line in inputfile:
            plotData.append(line.strip().split('\t')) #Tab is used as seperator between values
        for j in range(len(plotData)): #Cast list items from string to float type
            plotData[j] = [float(plotData[j][i]) for i in range(len(plotData[0]))] # cast entries to float
    return np.array(plotData) # cast to numpy array

def importObsData(filepath):
    obsData = [] # Array to save the observable data
    with open(filepath,'r') as obsfile:
        for line in obsfile:
            obsData.append(line.strip().split('\t'))
        for j in range(len(obsData)):
            obsData[j] = [float(obsData[j][i]) for i in range(len(obsData[0]))]
    return np.array(obsData).T

def makePlot(data, y_label):
    plt.plot(data[0],data[1])
    plt.xlabel("Montecarlo steps")
    plt.ylabel(y_label)
    plt.show()

#calculate the autocorrelation of data point k steps apart in the array obs
def auto_corr(obs, N, k, mu):
    return sum((obs[:N-k] - mu) * (obs[k:] - mu))/(N-k)

#generate an array with the autocorrelation of the data array with varying k
def calc_autocorr(data, k_max):
    autocorr = []
    k_array = np.arange(k_max)
    energy_expect = np.mean(data)
    for k in k_array:
        autocorr.append(auto_corr(data, len(data), k, energy_expect))
    return autocorr/auto_corr(data, len(data), 0, energy_expect)

#fit function for scipy.optimize.curve_fit
exp_fit = lambda x, a, tau : a*np.exp(-x/tau)

#integrated autocorrelation time
integrated_autocorr_time = lambda autocorr : sum(autocorr)

#autocorrelation time with fit
fit_autocorr_time = lambda autocorr, k_max : opt.curve_fit(exp_fit,np.arange(k_max),autocorr[:],p0=(1,5))[0]

def makeFitPlot(data, k_max, A, tau):
    k_array = np.arange(k_max)
    plt.plot(k_array[:k_max],data[:k_max])
    plt.plot(k_array[:k_max], A * np.exp(-k_array[:k_max]/tau))
    plt.xlabel("steps after thermalisation k")
    plt.ylabel("C(k)/C(0)")
    plt.show()
