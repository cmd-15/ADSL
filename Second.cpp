#include<iostream>
#include<string>

using namespace std;
#define MAX 30
class Node{
    public:
    Node* LC;
    Node *RC;
    char data;
    
    Node(char exp ){
        data = exp;
        LC = RC = NULL;
    }
};

class Stack{
    
    Node *stack[MAX];
    int top;

public:
    Stack(){
        top = -1;
    }

    bool IsEmpty(){
        return(top == -1);
    }

    bool IsFull(){
        return (top == MAX - 1);
    }

    void push(Node* exp){
        if(!IsFull()){
            stack[++top] = exp;
        }
        else{
            cout << "\nStack Overflow!!" << endl;
        }
    }

    Node* pop(){
        if(!IsEmpty()){
            return stack[top--];
        }
        else{
            cout << "\nStack Underflow!!";
            return NULL;
        }
    }
};

class Expressiontree{
    string exp;
    Node *root;

public:
    Expressiontree()
    {
        root = NULL;
    }

    void Getexp(){
        cout << "\nEnter the expression: ";
        cin >> exp;
    }

    void Printexp(){
        cout << "\nThe Expression is: " << exp << endl;
    }

    bool Operand( char value){
        return ((value >= 'a' && value <= 'z') || (value >= 'A' && value <= 'Z'));
    }

    bool Operator(char value){
        return (value == '+' || value == '-' || value == '*' || value == '/' || value == '^');
    }

void BuildTree(){
    root = NULL;

    Stack S;
    Node* p;

    for (int i = exp.length() - 1; i >= 0; i--)
    {
        p = new Node(exp[i]);
        p->LC = NULL;
        p->RC = NULL;
        if(Operand(exp[i])){
            S.push(p);
        }
        else if (Operator(exp[i]))
        {

            Node *left = S.pop();
            Node *right = S.pop();

            if (left == NULL || right == NULL)
            {
                cout << "\nInvalid Prefix Expression";
                return ;
            }

            p->LC = left;
            p->RC = right;

            S.push(p);
        }
    }
    root = S.pop();
}

 void Inorder(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        else{
        Inorder(root->LC);
        cout << root->data<<" ";
        Inorder(root->RC);
    }
 }

 void Nonrecur(){
    if (root == NULL) {
        return;
    }
    Stack s1, s2;
    s1.push(root);

    while(!s1.IsEmpty()){
        Node *temp = s1.pop();
        s2.push(temp);

        if(temp->LC){
            s1.push(temp->LC);
        }

        if(temp->RC){
            s1.push(temp->RC);
        }
    }
    while(!s2.IsEmpty()){
        cout << s2.pop()->data << " ";
    }
}

Node*getroot(){
    return root;
}

};

int main(){
    Expressiontree E;
    int choice=0;
 while(choice!=6){
    cout << "1.Enter the expression";
    cout << "\n2.Print the Expression";
    cout << "\n3.Build Tree";
    cout << "\n4.Print Inorder";
    cout << "\n5.Non recursive Postorder";
    cout << "\n6.Exit";

    cout << "\nEnter the choice: ";
    cin >> choice;

    switch(choice){

        case 1:
            E.Getexp();
            break;

        case 2:
            E.Printexp();
            break;
        
        case 3:
            E.BuildTree();
            break;

        case 4:
            E.Inorder(E.getroot());
            break;

        case 5:
            E.Nonrecur();
            break;

        case 6:
            cout << "Exiting";
            break;

        default:
            cout << "wrong choice";
    }
 }
return 0;
}
