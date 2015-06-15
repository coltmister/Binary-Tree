// ConsoleApplication4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
	int depth;
	int key;
	char value[17];
	Node* left;
	Node* right;
}Node;

Node* CreateNode(int key1,char value[17]);
Node* CreateNode1(int key1,char value[17]);
void PrintNode(Node* item, int depth);
Node* InsertNode(Node* root,Node* newNode);
void PrintSpaces(int n);
void FreeNode(Node* item);
Node* DeleteNode(Node* item,int key);
Node* FindItem(Node* root,int key);
Node* GetMin(Node* root);
Node* GetNext(Node* root, Node* key);
void PrintFileRecord(FILE* output, Node* root);
Node* ScanFileRecord(FILE* input);
Node* Balance(Node* root);

int _tmain(int argc, _TCHAR* argv[])
{
	//FILE* output = fopen("output.txt","w");
	//FILE* input = fopen("input.txt","r");
	//Node* head = ScanFileRecord(input);
	
	
	Node* newRoot;
	Node* head = CreateNode(8, "data");

	newRoot = CreateNode(14,"data");
	head = InsertNode(head,newRoot);
		newRoot = CreateNode(13,"data");
	head = InsertNode(head,newRoot);
		newRoot = CreateNode(3,"data");
	head = InsertNode(head,newRoot);
		newRoot = CreateNode(6,"data");
	head = InsertNode(head,newRoot);
		newRoot = CreateNode(1,"data");
	head = InsertNode(head,newRoot);
		newRoot = CreateNode(7,"data");
	head = InsertNode(head,newRoot);
		newRoot = CreateNode(4,"data");
	head = InsertNode(head,newRoot);

	/*scanf("%d",&key2);
	FindItem(head,key2);
	DeleteNode(head,key2)*/
	PrintNode(head,head->depth);
	Node* curr = GetMin(head);
	head = Balance(head);
	PrintNode(head,head->depth);
	//PrintFileRecord(output, curr);
	//while (curr != NULL)
	//{
	//curr = GetNext(head,curr);
	//	if (curr != NULL)
	//	{
	//		PrintFileRecord(output, curr);
	//	}
	//}
	
	//fclose(output);
	getchar();

	FreeNode(head);
	
	getchar();
	return 0;
}
Node* CreateNode(int key1,char value[17])
{
	Node* p = new Node;
	p->key=key1;
	p->depth = 0;

    strncpy(p->value, value, 17);
	
	p->depth = 0;
	p->left=NULL;
	p->right=NULL;

	return p;
	delete p;
}

void PrintNode(Node* item, int depth)
{
	if (item == NULL) return;
	PrintSpaces(depth);
	printf("key: %d value: %s\n", item->key, item->value);
	
	if (item->left != NULL)
	{
		PrintSpaces(depth);
		printf("left:");
		PrintNode(item->left,depth+1);
	}
	if (item->right != NULL)
	{
		PrintSpaces(depth);
		printf("right:");
		PrintNode(item->right,depth+1);
	}

}

void PrintSpaces(int n)
{
	for (int i = 0; i<n; i++) printf("  ");
}

Node* InsertNode(Node* root,Node* newNode)
{	
	if (newNode==NULL) return root;
	if (newNode->key < root->key)	
	{
		if (NULL == root->left)
		{
			newNode->depth = root->depth + 1;
			root->left = newNode;
		}
		else
		{
			root->left = InsertNode(root->left, newNode);
		}
		return root;
	}
	if( newNode->key > root->key)
	{
		if (NULL == root->right)
		{
			newNode->depth = root->depth + 1;
			root->right = newNode;
		}
		else
		{
			root->right = InsertNode(root->right, newNode);
		}
		return root;
	}
	if( newNode->key == root->key)
	{
		newNode->right = root->right;
		newNode->left = root->left;
		newNode->depth = root->depth;
		delete root;
		return newNode;
	}
}

void FreeNode(Node* item)
{
	if (item == NULL) return;

	if (item->left!=NULL)
	FreeNode(item->left);
	
	if (item->right!=NULL)
    FreeNode(item->right);
	
	delete item;
}
Node* DeleteNode(Node* item,int key)
{
	Node* result = NULL;
	Node* rightRoot;
	Node* leftMost;

	if (item==NULL) return NULL;	/*Если дерево T пусто, остановиться*/
	//Иначе сравнить K с ключом X корневого узла n.
	if (key>item->key)
	{/*Если K>X, циклически удалить K из правого поддерева Т*/
		item->right = DeleteNode(item->right,key);
		return item;
	}

	else if (key<item->key)
	{/*Если K<X, циклически удалить K из левого поддерева Т;*/
		item->left = DeleteNode(item->left,key);
		return item;
	}
	else	/*Если K=X, то необходимо рассмотреть три случая.*/
	{
		if (item->left == NULL && item->right == NULL)	/*Если обоих детей нет,*/
		{
			delete item;	/*то удаляем текущий узел и обнуляем 
							ссылку на него у родительского узла;*/
			return result;
		}
		/*Если одного из детей нет*/
		if (item->left == NULL && item->right != NULL)
		{
			result = item->right;	/*то значения полей ребёнка m ставим 
									вместо соответствующих значений корневого узла, */
			delete item;	/*и освобождаем память, занимаемую узлом m;*/
			return result;
		}
		if (item->left != NULL && item->right == NULL)
		{
			result = item->left;	/*то значения полей ребёнка m ставим 
									вместо соответствующих значений корневого узла, */
			delete item;/*и освобождаем память, занимаемую узлом m;*/
			return result;
		}
	/*	Если оба ребёнка присутствуют, то*/
		if (item->left != NULL && item->right != NULL)
		{
			rightRoot = item->right;
			leftMost = item->right;

			/*Если левый узел m правого поддерева отсутствует (n->right->left)*/
			
			if (rightRoot->left == NULL)	
			{
				/*Копируем поля и ссылки*/

				rightRoot->left = item->left;
				delete item;
				return rightRoot;
			}
			/*Иначе*/
			else if (leftMost->left != NULL)
			{
				while (leftMost->left !=NULL)	/*возьмем самый левый узел m,*/
				leftMost = leftMost->left;		/*правого поддерева n->right;*/
				
				/*скопируем данные (кроме ссылок на дочерние элементы) из leftMost в item;*/
				
				item->key = leftMost->key;
				strncpy(item->value,leftMost->value,17);

				/*рекурсивно удалим узел m.*/

				item->right = DeleteNode(item->right,key);
				return item;
			}

		}

	}

}
Node* FindItem(Node* root,int key)
{
	if (root == NULL) printf("NULL");
	if (root->key == key)
	{
		return root;
	}
	if (key > root->key) 
		return FindItem(root->right,key);
	if (key < root->key)
		return FindItem(root->left,key);
}

Node* GetMin(Node* root)
{
	if (root->left == NULL)
		return root;
	else return GetMin(root->left);
}
Node* GetParent(Node* root,Node* prev)
{
	Node* next = NULL;
	Node* parent = root;
		while (parent != prev)
		{ 
			if (prev->key < parent->key)
			{
				next = parent;
				parent = parent->left;
			}
			else 
				parent = parent->right;
		}
		return next;
}
Node* GetNext(Node* root, Node* current)
{	
	//Node* current = FindItem(root,key);
	Node* success = NULL;

	if (current==NULL) return NULL;
	if (current->right != NULL)
		return GetMin(current->right);
	else 
	{
		return GetParent(root,current);
	}
}

void PrintFileRecord(FILE* output,Node* curr)
{	
	fprintf(output,"%d %s ",curr->key, curr->value);
}
Node* ScanFileRecord(FILE* input)
{
	int key = 0;
	char value[17];
	Node* head;
	Node* newRoot;	
	fscanf(input,"%d %s",&key, value);
	head = CreateNode(key,value);
	while (!feof(input))
	{
		fscanf(input,"%d %s",&key, value);
		newRoot = CreateNode(key,value);
		head = InsertNode(head,newRoot);
	}
	return head;
}
Node* SmallLeftTurning(Node* head)
{
	Node* rightRoot = head->right;
	head->right = rightRoot->left;
	rightRoot->left = head;
	
	return rightRoot;
}
Node* SmallRightTurning(Node* head)
{
	Node* leftRoot = head->left;
	head->left = leftRoot->right;
	leftRoot->right = head;

	return leftRoot;
}
Node* BigLeftTurning(Node* head)
{
	Node* rightRoot = head->right;
	rightRoot = SmallRightTurning(rightRoot);
	Node* leftSubRootOfRightRoot = SmallLeftTurning(head);

	return leftSubRootOfRightRoot;
}
Node* BigRightTurning(Node* head)
{
	Node* leftRoot = head->left;
	leftRoot = SmallLeftTurning(leftRoot);
	Node* RightSubRootOfLeftRoot = SmallRightTurning(head);

	return RightSubRootOfLeftRoot;
}
int Height(Node* head)
{
	if (head == NULL) return 0;

	int resultl = 0;
	resultl = Height(head->left);
	int resultr = 0;
	resultr = Height(head->right);
	int max = 0;

	if (resultr<resultl) max = resultl+1;
	else max = resultr+1;
}
Node* Balance(Node* root)
{
	if (root == NULL)
		return NULL;
	else
	{
		if (Height(root->right) < Height(root->left) )
		{
			if (Height(root->left->right) <= Height(root->left->left))
				 root->left = SmallRightTurning(root);
			return BigRightTurning(root);
		}
		else 
		{
			if (Height(root->right->left) <= Height(root->right->right))
				return root->right = SmallLeftTurning(root);
			else return BigLeftTurning(root);
		}
	}
}
