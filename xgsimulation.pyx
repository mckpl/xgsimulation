import numpy as np
cimport numpy as np
from libc.stdlib cimport srand
from libc.time cimport time

# Podpięcie nagłówka z Twojego katalogu C
cdef extern from "simulation.h":
    double c_calculate_xg "calculate_xg" (
        double shooter_x, double shooter_y,
        double shot_variance,
        double* defender_xs, double* defender_ys,
        int n_defenders,
        double defender_body_r, double defender_reach_r,
        double goalkeeper_x, double goalkeeper_y,
        double goalkeeper_body_r, double goalkeeper_reach_r,
        int n_iterations
    )
srand(time(NULL))

def calculate_xg(double shooter_x, double shooter_y, double shot_variance,
                 double[::1] defender_xs not None, double[::1] defender_ys not None,
                 double defender_body_r, double defender_reach_r,
                 double goalkeeper_x, double goalkeeper_y,
                 double goalkeeper_body_r, double goalkeeper_reach_r,
                 int n_iterations=1000):
    """
    calculates expected goals using simulation

    Parameters
    ----------
    shooter_x : float
        x-coordinate of the shooter
    shooter_y : float
        y-coordinate of the shooter
    shot_variance : float
        variance of the shot inaccuracy
    defender_xs : np.ndarray of float64
        array of defenders' x-coordinates
    defender_ys : np.ndarray of float64
        array of defenders' y-coordinates
    defender_body_r : float
        defender physical body radius
    defender_reach_r : float
        defender reach blocking radius
    goalkeeper_x : float
        x-coordinate of the goalkeeper
    goalkeeper_y : float
        y-coordinate of the goalkeeper
    goalkeeper_body_r : float
        goalkeeper physical body radius
    goalkeeper_reach_r : float
        goalkeeper reach blocking radius
    n_iterations : int, optional
        number of Monte Carlo simulations, default is 1000

    Returns
    -------
    float
        probability of scoring a goal (xG value)
    """

    cdef int n_defenders = defender_xs.shape[0]
    
    if n_defenders != defender_ys.shape[0]:
        raise ValueError("defender_xs and defender_ys must have equal lenght")

    cdef double* c_def_x = NULL
    cdef double* c_def_y = NULL

    if n_defenders > 0:
        c_def_x = &defender_xs[0]
        c_def_y = &defender_ys[0]

    return c_calculate_xg(
        shooter_x, shooter_y, shot_variance,
        c_def_x, c_def_y, n_defenders,
        defender_body_r, defender_reach_r,
        goalkeeper_x, goalkeeper_y, goalkeeper_body_r, goalkeeper_reach_r,
        n_iterations
    )