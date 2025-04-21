#ifndef BPulsTREE_H
#define BPlusTREE_H

#include <vector>
#include <iostream>
class Tree{
public:
struct Node{
  std::vector<int> keys;
  std::vector<Node *> children;
  Node *parent;
  Node *next;//for leaf nodes
  bool isLeaf; 
  public:

  Node(bool leaf=false) : isLeaf(leaf), parent(nullptr), next(nullptr) {}
};


Node *root;
int M;

~Tree();


Tree(int M=3):M(M){}
void split(Node *node);
void printTree();

void insert(int key) ;
Node* findLeaf(Node *root,int &key);
int search(int key);
};

#include "BPlusTree.cpp" 

#endif 