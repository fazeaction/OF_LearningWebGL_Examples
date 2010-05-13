#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxShader.h"



class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void setupScreenForLesson();
	void setMatrixUniforms();
	void checkForKeys();
	void updateTextureFilter();

	GLuint	vboId[2];
	GLint locationID[4];
	GLfloat pMatrix[16];
	GLfloat mvMatrix[16];
	int current_filter;
	
	float xRot;
	float xSpeed;
	
	float yRot;
	float ySpeed;
	
	float z;
	
	bool of_key_page_up_pressed;
	bool of_key_page_down_pressed;
	bool of_key_left_pressed;
	bool of_key_right_pressed;
	bool of_key_up_pressed;
	bool of_key_down_pressed;
	

	ofImage neheTexture;
	ofTrueTypeFont	verdana;
	ofxShader	shader;
	

};

#endif
