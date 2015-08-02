#include "ofApp.h"

/*
	This is a conversion of the hourly art app from processing to OpenFrameworks.
	The code is still messy and not as functional yet, a WIP

	Changing from processing with hourly art to openFrameworks
		1) Load a random image from online
		2) Create agents to run over the pixels
		3) On update - update the agents - decide how to run (lines, curves, etc.)
		4) On draw - draw the current image

	To Do's
		Push to github
		Fix (or use) brush
		Add gif saving (https://github.com/jesusgollonet/ofxGifEncoder)
		Pull images from art history apis

		Nice future features
			Video streaming of live changes

	
	*/

//--------------------------------------------------------------
void ofApp::setup(){
	H = 1024/1.5;
	W = 768/1.5;
	curvePointX = 0;
	curvePointY = 0;
	pointCount = 1;
	loopNum = 0;
	numOpp = 100;
	lineWeight = 0;
	diffusion = 50;
	loopNumLine = 0;
	numOppLine = 100;
	timeToRun = 10000;
	drawLines = false;
	drawSmLinesb = false;
	drawCurvesb = true;
	smCurves = true;
	smLines = false;
	showTint = false;
	frameNum = 0;
	w = ofGetWidth();
	h = ofGetHeight();
	x = ofGetWidth()/2;
	y = ofGetHeight()/2;
	saveRate = 1000;

	currImage.loadImage("images/doge_loredan.jpg");
	currImage.resize(ofGetWindowWidth(),ofGetWindowHeight());
	ofSeedRandom();


	// Need this so we don't always erase the lines...
	ofSetBackgroundAuto(false);

	// Draw the image one time
	currImage.draw(0,0);

	// Agents
	// ------ agents ------
	const int numAgents = int(ofRandom(100,1000));
	vector<Agent> agents(numAgents);
	int agentsCount = 4000;
	float noiseScale = 100, noiseStrength = 10, noiseZRange = 0.4;
	float overlayAlpha = 10, agentsAlpha = 90, strokeWidth = 0.3;
	int drawMode = 1;
	// end Agents

}

//--------------------------------------------------------------
void ofApp::update(){
	//ofBackground(255);
    //runAgents();
	//ofSleepMillis(1000);
	//drawSmallLines();
	// Will need to check to save every 20 seconds
	
	//frameNum ++;
	//if (frameNum = saveRate) {
	//	ofImage myImage;
	//	currImage.grabScreen(0,0,500,500);
	//	string frameName;
	//	frameName = "img_" + ofToString(frameNum) + ".png"; 
	//	////ofSaveFrame();
	//	currImage.saveImage(frameName);
	//	//ofSaveScreen(frameName);
	//	saveRate = frameNum + 10000;
	//}

}

//--------------------------------------------------------------
void ofApp::draw(){
	drawSmallLines();
	drawLargeLines();
	drawCurves();
}

//---------------------------------------------------------------
void ofApp::drawSmallLines(){
  getColor();
  ofSetLineWidth(ofRandom(.1,3));
  if (loopNumLine >= numOppLine) {
    if(smLines){
      ofLine(x,y, x+ ofRandom(-w, w)/8, y + ofRandom(-h, h)/8);
    } else {
      ofLine(x,y, x+ ofRandom(-w, w)/2, y + ofRandom(-h, h)/2);
    }
    loopNumLine = 0;
  } else {
    ofLine(x, y, x+ ofRandom(3,30), y+ ofRandom(3,30));
	customBrush(x, y);
	//customBrush(x+ ofRandom(3,30), y+ ofRandom(3,30));
    loopNumLine = loopNumLine + (int)ofRandom(-1,5);
    x = (int)ofRandom(0, w);
    y  = (int)ofRandom(0, h);
  }
}

void ofApp::drawCurves() {
	  getColor();
    // every numOpp times - do a stright line
  if( loopNumLine >= numOppLine ) {
    if(!drawCurvesb){
      ofLine(x,y, x+ ofRandom(-w, w)/8, y + ofRandom(-h, h)/8);
    } else {
      ofLine( x, y, x + ofRandom(-w,w)/2, y + ofRandom(-h,h)/2);
    }
    loopNumLine = 0;
    //printText("Line!!!!!!!!!!!!!!!!!!!!!",10,20);
  } else {
    ofBeginShape();
    ofCurveVertex(x,y);
    ofCurveVertex(x,y);
    for( int i = 0; i<pointCount; i++) {
      if(smCurves) {
        curvePointX = ofClamp(x+ofRandom(-10, 10), 0, w-1);
        curvePointY = ofClamp(y+ofRandom(-10,10),0, h-1);        
      } else {
        curvePointX = ofClamp(x+ofRandom(-50, 50), 0, w-1);
        curvePointY = ofClamp(y+ofRandom(-50,50),0, h-1);
      }
      ofCurveVertex(curvePointX, curvePointY);
    }   
    ofCurveVertex(curvePointX, curvePointY);
    ofEndShape();
    x = curvePointX;
    y = curvePointY;
    loopNumLine = loopNumLine + (int)ofRandom(-1,5);
  }
}

void ofApp::drawLargeLines(){
	  getColor();
  if (loopNumLine >= numOppLine) {
    if(smLines){
      ofLine(x,y, x+ ofRandom(-w, w)/8, y + ofRandom(-h, h)/8);
    } else {
      ofLine(x,y, x+ ofRandom(-w, w)/2, y + ofRandom(-h, h)/2);
    }
    loopNumLine = 0;
  } else {
    ofLine(x, y, x+ ofRandom(1,10), y+ ofRandom(1,10));
	customBrush(x,y);
    loopNumLine = loopNumLine + (int)ofRandom(-1,5);
    x = (int)ofRandom(0, w);
    y = (int)ofRandom(0, h);
  }

}

void ofApp::runAgents(){
	// Agent code
	// Now that the initial image is done - run the Agents!
		// Which type
		int x, y;
		x = 0;
		y = 0;
		int type = int(ofRandom(1,2));
		int time_to_run = int(ofRandom(10,200));
		for(int j = 0; j < time_to_run; j++){ 
		  if(type ==1) {
			  for(int i=0; i<agents.size(); i++) 
			agents[i].update1();
			//int pixelIndex = ( x+ (y*currImage.width ));
			//ofColor c = currImage.getPixelsRef()[pixelIndex];
		   ofColor newC = currImage.getColor(x, y);
			ofSetColor(newC);
		  //ofSetColor(c,ofRandom(1,255)); 
		  // using Hue now - but may want to change that later
		  ofSetLineWidth(newC.getHue());
			pointCount = (int)ofRandom(1,5);
			x = (int)ofRandom(0, currImage.width);
			y  = (int)ofRandom(0, currImage.height);
			//ofSetColor(c, ofRandom(1,255));
			currImage.setColor(x, y, newC);
			//p.setColor(x,y,c);
			//currImage.draw(x,y);
			currImage.update();
		  } 
		  else {
			for(int i=0; i<agentsCount; i++) 
				agents[i].update2();
			 // int pixelIndex = ( x+ (y*currImage.width ));
		  //ofColor c = currImage.getPixelsRef()[pixelIndex];
		  //ofSetColor(c,ofRandom(1,255));
			ofColor newC = currImage.getColor(x, y);
			ofSetColor(newC);
		  // using Hue now - but may want to change that later
		  ofSetLineWidth(newC.getHue()); 
			pointCount = (int)ofRandom(1,5);
			x = (int)ofRandom(0, currImage.width);
			y  = (int)ofRandom(0, currImage.height);
			currImage.setColor(x, y, newC);
			//p.setColor(x,y,c);
			//currImage.draw(x,y);
			currImage.update();
		  } 

		}
	// End Agent code
	// Set the pixles back into the texture
		//tex.readToPixels(p);
}

//--------------------------------------------------------------
void ofApp::getColor(){
   ofColor newC = currImage.getColor(x, y);
   ofSetColor(newC);
}

void ofApp::customBrush(int x, int y){
	int maxRadius = 20;  // Increase for a wider brush
	int radiusStepSize = 5;  // Decrease for more circles (i.e. a more opaque brush)
	int alpha = 0;  // Increase for a more opaque brush
	int maxOffsetDistance = 200;  // Increase for a larger spread of circles
	for (int radius=maxRadius; radius>0; radius-=radiusStepSize) {
		float angle = ofRandom(ofDegToRad(360.0)); 
		float distance = ofRandom(0,maxOffsetDistance);
		float xOffset = cos(angle) * distance;
		float yOffset = sin(angle) * distance;
		ofSetColor(255, alpha);
		ofCircle(x+xOffset, y+yOffset, radius);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


void Agent::setup(){
	// Set some vars
	noiseZ = 0.01f;
	noiseZVelocity = 0.01f;
	// Need to figure out how to use one standard width
	H = 1024/1.5;
	W = 768/1.5;
	p = ofVec2f(ofRandom(W, H));
	pOld = ofVec2f(p.x, p.y);
	stepSize = ofRandom(1,5);
	setNoiseZRange(0.4f);
	noiseScale = 100, noiseStrength = 10, noiseZRange = 0.4f;
	}

void Agent::update1(){

	angle = ofNoise(p.x/noiseScale, p.y/noiseScale, noiseZ) * noiseStrength;

    p.x += cos(angle) * stepSize;
    p.y += sin(angle) * stepSize;

    // offscreen wrap
    if (p.x<-10) p.x=pOld.x=W+10;
    if (p.x>W+10) p.x=pOld.x=-10;
    if (p.y<-10) p.y=pOld.y=H+10;
    if (p.y>H+10) p.y=pOld.y=-10;

	ofSetLineWidth( ofGetLineWidth()* stepSize);
	ofLine(pOld.x, pOld.y, p.x, p.y);

    pOld.set(p);
    noiseZ += noiseZVelocity;
};

void Agent::update2(){
	angle = ofNoise(p.x/noiseScale ,p.y/noiseScale, noiseZ) * 24;
    angle = (angle - int(angle)) * noiseStrength;

    p.x += cos(angle) * stepSize;
    p.y += sin(angle) * stepSize;

    // offscreen wrap
    if (p.x<-10) p.x=pOld.x=W+10;
    if (p.x>W+10) p.x=pOld.x=-10;
    if (p.y<-10) p.y=pOld.y=H+10;
    if (p.y>H+10) p.y=pOld.y=-10;

	ofSetLineWidth( ofGetLineWidth()* stepSize);
	ofLine(pOld.x, pOld.y, p.x, p.y);

    pOld.set(p);
    noiseZ += noiseZVelocity;
}

void Agent::setNoiseZRange(float theNoiseZRange){
	// small values will increase grouping of the agents
    noiseZ = ofRandom(theNoiseZRange);
}


