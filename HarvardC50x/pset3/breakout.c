//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
void DisplayFinalMessage(GWindow window, string condition);
void initBallVelocity(double velocity[2]);

int main(void)
{
    // stores object returned by collision detection
    GObject collidedObj;

    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
    
    // set ball's initial velocity
    double velocity[2];
    initBallVelocity(velocity);
 
    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
    
    // set effect of paddle on horizontal ball velocity
    double paddleEffect = 0.0006; 

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    waitForClick();
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        //Check for mouse movement
        GEvent event = getNextEvent(MOUSE_EVENT);
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - getWidth(paddle) / 2;
                double y = getY(paddle);
                if (x<0)
                {
                    x = 0;
                }
                else if (x>getWidth(window)-getWidth(paddle))
                {
                    x = getWidth(window)-getWidth(paddle);
                }
                setLocation(paddle, x, y);
            }
        }
        
        //Move the ball
        move(ball,velocity[0],velocity[1]);
        
        //Check for ball collisions and update velocity
        //  bouncing against wall:
        if (getX(ball)<=0)
        {
            velocity[0] = -velocity[0];   
        }
        if (getX(ball)+getWidth(ball)>=getWidth(window))
        {
            velocity[0] = -velocity[0];
        }
        if (getY(ball)<=0)
        {
            velocity[1] = -velocity[1];
        }
        if (getY(ball)+getHeight(ball)>=getHeight(window))
        {
            lives--;
            if(lives==0)
            {   
                DisplayFinalMessage(window,"lose");
                break;
            }
            else
            {
                setLocation(ball,(getWidth(window)-getWidth(ball))/2,(getHeight(window)-getHeight(ball))/2);   
                initBallVelocity(velocity);
                waitForClick();
            }
        }
        //  check for other collisions:
        collidedObj = detectCollision(window,ball);
        if (collidedObj != NULL)
        {
            if (collidedObj == paddle)
            {
                velocity[1]=-velocity[1];  
                
                double tempPaddleX,tempBallX,paddleDVx;       
                tempPaddleX = getX(paddle)+(getWidth(paddle)/2);
                tempBallX = getX(ball)+(getWidth(ball)/2);
                paddleDVx = paddleEffect*(tempBallX-tempPaddleX);
                velocity[0] = velocity[0] + paddleDVx;
            }
            else if (strcmp(getType(collidedObj),"GRect")==0)
            {
                points++;
                updateScoreboard(window,label,points);
                removeGWindow(window,collidedObj);
                velocity[1] = -velocity[1];
                if(points==ROWS*COLS)
                {
                    DisplayFinalMessage(window,"win");
                    break;
                }
            }
            collidedObj = NULL;
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    double windowWidth = getWidth(window);
    double windowHeight = getHeight(window);
    
    // Create ROWS x COLS number of bricks in a grid
    double brickSpacing = windowWidth/100;
    double brickWidth = ((windowWidth-brickSpacing)/COLS) - brickSpacing;
    double brickHeight = getHeight(window)/55;
    GRect brickArray[ROWS][COLS];
    double brickXPos, brickYPos;
    
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
        {
            brickXPos = ((j+1)*brickSpacing) + (j*brickWidth);
            brickYPos = (0.7/10.0)*windowHeight + (i*(brickHeight+brickSpacing));
            brickArray[i][j] = newGRect(brickXPos,brickYPos,brickWidth,brickHeight);
            setFilled(brickArray[i][j],true);        
            switch(i) 
            {
                case 0:
                    setColor(brickArray[i][j],"RED");
                    break;
                case 1:
                    setColor(brickArray[i][j],"ORANGE");
                    break;
                case 2:
                    setColor(brickArray[i][j],"YELLOW");
                    break;
                case 3:
                    setColor(brickArray[i][j],"GREEN");
                    break;
                case 4:
                    setColor(brickArray[i][j],"CYAN");
                    break;
                case 5:
                    setColor(brickArray[i][j],"BLUE");
                    break;
                case 6:
                    setColor(brickArray[i][j],"PINK");
                    break;
            }
            add(window,brickArray[i][j]);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    double windowWidth = getWidth(window);
    double windowHeight = getHeight(window);
    
    double ballWidth = windowWidth/20;
    double ballHeight = ballWidth;
    double ballXPos = (windowWidth-ballWidth)/2;
    double ballYPos = (windowHeight-ballHeight)/2;
    
    GOval ball = newGOval(ballXPos,ballYPos,ballWidth,ballHeight);
    setFilled(ball,true);
    setColor(ball,"BLACK");
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    double windowWidth = getWidth(window);
    double windowHeight = getHeight(window);

    double paddleWidth = windowWidth/6;
    double paddleHeight = windowHeight/50;     
    double paddleXPos = (windowWidth - paddleWidth)/2;
    double paddleYPos = ((8.5/10.0)*windowHeight) - paddleHeight/2;
    
    GRect paddle = newGRect(paddleXPos,paddleYPos,paddleWidth,paddleHeight);
    setFilled(paddle, true);
    setColor(paddle,"BLACK");
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    double windowWidth = getWidth(window);
    double windowHeight = getHeight(window);

    GLabel label = newGLabel("0");
    setFont(label,"SansSerif-48");
    setColor(label,"GRAY");

    double labelXPos = (windowWidth - getWidth(label))/2;
    double labelYPos = ((9.0/10)*windowHeight - getHeight(label))/2;

    setLocation(label, labelXPos, labelYPos);
    add(window,label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = ((9.0/10)*getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}

/**
 * Displays final message to player, where condition 
 * is either "win" or "lose".
 */
void DisplayFinalMessage(GWindow window, string condition)
{
    char mess[12];
    double windowWidth = getWidth(window);
    double windowHeight = getHeight(window);
    
    GLabel finalMess = newGLabel("");
    setFont(finalMess,"SansSerif-36");
    setColor(finalMess,"BLACK");

    if(strcmp(condition,"win")==0)
    {
        sprintf(mess, "You Win!");
        setLabel(finalMess,mess);
    }
    
    else if(strcmp(condition,"lose")==0)
    {
        sprintf(mess, "You Lose!");
        setLabel(finalMess,mess);
    }
    
    double finalMessXPos = (windowWidth - getWidth(finalMess))/2;
    double finalMessYPos = ((6.5/10)*windowHeight - getHeight(finalMess))/2;
    setLocation(finalMess, finalMessXPos, finalMessYPos);
    add(window,finalMess);
    return;
}

/**
 * Initializes ball velocity with magnitude initVel and in 
 * a random direction.  The variable relHorizVel determines
 * how "downward" the initial velocity will be - do not want
 * to give ball an initial velocity in x-direction. Called
 * at beginning of game and every time a life is lost. 
 */
void initBallVelocity(double velocity[2])
{
    double initVel = 0.03;
    double relHorizVel = 0.9*initVel;
    velocity[0] = (relHorizVel*drand48())-(relHorizVel/2);
    velocity[1] = sqrt((initVel*initVel)-(velocity[0]*velocity[0]));
}
