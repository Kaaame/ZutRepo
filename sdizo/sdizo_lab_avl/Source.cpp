#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <fstream>

typedef struct node
{
	node * rightnode;
	node * leftnode;
	int key;
	int balance = 0;
	char arr[10];
} node;

typedef struct stack
{
	stack * prev;
	node * var;
} stack;

node * pop(stack ** stos);
void push(stack ** stos, node * fnode);
node * top(stack ** stos);

void initalize(node ** head, stack ** stos);
bool addelement(node ** fnode, stack ** stos, int key);
void str(int key, char arr[10]);
void generate(node ** fnode, stack ** stos, int num);
bool findkey(node ** fnode, int key);
bool deletebykey(int key, node ** root);

void removenode(node * fnode, node ** root);

node * findparentnode(node ** root, int key);
node * findnode(node ** fnode, int key);

node * pred(node * fnode);
node * succ(node * fnode);

node * max(node ** fnode);
node * min(node ** fnode);

void preorder(node ** root, int * counter);
void inorder(node ** root, int * counter);
void postorder(node ** root, int * counter);

node * rightrotation(node ** root, node * fnode);
node * leftrotation(node ** root, node * fnode);
node * rotationlr(node ** root, node *fnode);
node * rotationrl(node ** root, node *fnode);
node * FreeTree(struct node ** root);

int * readarr(const char *);

int height(node ** root);
int treebalance(node ** root);

int main()
{
	srand(2137);
	int counter = 0;

	stack * stos = (stack *)malloc(sizeof(stack));

	int x;//, k1, k2, k3, k4;
	int n[] = { 100000, 150000, 200000, 250000, 300000, 350000, 400000, 450000, 500000 };
	clock_t timet[5];
	int wyniki[5];

	clock_t start, stop;
	/*FILE * fp = fopen("inlab04.txt", "r");
	if (fp != NULL)
	{
		fscanf(fp, "%d %d %d %d %d", &x, &k1, &k2, &k3, &k4);
		fclose(fp);
	}*/
	//std::fstream file;
	//file.open("rand.txt", std::fstream::in);

	int * keys;
	keys = readarr("rand.txt");
	node * head = NULL;
	head = (node *)malloc(sizeof(node));
	initalize(&head, &stos);
	/*x = 500000;
	wyniki[0] = 0;
	wyniki[1] = 0;
	start = clock();

	for (int i = 0; i < n[8]; i++)
	{
		//int randkey = rand() % 25000 * (rand() % 400);// 10m
		int randkey = keys[i];// 10m

		if (addelement(&head, &stos, randkey)) wyniki[0]++;
	}
	stop = clock();
	timet[0] = stop - start;
	start = clock();
	for (int i = 0; i < n[8]/2; i++)
	{
		//int randkey = rand() % 25000 * (rand() % 400);// 10m
		int randkey = keys[i];// 10m

		if (deletebykey(randkey, &head)) wyniki[1]++;
	}
	stop = clock();
	timet[1] = stop - start;
	printf("czas wstawiania = %lu ms\twstawiono: %d\n", timet[0], wyniki[0]);
	printf("czas usuwania = %lu ms\tusunieto: %d\n", timet[1], wyniki[1]);
	_getch();*/
	for (int j = 0; j < 9; j++)
	{

		initalize(&head, &stos);
		wyniki[0] = 0;//dodawanie z pliku
		wyniki[1] = 0;//wyszukiwanie z pliku
		wyniki[2] = 0;//wyszukiwanie losowo
		wyniki[3] = 0;//usuwanie losowo
		wyniki[4] = 0;//usuwanie z pliku

#pragma region onebloc
		start = clock();
		for (int i = 0; i < n[j]; i++)
		{
			int randkey = keys[i];// 10m

			if (addelement(&head, &stos, randkey)) wyniki[0]++;
		}
		stop = clock();
		timet[0] = stop - start;
#pragma endregion onebloc

#pragma region onebloc
		start = clock();
		for (int i = 0; i < n[j]; i++)
		{
			int randkey = keys[i];// 10m

			if (findkey(&head, randkey)) wyniki[1]++;
		}
		stop = clock();
		timet[1] = stop - start;
#pragma endregion onebloc

#pragma region onebloc
		start = clock();
		for (int i = 0; i < n[j]; i++)
		{
			int randkey = rand() % 25000 * (rand() % 400);// 10m

			if (findkey(&head, randkey)) wyniki[2]++;
		}
		stop = clock();
		timet[2] = stop - start;
#pragma endregion onebloc

#pragma region onebloc
		start = clock();
		for (int i = 0; i < n[j]; i++)
		{
			int randkey = rand() % 25000 * (rand() % 400);// 10m

			if (deletebykey(randkey, &head)) wyniki[3]++;
		}
		stop = clock();
		timet[3] = stop - start;
#pragma endregion onebloc

#pragma region onebloc
		start = clock();
		for (int i = 0; i < n[j]/2; i++)
		{
			int randkey = keys[i];// 10m

			if (deletebykey(randkey, &head)) wyniki[4]++;
		}
		stop = clock();
		timet[4] = stop - start;
#pragma endregion onebloc

		printf("%d elementow(z pliku): czas wstawiania = %lu ms\twstawiono: %d\n",n[j], timet[0], wyniki[0]);
		printf("%d elementow(z pliku): czas wyszukiwania = %lu ms\twyszukano: %d\n", n[j], timet[1], wyniki[1]);
		printf("%d elementow(losowo): czas wyszukiwania = %lu ms\twyszukano: %d\n", n[j], timet[2], wyniki[2]);
		printf("%d elementow(losowo): czas usuwania = %lu ms\tusunieto: %d\n", n[j], timet[3], wyniki[3]);
		printf("%d elementow(z pliku): czas usuwania = %lu ms\tusunieto: %d\n\n", n[j], timet[4], wyniki[4]);
		FreeTree(&head);
			

	}
	_getch();

	//printf("Czas trwania %lu ms\nBalans drzewa = %i", (stop - start), treebalance(&head));



}

void initalize(node ** head, stack ** stos)
{
	*head = (node *)malloc(sizeof(node));
	(*head)->leftnode = NULL;
	(*head)->rightnode = NULL;
	(*head)->balance = 0;
	(*head)->key = 10000001;

	(*stos)->var = NULL;
	(*stos)->prev = NULL;
}

bool addelement(node ** root,stack ** stos,int key)
{
	if ((*root)->key == 10000001)
	{
		(*root)->key = key;
		str(key, (*root)->arr);
		return true;
	}

	while ((*stos)->var != NULL)
	{
		pop(stos);
	}

	node * hold = *root; //korzen na starcie
	node * parenthold = NULL;
	node * added = (node *)malloc(sizeof(node));

	added->leftnode = NULL;
	added->rightnode = NULL;
	added->balance = 0;
	added->key = key;
	str(key, added->arr);

	while (hold)
	{
		if (hold->key == key)
		{
			//printf("ten sam klucz\n");
			free(added);
			//break;
			return false;
		}
		if (added->key < hold->key)
		{
			push(stos, hold);
			parenthold = hold;
			hold = hold->leftnode;
		}
		else
		{
			push(stos, hold);
			parenthold = hold;
			hold = hold->rightnode;
		}
	}

	if (added->key < parenthold->key)
	{
		parenthold->leftnode = added;
		//parenthold->balance -= 1;
	}
	else
	{
		parenthold->rightnode = added;
		//parenthold->balance += 1;
	}

	if (parenthold->balance != 0)
	{
		parenthold->balance = 0;
		return true;
	}
	if (parenthold->leftnode == added) parenthold->balance -= 1;
	else parenthold->balance += 1;
	//printf(" znaleziono klucz\n ");
	pop(stos);
	hold = pop(stos);//parent parentholda
	/*while (hold)
	{
		int balance = treebalance(&hold) - treebalance(&added);
		if (balance > 0) hold->balance--;
		else balance++;
		if (hold->balance == 0) return true;
		if (hold->balance == 1 || hold->balance == -1)
		{
			added = hold;
			hold = pop(stos);
			continue;
		}
		if (hold->balance == 2)
		{
			if (hold->rightnode->balance == 1)
			{
				hold->balance = 0;
				hold->rightnode->balance = 0;
				rotationleft(root, pop(stos), hold, hold->rightnode);
			}
			else
			{
				if (hold->leftnode == NULL) hold->balance = 0;
				else hold->balance = -1;

				hold->rightnode->balance = 0;
				if (hold->rightnode->leftnode->leftnode == NULL) hold->rightnode->leftnode->balance = 0;
				else hold->rightnode->leftnode->balance = -1;
				rotationright(root, hold, hold->rightnode, hold->rightnode->leftnode);
				rotationleft(root, pop(stos), hold, hold->rightnode);
			}
		}
		else if (hold->balance == -2)
		{
			if (hold->leftnode->balance == -1)
			{
				hold->balance = 0;
				hold->leftnode->balance = 0;
				rotationright(root, pop(stos), hold, hold->leftnode);
			}
			else
			{
				if (hold->rightnode == NULL) hold->balance = 0;
				else hold->balance = 1;
				hold->leftnode->balance = 0;
				if (hold->leftnode->rightnode->rightnode == NULL) hold->leftnode->rightnode->balance = 0;
				else hold->leftnode->rightnode->balance = 1;
				rotationleft(root, hold, hold->leftnode, hold->leftnode->rightnode);
				rotationright(root, pop(stos), hold, hold->leftnode);
			}
		}
		return NULL;
	}*/
	
	while (hold)
	{
		if (hold->balance != 0) break;
		if (hold->leftnode == parenthold) hold->balance -= 1;
		else hold->balance += 1;
		parenthold = hold;
		hold = pop(stos);
	}


	if (hold == NULL)//hold jest teraz rodzicem parentholda pokrecone xd
	{
		return true;
	}
	if (hold->balance == -1)//przesuniete w lewo
	{
		if (hold->rightnode == parenthold)//ma prawego
		{
			hold->balance = 0;
			return true;
		}
		if (parenthold->balance == 1) rotationlr(root, hold);
		else leftrotation(root, hold);
		return true;
	}
	else
	{
		if (hold->leftnode == parenthold)
		{
			//hold->balance = treebalance(&hold);
			hold->balance = 0;
			return true;
		}
		if (parenthold->balance == -1) rotationrl(root, hold);
		else rightrotation(root, hold);
		return true;
	}
}

void str(int key, char arr[10])
{
	sprintf(arr, "%d", key);
}

void generate(node ** fnode, stack ** stos, int num)
{
	int genkey;
	for (int i = 0; i < num; i++)
	{
		do
		{
			genkey = rand() % 25000 * (rand() % 400);
		} while (!addelement(fnode, stos, genkey));//zle
	}
}

bool findkey(node ** fnode, int key)
{
	node * hold = *fnode;
	if (*fnode == NULL) return false;
	while (hold != NULL && hold->key != key)
	{
		if (key < hold->key) hold = hold->leftnode;
		else hold = hold->rightnode;
	}
	if (hold == NULL) return false;
	return true;
}


node * min(node ** fnode)
{
	node * hold = *fnode;
	if (hold != NULL)
	{
		while (hold->leftnode)
		{
			hold = hold->leftnode;
		}
	}
	return hold;
}

node * max(node ** fnode)
{
	node * hold = *fnode;
	while (hold->rightnode)
	{
		hold = hold->rightnode;
	}
	return hold;
}

node * pred(node * fnode)
{
	if (fnode->leftnode) return max(&(fnode->leftnode));
	node * hold;
	do
	{
		hold = fnode;
		fnode = fnode->rightnode;
	} while (fnode != NULL && (fnode->rightnode != hold));
	return fnode;
}

node * succ(node * fnode)
{
	if (fnode->rightnode) return min(&(fnode->rightnode));
	node * hold;
	do
	{
		hold = fnode;
		fnode = fnode->rightnode;
	} while (fnode != NULL && (fnode->leftnode != hold));
	return fnode;
}

void removenode(node * fnode, node ** root)//fnode usuwany, root korzen
{
	node * parenthold = findparentnode(root, fnode->key);
	node * delhold = fnode, *replacehold;

	bool deleted = false;

	stack * stos = (stack *)malloc(sizeof(stack));
	stos->var = NULL;
	stos->prev = NULL;

	node * hold = *root;
	while (hold != NULL && hold->key != fnode->key)
	{
		push(&stos, hold);
		if (fnode->key < hold->key) hold = hold->leftnode;
		else hold = hold->rightnode;
	}

	int parentlr;
	if (fnode != *root)
	{
		if (parenthold->rightnode == delhold && fnode) parentlr = 1;
		else parentlr = 0;
	}
	else parentlr = 0;
	if (delhold->leftnode == NULL && delhold->rightnode == NULL)
	{	
		if (parenthold)
		{
			if (parenthold->rightnode == delhold) parenthold->rightnode = NULL;
			if (parenthold->leftnode == delhold) parenthold->leftnode = NULL;
			free(delhold);

		}
		else
		{
			free(*root);
			*root = NULL;
		}
		deleted = true;


	}//brak potomkow
	if (!deleted)
	{
		if ((delhold->leftnode == NULL && delhold->rightnode != NULL) || (delhold->leftnode != NULL && delhold->rightnode == NULL))
		{
			int leftright;//jezeli lewo to 0, prawo to 1

			if (delhold->rightnode == NULL) leftright = 0;
			else leftright = 1;

			if (parentlr == 0)
			{
				if (leftright == 0)
				{
					replacehold = delhold->leftnode;
					if (fnode != *root) parenthold->leftnode = replacehold;
					free(delhold);
				}
				else
				{
					replacehold = delhold->rightnode;
					if (fnode != *root) parenthold->leftnode = replacehold;
					free(delhold);
				}
			}
			else
			{
				if (leftright == 0)
				{
					replacehold = delhold->leftnode;
					if (fnode != *root) parenthold->rightnode = replacehold;
					free(delhold);
				}
				else
				{
					replacehold = delhold->rightnode;
					if (fnode != *root) parenthold->rightnode = replacehold;
					free(delhold);
				}
				if (fnode == *root) *root = replacehold;

			}
			if (fnode == *root) *root = replacehold;
			deleted = true;

			//return;
		}//jeden potomek w
	}
	//return;
	if (!deleted)
	{
		//jeden potomek w usuwanym
		if (delhold->leftnode && delhold->rightnode)
		{
			if (fnode != *root)
			{
				node * predes;
				replacehold = pred(fnode);

				//node * parentfnode = findparentnode(root, delhold->key);

				predes = findparentnode(root, replacehold->key); //ojciec poprzednika
				if (replacehold->leftnode) predes->rightnode = replacehold->leftnode;// jezeli poprzednik mial lewa odnoge, podlacz do drzewa
																					 //predes->rightnode = NULL;
				predes->leftnode = NULL;
				predes->rightnode = NULL;

				replacehold->leftnode = delhold->leftnode;	//	przygotowanie do usuniecia
				replacehold->rightnode = delhold->rightnode;//

				if (parenthold->leftnode == delhold) parenthold->leftnode = replacehold;
				else parenthold->rightnode = replacehold;

				//else qwe->rightnode = delhold;
				free(delhold);
			}
			else
			{
				replacehold = pred(*root);
				node * predes = findparentnode(root, replacehold->key);
				if (predes == NULL)
				{

				}

				replacehold->rightnode = (*root)->rightnode;
				replacehold->leftnode = (*root)->leftnode;

				free(*root);

				predes->rightnode = NULL;
				predes->leftnode = NULL;

				*root = replacehold;
			}
			deleted = true;
		}//dwa potomki
	}
	if (deleted)
	{
		/**/
		hold = pop(&stos);
		parenthold = pop(&stos);
		while (parenthold)
		{
			parenthold->balance = treebalance(&parenthold);
			if(parenthold->rightnode) parenthold->rightnode->balance = treebalance(&parenthold->rightnode);
			if (parenthold->leftnode) parenthold->leftnode->balance = treebalance(&parenthold->leftnode);

			if (!parenthold->balance)
			{
				if (parenthold->leftnode) parenthold->balance = -1;
				else parenthold->balance = 1;
				break;
			}
			else
			{
				if (((parenthold->balance == 1) && (parenthold->leftnode == hold)) || ((parenthold->balance == -1) && (parenthold->rightnode == hold)))
				{
					parenthold->balance = 0;
					hold = parenthold;
					parenthold = pop(&stos);
				}
				else
				{
					replacehold = (parenthold->leftnode == hold) ? parenthold->leftnode : parenthold->rightnode;
					if (replacehold)
					{
						if (!(replacehold->balance))
						{
							if (parenthold->balance <= -1)leftrotation(root, parenthold);
							else rightrotation(root, parenthold);
							break;
						}
						else if (parenthold->balance == replacehold->balance)
						{
							if (parenthold->balance <= -1) leftrotation(root, parenthold);
							else rightrotation(root, parenthold);
							hold = replacehold;
							//pop(&stos);

							parenthold = pop(&stos);
							continue;
						}
					}
					//else
					//{
						/*if (parenthold->rightnode == NULL && parenthold->leftnode == NULL)
						{
							hold = parenthold;
							parenthold = pop(&stos);
							continue;
						}*/
						if (parenthold->rightnode)
						{						
							if (parenthold->rightnode->balance >= 2)
							{
								rightrotation(root, parenthold);
								hold = parenthold;
								parenthold = pop(&stos);
								continue;
							}
						}
						if (parenthold->leftnode)
						{

							if (parenthold->leftnode->balance <= -2)
							{
								leftrotation(root, parenthold);
								hold = parenthold;
								parenthold = pop(&stos);
								continue;
							}
						}
						if (parenthold->balance >= 2)
						{
							if (parenthold->rightnode->balance <= -1)
							{
								rotationrl(root, parenthold);
							}
							else 
							{
								rightrotation(root, parenthold->rightnode);
							}
							hold = parenthold;
							parenthold = pop(&stos);
							continue;
						}
						if (parenthold->balance <= -2)
						{
							if (parenthold->leftnode->balance >= 1)
							{
								rotationlr(root, parenthold);
							}
							else
							{
								leftrotation(root, parenthold->leftnode);
							}
							hold = parenthold;
							parenthold = pop(&stos);
							continue;
						}

						if (parenthold->balance == 1)rotationrl(root, parenthold);
						else rotationlr(root, parenthold);
						hold = parenthold;
						parenthold = pop(&stos);
					//}
				}
			}
			//parenthold = pop(&stos);
		}
	}
	delhold = NULL;
	return;
}

node * findparentnode(node ** root, int key)
{
	node * hold = *root;
	node * parenthold = NULL;
	while (hold != NULL && hold->key != key)//chyba dziala
	{
		parenthold = hold;
		if (key < hold->key) hold = hold->leftnode;
		else hold = hold->rightnode;
	}
	if (hold == NULL) return NULL;
	return parenthold;
}

bool deletebykey(int key, node ** root)
{
	if (!findkey(root, key))
	{
		//printf("nie znaleziono klucza\n");
		return false;
	}
	else
	{
		//printf("USUWANKO\n");
		node * fnode = findnode(root, key);
		removenode(fnode, root);
		return true;
	}
}

node * findnode(node ** fnode, int key)
{
	node * hold = *fnode;
	while (hold != NULL && hold->key != key)
	{
		if (key < hold->key) hold = hold->leftnode;
		else hold = hold->rightnode;
	}
	if (hold == NULL) return NULL;
	return hold;
}

void preorder(node ** root, int * counter)
{
	if (*root)
	{
		printf("Adres lewego: %p\t Adres prawego: %p\t klucz: %i\n", (void*)(*root)->leftnode, (void*)(*root)->rightnode, (*root)->key);
		*counter++;
		preorder(&((*root)->leftnode), counter);
		preorder(&((*root)->rightnode), counter);
	}

}
void inorder(node ** root, int * counter)
{
	if (*root)
	{
		inorder(&((*root)->leftnode), counter);
		*counter++;
		printf("Adres lewego: %p\t Adres prawego: %p\t klucz: %i\tbalans: %i\n", (void*)(*root)->leftnode, (void*)(*root)->rightnode, (*root)->key, (*root)->balance);
		inorder(&((*root)->rightnode), counter);
	}
}
void postorder(node ** root, int * counter)
{
	if (*root)
	{
		postorder(&((*root)->leftnode), counter);
		postorder(&((*root)->rightnode), counter);
		*counter++;
		printf("Adres lewego: %p\t Adres prawego: %p\t klucz: %i\tbalans: %i\n", (void*)(*root)->leftnode, (void*)(*root)->rightnode, (*root)->key, (*root)->balance);
	}
}

node * pop(stack ** stos)
{
	if ((*stos)->var == NULL) return NULL;
	node * top = ((*stos)->var);
	stack * deltemp = (*stos);
	(*stos) = (*stos)->prev;
	free(deltemp);
	return top;
}

void push(stack ** stos, node * fnode)
{
	stack * newtop = (stack *)malloc(sizeof(stack));
	newtop->var = fnode;
	newtop->prev = (*stos);
	(*stos) = newtop;
}

node * top(stack ** stos)
{
	return (*stos)->var;
}

node * rightrotation(node ** root, node * fnode)
{
	node * right = fnode->rightnode;
	node * parent = findparentnode(root, fnode->key);
	fnode->rightnode = right->leftnode;
	if (parent)
	{
		if (parent->leftnode == fnode) parent->leftnode = right;
		else parent->rightnode = right;
	}
	else *root = right;

	right->leftnode = fnode;
	
	right->balance = treebalance(&right);
	fnode->balance = treebalance(&fnode);
	return right;
}



node * leftrotation(node ** root, node * fnode)
{
	node * left = fnode->leftnode;//fnode - a, left - b, parent - p
	node * parent = findparentnode(root, fnode->key);
	fnode->leftnode = left->rightnode;
	if (parent)
	{
		if (parent->leftnode == fnode) parent->leftnode = left;
		else parent->rightnode = left;
	}
	else *root = left;
	left->rightnode = fnode;
	
	left->balance = treebalance(&left);
	fnode->balance = treebalance(&fnode);

	return left;
}

node * rotationlr(node ** root, node *fnode)
{
	rightrotation(root, fnode->leftnode);
	leftrotation(root, fnode);
	return NULL;
}

node * rotationrl(node ** root, node *fnode)
{
	leftrotation(root, fnode->rightnode);
	rightrotation(root, fnode);
	return NULL;
}

int height(node ** root)
{
	if (*root == NULL) return 0;
	int l = height(&((*root)->leftnode));
	int r = height((&(*root)->rightnode));
	if (l > r)return l + 1;
	return r + 1;
}

int treebalance(node ** root)
{
	return(height(&((*root)->rightnode)) - height(&((*root)->leftnode)));
}

struct node * FreeTree(struct node ** root)
{
	if (*root)
	{
		FreeTree(&((*root)->leftnode));
		FreeTree(&((*root)->rightnode));
		free(*root);
	}
	return NULL;
}

int * readarr(const char * filename)
{
	std::fstream file;
	int * arr = new int[500000];
	int counter = 0;
	file.open(filename, std::fstream::in);
	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> arr[counter];
			counter++;
		}
	}
	return arr;
}