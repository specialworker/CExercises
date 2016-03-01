#ifndef _HASH_H_
#define _HASH_H_
typedef struct _ListNode
{
	struct _ListNode *prev;
	struct _ListNode *next;
	int data;
}ListNode;
typedef ListNode *List;
typedef ListNode *Position;
typedef struct _HashTbl
{
	int TableSize;
	List *Thelists;
}HashTbl;
int Hash( int key, int TableSize );
HashTbl *InitHash( int TableSize );
void Insert( int key, HashTbl *HashTable );
Position Find( int key, HashTbl *HashTable );
void Destory( HashTbl *HashTable );
int Retrieve( Position P );
#endif

