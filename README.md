# xgsimulation

It is a Python library that allows to calculate approximate probability of scoring a goal (xG) it takes position of players on football pitch and runs many simulations which result in (xG) metric, it is really simple as it takes only 2d dimensions making it really good model for measuring opportunities of shots take on ground

## dependencies
- Python at least 3.9
- NumPy at least 1.21


## installation
to install clone repository and use `pip`

```bash
git clone https://github.com/mckpl/xgsimulation.git
cd xgsimulation
pip install .
```

## usage example

```python
import numpy as np
from xgsimulation import calculate_xg

xg_penalty = calculate_xg(
    shooter_x=0.0, shooter_y = 11.0,
    shot_variance = 0.001,
    defender_xs = np.array([]), defender_ys = np.array([]),
    defender_body_r = 0.0, defender_reach_r = 0.0,
    goalkeeper_x = 0.0, goalkeeper_y = 0.0,
    goalkeeper_body_r=0.5, goalkeeper_reach_r=1.5,
    n_iterations=5000
)

print(f"penalty xG: {xg_penalty}")
```

Output:
```text
penalty xG: 0.945
```
result should be around that value

## license
MIT