#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    gomiNumber=0;
    
    //gui setting
    resetBackground.addListener(this,&ofApp::resetBackgroundMethod);
    gui.setup();
    gui.add(resetBackground.setup("resetBackground"));
    gui.add(bgThreshold.setup("bgThreshold",50,0,100));
    gui.add(timerSec.setup("TimerSec",2,1,20));


    //camera settings
    camWidth=1280;
    camHeight=720;
    videoGrabber.setDeviceID(0);
    ofSetLogLevel(OF_LOG_VERBOSE);
    videoGrabber.setVerbose(true);
    videoGrabber.listDevices();
    videoGrabber.initGrabber(camWidth, camHeight);

    //openCV initialize
    background.setLearningTime(900);
    background.setThresholdValue(20);
    diffBackground.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    
   
}

//--------------------------------------------------------------
void ofApp::update(){
    videoGrabber.update();
    if(videoGrabber.isFrameNew()) {
    background.setThresholdValue(bgThreshold);//0-100
    background.update(videoGrabber,diffBackground);
    
        diffBackground.update();
        
 
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    //video
    videoGrabber.draw(0,0,camWidth, camHeight);
    diffBackground.draw(0,0);
    
    
    //key[0]-> settings
    if(keyState==0){
    gui.draw();
    }
    
   
    int cvWhiteColorArea=0;//白の面積
    //数時間ごとに認識処理
    if((int)ofGetElapsedTimef()%timerSec==0){
     //白エリアを検出
    for(int x=0;x<camWidth;x++){
        for(int y=0;y<camHeight;y++){
            
            if(diffBackground.getColor(x, y)==ofFloatColor(255)){//float????
                cvWhiteColorArea++;
            }
        }
    }
    
    
    dirtyLevel[1]=ofMap(cvWhiteColorArea, 0, camWidth*camHeight,0, 100);
        if(dirtyLevel[1]-dirtyLevel[0]>0){//ゴミが増えた時
            gomiNumber+=dirtyLevel[1]-dirtyLevel[0];
            for(int n=0;n<dirtyLevel[1]-dirtyLevel[0];n++)system("sh ~/gomiadmin/gomigen.sh");
        }
        else if(dirtyLevel[0]-dirtyLevel[1]>0){//減った時
             gomiNumber-=dirtyLevel[0]-dirtyLevel[1];
             for(int n=0;n<dirtyLevel[0]-dirtyLevel[1];n++)system("sh ~/gomiadmin/gomithrow.sh");
        }
        
        dirtyLevel[0]=dirtyLevel[1];//代入
    }
    ofSetColor(255, 0, 0);
    ofDrawBitmapString("Number of gomi-> "+ofToString(gomiNumber), 50, 100);
    ofDrawBitmapString("white Area-> "+ofToString(cvWhiteColorArea), 50, 50);
    
    
}

void ofApp::resetBackgroundMethod(){
    background.reset();
    for(int n=0;n<gomiNumber;n++)system("sh ~/gomiadmin/gomithrow.sh");
    gomiNumber=0;

}
void ofApp::exit(){
    for(int n=0;n<gomiNumber;n++)system("sh ~/gomiadmin/gomithrow.sh");
    cout<<"exit"<<endl;
    gomiNumber=0;

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='0')keyState=0;
    if(key=='9')system("sh ~/gomiadmin/gomidel.sh");

    else keyState=99;
   

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
