'''
General purpouse utilities
'''

from pathlib import Path

LOG_PATH = Path('../logs/VertexMonitoring')

def log(what, where, log_path=LOG_PATH):
    where: Path = log_path / where
    where.parent.mkdir(parents=True, exist_ok=True)

    with open(where.with_suffix(f'.log'), 'w') as flog:
        print(what, file=flog)