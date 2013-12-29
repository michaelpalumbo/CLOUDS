/* 
 WOW SUCH VISUAL
 VERY COPYRIGHT
 */


#pragma once

#include "CloudsVisualSystem.h"

#include "gCell.h"

class CloudsVisualSystemColony : public CloudsVisualSystem {
public:
    
    string getSystemName();
    
    void selfSetup();
    void selfSetupGuis();
    
    void selfAutoMode();
    void selfUpdate();
    void selfDrawBackground();
    void selfDraw();
    void selfDrawDebug();
    void selfSceneTransformation();
    
    void selfExit();
    void selfBegin();
    void selfEnd();
    
    void selfKeyPressed(ofKeyEventArgs & args);
    void selfKeyReleased(ofKeyEventArgs & args);
    
    void mouseDragged(ofMouseEventArgs & args);
    void mouseMoved(ofMouseEventArgs & args);
    void mousePressed(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);
    
    void selfSetupGui();
    void selfGuiEvent(ofxUIEventArgs &e);
    
    void selfSetupSystemGui();
    void guiSystemEvent(ofxUIEventArgs &e);
    
    void selfSetupRenderGui();
    void guiRenderEvent(ofxUIEventArgs &e);
    
    void selfPresetLoaded(string presetPath);
    
    
private:
    
    /*  SUCH PARAMS */
    cellParams params;
    bool levelSetMode;
    int numInitialCells;
    float translucenseCell, translucenseDish;
    ofVec4f kernelColor_high, kernelColor_low;

    /* MUCH PRIVATE */
    float kernel_maxValue;
    
    /* MUCH GEOMETRY */
    ofVboMesh   vbo;
    ofShader    noiseShader;
    ofShader    cellShader;
    ofShader    levelSet;
    ofShader    billboard;
    
    /* WOW VIDEO */
    ofFbo fbo_main, foodTexture;
    ofTexture sprite, grunge;
    ofImage grime;
    
    /* LOL DATA */
    colonyPartitionMap pMap;
    vector< cellPtr > cells;
    
    /* WOW UTILITY */
    void updateFoodTexture();
    bool areFbosAllocatedAndSized();
    void loadShaders();
    void reallocateFramebuffers();
    
    void clear();
    void populate();
};
