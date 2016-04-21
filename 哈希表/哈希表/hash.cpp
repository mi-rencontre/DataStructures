#include <iostream>
using namespace std;

enum Status
{
	EXIT,
	DELETE,
	EMPTY,
};

template<class K>
class HashTable
{
public:
	HashTable()
		:_table(NULL)
		, _size(0)
		, _cpacity(0)
		, _status(0)
	{}

	HashTable(size_t capacity)
		:_table(new K[capacity])
		, _size(0)
		, _capacity(capacity)
		, _status(new Status[capacity])
	{
		for (size_t i = 0; i < _capacity; i++)
		{
			_status[i] = EMPTY;
		}
	}

	~HashTable()
	{
		if (_table)
		{
			delete[] _table;
		}
		if (_status)
		{
			delete[] _status;
		}
	}

public:
	bool Insert(const K& x)
	{
		if ((_size * 10 / _capacity) > 8)
		{
			HashTable ht(_capacity * 2);
			int i = 0;
			Swap(ht);
			while (i < ht._capacity)
			{
				if (ht._status[i] == EXIT)
				{
					Insert(ht._table[i]);
				}
				i++;
			}
		}
		int index = HashFunc(x);
		while (_status[index] == EXIT)
		{	
			index++;
			if (index == _capacity)
			{
				index = 0;
			}
		}
		_table[index] = x;
		_status[index] = EXIT;
		_size++;
		return true;
	}

	bool Remove(const K& x)
	{
		int index = HashFunc(x);
		while (_status[index] != EMPTY)
		{
			if (_table[index] == x)
			{
				_status[index] = DELETE;
				return true;
			}
			index++;
			if (index == _capacity)
			{
				index = 0;
			}
		}
		return false;
	}

	bool Find(const K& x)
	{
		int index = HashFunc(x);
		while (_status[index] != EMPTY)
		{
			if (_table[index] == x)
			{
				return true;
			}
			index++;
			if (index == _capacity)
			{
				index = 0;
			}
		}
		return false;
	}

	void Print()
	{
		for (size_t i = 0; i < _capacity; ++i)
		{
			cout << _status[i] << ":";
			cout << _table[i] << " ";
		}
		cout << endl;
	}

protected:

	void Swap(HashTable<int>& ht)
	{
		swap(_table, ht._table);
		swap(_status, ht._status);
		swap(_size, ht._size);
		swap(_capacity, ht._capacity);
	}

	size_t HashFunc(const K& x)
	{
		return (x % _capacity);
	}

private:
	K* _table;
	size_t _size;
	size_t _capacity;
	Status* _status;
};

int main()
{
	HashTable<int> ht1(10);
	ht1.Insert(89);
	ht1.Insert(18);
	ht1.Insert(49);
	ht1.Insert(58);
	ht1.Insert(9);
	ht1.Insert(55);
	ht1.Insert(34);
	ht1.Insert(44);
	ht1.Insert(99);
	ht1.Insert(22);
	ht1.Print();
	ht1.Remove(49);
	ht1.Print();
	ht1.Find(58);
	return 0;
}

// K/V–Œ Ω
//enum Status
//{
//	EXIT,
//	DELETE,
//	EMPTY,
//};
//
//template<class K,class V>
//class KeyValueNode
//{
//public:
//	KeyValueNode(const K& key, const V& value)
//		:_key(key)
//		, _value(value)
//	{}
//
//private:
//	K _key;
//	V _value;
//};
//
//template < class K, class V>
//class HashTable
//{
//	typedef KeyValueNode<K, V> KVNode;
//public:
//	HashTable()
//		:_table(NULL)
//		, _size(0)
//		, _capacity(0)
//		, _status(0)
//	{}
//
//	HashTable(size_t capacity)
//		:_table(new KVNode[capacity])
//		, _size(0)
//		, _capacity(capacity)
//		, _status(new Status[capacity])
//	{
//		for (size_t i = 0; i < _capacity; i++)
//		{
//			_status[i] = EMPTY;
//		}
//	}
//
//private:
//	KVNode* _table;
//	size_t _size;
//	size_t _capacity;
//	Status* _status;
//};
//
//int main()
//{
//	return 0;
//}