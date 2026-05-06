#include<iostream>
#include<string>
using namespace std;

class Node{
    public:
        string word;
        string meaning;
        Node* RC;
        Node* LC;

        Node(string w, string m)
        {
            word = w;
            meaning = m;
            LC = RC = NULL;
        }
};

Node* insert( Node* root, string word, string meaning){
    if(root==NULL){
        return new Node(word, meaning);
    }
    if (word == root->word)
    {
        cout << "\nDuplicate node!!";
        return root;
    }
    if(word < root->word){
        root->LC = insert(root->LC, word,meaning);
    }
    else{
        root->RC = insert(root->RC, word,meaning);
    }
    return root;
}

void search(Node* root, string key,int count){
    if(root==NULL){
        cout << "key is not found\n";
        return;
    }
    count++;
    if (key == root->word)
    {
        cout << "Key is Found: "<<root->word<<":"<<root->meaning<<endl;
        cout << "Total comparisons to Search Element:" << count;
        return;
    }
    else if(key<root->word){
        search(root->LC, key,count);
        
    }
    else{
        search(root->RC, key,count);  
    }
}

void update(Node *root, string key, string New)
{
    if(root==NULL){
        cout << "word not exist";
        return;
    }
    if (key==root->word){
        root->meaning = New;
        cout << "updated:"<< root->word << endl;
    }
    else if(key<root->word){
        update(root->LC, key, New);
    }
    else
        update(root->RC, key, New);
}

Node* Inordersuccesor(Node* root){
    Node *temp = root->RC;
    while(temp && temp->LC!=NULL){
        temp = temp->LC;
    }
    return temp;
}

Node *deleteW(Node *root, string key)
{
    if (root==NULL){
        cout << "Tree Empty\n";
        return NULL;
    }

    if(key<root->word){
        root->LC = deleteW(root->LC, key);
    }
    else if(key>root->word){
        root->RC = deleteW(root->RC, key);
    }

     else{

        if (root->LC == NULL && root->RC == NULL){
            delete root;
            return NULL;
        }
        else if((root->LC!=NULL && root->RC == NULL)){
            Node* temp=root -> LC;
            delete root;
            return temp;
            }
        else if((root->LC==NULL && root->RC!=NULL)){
            Node* temp=root->RC;
            delete root;
            return temp;
        }
        else{
            root->word = Inordersuccesor(root)->word;
            root->meaning = Inordersuccesor(root)->meaning;
            root->RC = deleteW(root->RC, Inordersuccesor(root)->word);
        }
    }
    return root;
}

void displayAsc(Node *root)
{
    if (root == NULL) {
        return;
    }

    displayAsc(root->LC);
    cout << root->word << ":" << root->meaning<<endl;
    displayAsc(root->RC);
}

void displayDsc(Node *root)
{
    if (root == NULL){
        return;
    }

    displayDsc(root->RC);
    cout << root->word << ":" << root->meaning<<endl;
    displayDsc(root->LC);
}

int main()
{
    Node *root = NULL;
    int choice;
    string key;
    string New;
    string word, meaning;

    do
    {
        cout << "\n Dictionary Menu \n";
        cout << "1. Insert\n2. Search\n3. Update\n4. Delete\n5. Display\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {

        case 1:
            cout << "Enter word: ";
            cin >> word;

            cout << "Enter meaning: ";
            cin >> meaning;
            root = insert(root, word, meaning);
            break;

        case 2:
            cout << "enter the key You want to search:";
            cin >> key;
            search(root, key, 0);
            break;

        case 3:
            cout << "enter the meaning of new word:";
            cin >> New;
            cout << "Enter the String you want to update:";
            cin >> key;
            update(root, key, New);
            break;
        
        case 4:
            cout << "Enter the word you want to delete:";
            cin >> key;
            root=   deleteW(root, key);
            cout << "Deletion Successfull";
            break;

        case 5:
            cout << "\nDictionary:\n";
            int choice;

                cout << "1. Ascending order\n2. Descending Order\n";
                cout << "Enter Choice";
                cin >> choice;
    
             if(choice==1){
                    displayAsc(root);
             }

             else if(choice==2){
                displayDsc(root);
             }

            else{
                cout << "Invalid Choice";
            }
        break;

        case 6:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice\n";
            break;
        }

    } while (choice != 6);

    return 0;
}