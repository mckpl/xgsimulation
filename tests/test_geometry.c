#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "../src/c/geometry.h"
#include "../src/c/constants.h"

#define LESS -1
#define EQUAL 0
#define GREATER 1

void assert_double_equal(double expected, double actual) {
    if (isinf(expected) && isinf(actual)) {
        assert(expected * actual > 0);
        return;
    }
    assert(compare(expected, actual) == EQUAL);
}

void assert_point_equal(Point expected, Point actual) {
    assert_double_equal(expected.x, actual.x);
    assert_double_equal(expected.y, actual.y);
}

void assert_vector_equal(Vector expected, Vector actual) {
    assert_double_equal(expected.x, actual.x);
    assert_double_equal(expected.y, actual.y);
}

void assert_ray_equal(Ray expected, Ray actual) {
    assert_point_equal(expected.origin, actual.origin);
    assert_vector_equal(expected.vector, actual.vector);
}

void assert_interval_equal(Interval expected, Interval actual) {
    assert_double_equal(expected.left, actual.left);
    assert_double_equal(expected.right, actual.right);
}

void assert_union_equal(Union_Of_Intervals expected, Union_Of_Intervals actual) {
    assert(expected.n == actual.n);
    for (size_t i = 0; i < expected.n; ++i) 
        assert_interval_equal(expected.intervals[i], actual.intervals[i]);
}

void test_compare() {
    double a = -1.0;
    double b = 0.0;
    assert(compare(a,b) == LESS);
    
    assert(compare(b,a) == GREATER);

    assert(compare(0.000000001,0.000000002) == EQUAL);

    assert(compare(0.000000001,0.000000003) == LESS);
}


void test_dist_point_point() {
    Point a = {0.0, 0.0};
    Point b = {3.0, 4.0};
    assert_double_equal(5.0, dist_point_point(a, b));

    assert_double_equal(0, dist_point_point((Point) {0, 1}, (Point) {0, 1}));

    assert_double_equal(21, dist_point_point((Point) {-10.5, 0}, (Point) {10.5, 0}));

    printf("dist_point_point ok\n");
}

void test_unit_vector() {
    // test: trojkat pitagorejski
    Point a = {0.0, 0.0};
    Point b = {3.0, 4.0};

    Vector vector = unit_vector(a, b);
    
    assert_vector_equal((Vector) {3.0/5.0, 4.0/5.0}, vector);

    // test: trojkat pitagorejski
    a = (Point) {0.0, 0.0};
    b = (Point) {3.0, -4.0};

    vector = unit_vector(a, b);
    
    assert_vector_equal((Vector) {3.0/5.0, -4.0/5.0}, vector);


    // test: pionowo do dolu 
    a = (Point) {10.0, 10.0};
    b = (Point) {10.0, 0.0}; 
    vector = unit_vector(a, b);
    assert_vector_equal((Vector) {0.0, -1.0}, vector);

    // test: na ujemnych wspolrzednych
    a = (Point) {-10.0, -10.0};
    b = (Point) {-7.0, -6.0}; 
    vector = unit_vector(a, b);
    assert_vector_equal((Vector) {3.0/5.0, 4.0/5.0}, vector);

    // test: wektor z punktu w ten sam punkt
    a = (Point) {5.0, 5.0};
    b = (Point) {5.0, 5.0};
    
    vector = unit_vector(a, b);

    assert_vector_equal((Vector) {0.0, 0.0}, vector);

    // test
    a = (Point) {5.0, 5.0};
    b = (Point) {4.5, 4.5};
    
    vector = unit_vector(a, b);

    assert_vector_equal((Vector) {-sqrt(2)/2, -sqrt(2)/2}, vector);

    // test
    a = (Point) {5.0, 5.0};
    b = (Point) {5.5, 4.5};
    
    vector = unit_vector(a, b);

    assert_vector_equal((Vector) {sqrt(2)/2, -sqrt(2)/2}, vector);

    // test: odleglosc teoretycznie rowna EPS
    a = (Point) {10.0, 10.0};
    b = (Point) {10.0, 10.000000001};
    // matematycznie wychodzi ze odleglosc tych punktow jest rowna 1e-9 czyli EPS
    // ale tak naprawde jest troche wieksza, czyli wektor z a do b bedzie do gory

    vector = unit_vector(a, b);
    assert_vector_equal((Vector) {0.0, 1.0}, vector);

    // test: odleglosc faktycznie mniejsza niz EPS
    a = (Point) {10.0, 10.0};
    b = (Point) {10.0, 10.0000000001};
    // matematycznie wychodzi ze odleglosc tych punktow jest rowna 1e-10
    // czyli wektor zerowy 

    vector = unit_vector(a, b);
    assert_vector_equal((Vector) {0.0, 0.0}, vector);

    printf("unit_vector ok\n");
}

void test_ray_through_points() {
    // test 1
    Point origin = {10.0, 10.0};
    Point target = {10.0, 5.0};
    
    Ray actual = ray_through_points(origin, target);
    
    Ray expected = {origin, {0.0, -1.0}};
    assert_ray_equal(expected, actual);
}

void test_unit_vector_with_oriented_angle() {
    //test
    double oriented_angle = 0.0;
    Vector actual = unit_vector_with_oriented_angle(oriented_angle);
    Vector expected = {1.0, 0.0};
    assert_vector_equal(expected, actual);
    //test
    assert_vector_equal((Vector){0.0,1.0}, unit_vector_with_oriented_angle(M_PI / 2));
    assert_vector_equal((Vector){0.0,-1.0}, unit_vector_with_oriented_angle(-M_PI / 2));
    assert_vector_equal((Vector){0.0,-1.0}, unit_vector_with_oriented_angle(-M_PI / 2 + 2*M_PI));
    
    printf("unit_vector_with_oriented_angle ok \n");
}

void test_oriented_angle_of_ray() {
    Point origin = {0.0, 0.0};
    assert_double_equal(0.0, oriented_angle_of_ray((Ray){origin, {1.0, 0.0}}));
    assert_double_equal(M_PI/4, oriented_angle_of_ray((Ray){origin, {1.0, 1.0}}));
    assert_double_equal(-M_PI/4, oriented_angle_of_ray((Ray){origin, {1.0, -1.0}}));
    assert_double_equal(-M_PI/2, oriented_angle_of_ray((Ray){origin, {0.0, -1.0}}));

    printf("oriented_angle_of_ray ok\n");
}

void test_ray_intersection_with_y_0() {
    //test: pionowo w dol
    Ray ray = {{10.0, 10.0}, {0.0, -1.0}};
    assert_double_equal(10.0, ray_intersection_with_y_0(ray));
    // test
    ray = (Ray) {{10.0, 10.0}, {sqrt(2)/2, -sqrt(2)/2}};
    assert_double_equal(20.0, ray_intersection_with_y_0(ray));

    //test
    ray = (Ray) {{10.0, 10.0}, {-0.6, -0.8}};
    assert_double_equal(2.5, ray_intersection_with_y_0(ray));

    //test
    ray = (Ray) {{10.0, 10.0}, {1.0, 0.0}};
    assert(isinf(ray_intersection_with_y_0(ray)) && ray_intersection_with_y_0(ray) > 0); // infinity
    //test
    ray = (Ray) {{10.0, 10.0}, {-1.0, 0.0}};
    assert(isinf(ray_intersection_with_y_0(ray)) && ray_intersection_with_y_0(ray) < 0); //-infinity
    //test
    ray = (Ray) {{10.0, 10.0}, {-sqrt(2)/2 , sqrt(2)/2}};
    assert(isinf(ray_intersection_with_y_0(ray)) && ray_intersection_with_y_0(ray) < 0); // -infinity
    //test
    ray = (Ray) {{10.0, 10.0}, {sqrt(2)/2 , sqrt(2)/2}};
    assert(isinf(ray_intersection_with_y_0(ray)) && ray_intersection_with_y_0(ray) > 0); // infinity
    //test
    ray = (Ray) {{10.0, 10.0}, {0.0, 1.0}};
    assert(isinf(ray_intersection_with_y_0(ray))  && ray_intersection_with_y_0(ray) < 0);

    //test
    ray = (Ray) {{15.0, 0.0}, {0.0, 1.0}};
    assert_double_equal(15.0, ray_intersection_with_y_0(ray));
    
    printf("ray_intersection_with_y_0 ok\n");
}

void test_create_union() {

    // test
    Interval in1[] = {{1.0, 3.0}, {3.0, 5.0}};
    Interval exp1[] = {{1.0, 5.0}};

    Union_Of_Intervals expected1 = {exp1, 1};
    Union_Of_Intervals actual1 = create_union(in1, 2);

    assert_union_equal(expected1, actual1);
    delete_union(actual1);
    
    // test
    Interval in2[] = {{1.0, 2.0}, {2.1, 5.0}};
    Interval exp2[] = {{1.0, 2.0}, {2.1, 5.0}};
    Union_Of_Intervals expected2 = {exp2, 2};
    
    Union_Of_Intervals actual2 = create_union(in2, 2);
    assert_union_equal(expected2, actual2);
    delete_union(actual2);

    // test
    Interval in3[] = {{1.0, 4.0}, {2.0, 5.0}, {4.5, 7.0}};
    Interval exp3[] = {{1.0, 7.0}};
    Union_Of_Intervals expected_union3 = {exp3, 1};
    
    Union_Of_Intervals actual3 = create_union(in3, 3);
    assert_union_equal(expected_union3, actual3);
    delete_union(actual3);

    // test
    Interval in4[] = {{1.0, 10.0}, {2.0, 3.0}, {4.0, 5.0}, {8.0, 9.0}};
    Interval exp4[] = {{1.0, 10.0}};
    Union_Of_Intervals expected4 = {exp4, 1};
    
    Union_Of_Intervals actual4 = create_union(in4, 4);
    assert_union_equal(expected4, actual4);
    delete_union(actual4);

    // test
    Interval in5[] = {{8.0, 10.0}, {1.0, 3.0}, {5.0, 6.0}, {2.0, 4.0}};
    Interval exp5[] = {{1.0, 4.0}, {5.0, 6.0}, {8.0, 10.0}};
    Union_Of_Intervals expected5 = {exp5, 3};
    
    Union_Of_Intervals actual5 = create_union(in5, 4);
    assert_union_equal(expected5, actual5);
    delete_union(actual5);

    // test
    Interval int6[] = {{1.0, 3.0}, {3.0 + 1e-10, 5.0}};
    Interval exp6[] = {{1.0, 5.0}};
    Union_Of_Intervals expected6 = {exp6, 1};
    
    Union_Of_Intervals actual6 = create_union(int6, 2);
    assert_union_equal(expected6, actual6);
    delete_union(actual6);
    
    // test
    Interval in7[] = {{-INFINITY, -5.0}, {-6.0, 5.0}, {5.0, INFINITY}};
    Interval exp7[] = {{-INFINITY, INFINITY}};
    Union_Of_Intervals expected7 = {exp7, 1};
    
    Union_Of_Intervals actual7 = create_union(in7, 3);
    assert_union_equal(expected7, actual7);
    delete_union(actual7);

    //test 
    Union_Of_Intervals actual = create_union(NULL, 0);
    assert(actual.intervals ==NULL);
    assert(actual.n == 0);

    
    printf("create_union ok \n");
}

void test_circle_coverage_on_y_0() {
    // test
    Circle circle1 = {{0.0, 1.0}, 1};
    Point point1 =  {1.0, 3.0};
    Interval expected1 = {-3.0, 1.0};
    Interval actual1 = circle_coverage_on_y_0(circle1, point1);
    assert_interval_equal(expected1, actual1);

    //test 
    Circle circle2 = {{0.0, 1.0}, 0.597347143};
    Point point2 =  {1.5, 2.5};
    Interval expected2 = {-3.076815745, 0.134421758};
    Interval actual2 = circle_coverage_on_y_0(circle2, point2);
    assert_interval_equal(expected2, actual2);


    // test
    Circle circle3 = {{0.0, 5.0}, 1.0};
    Point point3 = {0.0, 10.0};
    Interval expected3 = {-2.041241452, 2.041241452}; 
    Interval actual3 = circle_coverage_on_y_0(circle3, point3);
    assert_interval_equal(expected3, actual3);

    // test
    Circle circle4 = {{0.0, 5.0}, 1.0};
    Point point4 = {0.0, 5.0};
    Interval expected4 = {-INFINITY, INFINITY}; 
    Interval actual4 = circle_coverage_on_y_0(circle4, point4);
    assert_interval_equal(expected4, actual4);

    // test
    Circle circle5 = {{0.0, 5.0}, 1.0};
    Point point5 = {1.0, 5.0};
    Interval expected5 = {-INFINITY, INFINITY}; 
    Interval actual5 = circle_coverage_on_y_0(circle5, point5);
    assert_interval_equal(expected5, actual5);

    // test
    Circle circle6 = {{3.0, 5.0}, 2.5};
    Point point6 = {0.0, 5.0};
    Interval expected6 = {3.316624790, INFINITY}; 
    Interval actual6 = circle_coverage_on_y_0(circle6, point6);
    assert_interval_equal(expected6, actual6);


    printf("circle_coverage_on_y0 ok \n");
}

void test_trim_union() {
    // test
    Interval in1[] = {{1.0, 2.0}, {3.0, 4.0}};
    Union_Of_Intervals union1 = {in1, 2};
    Interval exp1[] = {{1.0, 2.0}, {3.0, 4.0}};
    Union_Of_Intervals expected1 = {exp1, 2};
    
    Union_Of_Intervals actual1 = trim_union(union1, 0.0, 5.0);
    assert_union_equal(expected1, actual1);
    delete_union(actual1);

    // test
    Interval in2[] = {{0.0, 3.0}, {5.0, 10.0}};
    Union_Of_Intervals union2 = {in2, 2};
    Interval exp2[] = {{2.0, 3.0}, {5.0, 8.0}};
    Union_Of_Intervals expected2 = {exp2, 2};
    
    Union_Of_Intervals actual2 = trim_union(union2, 2.0, 8.0);
    assert_union_equal(expected2, actual2);
    delete_union(actual2);

    // test
    Interval in3[] = {{-5.0, -2.0}, {8.0, 10.0}};
    Union_Of_Intervals union3 = {in3, 2};
    
    Union_Of_Intervals actual3 = trim_union(union3, 0.0, 5.0);
    assert(actual3.intervals == NULL);
    assert(actual3.n == 0);

    // test
    Interval in4[] = {{-10.0, 10.0}};
    Union_Of_Intervals union4 = {in4, 1};
    Interval exp4[] = {{-3.66, 3.66}};
    Union_Of_Intervals expected4 = {exp4, 1};
    
    Union_Of_Intervals actual4 = trim_union(union4, -3.66, 3.66);
    assert_union_equal(expected4, actual4);
    delete_union(actual4);

    // test
    Interval in5[] = {{-INFINITY, 2.0}, {4.0, INFINITY}};
    Union_Of_Intervals union5 = {in5, 2};
    Interval exp5[] = {{0.0, 2.0}, {4.0, 5.0}};
    Union_Of_Intervals expected5 = {exp5, 2};
    
    Union_Of_Intervals actual5 = trim_union(union5, 0.0, 5.0);
    assert_union_equal(expected5, actual5);
    delete_union(actual5);

    // test
    Union_Of_Intervals union6 = {NULL, 0};
    Union_Of_Intervals actual6 = trim_union(union6, -5.0, 5.0);
    assert(actual6.intervals == NULL);
    assert(actual6.n == 0);

    printf("trim_union ok \n");
}


int main() {
    test_compare();
    test_dist_point_point();
    test_unit_vector();
    test_ray_through_points();
    test_unit_vector_with_oriented_angle();
    test_oriented_angle_of_ray();
    test_ray_intersection_with_y_0();
    test_create_union();
    test_circle_coverage_on_y_0();
    test_trim_union();

    return 0;
}