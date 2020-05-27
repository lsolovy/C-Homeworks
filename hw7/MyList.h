//
// Created by solov on 4/28/2020.
//

#ifndef COVID_19_MYLIST_H
#define COVID_19_MYLIST_H

#include "Node.h"

class MyList{
public:
    MyList(){
        m_startPtr = nullptr;
        m_currentPtr = nullptr;
    }
    bool empty() const;
    void print() const;
    void insert(Node*node);
    void remove(Node node);
    void clear();
    const Node * getCurrentNode();
    void advanceToNextNode();
    void resetCurrentPtr();
     ~MyList();



private:
    Node *m_startPtr;
    Node *m_currentPtr;

};
#endif //COVID_19_MYLIST_H
