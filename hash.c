#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

#define HASH_ENTRIES   (256*1024)
#define OP_NUM 1024*32*8

/*int Hash( void *key, int TableSize )
{
	char c;
	int i;
	int hval = 0;
	for( i = 1;(c = *(char *)key++) != 0; i++)
		hval += c*i;
	return (hval%TableSize);
}
struct timeval{
	long tv_sec;  
	long tv_usec;  
};
 
struct timezone{
	int tz_minuteswest;  
	int tz_dsttime;  
};
*/

int Hash( int key, int TableSize ) {
    return key % TableSize;
}
HashTbl *InitHash( int TableSize )
{
	int i;
	HashTbl *HashTable;
	HashTable = malloc(sizeof(HashTbl));
	if( NULL == HashTable )
	{
		printf("HashTable malloc error\n");
		return;
	}
	HashTable->TableSize = TableSize;
	
	HashTable->Thelists = malloc(sizeof(List)*TableSize);
	if( NULL == HashTable->Thelists )
	{
		printf("HashTable malloc error\n");
		return;
	}
	for( i = 0; i < TableSize; i++)
	{
		HashTable->Thelists[i] = malloc(sizeof(ListNode));
		if( NULL == HashTable->Thelists[i] )
		{
			printf("HashTable malloc error\n");
			return;
		}
		else
		{
			HashTable->Thelists[i]->next = NULL;
			HashTable->Thelists[i]->prev = NULL;
		}	
	}
	return HashTable;
}
Position Find( int key, HashTbl *HashTable )
{
	int i,j;
	List L;
	Position P;
	i = Hash(key,HashTable->TableSize);
	L = HashTable->Thelists[i];
	P = L->next;
	while( P != NULL && P->data != key )
		P = P->next;
	return P;
}
void Insert( int key, HashTbl *HashTable )
{
	Position P,tmp;
	List L;
	P = Find(key,HashTable);
	
	if( NULL == P )
	{
		tmp = malloc(sizeof(ListNode));
		if( NULL == tmp )
		{
			printf("malloc error\n");
			return;
		}
		L = HashTable->Thelists[Hash(key,HashTable->TableSize)];
		tmp->data = key;
		tmp->next = L->next;
		if(L->next != NULL)
			L->next->prev = tmp;
		tmp->prev = L;
		L->next = tmp;
	}
	else
		printf("the key already exist\n");
}
int Retrieve( Position P )
{
	return P->data;
}
void Destory( HashTbl *HashTable )
{
	int i;
	List L;
	Position tmp,tmp2;
	for( i = 0; i < HashTable->TableSize; i++)
	{
		L = HashTable->Thelists[i];
		tmp = L->next;
		while(tmp->next != NULL)
		{
			tmp2 = tmp->next;
			free(tmp);
			tmp = tmp2;
		}
		free(L);
	}
	free(HashTable);
}
void main( void )
{
	HashTbl *HashTable;
	HashTable = InitHash(HASH_ENTRIES);
	struct timeval t1,t2;
	double timeuse;
	int i=0;
	char str[26];
	gettimeofday(&t1,NULL);

	for(i=0;i<OP_NUM;i++){
		Insert(i,HashTable);
	}
	gettimeofday(&t2,NULL);
	timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec)/1000000.0;
	printf("Use Time:%f\n",timeuse);
	Position P;
	P = Find(34,HashTable);
	printf("%d\n",Retrieve(P));
}

