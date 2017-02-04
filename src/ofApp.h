#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGUI.h"


using namespace ofxCv;
using namespace cv;


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    //camera
    int camWidth,camHeight;
    ofVideoGrabber videoGrabber;
    
    //background difference
    ofxCv::RunningBackground background;
    ofImage diffBackground;
    void resetBackgroundMethod();

    //gui  [only if(key==0)]
    ofxPanel gui;
    ofxButton resetBackground;
    ofxIntSlider bgThreshold;
    ofxIntSlider timerSec;


    //[0:old,1:new]
    float dirtyLevel[2]={0,0};
    
    int gomiNumber;
    
    //press key number
    int keyState=NULL;
    

    
  
    
    
    

    
};
