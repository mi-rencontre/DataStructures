#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_SIZE 20

typedef int DataType;

typedef struct SeqList
{
	DataType array[MAX_SIZE];
	size_t size;
}SeqList;

void InitSeqList(SeqList *pSeq)
{
	memset(pSeq->array,0,sizeof(DataType)*MAX_SIZE);
	pSeq->size = 0;
}

void PushBack(SeqList *pSeq,DataType x)
{
	assert(pSeq);

	if(pSeq->size >= MAX_SIZE)
	{
		printf("SeqList is full\n");
		return;
	}

	pSeq->array[pSeq->size++] = x;
}

void ShowSeqList(SeqList *pSeq)
{
	for(int i=0; i < pSeq->size;++i)
	{
		printf("  %d",pSeq->array[i]);
	}
	printf("\n");
}

//删除pos的数据
void Erase(SeqList *pSeq,size_t pos)
{
	if(pos > (pSeq->size-1))
	{
		printf("erase error\n");
		return;
	}
	int i = pos - 1;
	for(;i < pSeq->size;i++)
	{
		pSeq->array[i] = pSeq->array[i+1];
	}
	pSeq->size--;
}

//删除找到的第一个x
void Remove(SeqList *pSeq,DataType x)
{
	if(pSeq->size == 0)
	{
		printf("can't remove\n");
		return;
	}
	int i = 0;
	for(;i < pSeq->size;i++)
	{
		if(pSeq->array[i] == x)
		{
			for(int j = i;j<pSeq->size;j++)
			{
				pSeq->array[j] = pSeq->array[j+1];
			}
			pSeq->size--;
			return;
		}
	}
	printf("no x\n");
	return;
}

//删除所有的x
void RemoveAll(SeqList *pSeq,DataType x)
{
	if(pSeq->size == 0)
	{
		printf("can't remove\n");
		return;
	}
	int i = 0;
	for(;i < pSeq->size;i++)
	{
		if(pSeq->array[i] == x)
		{
			for(int j = i;j<pSeq->size;j++)
			{
				pSeq->array[j] = pSeq->array[j+1];
			}
			pSeq->size--;
		}
	}
	return;
}

//冒泡排序
size_t Sort(SeqList *pSeq)
{
	if(pSeq->size == 0)
	{
		printf("can't sort\n");
		return 0;
	}
	int i = 0;
	for(;i<pSeq->size-1;i++)
	{
		for(int j = 0;j < (pSeq->size-1)-i;j++)
		{
			if(pSeq->array[j] > pSeq->array[j+1])
			{
				int t;
				t = pSeq->array[j];
				pSeq->array[j] = pSeq->array[j+1];
				pSeq->array[j+1] = t;
			}
		}
	}
}

int main()
{
	SeqList mylist;
	InitSeqList(&mylist);
	PushBack(&mylist,1);
	PushBack(&mylist,3);
	PushBack(&mylist,4);
	PushBack(&mylist,5);
	PushBack(&mylist,2);
	ShowSeqList(&mylist);
	//Erase(&mylist,3);
	//Remove(&mylist, 3);
	//RemoveAll(&mylist,3);
	Sort(&mylist);
	ShowSeqList(&mylist);
	return 0;
}