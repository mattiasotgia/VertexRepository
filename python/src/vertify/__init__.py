from pathlib import Path

import matplotlib as mpl
import matplotlib.style as mstyle

from . import pandora, plotting, utils

_style_dir = Path(__file__).parent / "style"


def _register_styles():
    for f in _style_dir.glob("*.mplstyle"):
        mstyle.library[f.stem] = mpl.rc_params_from_file(
            f, use_default_template=False
        )
    mstyle.available[:] = sorted(mstyle.library)


_register_styles()