#include "BPlusTree.h"
#include<iostream>
#include <string>
#include<vector>

int main() {

    
    
    //  // Initialize a B+ Tree with a degree of 3
     Tree tree(4);

    //  Insert some keys and values
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
     
     auto res=tree.rangeQuery(0,100);
   
    
      for(auto key:res){
         std::cout<<key<<" ";
      }
      std::cout<<" "<<std::endl;

    
                     
    return 0;
}







