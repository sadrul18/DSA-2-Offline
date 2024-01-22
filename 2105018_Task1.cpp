#include<iostream>
#include "color.hpp"
using namespace std;

const string R="Red";
const string B="Black";

class Node
{

    public:
    Node* left;
    Node* right;
    Node* parent;
    string color;
    string key;
    int value;

    Node()
    {
        left=NULL;
        right=NULL;
        parent=NULL;
    }
    Node(string key,int value)
    {
        this->value=value;
        this->key=key;
        left=NULL;
        right=NULL;
        parent=NULL;
    }

    Node(int value, Node* left, Node* right)
    {
        this->left=left;
        this->right=right;
        this->value=value;
    }
};

class redBlackTrees
{
    Node* root;
    void leftRotate(Node* node)
    {
        Node* y=node->right;
        node->right=y->left;
        if(y->left!=NULL)
        {
            y->left->parent=node;
        }
        y->parent=node->parent;

        if(node->parent==NULL)
        {
            root=y;
        }
        else if(node==node->parent->left)
        {
            node->parent->left=y;
        }
        else
        {
            node->parent->right=y;
        }

        y->left=node;
        node->parent=y;
    }

    void rightRotate(Node* node)
    {
        Node* y=node->left;
        node->left=y->right;
        if(y->right!=NULL)
        {
            y->right->parent=node;
        }
        y->parent=node->parent;

        if(node->parent==NULL)
        {
            root=y;
        }
        else if(node==node->parent->left)
        {
            node->parent->left=y;
        }
        else
        {
            node->parent->right=y;
        }

        y->right=node;
        node->parent=y;
    }

    void rb_insert_fix(Node*  node)
    {
        Node* y;
       while(node->parent!=NULL && node->parent->color==R)
       {
          if(node->parent==node->parent->parent->left)
          {
            y=node->parent->parent->right;
            if(y==NULL || y->color==B)
            {
                if(node==node->parent->right)
                {
                    node=node->parent;
                    leftRotate(node);
                }
                node->parent->color=B;
                node->parent->parent->color=R;
                rightRotate(node->parent->parent);
            }
            else if(y->color==R)
            {
                
                node->parent->color=B;
                node->parent->parent->color=R;
                y->color=B;
                node=node->parent->parent;
            }
          }

          else
          {
            y=node->parent->parent->left;
            if(y==NULL || y->color==B)
            {
                if(node==node->parent->left)
                {
                    node=node->parent;
                    rightRotate(node);
                }
                node->parent->color=B;
                node->parent->parent->color=R;
                leftRotate(node->parent->parent);
            }

            else if(y->color==R)
            {
                node->parent->color=B;
                y->color=B;
                node->parent->parent->color=R;
                node=node->parent->parent;
            }
          }
       } 

       root->color=B;
    }

    void delete_fix(Node* node)
    {

    }

    void preorderTraversal(Node* &node)
    {
        if(node==NULL)
        {
            return;
        }
        cout<<"("<<node->value<<" ";
        if(node->color==R)
        {
            cout<<dye::red(node->key)<<")"<<" ";
        }
        else
        {
            cout<<node->key<<")"<<" ";
        }
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
    public:
    redBlackTrees()
    {
        root=NULL;
    }

    void rb_insert(int value,string key)
    {
        if(root==NULL)
        {
            Node* node=new Node(key,value);
            root=node;
            root->color=B;
            return;
        }
        Node* node=new Node(key,value);
        Node* x=root;
        Node* y;
        while(x!=NULL)
        {
            y=x;
            if(node->value<x->value)
            {
                x=x->left;
            }
            else
            {
                x=x->right;
            }
        }

        node->parent=y;

        if(node->value<y->value)
        {
            y->left=node;
        }
        else
        {
            y->right=node;
        }
        node->color=R;
        rb_insert_fix(node);
    }

    void printNode()
    {
        preorderTraversal(root);
    }

    // void check(int flag)
    // {
    //     if(flag)
    //     {
    //         leftRotate(root);
    //     }
    //     else
    //     {
    //         rightRotate(root);
    //     }
    // }
};

int main()
{
    redBlackTrees rb;
     rb.rb_insert(10 ,"Thors");
    rb.rb_insert(34, "Canute");
    rb.rb_insert(43,"Olaf");
    rb.rb_insert(15,"Einer");
    rb.rb_insert(40,"Olmar");
    rb.rb_insert(53,"Floki");
    rb.printNode();

    // rb.check(1);
    // cout<<"After left-rotation: "<<endl;
    // rb.printNode();
}