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


#ifndef _TEST_APP
#define _TEST_APP
#include "testApp.h"

#include "ofMain.h"
#include "LSys.h"
#include "Turtle.h"

#define BUFFER_SIZE 256
#define NUM_WINDOWS 80
class testApp : public ofSimpleApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();


	private:

        float currentPresetIndex;

        //fft stuff
        float * fftSmoothed;
        float * left;
		float * right;
		float index;

		string result;

        LSys system;
        Turtle turtle;
		float counter;

        int draw_x;
        int draw_y;

        float rotate_x;
        float rotate_y;
        float rotate_z;

		struct preset
		{
            int bgRed;
            int bgGreen;
            int bgBlue;

            float lineLength;
            float linewidth;
            float angle;
            float zAngle;
            float startAngle;

            string start;
            vector <LRule> lrules;

            float growspeed;
            int level;


            int draw_x;
            int draw_y;

            float rotate_x;
            float rotate_y;
            float rotate_z;

            int colorOffset;
		};

		vector<preset> sets;

        int angle_incr;
        int z_angle_incr;

        void loadPreset(preset);

        void presets();

        void randomizeRotateVector();
};

#endif
