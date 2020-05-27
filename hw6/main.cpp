/* Reasons extra credit should be given
 * Added a welcome screen with instructions
 * Will display the score of the player
 * Will display the amount of lifes the player has
 * Added a gameover screen that will prompt the user (also will display the score)
 * Added a characteristic that when you score gets higher the background will change colors
 * Added a characteristic that will allow the user to shoot blue or red bullets
 * IMPORTANT NOTE ---- To shoot in the game use either A or S NOT the spacebar
 * refractored code to have proper indentation
 */
//Gameplay by Geronimo Fonts, https://www.1001freefonts.com/, License: Free for personal use.
//Icons made by <a href="https://www.flaticon.com/authors/freepik" title="Freepik">Freepik</a> from <a href="https://www.flaticon.com/" title="Flaticon"> www.flaticon.com</a>, Free for personal and commercial purpose with attribution.
//Video Game Retro Arcade Space Invade Pac Man Classic 80s Vintage 8 bit Atar Ninten Jump by SCICOFILMS.com, https://www.1001freefonts.com/, License: Free for personal use.
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <cmath>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>


using namespace sf;
using namespace std;
//Height and Width of window
const int W = 1200;
const int H = 800;
//degrees to radians
float DEGTORAD = 0.017453f;

class Animation {
public:
    float Frame, speed;
    Sprite sprite;
    std::vector<IntRect> frames;

    Animation() {}
    // constructor for the animation class
    Animation(Texture &t, int x, int y, int w, int h, int count, float Speed) {
        Frame = 0;
        speed = Speed;

        for (int i = 0; i < count; i++) {
            frames.push_back(IntRect(x + i * w, y, w, h));
        }

        sprite.setTexture(t);
        sprite.setOrigin(w / 2, h / 2);
        sprite.setTextureRect(frames[0]);
    }


    // sprite animation
    // will update which frame should be pick
    // will pick the correct picture that needs to be printed to the screen
    void update() {
        Frame += speed;
        int n = frames.size();
        if (Frame >= n) { Frame -= n; }
        if (n > 0) { sprite.setTextureRect(frames[int(Frame)]); }
    }

    bool isEnd() {
        return Frame + speed >= frames.size();
    }

};


class Entity {
public:
    float x, y, dx, dy, R, angle;
    bool life;
    std::string name;
    Animation anim;

    Entity() {
        life = 1;
    }

    void settings(Animation &a, int X, int Y, float Angle = 0, int radius = 1) {
        anim = a;
        x = X;
        y = Y;
        angle = Angle;
        R = radius;
    }

    virtual void update() {};
    // will get the postion of each sprite
    // can but is commented out that it will draw a circle around each sprite
    void draw(RenderWindow &app) {
        anim.sprite.setPosition(x, y);
        anim.sprite.setRotation(angle + 90);
        app.draw(anim.sprite);

        CircleShape circle(R);
        circle.setFillColor(Color(255, 0, 0, 170));
        circle.setPosition(x, y);
        circle.setOrigin(R, R);
        //app.draw(circle);
    }

    virtual ~Entity() {};
};


class asteroid : public Entity {
public:

    asteroid() {
        dx = rand() % 8 - 4;
        dy = rand() % 8 - 4;
        name = "asteroid";
        asteroidcount++;
    }
    // will kept track of how many asteroids are on the screen
    static int getCount(){return asteroidcount;}

    void update() {
        x += dx;
        y += dy;
        // makes sure that if the asteroid goes off the screen will come back around
        if (x > W) { x = 0; }
        if (x < 0) { x = W; }
        if (y > H) { y = 0; }
        if (y < 0) { y = H; }

    }
    ~asteroid(){
        asteroidcount--;
    }
private:
    static int asteroidcount;
};
int asteroid::asteroidcount{0};

class bullet : public Entity {
public:
    bullet() {
        name = "bullet";
    }
    // will update the bullet
    // if the bullet goes off the screen it will remove the bullet
    void update() {
        dx = cos(angle * DEGTORAD) * 6;
        dy = sin(angle * DEGTORAD) * 6;
        // angle+=rand()%6-3;
        x += dx;
        y += dy;

        if (x > W || x < 0 || y > H || y < 0) { life = 0; }
    }

};


class player : public Entity {
public:
    bool thrust;

    player() {
        name = "player";
    }

    void update() {
        // if the spaceship is in thrust will increase the speed by 0.2
        // the longer the hold on thrust the faster it will go
        if (thrust) {
            dx += cos(angle * DEGTORAD) * 0.2;
            dy += sin(angle * DEGTORAD) * 0.2;
        }
        // if thrust is false will slow down the spaceship by 1%
        else {
            dx *= 0.99;
            dy *= 0.99;
        }
        // maxes out the speed of the spaceship
        int maxSpeed = 15;
        float speed = sqrt(dx * dx + dy * dy);
        if (speed > maxSpeed) {
            dx *= maxSpeed / speed;
            dy *= maxSpeed / speed;
        }

        x += dx;
        y += dy;
        // makes sure that is the spaceship goes off the screen will come back around
        if (x > W) { x = 0; }
        if (x < 0) { x = W; }
        if (y > H) { y = 0; }
        if (y < 0) { y = H; }
    }

};

class UFO: public Entity{
public:
    UFO(){

        dx = 5;
        name = "UFO";


    }
    void update(){
        x += dx;
        // makes sure that is the UFO goes off the screen will come back around
        if (x > W) { x = 0; }
        if (x < 0) { x = W; }
        if (y > H) { y = 0; }
        if (y < 0) { y = H; }

    }

};


// will check to see if the entities are in collision
bool isCollide(Entity *a, Entity *b) {
    return (b->x - a->x) * (b->x - a->x) +
           (b->y - a->y) * (b->y - a->y) <
           (a->R + b->R) * (a->R + b->R);
}


int main() {
    int ufocount = 0;
    int score = 0;
    int lifes = 3;

    srand(time(0));

    RenderWindow app(VideoMode(W, H), "Asteroids!");
    app.setFramerateLimit(60);


    // will load all the essential files needed
    Texture t1, t2, t3, t4, t5, t6, t7, t8,t9,t10,t11;
    t1.loadFromFile("images/spaceship.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/explosions/type_C.png");
    t4.loadFromFile("images/rock.png");
    t5.loadFromFile("images/fire_red.png");
    t6.loadFromFile("images/rock_small.png");
    t7.loadFromFile("images/explosions/type_B.png");
    t10.loadFromFile("images/background2.jpg");
    t11.loadFromFile("images/background3.jpg");
    if(!t8.loadFromFile("images/ufo.png")){
        return EXIT_FAILURE;
    }
    t9.loadFromFile("images/fire_blue.png");
    t1.setSmooth(true);
    t2.setSmooth(true);
    t8.setSmooth(true);
    t10.setSmooth(true);
    Sprite background(t2);
    Sprite background2(t10);
    Sprite background3(t11);

    SoundBuffer buffer;
    if (!buffer.loadFromFile("../sounds/UFO.ogg")) {
        return EXIT_FAILURE;
    }
    Sound sound;
    sound.setBuffer(buffer);

    Font font;
    if (!font.loadFromFile("../fonts/Gameplay.ttf")) {
        return EXIT_FAILURE;
    }
    Text text;
    text.setFont(font);
    Text text2;
    text2.setFont(font);
    Text welcometext;
    welcometext.setFont(font);
    Text welcometext2;
    welcometext2.setFont(font);
    Text Endtext;
    Endtext.setFont(font);
    Text Endtext2;
    Endtext2.setFont(font);




    Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5);
    Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
    Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);
    Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
    Animation s2Bullet(t9, 0, 0, 32, 64, 16, 0.8);
    Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
    Animation sPlayer_go(t1, 40, 40, 40, 40, 1, 0);
    Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);
    Animation sUFO(t8,0,0,64,64,1,0.2);
    // list of entity pointers - will determine what gets printed to the screen
    std::list<Entity *> entities;

    // 15 asteroids, will give an asteroid a pointer
    // will set where the new asteroids are and size
    for (int i = 0; i < 15; i++) {
        asteroid *a = new asteroid();
        a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
        a->getCount();
        entities.push_back(a);
    }
    // will set the spaceship to the starting positon
    player *p = new player();
    p->settings(sPlayer, 200, 200, 0, 20);
    entities.push_back(p);

    //start of state machine
    enum GameState{
        Welcome_State, Play_State, End_State
    };
    GameState Game;
    Game = Welcome_State;

    /////main loop/////
    while (app.isOpen()) {
        if(Game == Welcome_State){
            Event e;
            while (app.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    app.close();
                }
                // if S is pressed on the keyboard the state will change to Play state
                if (e.type == Event::KeyPressed) {
                    if (e.key.code == Keyboard::Space) {
                        Game = Play_State;
                    }
                }

            }
            ////draw for welcome screen/////
            welcometext.setString("Welcome to Asteroids!");
            welcometext.setCharacterSize(40);
            welcometext.setFillColor(sf::Color::Red);
            welcometext.setPosition(300, 0);
            welcometext2.setString("Instructions:\n\nTo move around use the arrow keys.\n\nTo shoot red bullets use the S key.\n\nTo shoot blue bullets use the A key.\n\nWatch out for the asteroids. \n\nWatch out for the UFO.\n\n Press the space bar to start. \n\n                            Good luck!");
            welcometext2.setCharacterSize(22);
            welcometext2.setFillColor(sf::Color::Yellow);
            welcometext2.setPosition(300, 100);
            app.draw(background);
            app.draw(welcometext);
            app.draw(welcometext2);
            app.display();
        }
        else if (Game == Play_State){
            Event event;
            while (app.pollEvent(event)) {
                    if (event.type == Event::Closed) {
                        app.close();
                    }
                // if the s is pressed will fire red a bullet
                // if the a is pressed will fire blue a bullet
                // will set the new bullets angle
                // will put it on the entites list to be draw
                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::S) {
                        bullet *b = new bullet();
                        b->settings(sBullet, p->x, p->y, p->angle, 10);
                        entities.push_back(b);
                    }
                    if(event.key.code == Keyboard:: A){
                        bullet *b = new bullet();
                        b->settings(s2Bullet, p->x, p->y, p->angle, 10);
                        entities.push_back(b);
                    }
                }
            }
            // if the left or right arrow is pressed will can the angle of the spaceship
            // if the up arrow is presses will thrust the spaceship forward
            // if the up arrow is not pressed the spaceship is stationary
            if (Keyboard::isKeyPressed(Keyboard::Right)) { p->angle += 3; }
            if (Keyboard::isKeyPressed(Keyboard::Left)) { p->angle -= 3; }
            if (Keyboard::isKeyPressed(Keyboard::Up)) { p->thrust = true; }
            else { p->thrust = false; }

            // will run throught both entities A and B
            // will check to see if the bullet hits the asteroid
            // if they do collide, then they are both destroyed with an explosion
            // score increases by 1
            for (auto a:entities) {
                for (auto b:entities) {
                    if (a->name == "asteroid" && b->name == "bullet") {
                        if (isCollide(a, b)) {
                            a->life = false;
                            b->life = false;
                            score ++;
                            Entity *e = new Entity();
                            e->settings(sExplosion, a->x, a->y);
                            e->name = "explosion";
                            entities.push_back(e);




                            // if its a bigger asteroid then wil create 2 smaller asteroids
                            for (int i = 0; i < 2; i++) {
                                if (a->R == 15) { continue; }
                                Entity *e = new asteroid();
                                e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
                                entities.push_back(e);
                            }

                        }
                    }
                    // will run throught both entities A and B
                    // will check to see if the player hits the asteroid
                    // if they do collide, then they are both destroyed with an explosion
                    // number of lifes also decreases by 1
                    // will set the spaceship to the middle of the screen
                    if (a->name == "player" && b->name == "asteroid") {
                        if (isCollide(a, b)) {
                            b->life = false;
                            lifes--;

                            Entity *e = new Entity();
                            e->settings(sExplosion_ship, a->x, a->y);
                            e->name = "explosion";
                            entities.push_back(e);

                            p->settings(sPlayer, W / 2, H / 2, 0, 20);
                            p->dx = 0;
                            p->dy = 0;
                        }
                    }
                    // will run throught both entities A and B
                    // will check to see if the UFO hits a bullet
                    // if they do collide, then they are both destroyed with an explosion
                    // will increment the score by 10 points
                    // will end the sound of the UFO when destroyed
                    if(a->name == "UFO" && b->name == "bullet"){
                        if(isCollide(a,b)){
                            b->life = false;
                            a->life = false;
                            score = score + 10;
                            Entity *e = new Entity();
                            e->settings(sExplosion, a->x, a->y);
                            e->name = "explosion";
                            entities.push_back(e);
                            sound.setLoop(false);

                        }
                    }
                    // will run throught both entities A and B
                    // will check to see if the UFO hits the player
                    // if they do collide, then they are both destroyed with an explosion
                    // lifes decrease by 1
                    // sound of the UFO will stop
                    // will set the spaceship to the middle of the screen
                    if(a->name == "UFO" && b->name == "player"){
                        if(isCollide(a,b)){

                            a->life = false;
                            lifes--;
                            Entity *e = new Entity();
                            e->settings(sExplosion, a->x, a->y);
                            e->name = "explosion";
                            entities.push_back(e);
                            sound.stop();



                            p->settings(sPlayer, W / 2, H / 2, 0, 20);
                            p->dx = 0;
                            p->dy = 0;
                            p->life = 1;

                        }
                    }
                }
            }

            if (p->thrust) { p->anim = sPlayer_go; }
            else { p->anim = sPlayer; }


            for (auto e:entities) {
                if (e->name == "explosion") {
                    if (e->anim.isEnd()) { e->life = 0; }
                }
            }
            //will get the count of asteroids
            // if the count is 0 then it will generate 15 more to the screen
            // postions are random
            if(asteroid::getCount() == 0 ){
                for (int i = 0; i < 15; i++) {
                    asteroid *a = new asteroid();
                    a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
                    a->getCount();
                    entities.push_back(a);
                }
            }
            //PART 3 (comment out this block of code)
            /*if (rand() % 150 == 0) {
                asteroid *a = new asteroid();
                a->settings(sRock, 0, rand() % H, rand() % 360, 25);
                entities.push_back(a);
            }*/

            // will spawn in the UFO
            // will play the sound when the UFO is on the screen
            // will have the UFO spawn in at a random Y
            // will increment the ufocount by 1
            if(ufocount == 0){
                if (rand() % 150== 0) {
                    UFO *u = new UFO();
                    sound.setVolume(25.f);
                    sound.play();
                    sound.setLoop(true);
                    u->settings(sUFO, 0, rand() % H , 270, 20);
                    entities.push_back(u);
                    ufocount += 1;

                }
            }
            // if the lifes are 0 will bring the user to the gameover screen
            if(lifes == 0){
                Game = End_State;
                sound.stop();
            }

            // will loop through the entities from beggining to end
            // will update the object and animation
            for (auto i = entities.begin(); i != entities.end();) {
                Entity *e = *i;

                e->update();
                e->anim.update();
                // will check to see if the entity is alive
                // if false will erase the entity from the list
                if (e->life == false) {
                    if(e->name == "UFO"){
                        ufocount--;
                    }
                    i = entities.erase(i);
                    delete e;
                } else { i++; }
            }



            //////draw//////
            // depending on the score the background will be a different color
            // only did it up to when the score is 80
            // will change three times
            //will draw the number of lifes to the screen
            //will draw the score to the screen
            if(score < 40){
                app.draw(background);
            }

            if(score > 40){
                app.draw(background2);
            }
            if(score > 80){
                app.draw(background3);
            }
            text.setString("Lifes: " + to_string(lifes));
            text.setCharacterSize(22);
            text.setFillColor(sf::Color::Red);
            text.setPosition(1050, 15);
            text2.setString("Score: " + to_string(score));
            text2.setCharacterSize(22);
            text2.setFillColor(sf::Color::Red);
            text2.setPosition(1050, 40);
            app.draw(text);
            app.draw(text2);
            for (auto i:entities) {
                i->draw(app);
            }
            app.display();
        }
        // if in END STATE
        else{
            Event e;
            while (app.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    app.close();
                }
                // if Q is pressed will exit the game
                if (e.type == Event::KeyPressed) {
                    if (e.key.code == Keyboard::Q) {
                        app.close();
                    }
                }
                // if R is pressed will restart the game from the play state
                // will put the score and lifes back to original state
                if (e.type == Event::KeyPressed) {
                    if (e.key.code == Keyboard::R) {
                        Game = Play_State;
                        score = 0;
                        lifes = 3;
                    }
                }
            }
            /////draw for the gameover screen//////
            // will insctruct the user what to do next
            // will but the score to screen
            Endtext.setString("GAME OVER");
            Endtext.setCharacterSize(80);
            Endtext.setFillColor(sf::Color::Red);
            Endtext.setPosition(325, 300);
            Endtext2.setString("Score = " + to_string(score) + "\nTo restart press r.\n To quit press q.");
            Endtext2.setCharacterSize(22);
            Endtext2.setFillColor(sf::Color::Red);
            Endtext2.setPosition(450, 400);
            app.draw(background);
            app.draw(Endtext);
            app.draw(Endtext2);
            app.display();
        }

    }

    return 0;
}
