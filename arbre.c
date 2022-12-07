#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Btree.c" 

// fonction d'affichage en parcour infixé
void afficheArbre(Node* noeud)
{
    if (!isEmptyBTree(noeud))
    {   
        printf("cle : %d \n",noeud->elem);
        afficheArbre(noeud->left);
        afficheArbre(noeud->right);
    }
}


// fonction recursive
//la complexite de cette fonction est on O(N) tel que n est le nombre de noued
//le pire cas est quand les deux arbre sont identique  
int equalBTrees(BTree bt1, BTree bt2) {
    //les deux arbres sont a nil
    if(isEmptyBTree(bt1) && isEmptyBTree(bt2))  
          return 1;  
    
    if(bt1->elem != bt2->elem)
          return 0 ;
      
    //on a au moins un des deux arbre qui est a nil 
    if(isEmptyBTree(bt1) || isEmptyBTree(bt2))  
          return 0; 
      
    //si les deux arbres ne sont pas a nil alors on compare les cle des noeuds  
    //on reptons pour le fils gauche et le fils droit  
    if(!isEmptyBTree(bt1)  && !isEmptyBTree(bt2)) {  
            
     return (((bt1->elem == bt2->elem))&&
            (equalBTrees(leftChild(bt1), leftChild(bt2)))&& 
            (equalBTrees(rightChild(bt1), rightChild(bt2))));  
    }
    return 0; 
}

//L'idée est de vérifier à chaque nœud le sous-arbre.
// la complexité est on O(M*N) car on a traversée les sous-arbre Sbt de taille M pour chaque nœud N de l'arbre bt
int isSubBTree(BTree sbt, BTree bt){
    //si le sous arbre sbt est egale a l'arbre bt alors on retourn vrai sinon on avance a gauche ou a droite danst bt
    if(isEmptyBTree(sbt))
        return 1;
        
    if(isEmptyBTree(bt))
        return 0;
        
    if (equalBTrees(sbt,bt)){
        return 1;
        }   
/* Si l'arbre avec la racine comme nœud actuel ne correspond pas, alors 
  essayez les sous-arbres gauche et droit un par un */
    return ((isSubBTree(sbt,bt->left))||(isSubBTree(sbt,bt->right)));
}

// la complexité est O(n) car j'ai utilisé la récursivité pour parcourir N nœuds de l'arbre.
int findElem(BTree bt, Element e){
    if (isEmptyBTree(bt))
        return 0;

    if (bt->elem == e)
        return 1;

    return (findElem(leftChild(bt),e)||findElem(rightChild(bt),e));
}

// la complexité est en O(n) car on va parcourir tous les noeud dans le pire cas;
Element findMin(BTree bt){
    
    if (isEmptyBTree (bt))
    {
        return __INT_MAX__ ;
    }
    
    Element min = bt->elem;
    int lkey = findMin(leftChild(bt));
    int rkey = findMin(rightChild(bt));

// on doit avoir les cle de fils gauche et fils droit a chaque noued pour comparer et avoir le min
    if (min>lkey)
    {
        min=lkey ;
    }
    if (min>rkey)
    {
        min=rkey;
    }
    return min;
}


// la complexité est en O(n) car on va parcourir tous les noeud dans le pire cas;
void printWidthOrder(BTree bt){
    val = bt->elem;
    queue[premier+1]=val;
    if ((premier <= dernier)&&(bt->elem == queue[premier+1]))
    {
        if (!isEmptyBTree(bt->left))
            queue[++dernier] = bt->left->elem;
        if (!isEmptyBTree(bt->right))
            queue[++dernier] = bt->right->elem;
        premier++;
    }
    if (!isEmptyBTree(bt->left))
    {
        printWidthOrder(bt->left);
    }

    if (!isEmptyBTree(bt->right))
    {
        printWidthOrder(bt->right);
    }
}


int main(int argc, char const *argv[])
{

    BTree racineB1 , racineB2,p;
    int m , n = 31;
    racineB1=makeB1();
    racineB2=makeB2();
    p=makeSubT();

    printf("affichage arbre b1 : \n");
    afficheArbre(racineB1);
    printf("affichage arbre b2 : \n");
    afficheArbre(racineB2);
    printf("affichage arbre p : \n");
    afficheArbre(p);
    
    if (equalBTrees(racineB1,racineB2))
        printf("les deux arbres sont identique \n");
    else 
        printf("les deux arbres ne sont pas identique ! \n");


    if (isSubBTree(p, racineB1)){
        printf("p est un sous arbre de racine B1 \n");}
    else
        printf("p n'est pas sous arbre de racine B1 \n");
    
    //find element
    if (findElem(racineB1,n))
    {
        printf("%d exist dans l'arbre b1 \n",n);
    }
    else
        printf("%d n'existe pas dans l'arbre \n",n);
    
    //find minimum
    printf("le minimum de l'arbre B1 est : %d \n ",findMin(racineB1));
    printf("le minimum de l'arbre B2 est : %d \n ",findMin(racineB2));
    
      
    printf("elements en parcour par largeur :\n"); 
    printWidthOrder(racineB1);
    for (int i = 0; i <= dernier; i++){
        printf("%d ", queue[i]);}
    return 0;
}
    