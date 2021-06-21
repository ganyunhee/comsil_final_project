#pragma once

#include "ofMain.h"
#include "ofxWinMenu.h" // Menu Add-On

class ofApp : public ofBaseApp{

	public:
		// Functions Used
		void setup();				// example function (edited)
		void draw();				// example function (edited)
		void saveScreenshot();		// user-defined
		void keyPressed(int key);	// example function (edited)

		void update();
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		// Windows Dialog Menu
		ofxWinMenu* menu; // Menu object
		void appMenuFunction(string title, bool bChecked); // Menu return function

		// Used by example app
		ofTrueTypeFont myFont;
		ofImage myImage;
		float windowWidth, windowHeight;
		HWND hWnd;				// Application window
		HWND hWndForeground;	// current foreground window

		// Options Menu Variables
		
		bool bSingleBrush;
		bool bGradientBrush;
		bool bScatterBrush;
		bool bGlowingBrush;

		// Example menu variables
		bool bShowInfo;
		bool bFullscreen;
		bool bTopmost;

		// Example functions
		void doFullScreen(bool bFull);
		void doTopmost(bool bTop);

};
