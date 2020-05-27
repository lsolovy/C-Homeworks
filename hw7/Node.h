//
// Created by solov on 4/28/2020.
//

#ifndef COVID_19_NODE_H
#define COVID_19_NODE_H

class Node{
public:
    explicit Node(float latitude = 1,float longitude = 1, int day = 1, int month = 1, int year = 2020,Node *nextPtr = nullptr);
    float getLatitude() const;
    void setLatitude(float latitude);
    float getLongitude() const;
    void setLongitude(float longitude);
    int getDay() const;
    void setDay(int day);
    int getMonth() const;
    void setMonth(int month);
    int getYear() const;
    void setYear(int year);
    Node *getNextPtr() const;
    void setNextPtr(Node *nextPtr);


    bool operator<(const Node &rhs) const;
    bool operator>(const Node &rhs) const;
    bool operator<=(const Node &rhs) const;
    bool operator>=(const Node &rhs) const;
    bool operator==(const Node &rhs) const;
    bool operator!=(const Node &rhs) const;


private:
    float m_latitude;
    float m_longitude;
    int m_day;
    int m_month;
    int m_year;
    Node *m_nextPtr;

};

#endif //COVID_19_NODE_H
