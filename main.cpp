/*
* Gavri Kepets
* ECE264 DSA1 Project 1
*
* This program is an implementation of the Stack and Queue data structures.
* Basic functions such as insertAtStart, insertAtEnd and removeFromStart
* were implemented for different push and pop operations for the stacks and queues.
*/

#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <regex>
using namespace std;

template <class T>
class SimpleList // The SimpleList Class is the base class for Stacks and Queues
{
private:
    class Node // The Node class keeps track of each element in a SimpleList
    {
    private:
        T val;          // Value in the node (can be string, double, int, etc.)
        Node *nextNode; // The next node in the list

    public:
        Node(){};
        Node(T val, Node *nextNode);
        T getVal();
        void setNextNode(Node *nextNode);
        Node *getNextNode();
    };
    string name;  // Name of the list
    Node *pStart; // A pointer to the node at the beginning of the list
    Node *pEnd;   // A pointer to the node at the end of the list

public:
    SimpleList(string name);
    string getName(void);
    bool isEmpty();
    virtual void push(T val) = 0;
    virtual T pop() = 0;

protected:
    void insertAtStart(T val);
    void insertAtEnd(T val);
    T removeFromStart();
};

template <class T>
SimpleList<T>::SimpleList(string name) // Constructor for SimpleList
{
    this->name = name;
    this->pStart = nullptr;
    this->pEnd = nullptr;
}

template <class T>
string SimpleList<T>::getName(void) // Getter function for SimpleList Name
{
    return this->name;
}

template <class T>
bool SimpleList<T>::isEmpty(void) // Function that checks if a SimpleList is empty
{
    return (pStart == nullptr && pEnd == nullptr);
}

template <class T>
SimpleList<T>::Node::Node(T val, Node *nextNode) // Constructor for Node
{
    this->val = val;
    this->nextNode = nextNode;
};

template <class T>
T SimpleList<T>::Node::getVal(void) // Getter function for a Node value
{
    return this->val;
};

template <class T>
void SimpleList<T>::Node::setNextNode(Node *nextNode) // Setter function for a Node's next node
{
    this->nextNode = nextNode;
}

template <class T>
typename SimpleList<T>::Node *SimpleList<T>::Node::getNextNode() // Getter function for a Node's next node
{
    return this->nextNode;
}

template <class T>
void SimpleList<T>::insertAtStart(T val) // Function to insert Node at the start of a SimpleList
{
    SimpleList<T>::Node *node = new Node(val, this->pStart);

    if (this->isEmpty()) // If the list is empty, set the end and start node to this one.
    {
        this->pEnd = node;
    }

    this->pStart = node;
}

template <class T>
void SimpleList<T>::insertAtEnd(T val) // Function that inserts node at the start of a SimpleList
{
    SimpleList<T>::Node *node = new Node(val, nullptr);

    if (this->isEmpty()) // If the list is empty, set the end and start node to this one.
    {
        this->pStart = node;
    }
    else
    {
        this->pEnd->setNextNode(node); // If the list is not empty, set the next node of the last node to the one that is about to be added.
    }

    this->pEnd = node;
}

template <class T>
T SimpleList<T>::removeFromStart() // Function that removes node from the start of a SimpleList
{
    Node *currentStart = this->pStart;
    T val = this->pStart->getVal();

    if (currentStart->getNextNode() == nullptr)
    {
        this->pEnd = nullptr;
    }

    this->pStart = currentStart->getNextNode();
    delete currentStart;

    return val;
}

template <class T>
class Stack : public SimpleList<T> // Stack class that is derived from a SimpleList
{
public:
    Stack(string name) : SimpleList<T>(name){};
    void push(T val);
    T pop();
};

template <class T>
void Stack<T>::push(T val) // Push function which inserts a node at the top of the list
{
    SimpleList<T>::insertAtStart(val);
}

template <class T>
T Stack<T>::pop() // Pop function which removes a node from the top of the list
{
    return SimpleList<T>::removeFromStart();
}

template <class T>
class Queue : public SimpleList<T> // Queue class that is derived from a SimpleList
{
public:
    Queue(string name) : SimpleList<T>(name){};
    void push(T val);
    T pop();
};

template <class T>
void Queue<T>::push(T val) // Push function which inserts a node at the bottom of the list
{
    SimpleList<T>::insertAtEnd(val);
}

template <class T>
T Queue<T>::pop() // Pop function which removes a node from the top of the list
{
    return SimpleList<T>::removeFromStart();
}

template <class T>
SimpleList<T> *listExists(string name, list<SimpleList<T> *> *list) // Function to check if a list already exists
{
    for (auto obj : *list)
    {
        if (obj->getName() == name)
        {
            return obj;
        }
    }

    return NULL;
}

void create(string name, string parameter, list<SimpleList<int> *> *iListP, list<SimpleList<double> *> *dListP, list<SimpleList<string> *> *sListP, ofstream *outputFile) // Function that creates a Stack or Queue
{
    if (name[0] == 'i') // If it is an integer list
    {
        SimpleList<int> *list = listExists(name, iListP);

        if (list != NULL) // If the list exists print an error
        {
            *outputFile << "ERROR: This name already exists!" << '\n';
        }
        else
        {
            iListP->push_back(parameter == "stack" ? (SimpleList<int> *)new Stack<int>(name) : (SimpleList<int> *)new Queue<int>(name)); // Push a newly created Stack or Queue based on a ternary operator and the parameter from the command.
        }
    }
    else if (name[0] == 'd')
    {
        SimpleList<double> *list = listExists(name, dListP);

        if (list != NULL)
        {
            *outputFile << "ERROR: This name already exists!" << '\n';
        }
        else
        {
            dListP->push_back(parameter == "stack" ? (SimpleList<double> *)new Stack<double>(name) : (SimpleList<double> *)new Queue<double>(name));
        }
    }
    else if (name[0] == 's')
    {
        SimpleList<string> *list = listExists(name, sListP);

        if (list != NULL)
        {
            *outputFile << "ERROR: This name already exists!" << '\n';
        }
        else
        {
            sListP->push_back(parameter == "stack" ? (SimpleList<string> *)new Stack<string>(name) : (SimpleList<string> *)new Queue<string>(name));
        }
    }
}

void push(string name, string parameter, list<SimpleList<int> *> *iListP, list<SimpleList<double> *> *dListP, list<SimpleList<string> *> *sListP, ofstream *outputFile) // Function that runs a push command
{
    if (name[0] == 'i')
    {
        SimpleList<int> *list = listExists(name, iListP); // Check for existence

        if (list != NULL)
        {
            list->push(stoi(parameter));
        }
        else
        {
            *outputFile << "ERROR: This name does not exist!" << '\n';
        }
    }
    else if (name[0] == 'd')
    {
        SimpleList<double> *list = listExists(name, dListP);

        if (list != NULL)
        {
            list->push(stod(parameter));
        }
        else
        {
            *outputFile << "ERROR: This name does not exist!" << '\n';
        }
    }
    else if (name[0] == 's')
    {
        SimpleList<string> *list = listExists(name, sListP);

        if (list != NULL)
        {
            list->push(parameter);
        }
        else
        {
            *outputFile << "ERROR: This name does not exist!" << '\n';
        }
    }
}

void pop(string name, list<SimpleList<int> *> *iListP, list<SimpleList<double> *> *dListP, list<SimpleList<string> *> *sListP, ofstream *outputFile) // Function that runs the pop command
{
    if (name[0] == 'i')
    {
        SimpleList<int> *list = listExists(name, iListP);

        if (list != nullptr) // First check if the list exists
        {
            if (list->isEmpty()) // The check if it is empty
            {
                *outputFile << "ERROR: This list is empty!" << '\n';
            }
            else
            {
                int val = list->pop(); // If it is not empty and it exists, pop the value
                *outputFile << "Value popped: " << val << '\n';
            }
        }
        else
        {
            *outputFile << "ERROR: This name does not exist!" << '\n';
        }
    }
    else if (name[0] == 'd')
    {
        SimpleList<double> *list = listExists(name, dListP);

        if (list != nullptr)
        {
            if (list->isEmpty())
            {
                *outputFile << "ERROR: This list is empty!" << '\n';
            }
            else
            {
                double val = list->pop();
                *outputFile << "Value popped: " << val << '\n';
            }
        }
        else
        {
            *outputFile << "ERROR: This name does not exist!" << '\n';
        }
    }
    else if (name[0] == 's')
    {
        SimpleList<string> *list = listExists(name, sListP);

        if (list != nullptr)
        {
            if (list->isEmpty())
            {
                *outputFile << "ERROR: This list is empty!" << '\n';
            }
            else
            {
                string val = list->pop();
                *outputFile << "Value popped: " << val << '\n';
            }
        }
        else
        {
            *outputFile << "ERROR: This name does not exist!" << '\n';
        }
    }
}

void processCommand(string cmd, list<SimpleList<int> *> *iListP, list<SimpleList<double> *> *dListP, list<SimpleList<string> *> *sListP, ofstream *outputFile) // Function that runs a command
{
    /* Regex parses the command. Each parentheses is a group, and in each group can be a string.
    Some commands are 2 strings and others are 3, so the question marks mark the space after the second group
    as well as the entire third group as optional.*/
    regex r("(\\w+) (\\w+) ?(.*)?");
    smatch m;

    if (regex_search(cmd, m, r)) // search for matches to the regex pattern
    {
        string action = m[1];    // group one is the action from the command
        string name = m[2];      // group two is the name of the list
        string parameter = m[3]; // group three is for values to push or names of lists to create

        *outputFile << "PROCESSING COMMAND: " << cmd << '\n';

        if (action == "create")
        {
            create(name, parameter, iListP, dListP, sListP, outputFile);
        }
        else if (action == "push")
        {
            push(name, parameter, iListP, dListP, sListP, outputFile);
        }
        else if (action == "pop")
        {
            pop(name, iListP, dListP, sListP, outputFile);
        }
    }
}

int main()
{
    string inputFileName;
    string outputFileName;

    cout << "Please input the name of the instruction file.\n";
    cin >> inputFileName;

    cout << "Please input the name of the output file.\n";
    cin >> outputFileName;

    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);
    string cmd;

    list<SimpleList<int> *> iList;
    list<SimpleList<double> *> dList;
    list<SimpleList<string> *> sList;

    if (inputFile.is_open())
    {
        while (getline(inputFile, cmd)) // continuously loop through the input command file and run each command until the file ends
        {
            processCommand(cmd, &iList, &dList, &sList, &outputFile);
        }
    }

    return 0;
}