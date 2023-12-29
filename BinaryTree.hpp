#ifndef BINARY_TREE
#define BINARY_TREE
#include <iostream>
class BinaryTree{
    class Node{
        public:
        int value;
        Node *left;
        Node *right;
    };
    public:
        Node *root=nullptr;
        int height=0;
        int sizeOfTree=0;
    void insert(int x)
    {
        if(root==nullptr)
        {
            root=new Node();
            root->value=x;
            sizeOfTree++;
            height=1;
        }
        else
        {
            Node *temp = root;
            int level=1;
            while(true)
            {
                level++;
                if(x >= temp->value)
                {
                    if(temp->right==nullptr)
                    {
                    temp->right=new Node();
                    temp->right->value=x;
                    sizeOfTree++;
                    if(level>height)height=level;
                    break;
                    }
                    temp=temp->right;
                }
                else
                {
                    if(temp->left==nullptr)
                    {
                    temp->left=new Node();
                    temp->left->value=x;
                    sizeOfTree++;
                    if(level>height)height=level;
                    break;
                    }
                    temp=temp->left;
                }
            }
        }
    }
    Node* search(int x)
    {
        Node *temp = root;
        while(temp!=nullptr)
        {
            if(x==temp->value) return temp;
            else
            {
                if(x > temp->value) temp=temp->right;
                else temp=temp->left;
            }
        }
        return nullptr;
    }
    Node* searchRecursive(Node* node, int x)
    {
        if(node == nullptr) return nullptr;
        if(node->value==x) return node;
        else
        {
            if(x>node->value) return searchRecursive(node->right,x);
            else return searchRecursive(node->right,x);
        }
    }
    int size(){return sizeOfTree;}
    int minimum()
    {
        Node *temp=root;
        while(temp->left!=nullptr)
        {
            temp=temp->left;
            height--;
        }
        return temp->value;
    }
    int maximum()
    {
        Node *temp=root;
        while(temp->right!=nullptr)
        {
            temp=temp->right;
        }
        return temp->value;
    }
    int depth() {return height;}

    ~BinaryTree()
    {
        destructor(root);
    }
    void destructor(Node *node)
    {
        if(node!=nullptr)
        {
            destructor(node->left);
            destructor(node->right);
            delete node;
        }
    }
        void inorder()
    {
        innerInorder(root);
    }
        void preorder()
    {
        innerPreorder(root);
    }
        void postorder()
    {
        innerPostorder(root);
    }
    private:
        void innerInorder(Node *node)
        {
            if(node!=nullptr)
            {
                innerInorder(node->left);
                std::cout<<node->value<<std::endl;
                innerInorder(node->right);
            }
        }
        void innerPreorder(Node *node)
        {
            if(node!=nullptr)
            {
                std::cout<<node->value<<std::endl;
                innerPreorder(node->left);
                innerPreorder(node->right);
            }
        }
        void innerPostorder(Node *node)
        {
            if(node!=nullptr)
            {
                innerPostorder(node->left);
                innerPostorder(node->right);
                std::cout<<node->value<<std::endl;
            }
        }
};
#endif
