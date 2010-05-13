#include "testApp.h"

#define VERTEX_POSITION_ATTRIBUTE 0
#define TEXTURE_COORD_ATTRIBUTE 1
#define P_MATRIX_UNIFORM 2
#define MV_MATRIX_UNIFORM 3


GLfloat cubeVertexPosition[]={
	// Front face
	-1.0, -1.0,  1.0,
	1.0, -1.0,  1.0,
	1.0,  1.0,  1.0,
	-1.0,  1.0,  1.0,
	
	// Back face
	-1.0, -1.0, -1.0,
	-1.0,  1.0, -1.0,
	1.0,  1.0, -1.0,
	1.0, -1.0, -1.0,
	
	// Top face
	-1.0,  1.0, -1.0,
	-1.0,  1.0,  1.0,
	1.0,  1.0,  1.0,
	1.0,  1.0, -1.0,
	
	// Bottom face
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0, -1.0,  1.0,
	-1.0, -1.0,  1.0,
	
	// Right face
	1.0, -1.0, -1.0,
	1.0,  1.0, -1.0,
	1.0,  1.0,  1.0,
	1.0, -1.0,  1.0,
	
	// Left face
	-1.0, -1.0, -1.0,
	-1.0, -1.0,  1.0,
	-1.0,  1.0,  1.0,
	-1.0,  1.0, -1.0
	
};


GLfloat cubeVertexTextureCoord []= {
	// Front face
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,
	
	// Back face
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,
	0.0, 0.0,
	
	// Top face
	0.0, 1.0,
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	
	// Bottom face
	1.0, 1.0,
	0.0, 1.0,
	0.0, 0.0,
	1.0, 0.0,
	
	// Right face
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,
	0.0, 0.0,
	
	// Left face
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,
};

GLubyte cubeVertexIndices[] = {
	0, 1, 2,      0, 2, 3,    // Front face
	4, 5, 6,      4, 6, 7,    // Back face
	8, 9, 10,     8, 10, 11,  // Top face
	12, 13, 14,   12, 14, 15, // Bottom face
	16, 17, 18,   16, 18, 19, // Right face
	20, 21, 22,   20, 22, 23  // Left face
};



//--------------------------------------------------------------
void testApp::setup(){
	
	ofBackground(0, 0, 0);
	ofSetFrameRate(60);
	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
	
	ofDisableArbTex();
    neheTexture.loadImage("images/crate.gif");
	
	shader.loadShader("shaders/shader");
	
	
    glGenBuffersARB(2, &vboId[0]);
    
	
    //GET ATTRIBUTE AND UNIFORMS
	shader.setShaderActive(true);
	
	locationID[VERTEX_POSITION_ATTRIBUTE] = glGetAttribLocationARB(shader.shader, "aVertexPosition");
	locationID[TEXTURE_COORD_ATTRIBUTE] = glGetAttribLocationARB(shader.shader, "aTextureCoord");
    glEnableVertexAttribArray(locationID[VERTEX_POSITION_ATTRIBUTE]);
	glEnableVertexAttribArray(locationID[TEXTURE_COORD_ATTRIBUTE]);
	locationID[P_MATRIX_UNIFORM] = glGetUniformLocationARB(shader.shader, "uPMatrix");
	locationID[MV_MATRIX_UNIFORM] = glGetUniformLocationARB(shader.shader, "uMVMatrix");
	
	
		
   
	//SQUARE BUFFER 	
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexPosition)+sizeof(cubeVertexTextureCoord), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cubeVertexPosition), cubeVertexPosition);                            
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cubeVertexPosition), sizeof(cubeVertexTextureCoord), cubeVertexTextureCoord);
	
	//INDEX BUFFERS
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeVertexIndices), cubeVertexIndices, GL_STATIC_DRAW);
	
	
	//SETUP ROTATION AND Z VARS
	z=-5;
	xSpeed=ySpeed=0;
	
	//KEYS
	of_key_page_up_pressed=false;
	of_key_page_down_pressed=false;
	of_key_left_pressed=false;
	of_key_right_pressed=false;
	of_key_up_pressed=false;
	of_key_down_pressed=false;
	
	current_filter=0;
	
	verdana.loadFont("fonts/verdana.ttf",8, false, true);
	verdana.setLineHeight(14.0f);
	
}

//--------------------------------------------------------------
void testApp::setMatrixUniforms(){
	
    glGetFloatv (GL_PROJECTION_MATRIX, pMatrix);
	glGetFloatv (GL_MODELVIEW_MATRIX, mvMatrix);
	glUniformMatrix4fv(locationID[P_MATRIX_UNIFORM], 1,false, pMatrix);
    glUniformMatrix4fv(locationID[MV_MATRIX_UNIFORM], 1, false, mvMatrix);
}	
	
	
	
//--------------------------------------------------------------
void testApp::update(){

	xSpeed*=0.9;
	ySpeed*=0.9;
	xRot += xSpeed;
	yRot += ySpeed;
	
	checkForKeys();
}

//--------------------------------------------------------------
void testApp::draw() {

	setupScreenForLesson();
	
	shader.setShaderActive(true);
	
	glTranslatef(0.0, 0.0, z);
    glRotatef(xRot,1.0,0.0,0.0);
	glRotatef(yRot,0.0,1.0,0.0);
	
	
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
	glVertexAttribPointer(locationID[VERTEX_POSITION_ATTRIBUTE], 3, GL_FLOAT, false, 0, 0);	
	glVertexAttribPointer(locationID[TEXTURE_COORD_ATTRIBUTE], 2, GL_FLOAT, false, 0, (void*)sizeof(cubeVertexPosition));
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, vboId[1]);
	
	//SET TEXTURE
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, neheTexture.getTextureReference().getTextureData().textureID);
	shader.setUniformVariable1i((char*)"uSampler", 0);
	
	
	setMatrixUniforms();
	glDrawElements(GL_TRIANGLES, sizeof(cubeVertexIndices), GL_UNSIGNED_BYTE,0);
	
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	shader.setShaderActive(false);
	
	ofSetupScreen();
	ofSetColor(0xFFFFFF);
	verdana.drawString("* Page Up/Page Down to zoom out/in\n* Cursor keys: make the cube rotate\n* F to toggle through three different\n  kinds of texture filters", 5,15);
		

	
}


void testApp::setupScreenForLesson(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void testApp::checkForKeys(){

	if(of_key_page_up_pressed) z -= 0.1;
	if(of_key_page_down_pressed) z += 0.1; 
	if(of_key_left_pressed) ySpeed -= 0.5;
	if(of_key_right_pressed) ySpeed += 0.5;
	if(of_key_up_pressed) xSpeed -= 0.5;
	if(of_key_down_pressed) xSpeed += 0.5;

}

void testApp::updateTextureFilter(){
	switch(current_filter) {
		case 0:
			neheTexture.getTextureReference().setTextureMinMagFilter(GL_LINEAR,GL_LINEAR);
			break;
		case 1:
			neheTexture.getTextureReference().setTextureMinMagFilter(GL_NEAREST,GL_NEAREST);
			break;
		case 2:
			neheTexture.getTextureReference().setTextureMinMagFilter(GL_LINEAR_MIPMAP_NEAREST,GL_LINEAR);
			glGenerateMipmapEXT(GL_TEXTURE_2D);
			break;
	}

}


//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	switch(key) {
		case OF_KEY_PAGE_UP:
			of_key_page_up_pressed=true;
			break;
		case OF_KEY_PAGE_DOWN:
			of_key_page_down_pressed=true;
			break;
		case OF_KEY_LEFT:
			of_key_left_pressed=true;
			break;
		case OF_KEY_RIGHT:
			of_key_right_pressed=true;
			break;
		case OF_KEY_UP:
			of_key_up_pressed=true;
			break;
		case OF_KEY_DOWN:
			of_key_down_pressed=true;
			break;
		
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
	switch(key) {
		case OF_KEY_PAGE_UP:
			of_key_page_up_pressed=false;
			break;
		case OF_KEY_PAGE_DOWN:
			of_key_page_down_pressed=false;
			break;
		case OF_KEY_LEFT:
			of_key_left_pressed=false;
			break;
		case OF_KEY_RIGHT:
			of_key_right_pressed=false;
			break;
		case OF_KEY_UP:
			of_key_up_pressed=false;
			break;
		case OF_KEY_DOWN:
			of_key_down_pressed=false;
			break;
		case 102: //PRESS F
			current_filter=++current_filter%3;
			updateTextureFilter();
			break;
			
	}
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

