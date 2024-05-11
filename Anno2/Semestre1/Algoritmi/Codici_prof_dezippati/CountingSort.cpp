#include<iostream>
using namespace std;

void print(int* array, int size) 
{
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << endl;
}


void countingSort(int* inputArray, int size)
{
	int max = inputArray[0];
	int min = inputArray[0];
	for (int i = 1; i < size; i++)
	{
		if (max < inputArray[i])
			max = inputArray[i];
		else if (min > inputArray[i])
			min = inputArray[i];
	}
	int range = max - min + 1;
	int* temp = new int[size];
	int* frequencyArray = new int[range];
	for (int i = 0; i < range; i++)
		frequencyArray[i] = 0;
	for (int i = 0; i < size; i++)
		frequencyArray[inputArray[i] - min]++;
	for (int i = 1; i < range; i++)
		frequencyArray[i] += frequencyArray[i - 1];
	for (int i = size - 1; i >= 0; i--) //stable version
	{
		temp[frequencyArray[inputArray[i] - min] - 1] = inputArray[i];
		frequencyArray[inputArray[i] - min]--;
	}
	for (int i = 0; i < size; i++)
		inputArray[i] = temp[i];

	delete[] frequencyArray;
	delete[] temp;
}


void countingSortInPlace(int* inputArray, int size)
{
	int max = inputArray[0];
	int min = inputArray[0];
	for (int i = 1; i < size; i++)
	{
		if (max < inputArray[i])
			max = inputArray[i];
		else if (min > inputArray[i])
			min = inputArray[i];
	}
	int range = max - min + 1;
	int* frequencyArray = new int[range];
	for (int i = 0; i < range; i++)
		frequencyArray[i] = 0;
	for (int i = 0; i < size; i++)
		frequencyArray[inputArray[i] - min]++;
	
	int j = 0;
	for (int i = 0; i < range; i++)
		while (frequencyArray[i] > 0)
		{
			inputArray[j] = i + min;
			frequencyArray[i]--;
			j++;
		}
	delete[] frequencyArray;
}


int main()
{
	int size = 8;
	int size2 = 6;
	int input[] = { 2, 5, 3, 0, 2, 3, 0, 3 };
	int input2[] = { 2, 3, 2, 1, 1, 4};
	cout << "Input Array: ";
	print(input, size);
	cout << endl;
	countingSort(input, size);
	countingSortInPlace(input2, size2);
	cout << "Array sorted with Counting-Sort: ";
	print(input, size);
	cout << "Array sorted with Counting-Sort in place: ";
	print(input2, size2);
	cout << endl;
}

