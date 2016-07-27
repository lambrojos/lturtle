/*
 *  Turtle.h
 *
 */

#pragma once

#include "ofMain.h"
#include <vector>


class Turtle {

public:

    Turtle();

	//line drawing config

    float drawLength;

    float lineWidth;
    float lineLength;

    float angle;
    float zAngle;

    float startAngle;
    float startZAngle;

    float growSpeed;

    int colorOffset;
    int alpha;

    int stayfunky;

    //turtle state
    struct turtleState
    {
        float angle;
        float zAngle;
        float x;
        float y;
        float z;

        float r;
        float g;
        float b;
    } curState;


    bool draw(string input, int x, int y, int z);

    void setColor( int _r, int _g, int _b);

    void setLineWidth(int _lineWidth);

private:

    vector<turtleState> savedStates;

    int   branchingLevel;
    int   branchingLevelsCompleted;

    static const char FORWARD = 'F';
    static const char RIGHT = '+';
    static const char LEFT = '-';

    static const char Z_RIGHT = '>';
    static const char Z_LEFT = '<';

    static const char BRANCH_START = '[';
    static const char BRANCH_STOP = ']';

    static const char MORE_BLUE = 'b';
    static const char LESS_BLUE = 'y';

    static const char MORE_RED = 'r';
    static const char LESS_RED = 'c';

    static const char MORE_GREEN = 'g';
    static const char LESS_GREEN = 'm';

    void moveForward();
};
