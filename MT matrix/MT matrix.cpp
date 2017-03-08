#include <vector>
#include <thread>
#include <cmath>
#include "MT matrix.h"

using namespace std;

void mul_aux(
	double** M1, size_t m1_height, size_t m1_width, 
	double** M2, size_t m2_height, size_t m2_width, size_t I1, size_t I2, double** out)
{
	for (size_t k = I1; k < I2; k++)
	{
		for (size_t j = 0; j < m2_width; j++)
		{
			out[k][j] = 0;
			for (size_t i = 0; i < m1_width; i++)
				out[k][j] += M1[k][i] * M2[i][j];
		}
	}
}

double** mt_matrix_mul(double** M1, size_t m1_height, size_t m1_width, double** M2, size_t m2_height, size_t m2_width, size_t max_threads)
{
	if (m1_width != m2_height)
		return nullptr;

	vector<thread*> thread_array(max_threads, nullptr);
	int thread_cnt = 0;

	double** out = new double*[m1_height];
	for (size_t i = 0; i < m1_height; i++)
		out[i] = new double[m2_width];
	
	const int lines_per_thread = ceilf((double)m1_height / (double)max_threads);
	for (size_t i = 0; i < m1_height; i += lines_per_thread)
	{
		thread_array[thread_cnt] = new thread(
			mul_aux, M1, m1_height, m1_width, M2, m2_height, m2_width, 
			i, (int)fmin(i + lines_per_thread, m1_height), out);
		thread_cnt++;
	}

	for (int i = 0; i < thread_cnt; i++)
	{
		thread_array[i]->join();
		delete thread_array[i];
	}
	return out;
}

double ** st_matrix_mul(double ** M1, size_t m1_height, size_t m1_width, double ** M2, size_t m2_height, size_t m2_width)
{
	if (m1_width != m2_height)
		return nullptr;

	double** out = new double*[m1_height];
	for (size_t i = 0; i < m1_height; i++)
	{
		out[i] = new double[m2_width];
		for (size_t j = 0; j < m2_width; j++)
		{
			out[i][j] = 0;
			for (size_t k = 0; k < m1_width; k++)
				out[i][j] += M1[i][k] * M2[k][j];
		}
	}
	return out;
}
