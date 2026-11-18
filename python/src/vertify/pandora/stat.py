'''
Statistical part of the Pandora-related stuff
'''

import numpy as np
import pandas as pd

import iminuit
from iminuit import Minuit
from iminuit.cost import UnbinnedNLL, BinnedNLL, ExtendedBinnedNLL

def fit(n, bins, p0: tuple, cdf, limits=None, fixed=None):

    cost = ExtendedBinnedNLL(n, bins, cdf)
    m = Minuit(cost, p0)

    if fixed:
        for f in fixed:
            m.fixed[f] = fixed[f]
    
    if limits:
        for l in limits:
            m.limits[l] = limits[l]
    m.migrad()
    m.hesse()

    return m

def success_rate(data):
    return np.divide(len(data[data.success == 1]), len(data.success), where=len(data.success)!=0, out=np.zeros_like(len(data.success)).astype(np.float64))