#include "testApp.h"

#define VERTEX_POSITION_ATTRIBUTE 0
#define VERTEX_COLOR_ATTRIBUTE 1
#define P_MATRIX_UNIFORM 2
#define MV_MATRIX_UNIFORM 3

GLfloat pyramidVertexPosition[]={
	// Front face
	0.0,  1.0,  0.0,
	-1.0, -1.0,  1.0,
	1.0, -1.0,  1.0,
	// Right face
	0.0,  1.0,  0.0,
	1.0, -1.0,  1.0,
	1.0, -1.0, -1.0,
	// Back face
	0.0,  1.0,  0.0,
	1.0, -1.0, -1.0,
	-1.0, -1.0, -1.0,
	// Left face
	0.0,  1.0,  0.0,
	-1.0, -1.0, -1.0,
	-1.0, -1.0,  1.0
	
};

GLfloat pyramidVertexColor []= {
	// Front face
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	// Right face
	1.0, 0.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	// Back face
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	// Left face
	1.0, 0.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	0.0, 1.0, 0.0, 1.0
	
};

GLfloat  cubeVertexPosition[]={
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

GLfloat cubeVertexColor []= {
	1.0, 0.0, 0.0, 1.0,     // Front face
	1.0, 0.0, 0.0, 1.0,     // Front face
	1.0, 0.0, 0.0, 1.0,     // Front face
	1.0, 0.0, 0.0, 1.0,     // Front face
	
	
	1.0, 1.0, 0.0, 1.0,     // Back face
	1.0, 1.0, 0.0, 1.0,     // Back face
	1.0, 1.0, 0.0, 1.0,     // Back face
	1.0, 1.0, 0.0, 1.0,     // Back face
	
	
	0.0, 1.0, 0.0, 1.0,     // Top face
	0.0, 1.0, 0.0, 1.0,     // Top face
	0.0, 1.0, 0.0, 1.0,     // Top face
	0.0, 1.0, 0.0, 1.0,     // Top face
	
	
	
	
	1.0, 0.5, 0.5, 1.0,     // Bottom face
	1.0, 0.5, 0.5, 1.0,     // Bottom face
	1.0, 0.5, 0.5, 1.0,     // Bottom face
	1.0, 0.5, 0.5, 1.0,     // Bottom face
	
	
	
	1.0, 0.0, 1.0, 1.0,     // Right face
	1.0, 0.0, 1.0, 1.0,     // Right face
	1.0, 0.0, 1.0, 1.0,     // Right face
	1.0, 0.0, 1.0, 1.0,     // Right face
	
	
	
	0.0, 0.0, 1.0, 1.0,     // Left face
	0.0, 0.0, 1.0, 1.0,     // Left face
	0.0, 0.0, 1.0, 1.0,     // Left face
	0.0, 0.0, 1.0, 1.0     // Left face
	
	
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
	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
	
	shader.loadShader("shaders/shader");
	
	
    glGenBuffersARB(3, &vboId[0]);
    
	
    //GET ATTRIBUTE AND UNIFORMS
	shader.setShaderActive(true);
	locationID[VERTEX_POSITION_ATTRIBUTE] = glGetAttribLocationARB(shader.shader, "aVertexPosition");
	locationID[VERTEX_COLOR_ATTRIBUTE] = glGetAttribLocationARB(shader.shader, "aVertexColor");
    glEnableVertexAttribArray(locationID[VERTEX_POSITION_ATTRIBUTE]);
	glEnableVertexAttribArray(locationID[VERTEX_COLOR_ATTRIBUTE]);
	locationID[P_MATRIX_UNIFORM] = glGetUniformLocationARB(shader.shader, "uPMatrix");
	locationID[MV_MATRIX_UNIFORM] = glGetUniformLocationARB(shader.shader, "uMVMatrix");
	shader.setShaderActive(false);
	
    //TRIANGLE BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertexPosition)+sizeof(pyramidVertexColor), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pyramidVertexPosition), pyramidVertexPosition);                            
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pyramidVertexPosition), sizeof(pyramidVertexColor), pyramidVertexColor);  
	
	
	
	//SQUARE BUFFER 	
	glBindBuffer(GL_ARRAY_BUFFER, vboId[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexPosition)+sizeof(cubeVertexColor), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cubeVertexPosition), cubeVertexPosition);                            
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cubeVertexPosition), sizeof(cubeVertexColor), cubeVertexColor);
	
	//INDEX BUFFERS
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeVertexIndices), cubeVertexIndices, GL_STATIC_DRAW);
	
	

	
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


}

//--------------------------------------------------------------
void testApp::draw() {

	setupScreenForLesson();
	
	shader.setShaderActive(true);
	
	
    glTranslatef(-1.5, 0.0, -8.0);
	
	glPushMatrix();
	glRotatef(rotTri, 0.0, 1.0, 0.0);
	
    
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
	glVertexAttribPointer(locationID[VERTEX_POSITION_ATTRIBUTE], 3, GL_FLOAT, false, 0, 0);
	glVertexAttribPointer(locationID[VERTEX_COLOR_ATTRIBUTE], 4, GL_FLOAT, false, 0, (void*)sizeof(pyramidVertexPosition));
	setMatrixUniforms();
	glDrawArrays(GL_TRIANGLES, 0, 12);
	
	glPopMatrix();
	
	
	
	glTranslatef(3.0, 0.0, 0.0);
	glPushMatrix();
	glRotatef(rotSquare, 1.0, 1.0, 1.0);
	
	glBindBuffer(GL_ARRAY_BUFFER, vboId[1]);
	glVertexAttribPointer(locationID[VERTEX_POSITION_ATTRIBUTE], 3, GL_FLOAT, false, 0, 0);	
	glVertexAttribPointer(locationID[VERTEX_COLOR_ATTRIBUTE], 4, GL_FLOAT, false, 0, (void*)sizeof(cubeVertexPosition));
	setMatrixUniforms();
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, vboId[2]);
	glDrawElements(GL_TRIANGLES, sizeof(cubeVertexIndices), GL_UNSIGNED_BYTE,0);
	glPopMatrix();
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	shader.setShaderActive(false);
	
	rotTri+=90 * 0.001;//float(ofGetEllapsedTimeMillis())/1000 + ofRandom(0,1) * PI;
	rotSquare-=75 * 0.001;
	
}




void testApp::setupScreenForLesson(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1.0, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

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

