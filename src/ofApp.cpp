#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30); // run at 60 fps
    
    
    sender.setup(HOST, PORT);
    
    
    filterFactor = 0.1f;
    
    recordContext.setup();
    recordContext.setMirror(true);
    recordDepth.setup(&recordContext);
    
    recordUser.setup(&recordContext);
    recordUser.setSmoothing(filterFactor);                // built in openni skeleton smoothing...
    recordUser.setMaxNumberOfUsers(1);
    
    recordContext.toggleRegisterViewport();
    //    recordContext.toggleMirror();
    
    //
    //    grayImg.allocate(recordDepth.getWidth(), recordDepth.getHeight());
    
    gui.setup();
    gui.add(bSendingOSC.set("Sending osc",false));
    gui.add(bTracking.set("Tracking",false));
    
    
    if (!ofFile("settings.xml"))
        gui.saveToFile("settings.xml");
    
    gui.loadFromFile("settings.xml");
    
    
    // init tracking data size;
    trackingDataSize = 8;// 30 frames for a sencod
    
    for(int i = 0;i<trackingDataSize;i++){
        
        trackingData.push_back(0.0);
        
    }
}
void ofApp::exit() {

    recordContext.shutdown();

}

//--------------------------------------------------------------
void ofApp::update(){
    recordContext.update();
    recordDepth.update();
    recordUser.update();
    
    if(bSendingOSC){
        // prepare data for osc send ----------------------------------------
        
        ofxOscMessage m;
        ofxOscMessage m1;
        //        m.setAddress("/composition/selectedclip/video/effects/pwl00/effect/float1");
        //        m.addFloatArg(ofMap(ofGetMouseX(), 0, ofGetWidth(), 0.f, 1.f, true));
        //        //    m.addFloatArg(ofMap(ofGetMouseY(), 0, ofGetHeight(), 0.f, 1.f, true));
        //        sender.sendMessage(m, false);
        //        m.clear();
        
        string data;
        
        for(int i = 0;i<trackingDataSize;i++){
            trackingData[i] = 0.0;
            trackingData[i] += i * 0.1;
            data += ofToString(trackingData[i]);
            if(i != trackingDataSize - 1){
                data += ",";
            }
            
        }
        
        cout << data << endl;
        
        // debug ================
        //        m.setAddress("/composition/selectedclip/video/effects/pwaveword/effect/osctextdata0");
        m.setAddress("/composition/selectedclip/video/effects/pwaveword/effect/osctextdata0");
        m.addStringArg(data);
        sender.sendMessage(m,false);
        
        
        m1.setAddress("/composition/selectedclip/video/effects/pwaveline/effect/oscdataline0");
        m1.addStringArg(data);
        sender.sendMessage(m1,false);
        
        m1.clear();
        
        
        
        
        //
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    recordDepth.draw(0,0,640,480);
    //    grayImg.draw(640,0,640,480);
    recordUser.draw();
    
    if(recordUser.getNumberOfTrackedUsers() > 0){
        
        
        recordUser.getTrackedUser(1)->skeletonCalibrating = true;
        
        
        float neck0x = recordUser.getTrackedUser(1)->neck.position[0].X;
        float neck0y = recordUser.getTrackedUser(1)->neck.position[0].Y;
        
        float neck1x = recordUser.getTrackedUser(1)->neck.position[1].X;
        float neck1y = recordUser.getTrackedUser(1)->neck.position[1].Y;
        
        float sLx = recordUser.getTrackedUser(1)->left_shoulder.position[1].X;
        float sLy = recordUser.getTrackedUser(1)->left_shoulder.position[1].Y;
        
        float sRx = recordUser.getTrackedUser(1)->right_shoulder.position[1].X;
        float sRy = recordUser.getTrackedUser(1)->right_shoulder.position[1].Y;
        
        float elbLx = recordUser.getTrackedUser(1)->left_upper_arm.position[1].X;
        float elbLy = recordUser.getTrackedUser(1)->left_upper_arm.position[1].Y;
        
        float elbRx = recordUser.getTrackedUser(1)->right_upper_arm.position[1].X;
        float elbRy = recordUser.getTrackedUser(1)->right_upper_arm.position[1].Y;
        
        
        float haLx = recordUser.getTrackedUser(1)->left_lower_arm.position[1].X;
        float haLy = recordUser.getTrackedUser(1)->left_lower_arm.position[1].Y;
        
        float haRx = recordUser.getTrackedUser(1)->right_lower_arm.position[1].X;
        float haRy = recordUser.getTrackedUser(1)->right_lower_arm.position[1].Y;
        
        
        float hix = recordUser.getTrackedUser(1)->hip.position[1].X*0.5 + recordUser.getTrackedUser(1)->hip.position[0].X*0.5;
        float hiy = recordUser.getTrackedUser(1)->hip.position[1].Y*0.5 + recordUser.getTrackedUser(1)->hip.position[0].Y*0.5;
        
        float tsX = recordUser.getTrackedUser(1)->left_upper_torso.position[1].X;
        float tsY = recordUser.getTrackedUser(1)->left_upper_torso.position[1].Y;
        
        
        ofSetColor(255, 255, 0);
        ofDrawCircle(neck0x,neck0y, 15);
        ofDrawCircle(neck1x,neck1y, 15);
        ofDrawCircle(sLx,sLy, 15);
        ofDrawCircle(sRx,sRy, 15);
        ofDrawCircle(elbLx,elbLy, 15);
        ofDrawCircle(elbRx,elbRy, 15);
        ofDrawCircle(haLx,haLy, 15);
        ofDrawCircle(haRx,haRy, 15);
        ofDrawCircle(hix,hiy, 15);
        ofDrawCircle(tsX,tsY, 15);
        
        
        
        
        
        
        
    }
    
    
    
    
    ofSetColor(255);
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 'f':
            recordContext.toggleMirror();
        default:
            break;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
