'''
Utilities to perform selections and basic efficiecny checks within Pandora monitoring
'''

import numpy as np
import pandas as pd

def select(df, selection):
    if not isinstance(selection, list):
        selection = [selection]
    return df.query(' & '.join(selection))