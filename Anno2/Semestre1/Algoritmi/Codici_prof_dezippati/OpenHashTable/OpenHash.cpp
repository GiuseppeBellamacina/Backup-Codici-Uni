#include <iostream>
#include<math.h>
using namespace std;

template <class T> class HashTable
{
public:
	virtual HashTable<T>* insertKey(T x) = 0;
	virtual int searchKey(T x) = 0;
	virtual HashTable<T>* deleteKey(T x) = 0;
	virtual void print() = 0;
};

template <class T> class OpenHashTable : public HashTable<T>
{
private:
	virtual int computeHashFunction(T x, int i) = 0;	
	virtual OpenHashTable<T>* insertKey(T x) = 0;
	virtual OpenHashTable<T>* deleteKey(T x) = 0;
    virtual int searchKey(T x) = 0;
	int tableSize; // dimensione della tabella
	int keyCounter; // dice quanto è piena la tabella
	T** table;		

public:

	OpenHashTable<T>(int tableSize)
	{				
		table = new T* [tableSize];
		for (int i = 0; i < tableSize; i++)
			table[i] = NULL;
		this->keyCounter = 0;
		this->tableSize = tableSize;
	}	
	
	void increaseKeyCounter()
	{
		keyCounter++;
	}

	void decreaseKeyCounter()
	{
		keyCounter--;
	}

	
	int getTableSize() 
	{
		return tableSize;
	}		

	int getKeyCounter() 
	{
		return keyCounter; 
	}	

	T** getTable() // accesso alla tabella
	{
		return table;
	}
};



template <class T> class TombstoneOpenHashTable : public OpenHashTable<T>
{
private:
	virtual int computeHashFunction(T x, int i) = 0;
	T* deleted;
	
public:
	TombstoneOpenHashTable<T>(int tableSize) : OpenHashTable<T>(tableSize)
	{
		this->deleted = new T();
	}	

	T* getDeleted()
	{
		return deleted;
	}

	TombstoneOpenHashTable<T>* insertKey(T x)
	{	
		// controlliamo se la tabella non è piena	
		if (this->getKeyCounter() == this->getTableSize())
			return this;		
		for (int i=0; i < this->getTableSize(); i++)
		{
			int hash = computeHashFunction(x, i);
			if (this->getTable()[hash] == NULL || this->getTable()[hash] == this->getDeleted())
			{
				this->getTable()[hash] = new T(x);
				this->increaseKeyCounter();
				return this;
			}			
		}
		return this;
	}


	int searchKey(T x)
	{
		// la tabella è vuota
		if (this->getKeyCounter() == 0)
			return -1;
		for (int iterator=0; iterator < this->getTableSize(); iterator++)
		{
			int hash = computeHashFunction(x, iterator);	
			if (this->getTable()[hash] == NULL)
				return -1;
			if (this->getTable()[hash] != this->getDeleted() && *(this->getTable()[hash]) == x)
				return hash;			
		}
		return -1;
	}


	TombstoneOpenHashTable<T>* deleteKey(T x)
	{	
		if(this->getKeyCounter() == 0)
			return this;
		int position = searchKey(x);
		if (position > -1)
		{
			delete this->getTable()[position];
			this->getTable()[position] = this->getDeleted();
			this->decreaseKeyCounter();			
		}
		return this;
	}


	void print()
	{
		for (int i = 0; i < this->getTableSize(); i++)
		{
			cout << i;
			if (this->getTable()[i] != this->getDeleted() && this->getTable()[i] )
				cout << "-> " << "[" << *(this->getTable()[i]) << "]";
			else
				cout << "-> []";
			cout << endl;
		}
		cout << endl;
	}
};



template <class T> class DeleteShiftOpenHashTable : public OpenHashTable<T>
{
private:
	virtual int computeHashFunction(T x, int i) = 0;
public:
	DeleteShiftOpenHashTable<T>(int tableSize) : OpenHashTable<T>(tableSize) {}

	DeleteShiftOpenHashTable<T>* insertKey(T x)
	{
		if (this->getKeyCounter() == this->getTableSize())
			return this;		
		for (int i = 0; i < this->getTableSize(); i++)
		{
			int hash = computeHashFunction(x, i);
			if (this->getTable()[hash] == NULL)
			{				
				this->getTable()[hash] = new T(x);
				this->increaseKeyCounter();
				return this;
			}			
		}
		return this;
	}

	int searchKey(T x)
	{
		if (this->getKeyCounter() == 0)
			return -1;		
		for (int iterator = 0; iterator < this->getTableSize(); iterator++)
		{			
			int hash = computeHashFunction(x, iterator);
			if (this->getTable()[hash] == NULL)
				return -1;
			if (*(this->getTable()[hash]) == x)
				return hash;			
		}
		return -1;
	}

	DeleteShiftOpenHashTable<T>* deleteKey(T x)
	{
		if (this->getKeyCounter() == 0)
			return this;	
		
		// la prima parte è un pezzo di ricerca
		for (int iterator = 0; iterator < this->getTableSize(); iterator++)
		{
			int hash = computeHashFunction(x, iterator);
			if (this->getTable()[hash] == NULL)
				return this;
			if (*(this->getTable()[hash]) == x)
			{
				// cancelliamo
				delete this->getTable()[hash];	
				this->getTable()[hash] = NULL;
				this->decreaseKeyCounter();
				iterator++;
				// si parte dall'indice succesivo
				for (; iterator < this->getTableSize(); iterator++)
				{					
					int hash2 = computeHashFunction(x, iterator);
					this->getTable()[hash] = (this->getTable()[hash2]);
					if (this->getTable()[hash2] == NULL) // forse l'indice è hash al posto di hash2
						return this;			
					hash = hash2;
				} 				
				return this;				
			}			
		}	
		return this;		
	}


	void print()
	{
		for (int i = 0; i < this->getTableSize(); i++)
		{
			cout << i;
			if (this->getTable()[i])
				cout << "-> " << "[" << *(this->getTable()[i]) << "]";
			else
				cout << "-> []";
			cout << endl;
		}
		cout << endl;
	}
};

template <class T> class LinearHashFunction
{
protected:
	int computeHashFunction(T x, int i, int m)
	{
		return (((int)x % m) + i) % m;
	}
};

template <class T> class QuadraticHashFunction
{
private:
	double c1;
	double c2;
protected:
	int computeHashFunction(T x, int i, int m)
	{
		return ((int)(((int)x % m) + this->getConstantC1() * i + this->getConstantC2() * pow(i, 2))) % m;
	}
public:
	QuadraticHashFunction(double x, double y)
	{
		c1 = x;
		c2 = y;
	}

	double getConstantC1()
	{
		return c1;
	}
	double getConstantC2()
	{
		return c2;
	}
};


template <class T> class LinearTombstoneOpenHashTable : public TombstoneOpenHashTable<T>, LinearHashFunction<T>
{
protected:
	int computeHashFunction(T x, int i)
	{
		return LinearHashFunction<T>::computeHashFunction(x, i, this->getTableSize());
	}
public:
	LinearTombstoneOpenHashTable(int tableSize) : TombstoneOpenHashTable<T>(tableSize) {}
};


template <class T> class LinearDeleteShiftOpenHashTable : public DeleteShiftOpenHashTable<T>, LinearHashFunction<T>
{
protected:
	int computeHashFunction(T x, int i)
	{
		return LinearHashFunction<T>::computeHashFunction(x, i, this->getTableSize());
	}
public:
	LinearDeleteShiftOpenHashTable(int tableSize) : DeleteShiftOpenHashTable<T>(tableSize) {}
};


template <class T> class QuadraticTombstoneOpenHashTable : public TombstoneOpenHashTable<T>, QuadraticHashFunction<T>
{
private:
	int computeHashFunction(T x, int i)
	{
		return QuadraticHashFunction<T>::computeHashFunction(x, i, this->getTableSize());
	}
public:
	QuadraticTombstoneOpenHashTable(int tableSize) : TombstoneOpenHashTable<T>(tableSize), QuadraticHashFunction<T>(1 / 2, 1 / 2) {}
};

template <class T> class QuadraticDeleteShiftOpenHashTable : public DeleteShiftOpenHashTable<T>, QuadraticHashFunction<T>
{
private:
	int computeHashFunction(T x, int i)
	{
		return QuadraticHashFunction<T>::computeHashFunction(x, i, this->getTableSize());
	}
public:
	QuadraticDeleteShiftOpenHashTable(int tableSize) : DeleteShiftOpenHashTable<T>(tableSize), QuadraticHashFunction<T>(1 / 2, 1 / 2) {}
};
