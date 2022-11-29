//  https://www.youtube.com/watch?v=Zgzoe8jjidk good starting video

#include <iostream>
using namespace std;


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



int main(void)
{

    node_t* ptr = new node();
    ptr->move = FORWARD;
    ptr->next = nullptr;
    
    head = ptr;
    tail = ptr;

    if ((ptr->move == FORWARD))
        {
        cout << "forward\n";
        }

    return 0;
}