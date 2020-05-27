//
// Created by solov on 4/28/2020.
//
#include <iostream>
#include "MyList.h"

using namespace std;

bool MyList :: empty () const {
    return m_startPtr == nullptr;
}

void MyList :: print() const {
    if(empty()){
        cout << "Empty List" << endl;
    }
    else{
        for(Node *currentPtr = m_startPtr; currentPtr != nullptr; currentPtr = currentPtr->getNextPtr()){
            cout <<"Latitude: " << currentPtr->getLatitude() << "" << endl;
            cout <<"Longitude: " << currentPtr->getLongitude() << "" << endl;
            cout <<"Date: " <<  currentPtr->getMonth() << "/" << currentPtr->getDay() <<"/"<< currentPtr->getYear() << endl;
        }
    }
}

void MyList :: insert(Node *node) {
    Node *prevNode = nullptr;
    Node *currentNode = m_startPtr;
    while ((currentNode != nullptr) && (*currentNode < *node)) {
        prevNode = currentNode;
        currentNode = currentNode->getNextPtr();
    }
    if(prevNode == nullptr){
        node->setNextPtr(currentNode);
        m_startPtr = node;
    }
    else{
        prevNode->setNextPtr(node);
        node->setNextPtr(currentNode);
    }

}
void MyList :: remove(Node node) {
    Node *prevNode = nullptr;
    Node *currentNode = m_startPtr;
    if(empty()) {
        cout << "Empty List" << endl;
    }
    else{
        while ((currentNode != nullptr) && (*currentNode != node)) {
            prevNode = currentNode;
            currentNode = currentNode->getNextPtr();
        }
        if(currentNode == nullptr){
            cout << "Node not found"<< endl;
        }
        else if(prevNode == nullptr){
            m_startPtr = m_startPtr->getNextPtr();
            cout << "deleted Node \n";
            cout <<"Latitude: " <<  currentNode->getLatitude() << "" << endl;
            cout <<"Longitude: " << currentNode->getLongitude() << "" << endl;
            cout <<"Date: " <<  currentNode->getMonth() << "/" << currentNode->getDay() <<"/"<< currentNode->getYear() << endl;
            delete currentNode;
        }
        else{
            prevNode->setNextPtr(currentNode->getNextPtr());
            cout << "deleted Node \n";
            cout <<"Latitude: " << currentNode->getLatitude() << "" << endl;
            cout <<"Longitude: " << currentNode->getLongitude() << "" << endl;
            cout <<"Date: " << currentNode->getMonth() << "/" << currentNode->getDay() <<"/"<< currentNode->getYear() << endl;
            delete currentNode;
        }
    }
}
void MyList :: clear() {
    Node *prevNode = nullptr;
    Node *currentNode = m_startPtr;
    if (empty()) {
        cout << "Empty List" << endl;
    } else {
        while ((currentNode->getNextPtr() != nullptr)) {
            prevNode = currentNode;
            currentNode = currentNode->getNextPtr();
            cout << "deleted Node \n";
            cout <<"Latitude: " << prevNode->getLatitude() << "" << endl;
            cout <<"Longitude: " <<  prevNode->getLongitude() << "" << endl;
            cout <<"Date: " << prevNode->getMonth() << "/" << prevNode->getDay() <<"/"<< prevNode->getYear() << endl;
            delete(prevNode);
        }
        cout << "deleted Node \n";
        cout <<"Latitude: " << currentNode->getLatitude() << "" << endl;
        cout <<"Longitude: " << currentNode->getLongitude() << "" << endl;
        cout <<"Date: " << currentNode->getMonth() << "/" << currentNode->getDay() <<"/"<< currentNode->getYear() << endl;
        delete(currentNode);
        m_startPtr = nullptr;
    }
}

MyList::~MyList() {
    clear();
}

const Node* MyList :: getCurrentNode(){
    return m_currentPtr;
}

void MyList ::advanceToNextNode() {
   if(m_currentPtr->getNextPtr() == nullptr){
       m_currentPtr = nullptr;
   }
   m_currentPtr = m_currentPtr->getNextPtr();
}
void MyList :: resetCurrentPtr() {
    m_currentPtr = m_startPtr;
}