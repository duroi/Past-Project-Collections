#include "countdowntree.h"
//g++ -std=c++14 countdowntree-lab.cpp countdowntree-provided.cpp countdowntree-driver.cpp

/*
BEGIN SEARCH FUNCTION MATERIAL: 
    THE FOLLOWING FUNCTIONS WERE: 
        DRIVEN BY ALBERT BARRON DINKINS
        NAVIGATED BY IGLI DURO

*/
bool CountdownTree::contains(int x) const{//not optional

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

void CountdownTree::insert(int x){//REQUIRED COUNTDOWNTREE INSERT

    
    if(size == 0){
        root = new Node(x);
    }else{
        root->insert(x);// this is a node insert
    }
    size++;
    
    count--;
    if(count == 0){
        root->rebalance();
        
        while(root->parent != nullptr){
            root = root->parent;
        }

        root->updateHeight();
        
        if(this->getHeight() <= 10){
            count = 10;
        }else if(this->getHeight() > 10){
            count = this->getHeight();
        }
    }

}

void Node::insert(int x){//optional NODE INSERT

    if(x < this->data){
        if(this->left == nullptr){
            this->left = new Node(x);
            this->left->parent = this;
           
            this->updateHeight();
            
        }else{
            this->left->insert(x);
            
            this->updateHeight();
           
        }
    }else if(x > this->data){
        if(this->right == nullptr){
            this->right = new Node(x);
            this->right->parent = this;
            
            this->updateHeight();
            
        }else{
            this->right->insert(x);
            
            this->updateHeight();
        }
    }

}


/*

END CONTAINS FUNCTION MATERIAL-------------------------

BEGIN DELETE FUNCTION MATERIAL: 
    THE FOLLOWING FUNCTIONS WERE: 
        DRIVEN BY IGLI DURO
        NAVIGATED BY ALBERT BARRON DINKINS

*/



void Node::rebalance(){//required NODE REBALANCE

    if(this->left != nullptr){//left
        this->left->rebalance();
    }

    if(this->right != nullptr){//right
        this->right->rebalance();
    }

        //temporary values
        //left and right child of this
        int rightHeight = 0;
        int leftHeight = 0;
        
        if( this->right != nullptr)
            rightHeight = this->right->height;
        if( this->left != nullptr)
            leftHeight = this->left->height;
        
        //left and right child of this->left
        int leftRightHeight = 0;
        int leftLeftHeight = 0;
        if(this->left != nullptr){
            if( this->left->right != nullptr)
                leftRightHeight = this->left->right->height;
            if( this->left->left != nullptr )
                leftLeftHeight = this->left->left->height;
        }   
        
        //right and left child of this->right
        int rightRightHeight = 0;
        int rightLeftHeight = 0; 
        
        if(this->right != nullptr){
            if( this->right->right != nullptr)
                rightRightHeight = this->right->right->height;
            if( this->right->left != nullptr)
                rightLeftHeight = this->right->left->height;
        }

        
        if((rightHeight - leftHeight) >= 2){//check balance +2
        
            
            if((rightRightHeight - rightLeftHeight) < 0 ){//Right-Left (positive, negative case)
                
                //cout << "RL " << data  << endl;
                if((this->right != nullptr) && (this->right->left != nullptr)){
                
                   
                    this->right->left->rotateRight();
                
                }
                if(this->right != nullptr){
                    
                    this->right->rotateLeft();
                    
                }

            }else{//Right-Right (positive, positive)


                if(this->right != nullptr){
                   
                    this->right->rotateLeft();
                }


            }
            
                
        }
        
        if((rightHeight - leftHeight) <= -2){//check balance -2
            
            
            if((leftRightHeight - leftLeftHeight) > 0 ){//Left-right (negative, positive case)

         
                
                if((this->left != nullptr) && (this->left->right != nullptr)){
                    this->left->right->rotateLeft();
                }

                if(this->left != nullptr){
                
                   this->left->rotateRight();
                }
               

            }else{//Left-left (negative, negative)
              
            
                if(this->left != nullptr){
                    this->left->rotateRight();
                }

            }
            
                
        }

        this->updateHeight();
    
}


void Node::rotateLeft(){//optional: Partially sourced from lecture 11's avl.h by Dr. William Hendrix
    //this is always pivot
   
    if(this->parent != nullptr)
        this->parent->right = this->left;

    if(this->left != nullptr)
        this->left->parent = this->parent;

    this->left = this->parent;

    this->parent = this->parent->parent;


    if(this->left->isLeftChild() == true){

        this->parent->left = this;

    }else if(this->left->isRightChild() == true){ 

        this->parent->right = this;

    }
    

    this->left->parent = this;

    //update height function goes here
    this->left->updateHeight();
    this->updateHeight();


}

void Node::rotateRight(){//optional: Partially sourced from lecture 11's avl.h by Dr. William Hendrix
    //this is always pivot
   
    if(this->parent != nullptr)
        this->parent->left = this->right;

    if(this->right != nullptr)
        this->right->parent = this->parent;
        
    this->right = this->parent;
    this->parent = this->parent->parent;

    if(this->right->isLeftChild() == true){

        this->parent->left = this;

    }else if(this->right->isRightChild() == true){

        this->parent->right = this;

    }

    this->right->parent = this;

    //update height function goes here
    this->right->updateHeight();
    this->updateHeight();

}

bool Node::isLeftChild() const{//OPTIONAL: Sourced from lecture 10's bst-soln.cpp by Dr. William Hendrix

    return (parent != nullptr && parent->left == this);
}


bool Node::isRightChild() const{//OPTIONAL: Sourced from lecture 10's bst-soln.cpp by Dr. William Hendrix

    return (parent != nullptr && parent->right == this);
}


void Node::updateHeight(){//OPTIONAL

    if(this->left == nullptr && this->right ==nullptr)
        this->height = 1;

    if(this->left != nullptr && this->right == nullptr){
        this->height = this->left->height +1;
    }

    if(this->left == nullptr && this->right != nullptr){
        this->height = this->right->height +1;
    }

    if(this->left != nullptr && this->right != nullptr){
        if(this->left->height > this->right->height){
            this->height = this->left->height + 1;
    
        }else{
            this->height = this->right->height + 1;
    
        }
    }
}




/*

ENDS REBALANCE/INSERT FUNCTION MATERIAL -----------------------------------

BEGIN DELETE FUNCTION MATERIAL: 
    THE FOLLOWING FUNCTIONS WERE: 
        DRIVEN BY ALBERT BARRON DINKINS 
        NAVIGATED BY IGLI DURO

*/


Node* Node::max(){

    //this always equals root
    Node* returnNode = this;
 
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


void CountdownTree::remove(int x){//Partially sourced from lecture 10's bst-soln.cpp by Dr. William Hendrix
    if(root == nullptr)
        return;
    
    Node* victim = root->search(x); 
    Node* parent = new Node(0);
    
    if(victim == nullptr)
        return;

    if(victim == root){
        
        root = victim->remove();
        
        Node* bottom = root;

        if(root->left != nullptr || root == nullptr)
            bottom = root->left->max();


        while(bottom != root){
            bottom->updateHeight();  
            bottom = bottom->parent;    
        }

        if(root != nullptr)
            root->updateHeight();
        
    }else{
       
        parent = victim->parent;
     
        victim->remove();
        while(parent != root){
            parent->updateHeight();
            parent = parent->parent;
        }
    }
    root->updateHeight();
    size--;

}

Node* Node::remove(){ //Sourced from lecture 10's bst-soln.cpp by Dr. William Hendrix
    int numChildren = (left != nullptr) + (right != nullptr);

    if(numChildren == 0){
        if(isLeftChild())
            parent->left = nullptr;
        else if(isRightChild())
            parent->right = nullptr;

        delete this;
        return nullptr;
    }else if(numChildren == 1){
        Node* child;
        if(left != nullptr)
            child = left;
        else    
            child = right;

        child->parent = parent;

        if(isLeftChild())
            parent->left = child;
        else if(isRightChild())
            parent->right = child;

        left = right = nullptr;
        delete this;
        return child;
    }else{
        Node* swap = left->max();
        data = swap->data;
        swap->remove();
        return this;
    }

}