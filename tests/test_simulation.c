#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h> 
#include <time.h>
#include "../src/c/simulation.h"
#include "../src/c/constants.h"

void assert_xg_approx(double expected, double actual, double epsilon) {
    assert(fabs(expected - actual) <= epsilon);
}

void test_empty_goal() {
    double shooter_x = 0.0;
    double shooter_y = 1.0;
    double variance = 0.001; 
    int n_defenders = 0;
    double gk_x = 100.0;
    double gk_y = 100.0;
    double gk_body_r = 0.5;
    double gk_reach = 1.5;

    double xg = calculate_xg(
        shooter_x, shooter_y, variance,
        NULL, NULL, n_defenders,
        0.0, 0.0,
        gk_x, gk_y, gk_body_r, gk_reach,
        1000
    );

    assert_xg_approx(1.0, xg, 0.001);
    printf("test_empty_goal ok\n");
}

void test_completely_blocked_goal() {
    double shooter_x = 0.0;
    double shooter_y = 11.0;
    double variance = 0.05;

    double def_x[] = {0.0};
    double def_y[] = {5.0};
    int n_defenders = 1;
    double def_body_r = 20.0; 
    double def_reach_r = 20.0;

    double gk_x = 0.0, gk_y = 0.0, gk_body_r = 0.5, gk_reach = 1.5;

    double xg = calculate_xg(
        shooter_x, shooter_y, variance,
        def_x, def_y, n_defenders,
        def_body_r, def_reach_r,
        gk_x, gk_y, gk_body_r, gk_reach,
        1000
    );

    assert_xg_approx(0.0, xg, 0.0);
    printf("test_completely_blocked_goal ok\n");
}

void test_penalty_kick_with_gk() {
    double shooter_x = 0.0;
    double shooter_y = 11.0;
    double variance = 0.005; 

    int n_defenders = 0;

    double gk_x = 0.0, gk_y = 0.0, gk_body_r = 0.4, gk_reach_r = 1.2;

    double xg = calculate_xg(
        shooter_x, shooter_y, variance,
        NULL, NULL, n_defenders,
        0.0, 0.0,
        gk_x, gk_y, gk_body_r, gk_reach_r,
        10000 
    );

    assert(xg > 0.5 && xg < 1.0);
    printf("test_penalty_kick_with_gk ok (xG = %.4f)\n", xg);
}

void test_out_of_bounds_variance() {
    double shooter_x = 0.0;
    double shooter_y = 11.0;
    double variance = 10.0;

    double gk_x = 0.0, gk_y = 0.0, gk_body_r = 0.5, gk_reach = 1.5;

    double xg = calculate_xg(
        shooter_x, shooter_y, variance,
        NULL, NULL, 0,
        0.0, 0.0,
        gk_x, gk_y, gk_body_r, gk_reach,
        1000
    );

    assert(xg >= 0.0 && xg < 0.2); 
    printf("test_out_of_bounds_variance ok\n");
}

int main() {
    srand(time(NULL));

    test_empty_goal();
    test_completely_blocked_goal();
    test_penalty_kick_with_gk();
    test_out_of_bounds_variance();

    return 0;
}