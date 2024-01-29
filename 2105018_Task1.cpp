#include <iostream>
#include<fstream>
#include "color.hpp"
using namespace std;

const string R = "Red";
const string B = "Black";

class Node
{

public:
    Node *left;
    Node *right;
    Node *parent;
    string color;
    string key;
    int value;

    Node()
    {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
    Node(string key, int value)
    {
        this->value = value;
        this->key = key;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    Node(int value, Node *left, Node *right)
    {
        this->left = left;
        this->right = right;
        this->value = value;
    }
};

class redBlackTrees
{
    Node *root;
    Node *Tnil;
    void leftRotate(Node *node)
    {
        Node *y = node->right;
        node->right = y->left;
        if (y->left != Tnil)
        {
            y->left->parent = node;
        }
        y->parent = node->parent;

        if (node->parent == nullptr)
        {
            root = y;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = y;
        }
        else
        {
            node->parent->right = y;
        }

        y->left = node;
        node->parent = y;
    }

    void rightRotate(Node *node)
    {
        Node *y = node->left;
        node->left = y->right;
        if (y->right != Tnil)
        {
            y->right->parent = node;
        }
        y->parent = node->parent;

        if (node->parent == nullptr)
        {
            root = y;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = y;
        }
        else
        {
            node->parent->right = y;
        }

        y->right = node;
        node->parent = y;
    }

    void rb_insert_fix(Node *node)
    {
        Node *y;
        while (node->parent != nullptr && node->parent->color == R)
        {
            if (node->parent == node->parent->parent->left)
            {
                y = node->parent->parent->right;
                if (y == Tnil || y->color == B)
                {
                    if (node == node->parent->right)
                    {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = B;
                    node->parent->parent->color = R;
                    rightRotate(node->parent->parent);
                }
                else if (y->color == R)
                {

                    node->parent->color = B;
                    node->parent->parent->color = R;
                    y->color = B;
                    node = node->parent->parent;
                }
            }

            else
            {
                y = node->parent->parent->left;
                if (y == Tnil || y->color == B)
                {
                    if (node == node->parent->left)
                    {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = B;
                    node->parent->parent->color = R;
                    leftRotate(node->parent->parent);
                }

                else if (y->color == R)
                {
                    node->parent->color = B;
                    y->color = B;
                    node->parent->parent->color = R;
                    node = node->parent->parent;
                }
            }
        }

        root->color = B;
    }

    void delete_fix(Node *node)
    {
        while (node!=root && node->color == B)
        {
            Node *w;
            if (node == node->parent->left)
            {
                w = node->parent->right;
                if (w->color == R)
                {
                    w->color = B;
                    node->parent->color = R;
                    leftRotate(node->parent);
                    w = node->parent->right;
                }

                if (w->left->color == B && w->right->color == B)
                {
                    w->color = R;
                    node = node->parent;
                }

                else
                {
                    if (w->right->color == B)
                    {
                        w->left->color = B;
                        w->color = R;
                        rightRotate(w);
                        w = node->parent->right;
                    }
                    w->color = node->parent->color;
                    node->parent->color = B;
                    w->right->color=B;
                    leftRotate(node->parent);
                    node = root;
                }
            }
            else
            {
                w = node->parent->left;
                if (w->color == R)
                {
                    w->color = B;
                    node->parent->color = R;
                    rightRotate(node->parent);
                    w = node->parent->left;
                }

                if (w->right->color == B && w->left->color == B)
                {
                    w->color = R;
                    node = node->parent;
                }
                else
                {
                    if (w->left->color == B)
                    {
                        w->right->color = B;
                        w->color = R;
                        leftRotate(w);
                        w = node->parent->left;
                    }
                    w->color = node->parent->color;
                    node->parent->color = B;
                    w->left->color=B;
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }

        node->color = B;
    }

    void transplant(Node *u, Node *v)
    {
        if (u->parent == Tnil)
        {
            root = v;
        }

        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }

        else
        {
            u->parent->right = v;
        }

        v->parent = u->parent;

        // if (v != nullptr)
        // {
        //     v->parent = u->parent;
        // }
    }

    Node *inorderSuccessor(Node *node)
    {
        Node *temp = node;
        while (temp->left != Tnil)
        {
            temp = temp->left;
        }
        return temp;
    }

    void inorderTraversal(Node* node)
    {
        if(node==Tnil)
        {
            return;
        }

        inorderTraversal(node->left);
        if (node->value != 0)
        {
            if (node->color == R)
            {
                cout<<dye::red(node->value)<<"=>"<< dye::red(node->key);
            }
            else
            {
                cout<<node->value<<"=>"<< node->key;
            }

            cout<<endl;
        }
        inorderTraversal(node->right);
    }

    void preorderTraversal(Node *&node)
    {
        if (node == Tnil)
        {
            return;
        }
        if (node->value != 0)
        {
            if (node->color == R)
            {
                cout<<dye::red(node->value)<<dye::red("_")<< dye::red(node->key);
            }
            else
            {
                cout<<node->value<<"_"<<node->key;
            }
            if(node->left!=Tnil || node->right!=Tnil) cout<<"(";
        }

        preorderTraversal(node->left);
        if(node->left!=Tnil || node->right!=Tnil && node->value!=0)cout<<",";
        preorderTraversal(node->right);
        if(node->left!=Tnil || node->right!=Tnil && node->value!=0)cout<<")";
    }

     void deleteAll(Node* node)
    {
        if(node==Tnil)
        {
            return;
        }

        deleteAll(node->left);
        deleteAll(node->right);
        delete node;
    }

    int sizeOfRb(Node* node,int &size)
    {
        if(node==Tnil)
        {
            return size;
        }

        sizeOfRb(node->left,size);
        size++;
        sizeOfRb(node->right,size);
    }

public:
    redBlackTrees()
    {
        Tnil = new Node;
        Tnil->color = B;
        Tnil->left = nullptr;
        Tnil->right = nullptr;
        root = Tnil;
    }

    void rb_insert(int value, string key)
    {
        if (root == Tnil)
        {
            Node *node = new Node(key, value);
            root = node;
            root->color = B;
            root->left = Tnil;
            root->right = Tnil;
            return;
        }
        Node *node = new Node(key, value);
        Node *x = root;
        Node *y = Tnil;
        while (x != Tnil)
        {
            y = x;
            if (node->value < x->value)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        node->parent = y;

        if (node->value < y->value)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }
        node->left = Tnil;
        node->right = Tnil;
        node->color = R;
        rb_insert_fix(node);
    }

    void deleteNode(Node* z)
    {

        if (z != Tnil)
        {
            Node *y = z;
            Node *x;
            string originColor = y->color;
            if (z->left == Tnil)
            {
                x = z->right;
                transplant(z, z->right);
            }

            else if (z->right == Tnil)
            {
                x = z->left;
                transplant(z, z->left);
            }

            else
            {
                y = inorderSuccessor(z->right);
                originColor = y->color;
                x = y->right;
                if (y->parent == z)
                {

                    x->parent = y;
                }

                else
                {
                    transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }

                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;

                y->color = z->color;
            }

            delete z;
            if (originColor == B)
            {
                delete_fix(x);
            }
        }
    }

    Node *find(int value)
    {
        Node *temp = root;
        while (temp != Tnil)
        {
            if (value < temp->value)
            {
                temp = temp->left;
            }

            else if (value > temp->value)
            {
                temp = temp->right;
            }

            else if (value == temp->value)
            {
                return temp;
                break;
            }
        }

        return nullptr;
    }

   void clear()
   {
      deleteAll(root);
      root=Tnil;
   }

    void printNode()
    {
        preorderTraversal(root);
        cout<<endl;
    }

    boolean isEmpty()
    {
        return root==Tnil;
    }

    int size()
    {
        int size;
        sizeOfRb(root,size);
        return size;
    }

    void iteration()
    {
        inorderTraversal(root);
    }
};

class mapM
{
    redBlackTrees R;

public:
    boolean deleteNode(int value)
    {
        Node* node=R.find(value);
        if (node== nullptr)
        {
            return false;
        }

        R.deleteNode(node);
        return true;
    } 
    void insert(int value,string key)
    {
        R.rb_insert(value,key);
    }

    int size()
    {
        return R.size();
    }

    boolean Empty()
    {
        return R.isEmpty();
    }

    void iteration()
    {
        R.iteration();
    }

    boolean find(int value)
    {
        return R.find(value)!=nullptr;
    }

    boolean clear()
    {
        if(R.isEmpty())
        {
            return false;
        }

        R.clear();
        return true;
    }


    void display()
    {
        R.printNode();
    }


};

int main()
{
    mapM m;
    freopen("input.txt","r",stdin);
    freopen("outputTest.txt","w",stdout);
    int count=0;
    while(!feof(stdin))
    {
        count++;
        string str;
        cin>>str;
        if(str=="I")
        {
            int value;
            string  key;
            cin>>value>>key;
            m.insert(value,key);
            m.display();
        }

        else if(str=="F")
        {
            int value;
            cin>>value;
            if(m.find(value))
            {
                cout<<value<<" found"<<endl;
            }
            else
            {
                cout<<value<<" not found"<<endl;
            }
        }

        else if(str=="E")
        {
            int value;
            cin>>value;
            if(m.deleteNode(value))
            {
                m.display();
            }
            else
            {
                cout<<value<<" not found"<<endl;
            }
        }

        else if(str=="Em")
        {
            if(m.Empty())
            {
                cout<<"yes"<<endl;
            }

            else
            {
                cout<<"no"<<endl;
            }
        }

        else if(str=="Clr")
        {
            if(m.clear())
            {
                cout<<"successful"<<endl;
            }
            else
            {
                cout<<"unsuccessful"<<endl;
            }
        }

        else if(str=="Itr")
        {
            m.iteration();
        }

        else if(str=="S")
        {
            cout<<m.size()<<endl;
        }
    }
}