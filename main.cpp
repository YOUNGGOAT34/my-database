#include "BPlusTree.h"
#include<iostream>
#include <string>
#include<vector>

int main() {
    
     // Initialize a B+ Tree with a degree of 3
     Tree tree(4);

     // Insert some keys and values
     tree.insert(1);
     tree.insert(4);
     tree.insert(7);
     tree.insert(10);
     tree.insert(17);
     tree.insert(21);
     tree.insert(31);
     tree.insert(25);
     tree.insert(19);
     tree.insert(20);
     tree.insert(28);
     tree.insert(42);

     tree.printTree();
    //  std::cout<<*(tree.root)<<std::endl;

     std::cout<<tree.search(10)<<std::endl;
     std::cout<<tree.search(17)<<std::endl;
     std::cout<<tree.search(21)<<std::endl;
     std::cout<<tree.search(31)<<std::endl;
     std::cout<<tree.search(25)<<std::endl;
     std::cout<<tree.search(19)<<std::endl;
     std::cout<<tree.search(20)<<std::endl;
     std::cout<<tree.search(28)<<std::endl;
     std::cout<<tree.search(42)<<std::endl;
     std::cout<<tree.search(0)<<std::endl;

    

     
 
     
                              
    return 0;
}








// void Tree::split(Node *node) {
//     int splitIndex = node->keys.size() / 2;
//     int keyToPromote = node->keys[splitIndex];

//     Node *rightNode = new Node(node->isLeaf);
//     rightNode->keys.assign(node->keys.begin() + splitIndex + (node->isLeaf ? 0 : 1), node->keys.end());
//     node->keys.resize(splitIndex);

//     // If it's an internal node, move children as well
//     if (!node->isLeaf) {
//         rightNode->children.assign(
//             node->children.begin() + splitIndex + 1,
//             node->children.end()
//         );
//         node->children.resize(splitIndex + 1);
        
//         // Update parent pointers for moved children
//         for (Node *child : rightNode->children) {
//             child->parent = rightNode;
//         }
//     }

//     // If node has a parent, insert the promoted key and rightNode
//     if (node->parent) {
//         Node *parent = node->parent;
//         auto it = std::lower_bound(parent->keys.begin(), parent->keys.end(), keyToPromote);
//         parent->keys.insert(it, keyToPromote);
        
//         // Find where to insert rightNode in children
//         auto childIt = parent->children.begin();
//         for (; childIt != parent->children.end(); ++childIt) {
//             if (*childIt == node) {
//                 break;
//             }
//         }
//         parent->children.insert(childIt + 1, rightNode);
//         rightNode->parent = parent;

//         // Check if parent needs splitting
//         if (parent->keys.size() >= M) {
//             split(parent);
//         }
//     } else {
//         // Create a new root
//         Node *newRoot = new Node(false);
//         newRoot->keys.push_back(keyToPromote);
//         newRoot->children.push_back(node);
//         newRoot->children.push_back(rightNode);
        
//         node->parent = newRoot;
//         rightNode->parent = newRoot;
        
//         root = newRoot;
//     }

//     // For leaf nodes, update the linked list
//     if (node->isLeaf) {
//         rightNode->next = node->next;
//         node->next = rightNode;
//     }
// }



// Tree::Node *Tree::findLeaf(Node *node, int &key) {
//     if (!node) return nullptr;
//     if (node->isLeaf) return node;

//     auto it = std::lower_bound(node->keys.begin(), node->keys.end(), key);
//     size_t index = it - node->keys.begin();
//     if (index >= node->children.size()) index = node->children.size() - 1;
//     return findLeaf(node->children[index], key);
// }




// void Tree::insert(int key) {
//     if (!root) {
//         Node *node = new Node(true);
//         node->keys.push_back(key);
//         root = node;
//         return;
//     }

//     Node *leaf = findLeaf(root, key);
//     auto it = std::lower_bound(leaf->keys.begin(), leaf->keys.end(), key);
//     leaf->keys.insert(it, key);

//     if (leaf->keys.size() >= M) {
//         split(leaf);
//     }
// }