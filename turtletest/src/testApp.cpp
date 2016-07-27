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


#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    //smooth lines
    glEnable( GL_LINE_SMOOTH );
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    // Enable Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ofSetFrameRate(25);
	ofSetVerticalSync(true);
	ofBackground(0,0,0);

	system = LSys();

    system.addVariable("F"); //forward
    system.addVariable("X"); //x variable
    system.addVariable("Y"); //y variable

    system.printVariables();

    system.addConstant("+"); //turn right on the xy plane
    system.addConstant("-"); //turn left  on the xy plane
    system.addConstant("<"); //turn right on the xz plane
    system.addConstant(">"); //turn left on the xz plane
    system.addConstant("]"); //start a branch
    system.addConstant("["); //end a branch
    system.addVariable("b"); //add blue to current color
    system.addVariable("y"); //add yellow to current color (less blue)
    system.addVariable("r"); //add red to current color
    system.addVariable("c"); //add cyan to current color (less red)
    system.addVariable("g"); //add green to current color
    system.addVariable("m"); //add magent to current color(less magenta)


    system.printConstants();

    presets();
    currentPresetIndex = 0;

    loadPreset(sets[currentPresetIndex]);


	counter = 0;
}

//--------------------------------------------------------------
//counter is used for rotation
void testApp::update(){

counter = counter + 0.025f;

}

//--------------------------------------------------------------
void testApp::draw()
{
    glPushMatrix();

            //rotate around the center
            glTranslatef(512, 384, 0);

            glRotatef(counter * 12 , rotate_x, rotate_y, rotate_z);

            glTranslatef(-512, -384, 0);


      turtle.draw(result, draw_x, draw_y, 0);

   glPopMatrix();
}

void testApp::randomizeRotateVector()
{
    srand ((unsigned) time(NULL) );
    rotate_x = rand() / (float) RAND_MAX;
    rotate_y = rand() / (float) RAND_MAX;
    rotate_z = rand() / (float) RAND_MAX;
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

    switch (key)
    {

        case (114): //R

            randomizeRotateVector();

        break;

        case (267): //F11

            ofToggleFullscreen();

        break;


        case (358):  //right arrow

            if (currentPresetIndex + 1 >= sets.size())
            {
                currentPresetIndex = 0;
                loadPreset(sets[currentPresetIndex]);
            }
            else
            {
                 loadPreset(sets[++currentPresetIndex]);
            }
        break;

        case (356): //left arrow

            if (currentPresetIndex -1 < 0)
            {
                currentPresetIndex = sets.size()-1;
                loadPreset(sets[currentPresetIndex]);
            }
            else
            {

                loadPreset(sets[--currentPresetIndex]);
            }

        break;

        case (119):
            draw_y--;

            cout << "y: " << draw_y <<endl;
        break;

        case (115):
            draw_y++;
            cout <<  "y: " << draw_y <<endl;
        break;

          case (97):
            draw_x--;

            cout << "x: " << draw_x <<endl;
        break;

        case (100):
            draw_x++;
            cout << "x: " << draw_x <<endl;
        break;
    }

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(){

}

void testApp::loadPreset(preset preset)
{
    ofBackground(preset.bgRed, preset.bgGreen, preset.bgBlue);

    system.clearRules();

    for (vector<LRule>::iterator it = preset.lrules.begin();
         it!=preset.lrules.end();
         ++it)
    {
        system.addRule(*it);
    }

    system.setStart(preset.start);

    result = system.getLevel(preset.level);

    turtle = Turtle();
    turtle.lineLength = preset.lineLength;
    turtle.growSpeed = preset.growspeed;
    turtle.setLineWidth(preset.linewidth);
    turtle.angle = preset.angle;
    turtle.zAngle = preset.zAngle;
    turtle.colorOffset = preset.colorOffset;
    turtle.startAngle = preset.startAngle;

    draw_x = preset.draw_x;
    draw_y = preset.draw_y;

    rotate_x  = preset.rotate_x;
    rotate_y  = preset.rotate_y;
    rotate_z = preset.rotate_z;
}

/*
In an ideal world, where days are 128 hours long and I'm not lazy,
these would be loaded from an XML file

Me from the future: HAHAHAH XML LOL LOL
*/

void testApp::presets()
{

    preset ultimo;

    //background color
    ultimo.bgRed = 0;
    ultimo.bgBlue = 0;
    ultimo.bgGreen = 0;

    //turtle linw width
    ultimo.linewidth = 4 ;

     //define initial l-system axiom
    ultimo.start = "X";

    //define substitution rules
    ultimo.lrules.push_back(LRule("X", "rr[>XY]+[<XY]<[+FX]"));
    ultimo.lrules.push_back(LRule("Y", "+[[X]+bY]"));
    ultimo.lrules.push_back(LRule("F", "gFF"));


    //define initial rotation vector
    ultimo.rotate_x = 0;
    ultimo.rotate_y = 1;
    ultimo.rotate_z = 0;

    //turtle configuration
    ultimo.lineLength =5;      //length of each segment
    ultimo.growspeed = 0.5f;  //if this is set to 0, the THINNER_BRANCHES thing won't happen
    ultimo.angle = 45;        //angle used for turns in the xy plane
    ultimo.zAngle =35;        //angle used for turns in the xz plane
    ultimo.startAngle = 90;   //you can set the initial angle
    ultimo.draw_x=464;        //start drawing from here
    ultimo.draw_y=430;        //and here
    ultimo.level  = 9;        //how many l-system iteration
    ultimo.colorOffset = 1;   //how much to increment/decrement a color component when a color variable is read
    sets.push_back(ultimo);

    /*-------------------------------------------------------*/

    preset albero_rosso;

    albero_rosso.bgRed = 200;
    albero_rosso.bgBlue = 200;
    albero_rosso.bgGreen = 200;

    albero_rosso.linewidth = 5 ;

    albero_rosso.lrules.push_back(LRule("X", "F-[[X][<X][>X]+>X]+<F[+FX][>FX]-X"));
    albero_rosso.lrules.push_back(LRule("F", "rFF"));

    //albero_rosso.lrules.push_back(LRule("H", "g-Z[<+H]L"));

    albero_rosso.rotate_x = 0;
    albero_rosso.rotate_y = 1;
    albero_rosso.rotate_z = 0;

    albero_rosso.start = "X";

    albero_rosso.lineLength = 7;
    albero_rosso.growspeed = 0.4f;
    albero_rosso.angle = 24;
    albero_rosso.zAngle =35;
    albero_rosso.startAngle = -90;
    albero_rosso.draw_x=464;
    albero_rosso.draw_y=730;
    albero_rosso.level  = 6;
    albero_rosso.colorOffset = 1;
    sets.push_back(albero_rosso);


/*-------------------------------------------------------*/

    preset pianta3;

    pianta3.bgRed = 200;
    pianta3.bgBlue = 200;
    pianta3.bgGreen = 200;

    pianta3.linewidth = 3 ;

    pianta3.lrules.push_back(LRule("S", "b[>>+++Z][<<—Z]TS"));
    pianta3.lrules.push_back(LRule("Z", "g+H[>-Z]L"));

    pianta3.lrules.push_back(LRule("H", "g-Z[<+H]L"));
    pianta3.lrules.push_back(LRule("T", ">TL"));

    pianta3.lrules.push_back(LRule("L", "r[-FFF][+FFF][>FFF][<FFF]F"));

    pianta3.rotate_x = 0;
    pianta3.rotate_y = 1;
    pianta3.rotate_z = 0;

    pianta3.start = "SLFFF";

    pianta3.lineLength = 20;
    pianta3.growspeed = 0.4f;
    pianta3.angle = 20;
    pianta3.zAngle =20;
    pianta3.startAngle = -90;
    pianta3.draw_x=464;
    pianta3.draw_y=630;
    pianta3.level  = 10;
    pianta3.colorOffset = 5;
    sets.push_back(pianta3);

 /*-------------------------------------------------------*/
    preset piantaboh;

    piantaboh.bgRed = 120;
    piantaboh.bgBlue = 120;
    piantaboh.bgGreen = 120;

    piantaboh.linewidth = 3;

    piantaboh.lrules.push_back(LRule("X", "F->ry<+gF[+FX]r->[r[X]+>bX][X]"));
    piantaboh.lrules.push_back(LRule("F", "FF"));
    piantaboh.lrules.push_back(LRule("b", "br"));
    piantaboh.lrules.push_back(LRule("g", "gyb"));

    piantaboh.rotate_x = 0;
    piantaboh.rotate_y = 1;
    piantaboh.rotate_z = 0;

    piantaboh.start = "rrrFX>[X]>[X]>[X]";

    piantaboh.lineLength = 4;
    piantaboh.growspeed = 0.3f;
    piantaboh.angle = 60;
    piantaboh.zAngle = 60;
    piantaboh.startAngle = -90;
    piantaboh.draw_x=464;
    piantaboh.draw_y=830;
    piantaboh.level  = 6;
    piantaboh.colorOffset = 4;
    sets.push_back(piantaboh);


 /*-------------------------------------------------------*/
    //not a sierpinsky triangle but looks like
    preset sierpinsky;

    sierpinsky.bgRed = 0;
    sierpinsky.bgBlue = 0;
    sierpinsky.bgGreen = 0;

    sierpinsky.linewidth = 3;

    sierpinsky.lrules.push_back(LRule("Y", "bXF-rYF->[[X->F]+bX->f]<ggXm"));
    sierpinsky.lrules.push_back(LRule("X", "bYF+rXF+Y"));

    sierpinsky.rotate_x = 0;
    sierpinsky.rotate_y = 1;
    sierpinsky.rotate_z = 0;

    sierpinsky.start = "YF";

    sierpinsky.lineLength = 5;
    sierpinsky.growspeed = 0.15f;
    sierpinsky.angle = 60;
    sierpinsky.zAngle = 60;
    sierpinsky.startAngle = 0;
    sierpinsky.draw_x=164;
    sierpinsky.draw_y=600;
    sierpinsky.level  = 7;
    sierpinsky.colorOffset = 105;
    sets.push_back(sierpinsky);


 /*-------------------------------------------------------*/
    preset square;

    square.bgRed = 0;
    square.bgBlue = 0;
    square.bgGreen = 0;

    square.linewidth = 3;

    square.lrules.push_back(LRule("F", "FrF+rF-[<X>]F+F+rFF"));
    square.lrules.push_back(LRule("X", "FrF+rF-[>X<]F+F+rgFF+F++F"));

    square.rotate_x = 0.3;
    square.rotate_y = 0;
    square.rotate_z = 1;

    square.start = "F+F+F+F";

    square.lineLength = 16;
    square.growspeed = 0.2f;
    square.angle = 90;
    square.zAngle = 90;
    square.startAngle = 0;
    square.draw_x=445;
    square.draw_y=52;
    square.level  = 4;
    square.colorOffset = 105;
    sets.push_back(square);



 /*-------------------------------------------------------*/
 /* that's my favourite */
    preset bph;

    bph.bgRed = 0;
    bph.bgBlue = 0;
    bph.bgGreen = 0;

    bph.linewidth = 1;

    //QUA C'È QUALCOSA CHE NON CAPISCO
    bph.lrules.push_back(LRule("F", "rrF++Fbb+Fr++yrrF"));

    bph.rotate_x = 0;
    bph.rotate_y = 0;
    bph.rotate_z = 1;

    bph.start = "F+F+F+F+F+F";

    bph.lineLength = 64;
    bph.growspeed = 0.4;
    bph.angle = 30;
    bph.zAngle = 30;
    bph.startAngle = 0;
    bph.draw_x=445;
    bph.draw_y=52;
    bph.level  = 5;
    bph.colorOffset = 150;
    sets.push_back(bph);

 /*-------------------------------------------------------*/

    preset esagoni;

    esagoni.bgRed = 0;
    esagoni.bgBlue = 0;
    esagoni.bgGreen = 0;

    esagoni.linewidth = 5;

    //QUA C'È QUALCOSA CHE NON CAPISCO
    esagoni.lrules.push_back(LRule("F", "[X]ggF+Fb+++Fr+rrF[X]"));
    esagoni.lrules.push_back(LRule("X", "F+Fb+++Fr+F"));


    esagoni.rotate_x = 1;
    esagoni.rotate_y = 0;
    esagoni.rotate_z = 1;

    esagoni.start = "F+>F+>F+>F";

    esagoni.lineLength = 24;
    esagoni.growspeed = 3;
    esagoni.angle = 60;
    esagoni.zAngle = 45;
    esagoni.startAngle = 0;
    esagoni.draw_x=465;
    esagoni.draw_y=165;
    esagoni.level  = 5;
    esagoni.colorOffset = 15;
    sets.push_back(esagoni);



 /*-------------------------------------------------------*/
        //COSA CHE CAZZO È ??? PERCHÈ<??
    preset c3;

    c3.bgRed = 0;
    c3.bgBlue = 0;
    c3.bgGreen = 0;

    c3.linewidth = 3;

    c3.lrules.push_back(LRule("F", "ggF+Fb++Fr+yyF"));

    c3.rotate_x = 0;
    c3.rotate_y = 0;
    c3.rotate_z = 1;

    c3.start = "F+F+F+F";

    c3.lineLength = 54;
    c3.growspeed = 0.2f;
    c3.angle = 30;
    c3.zAngle = 90;
    c3.startAngle = 0;
    c3.draw_x=465;
    c3.draw_y=165;
    c3.level  = 5;
    c3.colorOffset = 15;
    sets.push_back(c3);


 /*-------------------------------------------------------*/
    preset pg32tek;

    pg32tek.linewidth = 5;

    pg32tek.bgRed = 0;
    pg32tek.bgBlue = 0;
    pg32tek.bgGreen = 0;

    pg32tek.lrules.push_back(LRule("X", "rgbX+>[YF]<++<[YF->FX]>--gFXFX-mYF"));
    pg32tek.lrules.push_back(LRule("Y", ">[FFY]<g-FX+YmFYF++YF+FX--FX-Y"));
    pg32tek.lrules.push_back(LRule("F", "F"));

    pg32tek.lrules.push_back(LRule("b", "byr"));
    pg32tek.lrules.push_back(LRule("g", "gcc"));

    pg32tek.rotate_x = 0;
    pg32tek.rotate_y = 0.5f;
    pg32tek.rotate_z = 0.3f;

    pg32tek.start = "X";

    pg32tek.lineLength = 6;
    pg32tek.growspeed = 0.3;
    pg32tek.angle = 45;
    pg32tek.zAngle = 45;
    pg32tek.startAngle = 180;
    pg32tek.draw_x=500;
    pg32tek.draw_y=500;
    pg32tek.level  = 5;
    pg32tek.colorOffset = 3;

    sets.push_back(pg32tek);


 /*-------------------------------------------------------*/
    preset crystal;

    crystal.bgRed = 0;
    crystal.bgBlue = 0;
    crystal.bgGreen = 20;

    crystal.linewidth = 3;

    crystal.lrules.push_back(LRule("F", "r[>F[+bF][<F]]F+F++rF+gF"));

    //crystal.lrules.push_back(LRule("b", "byr"));
    //crystal.lrules.push_back(LRule("g", "gcc"));

    crystal.rotate_x = 0;
    crystal.rotate_y = 1;
    crystal.rotate_z = 1;

    crystal.start = "F+F+F+F";

    crystal.lineLength = 22;
    crystal.growspeed = 0.3;
    crystal.angle = 90;
    crystal.zAngle = 90;
    crystal.startAngle = 0;
    crystal.draw_x=250;
    crystal.draw_y=400;
    crystal.level  = 4;
    crystal.colorOffset = 3;

    sets.push_back(crystal);


    /*-------------------- ------------------------**/
    preset pg3d;

    pg3d.bgRed = 0;
    pg3d.bgBlue = 0;
    pg3d.bgGreen = 0;

    pg3d.linewidth = 3;

    pg3d.lrules.push_back(LRule("X", "rbX+>[YF]<++<[YFFX]>--cFXF-YF>[FFX]<"));
    pg3d.lrules.push_back(LRule("Y", ">[FFY]<r-FX+mYF++>[Y]<F+FX--FX-Y"));
    pg3d.lrules.push_back(LRule("F", "F"));

    pg3d.lrules.push_back(LRule("b", "byr"));
    pg3d.lrules.push_back(LRule("g", "gcc"));

    pg3d.rotate_x = 0;
    pg3d.rotate_y = 0.3f;
    pg3d.rotate_z = 0.3f;

    pg3d.start = "X";

    pg3d.lineLength = 7;
    pg3d.growspeed = 0.3;
    pg3d.angle = 60;
    pg3d.zAngle = 45;
    pg3d.startAngle = 180;
    pg3d.draw_x=500;
    pg3d.draw_y=700;
    pg3d.level  = 5;
    pg3d.colorOffset = 2;

    sets.push_back(pg3d);


 /*-------------------------------------------------------*/

    preset a2;

    a2.bgRed = 0;
    a2.bgBlue = 0;
    a2.bgGreen = 0;

    a2.linewidth = 3;

    a2.lrules.push_back(LRule("X", "F->by[[X]+bX]<+gF[+FX]b-g<X>"));
    a2.lrules.push_back(LRule("F", "FF"));
    a2.lrules.push_back(LRule("g", "br"));
    a2.lrules.push_back(LRule("g", "gyb"));

    a2.rotate_x = 0.3;
    a2.rotate_y = 1;
    a2.rotate_z = 0.4;

    a2.start = "X";

    a2.lineLength = 5;
    a2.growspeed = 0.2f;
    a2.angle = 90;
    a2.zAngle = 90;
    a2.startAngle = -90;
    a2.draw_x=500;
    a2.draw_y=900;
    a2.level  = 7;
    a2.colorOffset = 34;

    sets.push_back(a2);


    /*-------------------------------------*/

    preset alberodemmerda;

    alberodemmerda.bgRed = 0;
    alberodemmerda.bgBlue = 0;
    alberodemmerda.bgGreen = 0;

    alberodemmerda.linewidth = 3;

    alberodemmerda.lrules.push_back(LRule("X", "F->by[[X]+bX]<+gF[+FX]b-g<X>"));
    alberodemmerda.lrules.push_back(LRule("F", "FF"));
    alberodemmerda.lrules.push_back(LRule("b", "br"));
    alberodemmerda.lrules.push_back(LRule("g", "gyb"));

    alberodemmerda.rotate_x = 0;
    alberodemmerda.rotate_y = 1;
    alberodemmerda.rotate_z = 0.4;

    alberodemmerda.start = "X";

    alberodemmerda.lineLength = 4;
    alberodemmerda.growspeed = 0.3f;
    alberodemmerda.angle = 30;
    alberodemmerda.zAngle = 30;
    alberodemmerda.startAngle = -90;
    alberodemmerda.draw_x=500;
    alberodemmerda.draw_y=900;
    alberodemmerda.level  = 7;
    alberodemmerda.colorOffset = 34;

    sets.push_back(alberodemmerda);


     /*-------------------------------------------------------*/

    preset peano_gosper;

    peano_gosper.linewidth = 3;

    peano_gosper.bgRed = 0;
    peano_gosper.bgBlue = 0;
    peano_gosper.bgGreen = 0;

    peano_gosper.lrules.push_back(LRule("X", "gbX+YF++YF-FX--cFXFX-YF"));
    peano_gosper.lrules.push_back(LRule("Y", "r-FX+YFYF++YF+FX--FX-Y"));
    peano_gosper.lrules.push_back(LRule("F", "F"));

    peano_gosper.lrules.push_back(LRule("b", "brr"));
    peano_gosper.lrules.push_back(LRule("g", "gbb"));

    peano_gosper.rotate_x = 0;
    peano_gosper.rotate_y = 0;
    peano_gosper.rotate_z = 1;

    peano_gosper.start = "X";

    peano_gosper.lineLength = 8;
    peano_gosper.growspeed = 0.1;
    peano_gosper.angle = 60;
    peano_gosper.zAngle = 60;
    peano_gosper.startAngle = -90;
    peano_gosper.draw_x=500;
    peano_gosper.draw_y=500;
    peano_gosper.level  = 5;
    peano_gosper.colorOffset = 2;

    sets.push_back(peano_gosper);

}
