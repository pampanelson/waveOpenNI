#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxOpenNI.h"


//using namespace ofxCv;
//using namespace cv;
// send host (aka ip address)
#define HOST "localhost"
//#define HOST "192.168.0.174"

/// send port
#define PORT 8000

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
		
    
    
    ofxOscSender sender;
    
    ofxPanel gui;
    ofParameter<bool> bSendingOSC;
    ofParameter<bool> bTracking;
    ofParameter<float> near;
    ofParameter<float> far;

    
        ofxCvGrayscaleImage grayImg;
    
    ofxOpenNIContext    recordContext, playContext;
    
    ofxDepthGenerator    recordDepth;
    
    ofxUserGenerator    recordUser, playUser;
    float                filterFactor;
    
    ofxImageGenerator    recordImage, playImage;
    
    int trackingDataSize;
    vector<float> trackingData;
};
