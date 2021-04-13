#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <regex>
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
    bool isEmpty();
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
    this->pStart = nullptr;
    this->pEnd = nullptr;
}

template <class T>
string SimpleList<T>::getName(void)
{
    return name;
}

template <class T>
bool SimpleList<T>::isEmpty(void)
{
    //cout << (pStart == nullptr) << (pEnd == nullptr) << '\n';
    return (pStart == nullptr && pEnd == nullptr);
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
    Node *temp = this->pStart;
    T val = this->pStart->getVal();

    if (temp->getNextNode() == nullptr)
    {
        this->pEnd = nullptr;
    }

    this->pStart = temp->getNextNode();
    delete temp;

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

template <class T>
SimpleList<T> *listExists(string name, list<SimpleList<T> *> *list)
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

void create(string name, string parameter, list<SimpleList<int> *> *iListP, list<SimpleList<double> *> *dListP, list<SimpleList<string> *> *sListP)
{
    if (name[0] == 'i')
    {
        SimpleList<int> *list = listExists(name, iListP);
        if (list != NULL)
        {
            cout << "ERROR: This name already exists!\n";
        }
        else
        {
            iListP->push_back(parameter == "stack" ? new Stack<int>(name) : new Stack<int>(name));
        }
    }
    else if (name[0] == 'd')
    {
        SimpleList<double> *list = listExists(name, dListP);
        if (list != NULL)
        {
            cout << "ERROR: This name already exists!\n";
        }
        else
        {
            dListP->push_back(parameter == "stack" ? new Stack<double>(name) : new Stack<double>(name));
        }
    }
    else if (name[0] == 's')
    {
        SimpleList<string> *list = listExists(name, sListP);
        if (list != NULL)
        {
            cout << "ERROR: This name already exists!\n";
        }
        else
        {
            sListP->push_back(parameter == "stack" ? new Stack<string>(name) : new Stack<string>(name));
        }
    }
}

void push(string name, string parameter, list<SimpleList<int> *> *iListP, list<SimpleList<double> *> *dListP, list<SimpleList<string> *> *sListP)
{
    if (name[0] == 'i')
    {
        SimpleList<int> *list = listExists(name, iListP);
        if (list != NULL)
        {
            list->push(stoi(parameter));
        }
        else
        {
            cout << "ERROR: This name does not exist!\n";
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
            cout << "ERROR: This name does not exist!\n";
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
            cout << "ERROR: This name does not exist!\n";
        }
    }
}

void pop(string name, list<SimpleList<int> *> *iListP, list<SimpleList<double> *> *dListP, list<SimpleList<string> *> *sListP)
{
    if (name[0] == 'i')
    {
        SimpleList<int> *list = listExists(name, iListP);

        if (list != nullptr)
        {
            if (list->isEmpty())
            {
                cout << "ERROR: This list is empty!\n";
            }
            else
            {
                int val = list->pop();
                cout << "Value Popped: " << val << '\n';
            }
        }
        else
        {
            cout << "ERROR: This name does not exist!\n";
        }
    }
    else if (name[0] == 'd')
    {
        SimpleList<double> *list = listExists(name, dListP);

        if (list != nullptr)
        {
            if (list->isEmpty())
            {
            }
            else
            {
                double val = list->pop();
                cout << "Value Popped: " << val << '\n';
            }
        }
        else
        {
            cout << "ERROR: This name does not exist!\n";
        }
    }
    else if (name[0] == 's')
    {
        SimpleList<string> *list = listExists(name, sListP);

        if (list != nullptr)
        {
            if (list->isEmpty())
            {
                cout << "ERROR: This list is empty!\n";
            }
            else
            {
                string val = list->pop();
                cout << "Value Popped: " << val << '\n';
            }
        }
        else
        {
            cout << "ERROR: This name does not exist!\n";
        }
    }
}

void processCommand(string cmd, list<SimpleList<int> *> *iListP, list<SimpleList<double> *> *dListP, list<SimpleList<string> *> *sListP)
{
    regex r("(\\w+) (\\w+) ?(.*)?");
    smatch m;

    if (regex_search(cmd, m, r))
    {
        string action = m[1];
        string name = m[2];
        string parameter = m[3];

        cout << "PROCESSING COMMAND: " << cmd << '\n';

        if (action == "create")
        {
            create(name, parameter, iListP, dListP, sListP);
        }
        else if (action == "push")
        {
            push(name, parameter, iListP, dListP, sListP);
        }
        else if (action == "pop")
        {
            pop(name, iListP, dListP, sListP);
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
    string cmd;

    list<SimpleList<int> *> iList;
    list<SimpleList<double> *> dList;
    list<SimpleList<string> *> sList;

    if (inputFile.is_open())
    {
        while (getline(inputFile, cmd))
        {
            processCommand(cmd, &iList, &dList, &sList);
        }
    }

    return 0;
}