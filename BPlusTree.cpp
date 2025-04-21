#include <algorithm>
#include <stack>
#include<queue>

// template <typename Key, typename Value>
Tree::~Tree() {

   
   if (!root) return;
   std::stack<Node *> stack;

   stack.push(root);
   
   while(!stack.empty()){
      Node *current=stack.top();
      stack.pop();

      if (!current->isLeaf){
         for (auto child:current->children){
            stack.push(child);
         }
      }
      delete current;
   }
    
    
}



// //print the tree

// template <typename Key, typename Value>
void Tree::printTree(){
    if (!root) {
        std::cout << "Tree is empty!" << std::endl;
        return;
    }

    std::queue<Node*> nodeQueue;  // Queue for level-order traversal
    nodeQueue.push(root);

    while (!nodeQueue.empty()) {
        size_t levelSize = nodeQueue.size();  // Number of nodes at the current level

        for (size_t i = 0; i < levelSize; ++i) {
            Node* currentNode = nodeQueue.front();
            nodeQueue.pop();

            // Print the keys in the current node
            std::cout << "[ ";
            for (const auto& key : currentNode->keys) {
                std::cout << key << " ";
            }
            std::cout << "] ";

            // Add children to the queue (if not a leaf)
            if (!currentNode->isLeaf) {
                for (Node* child : currentNode->children) {
                    nodeQueue.push(child);
                }
            }
        }

        std::cout << std::endl;  // Move to the next level
    }
}






void Tree:: insert(int key){
    if(!root){
        Node *node=new Node(true);
        node->keys.push_back(key);
        root=node;
        return;
    }


    

    Node *leaf=findLeaf(root,key);
    auto it=std::lower_bound(leaf->keys.begin(),leaf->keys.end(),key);
    // auto index=it-leaf->keys.begin();
    leaf->keys.insert(it,key);

    //Does this leaf need splitting??
    if(leaf->keys.size()>=M){
        split(leaf);
    }
}

void Tree::split(Node *node){
    int splitIndex=node->keys.size()/2;
    auto keyToPromote=node->keys[splitIndex];

    //split the node
    Node *rightNode=new Node(node->isLeaf);
    
    rightNode->keys.assign(node->keys.begin()+splitIndex,node->keys.end());
    //if it is an internal node move the children as well
   // For leaves: include the split key in the right node
   if (node->isLeaf) {
    rightNode->keys.assign(node->keys.begin() + splitIndex, node->keys.end());
    node->keys.resize(splitIndex);
    }
   
    else {
        rightNode->keys.assign(node->keys.begin() + splitIndex + 1, node->keys.end());
        node->keys.resize(splitIndex);
    }
    
     // Handle children (only for internal nodes)
     if (!node->isLeaf) {
        rightNode->children.assign(node->children.begin() + splitIndex + 1,node->children.end());
        node->children.resize(splitIndex + 1);  

        // Update parent pointers for moved children
        for (Node *child : rightNode->children) {
            child->parent = rightNode;
        }
    }


    // Handle parent insertion
    if (node->parent) {
        Node *parent = node->parent;
        auto it = std::lower_bound(parent->keys.begin(), parent->keys.end(), keyToPromote);
        parent->keys.insert(it, keyToPromote);

        // Find where to insert `rightNode` in parent's children
        auto childIt = std::find(parent->children.begin(), parent->children.end(), node);
        parent->children.insert(childIt + 1, rightNode);
        rightNode->parent = parent;

        // Split parent if it overflows
        if (parent->keys.size() >= M) {
            split(parent);
        }
    }
    // If no parent, create a new root
    else {
        Node *newRoot = new Node(false);
        newRoot->keys.push_back(keyToPromote);
        newRoot->children.push_back(node);
        newRoot->children.push_back(rightNode);
        node->parent = newRoot;
        rightNode->parent = newRoot;
        root = newRoot;
    }


    if (node->isLeaf) {
        rightNode->next = node->next;
        node->next = rightNode;
    }
}

Tree::Node * Tree::findLeaf(Node *node,int &key){
    Node *leaf;
     if(!node) return nullptr;
     if(node->isLeaf) return node;
     //a binary seach to find the lower boundary
     auto it=std::upper_bound(node->keys.begin(),node->keys.end(),key);
     auto index=it-node->keys.begin();
     node=node->children[index];
     return findLeaf(node,key);
    

}

int Tree:: search(int key){
    if(!root){
        throw std::runtime_error("empty tree<");

    }

    Node *leaf=findLeaf(root,key);
    if(!leaf) throw std::runtime_error("key not found");

    
    int left=0,right=leaf->keys.size()-1;

    while(left<=right){
        int mid=left+(right-left)/2;

        if(leaf->keys[mid]==key) return key;

        if(leaf->keys[mid]<key) left=mid+1;
        else right=mid-1;
    }
  
    throw std::runtime_error("Key not found");
   
}




