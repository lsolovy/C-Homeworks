/**
 * hw7 implementation
 * @file main.cpp
 * @author Mitchell Hall and Gary E. Christensen
 */

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "MyList.h"

using namespace std;

/**
 * Unit tests to be made by students
 * @return True if all unit tests pass, false if a uni tests fails
 */
bool unitTests() {
    //////////////////////////////////////////////////////////////////////////////////////////////
    /// STUDENT - Add your unit tests here and return true or false if unit tests run properly ///
    //////////////////////////////////////////////////////////////////////////////////////////////
    Node n1(1,1,24,4,2020);
    Node n2(1,1,25,4,2020);
    Node n3(1,1,24,4,2020);
    cout << "Check if n1 < n2. Expected answer is 1. Computed answer is " << (n1 < n2) << endl;
    cout << "Check if n1 == n2. Expected answer is 0. Computed answer is " << (n1 == n2) << endl;
    cout << "Check if n1 > n2. Expected answer is 0. Computed answer is " << (n1 > n2) << endl;
    cout << "Check if n1 >= n2. Expected answer is 0. Computed answer is " << (n1 >= n2) << endl;
    cout << "Check if n1 != n3. Expected answer is 0. Computed answer is " << (n1 != n3) << endl;


    MyList list;
    cout << "Printing empty list.Nothing should print" << endl;
    list.print();
    cout << "After printing and empty list" << endl;
    cout << "\nInserting 4 nodes into a list." << endl;
    Node * node1 = new Node(1,2,8,9,2020);
    Node * node2 = new Node();
    Node * node3 = new Node(3,4,12,12,2021);
    Node * node4 = new Node(5,6,10,10,2022);
    Node * node5 = new Node(8,9,11,11,2023);
    Node * node6 = new Node(1,2,3,4,1999);
    Node * node7 = new Node(8,9,20,11,2024);
    list.insert(node1);
    list.insert(node2);
    list.insert(node3);
    list.insert(node4);
    list.insert(node5);
    //1 1 1 1 2020
    //1 2 8 9 2020
    //3 4 12 12 2021
    //5 6 10 10 2022
    //8 9 11 11 2023
    list.remove(*node2);
    //removing node from beginning
    list.remove(*node5);
    //removing node from end
    list.remove(*node3);
    //removing node from middle
    cout << "REMOVING CASES \nRemoved the beginning, middle, and end node." << endl;
    //1 2 8 9 2020
    //5 6 10 10 2022
    list.print();
    list.insert(node6);
    //inserted node at beginning
    list.insert(node7);
    // insert node at end
    list.insert(node3);
    // insert node at middle
    cout << "\nINSERT CASES \nInserted node at beginning, middle, and end node. The first 3 nodes printed are the nodes being added." << endl;
    //1 2 3 4 1999
    //1 2 8 9 2020
    //3 4 12 12 2021
    //5 6 10 10 2022
    //8 9 11 11 2023
    list.print();
    list.resetCurrentPtr();
    cout <<"\nTesting resetCurrentPtr() & advanceToNextNode() & getCurrentNode()" << endl;
    auto node = list.getCurrentNode();
    cout << node->getMonth() << " " << node->getDay() << " " << node->getYear() << endl;
    list.advanceToNextNode();
    node = list.getCurrentNode();
    cout << node->getMonth() << " " << node->getDay() << " " << node->getYear() << endl;
    list.advanceToNextNode();
    node = list.getCurrentNode();
    cout << node->getMonth() << " " << node->getDay() << " " << node->getYear() << endl;
    list.advanceToNextNode();
    node = list.getCurrentNode();
    cout << node->getMonth() << " " << node->getDay() << " " << node->getYear() << endl;
    list.advanceToNextNode();
    node = list.getCurrentNode();
    cout << node->getMonth() << " " << node->getDay() << " " << node->getYear() << endl;
    list.advanceToNextNode();
    node = list.getCurrentNode();
    cout << ((node == nullptr)) << endl;
    list.~MyList();

    return true;
}

int main() {

    // Change unitTesting to false to enable graphics
    bool unitTesting = false;
    if (unitTesting) {

            unitTests();
            cout << "Turn unit testing off to enable graphics." << endl;

    } else {

        // State enumeration
        enum SimulationState {
            Start, Running, Stop, Done
        };
        SimulationState state = Start;

        // Textures and sprites
        sf::Texture mapTexture;
        if (!mapTexture.loadFromFile("images/map.jpg")) { return EXIT_FAILURE; }
        sf::Sprite mapSprite(mapTexture);

        // Font and text
        sf::Font font;
        if (!font.loadFromFile("fonts/ObliviousFont.ttf")) { return EXIT_FAILURE; }
        sf::Text dateText("", font, 28), infoText("", font, 28);
        infoText.setPosition(5, 500);
        dateText.setPosition(5, 0);
        infoText.setFillColor(sf::Color::Black);
        dateText.setFillColor(sf::Color::Black);

        // Variable declarations
        sf::CircleShape circle(2, 10);
        circle.setOrigin(2, 2);
        circle.setFillColor(sf::Color(0, 0, 255, 100));

        const Node * curNode;
        const Node * dateNode;
        MyList myList;
        string tmpString;
        float longitude, latitude;
        int month, day, year;
        Node *tmpNode;

        // Load Cases
        ifstream fin("data/confirmed_cases.txt");
        if (fin.fail()) {
            cout << "Error: could not open data/confirmed_cases.txt" << endl;
            return EXIT_FAILURE;
        }
        getline(fin, tmpString);        // Get rid of first line
        while (fin.good()) {
            fin >> latitude >> longitude >> month >> day >> year;
            tmpNode = new Node(latitude, longitude, day, month, year);
            myList.insert(tmpNode);
        }
        fin.close();

        // Create window and eventr
        sf::RenderWindow app(sf::VideoMode(1080, 540), "COVID-19");
        app.setFramerateLimit(10);
        sf::Event e{};

        // Window icon
        sf::Image icon;
        if (!icon.loadFromFile("images/icon.png")) { return EXIT_FAILURE; }
        app.setIcon(64, 64, icon.getPixelsPtr());

        // Main application loop
        while (app.isOpen()) {

            // Event handler
            while (app.pollEvent(e)) {
                switch (e.type) {
                    case sf::Event::Closed:
                        app.close();
                        return 0;

                    case sf::Event::KeyPressed:
                        if (e.key.code == sf::Keyboard::Space) {
                            if (state == Running) {
                                state = Stop;
                                infoText.setString("Pause - Press 'SPACE' to Resume");
                                app.setTitle("COVID-19  |  Paused");
                            } else if (state == Stop) {
                                state = Running;
                                infoText.setString("Play - Press 'SPACE' to Pause");
                                app.setTitle("COVID-19  |  Running");
                            }
                        }
                        if (state == Done && e.key.code == sf::Keyboard::R) {
                            state = Start;
                        }
                        break;

                    case sf::Event::LostFocus:
                        if (state == Running) {
                            state = Stop;
                            infoText.setString("Pause - Press 'SPACE' to Resume");
                            app.setTitle("COVID-19  |  Paused");
                        }
                        break;

                    default:
                        break;
                }
            }

            // State Machine
            switch (state) {
                case Start:
                    myList.resetCurrentPtr();
                    curNode = myList.getCurrentNode(); // set the dateNode to the first day in the file
                    dateNode = curNode;
                    infoText.setString("Play - Press 'SPACE' to Pause");
                    app.setTitle("COVID-19  |  Playing");
                    state = Running;
                    break;

                case Running:
                    app.clear();
                    app.draw(mapSprite);

                    myList.resetCurrentPtr(); // reset currentPtr to start of list
                    curNode = myList.getCurrentNode();
                    while (curNode != nullptr && *curNode <= *dateNode) {        // Draw all cases
                        circle.setPosition(float(curNode->getLongitude() + 180) * 3.0f,
                                           float(540 - ((curNode->getLatitude() + 90) * 3.0f)));
                        app.draw(circle);
                        myList.advanceToNextNode();
                        curNode = myList.getCurrentNode();
                    }

                    if (curNode == nullptr) {        // If end of list
                        state = Done;
                        infoText.setString("Done - Press 'R' to Restart");
                        app.setTitle("COVID-19  |  Done");
                    } else {      // If not end of list
                        dateText.setString(to_string(curNode->getMonth()) + "/" +
                                           to_string(curNode->getDay()) + "/" +
                                           to_string(curNode->getYear()));
                        myList.advanceToNextNode();
                        dateNode = curNode;
                        myList.resetCurrentPtr(); // reset current pointer to start of list
                    }
                    app.draw(dateText);
                    app.draw(infoText);
                    app.display();
                    break;

                case Stop:
                    app.clear();
                    app.draw(mapSprite);

                    myList.resetCurrentPtr();
                    curNode = myList.getCurrentNode();
                    while (curNode != nullptr && *curNode <= *dateNode) {        // Draw all cases
                        circle.setPosition(float(curNode->getLongitude() + 180) * 3.0f,
                                           float(540 - ((curNode->getLatitude() + 90) * 3.0f)));
                        app.draw(circle);
                        myList.advanceToNextNode();
                        curNode = myList.getCurrentNode();
                    }
                    app.draw(dateText);
                    app.draw(infoText);
                    app.display();
                    break;

                default:
                    break;
            }
        }
    }

    return 0;
}
