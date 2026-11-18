'''
Generic (package spread) plotting utilities
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

PLOT_PATH = Path('../plots/VertexMonitoring')
SAVE_FORMATS = ['pdf', 'png']

def figure(title, title_loc='left', selection_title=None, **kw_args):

    selection_title_loc = kw_args.pop('selection_title_loc', (0.95, 0.9))
    
    fig, ax = plt.subplots(figsize=kw_args.pop('figsize', (3.5, 4)), **kw_args)

    plt.gca().set_title(title, loc=title_loc, color='gray')

    if selection_title:
        if title_loc == 'left':
            plt.gca().set_title(selection_title, loc='right')
        else:
            plt.gca().text(
                *selection_title_loc,
                selection_title,
                transform=ax.transAxes,
                ha='right',
                va='top',
                size=plt.rcParams['axes.titlesize']
            )
    
    return fig, ax

def add_hist(ax, data, bins, label, **kw_args):
    ax.set(
        xlabel=kw_args.pop('xlabel', ''),
        ylabel=kw_args.pop('ylabel', 'Entries'),
    )

    data = np.asarray(data)
    bins = np.asarray(bins)

    # Clipped copy: only for drawing, so overflow shows up in the last bin
    flow = kw_args.pop('flow', False)

    if flow:
        clipped_data = np.clip(data, bins[0], bins[-1])
    
    ax.hist((clipped_data if flow else data), bins=bins, histtype=kw_args.pop('histtype', 'step'),
            label=label, **kw_args)

    # Returned values: original data, so under/overflow is excluded
    n, edges = np.histogram(data, bins=bins,
                            weights=kw_args.get('weights'),
                            density=kw_args.get('density', False))
    return n, edges

def add_hist2d(ax, x, y, bins, levels, histtype: Literal['mix', 'fill', 'contour', 'scatter'] ='mix', label=None, color='C0', **kw_args):
    """2D histogram contour: either filled (fill=True) or lines only (fill=False)."""
    x, y = np.asarray(x), np.asarray(y)

    if histtype == 'mix':
        hist2d(x, y, bins=bins, levels=levels, color=color, **kw_args)
    else:
        raise NotImplementedError(f'Option {histtype=} not yet implemented')
    '''    
    H, xedges, yedges = np.histogram2d(x, y, bins=bins, **kw_args)
    H = H.T  # contour expects Z[y, x]

    if smooth:
        from scipy.ndimage import gaussian_filter
        H = gaussian_filter(H, smooth)

    Bin centers
    xc = 0.5 * (xedges[:-1] + xedges[1:])
    yc = 0.5 * (yedges[:-1] + yedges[1:])

    if fill:
        # Colormap built from the single color: transparent -> color,
        # so several datasets can be overlaid on the same axes
        r, g, b = to_rgb(color)
        cmap = LinearSegmentedColormap.from_list(
            'single', [(r, g, b, 0.0), (r, g, b, alpha)])
        ax.contourf(xc, yc, H, levels=levels, cmap=cmap)
        if label:  # empty proxy artist for the legend
            ax.fill_between([], [], color=color, alpha=alpha, label=label)
    else:
        ax.contour(xc, yc, H, levels=levels, colors=[color],
                   linestyles=linestyle, linewidths=linewidth)
        if label:
            ax.plot([], [], color=color, linestyle=linestyle,
                    linewidth=linewidth, label=label)
    return H
    '''

def add_fit(bins, m: Minuit, pdf, scale=1.0, N=100, draw_errorband=False, **kw_args):

    x = np.linspace(bins.min(), bins.max(), N)

    if draw_errorband:
        y, ycov = propagate(lambda p: pdf(x, p)/scale, m.values, m.covariance)
    else:
        y = pdf(x, m.values)/scale

    ax.plot(x, y, **kw_args)
    
    if draw_errorband:
        yerr = np.diag(ycov) ** 0.5
        ax.fill_between(x, y - yerr, y + yerr, alpha=0.5*kw_args.pop('alpha', 1), color=kw_args.get('color', 'k'))

def add_results(ax, names, m: Minuit, loc, skip=1, separator=', ',
                uncertainties=False, fmt='.2f', **kw_args):
    x, y = loc

    pairs = []
    for a, b, be in list(zip(names, m.values, m.errors))[skip:]:
        if uncertainties:
            val = f'{ufloat(b, be):L}'   # LaTeX output, e.g. 0.12 \pm 0.01
        else:
            val = f'{b:{fmt}}'
        pairs.append(f'${a} = {val}$')

    ax.text(x, y, separator.join(pairs), **kw_args)

def save(fig, where, plot_path=PLOT_PATH, ext=SAVE_FORMATS, **kw_args):
    where: Path = plot_path / where
    where.parent.mkdir(parents=True, exist_ok=True)

    if isinstance(ext, str):
        ext = [ext]
    
    bbox_inches = kw_args.pop('bbox_inches', 'tight')

    for e in ext:
        fig.savefig(where.with_suffix(f'.{e.lstrip(".")}'),
                    bbox_inches=bbox_inches, **kw_args)
