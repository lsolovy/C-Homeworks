//
// Created by solov on 4/28/2020.
//

#include "Node.h"


Node::Node(float latitude, float longitude, int day, int month, int year, Node *nextPtr) {
    setDay(day);
    setLatitude(latitude);
    setLongitude(longitude);
    setMonth(month);
    setYear(year);
    setNextPtr(nextPtr);
}

float Node::getLatitude() const {
    return m_latitude;
}

void Node::setLatitude(float latitude) {
    m_latitude = latitude;
}

float Node::getLongitude() const {
    return m_longitude;
}

void Node::setLongitude(float longitude) {
    m_longitude = longitude;
}

int Node::getDay() const {
    return m_day;
}

void Node::setDay(int day) {
    m_day = day;
}

int Node::getMonth() const {
    return m_month;
}

void Node::setMonth(int month) {
    m_month = month;
}

int Node::getYear() const {
    return m_year;
}

void Node::setYear(int year) {
    m_year = year;
}

Node *Node::getNextPtr() const {
    return m_nextPtr;
}

void Node::setNextPtr(Node *nextPtr) {
    m_nextPtr = nextPtr;
}

bool Node::operator==(const Node &rhs) const {
    return m_day == rhs.m_day &&
           m_month == rhs.m_month &&
           m_year == rhs.m_year;
}

bool Node::operator!=(const Node &rhs) const {
    return !(rhs == *this);
}

bool Node::operator < (const Node &rhs) const {
    if(m_year != rhs.m_year) {
        return m_year < rhs.m_year;
    }
    else if(m_month != rhs.m_month){
        return m_month < rhs.m_month;
    }
    return m_day < rhs.m_day;
}
bool Node::operator > (const Node &rhs) const {
    return !((*this < rhs) ||(*this == rhs));
}
bool Node::operator <= (const Node &rhs) const {
    return ((*this < rhs) || (*this == rhs));
}
bool Node::operator >= (const Node &rhs) const {
    return ((*this > rhs) || (*this == rhs));
}