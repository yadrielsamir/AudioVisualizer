#pragma once

#include "AudioVisualizer.hpp"
#include "ofMain.h"

class ofApp : public ofBaseApp {

  private:
    ofSoundPlayer sound;
    AudioVisualizer visualizer;

    vector<string> songs = {"beat.wav", "geesebeat.wav", "pigeon-coo.wav", "rock-song.wav"};
    bool X2Enabled = false;
    bool X05Enabled = false; 
    bool X0150Enabled = false;
    
    bool timebool = false;
    bool timebool2 = false;
    bool control = false; 
    char mod = ' ';
    bool equal = false;
    int song_playing = 0;
    bool shuffle = false; 
    int timeWhenFalse = 0;
    bool repeat = false;
    bool loop = false;
    bool cont = true;
    bool playing = false;
    char mode = '1';
    bool paused = false;

    int cur_x, cur_y = 0;

    float progress = 0;
    float lastPos = 0;

  public:
    void setup();
    void update();
    void draw();

    void drawMode1(vector<float> amplitudes);
    void drawMode2(vector<float> amplitudes);
    void drawMode3(vector<float> amplitudes);

    void onemode(char skey);
    void changeSound(const std::string& filename);
    void keyPressed(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
};
