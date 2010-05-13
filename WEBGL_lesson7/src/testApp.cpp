#include "testApp.h"

#define VERTEX_POSITION_ATTRIBUTE 0
#define TEXTURE_COORD_ATTRIBUTE 1
#define VERTEX_NORMAL_ATTRIBUTE 2
#define P_MATRIX_UNIFORM 3
#define MV_MATRIX_UNIFORM 4
#define NORMAL_MATRIX_UNIFORM 5


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

GLfloat cubeVertexNormal []= {
	// Front face
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	
	// Back face
	0.0,  0.0, -1.0,
	0.0,  0.0, -1.0,
	0.0,  0.0, -1.0,
	0.0,  0.0, -1.0,
	
	// Top face
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	
	// Bottom face
	0.0, -1.0,  0.0,
	0.0, -1.0,  0.0,
	0.0, -1.0,  0.0,
	0.0, -1.0,  0.0,
	
	// Right face
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	
	// Left face
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
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
	locationID[VERTEX_NORMAL_ATTRIBUTE] = glGetAttribLocationARB(shader.shader, "aVertexNormal");
    glEnableVertexAttribArray(locationID[VERTEX_POSITION_ATTRIBUTE]);
	glEnableVertexAttribArray(locationID[TEXTURE_COORD_ATTRIBUTE]);
	glEnableVertexAttribArray(locationID[VERTEX_NORMAL_ATTRIBUTE]);
	locationID[P_MATRIX_UNIFORM] = glGetUniformLocationARB(shader.shader, "uPMatrix");
	locationID[MV_MATRIX_UNIFORM] = glGetUniformLocationARB(shader.shader, "uMVMatrix");
	locationID[NORMAL_MATRIX_UNIFORM] = glGetUniformLocationARB(shader.shader, "uNMatrix");
	
	
	
	shader.setUniformVariable1i((char*)"uUseLighting", use_lighting=!use_lighting);
	
	shader.setUniformVariable3f((char*)"uAmbientColor",ambient_red_value=0.2,ambient_green_value=0.2,ambient_blue_value=0.2);
	
	lightDirection.set(0.0,0.0,1.0);
	shader.setUniformVariable3f((char*)"uLightingDirection", lightDirection.x,lightDirection.y,lightDirection.z);
	
   	shader.setUniformVariable3f((char*)"uDirectionalColor", direct_red_value=0.8,direct_green_value=0.8,direct_blue_value=0.8);
	
	shader.setShaderActive(false);
	
   
	//SQUARE BUFFER 	
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexPosition)+sizeof(cubeVertexTextureCoord)+sizeof(cubeVertexNormal), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cubeVertexPosition), cubeVertexPosition);                            
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cubeVertexPosition), sizeof(cubeVertexTextureCoord), cubeVertexTextureCoord);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cubeVertexPosition)+sizeof(cubeVertexTextureCoord), sizeof(cubeVertexNormal), cubeVertexNormal);
	
	//INDEX BUFFERS
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeVertexIndices), cubeVertexIndices, GL_STATIC_DRAW);
	
	
	//SETUP ROTATION AND Z VARS
	z=-7;
	xSpeed=ySpeed=0;
	
	//KEYS
	of_key_backspace_pressed=false;
	of_key_page_up_pressed=false;
	of_key_page_down_pressed=false;
	of_key_left_pressed=false;
	of_key_right_pressed=false;
	of_key_up_pressed=false;
	of_key_down_pressed=false;
	
	verdana.loadFont("fonts/verdana.ttf",8, false, true);
	verdana.setLineHeight(14.0f);
	
	
	

	
}

//--------------------------------------------------------------
void testApp::setMatrixUniforms(){
	
    glGetFloatv (GL_PROJECTION_MATRIX, pMatrix);
	glGetFloatv (GL_MODELVIEW_MATRIX, mvMatrix);
	glUniformMatrix4fv(locationID[P_MATRIX_UNIFORM], 1,false, pMatrix);
    glUniformMatrix4fv(locationID[MV_MATRIX_UNIFORM], 1, false, mvMatrix);
	
	ofxMatrix4x4 nMatrix;
	nMatrix=ofxMatrix4x4::getInverseOf((ofxMatrix4x4&) mvMatrix);
	nMatrix=ofxMatrix4x4::getTransposedOf((ofxMatrix4x4&) nMatrix);
		
	glUniformMatrix4fv(locationID[NORMAL_MATRIX_UNIFORM], 1, false, nMatrix.getPtr());
	
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
	
	glPushMatrix();
	glTranslatef(0.0, 0.0, z);
    glRotatef(xRot,1.0,0.0,0.0);
	glRotatef(yRot,0.0,1.0,0.0);
	
	
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
	glVertexAttribPointer(locationID[VERTEX_POSITION_ATTRIBUTE], 3, GL_FLOAT, false, 0, 0);	
	glVertexAttribPointer(locationID[TEXTURE_COORD_ATTRIBUTE], 2, GL_FLOAT, false, 0, (void*)sizeof(cubeVertexPosition));
	glVertexAttribPointer(locationID[VERTEX_NORMAL_ATTRIBUTE], 3, GL_FLOAT, false, 0, (void*)(sizeof(cubeVertexPosition)+sizeof(cubeVertexTextureCoord)));
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, vboId[1]);
	
	//SET TEXTURE
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, neheTexture.getTextureReference().getTextureData().textureID);
	shader.setUniformVariable1i((char*)"uSampler", 0);
	
	setMatrixUniforms();
	glDrawElements(GL_TRIANGLES, sizeof(cubeVertexIndices), GL_UNSIGNED_BYTE,0);
	glPopMatrix();	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	shader.setShaderActive(false);
	
	glPushMatrix();
	glTranslatef(0.0, 0.0, z);
		glPushMatrix();
		glRotatef(xRotLight,1.0,0.0,0.0);
		glRotatef(yRotLight,0.0,1.0,0.0);
		glTranslatef(0.0, 0.0, 2.0);
		glGetFloatv (GL_MODELVIEW_MATRIX, mvMatrix);
		lightDirection.set(mvMatrix[12],mvMatrix[13],mvMatrix[14]-z);
		glColor3f(1.0,1.0,1.0);
		glutSolidSphere(0.05,4,4);
		glPopMatrix();
	glPopMatrix();
	
	
	
	
	ofSetupScreen();
	ofSetColor(0xFFFFFF);
	verdana.drawString(	"* Page Up/Page Down to zoom out/in\n* Cursor keys: make the cube rotate\n* SpaceBar+Cursor keys: make the light rotate\n* L Key toggle light", 5,15);
	verdana.drawString(	"* QWE Keys: R-> "+ofToString(ambient_red_value,2)+" G-> "+ofToString(ambient_green_value,2)+" B-> "+ofToString(ambient_blue_value,2)+" COLOR AMBIENT LIGHT", 5,73);
	verdana.drawString(	"* ASD Keys: R-> "+ofToString(direct_red_value,2)+" G-> "+ofToString(direct_green_value,2)+" B-> "+ofToString(direct_blue_value,2)+" DIRECTIONAL LIGHT COLOR", 5,87);


	
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

	if(of_key_backspace_pressed){
		if(of_key_left_pressed) yRotLight -= 0.5;
		if(of_key_right_pressed) yRotLight += 0.5;
		if(of_key_up_pressed) xRotLight -= 0.5;
		if(of_key_down_pressed) xRotLight += 0.5;
		setPositionLight();
	}
	else
	{
		if(of_key_page_up_pressed) z -= 0.1;
		if(of_key_page_down_pressed) z += 0.1; 
		if(of_key_left_pressed) ySpeed -= 0.5;
		if(of_key_right_pressed) ySpeed += 0.5;
		if(of_key_up_pressed) xSpeed -= 0.5;
		if(of_key_down_pressed) xSpeed += 0.5;
	}

}

void testApp::setAmbientLightColor(){
	shader.setShaderActive(true);
	shader.setUniformVariable3f((char*)"uAmbientColor",ambient_red_value,ambient_green_value,ambient_blue_value);
	shader.setShaderActive(false);
}

void testApp::setDirectLightColor(){
	shader.setShaderActive(true);
	shader.setUniformVariable3f((char*)"uAmbientColor",direct_red_value,direct_green_value,direct_blue_value);
	shader.setShaderActive(false);
}

void testApp::setPositionLight(){
	shader.setShaderActive(true);
	lightDirection.normalize();
	shader.setUniformVariable3f((char*)"uLightingDirection", lightDirection.x,lightDirection.y,lightDirection.z);
    shader.setShaderActive(false);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	switch(key) {
		case 32: //SPACE BAR
			of_key_backspace_pressed=true;
			break;		
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
		//COLOR AMBIENT LIGHT -QWE Keys _RGB
		case 113:	//Q // R
			ambient_red_value=fmodf((ambient_red_value+=0.01),1.0);
			setAmbientLightColor();
			break;
		case 119:	//W // G
			ambient_green_value=fmodf((ambient_green_value+=0.01),1.0);
			setAmbientLightColor();
			break;
		case 101:	//E // B
			ambient_blue_value=fmodf((ambient_blue_value+=0.01),1.0);
			setAmbientLightColor();
			break;
		//COLOR DIRECTIONAL LIGHT -ASD Keys _RGB
		case 97:	//A // R
			direct_red_value=fmodf((direct_red_value+=0.01),1.0);
			setDirectLightColor();
			break;
		case 115:	//S // G
			direct_green_value=fmodf((direct_green_value+=0.01),1.0);
			setDirectLightColor();
			break;
		case 100:	//D // B
			direct_blue_value=fmodf((direct_blue_value+=0.01),1.0);
			setDirectLightColor();
			break;
	}
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	printf(">>> %i",key);
	switch(key) {
		case 32: //SPACE BAR
			of_key_backspace_pressed=false;
			break;	
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
		case 108:	// L
			shader.setShaderActive(true);
			shader.setUniformVariable1i((char*)"uUseLighting",use_lighting=!use_lighting);
			shader.setShaderActive(false);
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

