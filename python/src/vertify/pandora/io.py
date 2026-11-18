'''
Handle I/O for Pandora monitoring vertex algorithm
'''

import pathlib
import uproot

import numpy as np
import pandas as pd
import sqlite3 as sql

from pathlib import Path
from typing import List, Optional, Literal
from tqdm.auto import tqdm

def _load_one(file, tree = 'vertices', preselection: Optional[str | List[str]] = None):
    with uproot.open(file) as f:
        names = [k for k in f.keys(cycle=False) if k.startswith(tree)]
        dfs = []
        for name in names:
            df = f[name].arrays(library="pd")
            df["tree"] = name

            if preselection:
                de = select(df, preselection)
            
            dfs.append(df)
    
    df = pd.concat(dfs, ignore_index=True)
    return df

def load(path: Path, preselection: Optional[str | List[str]] = None):
    '''Load the data from the .root files 
    in the `path`. If `preselection`,  
    return the skimmed version of the data

    @params
        path: required, Path object
            path to the data files
        preselection: str | List[str]
    '''

    dfs = []
    
    for file in (pbar := tqdm(path.glob('*.root'))):
        df = _load_one(file, preselection=preselection)
        dfs.append(df)
        pbar.set_description(f'Processing {file}, this df has {df.shape = }')

    df = pd.concat(dfs, ignore_index=True)
    return df

def _query_one_table(table: str, db_file):

    connection = sql.connect(db_file)

    df = pd.read_sql_query(f'SELECT * FROM {table}', connection)

    connection.close()
    return df

def query_tables(path: Path, table: str, preselection: Optional[str | List[str]] = None):
    '''Load the data from the .db files 
    in the `path`. If `preselection`,  
    return the skimmed version of the data

    @params
        path: required, Path object
            path to the data files
        preselection: str | List[str]
    '''
    dfs = []
    
    for file in (pbar := tqdm(path.glob('*.db'))):
        df = _query_one_table(table, file)
        if preselection:
            df = select(df, preselection)
            
        dfs.append(df)

    df = pd.concat(dfs, ignore_index=True)
    return df