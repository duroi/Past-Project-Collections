
#include <iostream>
using namespace std;

//Implement the equeue(), dequeue(), and peak(), member functions for the queue class.
class queue
{

    typedef struct node
    {   
        int value;
        node_t* next;
    } note_t;

    //Assume CircularlyLinkedList class member functions are fully implemented and functional.
    class CircularlyLinkedList
    {
    private:
        node_t* head;
        node_t* tail;

    public:
        CircularlyLinkedList();
        node_t* getHead();
        node_t* getTail();
        void insert(node_t* before, int value);
        void remove(node_t* victim);

    };

private:
    CircularlyLinkedList cll;

public:
    queue();
    void enqueue();
    void dequeue();
    const peek();

};

//Add a new element to the back of the queue. Append.
void queue::enqueue(CircularlyLinkedList cll, note_t append)
{
    getTail()->next = append;
    append->next = getHead();
    getTail() = append;
}

//Remove the element to the front of the queue. Delete head.
void queue::dequeue(CircularlyLinkedList cll)
{
    remove(getHead());
}
//Retrurn the front of the queue without removing. Return head.
const queue::peek(const CircularlyLinkedList cll)
{
    return getHead();
}