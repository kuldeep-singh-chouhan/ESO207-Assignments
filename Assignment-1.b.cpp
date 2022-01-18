#include<iostream>
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

    while(p!= p1)           // if  some terms of p polynomial still remains
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

    while(q != q1)          // if  some terms of q polynomial still remains             
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

// function for multiplying polynomials
Node* multiplyPolynomial (Node* p, Node* q)
{
    // creating nodes for traversal through p and q
    Node* q1 = q -> next;
    Node* p1 = p -> next;

    Node* temp = NULL;
    Node* res = new Node();   // sentinel node for resultant polynomial
    res->next = res;
    res->prev = res;
    Node* res1 = res;         // node for traversal in resultant polynomial

    while(p != p1)
    {
        // multiply a term of p polynomial with each term of q polynomial
        while(q1 != q)
        {
            // multiply coefficients of the two terms from
            // respective polynomials and add their exponents
            temp = new Node();
            temp -> coefficient = (p1 -> coefficient) * (q1 -> coefficient);
            temp -> exponent = p1 -> exponent + q1 -> exponent;
            // linking the node with the sentinel node
            temp -> next = res;
            res -> prev = temp;
            // linking with the list
            res1 -> next = temp;
            temp -> prev = res1;
            res1 = temp;
          
            q1 = q1 -> next;
        }

        q1 = q1 -> next;    // Now q1 is pointing to first element of List q
        p1 = p1 -> next;
    }

    return res;
}

// using merge sort to create the final polynomial
Node* sortList(Node * head)
{
    Node* head1 = head->next;
    
    if(head1 == head || head1 -> next == head)  return head;       // if list is empty (only sentinel node is present)
    
    // creating nodes for breaking the list
    Node* a = head1;
    Node* b = head1 -> next;

    // for separating the list into two parts
    while (b != head)
    {
        b = b -> next;
        if (b != head)
        {
            a = a -> next;          // here b moves double the
            b = b -> next;          // length that is moved by a
        }
    }

    // creating a sentinel node for the second part
    Node* b1 = new Node();
    b1 -> next = b1;
    b1 -> prev = b1;

    b = a -> next;

    // linking sentinel node to the second part
    b1 -> next = b;
    b -> prev = b1;
    b1 -> prev  = head -> prev;
    (head -> prev) -> next = b1;

    // head is now sentinel node for the first part
    a -> next = head;
    head -> prev = a;

    // breaking these terms recursively and then adding
    // to form the required sorted polynomial
    return addPolynomial(sortList(head) , sortList(b1));
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

    // creating a polynomial of n*m length
    Node* mul = multiplyPolynomial(p, q);   // mul is now the sentinel node for resultant polynomial
    // sorting and collecting coefficients with same exponent
    mul = sortList(mul);

    printNode(mul, mul -> next);

    return 0;
}