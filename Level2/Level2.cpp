//LEVEL 2: SẮP XẾP MẢNG VỚI SỐ NGUYÊN CỰC LỚN
//1 số nguyên cực lớn được cấu tạo bởi mảng kiểu unsigned long long 
//với pt 0 là dấu của số đó (0 là âm, 2 là dương)
//pt 1 là 1 số nguyên có số chữ số <=19, (các chữ số trong số nguyên đó ứng với trong số nguyên ban đầu)
//pt 2,3,4... (nếu có) là 1 số nguyên có đúng 19 chữ số (có thể gồm nhiều số 0 ở đầu), (các chữ số trong số nguyên đó ứng với trong số nguyên ban đầu)
//ngoài ra còn có 1 mảng char riêng lưu số chữ số của các số nguyên cực lớn

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <math.h>

//số chữ số max trong số nguyên cực lớn, số pt max (mỗi pt là 1 số nguyên có <=19 chữ số như đã ghi ở trên), số chữ số max trong 1 pt
int SOCHUSOMAX = 114, SOPHANTUMAX = 7, SOCHUSOMAXTRONG1PHANTU = 19;
unsigned long long spg, spss;
int isort;
unsigned long long IntMax[1] = { 2 };

void Swap(unsigned long long *&a, unsigned long long *&b, char &sochuso_a, char &sochuso_b);
int SoSanh(unsigned long long *a, unsigned long long *b, char sochuso_a, char sochuso_b);
void InsertionSort(unsigned long long *a[], int length, char sochuso[]);
void ShellSort(unsigned long long *a[], int length, char sochuso[]);
void BubbleSort(unsigned long long *a[], int length, char sochuso[]);
void ShakeSort(unsigned long long *a[], int length, char sochuso[]);
void MergeSort(unsigned long long *a[], char sochuso[], int l, int r, unsigned long long **&ret, char *&sochuso_ret);
void QuickSort(unsigned long long *a[], char sochuso[], int l, int r);
void Shift(unsigned long long *a[], char sochuso[], int length, int i);
void HeapSort(unsigned long long *a[], char sochuso[], int length);
int Lay_Chu_So(unsigned long long *a, char sochuso, int order);
void RadixSort(unsigned long long **&a, char *&sochuso, int length);
void TaoDuLieu(unsigned long long **&a, int length, char *&sochuso);
void GhiMangKQ(FILE *f, unsigned long long* a[], int length, char sochuso[]);
void ThongKe();

void Swap(unsigned long long *&a, unsigned long long *&b, char &sochuso_a, char &sochuso_b)
{
	unsigned long long *t;
	char sochuso_t;
	t = a;
	sochuso_t = sochuso_a;
	a = b;
	sochuso_a = sochuso_b;
	b = t;
	sochuso_b = sochuso_t;
}

int SoSanh(unsigned long long *a, unsigned long long *b, char sochuso_a, char sochuso_b)
{
	int p, q;
	p = a[0]; p--;
	q = b[0]; q--;
	if (p * q == -1)
	{
		if (p == 1)
			return 1;
		return -1;
	}
	if (sochuso_a > sochuso_b)
		return p;
	if (sochuso_a < sochuso_b)
		return -p;
	int spt = (sochuso_a - 1) / SOCHUSOMAXTRONG1PHANTU + 1;
	for (int i = 1; i <= spt; i++)
	{
		if (a[i] > b[i])
			return p;
		else if (a[i] < b[i])
			return -p;
	}
	return 0;
}

void InsertionSort(unsigned long long *a[], int length, char sochuso[])
{
	int i, j, p, q, result = 0;
	unsigned long long *key;
	char sochusokey;
	for (i = 1; i < length; i++)
	{
		key = a[i];
		sochusokey = sochuso[i];
		spg++;
		for (j = i - 1;; j--)
		{
			if (j < 0)
				break;
			spss++;
			//So sánh a[j] và key. Dùng hàm sẽ lâu nên viết trực tiếp
			while (1)
			{
				p = a[j][0]; p--;
				q = key[0]; q--;
				if (p * q == -1)
				{
					if (p == 1)
					{
						result = 1;
						break;
					}
					result = -1;
					break;
				}
				if (sochuso[j] > sochusokey)
				{
					result = p;
					break;
				}
				if (sochuso[j] < sochusokey)
				{
					result = -p;
					break;
				}
				int spt = (sochuso[j] - 1) / SOCHUSOMAXTRONG1PHANTU + 1;
				for (int ii = 1; ii <= spt; ii++)
				{
					if (a[j][ii] > key[ii])
					{
						result = p;
						break;
					}
					else if (a[j][ii] < key[ii])
					{
						result = -p;
						break;
					}
				}
				break;
			}
			//a[j] <= key thì break
			if (result <= 0)
				break;
			a[j + 1] = a[j];
			sochuso[j + 1] = sochuso[j];
			spg++;
		}
		a[j + 1] = key;
		sochuso[j + 1] = sochusokey;
		spg++;
	}
}

void ShellSort(unsigned long long *a[], int length, char sochuso[])
{
	int knuth = 1, i, j;
	unsigned long long *key;
	char sochusokey;
	while (knuth < length / 3)
		knuth = knuth * 3 + 1;
	while (knuth >= 1)
	{
		for (i = knuth; i < length; i++)
		{
			key = a[i];
			sochusokey = sochuso[i];
			spg++;
			spss++;
			for (j = i - knuth; j >= 0 && SoSanh(a[j], key, sochuso[j], sochusokey) > 0; j -= knuth)
			{
				a[j + knuth] = a[j];
				sochuso[j + knuth] = sochuso[j];
				spg++;
				spss++;
			}
			a[j + knuth] = key;
			sochuso[j + knuth] = sochusokey;
			spg++;
		}
		knuth /= 2;
	}
}

void BubbleSort(unsigned long long *a[], int length, char sochuso[])
{
	int i, j, result = 0, p, q;
	unsigned long long *t;
	char sochuso_t;
	for (i = 0; i < length - 1; i++)
	{
		for (j = length - 1; j > i; j--)
		{
			spss++;
			// So sánh a[j], a[j-1]. //Dùng hàm sẽ chạy lâu nên viết trực tiếp
			while (1)
			{
				p = a[j][0]; p--;
				q = a[j - 1][0]; q--;
				if (p * q == -1)
				{
					if (p == 1)
					{
						result = 1;
						break;
					}
					result = -1;
					break;
				}
				if (sochuso[j] > sochuso[j - 1])
				{
					result = p;
					break;
				}
				if (sochuso[j] < sochuso[j - 1])
				{
					result = -p;
					break;
				}
				int spt = (sochuso[j] - 1) / SOCHUSOMAXTRONG1PHANTU + 1;
				for (int i = 1; i <= spt; i++)
				{
					if (a[j][i] > a[j - 1][i])
					{
						result = p;
						break;
					}
					else if (a[j][i] < a[j - 1][i])
					{
						result = -p;
						break;
					}
				}
				break;
			}
			if (result < 0)
			{
				spg += 3;
				t = a[j];
				sochuso_t = sochuso[j];
				a[j] = a[j - 1];
				sochuso[j] = sochuso[j - 1];
				a[j - 1] = t;
				sochuso[j - 1] = sochuso_t;
			}
		}
	}
}

void ShakeSort(unsigned long long *a[], int length, char sochuso[])
{
	int left, right, k = 1, j, p, q, result = 0;
	unsigned long long *t;
	char sochuso_t;
	left = 1;
	right = length - 1;
	while (left <= right)
	{
		for (j = right; j >= left; j--)
		{
			spss++;
			//So sánh a[j] và a[j-1]. Dùng hàm sẽ lâu nên so sánh trực tiếp
			while (1)
			{
				p = a[j][0]; p--;
				q = a[j - 1][0]; q--;
				if (p * q == -1)
				{
					if (p == 1)
					{
						result = 1;
						break;
					}
					result = -1;
					break;
				}
				if (sochuso[j] > sochuso[j - 1])
				{
					result = p;
					break;
				}
				if (sochuso[j] < sochuso[j - 1])
				{
					result = -p;
					break;
				}
				int spt = (sochuso[j] - 1) / SOCHUSOMAXTRONG1PHANTU + 1;
				for (int i = 1; i <= spt; i++)
				{
					if (a[j][i] > a[j - 1][i])
					{
						result = p;
						break;
					}
					else if (a[j][i] < a[j - 1][i])
					{
						result = -p;
						break;
					}
				}
				break;
			}
			if (result < 0)
			{
				spg += 3;
				t = a[j];
				sochuso_t = sochuso[j];
				a[j] = a[j - 1];
				sochuso[j] = sochuso[j - 1];
				a[j - 1] = t;
				sochuso[j - 1] = sochuso_t;
				k = j;
			}
		}
		left = k + 1;
		for (j = left; j <= right; j++)
		{
			spss++;
			//So sánh a[j] và a[j-1]. Dùng hàm sẽ lâu nên so sánh trực tiếp
			while (1)
			{
				p = a[j][0]; p--;
				q = a[j - 1][0]; q--;
				if (p * q == -1)
				{
					if (p == 1)
					{
						result = 1;
						break;
					}
					result = -1;
					break;
				}

				if (sochuso[j] > sochuso[j - 1])
				{
					result = p;
					break;
				}
				if (sochuso[j] < sochuso[j - 1])
				{
					result = -p;
					break;
				}
				int spt = (sochuso[j] - 1) / SOCHUSOMAXTRONG1PHANTU + 1;
				for (int i = 1; i <= spt; i++)
				{
					if (a[j][i] > a[j - 1][i])
					{
						result = p;
						break;
					}
					else if (a[j][i] < a[j - 1][i])
					{
						result = -p;
						break;
					}
				}
				break;
			}
			if (result < 0)
			{
				spg += 3;
				t = a[j];
				sochuso_t = sochuso[j];
				a[j] = a[j - 1];
				sochuso[j] = sochuso[j - 1];
				a[j - 1] = t;
				sochuso[j - 1] = sochuso_t;
				k = j - 1;
			}
		}
		right = k;
	}
}

//Riêng MergeSort thì mảng a[] ban đầu ko bị thay đổi, mảng ret là mảng đc sắp xếp (các pt mảng a đc gán cho mảng ret) 
void MergeSort(unsigned long long *a[], char sochuso[], int l, int r, unsigned long long **&ret, char *&sochuso_ret)
{
	int i, j, mid, k = 0;
	unsigned long long **left, **right;
	char *sochuso_left, *sochuso_right;
	ret = (unsigned long long**)malloc((r - l + 2)*sizeof(unsigned long long*));
	sochuso_ret = (char*)malloc((r - l + 2)*sizeof(char));
	if (l == r)
	{
		spg++;
		ret[0] = a[l];
		sochuso_ret[0] = sochuso[l];
		return;
	}
	mid = (l + r) / 2;
	spg += 2;
	MergeSort(a, sochuso, l, mid, left, sochuso_left);
	MergeSort(a, sochuso, mid + 1, r, right, sochuso_right);
	left[mid - l + 1] = IntMax;
	sochuso_left[mid - l + 1] = SOCHUSOMAX + 1;
	right[r - mid] = IntMax;
	sochuso_right[r - mid] = SOCHUSOMAX + 1;
	for (i = 0, j = 0; k < r - l + 1; k++)
	{
		spss++;
		if (SoSanh(left[i], right[j], sochuso_left[i], sochuso_right[j]) <= 0)
		{
			spg++;
			ret[k] = left[i];
			sochuso_ret[k] = sochuso_left[i];
			i++;
		}
		else
		{
			spg++;
			ret[k] = right[j];
			sochuso_ret[k] = sochuso_right[j];
			j++;
		}
	}
	free(left);
	free(right);
	free(sochuso_left);
	free(sochuso_right);
}

void QuickSort(unsigned long long *a[], char sochuso[], int l, int r)
{
	int pivot, i, j;
	unsigned long long *key;
	char sochuso_key;
	if (l <= r)
	{
		pivot = (l + r) / 2;
		key = (unsigned long long*)malloc(SOPHANTUMAX*sizeof(unsigned long long));
		spg++;
		sochuso_key = sochuso[pivot];
		for (i = 0; i <= (sochuso_key - 1) / SOCHUSOMAXTRONG1PHANTU + 1; i++)
			key[i] = a[pivot][i];
		i = l;
		j = r;
		while (i <= j)
		{
			spss += 2;
			while (SoSanh(a[i], key, sochuso[i], sochuso_key) < 0)
			{
				spss++;
				i++;
			}
			while (SoSanh(a[j], key, sochuso[j], sochuso_key) > 0)
			{
				spss++;
				j--;
			}
			if (i <= j)
			{
				spg += 3;
				Swap(a[i], a[j], sochuso[i], sochuso[j]);
				i++;
				j--;
			}
		}
		if (l < j)
			QuickSort(a, sochuso, l, j);
		if (r > i)
			QuickSort(a, sochuso, i, r);
		free(key);
	}
}

void Shift(unsigned long long *a[], char sochuso[], int length, int i)
{
	int imax;
	unsigned long long *t;
	char sochuso_t;
	while (1)
	{
		if (2 * i + 2 < length)
		{
			spss++;
			if (SoSanh(a[2 * i + 1], a[2 * i + 2], sochuso[2 * i + 1], sochuso[2 * i + 2]) >= 0)
				imax = 2 * i + 1;
			else
				imax = 2 * i + 2;
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
		if (SoSanh(a[i], a[imax], sochuso[i], sochuso[imax]) < 0)
		{
			spg += 3;
			Swap(a[i], a[imax], sochuso[i], sochuso[imax]);
			i = imax;
		}
		else
			break;
	}
}

void HeapSort(unsigned long long *a[], char sochuso[], int length)
{
	int i, imax;
	if (length == 1)
		return;
	//Tạo cây
	i = length / 2 - 1;
	//Chỉ phần tử này có thể có 1 hoặc 2 node con nên xét riêng, các pt trước phần tử này luôn có 2 node con nên xét chung
	if (2 * i + 2 < length)
	{
		spss++;
		if (SoSanh(a[2 * i + 1], a[2 * i + 2], sochuso[2 * i + 1], sochuso[2 * i + 2]) >= 0)
			imax = 2 * i + 1;
		else
			imax = 2 * i + 2;
	}
	else
		imax = 2 * i + 1;
	spss++;
	if (SoSanh(a[imax], a[i], sochuso[imax], sochuso[i]) > 0)
	{
		spg += 3;
		Swap(a[imax], a[i], sochuso[imax], sochuso[i]);
	}
	i--;
	for (; i >= 0; i--)
	{
		spss += 2;
		if (SoSanh(a[2 * i + 1], a[2 * i + 2], sochuso[2 * i + 1], sochuso[2 * i + 2]) >= 0)
			imax = 2 * i + 1;
		else
			imax = 2 * i + 2;
		if (SoSanh(a[imax], a[i], sochuso[imax], sochuso[i]) > 0)
		{
			spg += 3;
			Swap(a[imax], a[i], sochuso[imax], sochuso[i]);
			Shift(a, sochuso, length, imax);
		}
	}
	spg += 3;
	Swap(a[0], a[length - 1], sochuso[0], sochuso[length - 1]);
	length--;
	while (length > 1)
	{
		i = 0;
		Shift(a, sochuso, length, 0);
		spg += 3;
		Swap(a[0], a[length - 1], sochuso[0], sochuso[length - 1]);
		length--;
	}
}

int Lay_Chu_So(unsigned long long *a, char sochuso, int order)
{
	if (order < 1)
		return 0;
	unsigned long long x;
	int index, i, phanle, j, digit;
	phanle = sochuso % SOCHUSOMAXTRONG1PHANTU;
	if (phanle != 0 && order <= phanle)
	{
		x = a[1];
		i = order;
		j = phanle;
	}
	else
	{
		index = (order - phanle - 1) / SOCHUSOMAXTRONG1PHANTU + 1 + (phanle != 0);
		x = a[index];
		if ((order - phanle) % SOCHUSOMAXTRONG1PHANTU != 0)
			i = (order - phanle) % SOCHUSOMAXTRONG1PHANTU;
		else
			i = SOCHUSOMAXTRONG1PHANTU;
		j = SOCHUSOMAXTRONG1PHANTU;
	}
	while (j >= i)
	{
		digit = x - (x / 10) * 10;
		x = x / 10;
		j--;
	}

	digit = digit*(int)(a[0] - 1);
	return digit;
}

void RadixSort(unsigned long long **&a, char *&sochuso, int length)
{
	int i, b = 1, j, k, *sophantutronglo, diff = 0, digit, l;
	int SO_LO = 19;
	unsigned long long ***tempt;
	char **sochusotempt;
	tempt = (unsigned long long***)malloc(SO_LO * sizeof(unsigned long long**));
	sochusotempt = (char**)malloc(SO_LO * sizeof(char*));
	for (i = 0; i < SO_LO; i++)
	{
		*(tempt + i) = (unsigned long long**)malloc((length + 1)*sizeof(unsigned long long*));
		*(sochusotempt + i) = (char*)malloc((length + 1)*sizeof(char));
		//Riêng Radix thì cần cấp phát chi tiết từng chữ số trong 1 số để lưu, nếu chỉ cấp con trỏ để trỏ thì sẽ bị mất dữ liệu cũ
		for (j = 1; j <= length; j++)
			*(*(tempt + i) + j) = (unsigned long long*)malloc(SOPHANTUMAX * sizeof(unsigned long long));
	}
	sophantutronglo = (int*)malloc(SO_LO * sizeof(int));
	while (1)
	{
		spg += SO_LO;
		for (i = 0; i < SO_LO; i++)
			sophantutronglo[i] = 0;
		//Xếp các pt vào các lô 0,1,2,...,18
		spg += length;
		for (i = 0; i < length; i++)
		{
			digit = Lay_Chu_So(a[i], sochuso[i], (int)sochuso[i] - diff) + 9;
			for (j = 0; j <= (sochuso[i] - 1) / SOCHUSOMAXTRONG1PHANTU + 1; j++)
				tempt[digit][sophantutronglo[digit] + 1][j] = a[i][j];
			sochusotempt[digit][sophantutronglo[digit] + 1] = sochuso[i];
			sophantutronglo[digit]++;
		}
		if (sophantutronglo[9] == length)
			break;
		//Xếp lại các pt trong lô vào mảng chính
		k = 0;
		spg += length;
		for (i = 0; i < SO_LO; i++)
		{
			for (j = 1; j <= sophantutronglo[i]; j++)
			{
				for (l = 0; l <= (sochusotempt[i][j] - 1) / SOCHUSOMAXTRONG1PHANTU + 1; l++)
					a[k][l] = tempt[i][j][l];
				sochuso[k] = sochusotempt[i][j];
				k++;
			}
		}
		diff++;
	}
	for (i = 0; i < SO_LO; i++)
	{
		for (j = 1; j <= length; j++)
			free(*(*(tempt + i) + j));
		free(*(tempt + i));
		free(*(sochusotempt + i));
	}
	free(tempt);
	free(sochusotempt);
	free(sophantutronglo);
}

void TaoDuLieu(unsigned long long **&a, int length, char *&sochuso)
{
	FILE *f;
	time_t t;
	char filename[15];
	int i, minus, r, sophantu, j, k;
	unsigned long long s;
	a = (unsigned long long**)malloc(length*sizeof(unsigned long long*));
	sochuso = (char*)malloc(length*sizeof(char));
	_itoa(length, filename, 10);
	strcat(filename, ".txt");
	srand((unsigned)time(&t));
	for (i = 0; i < length; i++)
	{
		sochuso[i] = rand() % SOCHUSOMAX + 1;
		if (sochuso[i] == 1)
		{
			a[i] = (unsigned long long*)malloc(SOPHANTUMAX * sizeof(unsigned long long));
			a[i][0] = 2 * (rand() % 2);
			if (a[i][0] == 0)
				a[i][1] = (rand() % 9) + 1;
			else
				a[i][1] = rand() % 10;
			continue;
		}
		sophantu = (sochuso[i] - 1) / SOCHUSOMAXTRONG1PHANTU + 1;
		a[i] = (unsigned long long*)malloc(SOPHANTUMAX * sizeof(unsigned long long));
		a[i][0] = 2 * (rand() % 2);

		r = sochuso[i] % SOCHUSOMAXTRONG1PHANTU;
		j = s = 0;
		j = k = 1;
		if (r == 0)
			r = SOCHUSOMAXTRONG1PHANTU;
		s = s * 10 + (rand() % 9) + 1;
		while (j < r)
		{
			s = s * 10 + (rand() % 10);
			j++;
		}
		a[i][1] = s;
		for (k = 2; k <= sophantu; k++)
		{
			s = j = 0;
			while (j < SOCHUSOMAXTRONG1PHANTU)
			{
				s = s * 10 + (rand() % 10);
				j++;
			}
			a[i][k] = s;
		}
	}
	f = fopen(filename, "w+");
	GhiMangKQ(f, a, length, sochuso);
	fclose(f);
}

void GhiMangKQ(FILE *f, unsigned long long* a[], int length, char sochuso[])
{
	int i, j, k;
	unsigned long long x;
	for (i = 0; i < length; i++)
	{
		if (a[i][0] == 0)
			fprintf(f, "-");
		fprintf(f, "%llu", a[i][1]);
		for (j = 2; j <= (sochuso[i] - 1) / SOCHUSOMAXTRONG1PHANTU + 1; j++)
		{
			x = a[i][j];
			k = 0;
			while (x > 0)
			{
				x = x / 10;
				k++;
			}
			while (k < SOCHUSOMAXTRONG1PHANTU)
			{
				fprintf(f, "0");
				k++;
			}
			fprintf(f, "%llu", a[i][j]);
		}
		fprintf(f, "\n");
	}
}

void ThongKe()
{
	unsigned long long **a, **tempt, length, **mergeSortreturn;
	char *sochuso, *sochusotempt, *mergeSortSochusoreturn;
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
		a = (unsigned long long**)malloc(length*sizeof(unsigned long long*));
		sochuso = (char*)malloc(length*sizeof(char));
		isort = 0;
		TaoDuLieu(tempt, length, sochusotempt);
		f = fopen("ThongKe.txt", "a");
		fprintf(f, "Truong hop %d phan tu:\n\n", length);
		fclose(f);
		while (isort < 8)
		{
			total = 0;
			for (int i = 0; i < length; i++)
			{
				a[i] = tempt[i];
				sochuso[i] = sochusotempt[i];
			}
			spg = spss = 0;
			start = clock();
			if (isort == 0)
				InsertionSort(a, length, sochuso);
			else if (isort == 1)
				ShellSort(a, length, sochuso);
			else if (isort == 2)
				BubbleSort(a, length, sochuso);
			else if (isort == 3)
				ShakeSort(a, length, sochuso);
			else if (isort == 4)
				MergeSort(a, sochuso, 0, length - 1, mergeSortreturn, mergeSortSochusoreturn);
			else if (isort == 5)
				QuickSort(a, sochuso, 0, length - 1);
			else if (isort == 6)
				HeapSort(a, sochuso, length);
			else if (isort == 7)
				RadixSort(tempt, sochusotempt, length);
			end = clock();
			total = (double)(end - start) / CLOCKS_PER_SEC;
			_itoa(length, filename, 10);
			strcat(filename, thuattoan[isort]);
			strcat(filename, "MangKQ.txt");
			f = fopen(filename, "w+");
			if (isort == 4)
			{
				GhiMangKQ(f, mergeSortreturn, length, mergeSortSochusoreturn);
				free(mergeSortreturn);
				free(mergeSortSochusoreturn);
			}
			else if (isort == 7)
				GhiMangKQ(f, tempt, length, sochusotempt);
			else
				GhiMangKQ(f, a, length, sochuso);
			fclose(f);
			fopen("ThongKe.txt", "a");
			fprintf(f, "Thuat toan %s:\n", thuattoan[isort]);
			fprintf(f, "So phep gan: %llu\nSo phep so sanh: %llu\nThoi gian chay: %.6lf giay\n\n", spg, spss, total);
			fclose(f);
			isort++;
		}
		for (int i = 0; i < length; i++)
			free(tempt[i]);
		length *= 10;
		free(tempt);
		free(a);
		free(sochuso);
		free(sochusotempt);
	}
}

void main()
{
	ThongKe();
	system("pause");
}