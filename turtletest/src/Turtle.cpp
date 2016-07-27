/*
created By Giovanni Lela
giovanni.lela@gmail.com

 This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#define THINNER_BRANCHES true

#include "Turtle.h"

Turtle::Turtle()
{
    lineWidth = 2;
    glLineWidth(lineWidth);

    lineLength = 10;
    angle = 30;
    zAngle = 30;

    drawLength = 0;
    growSpeed = 0;
    colorOffset = 5;

    curState.x = ofGetWidth()/2;;
    curState.y = ofGetHeight()/2;
    curState.z = 0;
    curState.angle = startAngle = 0;
    curState.zAngle = startZAngle = 0;

    branchingLevel = 1;
    branchingLevelsCompleted = 0;

    alpha = 50;

    setColor(0,0,0);
}

void Turtle::setColor( int _r, int _g, int _b)
{
    curState.r = _r;
    curState.g = _g;
    curState.b = _b;
    ofSetColor(curState.r, curState.g, curState.b, alpha);
}


bool Turtle::draw(string input, int _x, int _y, int _z)
{
    curState.x = _x;
    curState.y = _y;
    curState.z = _z;
    curState.angle = startAngle;
    curState.zAngle = startZAngle;

    int length = input.size();
    setColor(0,0,0);

    if(growSpeed > 0)
    {
        growSpeed=10;
        drawLength += growSpeed * ofGetLastFrameTime();

        if (drawLength > lineLength){
                         drawLength = lineLength;
        }

    }


	for(int i = 0; i < length; i++)
	{
        switch (input[i])
        {
            case FORWARD:
                moveForward();
            break;

            case RIGHT:
                curState.angle += angle;
            break;

            case LEFT:
                 curState.angle -= angle;
            break;

            case Z_RIGHT:
                  curState.zAngle += zAngle;
            break;

            case Z_LEFT:
                 curState.zAngle -= zAngle;
            break;

            case BRANCH_START:
                 savedStates.push_back(curState);
                 branchingLevel++;
            break;

            case BRANCH_STOP:
                 curState = savedStates[savedStates.size()-1];
                 savedStates.pop_back();
                 branchingLevel--;
            break;

            case MORE_RED:

                 curState.r += colorOffset;

                if(curState.r > 255)
                    curState.r = 0;

                ofSetColor(curState.r, curState.g, curState.b, alpha);

            break;

            case LESS_RED:

                 curState.r -= colorOffset;

                 if(curState.r < 0)
                    curState.r = 0;

                 ofSetColor(curState.r, curState.g, curState.b, alpha);

            break;

            case MORE_GREEN:

                 curState.g += colorOffset;

                 if(curState.g > 255)
                    curState.g = 255;

                  ofSetColor(curState.r, curState.g, curState.b, alpha);
            break;

            case LESS_GREEN:

                 curState.g -= colorOffset;

                 if(curState.g < 0)
                    curState.g = 0;

                 ofSetColor(curState.r, curState.g, curState.b, alpha);
            break;

            case MORE_BLUE:

                 curState.b += colorOffset;

                 if(curState.b > 255)
                    curState.b = 255;

                  ofSetColor(curState.r, curState.g, curState.b, alpha);
            break;

            case LESS_BLUE:

                 curState.b -= colorOffset;

                 if(curState.b < 0)
                    curState.b = 0;

                 ofSetColor(curState.r, curState.g, curState.b, alpha);
            break;
        }


	}// endfor

	if(growSpeed > 0 && drawLength == lineLength)
	{

	    drawLength = 0;
	    branchingLevelsCompleted++;
	    return true;
	}

	return false;
}


void Turtle::setLineWidth(int _lineWidth)
{
    lineWidth = _lineWidth;
    glLineWidth(lineWidth);
}

void Turtle::moveForward()
{

    float length;

    // is growing enabled
    if(growSpeed > 0)
    {
        int width;

        /* Uncomment this if you want older branches to be thicker*/
        if( THINNER_BRANCHES )
        {
             width = lineWidth - branchingLevel;
        }

        /*if (width < lineWidth)
            width = lineWidth;*/


        if(alpha > 180) alpha = 180;

        ofSetColor(curState.r, curState.g, curState.b, alpha);

        //TODO LIMITARE QUESTO BAD BOY


        glLineWidth(width);

        if (branchingLevel > branchingLevelsCompleted +1)
            return;

        else if(branchingLevel == branchingLevelsCompleted +1)
            length = drawLength;

        else
            length = lineLength;

    }
    else length = lineLength;



    float newX = curState.x +  cos(ofDegToRad(curState.angle))  *
                               cos(ofDegToRad(curState.zAngle)) *
                               length;

    float newY = curState.y +  sin(ofDegToRad(curState.angle)) * length;

    float newZ = curState.z +  cos(ofDegToRad(curState.angle)) *
                               sin(ofDegToRad(curState.zAngle)) *
                               length;

    glBegin(GL_LINES);
        glVertex3f(curState.x, curState.y, curState.z);
        glVertex3f(newX, newY, newZ);
    glEnd( );

	curState.x = newX;
	curState.y = newY;
    curState.z = newZ;
}

