#include <string>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

template <class T>
class SimpleList
{
private:
    class Node
    {
    private:
        T val;
        Node *nextNode;

    public:
        Node();
        Node(T val, Node *nextNode);
        T getVal();
        void setNextNode(Node *nextNode);
        Node *getNextNode();
    };

    string name;
    Node *pStart;
    Node *pEnd;

public:
    SimpleList(string name);
    string getName(void);
    virtual void push(T val) = 0;
    virtual T pop() = 0;

protected:
    void insertAtStart(T val);
    void insertAtEnd(T val);
    T removeFromStart();
};

template <class T>
SimpleList<T>::SimpleList(string name)
{
    this->name = name;
}

template <class T>
string SimpleList<T>::getName(void)
{
    return name;
}

template <class T>
SimpleList<T>::Node::Node(){};

template <class T>
SimpleList<T>::Node::Node(T val, Node *nextNode)
{
    this->val = val;
    this->nextNode = nextNode;
};

template <class T>
T SimpleList<T>::Node::getVal(void)
{
    return this->val;
};

template <class T>
void SimpleList<T>::Node::setNextNode(Node *nextNode)
{
    this->nextNode = nextNode;
}

template <class T>
typename SimpleList<T>::Node *SimpleList<T>::Node::getNextNode()
{
    return this->nextNode;
}

template <class T>
void SimpleList<T>::insertAtStart(T val)
{
    SimpleList<T>::Node *node = new Node(val, this->pStart);

    if (this->pStart == nullptr)
    {
        this->pEnd = node;
    }

    this->pStart = node;
}

template <class T>
void SimpleList<T>::insertAtEnd(T val)
{
    SimpleList<T>::Node *node = new Node(val, nullptr);

    if (this->pEnd == nullptr)
    {
        this->pStart = node;
    }
    else
    {
        this->pEnd->setNextNode(node);
    }

    this->pEnd = node;
}

template <class T>
T SimpleList<T>::removeFromStart()
{
    Node *temp = this->pStart->getNextNode();
    T val = this->pStart->getVal();
    delete this->pStart;
    this->pStart = temp;

    return val;
}

template <class T>
class Stack : public SimpleList<T>
{
public:
    Stack(string name) : SimpleList<T>(name){};
    void push(T val);
    T pop();
};

template <class T>
void Stack<T>::push(T val)
{
    SimpleList<T>::insertAtStart(val);
}

template <class T>
T Stack<T>::pop()
{
    return SimpleList<T>::removeFromStart();
}

template <class T>
class Queue : public SimpleList<T>
{
public:
    Queue(string name) : SimpleList<T>(name){};
    void push(T val);
    T pop();
};

template <class T>
void Queue<T>::push(T val)
{
    SimpleList<T>::insertAtEnd(val);
}

template <class T>
T Queue<T>::pop()
{
    return SimpleList<T>::removeFromStart();
}

void create()
{
}

void push()
{
}

void pop()
{
}

void processCommand(string cmd)
{
    cout << "PROCESSING COMMAND: " << cmd << '\n';
    string type = cmd.substr(0, cmd.find(' '));

    if (type == "create")
    {
        create();
    }
    else if (type == "push")
    {
    }
    else if (type == "pop")
    {
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
    string cmd;

    list<SimpleList<int> *> iList;
    list<SimpleList<double> *> dList;
    list<SimpleList<string> *> sList;

    if (inputFile.is_open())
    {
        while (getline(inputFile, cmd))
        {
            processCommand(cmd);
        }
    }

    return 0;
}