#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTree.h"
#define max 1000
typedef BTree Slice;

int queue[100];
int val, dernier = 0;
int premier = -1; 

void errorB(char *s){
	fprintf(stderr, "%s", s);
	exit(EXIT_FAILURE);
}

void printNode(BTree root){
    if(!isEmptyBTree(root)) {
        printf("%d ", root->elem);
    }
}

// void enqueue(BTree root){
//     if(root != NULL){
//         dernier++;
//         queue[dernier] = root;
//     }
// }
// void dequeue(){
//     if(dernier>=premier){
//         BTree root = queue[premier];
//         printNode(root);
//         premier++;
//         enqueue(root->left);
//         enqueue(root->right);
//     }
// }


// void bfs(BTree root){
//     if(root != NULL){
//         enqueue(root);
//         do{
//             dequeue(root);
//         }while(premier <= dernier);
//     }
// }
/*****************************************************************************/
/**************************** fonctions de base ******************************/
/*****************************************************************************/
BTree makeB1(){
    return makeNode(10,
              makeNode(15,
                   makeNode(31,
                         makeLeaf(10),
                         makeNode(2,
                             makeEmptyBTree(),
                             makeNode(0,
                             makeLeaf(31),
                             makeEmptyBTree()
                             )
                        )
                    ),
                    makeNode(77,
                    makeLeaf(6),
                    makeEmptyBTree()
                    )
                ),makeNode(100,
                makeLeaf(12),
                makeLeaf(28)
                )
            );
}

BTree makeB2(){
    return makeNode(120,
              makeNode(15,
                   makeNode(31,
                         makeLeaf(10),
                         makeNode(2,
                             makeEmptyBTree(),
                             makeNode(22,
                             makeLeaf(31),
                             makeEmptyBTree()
                             )
                        )
                    ),
                    makeNode(77,
                    makeLeaf(6),
                    makeEmptyBTree()
                    )
                ),makeNode(100,
                makeLeaf(12),
                makeLeaf(28)
                )
            );
}

BTree makeSubT(){
    return makeNode(31,
                         makeLeaf(10),
                         makeNode(2,
                             makeEmptyBTree(),
                             makeNode(22,
                             makeLeaf(31),
                             makeEmptyBTree()
                             )
                        )
                    );
}

typedef struct Pile{
Slice T[max];
int sommet ;
}Pile;

Pile InitPile (void)
{   Pile p;
	p.sommet = -1;
	return p;
}

void empiler (Pile *p, BTree x){
	if(p->sommet == max-1){
		printf("Pile pleine");
	}
	p->sommet++;
	p->T[p->sommet] = x;
}

BTree depiler (Pile *p) {
	if(PileVide(p)){
		printf("Pile vide");
		return NULL;
	}
	Slice x = p->T[p->sommet];
	 p->sommet-- ;
	return x;
}

int sommetPile (Pile p){
	return (p.T[p.sommet]);
}

int PileVide (Pile *p){
	return (p->sommet == -1);
}
int PilePleine (Pile *p){
	return p->sommet == max;
}


BTree makeEmptyBTree(void){
	return (BTree)NULL;	
}

BTree makeNode(Element e, BTree l,  BTree r){
	BTree new;
	if ((new=(BTree)malloc(sizeof(Node)))==NULL) errorB("Allocation rat�e!");
	new->elem=e;
	new->left=l;
	new->right=r;
	return new;
}

BTree makeLeaf(Element e){
	return makeNode(e,makeEmptyBTree(),makeEmptyBTree());
}


int isEmptyBTree(BTree bt){
	return (bt==NULL);
}

Element root(BTree bt){
	if(isEmptyBTree(bt)) errorB("Pas de noeud � la racine d'un arbre vide!!!");
	return bt->elem;
}


BTree leftChild(BTree bt){
	if(isEmptyBTree(bt)) errorB("Pas de fils gauche dans un arbre vide!!!");
	return bt->left;
}

BTree rightChild(BTree bt){
	if(isEmptyBTree(bt)) errorB("Pas de fils droit dans un arbre vide!!!");
	return bt->right;
}

int isLeaf(BTree bt){
	return !isEmptyBTree(bt) && isEmptyBTree(leftChild(bt)) && isEmptyBTree(rightChild(bt));
}

void freeNode(Node *c){
	free(c);
}

/*****************************************************************************/
/*************************** fonctions bas niveau ****************************/
/*****************************************************************************/

void insertRight(Node *n, Element e){
	if(!isEmptyBTree(n) && isEmptyBTree(rightChild(n)))
		n->right=makeLeaf(e);
	else errorB("insertRight impossible!");
}

void insertLeft(Node *n, Element e){
	if(!isEmptyBTree(n) && isEmptyBTree(leftChild(n)))
		n->left=makeLeaf(e);
	else errorB("insertLeft impossible!");
}

Element deleteRight(Node *n){
	if(isEmptyBTree(n) || !isLeaf(rightChild(n)))
		errorB("deleteRight imossible!");
		
	Element res=root(n->right);
	n->right=makeEmptyBTree();
	return res;
}

Element deleteLeft(Node *n){
	if(isEmptyBTree(n)  || !isLeaf(leftChild(n)))
		errorB("deleteLeft imossible!");
		
	Element res=root(n->left);
	n->left=makeEmptyBTree();
	return res;
}

void insertRightmostNode(BTree *bt, Element e){
	if(isEmptyBTree(*bt))
		*bt=makeLeaf(e);
	else{
		BTree tmp=*bt;
		while(!isEmptyBTree(rightChild(tmp)))
			tmp=rightChild(tmp);
		insertRight(tmp,e);
	}
}

Element deleteLeftmostNode(BTree *bt){
	Element res;
	if(isEmptyBTree(*bt))
		errorB("deleteLeftmostNode imossible!");
	if(isEmptyBTree(leftChild(*bt))){
		res=root(*bt);
		*bt=rightChild(*bt);
	}
	else{
		BTree tmp=*bt;
		while(!isEmptyBTree(leftChild(leftChild(tmp))))
			tmp=leftChild(tmp);
		res=root(leftChild(tmp));
		tmp->left=(tmp->left)->right;
	}
	return res;
}
