#include <iostream>
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
            cout<<node->value<<"=>";
            if (node->color == R)
            {
                cout << dye::red(node->key);
            }
            else
            {
                cout << node->key;
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
            cout << "(" << node->value << " ";
            if (node->color == R)
            {
                cout << dye::red(node->key) << ")"
                     << " ";
            }
            else
            {
                cout << node->key << ")"
                     << " ";
            }
        }
        preorderTraversal(node->left);
        preorderTraversal(node->right);
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

    void deleteNode(int value)
    {
        Node *z = find(value);
        //cout<<endl;
        if (z != Tnil)
        {
            Node *y = z;
            Node *x;
            string originColor = y->color;
            if (z->left == Tnil)
            {
                x = z->right;
                cout << z->right->value << endl;
                transplant(z, z->right);
            }

            else if (z->right == Tnil)
            {
                x = z->left;
                cout << x->value << endl;
                transplant(z, z->left);
            }

            else
            {
                y = inorderSuccessor(z->right);
                originColor = y->color;
                x = y->right;
                cout << y->value << endl;
                cout << x->value << endl;
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
                break;
            }
        }

        return temp;
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

    }

    void iteration()
    {
        inorderTraversal(root);
    }
};

class map
{
    redBlackTrees R;

public:
    void deleteNode(int value)
    {
        if (R.find(value) != nullptr)
        {
            R.deleteNode(value);
        }
        else
        {
            cout << value << " Not found" << endl;
        }
    }
};

int main()
{
    redBlackTrees rb;
    rb.rb_insert(10, "Thors");
    rb.rb_insert(34, "Canute");
    rb.rb_insert(43, "Olaf");
    rb.rb_insert(15, "Einer");
    rb.rb_insert(40, "Olmar");
    rb.rb_insert(53, "Floki");
    rb.rb_insert(90, "Thorfinn");
    rb.rb_insert(12, "Snake");
    rb.rb_insert(78, "Askeladd");
    rb.printNode();
    rb.deleteNode(40);
    rb.printNode();
    rb.iteration();
}