/*
	DUPLICATE 'PAINT' PROGRAM
	made by 20201658 GAN EUNICE NELL

	FEATURES
	- Canvas / Screen : White Background (Color Editing - Not Yet Supported) ;
	- Dialog Menu (ofxWinMenu) :
			File > Save , Exit ;				// shows save and exit options

			Options >							// shows brush options
						Single Brush,			// Single Rectangle Brush
						Gradient Brush,			// Single Rectangle Gradient Brush
						Scatter Brush,			// Scatter Rectangle Brush
						Glowing Brush ;			// Glowing Circle Brush

			(Brush Colors : Grayscale - Not Yet Changeable)

			Help > About ;						// shows "about program" info
	- Input & Shortcuts :
			Keyboard --> 's' or 'S' for save screenshot, 'ESC' for exit ;
			Mouse --> 'Left Click' to draw, 'Right click' to erase all drawings ;

	OTHER
	- Coding Environment : openframeworks v0.11.2, C++ Visual Studio 2019
*/

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Basic Settings
	ofSetWindowTitle("'Paint'");	// Set Window title to 'Paint'
	ofSetFrameRate(60);				// Set frame rate to 60
	ofSetBackgroundAuto(false);		// disable Auto BG setting
	ofBackground(255, 255, 255);	// Set backround to white (255, 255, 255)

	// Get the window size for image loading
	//	** use in case of uploading images (Not Yet Supported)
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();

	// Centre on the screen
	ofSetWindowPosition((ofGetScreenWidth() - windowWidth) / 2, (ofGetScreenHeight() - windowHeight) / 2);

	// Load a font rather than the default
	myFont.loadFont("verdana.ttf", 12, true, true);

	// Window handle used for topmost function (Not Yet Supported)
	hWnd = WindowFromDC(wglGetCurrentDC());

	/* CREATE MENU USING ofxWinMenu */

	// A new menu object with a pointer to this class
	menu = new ofxWinMenu(this, hWnd);

	// Register an ofApp function that is called when a menu item is selected.
	// The function can be called anything but must exist. 
	// See the example "appMenuFunction".
	menu->CreateMenuFunction(&ofApp::appMenuFunction);

	// Create a window menu
	HMENU hMenu = menu->CreateWindowMenu();

	//
	// Create a "File" popup menu
	//
	HMENU hPopup = menu->AddPopupMenu(hMenu, "File");

	//
	// Add popup items to the File menu
	//
	
	// File popup menu item "Save"
	//	saves screenshot of canvas (can also be activated using keyboard shortcut : 's')
	menu->AddPopupItem(hPopup, "Save", false, false);

	// Final File popup menu item is "Exit"
	menu->AddPopupSeparator(hPopup);	// add seperator
	menu->AddPopupItem(hPopup, "Exit", false, false);
	

	//
	// Brushes Pop-Up Menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "Options");

	// FOR 'SHOW INFO' / 'TOPMOST' - Not Yet Supported
	//bShowInfo = true;  // screen info display on
	//bTopmost = false; // app is topmost

	
	bSingleBrush = true;
	menu->AddPopupItem(hPopup, "Single Brush", true); // Checked
	bGradientBrush = false;
	menu->AddPopupItem(hPopup, "Gradient Brush", false, true); // Not checked (default)
	bScatterBrush = false;
	menu->AddPopupItem(hPopup, "Scatter Brush", false, true);
	bGlowingBrush = false;
	menu->AddPopupItem(hPopup, "Glowing Brush", false, true);


	/* FOR FULLSCREEN VIEW - Not Yet Supported
	bFullscreen = false; // not fullscreen yet
	menu->AddPopupItem(hPopup, "Full screen", false, false); // Not checked and not auto-check
	*/

	//
	// Help popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "Help");
	menu->AddPopupItem(hPopup, "About", false, false); // No auto check

	// Set the menu to the window
	menu->SetWindowMenu();

	// Print text to console
	printf("Setup complete.\n");
	printf("Default Brush (Single Brush) Enabled.\n");

} // END SETUP

	//
	// Menu function
	//
	// This function is called by ofxWinMenu when an item is selected.
	// The title and state can be checked for required action.
	// 
void ofApp::appMenuFunction	(string title, bool bChecked) {
	//
	// File Menu
	//

	// Save Screenshot feature
	if (title == "Save") {
		saveScreenshot();
	}

	// Exit feature
	if (title == "Exit") {
		ofExit();
	}
	
	//
	// Brush Menu
	//
	if (title == "Single Brush") {
		// Disable / Uncheck other brushes

		//	if other brushes are enabled or checked //
		if (bGradientBrush == 1) {
			bGradientBrush = !bGradientBrush;
			menu->SetPopupItem("Gradient Brush", bGradientBrush);
		}
		if (bScatterBrush == 1) {
			bScatterBrush = !bScatterBrush;
			menu->SetPopupItem("Scatter Brush", bScatterBrush);
		}
		if (bGlowingBrush == 1) {
			bGlowingBrush = !bGlowingBrush;
			menu->SetPopupItem("Glowing Brush", bGlowingBrush);
		}

		// Enable / Check current brush

		bSingleBrush = bChecked;
		if (bSingleBrush == 1) printf("Enabled Single Brush.\n"); // Print text to console
		else printf("Disabled Single Brush.\n");
	}
	if (title == "Gradient Brush") {
		// Disable / Uncheck other brushes

		//	if other brushes are enabled or checked //
		if (bSingleBrush == 1) {
			bSingleBrush = !bSingleBrush;
			menu->SetPopupItem("Single Brush", bSingleBrush);
		}
		if (bScatterBrush == 1) {
			bScatterBrush = !bScatterBrush;
			menu->SetPopupItem("Scatter Brush", bScatterBrush);
		}
		if (bGlowingBrush == 1) {
			bGlowingBrush = !bGlowingBrush;
			menu->SetPopupItem("Glowing Brush", bGlowingBrush);
		}
		
		// Enable / Check current brush

		bGradientBrush = bChecked;
		printf("Enabled Gradient Brush.\n"); // Print text to console
	}
	if (title == "Scatter Brush") {
		// Disable / Uncheck other brushes

		//	if other brushes are enabled or checked //
		if (bSingleBrush == 1) {
			bSingleBrush = !bSingleBrush;
			menu->SetPopupItem("Single Brush", bSingleBrush);
		}
		if (bGradientBrush == 1) {
			bGradientBrush = !bGradientBrush;
			menu->SetPopupItem("Gradient Brush", bGradientBrush);
		}
		if (bGlowingBrush == 1) {
			bGlowingBrush = !bGlowingBrush;
			menu->SetPopupItem("Glowing Brush", bGlowingBrush);
		}
		
		// Enable / Check current brush

		bScatterBrush = bChecked;
		printf("Enabled Scatter Brush.\n"); // Print text to console
	}
	if (title == "Glowing Brush") {
		// Disable / Uncheck other brushes

		//	if other brushes are enabled or checked //
		if (bSingleBrush == 1) {
			bSingleBrush = !bSingleBrush;
			menu->SetPopupItem("Single Brush", bSingleBrush);
		}
		if (bGradientBrush == 1) {
			bGradientBrush = !bGradientBrush;
			menu->SetPopupItem("Gradient Brush", bGradientBrush);
		}
		if (bScatterBrush == 1) {
			bScatterBrush = !bScatterBrush;
			menu->SetPopupItem("Scatter Brush", bScatterBrush);
		}
		
		// Enable / Check current brush

		bGlowingBrush = bChecked;
		printf("Enabled Glowing Brush.\n"); // Print text to console
	}
	

	//
	// Help menu
	//
	if (title == "About") {
		ofSystemAlertDialog("'Paint' Program\n A Duplicate of MS Paint\n Or at least, a starting attempt on making such a program\n");
	}
} // END MENU FUNCTION

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() {

	// If the left mouse button is pressed... draw the ff

	// SINGLE RECTANGLE BRUSH
	if (bSingleBrush) {
		if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) { // If the left mouse button is pressed... 
			ofSetColor(50);
			ofSetRectMode(OF_RECTMODE_CENTER); 	ofDrawRectangle(ofGetMouseX(), ofGetMouseY(), 50, 50); // Draw a 50 x 50 rect centered over the mouse
		}
	} 
	// GRADIENT RECTANGLE BRUSH
	else if (bGradientBrush) {
		if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
			float randomColor = ofRandom(50, 255);
			ofSetColor(randomColor);
			ofSetRectMode(OF_RECTMODE_CENTER); 	ofDrawRectangle(ofGetMouseX(), ofGetMouseY(), 50, 50);
		}
	} 
	// BURST/SCATTER RECTANGLE BRUSH
	else if (bScatterBrush) {
		if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
			ofSetRectMode(OF_RECTMODE_CENTER);
			int numRects = 10;
			for (int r = 0; r < numRects; r++) {
				ofSetColor(ofRandom(50, 255));
				float width = ofRandom(5, 20);
				float height = ofRandom(5, 20);
				float xOffset = ofRandom(-40, 40);
				float yOffset = ofRandom(-40, 40);
				ofDrawRectangle(ofGetMouseX() + xOffset, ofGetMouseY() + yOffset, width, height);
			}
		}
	}

	// GLOWING CIRCLE BRUSH
	else if (bGlowingBrush) {
		int maxRadius = 100;  // Increase for a wider brush
		int radiusStepSize = 5;  // Decrease for more circles (i.e. a more opaque brush)
		int alpha = 3;  // Increase for a more opaque brush
		int maxOffsetDistance = 100;  // Increase for a larger spread of circles
		// draw smaller and smaller circles and layering (increasing) opaqueness
		if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
			for (int radius = maxRadius; radius > 0; radius -= radiusStepSize) {
				float angle = ofRandom(ofDegToRad(360.0));
				float distance = ofRandom(maxOffsetDistance);
				float xOffset = cos(angle) * distance;
				float yOffset = sin(angle) * distance;
				ofSetColor(132, alpha);
				ofDrawCircle(ofGetMouseX() + xOffset, ofGetMouseY() + yOffset, radius);
			}
		}
	}

	// If the right mouse button is pressed...
	if (ofGetMousePressed(OF_MOUSE_BUTTON_RIGHT)) {
		ofBackground(255);  // Erase the screen with a white background
	}
} // END DRAW FUNCTION

//--------------------------------------------------------------
void ofApp::saveScreenshot() {
	// SAVE SCREENSHOT FUNCTION
	// From section 1.ii.f, allowing you to save a screenshot by pressing the 's' key:
	glReadBuffer(GL_FRONT);

	// We use the timestamp here so that you can save multiple images without
	// overriding previous screenshots (i.e. each file has a unique name)
	ofSaveScreen("savedScreenshot_" + ofGetTimestampString() + ".png");

	printf("Screenshot Saved.\n"); // Print Text to Console
	ofSystemAlertDialog("Screenshot saved to \"\\bin\\data\" directory\n");
	// screenshot is saved in "\bin\data" directory
} // END SAVE SCREENSHOT FUNCTION

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// if 's' key is pressed ...

	if (key == 's' || key == 'S') {
		saveScreenshot();
	}
} // END KEYPRESSED FUNCTION

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
