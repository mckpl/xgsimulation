import numpy as np
from xgsimulation import calculate_xg

def_x = np.array([0.0, -1.0], dtype=np.float64)
def_y = np.array([5.0, 7.0], dtype=np.float64)

xg = calculate_xg(
    shooter_x=0.0, shooter_y=11.0, 
    shot_variance=0.005,
    defender_xs=def_x, defender_ys=def_y,
    defender_body_r=0.4, defender_reach_r=1.0,
    goalkeeper_x=0.0, goalkeeper_y=0.0,
    goalkeeper_body_r=0.5, goalkeeper_reach_r=1.5,
    n_iterations=5000
)

xg_penalty = calculate_xg(
    shooter_x=0.0, shooter_y = 11.0,
    shot_variance = 0.001,
    defender_xs = np.array([]), defender_ys = np.array([]),
    defender_body_r = 0.0, defender_reach_r = 0.0,
    goalkeeper_x = 0.0, goalkeeper_y = 0.0,
    goalkeeper_body_r=0.5, goalkeeper_reach_r=1.5,
    n_iterations=5000
)

print(f"xG: {xg}")
print(f"penalty xG: {xg_penalty}")