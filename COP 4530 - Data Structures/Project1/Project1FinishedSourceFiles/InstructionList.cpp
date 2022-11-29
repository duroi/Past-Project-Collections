//COP 4530
//IGLI DURO (DRIVER)
//AUSTYN MIKOLON (NAVIGATOR)

#include "instruction_list.h"

using namespace std;

ostream& operator<< (ostream& out, const InstructionList& list)
{
	//curr is a node to hold the current node to print
	InstructionList::node* curr = list.head;

	//while loop to loop though the list
	while (curr != nullptr)
	{
		//switch to determine the letter to print
		switch (curr->move)
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
			out << "Error!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
			break;
		}
		//go to the next node in the list
		curr = curr->next;
	}

	return out;

}

//Prints the instruction list
// prints the InstructionList.  Instructions should be separated by spaces, and each instruction should be printed as a single character:  
//F (FORWARD), L (TURN_LEFT), R (TURN_RIGHT), O (ODD), or E (EVEN).  You may print an additional space at the end, for simplicity.

void InstructionList::append(hilbert_t ins)
{
	//new node to hold the new instruction coming in
	node* newIns = new node();

	newIns->move = ins;

	//if at the beginning of the list put the node at the beginning
	if (head == nullptr)
	{
		head = newIns;
		newIns->next = nullptr;
		tail = newIns;
	}
	//else make the new node the end of the list 
	else
	{
		tail->next = newIns;
		newIns->next = nullptr;
		tail = newIns;
	}


}

//add instructions to end of the list
//adds the given instruction (one of FORWARD, TURN_LEFT, TURN_RIGHT, ODD, or EVEN) to the end of the list.

void InstructionList::substitute(const unordered_map<hilbert_t, const InstructionList*>& map)
{
	//new nodes to hold the next node in rules as we subsitute,
	//and a node to run thought the list 
	node* rules = head;
	node* holder = new node();

	//run while the until we are at the end of the list
	while (rules != nullptr)
	{
		//if rules equals odd then run the statement
		if (rules->move == ODD)
		{
			//node to run though the odd list 
			node* odd = map.at(ODD)->head;
			//holding the next instruction in rules 
			holder = rules->next;
			//subsitute in the odd list of nodes
			while (odd != nullptr)
			{
				rules->next = new node();
				rules->move = odd->move;
				//prevents the creation of an extra foward move
				if (odd->next != nullptr)
				{
					rules = rules->next;
				}
				odd = odd->next;
			}
			//continue with where you left off
			rules->next = holder;
		}
		
		//if rules equals even then run this statment
		if (rules->move == EVEN)
		{
			node* even = map.at(EVEN)->head;
			holder = rules->next;
			//subsitute in the even list of nodes 
			while (even != nullptr)
			{
				rules->next = new node();
				rules->move = even->move;
				
				//prevents the creation of an extra foward move
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

//iterates through this InstructionList, replacing instructions in the list according to the substitution rules given in the map.
//To generate a Hilbert curve, your map should have one entry for ODDand another for EVEN, though this function should be able to apply any substitution rule.
//O->L, E, F, R, O, F, O, R, F, E, L
//E->R, O, F, L, E, F, E, L, F, O, R;

InstructionList::~InstructionList()
{
	//node to hold a temp node
	node* temp;
	//while head is not equal to null pointer run the loop and delete all the nodes
	while (head != nullptr)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

