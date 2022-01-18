#include<bits/stdc++.h>
using namespace std;

class twoThreeNode{
    public:
        int firstData;
        int secondData;
        twoThreeNode* firstChild;
        twoThreeNode* secondChild;
        twoThreeNode* thirdChild;
        int flag;
};
class returnTuple{
    public:
        twoThreeNode* n1;
        twoThreeNode* n2;
        int m;
};
int minData(twoThreeNode* T) {
    twoThreeNode* temp = T;
    while(temp->flag != 1){
        temp = temp-> firstChild;
    }
    return temp->firstData;
}

int height(twoThreeNode* T) {
    int h = 0;
    twoThreeNode* temp = T;
    while(temp->flag != 1){
        temp = temp-> firstChild;
        h++;
    }
    return h;
}

void Extract(twoThreeNode* T) {
    if(T == NULL) return;
    if(T->flag == 1) {   // if T is a leaf node
        cout << T->firstData << " ";
    }
    else if(T->flag == 2) {  // if T has two children
        Extract(T->firstChild);
        Extract(T->secondChild);
    }
    else if(T->flag == 3) {  // if T has three children
        Extract(T->firstChild);
        Extract(T->secondChild);
        Extract(T->thirdChild);
    }
    return ;
}
twoThreeNode* MakeSingleton(int x){
    twoThreeNode* leaf = new twoThreeNode();
    leaf->firstData = x;
    leaf->secondData = 0;
    leaf->firstChild = NULL;
    leaf->secondChild = NULL;
    leaf->thirdChild = NULL;
    leaf->flag =1;

    return leaf;
}
twoThreeNode* MakeTwoChildNode(twoThreeNode* fChild, twoThreeNode* sChild, int fData) {
    twoThreeNode* T = new twoThreeNode();
    T->firstData = fData;
    T->secondData = 0;
    T->firstChild = fChild;
    T->secondChild = sChild;
    T->thirdChild = NULL;
    T->flag = 2;
    return T; 
}
twoThreeNode* MakeThreeChildNode(twoThreeNode* fChild, twoThreeNode* sChild, twoThreeNode* tChild, int fData, int sData) {
    twoThreeNode* T = new twoThreeNode();
    T->firstData = fData;
    T->secondData = sData;
    T->firstChild = fChild;
    T->secondChild = sChild;
    T->thirdChild = tChild;
    T->flag = 3;
    return T; 
}
returnTuple* insert(int h1, int h2, twoThreeNode* T1, twoThreeNode* T2, int minValue){  // T1 and T2 are passed such that h1 > h2
    if(h1 > h2) {
        returnTuple* rT = new returnTuple();
        if(h1 = h2+1) {
            if(T1->flag == 2) {
                rT->n1 = MakeThreeChildNode(T1->firstChild, T1->secondChild, T2, T1->firstData, minValue);
                rT->n2 = NULL;
                rT->m = 0;
                return rT;
            }
            else {
                rT->n1 = MakeTwoChildNode(T1->firstChild, T1-> secondChild, T1->firstData);
                rT->n2 = MakeTwoChildNode(T1->thirdChild, T2, minValue);
                rT->m = minValue; // check minValue
                return rT;
            }
        }
        else if(T1->flag == 2) {
            rT = insert(h1-1, h2, T1->secondChild,T2,minValue);
            if(rT->n2 ==NULL) {
                T1->secondChild = rT->n1;
                rT->n1 = T1;
                rT->n2 = NULL;
                rT->m = 0;
                return rT;
            }
            else{
                T1->secondChild = rT->n1;
                T1->thirdChild = rT->n2;
                T1->secondData = rT->m;
                rT-> n1 = T1;
                rT-> n2 = NULL;
                rT->m = 0;
                return rT;
            }
        }
        else{
            rT = insert(h1-1, h2, T1->secondChild,T2,minValue);
            if(rT->n2 == NULL) {
                T1->thirdChild = rT->n1;
                rT->n1 = T1;
                rT->n2 = NULL;
                rT->m = 0;
                return rT;
            }
            else {
                returnTuple* temp = new returnTuple();
                temp->n2 = MakeTwoChildNode(rT->n1, rT->n2,rT->m);
                temp->n1 = MakeTwoChildNode(T1->firstChild, T1->secondChild, T1->firstData);

                temp->m = T1->secondData;
                return temp;
            }
        }
    }

}

twoThreeNode* Merge(twoThreeNode* T1, twoThreeNode* T2) { // assume T1 values are smaller than T2 values
    if(T1 == NULL) return T2;
    if(T2 == NULL) return T1;
    int h1 = height(T1);
    int h2 = height(T2);
    twoThreeNode* temp1 = T1;
    twoThreeNode* temp2 = T2;
    if(h1 == h2) {
        return MakeTwoChildNode(T1, T2, minData(T2)) ;
    }
    else if(h1 > h2){
        returnTuple* tup = new returnTuple();
        tup = insert(h1, h2, T1, T2, minData(T2));
        if(tup->n2 == NULL) return tup->n1;
        else{
            return MakeTwoChildNode(tup->n1, tup->n2 , tup->m);
        }
    }
    else{ // if h2 > h1 trees are passed to insert func such that bigger tree is T1 in insert function
        returnTuple* tup = new returnTuple();
        tup = insert(h2, h1, T2, T1, minData(T1));
        if(tup->n2 == NULL) return tup->n1;
        else{
            return MakeTwoChildNode(tup->n1, tup->n2 , tup->m);
        }
    }
    return NULL;


}
void Test(){
    twoThreeNode* T1 = MakeSingleton(1);
    for(int i = 2; i <= 500; i++) {
        T1 = Merge(T1, MakeSingleton(i)) ;
    }
    twoThreeNode* T2 = MakeSingleton(777);
    for(int i = 778; i <= 1000; i++) {
        T2 = Merge(T2, MakeSingleton(i)) ;
    }

    twoThreeNode* resultant = Merge(T1, T2);
    Extract(resultant);

}

int main() {
    Test();
    return 0;
}