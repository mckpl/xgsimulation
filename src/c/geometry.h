#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <stddef.h>

typedef struct _Point {
    double x;
    double y;
} Point;

typedef struct _Vector {
    double x;
    double y;
} Vector;

typedef struct _Ray {
    Point origin;
    Vector vector;
} Ray;

typedef struct _Circle {
    Point center;
    double radius;
} Circle;

typedef struct _Interval {
    double left;
    double right;
} Interval;

typedef struct _Union_Of_Intervals {
    Interval* intervals;
    size_t n;
} Union_Of_Intervals;

// podstawowe funkcje
int compare(double a, double b);
int is_equal(double a, double b);

// punkty i wektory
double dist_point_point(Point a, Point b);
Vector vector_between(Point start, Point end);
Vector scale_vector(double scalar, Vector vector);
Vector unit_vector(Point start, Point end);
Vector unit_vector_with_oriented_angle(double oriented_angle);

// ray
Ray ray_through_points(Point origin, Point target);
Ray ray_with_oriented_angle(Point origin, double oriented_angle);
double oriented_angle_of_ray(Ray ray);
double ray_intersection_with_y_0(Ray ray);

// przedzialy
double interval_length(Interval interval);
double interval_midpoint(Interval interval);
Union_Of_Intervals create_union(Interval* intervals, size_t n);
Union_Of_Intervals trim_union(Union_Of_Intervals union_of_intervals, double left_limit, double right_limit);
Union_Of_Intervals subtract_union_from_interval(Union_Of_Intervals union_of_intervals, double left_limit, double right_limit);
Interval biggest_interval(Union_Of_Intervals union_of_intervals);
int is_point_in_union(Union_Of_Intervals union_of_intervals, double point);

void delete_union(Union_Of_Intervals union_of_intervals);

Interval circle_coverage_on_y_0(Circle circle, Point point);

#endif