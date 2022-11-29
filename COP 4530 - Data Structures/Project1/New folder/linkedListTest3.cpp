//  https://www.youtube.com/watch?v=Zgzoe8jjidk good starting video

#include <iostream>
using namespace std;
#include "instruction_list.h"


enum hilbert_t { FORWARD, TURN_LEFT, TURN_RIGHT, ODD, EVEN };


typedef struct node 
  {
    hilbert_t move;
    struct node* next;
    void operator=(const struct node& rhs)
     { move = rhs.move; }
  } node_t;

node_t* head = nullptr;
node_t* tail = nullptr;


void printList(node_t* node)
{
  while (node != nullptr)
    {
      switch(node->move)
            {
                case FORWARD:
                cout << "F ";
                break;

                case TURN_LEFT:
                cout << "L ";
                break;
                
                case TURN_RIGHT:
                cout << "R ";
                break;

                case ODD:
                cout << "O ";
                break;

                case EVEN:
                cout << "E ";
                break;
      
      
            }
      node = node->next;
    }
}

int main(void)
{
  
    node_t* first = new node();
    node_t* second = new node();
    node_t* third = new node();
    first->next = second;
    first->move = FORWARD;
    
    second->next = third;
    second->move = TURN_LEFT;
    
    third->next = nullptr;
    third->move = TURN_RIGHT;

    head = first;
    tail = third;
      
    printList(head);

    return 0;
}