//
//  main.cpp
//  301 Assignment 4
//
//  Created by David Pedroza on 10/31/13.
//  Copyright (c) 2013 David Pedroza. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;



class NodeType {
    
public:
    NodeType( int = 0 );  		// constructor with default value for
                                // info field
    int info;                 	// data
    NodeType * link; 		// pointer to next node in the list
};

// Constructor
NodeType::NodeType( int data )
{
    info = data;
    link = 0;
}



typedef NodeType *PointerType;
PointerType head;
PointerType current;

void insert(int value, NodeType* &head); // function
void printList(NodeType *head);
void deleteNode(NodeType* &head);
void find(NodeType *head);
void selectDelete(NodeType* &head);
void printBackwards(NodeType *current);
void deleteLast( NodeType* &head);
void insertAtEnd(int value, NodeType* &head);
void selectDeleteRecursion(NodeType* &head, NodeType *current, int key);

int main()
{
    int value;
    char ans;
    head = NULL;                // head ---> null
    
    
    cout << "===== Linked-List Builder =====\n\n";
    
    cout <<"Selections: \n"
    << "Enter 'a' to Add numbers to the list\n"
    << "Enter 'e' to Add number to end\n"
    << "Enter 'd' to Delete the previous number\n"
    << "Enter 'l' to Delete from end of list\n"
    << "Enter 's' to Select Delete\n"
    << "Enter 'r' to Select Delete Recursion\n"
    << "Enter 'f' to Find a number\n"
    << "Enter 'p' to Print the list\n"
    << "Enter 'c' to Print using Recursion\n"
    << "Enter 'b' to Print backwards\n"
    << "Enter 'q' to Quit\n\n";
    
    do{
        //MENU
        
        cout << "Make a Selection: ";
        cin >> ans;
        cout << endl;
        
        //Selections
        if (ans == 'a')
        {
            cout << "Enter a value to the List: ";
            cin >> value;
            cout << endl;
        
            insert(value, head); //Add a node
        }
        else if(ans == 'e')
        {
            current = head;
            cout << "Enter a value to the end of List: ";
            cin >> value;
            cout << endl;
            insertAtEnd(value, head);
        }
        
        
        
        else if(ans =='f')//Find
            find(head);
        
        else if(ans == 'd')//Delete
            deleteNode(head);
        else if(ans == 'l')
        {
            //current = head;
            deleteLast( head);
            cout << endl;
        }
        else if(ans == 's') //Select Delete
            selectDelete(head);
        else if (ans == 'r')
        {
            current = head;
            cout << "Enter a number to search and delete: ";
            cin >> value;
            selectDeleteRecursion(head, current, value);
        }
        else if(ans == 'p')//Print
            printList(head);
        else if(ans == 'b')
        {
            current = head;
            cout << "List: ";
            printBackwards(current);
            cout << endl << endl;
        }
        
        
    }while (ans != 'q');
    
    
    cout << "GoodBye :)" << endl;
    
    
    
    return 0;
}




void insert(int value, NodeType* &head)
{
    PointerType currentPtr;

    
    currentPtr = new NodeType;  // currentPointer = "nodeType" Address
                                // currentPointer ---> ******************************
                                //                     * info = 0      *link = 0    *
                                //                     *               *            *
                                //                     ******************************
    
    currentPtr->info = value;   // currentPointer ---> ******************************
                                //                     * info = value  *link = NULL *
                                //                     *               *            *
                                //                     ******************************
    
    
    currentPtr->link = head;    // currentPointer ---> **********************************
                                //                     * info = value  *link = NULL     *
                                //                     *               *                *
                                //                     **********************************
    
    
                                
    head = currentPtr;          // head----->          ******************************
                                // currentPointer -->  * info = value  *link = NULL *
                                //                     *               *            *
                                //                     ******************************
    
}


void deleteNode(NodeType* &head)
{
    PointerType eraseNode;
    
    if(head != NULL)
    {
        eraseNode = head;
        head = head->link;
    
        delete eraseNode;
    }
    
    else
        cout << "The list is empty\n";

}



void selectDelete(NodeType* &head)
{
    PointerType current, previous, eraseNode;
    int number;
    bool found = false;
    
    cout << "Select a number to delete: ";
    cin >> number;
    
    current = head;
    previous = head;
    eraseNode = head;
    
    int count = 0;
    
    while (!found && current != NULL)
    {
        
        if ((count == 0) && current->info == number)
        {
            previous = current->link;
            head = head->link;
            eraseNode = head;
            
            delete eraseNode;
            printList(head);
            found = true;
        }
        
        else if((count > 0) && current->info == number)
        {
            eraseNode = current;
            previous->link = current->link;
            
            delete eraseNode;
            printList(head);
            found = true;
        }
        
        if(count > 0)
            previous = previous->link;
        
        current = current->link;
        count++;
    }
    
    if(!found)
        cout << "The number " << number << " not found in list\n\n";
    
}





void find(NodeType *head)
{
    PointerType finder;
    bool found = false;
    int number;
    
    finder = head;
    
    cout << "Search: ";
    cin >> number;
    
    while (finder != NULL && !found)
    {
        if(finder->info == number)
        {
            cout << "The number " << number << " is Found\n\n";
            found = true;
        }
        
        else
            finder = finder->link;
    }
    
    if (!found) {
        cout << "The number " << number << " is Not Found\n\n";

    }

}





void printList(NodeType *head)
{
    PointerType currentPtr;
    
    currentPtr = head;
    
    
    cout << "List: ";
    
    while (currentPtr != NULL)
    {
        cout << currentPtr->info << " ";
        currentPtr = currentPtr->link;
    }
    
    cout << endl << endl;
    
}


void printBackwards(NodeType *current) //using recursion 
{
    
    if (current != NULL)
    {
        printBackwards(current->link);
        cout << current->info << " ";
    }
}

void printForward(NodeType *current) //using recursion
{
    
    if (current != NULL)
    {
        cout << current->info << " ";
        printBackwards(current->link);
    }
}


void deleteLast(NodeType* &head) //using recursion
{
    
    if (head == NULL) // if the list is EMPTY
        cout << "The list is empty\n";
    else if(head->link != NULL) // recursive case
    {
        deleteLast(head->link);
    }
    
    else //Base Case
    {
        delete head;
        head = NULL;
    }
}


void insertAtEnd(int value, NodeType* &head) //using recursion
{
   
    
    if (head == NULL) //Base Case
    {
        head = new NodeType;
        head->info = value;
    }
    
    else
        insertAtEnd(value, head->link);
    

}


void selectDeleteRecursion(NodeType* &head, NodeType *current, int key)
{
    PointerType temp;
    temp = head;
    
    if (head == NULL) {
        cout << "Value not found\n";
    }
    else if(temp->info == key){
        head = head->link;
        delete temp;
    }
    
    else
        selectDeleteRecursion(head->link, current, key);
}





