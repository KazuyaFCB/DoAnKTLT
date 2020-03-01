//LEVEL 1: SẮP XẾP MẢNG VỚI SỐ NGUYÊN KIỂU INT

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <math.h>

unsigned long long isort, spg, spss;

void GhiMangKQ(FILE *f, int a[], int length);
void Swap(int &a, int &b);
void InsertionSort(int a[], int length);
void ShellSort(int a[], int length);
void BubbleSort(int a[], int length);
void ShakeSort(int a[], int length);
int* MergeSort(int a[], int l, int r);
void QuickSort(int* &a, int l, int r);
void Shift(int a[], int length, int i);
void HeapSort(int a[], int length);
void RadixSort(int a[], int length);
void TaoDuLieu(int *&a, int length);
void GhiMangKQ(FILE *f, int a[], int length);
void ThongKe();

void Swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

void InsertionSort(int a[], int length)
{
	int i, j, key;
	for (i = 1; i < length; i++)
	{
		key = a[i];
		spg++;
		spss++;
		for (j = i - 1; j >= 0 && a[j] > key; j--)
		{
			a[j + 1] = a[j];
			spg++;
			spss++;
		}
		a[j + 1] = key;
		spg++;
	}
}

void ShellSort(int a[], int length)
{
	int knuth = 1, i, j, key;
	while (knuth < length / 3)
		knuth = knuth * 3 + 1;
	while (knuth >= 1)
	{
		for (i = knuth; i < length; i++)
		{
			key = a[i];
			spg++;
			spss++;
			for (j = i - knuth; j >= 0 && a[j] > key; j -= knuth)
			{
				a[j + knuth] = a[j];
				spg++;
				spss++;
			}
			a[j + knuth] = key;
			spg++;
		}
		knuth /= 2;
	}
}

void BubbleSort(int a[], int length)
{
	int i, j, t;
	for (i = 0; i < length - 1; i++)
	{
		for (j = length - 1; j > i; j--)
		{
			spss++;
			if (a[j] < a[j - 1])
			{
				spg += 3;
				t = a[j];
				a[j] = a[j - 1];
				a[j - 1] = t;
			}
		}
	}
}

void ShakeSort(int a[], int length)
{
	int left, right, k = 1, j, t;
	left = 1;
	right = length - 1;
	while (left <= right)
	{
		for (j = right; j >= left; j--)
		{
			spss++;
			if (a[j] < a[j - 1])
			{
				spg += 3;
				t = a[j];
				a[j] = a[j - 1];
				a[j - 1] = t;
				k = j;
			}
		}
		left = k + 1;
		for (j = left; j <= right; j++)
		{
			spss++;
			if (a[j] < a[j - 1])
			{
				spg += 3;
				t = a[j];
				a[j] = a[j - 1];
				a[j - 1] = t;
				k = j - 1;
			}
		}
		right = k;
	}
}

int* MergeSort(int a[], int l, int r)
{
	int i, j, mid, *ret, k = 0, *left, *right;
	ret = (int*)malloc((r - l + 2)*sizeof(int));
	if (l == r)
	{
		spg++;
		ret[0] = a[l];
		return ret;
	}
	mid = (l + r) / 2;
	spg += 2;
	left = MergeSort(a, l, mid);
	right = MergeSort(a, mid + 1, r);
	left[mid - l + 1] = INT_MAX;
	right[r - mid] = INT_MAX;
	for (i = 0, j = 0; k < r - l + 1; k++)
	{
		spss++;
		if (left[i] <= right[j])
		{
			spg++;
			ret[k] = left[i];
			i++;
		}
		else
		{
			spg++;
			ret[k] = right[j];
			j++;
		}
	}
	free(left);
	free(right);
	return ret;
}

void QuickSort(int* &a, int l, int r)
{
	int pivot, i, j, x;
	if (l <= r)
	{
		pivot = l + (r - l) / 2;
		spg++;
		x = a[pivot];
		i = l;
		j = r;
		while (i <= j)
		{
			spss += 2;
			while (a[i] < x)
			{
				spss++;
				i++;
			}
			while (a[j] > x)
			{
				spss++;
				j--;
			}
			if (i <= j)
			{
				spg += 3;
				Swap(a[i], a[j]);
				i++;
				j--;
			}
		}
		if (l < j)
			QuickSort(a, l, j);
		if (r > i)
			QuickSort(a, i, r);
	}
}
//Di chuyển node thứ i đến đúng vị trí của nó
void Shift(int a[], int length, int i)
{
	int imax;
	while (1)
	{
		if (2 * i + 2 < length)
		{
			spss++;
			imax = (a[2 * i + 1] >= a[2 * i + 2])*(2 * i + 1) + (a[2 * i + 1] < a[2 * i + 2])*(2 * i + 2);
		}
		else
		{
			if (2 * i + 1 < length)
			{
				imax = 2 * i + 1;
			}
			else
				break;
		}
		spss++;
		if (a[i] < a[imax])
		{
			spg += 3;
			Swap(a[i], a[imax]);
			i = imax;
		}
		else
			break;
	}
}

void HeapSort(int a[], int length)
{
	int i, imax;
	if (length == 1)
		return;
	i = length / 2 - 1;
	if (2 * i + 2 < length)
	{
		spss++;
		imax = (a[2 * i + 1] >= a[2 * i + 2])*(2 * i + 1) + (a[2 * i + 1] < a[2 * i + 2])*(2 * i + 2);
	}
	else
		imax = 2 * i + 1;
	spss++;
	if (a[imax] > a[i])
	{
		spg += 3;
		Swap(a[imax], a[i]);
	}
	i--;
	for (; i >= 0; i--)
	{
		spss += 2;
		imax = (a[2 * i + 1] >= a[2 * i + 2])*(2 * i + 1) + (a[2 * i + 1] < a[2 * i + 2])*(2 * i + 2);
		if (a[imax] > a[i])
		{
			spg += 3;
			Swap(a[imax], a[i]);
			Shift(a, length, imax);
		}
	}
	spg += 3;
	Swap(a[0], a[length - 1]);
	length--;
	while (length > 1)
	{
		Shift(a, length, 0);
		spg += 3;
		Swap(a[0], a[length - 1]);
		length--;
	}
}

void RadixSort(int a[], int length)
{
	//Mảng tempt với dòng 0,1,2...,18 là các lô ứng với các chữ số -9,-8,...,0,1,2...,9. Cột 0 là số pt trong lô đó, cột 1,2... chứa các pt
	int **tempt, i, b = 1, j, k;
	tempt = (int**)malloc(19 * sizeof(int*));
	for (i = 0; i < 19; i++)
		*(tempt + i) = (int*)malloc((length + 1)*sizeof(int));
	while (1)
	{
		spg += 19;
		for (i = 0; i < 19; i++)
			tempt[i][0] = 0;
		//Xếp các pt vào các lô 0,1,2,...,18
		spg += length;
		for (i = 0; i < length; i++)
		{
			tempt[((a[i] / b) % 10) + 9][tempt[((a[i] / b) % 10) + 9][0] + 1] = a[i];
			tempt[((a[i] / b) % 10) + 9][0]++;
		}
		//Đk dừng khi lô 0 chứa tất cả các pt trong mảng
		if (tempt[9][0] == length)
			break;
		//Xếp lại các pt trong lô vào mảng chính
		k = 0;
		spg += length;
		for (i = 0; i < 19; i++)
		{
			for (j = 1; j <= tempt[i][0]; j++)
			{
				a[k] = tempt[i][j];
				k++;
			}
		}
		b *= 10;
	}
	for (i = 0; i < 19; i++)
		free(*(tempt + i));
	free(tempt);
}

void TaoDuLieu(int *&a, int length)
{
	FILE *f;
	time_t t;
	char filename[15];
	int sochuso, minus, s = 0, i, j = 0;
	a = (int*)malloc(length*sizeof(int));
	_itoa(length, filename, 10);
	strcat(filename, ".txt");
	srand((unsigned)time(&t));
	for (i = 0; i < length; i++)
	{
		minus = 2 * (rand() % 2);
		minus--;
		a[i] = (rand() << (rand() % 16))*minus + (rand() % 2);
	}
	f = fopen(filename, "w+");
	GhiMangKQ(f, a, length);
	fclose(f);
}

void GhiMangKQ(FILE *f, int a[], int length)
{
	for (int i = 0; i < length; i++)
		fprintf(f, "%15d", a[i]);
}

void ThongKe()
{
	int *a, length, *tempt, *mergeReturn;
	FILE *f;
	clock_t start, end;
	double total;
	char filename[35], *thuattoan[8];
	thuattoan[0] = "InsertionSort";
	thuattoan[1] = "ShellSort";
	thuattoan[2] = "BubbleSort";
	thuattoan[3] = "ShakeSort";
	thuattoan[4] = "MergeSort";
	thuattoan[5] = "QuickSort";
	thuattoan[6] = "HeapSort";
	thuattoan[7] = "RadixSort";
	length = 100;
	while (length <= 10000)
	{
		isort = 0;
		TaoDuLieu(tempt, length);
		a = (int*)malloc(length*sizeof(int));
		f = fopen("ThongKe.txt", "a");
		fprintf(f, "Truong hop %d phan tu:\n\n", length);
		fclose(f);
		while (isort < 8)
		{
			total = 0; 
			for (int i = 0; i < length; i++)
				a[i] = tempt[i];
			spg = spss = 0;
			start = clock();
			if (isort == 0)
				InsertionSort(a, length);
			else if (isort == 1)
				ShellSort(a, length);
			else if (isort == 2)
				BubbleSort(a, length);
			else if (isort == 3)
				ShakeSort(a, length);
			else if (isort == 4)
				mergeReturn = MergeSort(a, 0, length - 1);
			else if (isort == 5)
				QuickSort(a, 0, length - 1);
			else if (isort == 6)
				HeapSort(a, length);
			else if (isort == 7)
				RadixSort(a, length);
			end = clock();
			total = (double)(end - start) / CLOCKS_PER_SEC;
			_itoa(length, filename, 10);
			strcat(filename, thuattoan[isort]);
			strcat(filename, "MangKQ.txt");
			f = fopen(filename, "w+");
			if (isort == 4)
			{
				GhiMangKQ(f, mergeReturn, length);
				free(mergeReturn);
			}
			else
				GhiMangKQ(f, a, length);
			fclose(f);
			fopen("ThongKe.txt", "a");
			fprintf(f, "Thuat toan %s:\n", thuattoan[isort]);
			fprintf(f, "So phep gan: %llu\nSo phep so sanh: %llu\nThoi gian chay: %.6lf giay\n\n", spg , spss , total);
			fclose(f);
			isort++;
		}
		length *= 10;
		free(tempt);
		free(a);
	}
}

void main()
{
	ThongKe();
	system("pause");
}