# Changelog


### Added [2026-06-08]
- `Point`, `Vector`, `Line`, `Ray`, `Circle`, `Interval`, `Union_Of_Intervals` -
  podstawowe struktury danych modułu geometrycznego
- `compare()` - porównywanie doubli z tolerancją EPS
- `dist_point_point()` - odległość między dwoma punktami
- `unit_vector()` - jednostkowy wektor kierunkowy między dwoma punktami
- `unit_vector_with_oriented_angle()` - wektor jednostkowy z kąta skierowanego
- `oriented_angle_of_ray()` - kąt skierowany promienia
- `ray_through_points()` - promień przez dwa punkty
- `ray_with_oriented_angle()` - promień z punktu i kąta
- `ray_intersection_with_y_0()` - przecięcie promienia z prostą y=0
- `create_union()` - unia przedziałów (tworzenie sumy rozłącznych przedziałów)
- `trim_union()` - przycinanie unii przedziałów do zadanego zakresu
- `circle_coverage_on_y_0()` - rzut zasłony okręgu na linię y=0 z punktu obserwatora
- `delete_union()` - zwolnienie pamięci unii przedziałów
- Testy jednostkowe dla istotnych funkcji geometrycznych (`test_geometry.c`)

### Added [2026-06-09]
- `subtract_union_from_interval()` - odjęcie od przedziału sumy przedziałów
- `biggest_interval()` - najdłuższy przedział z sumy przedziałów
- `is_point_in_union()` - sprawdzenie czy punkt nalezy do sumy przedziałów
- `Positions` - struktura opisujaca obiekty na boisku
- `create_positions()` - tworzy strukture 
- `delete_positions()` - usuwa strukture
- `choose_target()` - wybiera cel biorac pod uwage sytuacje na boisku
- `is_goal()` - weryfikuje czy strzal zakonczyl sie golem
- `generate_normal_zero_mean()` - generuje liczbe pseudo losowa z rozkladu normalnego o zadanej wariancji i wartosci oczekiwanej rownej 0

