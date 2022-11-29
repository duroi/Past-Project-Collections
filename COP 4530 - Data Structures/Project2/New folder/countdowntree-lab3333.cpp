#include "countdowntree.h"
//g++ -std=c++14 countdowntree-lab.cpp countdowntree-provided.cpp countdowntree-driver.cpp



bool CountdownTree::contains(int x) const{ //not optional

    if(x == this->root->data){
        return true;
    }else if(x > this->root->data){
        //process right
        if(root->right->search(x) == nullptr){
            return false;
        }else{
            return true;
        }
    }else if(x < this->root->data){
        //process left
        if(root->left->search(x) == nullptr){
            return false;
        }else{
            return true;
        }   
    }else{
        return false;
    }

}

Node* Node::search(int x){//optional
    if(x == this->data){
        return this;
    }else if(x > this->data){
        if(this->right != nullptr)
            return this->right->search(x);
        else
            return nullptr;
    }else if(x < this->data){
        if(this->left!=nullptr)
            return this->left->search(x);
        else 
            return nullptr;
    }else{
        return nullptr;
    }
}

/*

END CONTAINS FUNCTION MATERIAL

*/

void CountdownTree::insert(int x){

    if(size == 0){
        root = new Node(x);
    }else{
        root->insert(x);// this is a node insert
    }
    size++;
    
    count--;
    if(count == 0){
        root->rebalance();
        
        if(this->getHeight()<10){
            count = 10;
        }else{
            count = this->getHeight();
        }
    }

}
/*
Node* Node::max(){

    //this always equals root
    Node* returnNode = new Node();
    returnNode = this;
    if(returnNode->right != nullptr){//check left
        returnNode = returnNode->right;
        return returnNode->max();
    }else if (returnNode->left != nullptr){
        returnNode = returnNode->left;
        return returnNode->max();
    }else{
        return returnNode;
    }  

}
*/
void Node::rebalance(){//required

    if(this->left != nullptr){//left
        this->left->rebalance();
    }

    if(this->right != nullptr){//right
        this->right->rebalance();
    }

    if(this != nullptr){//self

        if(this->right == nullptr){
            this->right->height = 0;    
        }
            
        
        if(this->left == nullptr){
            this->left->height = 0;
        }
        
        if((this->right->height - this->left->height) >= 2){//check balance +2


            if((this->right->right->height - this->right->left->height) <= -1 ){//Right-Left

                this->right->left->rotateRight();
                this->parent->rotateLeft();
            }

          
            if((this->right->right->height - this->right->left->height) >= 1 ){//Right-Right
                this->right->rotateLeft();

            }
        }

        if((this->right->height - this->left->height) <= -2){//check balance -2

            if((this->left->right->height - this->left->left->height) <= -1 ){//Left-Left

                this->left->rotateRight();

            }

          
            if((this->left->right->height - this->left->left->height) >= 1 ){//Left-Right

                this->left->right->rotateLeft();
                this->parent->rotateRight();

            }
         }
    }
}


void Node::rotateLeft(){//optional
    //this is always pivot
    Node* temp = new Node(this->left->data);
    temp = this->left;

    bool isLeftChild;

    if(this->parent->parent->data > this->parent->data) {
        isLeftChild = true;
    }

    else {
        isLeftChild = false;
    }


    //parent becomes left child
    this->left = this->parent;

    //pivot becomes parent
    this->parent = this->left->parent;

    this->left->parent = this;

    //old left child becomes parent right child
    this->left->right = temp;

    this->left->right->parent = this->left;

    if(isLeftChild == true) {
        this->parent->left = this;
    }
    
    else {
        this->parent->right = this;
    }
    
    this->left->height--;

    this->height++;

}

void Node::rotateRight(){//optional
    //this is always pivot
    Node* temp = new Node(this->right->data);
    temp = this->right;

    bool isLeftChild;

    if(this->parent->parent->data > this->parent->data) {
        isLeftChild = true;
    }

    else {
        isLeftChild = false;
    }

    //parent becomes left child
    this->right = this->parent;

    //pivot becomes parent
    this->parent = this->right->parent;

    this->right->parent = this;

    //old right child becomes parent left child
    this->right->left = temp;

    this->right->left->parent = this->right;

    if(isLeftChild == true) {
        this->parent->left = this;
    }
    
    else {
        this->parent->right = this;
    }

    this->right->height--;

    this->height++;
}

void Node::insert(int x){//optional

    if(x < this->data){
        if(this->left == nullptr){
            this->left = new Node(x);
            this->left->parent = this;
            this->height++;
        }else{
            this->left->insert(x);
            this->height++;
        }
    }else if(x > this->data){
        if(this->right == nullptr){
            this->right = new Node(x);
            this->right->parent = this;
            this->height++;
        }else{
            this->right->insert(x);
            this->height++;
        }
    }

}

