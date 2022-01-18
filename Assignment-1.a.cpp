#include <iostream>
using namespace std;

// defination of node
class Node
{
public:
    long long int exponent;
    long long int coefficient;
    Node* next;
    Node* prev;
};

// Function to display the linkedList list 
void printNode(Node *sent, Node*head)
{
    while(head != sent)
    {
        if(head -> coefficient != 0)
        {
            cout << head -> coefficient << " ";
            cout << head -> exponent << " ";
        }
        head = head -> next;
    }
    cout << endl;
}

// Function to add polynomial
Node* addPolynomial(Node* p, Node* q)   
{
    Node* res = new Node();     // resultant node (sentinel) after adding polynomial 1 and 2
    res -> prev = res;
    res -> next = res;
    Node* res1 = res;          // res1 = pointer to iterate in Linked List res
    Node* p1 = p -> next;      // p1 = pointer to iterate in Linked List p
    Node* q1 = q -> next;      // q1 = pointer to iterate in Linked List q
    Node* temp = NULL;         // temp = to store a temporary Node


    while(p != p1 && q != q1)  // Merge two polynomial in ascending order till any one list comes to end
    {    
        
        if(p1 -> exponent > q1 -> exponent)        // q has smallest exponent
        {
         temp = new Node();
         temp -> exponent = q1 -> exponent;
         temp -> coefficient = q1 -> coefficient;
         q1 = q1 -> next;
        }
        else if(p1 -> exponent < q1 -> exponent)   // p has smallest exponent
        {
            temp = new Node();
            temp -> exponent = p1 -> exponent;
            temp -> coefficient = p1 -> coefficient;
            p1 = p1 -> next;
        }
        else                                       // both have same exponents
        {
            temp = new Node();
            temp -> exponent = p1 -> exponent;
            temp -> coefficient = p1 -> coefficient + q1 -> coefficient;
            p1 = p1 -> next;
            q1 = q1 -> next;
        }
        // linking last element to the sentinel node
        temp -> next = res;
        res -> prev = temp;
        // linking last element to the list
        res1 -> next = temp;
        temp -> prev = res1;
        res1 = temp;
    }

    while(p!= p1)           //if  some terms of p polynomial still remains
    {                      
        temp = new Node();
        temp -> exponent = p1 -> exponent;
        temp -> coefficient = p1 -> coefficient;
        p1 = p1 -> next;

        // linking last element to the sentinel node
        temp -> next = res;
        res -> prev = temp;
        // linking last element to the list
        res1 -> next = temp;
        temp -> prev = res1;
        res1 = temp;
    }
    while(q != q1)          //if  some terms of q polynomial still remains             
    {
        temp = new Node();
        temp -> exponent = q1 -> exponent;
        temp -> coefficient = q1 -> coefficient;
        q1 = q1 -> next;

        // linking last element to the sentinel node
        temp -> next = res;
        res -> prev = temp;
        // linking last element to the list
        res1 -> next = temp;
        temp -> prev = res1;
        res1 = temp;
    }
    return res;
}

// creating the node
void inputNode(Node* sent, Node* x)
{
    long long int coeff, exp;
    cin >> coeff >> exp;
    Node*temp = new Node();
    temp -> coefficient = coeff;
    temp -> exponent = exp;
    // linking node to the sentinel node
    temp -> next = sent;
    sent -> prev = temp;
    // linking node to the list
    temp -> prev = x;
    x -> next = temp;

}
int main()
{   
    // taking lengths of polynomial
    int n, m;
    cin >> n >> m;

    // creating sentinel nodes for p and q polynomials
    Node* p = new Node();
    p -> next = p;
    p -> prev = p;
    Node* p1 = p;

    Node* q = new Node();
    q -> next = q;
    q -> prev = q;
    Node* q1 = q;

    // creating doubly linked list
    while(n--)
    {
        inputNode(p, p1);
        p1 = p1 -> next;
    }

    p1 = (p1 -> next) -> next;  // p1 is pointing to first element of polynomial p

    while(m--)
    {
        inputNode(q, q1);
        q1 = q1 -> next;
    }
    
    q1 = (q1 -> next) -> next;  // q1 is pointing to first element of polynomial q

    Node * add = addPolynomial(p, q);
    printNode(add, add -> next);
    return 0;
}