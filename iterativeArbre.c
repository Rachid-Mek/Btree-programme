#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Btree.c" 

// fonction d'affichage en parcour infixé
void afficheArbre(Node* noeud)
{
    if (!isEmptyBTree(noeud))
    {
        afficheArbre(noeud->left);
        printf("cle : %d \n",noeud->elem);
        afficheArbre(noeud->right);
    }
}

// la complexite est O(N) car on a chaque fois empiler puis comparer n noued (le pire cas est identique) 
int equalBTrees(BTree bt1, BTree bt2) {
Pile p = InitPile();  
empiler(&p,bt1);
empiler(&p,bt2);
while (!PileVide(&p))
{   //le prmier element est celle de bt2
    bt2=depiler(&p);
    bt1=depiler(&p);
    //si bt1 et bt2 ne sont pas nil 
    if(bt1 && bt2){
        // on test si bt1->elem = bt2->elem
        if (root(bt1)== root(bt2))
        {
            empiler(&p,rightChild(bt1));
            empiler(&p,rightChild(bt2));
            empiler(&p,leftChild(bt1));
            empiler(&p,leftChild(bt2));
        }
        //si bt1->elem =/= bt2->elem alors return faux
        else{
            return 0;   
            }
    }
    //si bt1 et bt2 sont a nil alors continue (cas des deux arbre on a pas un fils gauche...)
    else if(!bt1 && !bt2){
        continue;
    }
    else{
        return 0 ;
    }
}
}
//la complexite est o(m*n)
int isSubBTree(BTree sbt, BTree bt){
Pile p = InitPile() ;
    if(isEmptyBTree(sbt)){
        return 1 ;
    }
    if(isEmptyBTree(bt)){
        return 0;
    }
    empiler(&p,bt);
    while (!PileVide(&p))
    {
        bt=depiler(&p);
        if (root(bt)==root(sbt))
        {
            if (equalBTrees(bt,sbt))
            {
                return 1;
            }
            empiler(&p,bt->left);
            empiler(&p,bt->right);
        }
    }
}

int findElem(BTree bt,Element e){
Pile p = InitPile() ;

empiler(&p,bt);
while (!PileVide(&p))
{
    bt=depiler(&p);
    
    if (root(bt) == e)
    {
        return 1;
    }
    if (bt->left)
    {
        empiler(&p,bt->left);
    }
    if (bt->right)
    {
        empiler(&p,bt->right);
    }
}
return 0;
}

Element findMin(BTree bt){
    Pile p = InitPile() ;
    empiler(&p,bt);
    Element min = bt->elem;
    while (!PileVide(&p))
    {
       BTree t=depiler(&p);
        if (t->elem < min)
        min = t->elem;
        if (t->left)
        {
            empiler(&p,t->left);
        }
        if (t->right)
        {
            empiler(&p,t->right);
        }
    }
    return min;
}

void printWidthOrder(BTree bt){
    Pile p = InitPile() ;
    empiler(&p,bt);
    while (!PileVide(&p))
    {
        bt=depiler(&p);
        printf("%d ",root(bt));
        if (bt->left)
        {
            empiler(&p,bt->left);
        }

        if (bt->right)
        {
            empiler(&p,bt->right);
        }
    }
}

int main(int argc, char const *argv[])
{

    BTree racineB1 , racineB2, p ;
    racineB1 = makeB1() ;
    racineB2 = makeB2();
    p=makeSubT();

    printf("affichage arbre bt1 : \n");
    afficheArbre(racineB1);
    printf("affichage arbre b2 : \n");
    afficheArbre(racineB2);
     printf("affichage arbre p : \n");
    afficheArbre(p);

    if (equalBTrees(racineB1,racineB2))
        printf("les deux arbres sont identique \n");
    else{
        printf("les deux arbres ne sont pas identique ! \n");}
    
    if (isSubBTree(p, racineB1))
        printf("p est un sous arbre de racine B1 \n");
    else
        printf("p n'est pas sous arbre de racine B1 \n");
     

     if (findElem(racineB1,10)){
        printf("l'element est dans l'arbre \n");
     }
     else{
        printf("l'element n'est pas dans l'arbre \n");
        }

  printf("le minimum de l'arbre 1 est : %d \n",findMin(racineB1));    
  printf("le minimum de l'arbre 2 est : %d \n",findMin(racineB2));

  printWidthOrder(racineB1);
    return 0;
}