#include <iostream>
using namespace std;

#include <vector>
#include<string>

template<class K>
struct DefaultHashFun
{
	size_t operator()(const K&key)
	{
		return key;
	}
};

template<>
struct DefaultHashFun<string>
{
	static size_t BKDRHash(const char *s)
	{
		unsigned int seed = 131;
		unsigned hash = 0;
		while (*s)
		{
			hash = hash*seed + (*s++);

		}
		return (hash & 0x7FFFFFFF);
	}

	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str());
	}
};

template<class K, class V>
struct HashTableNode
{
	K _key;
	V _value;
	HashTableNode<K, V>* _next;

	HashTableNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _next(NULL)
	{}
};

template<class K, class V,class HashFun = DefaultHashFun<K>>
class HashTableBucket
{
	typedef HashTableNode<K, V> KVNode;

public:
	HashTableBucket()
		:_size(0)
	{}

	HashTableBucket(size_t size)
		:_size(0)
	{
		_table.resize(size);
	}

	HashTableBucket(const HashTableBucket<K, V,HashFun>& ht)
		:_size(0)
	{
		_table.resize(ht._table.size());
		for (size_t i = 0; i < ht._table.size(); ++i)
		{
			KVNode* cur = ht._table[i];
			while (cur)
			{
				this->Insert(cur->_key, cur->_value);
				cur = cur->_next;
			}
		}
		/*HashTableBucket<K, V, HashFun> Newtable(ht._table.size());
		for (size_t i = 0; i <ht._table.size(); ++i)
		{
			KVNode* cur = ht._table[i];
			while (cur)
			{
				Newtable.Insert(cur->_key, cur->_value);
				cur = cur->_next;
			}
		}
		Swap(Newtable);*/
	}

	HashTableBucket<K, V>& operator=(const HashTableBucket<K, V,HashFun>& ht)
	{
		if (this != &ht)
		{
			HashTableBucket<K, V, HashFun> tmp(ht);
			this->Swap(tmp);
		}
		return *this;
	}

	~HashTableBucket()
	{
		for (size_t i = 0; i < _table.size(); i++)
		{
			KVNode* cur = _table[i];
			while (cur)
			{
				KVNode* del = cur;
				cur = cur->_next;
				delete del;
				del = NULL;
			}
			_table[i] = NULL;
		}
		_size = 0;
	}

public:
	bool Insert(const K& key, const V& value)
	{
		_CheckCapacity();

		size_t index = HashFunc(key);
		KVNode* cur = _table[index];
		KVNode* tmp = new KVNode(key, value);
		while (cur)
		{
			if (cur->_key == key)
			{
				return false;
			}
			cur = cur->_next;
		}
		tmp->_next = _table[index];
		_table[index] = tmp;
		++_size;
	}

	bool Remove(const K& key)
	{
		size_t index = HashFunc(key);
		KVNode* cur = _table[index];
		while (cur)
		{
			if (cur->_key == key)
			{
				_table[index] = cur->_next;
				delete cur;
				cur = NULL;
				_size--;
				return true;
			}
			if (cur->_next->_key == key)
			{
				KVNode* del = cur->_next;
				cur->_next = del->_next;
				delete del;
				del = NULL;
				_size--;
				return true;
			}
			cur = cur->_next;
		}
		return false;
	}

	KVNode* Find(const K& key)
	{
		size_t index = HashFunc(key);
		KVNode* cur = _table[index];
		while (cur)
		{
			if (cur->_key == key)
			{
				return cur;
			}
			cur = cur->_next;
		}
		return NULL;
	}

	void Print()
	{
		for (int i = 0; i < _table.size(); ++i)
		{
			cout << "table[" << i << "]->";
			KVNode *cur = _table[i];
			while (cur)
			{
				cout << cur->_key << ":" << cur->_value << "->";
				cur = cur->_next;
			}
			cout << "NULL" << endl;
		}
	}
protected:

	size_t _GetNextPrime()
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};
		if (_table.size() == _table.capacity())
		{
			for (size_t i = 0; i < _PrimeSize; i++)
			{
				if (_PrimeList[i] > _size)
				{
					return _PrimeList[i];
					break;
				}
			}
		}
		return _PrimeList[_PrimeSize];
	}

	void _CheckCapacity()
	{
		size_t NewCapacity = _GetNextPrime();
		if (_table.capacity() == NewCapacity)
		{
			return;
		}

		vector<KVNode*> Newtable;
		Newtable.resize(NewCapacity);

		for (size_t i = 0; i < _table.size(); ++i)
		{
			KVNode* cur = _table[i];
			while (cur)
			{
				KVNode* tmp = cur;
				cur = cur->_next;
				size_t newIndex = HashFunc(tmp->_key);
				tmp->_next = Newtable[newIndex];
				Newtable[newIndex] = tmp;
			}
			_table[i] = NULL;
		}
		_table.swap(Newtable);
	}

	size_t HashFunc(K key)
	{
		HashFun hf;
		return (hf(key) % _table.size());
	}

	void Swap(HashTableBucket<K, V, HashFun>& ht)
	{
		_table.swap(ht._table);
		swap(_size, ht._size);
	}

private:
	vector<KVNode*> _table;
	size_t _size;
};

int main()
{
	HashTableBucket<string,string> htb1;
	htb1.Insert("×Öµä", "dictionary");
	htb1.Insert("Ïã½¶", "banana");
	htb1.Insert("²ÝÝ®", "strawberry");
	htb1.Insert("²¤ÂÜ", "pineapple");
	htb1.Insert("Î÷¹Ï", "watermelon");
	htb1.Print();
	HashTableBucket<string, string> htb2;
	htb2.Insert("11", "222");
	htb2 = htb1;
	htb2.Print();
	return 0;
}