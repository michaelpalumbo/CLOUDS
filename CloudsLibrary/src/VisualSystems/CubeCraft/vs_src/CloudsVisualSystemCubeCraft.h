//
// CLOUDS Interactive Documentary
//
// VISUAL SYSTEMS
//
// Welcome to the EMPTY CloudsVisualSystem
//
//
//

#pragma once

#include "CloudsVisualSystem.h"
#include "CloudsGlobal.h"
#include "ofxObjLoader.h"


class CloudsVisualSystemCubeCraft : public CloudsVisualSystem {
public:
    
	
	//TODO: Change this to the name of your visual system
	//This determines your data path so name it at first!
	//ie getVisualSystemDataPath() uses this
    string getSystemName(){
		return "CubeCraft";
	}
	
	//These methods let us add custom GUI parameters and respond to their events
    void selfSetupGui();
    void selfGuiEvent(ofxUIEventArgs &e);
    
	//Use system gui for global or logical settings, for exmpl
    void selfSetupSystemGui();
    void guiSystemEvent(ofxUIEventArgs &e);
    
	//use render gui for display settings, like changing colors
    void selfSetupRenderGui();
    void guiRenderEvent(ofxUIEventArgs &e);
	
	// selfSetup is called when the visual system is first instantiated
	// This will be called during a "loading" screen, so any big images or
	// geometry should be loaded here
    void selfSetup();
	
	void selfSetDefaults();
	
	// selfBegin is called when the system is ready to be shown
	// this is a good time to prepare for transitions
	// but try to keep it light weight as to not cause stuttering
    void selfBegin();
	
	// selfPresetLoaded is called whenever a new preset is triggered
	// it'll be called right before selfBegin() and you may wish to
	// refresh anything that a preset may offset, such as stored colors or particles
	void selfPresetLoaded(string presetPath);
    
	//do things like ofRotate/ofTranslate here
	//any type of transformation that doesn't have to do with the camera
    void selfSceneTransformation();
	
	//normal update call
	void selfUpdate();
	
	// selfDraw draws in 3D using the default ofEasyCamera
	// you can change the camera by returning getCameraRef()
    void selfDraw();
	
	// use this to draw the point cloud
	void selfDrawRGBD();
	
    // draw any debug stuff here
	void selfDrawDebug();
	
	//draws through RGBD camera;
	//	void selfDrawRGBD();
	
	// or you can use selfDrawBackground to do 2D drawings that don't use the 3D camera
	void selfDrawBackground();
	
	// this is called when your system is no longer drawing.
	// Right after this selfUpdate() and selfDraw() won't be called any more
	void selfEnd();
	
	// this is called when you should clear all the memory and delet anything you made in setup
    void selfExit();
	
	//events are called when the system is active
	//Feel free to make things interactive for you, and for the user!
    void selfKeyPressed(ofKeyEventArgs & args);
    void selfKeyReleased(ofKeyEventArgs & args);
    
    void selfMouseDragged(ofMouseEventArgs& data);
    void selfMouseMoved(ofMouseEventArgs& data);
    void selfMousePressed(ofMouseEventArgs& data);
    void selfMouseReleased(ofMouseEventArgs& data);
	
protected:
	
	void loadFileToGeometry( string loc, vector<ofVec3f>& points );
	
	void drawVoxelGrid();
	void drawCubeCraft();
	void updateAllColors();
	
	void resizeVoxelGrid();
	void loadShaders();
	void unloadShaders();
	
	void updateGroundMap();
	
	ofxUISuperCanvas* customGui;
	
	ofxUISuperCanvas* cubeGui;
	ofxUISuperCanvas* fogGui;
	ofxUISuperCanvas* meshRenderGui;
	ofxUISuperCanvas* mineCraftGui;
	
	int dimX, dimY, dimZ;
	int halfDimX, halfDimY, halfDimZ;
	ofMesh cubeMesh;
	ofVbo voxelVbo;
	int voxelIndexCount, cubeIndexCount;
	
	ofShader cubeCraftShader;
	ofShader voxelShader;
	ofShader mineCraftGroundShader;
	ofShader mineCraftCloudsShader;
	
	ofVec3f noiseDirection;
	float noiseTime, lastTime, speed;
	float noiseThreshold, noiseScale, edgeWidth;
	bool bFillCubes, bScaleCubes;
	
	float edgeSmoothing, cubeScale, specExpo, specScale;
	ofImage colorMap;
	ofColor edgeColor, fillColor, fillColor2, fogColor;
	float fogDist, fogExpo;
	int fogSaturation, fogHue, fogBrightness;
	bool bUseFog;
	
	bool bDrawVoxels, bDrawCubeCraft;
	
	
	float groundDrama, cloudThreshold, cloudHeight, cloudSpeed, cloudThickness, cloudShadow;
	
	ofColor groundColor;
	float groundHue, groundSaturation, groundBrightness;
	
	ofColor undergroundColor;
	float undergroundHue, undergroundSaturation, undergroundBrightness;
	
	ofColor cloudShadowColor;
	float cloudShadowHue, cloudShadowSaturation, cloudShadowBrightness;
	
//	ofImage groundMap;
	ofVec3f cameraOffset;
	
	ofFloatColor fc;
	
	int mineCraftDimX, mineCraftDimY;
	
	GLenum cullDirection;
};
