// COP 4530
// IGLI DURO U#3376-6202 (DRIVER) 
// AUSTYN MIKOLON (NAVIGATOR)

#include "instruction_list.h"
#include <iostream>
#include <unordered_map>
using namespace std;

ostream& operator<<(ostream& out, const InstructionList& list)
{
//prints the InstructionList.  
//Instructions should be separated by spaces, and each instruction should be printed as a single character:  
//F (FORWARD), L (TURN_LEFT), R (TURN_RIGHT), O (ODD), or E (EVEN).  You may print an additional space at the end, for simplicity.



    InstructionList::node_t* curr = list.head;

    
    while (curr != nullptr)
        {
            switch(curr->move)
            {
                case FORWARD:
                out << "F ";
                break;

                case TURN_LEFT:
                out << "L ";
                break;
                
                case TURN_RIGHT:
                out << "R ";
                break;

                case ODD:
                out << "O ";
                break;

                case EVEN:
                out << "E ";
                break;

                default:
                out << "ERROR!!!!!!!!!!!!!!!!!!!!";
                break;

            }

    
        curr = curr->next;
        }

    return out;
}



void InstructionList::append(hilbert_t ins)
{
//adds the given instruction (one of FORWARD, TURN_LEFT, TURN_RIGHT, ODD, or EVEN) to the end of the list
    
    node_t* append = new node();

    append->move = ins;

    if (head == nullptr)
    {
        head = append;
        append->next = nullptr;
        tail = append;
    }
    
    else 
    {
        tail->next = append;
        append->next = nullptr;
        tail = append;
    }

}



void InstructionList::substitute(const unordered_map<hilbert_t, const InstructionList*>& map)
{
    //iterates through this InstructionList, replacing instructions in the list according to the substitution rules given in the map.  
    //To generate a Hilbert curve, your map should have one entry for ODD and another for EVEN, though this function should be able to apply any substitution rule.

    //O -> L, E, F, R, O, F, O, R, F, E, L
    //ENUM 1, 4, 0, 2, 3, 0, 3, 2, 0, 4, 1
   
    //E -> R, O, F, L, E, F, E, L, F, O, R
    //ENUM 2, 3, 0, 1, 4, 0, 4, 1, 0, 3, 2


    node* rules = head;
    node* holder = new node();

    while (rules != nullptr)
    {
        if (rules->move == ODD)
        {
            node* odd = map.at(ODD)->head;
            holder = rules->next;
            while (odd != nullptr)
            {
                rules->next = new node();
                rules->move = odd->move;
                
                if (odd->next != nullptr)
                {
                    rules = rules->next;
                }

                odd = odd->next;
            }
            rules->next = holder;
        }
        
        if (rules->move == EVEN)
        {
            node* even = map.at(EVEN)->head;
            holder = rules->next;
            while (even != nullptr)
            {
                rules->next = new node();
                rules->move = even->move;

                if (even->next != nullptr)
                {
                    rules = rules->next;
                }

                even = even->next;
            }
            rules->next = holder;
        }
        rules = rules->next;
    }

    
}

InstructionList::~InstructionList()
{
//destructor for InstructionList, which should deallocate all of the Nodes in the list
    node_t* temp;
    while( head != nullptr )
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}

/*

int main ()
{
    cout << endl;

    unordered_map<hilbert_t, const InstructionList*> rules;
    InstructionList list;

    list.append(ODD);
    //list.append(FORWARD);
    //list.append(TURN_LEFT);
    //list.append(EVEN);

    InstructionList odd;
    const InstructionList* oddPtr = &odd;
//O -> L, E, F, R, O, F, O, R, F, E, L
    odd.append(TURN_LEFT);
    odd.append(EVEN);
    odd.append(FORWARD);
    odd.append(TURN_RIGHT);
    odd.append(ODD);
    odd.append(FORWARD);
    odd.append(ODD);
    odd.append(TURN_RIGHT);
    odd.append(FORWARD);
    odd.append(EVEN);
    odd.append(TURN_LEFT);

//E -> R, O, F, L, E, F, E, L, F, O, R

    InstructionList even;
    const InstructionList* evenPtr = &even;

    even.append(TURN_RIGHT);
    even.append(ODD);
    even.append(FORWARD);
    even.append(TURN_LEFT);
    even.append(EVEN);
    even.append(FORWARD);
    even.append(EVEN);
    even.append(TURN_LEFT);
    even.append(FORWARD);
    even.append(ODD);
    even.append(TURN_RIGHT);

    rules[ODD] = oddPtr;
    rules[EVEN] = evenPtr;
    
    cout << list << endl;

    list.substitute(rules);
   
    cout << list << endl;

    list.substitute(rules);

    cout << list << endl;

    return 0;
}

*/