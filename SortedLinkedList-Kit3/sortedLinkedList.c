#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

struct Item {
	int val;
	struct Item* next;
	struct Item* prev;
};

struct Item* head = NULL;
struct Item* tail = NULL;

void addItem(int newItem);
struct Item* findHigher(int val);
void locateAfterTail(struct Item* item);
void locateBeforeHead(struct Item* item);
void locateBeforeItem(struct Item* newItem, struct Item* itemInList);

void printList()
{
	struct Item* currentItem = head;
	printf("Head");
	while (currentItem != NULL)
	{
		printf("->(%d)", currentItem->val);
		currentItem = currentItem->next;
	}
	printf("->Null\n");
}

void freeList()
{
	struct Item* currentItem = head;
	struct Item* releaseItem = head;
	while (currentItem != NULL)
	{
		releaseItem = currentItem;
		currentItem = currentItem->next;
		free(releaseItem);
	}
}

void resetList()
{
	if (head != NULL)
	{
		freeList();
		head = NULL;
		tail = NULL;
	}
}

void addItem(int newItem)
{
	struct Item* curr;
	curr = (struct Item*)malloc(sizeof(struct Item));
	curr->val = newItem;

	if (head == NULL)
	{
		head = curr;
		tail = curr;
		curr->next = NULL;
		curr->prev = NULL;
	}
	else
	{
		struct Item* highItem = findHigher(curr->val);
		if (highItem == NULL)
		{
			locateAfterTail(curr);
		}
		else
		{
			if (highItem == head)
			{
				locateBeforeHead(curr);
			}
			else
			{
				locateBeforeItem(curr, highItem);
			}
		}
	}
}

void locateAfterTail(struct Item* item)
{
	item->next = NULL;
	item->prev = tail;
	tail->next = item;
	tail = item;
}

void locateBeforeHead(struct Item* item)
{
	item->next = head;
	item->prev = NULL;
	head->prev = item;
	head = item;
}

void locateBeforeItem(struct Item* newItem, struct Item* itemInList)
{
	itemInList->prev->next = newItem;
	newItem->prev = itemInList->prev;
	newItem->next = itemInList;
	itemInList->prev = newItem;
}

struct Item* findHigher(int val)
{
	struct Item* ret = NULL;
	struct Item* curr = head;

	while (curr != NULL)
	{
		if (curr->val > val)
		{
			ret = curr;
			return ret;
		}
		curr = curr->next;
	}
	return ret;
}

int main()
{
	addItem(2);
	addItem(1);
	addItem(10);
	addItem(-1);
	addItem(8);
	addItem(80);
	printList();
	resetList();

	return 0;
}
