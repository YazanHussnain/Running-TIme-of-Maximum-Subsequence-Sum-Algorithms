#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

/*Define one of Cubic Algorithm, Quadratic Algorithm, NlogNAlgorithm, or
Linear Algorithm to get that one algorithm compiled*/

#define CubicAlgorithm

#ifdef CubicAlgorithm // O(N^3) Algorithm

int MaxSubsequenceSum(const int A[], int N)
{
	int ThisSum, MaxSum, i, j,k;
	MaxSum = 0;
	for (i = 0; i < N; i++)
	{
		for (j = i; j < N; j++)
		{
			ThisSum = 0;
			for (k = i; k < N; k++)
			{
				ThisSum += A[k];
			}
			if (ThisSum > MaxSum)
				MaxSum = ThisSum;
		}
	}
	return MaxSum;
}

#endif

#ifdef QuadraticAlgorithm // O(N^2) Algorithm

int MaxSubsequenceSum(const int A[], int N)
{
	int ThisSum, MaxSum, i, j;
	MaxSum = 0;
	for (i = 0; i < N; i++)
	{
		ThisSum = 0;
		for (j = i; j < N; j++)
		{
			ThisSum += A[j];
		}
		if (ThisSum > MaxSum)
			MaxSum = ThisSum;
	}
	return MaxSum;
}

#endif

#ifdef NlogNAlgorithm // O(N log(N)) Algorithm

static int Max3(int A, int B, int C)
{
	return A > B ? A > C ? A : C : B > C ? B : C;
}

static int MaxSubSum(const int A[], int Left, int Right)
{
	int MaxLeftSum, MaxRightSum;
	int MaxLeftBorderSum, MaxRightBorderSum;
	int LeftBorderSum, RightBorderSum;
	int Center, i;

	if (Left == Right) //Base Case
		if (A[Left > 0])
			return A[Left];
		else
			return 0;

	Center = (Left + Right) / 2;
	MaxLeftSum = MaxSubSum(A, Left, Center);
	MaxRightSum = MaxSubSum(A, Center + 1, Right);
	MaxLeftBorderSum = 0;
	LeftBorderSum = 0;

	for (i = Center; i >= Left; i--)
	{
		LeftBorderSum += A[i];
		if (LeftBorderSum > MaxLeftBorderSum)
			MaxLeftBorderSum = LeftBorderSum;
	}

	MaxRightBorderSum = 0;
	RightBorderSum = 0;

	for (i = Center + 1; i <= Right; i++)
	{
		RightBorderSum += A[i];
		if (RightBorderSum > MaxRightBorderSum)
			MaxRightBorderSum = RightBorderSum;
	}
	return Max3(MaxLeftSum, MaxRightSum, MaxLeftBorderSum + MaxRightBorderSum);
}

int MaxSubsequenceSum(const int A[], int N)
{
	return MaxSubSum(A, 0, N - 1);
}

#endif

#ifdef LinearAlgorithm // O(N) Algorithm

int MaxSubsequenceSum(const int A[], int N)
{
	int ThisSum, MaxSum, j;
	ThisSum = 0;
	MaxSum = 0;

	for (j = 0; j < N; j++)
	{
		ThisSum += A[j];
		if (ThisSum > MaxSum)
			MaxSum = ThisSum;
		else if (ThisSum < 0)
			ThisSum = 0;
	}

	return MaxSum;
}

#endif

#define 	TOTAL_SIZE 	100000000
#define 	N_START		10
#define 	N_END		(N_START*1000)

int main() {

	LARGE_INTEGER start_time, end_time, elapsed_time, frequency;

	double run_time;
	int roll_no = 72, sum;
	int *data = malloc(TOTAL_SIZE*sizeof(int));
	QueryPerformanceFrequency(&frequency);

	for (int N = N_START; N <= N_END; N *= 10) {

		srand(roll_no);
		for (int k = 0; k < N; ++k) {
			data[k] = rand() % 10;
		}

		QueryPerformanceCounter(&start_time);

		sum = MaxSubsequenceSum(data, N);

		QueryPerformanceCounter(&end_time);
		elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
		run_time = ((double) elapsed_time.QuadPart) / frequency.QuadPart;

		printf("N = %d, \ttime = %g s, \tsum = %d\n", N, run_time, sum);
	}

	free(data);

	return 0;
}
