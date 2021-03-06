#pragma once

#include "ofMain.h"
#include "CloudsVisualSystemClusterMap.h"
#include "CloudsRun.h"
#include "CloudsStoryEngine.h"
#include "CloudsAct.h"
#include "CloudsFCPParser.h"
#include "CloudsVisualSystemManager.h"

class testApp : public ofBaseApp {
  public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void exit();
	
	CloudsVisualSystemClusterMap clusterMap;
	CloudsRun run;
	CloudsFCPParser parser;
	CloudsStoryEngine storyEngine;
	CloudsVisualSystemManager visualSystems;
};
