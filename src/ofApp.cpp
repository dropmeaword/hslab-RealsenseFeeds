#include "ofApp.h"

// ////////////////////////////////////////////////////////////////
void ofApp::setup(){
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_NOTICE);

    acquiring = false;

    vector<string> ids = ofxRealsense::get_serials();
    if( ids.size() > 0 ) {
        // print all available IDs
        for(auto id : ids) {
            ofLogNotice() << "RealSense device found with ID " << id;
        }

        ofLogNotice() << "Initializing first available camera with ID " << ids[0];
        ofxRealsense_Settings cfg;
        cfg.depth_w = 848;
        cfg.depth_h = 480;
        cfg.depth_fps = 30;
        cfg.rgb_w = 1920;
        cfg.rgb_h = 1080;
        cfg.rgb_fps = 30;

        rscam.setup(ids[0], cfg);
    } else {
        ofLogWarning() << "No RealSense cameras detected, plug one and try again!";
    }
}

// ////////////////////////////////////////////////////////////////
void ofApp::update() {
    rscam.update();
}

// ////////////////////////////////////////////////////////////////
void ofApp::draw() {
    float scale = 0.5f;

    if ( !rscam.connected() ) return;

    rscam.get_depth_texture( depth );
    //rscam.get_ir_texture( color );
    rscam.get_color_texture( color );

    // draw color feed
    if ( color.isAllocated() ) {
        ofSetColor(255);
        color.draw(0, 0, color.getWidth() * scale, color.getHeight() * scale);
    }

    // draw depth feed
    if ( depth.isAllocated() ) {
        ofSetColor(255);
        depth.draw(ofGetWidth()/2, 0, depth.getWidth() * scale, depth.getHeight() * scale);
    }
}
