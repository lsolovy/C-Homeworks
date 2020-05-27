/* Name: Louis Solovy
 * Date: 4/1/2020
 * Program name: Bejeweled
 * Description: A rough version of Bejeweled. The objective is to get the highest score in the amount of time given.
   There is a welcome screen, and only one level. The program uses a state machine to switch between the two states of
   the game. All copyright material is given credit right below this.
 * Gameplay by Geronimo Fonts, https://www.1001freefonts.com/, License: Free for personal use.
 * gem_ping.wav by high_festiva,https://freesound.org/, License: Creative Commons 0
 * blue-and-purple-cosmic-sky-956999 by Felix Mittermeier,https://pexels.com/, License: Free for personal use */
#include <SFML/Graphics.hpp>
#include <time.h>
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;
using namespace std;

int ts = 54; //tile size
Vector2i offset(48,24); // offest of the grid in picture from top left corner of window

class Piece{
public:
    //match - 0 - set to one if three in a row
    //alpha = 255 - transparency of piece/gem. 255 opaque and 0 transparent
    Piece(int x = 0, int y = 0, int col = 0, int row = 0, int kind = 0, int match = 0, int alpha = 255){
        setX(x);
        setY(y);
        setAlpha(alpha);
        setMatch(match);
        setKind(kind);
        setCol(col);
        setRow(row);

    };

    static void swap(Piece p1,Piece p2);

    int getX() const {
        return x;
    }

    void setX(int x) {
        Piece::x = x;
    }

    int getY() const {
        return y;
    }

    void setY(int y) {
        Piece::y = y;
    }

    int getCol() const {
        return col;
    }

    void setCol(int col) {
        Piece::col = col;
    }

    int getRow() const {
        return row;
    }

    void setRow(int row) {
        Piece::row = row;
    }

    int getKind() const {
        return kind;
    }

    void setKind(int kind) {
        Piece::kind = kind;
    }

    int getMatch() const {
        return match;
    }

    void setMatch(int match) {
        Piece::match = match;
    }

    int getAlpha() const {
        return alpha;
    }

    void setAlpha(int alpha) {
        Piece::alpha = alpha;
    }

private:
    int x;
    int y;
    int col;
    int row;
    int kind;
    int match;
    int alpha;
};
Piece grid[10][10];

 void Piece::swap(Piece p1,Piece p2){

    int temp = p1.getCol();
    p1.setCol(p2.getCol());
    p2.setCol(temp);

    temp = p1.getRow();
    p1.setRow(p2.getRow());
    p2.setRow(temp);

    grid[p1.getRow()][p1.getCol()]=p1;
    grid[p2.getRow()][p2.getCol()]=p2;
}



int main() {

    int ScoretoScreen = 0;
    srand(time(0));

    RenderWindow app(VideoMode(740, 480), "Match-3 Game!");
    app.setFramerateLimit(60);



    // return -1 if the font does not open
    Font font;
    if (!font.loadFromFile("../fonts/Gameplay.ttf")) {
        return EXIT_FAILURE;
    }
    // sets all the text to the font
    Text text;
    text.setFont(font);
    Text timertext;
    timertext.setFont(font);
    Text gameovertext;
    gameovertext.setFont(font);
    Text quitgame;
    quitgame.setFont(font);
    Text welcometext;
    welcometext.setFont(font);
    Text welcometext2;
    welcometext2.setFont(font);

    //return -1 if the sound does not open
    SoundBuffer buffer;
    if (!buffer.loadFromFile("../sounds/gemsound.ogg")) {
        return EXIT_FAILURE;
    }
    Sound sound;
    sound.setBuffer(buffer);

    //return -1 if the background for the welcome screen does not open
    Texture t3;
    if (!t3.loadFromFile("../images/welcome.jpg")) {
        return EXIT_FAILURE;
    }
    Sprite start(t3);
    t3.setSmooth(true);
    Texture t1, t2;

    // return -1 if the background does not open
    if (!t1.loadFromFile("images/background.png")) {
        return EXIT_FAILURE;
    }
    // return -1 if the gems does not open
    if (!t2.loadFromFile("images/gems.png")) {
        return EXIT_FAILURE;
    }

    Sprite background(t1), gems(t2);
    t2.setSmooth(true);
    //intinalizes the grid
    //kind variable is set to random (0,1,2)
    // x and y are set to default spot (left corner)
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            grid[i][j].setKind(rand() % 3);
            grid[i][j].setCol(j);
            grid[i][j].setRow(i);
            grid[i][j].setX(j * ts);
            grid[i][j].setY(i * ts);
        }
    }


    int x0, y0, x, y;
    int click = 0;
    Vector2i pos;
    bool isSwap = false, isMoving = false;
    int notBeginnning = 0;


    int countdown = 1000;
    string gameover;
    string quit;

    // beginning to the state machine
    // has two states, one for the welcome screen and the other for the playing state
    //intializes the state to welcome state
    enum GameState {
        Welcome_state, Play_state
    };
    GameState Game;
    Game = Welcome_state;


    while (app.isOpen()) {
        if (Game == Welcome_state) {
            Event e;
            while (app.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    app.close();
                }
                // if S is pressed on the keyboard the state will change to Play state
                if (e.type == Event::KeyPressed) {
                    if (e.key.code == Keyboard::S) {
                        Game = Play_state;
                    }
                }

            }
            //////draw///////
            // will draw the welcome text to the screen
            // will draw the welcome background to the screen
            welcometext.setString("Welcome to Bejeweled!");
            welcometext.setCharacterSize(22);
            welcometext.setFillColor(sf::Color::White);
            welcometext.setPosition(210, 120);
            welcometext2.setString("To start the game press S");
            welcometext2.setCharacterSize(22);
            welcometext2.setFillColor(sf::Color::White);
            welcometext2.setPosition(180, 200);
            app.draw(start);
            app.draw(welcometext);
            app.draw(welcometext2);
            app.display();


        } else if (Game == Play_state) {
            // if the timer is not 0 it will countdown
            if (countdown > 0) {
                countdown--;
            }
            // if the timer is 0 it will prompt the user to restart to quit
            // will set the gamover string to say game over
            if (countdown == 0) {
                gameover = "Game Over";
                quit = "Press R to restart \nPress Q to Quit";
            }
            notBeginnning++;
            Event e;
            while (app.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    app.close();
                }
                if (e.type == Event::MouseButtonPressed) {
                    if (e.key.code == Mouse::Left) {
                        if (!isSwap && !isMoving) {
                            click++;

                        }
                        pos = Mouse::getPosition(app) - offset;
                    }
                }
                // if R is pressed it will reset the game to original state
                if (e.type == Event::KeyPressed) {
                    if (e.key.code == Keyboard::R) {
                        countdown = 1000;
                        ScoretoScreen = 0;
                        gameover = "";
                        quit = "";
                    }
                }
                // if Q is pressed it will close the window
                if (e.type == Event::KeyPressed) {
                    if (e.key.code == Keyboard::Q) {
                        app.close();
                    }
                }
            }






            // mouse click
            // sets the index of the row and column of the second click
            if (click == 1) {
                x0 = pos.x / ts + 1;
                y0 = pos.y / ts + 1;
            }
            //will make sure that its a valid swap (one apart)
            //and then it will swap if valid swap
            //if its a valid swap will reset clicks to 0, if not will keep the first click
            if (click == 2) {
                x = pos.x / ts + 1;
                y = pos.y / ts + 1;
                if (abs(x - x0) + abs(y - y0) == 1) {
                    Piece::swap(grid[y0][x0], grid[y][x]);
                    isSwap = 1;
                    click = 0;
                } else {
                    click = 1;
                }
            }


            //Match finding
            // will see if there are three gems in a row (same kind) in grind (8x8)
            for (int i = 1; i <= 8; i++) {
                for (int j = 1; j <= 8; j++) {
                    // will see if the each gem in the middle is sandwhiched by the same kind gem (horizontal)
                    if (grid[i][j].getKind() == grid[i + 1][j].getKind()) {
                        if (grid[i][j].getKind() == grid[i - 1][j].getKind()) {
                            for (int n = -1; n <= 1; n++) {
                                grid[i + n][j].setMatch(grid[i + n][j].getMatch() + 1);
                            }
                        }

                    }

                    // will see if the each gem in the middle is sandwhiched by the same kind gem (vertical)
                    if (grid[i][j].getKind() == grid[i][j + 1].getKind()) {
                        if (grid[i][j].getKind() == grid[i][j - 1].getKind()) {
                            for (int n = -1; n <= 1; n++) {
                                grid[i][j + n].setMatch(grid[i + n][j].getMatch() + 1);

                            }
                        }

                    }

                }
            }


            //Moving animation
            //gems move 1 pixel at a time for n
            //isMoving will be true until it stops moving
            //dx is horizontal. dy is vertical
            isMoving = false;
            for (int i = 1; i <= 8; i++) {
                for (int j = 1; j <= 8; j++) {
                    Piece &p = grid[i][j];
                    int dx, dy;
                    for (int n = 0; n < 6; n++) { // 4 - speed
                        dx = p.getX() - p.getCol() * ts;
                        dy = p.getY() - p.getRow() * ts;
                        if (dx) {
                            p.setX(p.getX() - dx / abs(dx));
                        }
                        if (dy) {
                            p.setY(p.getY() - dy / abs(dy));
                        }

                    }
                    if (dx || dy) {
                        isMoving = 1;
                    }


                }
            }

            //Deleting amimation
            //if gems aren't moving alpha will be set to the color
            //if the gems match and alpha > 10 will set isMoving to true
            if (!isMoving) {
                for (int i = 1; i <= 8; i++) {
                    for (int j = 1; j <= 8; j++) {
                        if (grid[i][j].getMatch()) {
                            if (grid[i][j].getAlpha() > 10) {
                                grid[i][j].setAlpha(grid[i][j].getAlpha() - 10);
                                isMoving = true;
                            }
                        }
                    }


                }


            }

            //Get score
            //will save the score of matches
            int score = 0;
            for (int i = 1; i <= 8; i++) {
                for (int j = 1; j <= 8; j++) {
                    score += grid[i][j].getMatch();


                }
            }


            //Second swap if no match
            //if the gems aren't moving and a swap was done it will swap back cause no match
            if (isSwap && !isMoving) {
                if (!score) {
                    Piece::swap(grid[y0][x0], grid[y][x]);

                }
                isSwap = 0;
            }




            //Update grid
            //will check to see if there is a match
            //will swap to check and will unswap if there is no match
            // break is for only executing swap once
            if (!isMoving) {
                for (int i = 8; i > 0; i--) {
                    for (int j = 1; j <= 8; j++) {
                        if (grid[i][j].getMatch()) {
                            sound.setVolume(50.f);
                            sound.play();
                            for (int n = i; n > 0; n--) {
                                if (!grid[n][j].getMatch()) {
                                    Piece::swap(grid[n][j], grid[i][j]);
                                    break;
                                }
                            }

                        }

                    }


                }
                // will also check to see if there are any new matches when the new gems fall
                // if match will have gems fall from the top
                // if it is a match will set a new gem with the right coordinates
                // will pick a new piece at the top in the same column
                // n is the number of columns with a match in it
                // will make sure that no points get added to the score for the initial drop of gems (tried my best)
                for (int j = 1; j <= 8; j++) {
                    for (int i = 8, n = 0; i > 0; i--) {
                        if (grid[i][j].getMatch()) {
                            if (notBeginnning > 30) {
                                ScoretoScreen = ScoretoScreen + 1;
                            }
                            grid[i][j].setKind(rand() % 7);
                            grid[i][j].setY(-ts * n++);
                            grid[i][j].setMatch(0);
                            grid[i][j].setAlpha(255);
                        }
                    }

                }

            }





            //////draw///////
            // will draw the background to the screen
            // will draw the gems to the screen
            // will draw the score to the screen
            // will draw the timer to the screen
            // will draw the gameover text to the screen
            // will draw the quit text to the screen
            app.draw(background);
            text.setString("Score: " + to_string(ScoretoScreen));
            text.setCharacterSize(22);
            text.setFillColor(sf::Color::Red);
            text.setPosition(500, 250);
            timertext.setString("Time: " + to_string(countdown));
            timertext.setFillColor(sf::Color::Red);
            timertext.setCharacterSize(22);
            timertext.setPosition(500, 275);
            gameovertext.setString(gameover);
            gameovertext.setPosition(100, 150);
            gameovertext.setCharacterSize(75);
            gameovertext.setFillColor(sf::Color::Black);
            quitgame.setString(quit);
            quitgame.setFillColor(sf::Color::Black);
            quitgame.setCharacterSize(18);
            quitgame.setPosition(500, 350);
            app.draw(text);
            app.draw(timertext);
            app.draw(quitgame);
            //will draw everything to the screen on the 10 x 10 grid (row i, column j)
            //will put each piece to the grind and will put a gem to it
            //sets texture of gems to 49x49 picture by p.getKind() (0-6 kinds)
            //then will set a color to the gem and transparency with p.getAlpha
            //the gem will then move down the grid
            for (int i = 1; i <= 8; i++) {
                for (int j = 1; j <= 8; j++) {
                    Piece p = grid[i][j];
                    gems.setTextureRect(IntRect(p.getKind() * 49, 0, 49, 49));
                    gems.setColor(Color(255, 255, 255, p.getAlpha()));
                    gems.setPosition(p.getX(), p.getY());
                    gems.move(offset.x - ts, offset.y - ts);
                    app.draw(gems);

                }
            }
            app.draw(gameovertext);
            app.display();
        }
    }

    return 0;
 }





