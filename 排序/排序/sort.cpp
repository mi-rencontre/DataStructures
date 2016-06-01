#include<iostream>
using namespace std;

#include<assert.h>
#include<stack>

//≤Â»Î≈≈–Ú
void InsertSort(int *a, size_t size)
{
	assert(a);
	for (int i = 1; i < size; i++)
	{
		int index = i;
		int tmp = a[index];
		int end = index - 1;
		while (end >= 0 && a[end] > tmp)
		{
			a[end + 1] = a[end];
			end--;
		}
		a[end + 1] = tmp;
	}
}

//œ£∂˚≈≈–Ú
void ShellSort(int *a, size_t size)
{
	assert(a);
	int gap = size;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (size_t i = gap; i < size; i++)
		{
			int index = i;
			int tmp = a[index];
			int end = index - gap;
			while (end >= 0 && a[end] > tmp)
			{
				a[end + gap] = a[end];
				end -= gap;
			}
			a[end + gap] = tmp;
		}
	}
}

//—°‘Ò≈≈–Ú
void SelectSort(int *a, size_t size)
{
	assert(a);
	int left, right;
	for (left = 0, right = size - 1; left < right; left++, right--)
	{
		int min = left;
		int max = right;
		for (int i = left; i <= right; i++)
		{
			if (a[i] < a[min])
			{
				swap(a[i], a[min]);
			}
			if (a[i] > a[max])
			{
				swap(a[i], a[max]);
			}
		}
	}
}

void Adjust(int *a, int size, int root)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < size)
	{
		if ((child + 1 < size) && (a[child] < a[child + 1]))
		{
			child++;
		}
		if (a[child] > a[parent])
		{
			swap(a[child], a[parent]);
			parent = child;
			child = child * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

//∂—≈≈–Ú
void HeapSort(int *a, int size)
{
	assert(a);
	for (int i = (size - 2) / 2; i >= 0; i--)
	{
		Adjust(a, size, i);
	}
	for (int j = size - 1; j >= 0; j--)
	{
		swap(a[0], a[j]);
		Adjust(a, j, 0);
	}
}

void Print(int *a, size_t size)
{
	assert(a);
	for (size_t i = 0; i < size; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

//√∞≈›≈≈–Ú
void BubbleSort(int *a, int size)
{
	assert(a);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
			}
		}
	}
}

int PartSort1(int *a, int left, int right)
{
	int key = a[right];
	int begin = left;
	int end = right - 1;
	while (begin < end)
	{
		while (begin < end && a[begin] <= key)
		{
			begin++;
		}
		while (end > begin && a[end] >= key)
		{
			end--;
		}
		if (a[begin] > a[end])
		{
			swap(a[begin], a[end]);
		}
	}
	if (a[begin] > key)
	{
		swap(a[begin], a[right]);
		return begin;
	}
	else
	{
		return right;
	}
}

//”≈ªØ
int PartSort2(int *a, int left, int right)
{
	assert(a);
	int key = a[right];
	int cur = left;
	int prev = cur - 1;
	while (cur < right)
	{
		if (a[cur] < key && ++prev != cur)
		{
			swap(a[cur], a[prev]);
		}
		++cur;
	}
	swap(a[++prev], a[right]);
	return prev;
}

//øÏÀŸ≈≈–Ú(µ›πÈ)
void QuickSort1(int *a, int left, int right)
{
	assert(a);
	if (right > left)
	{
		int boundary = PartSort2(a, left, right);
		QuickSort1(a, left, boundary - 1);
		QuickSort1(a, boundary + 1, right);
	}
}

//∑«µ›πÈ
void QuickSort2(int *a, int left, int right)
{
	assert(a);
	stack<int> s;
	if (right > left)
	{
		int boundary = PartSort1(a, left, right);
		if (left < boundary - 1)
		{
			s.push(left);
			s.push(boundary - 1);
		}
		if (right > boundary + 1)
		{
			s.push(boundary + 1);
			s.push(right);
		}

		while (!s.empty())
		{
			int end = s.top();
			s.pop();
			int begin = s.top();
			s.pop();
			boundary = PartSort1(a, begin, end);
			if (begin < boundary - 1)
			{
				s.push(begin);
				s.push(boundary - 1);
			}
			if (boundary + 1 < end)
			{
				s.push(boundary + 1);
				s.push(end);
			}
		}
	}
}

void SectionSort(int *a, int *tmp, int begin1, int end1, int begin2, int end2)
{
	int index = begin1;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
		{
			tmp[index++] = a[begin1++];
		}
		else
		{
			tmp[index++] = a[begin2++];
		}
	}
	if (begin1 <= end1)
	{
		for (int i = begin1; i <= end1; i++)
		{
			tmp[index++] = a[begin1++];
		}
	}
	if (begin2 <= end2)
	{
		for (int i = begin2; i <= end2; i++)
		{
			tmp[index++] = a[begin2++];
		}
	}
}

void _MergeSort(int *a, int *tmp, int left, int right)
{
	int mid = left + (right - left) / 2;
	if (left < right)
	{
		_MergeSort(a, tmp, left, mid);
		_MergeSort(a, tmp, mid+1, right);
		SectionSort(a, tmp, left, mid, mid+1, right);
		memcpy(a + left, tmp + left, (right - left + 1)*sizeof(int));
	}	
}

//πÈ≤¢≈≈–Ú
void MergeSort(int *a,int size, int left, int right)
{
	assert(a);
	int *tmp = new int[size];
	_MergeSort(a, tmp,left, right);
	delete []tmp;
}

//º∆ ˝≈≈–Ú
void CountSort(int *a, size_t size)
{
	assert(a);
	int max = a[0];
	int min = a[0];
	for (int i = 0; i < size; i++)
	{
		if (a[i] > max)
		{
			max = a[i];
		}
		else if (a[i] < min)
		{
			min = a[i];
		}
	}
	int len = max - min + 1;
	int *countArr = new int[len];
	memset(countArr, 0, sizeof(int)*len);
	for (int i = 0; i < size; i++)
	{
		countArr[a[i] - min]++;
	}
	int tmp = 0;
	for (int i = 0; i < len; i++)
	{
		while (countArr[i]--)
		{
			a[tmp++] = i + min;
		}
	}
}

int GetMaxDigit(int *a, size_t size)
{
	int digit = 1;
	int max = 10;
	for (int i = 0; i < size; i++)
	{
		if (a[i] >= max)
		{
			digit++;
			max *= 10;
		}
	}
	return digit;
}

//ª˘ ˝≈≈–Ú
void LSDSort(int *a, size_t size)
{
	int maxdigit = GetMaxDigit(a, size);
	int *bucket = new int[size];
	int count[10];
	int start[10];
	int bit = 1;
	int digit = 1;
	while (bit <= maxdigit)
	{
		memset(count, 0, sizeof(int)* 10);
		memset(start, 0, sizeof(int)* 10);
		for (int i = 0; i < size; i++)
		{
			int num = (a[i]/digit) % 10;
			count[num]++;
		}
		start[0] = 0;
		for (int i = 1; i < size; i++)
		{
			start[i] = start[i - 1] + count[i - 1];
		}
		for (int i = 0; i < size; i++)
		{
			int num = (a[i] / digit) % 10;
			bucket[start[num]++] = a[i];
		}
		memcpy(a, bucket, sizeof(int)*size);
		digit *= 10;
		bit++;
	}
}

int main()
{
	int a[10] = { 23, 25, 45, 93, 32, 56, 850, 7, 1000, 30 };
//	InsertSort(a, 10);
//	ShellSort(a, 10);
//	SelectSort(a, 10);
//	HeapSort(a, 10);
//	BubbleSort(a, 10);
	QuickSort1(a, 0, 9);
//	QuickSort2(a, 0, 9);
//	MergeSort(a,10, 0, 9);
//	CountSort(a, 10);
//	LSDSort(a, 10);
	Print(a, 10);
	return 0;
}