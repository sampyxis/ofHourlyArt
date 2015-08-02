#pragma once

#include "ofMain.h"
#include "ofVectorMath.h"

class Agent {
	public:
	  ofVec2f p, pOld;
	  float noiseZ, noiseZVelocity;
	  float stepSize, angle;
	  float W, H;
	  float noiseScale, noiseStrength, noiseZRange;

	  //void Agent(int i);
	  void setup();
	  void update1();
	  void update2();
	  void setNoiseZRange(float f);
};

class ofApp : public ofBaseApp{

	public:
		ofImage currImage;
		ofImage newImage;
		int H;
		int W;
		int w, h;
		int x,y;
		vector<Agent> agents;
		int pointCount;
		int agentsCount;
		ofPixels p;
		ofTexture tex;

		float curvePointX;
		float curvePointY;
		//int pointCount;
		int loopNum;
		int numOpp;
		float lineWeight;
		float diffusion;
		int loopNumLine;
		int numOppLine;
		int timeToRun;
		bool drawLines;
		bool drawSmLinesb;
		bool drawCurvesb;
		bool smCurves;
		bool smLines;
		bool showTint;

		int frameNum;
		int saveRate;
		
		void setup();
		void update();
		void draw();

		void drawSmallLines();
		void drawLargeLines();
		void drawCurves();

		void getColor();

		void customBrush(int x, int y);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void runAgents();
};


