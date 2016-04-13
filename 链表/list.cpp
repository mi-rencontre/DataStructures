#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int DataType;

typedef struct ListNode
{
	DataType data;
	struct ListNode *next;
}ListNode;

ListNode *mylist;

void InitListNode(ListNode*& pHead)
{
	pHead = NULL;
}

ListNode* BuyNode(DataType x)
{
	ListNode *s = (ListNode *)malloc(sizeof(ListNode));
	s->data = x;
	s->next = NULL;
	return s;
}

void PushBack(ListNode*& pHead,DataType x)
{
	if(pHead == NULL)
	{
		pHead = BuyNode(x);
	}
	else
	{
		ListNode *tail = pHead;
		while(tail->next != NULL)
		{
			tail = tail->next;
		}
		tail->next = BuyNode(x);
	}
}

void PopBack(ListNode*& pHead)
{
	if(pHead == NULL)
	{
		printf("List is empty!\n");
		return;
	}
	else if(pHead->next == NULL)
	{
		free(pHead);
		pHead = NULL;
	}
	else
	{
		ListNode* prev = NULL;
		ListNode* tail = pHead;
		while(tail->next != NULL)
		{
			prev = tail;
			tail = tail->next;
		}
		prev->next = NULL;
		free(tail);
	}
}

void PushFront(ListNode*& pHead,DataType x)
{
	ListNode *cur = BuyNode(x);
	cur->next = pHead;
	pHead = cur;
}

void PopFront(ListNode*& pHead)
{
	if(pHead == NULL)
	{
		printf("List is empty!\n");
		return;
	}
	else
	{
		ListNode *cur = pHead;
		pHead = pHead->next;
		free(cur);
		cur = NULL;
	}
}

ListNode *Find(ListNode *pHead,DataType x)
{
	ListNode *cur = pHead;
	if(cur == NULL)
	{
		printf("List is empty!\n");
		return NULL;
	}
	while(cur != NULL)
	{
		if(cur->data == x)
		{
			return cur;
		}
		else
		{
			cur = cur->next;
		}
	}
	printf("no x\n");
	return 0;
}

void Insert(ListNode *pos,DataType x)
{
	if(pos == NULL)
	{
		return;
	}
	ListNode *cur = BuyNode(x);
	cur->next = pos->next;
	pos->next = cur;
}

void Erase(ListNode*& pHead,ListNode *pos)
{
	ListNode *cur = pos;
	ListNode *s = pHead;
	if(pos == NULL)
	{
		return;
	}
	if(pHead == cur)
	{
		pHead = pHead->next;
		free(cur);
		cur = NULL;
		return;
	}
	else
	{
		while(s != NULL)
		{
		    if(s->next == cur)
			{
				s->next = cur->next;
				free(cur);
				cur = NULL;
				return;
			}
			else 
			{
				s = s->next;
			}
		}
	}	
}

void Reverse(ListNode*& pHead)
{
	ListNode *newhead = NULL;
	ListNode *cur = pHead;
	while(cur)
	{
		ListNode *tmp = cur;
		cur = cur->next;
		tmp->next = newhead;
		newhead = tmp;
	}
	pHead = newhead;
} 

void PrintTailToHead(ListNode *pHead)
{
	if(pHead != NULL)
	{
		if(pHead->next != NULL)
		{
			PrintTailToHead(pHead->next);
		}
		printf("   %d",pHead->data);
	}
}

//ÊÇ·ñ´ø»·
ListNode* HasCycle(ListNode *pHead)
{
	ListNode *fast = pHead;
	ListNode *slow = pHead;
	while(fast && fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
		if(slow == fast)
		{
			return slow;
		}
	}
	return NULL;
}

int GetLength(ListNode *MeetNode)
{
	if(MeetNode == NULL)
	{
		return 0;
	}
	ListNode *cur = MeetNode;
	int count = 0;
	while(1)
	{
		cur = cur->next;
		count++;
		if(cur == MeetNode)
		{
			return count;
		}
	}
}

ListNode* GetEnterNode(ListNode *pHead,ListNode *MeetNode)
{
	ListNode *cur = pHead;
	ListNode *tmp = MeetNode;
	while(cur && tmp)
	{
		if(cur == tmp)
		{
			return cur;
		}
		cur = cur->next;
		tmp = tmp->next;
	}
	return NULL;
}

void ShowList(ListNode* pHead)
{
	ListNode *cur = pHead;
	while(cur)
	{
		printf("%d-->",cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}

int main()
{
	InitListNode(mylist);
	PushBack(mylist,1);
	PushBack(mylist,2);
	PushBack(mylist,3);
	PushBack(mylist,4);
	PushBack(mylist,5);
	PushBack(mylist,6);
	PushBack(mylist,7);
	PushBack(mylist,8);
	//ShowList(mylist);
	(Find(mylist,8)->next) = (Find(mylist,5));
	ListNode *ret = HasCycle(mylist);
	GetLength(ret);
	GetEnterNode(mylist,ret);
	//Insert(Find(mylist,5),9);
	//Insert(Find(mylist,1),9);
	//Insert(Find(mylist,3),9);
	//Insert(Find(mylist,0),9);
	//Erase(mylist,Find(mylist,9));
	//PopBack(mylist);
	//PopBack(mylist);
	//PopBack(mylist);
	//PopBack(mylist);
	//PopBack(mylist);
	//PushFront(mylist,2);
	//PushFront(mylist,3);
	//PushFront(mylist,4);
	//PopFront(mylist);
	//Reverse(mylist);
	//PrintTailToHead(mylist);
	//ShowList(mylist);
	return 0;
}
