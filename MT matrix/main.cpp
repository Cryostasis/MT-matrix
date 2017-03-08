#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "MT matrix.h"

using namespace std;

template <typename T>
T** rand_matrix(size_t sz1, size_t sz2)
{
	T** out = new T*[sz1];
	for (size_t i = 0; i < sz1; i++)
	{
		out[i] = new T[sz2];
		for (size_t j = 0; j < sz2; j++)
			out[i][j] = rand() % 10 - 5;
	}
	return out;
}

void print_matrix(double** M, size_t h, size_t w)
{
	for (size_t i = 0; i < h; i++)
	{
		for (size_t j = 0; j < w; j++)
			cout << M[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
}

const int A_H = 300;
const int A_W = 4000;

const int B_H = 4000;
const int B_W = 500;

int main()
{
	srand((unsigned int)time(NULL));

	double** A = rand_matrix<double>(A_H, A_W);
	double** B = rand_matrix<double>(B_H, B_W);

	chrono::time_point<chrono::system_clock> t1 = chrono::system_clock::now();
	double** C = mt_matrix_mul(A, A_H, A_W, B, B_H, B_W, 4);
	chrono::time_point<chrono::system_clock> t2 = chrono::system_clock::now();
	cout << t2.time_since_epoch().count() - t1.time_since_epoch().count() << endl;

	t1 = chrono::system_clock::now();
	double** D = st_matrix_mul(A, A_H, A_W, B, B_H, B_W);
	t2 = chrono::system_clock::now();
	cout << t2.time_since_epoch().count() - t1.time_since_epoch().count() << endl;

	//print_matrix(A, A_H, A_W);
	//print_matrix(B, B_H, B_W);
	//print_matrix(C, A_H, B_W);
	//print_matrix(D, A_H, B_W);
	system("pause");
}