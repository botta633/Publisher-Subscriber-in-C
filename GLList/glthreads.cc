#include "glthreads.h"

Node *Node::getLeft() { return this->left; }

Node *Node::getRight() { return this->right; }

void Node::setLeft(Node *left) { this->left = left; }

void Node::setRight(Node *right) { this->right = right; }

void Node::init()
{
    this->left = nullptr;
    this->right = nullptr;
}

void Node::addNext(Node *currNode, Node *newNode)
{
    if (!currNode->right)
    {
        currNode->right = newNode;
        newNode->left = currNode;
        return;
    }

    Node *temp = currNode->right;
    currNode->right = newNode;
    newNode->left = currNode;
    newNode->right = temp;
    temp->left = newNode;

    return;
}

void glthread::addNode(Node *node)
{

    node->setLeft(nullptr);
    node->setRight(nullptr);

    if (!this->head)
    {
        this->head = node;
        return;
    }

    Node *head = this->head;
    Node::addNext(node, head);
    this->head = node;
}

void Node::removeNode(Node *node)
{
    if (!node->left)
    {
        if (node->right)
        {
            node->right->left = nullptr;
            node->right = nullptr;
            return;
        }

        return;
    }

    if (!node->right)
    {
        node->left->right = nullptr;
        node->left = nullptr;
        return;
    }

    node->left->right = node->right;
    node->right->left = node->left;
    node->left = nullptr;
    node->right = nullptr;
    delete node;
}

void glthread::removeNode(Node *node)
{
    Node *head = this->head;

    if (head == node)
    {
        Node *temp = head->getRight();
        delete head;
        this->head = temp;
    }

    Node::removeNode(node);
}

void glthread::initThread(unsigned int offset)
{
    this->head = nullptr;
    this->offset = offset;
}

