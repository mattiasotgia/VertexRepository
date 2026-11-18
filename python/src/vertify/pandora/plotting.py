'''
Pandora-monitoring specific plotting utilities
'''

from __future__ import annotations

import numpy as np
import pandas as pd

import matplotlib as mpl
import matplotlib.pyplot as plt

import mplhep as hep
import hist

from corner import hist2d

import iminuit
from iminuit import Minuit

from jacobi import propagate
from uncertainties import ufloat

import pathlib
from pathlib import Path

from cycler import cycler

from typing import List, Optional, Literal

def add_efficiency(ax, data, success, cuts, label=None, **kw_args):
    data, success, cuts = np.asarray(data), np.asarray(success).astype(bool), np.asarray(cuts)
    passed = data[success]
    
    fraction_passed = np.array([np.count_nonzero(passed < c) for c in cuts]) / len(data)

    ax.plot(cuts, fraction_passed, label=label, **kw_args)

    ax.set(
        ylabel='Fraction of events'
    )