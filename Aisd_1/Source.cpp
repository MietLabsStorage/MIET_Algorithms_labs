#include <iostream>
#include <iomanip>
#include <time.h>
#include <chrono>

using namespace std;
using namespace chrono;

//print array
template <typename T>
void showArr(T* arr, int arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

//----------------sorts----------------//

//return major element
template <typename T>
T max(T elem1, T elem2)
{
	if (elem1 > elem2)
	{
		return elem1;
	}
	else
	{
		return elem2;
	}
}

//return minor element
template <typename T>
T min(T elem1, T elem2)
{
	if (elem1 < elem2)
	{
		return elem1;
	}
	else
	{
		return elem2;
	}
}

//return minor element and write in var e if elem1 less then elem2
template <typename T>
T min(T elem1, T elem2, bool& e)
{
	if (elem1 < elem2)
	{
		e = true;
		return elem1;
	}
	else
	{
		e = false;
		return elem2;
	}
}

template <typename T>
T* mergeSort(T* arr1, T* arr2, int arr1Size, int arr2Size)
{
	int marker1 = 0, marker2 = 0;
	bool e;
	int i = 0;
	T* resultArr = new T[arr1Size + arr2Size];
	//merge arrs while noone is finished
	while (true)
	{
		if (marker1 > arr1Size - 1 || marker2 > arr2Size - 1)
		{
			break;
		}
		resultArr[i] = min(arr1[marker1], arr2[marker2], e);
		e ? marker1++ : marker2++;
		i++;
	}
	//actions when one of arrs is finished
	if (marker1 < arr1Size)
	{
		//if arr1 is not finished
		for (int j = i; j < arr1Size + arr2Size; j++)
		{
			resultArr[j] = arr1[marker1];
			marker1++;
		}
	}
	else
	{
		//if arr2 is not finished
		for (int j = i; j < arr1Size + arr2Size; j++)
		{
			resultArr[j] = arr2[marker2];
			marker2++;
		}
	}
	return resultArr;
}

template <typename T>
T* insertionSort(T* arr, int arrSize)
{
	for (int i = 1; i < arrSize; i++)
	{
		T temp = arr[i];
		int j = i;
		//compare elements
		while (arr[j - 1] > arr[i])
		{
			j--;
		}
		//swap elements
		for (int k = i; k > j; k--)
		{
			swap(arr[k], arr[k - 1]);
		}
	}
	return arr;
}

//----------------searchs----------------//

template <typename T>
int binarySearch(T* arr, int arrSize, T key)
{
	//left index
	int a = 0; 
	//right index
	int b = arrSize - 1;
	//current index
	int n = 1;
	while (key != arr[n-1])
	{
		if (key > arr[n-1])
		{
			a = n;
		}
		else 
		{
			b = (n - 1) - 1;
		}
		if (b - a <= -1)
		{
			return -1;
		}
		n = a + (b - a + 1) / 2 + 1;
	}
	return n;
}

template <typename T>
int interpolationSearch(T* arr, int arrSize, T key)
{
	int i = 0;
	int j = arrSize - 1;
	int d = 0;
	while (key != arr[i+d])
	{
		d = (j - i) * (key - arr[i]) / (arr[j] - arr[i]);
		if (d == 0)
		{
			if (arr[i + 1] == key)
			{
				return (i+1)+1;
			}
			else
			{
				return -1;
			}
		}
		else if (key > arr[i+d])
		{
			i = i + d;
		}
		else 
		{
			j = i + d;
		}
		if (j == i)
		{
			return -1;
		}
	}
	return i + d + 1;
}

//----------------rnd generatorss----------------//

struct rndXY
{
	int* x;
	double* y;
};
rndXY congruentialGenerator(int b, int x0, int k, int m, int quantity)
{
	rndXY xy;
	xy.x = new int[m + 1];
	xy.y = new double[m + 1]; 
	xy.x[0] = x0;
	xy.y[0] = (double)xy.x[0] / m;
	for (int j = 1; j <= quantity; j++)
	{
		xy.x[j] = (b * xy.x[j - 1] + k) % m;
		xy.y[j] = (double)xy.x[j] / m;
	}
	return xy;
}

struct n1n2
{
	double n1, n2;
};
n1n2 polarGenerator()
{
	n1n2 n;
	double u1 = rand() / RAND_MAX;
	double u2 = rand() / RAND_MAX;
	double v1 = 2 * u1 - 1;
	double v2 = 2 * u2 - 1;
	double s = v1 * v1 + v2 * v2;
	while (s >= 1)
	{
		u1 = double(rand()) / RAND_MAX;
		u2 = double(rand()) / RAND_MAX;
		v1 = 2 * u1 - 1;
		v2 = 2 * u2 - 1;
		s = v1 * v1 + v2 * v2;
	}
	n.n1 = v1 * sqrt(-2 * log(s) / s);
	n.n2 = v2 * sqrt(-2 * log(s) / s);
	return n;
}

int main()
{
	srand(time(NULL));
	time_point<system_clock> start, end;

	//--sorts--

	int arr1[3] = { 6, 9, 12 }, arr2[4] = { 3, 8, 10, 14 };
	cout << "--merge sort:\n";
	cout << "-primary arrs: \n"; cout << "  arr1: "; showArr(arr1, 3); cout << "  arr2: "; showArr(arr2, 4);
	cout << "-sorts: \n";
	cout << "  arr1 + arr2:: ";  showArr(mergeSort(arr1, arr2, 3, 4), 3 + 4);
	cout << "  arr2 + arr1:: ";  showArr(mergeSort(arr2, arr1, 4, 3), 3 + 4);
	cout << "  arr1 (firsts 2 elems) + arr2 (firsts 2 elems):: ";  showArr(mergeSort(arr1, arr2, 2, 2), 2 + 2);

	int arr211[1700], arr212[1700];
	for (int i = 0; i < 1700; i++)
	{
		arr211[i] = i * i + i;
		arr212[i] = i * i - i;
	}
	start = system_clock::now();
	mergeSort(arr211, arr212, 1700, 1700);
	end = system_clock::now();
	cout << "-time (1700 elems): " << duration_cast<microseconds> (end - start).count() << " microseconds" << endl;
	int arr221[2800], arr222[2800];
	for (int i = 0; i < 2800; i++)
	{
		arr221[i] = i * i + i;
		arr222[i] = i * i - i;
	}
	start = system_clock::now();
	mergeSort(arr221, arr222, 2800, 2800);
	end = system_clock::now();
	cout << "-time (2800 elems): " << duration_cast<microseconds> (end - start).count() << " microseconds" << endl;
	int arr231[7500], arr232[7500];
	for (int i = 0; i < 7500; i++)
	{
		arr231[i] = i * i + i;
		arr232[i] = i * i - i;
	}
	start = system_clock::now();
	mergeSort(arr231, arr232, 7500, 7500);
	end = system_clock::now();
	cout << "-time (7500 elems): " << duration_cast<microseconds> (end - start).count() << " microseconds" << endl;

	int arr3[5] = { 6,3,5,1,7};
	int arr4[13] = { 1, 5, 6, 7, 2, 4, 3, 9, 8, 5, 4, 5, 6 };
	cout << "\n--insertion sort:\n";
	cout << "-primary arrs: \n"; cout << "  arr3: "; showArr(arr3, 5); cout << "  arr4: "; showArr(arr4, 13);
	cout << "-sorts: \n";
	cout << "  arr3: "; showArr(insertionSort(arr3, 5), 5);
	cout << "  arr4: "; showArr(insertionSort(arr4, 13), 13);

	int arr41[1000];
	for (int i = 0; i < 1000; i++)
	{
		arr41[i] = rand()%1000;
	}
	start = system_clock::now();
	insertionSort(arr41, 1000);
	end = system_clock::now();
	cout << "-time (1000 elems): " << duration_cast<microseconds> (end - start).count() << " microseconds" << endl;
	int arr42[4000];
	for (int i = 0; i < 4000; i++)
	{
		arr42[i] = rand() % 1000;
	}
	start = system_clock::now();
	insertionSort(arr42, 4000);
	end = system_clock::now();
	cout << "-time (1000 elems): " << duration_cast<microseconds> (end - start).count() << " microseconds" << endl;	
	int arr43[6000];
	for (int i = 0; i < 6000; i++)
	{
		arr43[i] = rand() % 1000;
	}
	start = system_clock::now();
	insertionSort(arr43, 6000);
	end = system_clock::now();
	cout << "-time (1000 elems): " << duration_cast<microseconds> (end - start).count() << " microseconds" << endl;
	

	//--search--

	int arr5[12] = { 6, 8, 10, 13, 20, 24, 29, 33, 40, 41, 43, 47 };
	int arr6[12] = { 3, 7, 10, 15, 20, 27, 36, 43, 51, 60, 75, 80 };

	cout << "\n\n--binary search: \n";
	cout << "-primary arr: "; showArr(arr5, 12);
	cout << "-try find every element in arr (and return index): \n   ";
	for(int i = 0; i < 12; i++)
		cout << binarySearch(arr5, 12, arr5[i]) << " ";
	cout << "\n-try find elements which absent in arr (and return -1 if not found): \n";
	cout << "  search 100: " << binarySearch(arr5, 12, 100) << endl;
	cout << "  search 1: " << binarySearch(arr5, 12, 1) << endl;
	cout << "  search 22: " << binarySearch(arr5, 12, 22) << endl;

	
	cout << "\n\n--interpolation search: \n";
	cout << "-primary arr: "; showArr(arr6, 12);
	cout << "-try find every element in arr (and return index): \n   ";
	for (int i = 0; i < 12; i++)
		cout << interpolationSearch(arr6, 12, arr6[i]) << " ";
	cout << "\n-try find elements which absent in arr (and return -1 if not found): \n";
	cout << "  search 2: " << interpolationSearch(arr6, 12, 2) << endl;
	cout << "  search 101: " << interpolationSearch(arr6, 12, 101) << endl;
	cout << "  search 22: " << interpolationSearch(arr6, 12, 46) << endl;


	//--random--

	cout << "\n\n--congruential generator:\n";
	rndXY xy = congruentialGenerator(101, 432, 0, 2048, 10);
	cout << " -random numbers: "; 
	for (int i = 0; i <= 10; i++)
		cout << xy.x[i] << "\t";
	cout << endl;
	cout << " -normed numbers: ";
	for (int i = 0; i <= 10; i++)
		cout << setprecision(2) << xy.y[i] << "\t";
	cout << endl;

	cout << "\n--congruential generator:\n";
	cout << " -random numbers: \n";
	n1n2 n;
	for (int i = 0; i < 5; i++)
	{
		n = polarGenerator();
		cout << "   "<< n.n1 << " " << n.n2 << endl;
	}

}