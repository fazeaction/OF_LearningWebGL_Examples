#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxShader.h"
#include "ofxVectorMath.h"


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
	void setAmbientLightColor();
	void setDirectLightColor();
	void setPositionLight();
	
	GLuint	vboId[2];
	GLint locationID[6];
	GLfloat pMatrix[16];
	GLfloat mvMatrix[16];
	
	
	float xRot;
	float xSpeed;
	
	float yRot;
	float ySpeed;
	
	float xRotLight;
	float yRotLight;
	
	float z;
	
	//AMBIENT COLOR VALUES
	float ambient_red_value;
	float ambient_green_value;
	float ambient_blue_value;
	
	//DIRECT LIGHT COLOR VALUES
	float direct_red_value;
	float direct_green_value;
	float direct_blue_value;
	
	//POSITION LIGTH
	float xpos;
	float ypos;
	float zpos;
	
	//ALPHA VALUE
	float alpha;
	
	bool of_key_backspace_pressed;
	bool of_key_page_up_pressed;
	bool of_key_page_down_pressed;
	bool of_key_left_pressed;
	bool of_key_right_pressed;
	bool of_key_up_pressed;
	bool of_key_down_pressed;
	bool use_lighting;
	bool blending;
	
	

	ofImage neheTexture;
	ofTrueTypeFont	verdana;
	ofxShader	shader;
	ofxVec3f lightDirection;
	
	
   	

};

#endif
