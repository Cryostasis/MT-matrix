#pragma once

double** mt_matrix_mul(double** M1, size_t m1_height, size_t m1_width, double** M2, size_t m2_height, size_t m2_width, size_t max_threads);
double** st_matrix_mul(double** M1, size_t m1_height, size_t m1_width, double** M2, size_t m2_height, size_t m2_width);

