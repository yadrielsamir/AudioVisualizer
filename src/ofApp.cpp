#include "ofApp.hpp"
//--------------------------------------------------------------
void ofApp::setup() {
    sound.load(songs[song_playing]);           // Loads a sound file (in bin/data/)
    sound.setLoop(true);              // Makes the song loop indefinitely
    sound.setVolume(1);               // Sets the song volume
}
//--------------------------------------------------------------
void ofApp::update() {
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */
    ofSoundUpdate();
    if (!paused){               // Updates all sound players
        visualizer.updateAmplitudes(); // Updates Amplitudes for visualizer
    }
    progress = sound.getPosition();

    //loop
    if (progress >= 0.99 && loop){
        if(song_playing < songs.size() - 1){
            changeSound(songs[song_playing + 1]);
            song_playing++;
        } else {
            song_playing = 0;
            changeSound(songs[song_playing]);
        }
    }

    //2x, 1.5x and 0.5x
    if (X2Enabled) {
        sound.setSpeed(2.0);
    } 
    else if (X0150Enabled){
        sound.setSpeed(1.5);
    }
    else if (X05Enabled) {
        sound.setSpeed(0.5);
    } 
    else {
        sound.setSpeed(1.0);
    }

    //repeat 
    if (progress >= 0.99 && repeat){
        changeSound(songs[song_playing]);
    }

    //shuffle
    if (shuffle){
        int random = ofRandom(songs.size());
        changeSound(songs[random]);
        song_playing = random;
        shuffle = false;
    }

    //shuffle message
    if ((timebool || timebool2) && ofGetElapsedTimef() - timeWhenFalse > 1){
            timebool = false;
            timebool2 = false;
        }
}
//--------------------------------------------------------------
void ofApp::draw() {
    /* The update method is called muliple times per second
    It's in charge of drawing all figures and text on screen */

    // Progress Bar
    ofFill();
    if (mode == '1') {
        ofSetColor(0, 0, 256);
    } 
    else if (mode == '2'){
        ofSetColor( 256, 18, 144);
    } 
    else if (mode == '3'){
        for (int i = 1; i < 16; i++){
        ofSetColor(ofColor::fromHsb(i * 10, 200, 125));
        }
    }
    ofDrawRectRounded(0, ofGetHeight() - 65 , sound.getPosition() * ofGetWidth() ,30,20);
    ofSetLineWidth(3);
    ofNoFill();
    ofDrawRectRounded( 0, ofGetHeight() - 65 , ofGetWidth() , 30 , 20 );      
    ofNoFill();

    // X2, X0.5 and X1.50 Buttons
    ofSetLineWidth(3);
    ofNoFill();
    ofDrawRectangle(ofGetWidth() - 37, ofGetHeight() - 90,  35, 20);
    ofDrawRectangle(ofGetWidth() - 85, ofGetHeight() - 90,  35, 20);
    ofDrawRectangle(ofGetWidth() - 133, ofGetHeight() - 90,  35, 20);

    //Control Button
    ofDrawRectangle(ofGetWidth() - 85, 20,  80, 35);   
    ofDrawBitmapString("Controls", ofGetWidth() - 77, 42);

    ofDrawBitmapString("2.0x", ofGetWidth() - 35, ofGetHeight() - 75);
    ofDrawBitmapString("1.5x", ofGetWidth() - 83, ofGetHeight() - 75);
    ofDrawBitmapString("0.5x", ofGetWidth() - 131, ofGetHeight() - 75);

    ofFill();
    if(control){
        ofDrawRectangle(ofGetWidth() - 85, 20,  80, 35);
        ofSetColor(256);
        ofDrawBitmapString("Controls", ofGetWidth() - 77, 42);
    }
    if (X2Enabled){
        ofDrawRectangle(ofGetWidth() - 37, ofGetHeight() - 90,  35, 20);
        ofSetColor(256);
        ofDrawBitmapString("2.0x", ofGetWidth() - 35, ofGetHeight() - 75);
    } 
    else if(X0150Enabled){
        ofDrawRectangle(ofGetWidth() - 85, ofGetHeight() - 90,  35, 20);
        ofSetColor(256);
        ofDrawBitmapString("1.5x", ofGetWidth() - 83, ofGetHeight() - 75);
    }
    else if(X05Enabled){
        ofDrawRectangle(ofGetWidth() - 133, ofGetHeight() - 90,  35, 20);
        ofSetColor(256);
        ofDrawBitmapString("0.5x", ofGetWidth() - 131, ofGetHeight() - 75);
    }
      
    
//white text------------------------------------------------------------------------------------------

    //Song % 
    ofSetColor(256);
    float pos = playing ? progress : lastPos;
    int percent = pos * 100;
    ofDrawBitmapString("Song Progress: " + ofToString(percent) + "%", 0, 30);

    //control button
    if (control){
        ofSetColor(0);
        ofFill();
        int x1 = ofGetWidth() / 2 - 195;
        int y1 = ofGetHeight() / 2;
        ofDrawRectangle(ofGetWidth() / 2 - 200, y1 - 185,  ofGetWidth() / 3, y1);
        ofSetColor(256);
        ofDrawBitmapString("EXIT", ofGetWidth() / 2 + 100, y1 - 160);
        ofDrawBitmapString("1. Pause animation: Press 'a'", x1, y1 - 170);
        ofDrawBitmapString("2. Loop songs: Press 'l'", x1, y1 - 155);
        ofDrawBitmapString("3. Repeat song: Press 'r'", x1, y1 - 140);
        ofDrawBitmapString("4. Random song: Press 'b'", x1, y1 - 125);
        ofDrawBitmapString("5. Play music 1: Press 'm'", x1, y1 - 110);
        ofDrawBitmapString("6. Play music 2: Press 'u'", x1, y1 - 95);
        ofDrawBitmapString("7. Play music 3: Press 's'", x1, y1 - 80);
        ofDrawBitmapString("8. Play music 4: Press 'i'", x1, y1 - 65);
        ofDrawBitmapString("9. Mode 1: Press '1'", x1, y1 - 50);
        ofDrawBitmapString("10. Mode 2: Press '2'", x1, y1 - 35);
        ofDrawBitmapString("11. Mode 3: Press '3'", x1, y1 - 20);
        ofDrawBitmapString("12. Mode 4: Press '4'", x1, y1 - 5);
        ofDrawBitmapString("13. Raise volume: Press '='", x1, y1 + 10);
        ofDrawBitmapString("14. Lower volume: Press '-'", x1, y1 + 25);
        
    }

    // Mode Selection
    if (!playing && cont) {
        ofTrueTypeFont font;
        font.load("COMIC.ttf", 20); 
        ofSetColor(255, 255, 255);
        font.drawString("Press 'p' to play some music!", ofGetWidth() / 2 - 185, ofGetHeight() / 2);
    }
    if (paused){
        ofDrawBitmapString("Animation: enabled", 0, 45);
    } else{
        ofDrawBitmapString("Animation: disabled", 0, 45);
    }
    if (loop){
        ofDrawBitmapString("Loop songs: enabled", 0, 60);
    } else{
        ofDrawBitmapString("Loop songs: disabled", 0, 60);
    }
    if (repeat){
        ofDrawBitmapString("Repeat song: enabled", 0, 75);
    } else{
        ofDrawBitmapString("Repeat song: disabled", 0, 75);
    }
    if (!shuffle && !timebool){
        ofDrawBitmapString("Random song: disabled", 0, 90);
    }
    if (timebool){
        ofDrawBitmapString("Random song: enabled", 0, 90);
    }
    if (timebool2){
        ofPushMatrix();
        ofTranslate(ofRandom(-2, 2), ofRandom(-2, 2));
        ofTrueTypeFont font;
        font.load("COMIC.ttf", 20);
        font.drawString("One mode at a time!!!!", ofGetWidth() / 2 - 185, 0 + 25);
        ofPopMatrix();
    }
//drawmodes-----------------------------------------------------------------------------------------------------------

    //Backgrounds
    vector<float> amplitudes = visualizer.getAmplitudes();
    if (!control){
        if (mode == '1' ) {
            drawMode1(amplitudes);
            ofSetBackgroundColor(70, 0, 0);
        } else if (mode == '2') {
            drawMode2(amplitudes);
            ofSetBackgroundColor(0, 0, 150);
        } else if (mode == '3') {
            drawMode3(amplitudes);
            ofSetBackgroundColor(0, 0, 0);
        }
    }

    ofSetColor(256);
    if (mode == '1' ) {
        ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
    } else if (mode == '2') {
        ofDrawBitmapString("Circle Radius Visualizer", 0, 15);
    } else if (mode == '3') {
        ofDrawBitmapString("Mixed Visualizer", 0, 15);
    }
    
    // ofDrawBitmapString("Current Mouse Position: " + ofToString(cur_x) + ", " + ofToString(cur_y), 0, 30);
}
    //Visualizer
void ofApp::drawMode1(vector<float> amplitudes) {
    ofFill();        // Drawn Shapes will be filled in with color
    ofSetColor(256); // This resets the color of the "brush" to white
    ofSetColor(0, 0, ofRandom(255));
    float width = (float)ofGetWidth() / (float)64;
    float x = 0;  
    for (int i = 0; i < amplitudes.size(); i++){
        ofDrawRectRounded(x, ofGetHeight() - 100, width, amplitudes[i], 5);
        x += width;
    }
}
void ofApp::drawMode2(vector<float> amplitudes) {
    ofSetLineWidth(5); // Sets the line width
    ofNoFill();        // Only the outline of shapes will be drawn
    ofSetColor(256);   // This resets the color of the "brush" to white
    int bands = amplitudes.size();
    for (int i = 0; i < bands; i++) {
        ofSetColor((bands - i) * 32 % 256, 18, 80); // Color varies between frequencies
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, amplitudes[0] / (i + 1));
    }
}
void ofApp::drawMode3(vector<float> amplitudes) {
    static float color = 0; 
    color += 0.5; 
    if (color >= 255) {
        color = 0;
    }
    ofSetLineWidth(5); 
    ofNoFill();      
    int bands = amplitudes.size();
    for (int i = 0; i < bands; i++) {
        ofSetColor(ofColor::fromHsb(color + (i * 10), 200, 200)); 
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, amplitudes[0] / (i + 1));
    }
    ofFill();       
    float width = (float)ofGetWidth() / (float)32;
    float x = 0;  
    float x2 = ofGetWidth() - width;
    for (int i = 0; i < 16; i++){
        ofSetColor(ofColor::fromHsb(color + (i * 10), 200, 125));
        ofDrawRectRounded(x, ofGetHeight() - 100, width, amplitudes[i], 10);
        x += width;
        ofDrawRectRounded(x2, ofGetHeight() - 100, width, amplitudes[i], 10);
        x2 -= width;
    }
}
//--------------------------------------------------------------
void ofApp::changeSound(const std::string& filename) {
    sound.load(filename);
    cont = false;
    sound.play();
    playing = true;
    sound.setLoop(true);              
}
//Allows 1 mode only--------------------------------------------------------------
void ofApp::onemode(char skey){
    if (mod == skey || !equal){
        equal = !equal;
        mod = skey;
        if(mod == 'l'){
            loop = !loop;
        }
        else if(mod == 'r'){
            repeat = !repeat;
        }
        else if(mod == 'a'){
            paused = !paused;
        }
        else if(mod == 'b'){
            shuffle = true;
            timebool = true;
            timeWhenFalse = ofGetElapsedTimef();
            equal = false;
        }
    } else {
        timebool2 = true;
        timeWhenFalse = ofGetElapsedTimef();
    }
}
//Modes--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    switch (key) {
        case 'p':
            cont = true;
            if (playing) {
                sound.stop();
            } else {
                sound.play();
            }
            playing = !playing;
            break;
        case 'a':
            onemode('a');
            break;
        case 'm':
            changeSound(songs[0]);
            song_playing = 0;
            break;
        case 'u':
            changeSound(songs[1]);
            song_playing = 1;
            break;
        case 's':
            changeSound(songs[2]);
            song_playing = 2;
            break;
        case 'i':
            changeSound(songs[3]);
            song_playing = 3;
            break;
        case 'l':
            onemode('l');
            break;
        case 'r':
            onemode('r');
            break;
        case 'b': 
            onemode('b');
            break;
        case '=':   
            sound.setVolume(min((float)1.0, sound.getVolume() + (float)0.1));
            break;
        case '-':    
            sound.setVolume(max((float)0.0, sound.getVolume() - (float)0.1));
            break;
        case '1':
            mode = '1';
            break;
        case '2':
            mode = '2';
            break;
        case '3':
            mode = '3';
            break;
    }
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    cur_x = x;
    cur_y = y;
}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    if (y > ofGetHeight() - 65 && y < ofGetHeight() - 35) {
        float newProgress = ofMap(x, 0, ofGetWidth(), 0, 1, true);
        sound.setPosition(newProgress);
    } 
    if(y>ofGetHeight() - 65 && y < ofGetHeight() - 35){
        float newProgress = ofMap(x,0,ofGetWidth(), 0, 1, true);
        sound.setPosition(newProgress);
    }

}
//Buttons--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    if (x > ofGetWidth() - 37 && x < ofGetWidth() - 2 && y > ofGetHeight() - 91 && y < ofGetHeight() - 70 && playing) {   //2.0x
        X2Enabled = !X2Enabled;
        X05Enabled = false;
        X0150Enabled = false;
    }
    if (x > ofGetWidth() - 85 && x < ofGetWidth() - 50 && y > ofGetHeight() - 90 && y < ofGetHeight() - 70) {   //1.5x
        X0150Enabled = !X0150Enabled;
        X05Enabled = false;
        X2Enabled = false;
    }
    if (x > ofGetWidth() - 133 && x < ofGetWidth() - 98 && y > ofGetHeight() - 90 && y < ofGetHeight() - 70) {   //0.5x
        X05Enabled = !X05Enabled;
        X2Enabled = false;
        X0150Enabled = false;
    } 
    if (x > ofGetWidth() - 85 && x < ofGetWidth() - 5 && y > 20 && y < 55) {   //Control
        control = true;  
        cont = false;
        sound.stop();
    }       
    if (x > ofGetWidth() / 2 + 90 && x < ofGetWidth() / 2 + 140 && ofGetHeight() / 2 - 80 && ofGetHeight() / 2 - 40){   //Exit
        if (playing){
            sound.play();
        } else {
            playing = false;
        }
        control = false;
        cont = true;
    }
}