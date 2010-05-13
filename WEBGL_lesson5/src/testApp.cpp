#include "testApp.h"

#define VERTEX_POSITION_ATTRIBUTE 0
#define VERTEX_TEXTURE_COORD 1
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
	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
	
	ofDisableArbTex();
    neheTexture.loadImage("images/nehe.gif");
	
	shader.loadShader("shaders/shader");
	
	
    glGenBuffersARB(2, &vboId[0]);
    
	
    //GET ATTRIBUTE AND UNIFORMS
	shader.setShaderActive(true);
	
	locationID[VERTEX_POSITION_ATTRIBUTE] = glGetAttribLocationARB(shader.shader, "aVertexPosition");
	locationID[VERTEX_TEXTURE_COORD] = glGetAttribLocationARB(shader.shader, "aTextureCoord");
    glEnableVertexAttribArray(locationID[VERTEX_POSITION_ATTRIBUTE]);
	glEnableVertexAttribArray(locationID[VERTEX_TEXTURE_COORD]);
	locationID[P_MATRIX_UNIFORM] = glGetUniformLocationARB(shader.shader, "uPMatrix");
	locationID[MV_MATRIX_UNIFORM] = glGetUniformLocationARB(shader.shader, "uMVMatrix");
	
	
	//SET TEXTURE
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, neheTexture.getTextureReference().getTextureData().textureID);
	shader.setUniformVariable1i((char*)"uSampler", 0);
	
	shader.setShaderActive(false);
	
   
	//SQUARE BUFFER 	
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexPosition)+sizeof(cubeVertexTextureCoord), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cubeVertexPosition), cubeVertexPosition);                            
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cubeVertexPosition), sizeof(cubeVertexTextureCoord), cubeVertexTextureCoord);
	
	//INDEX BUFFERS
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId[1]);
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
	
	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(rot, 1.0, 0.0, 0.0);
	glRotatef(rot, 0.0, 1.0, 0.0);
	glRotatef(rot, 0.0, 0.0, 1.0);

	
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
	glVertexAttribPointer(locationID[VERTEX_POSITION_ATTRIBUTE], 3, GL_FLOAT, false, 0, 0);	
	glVertexAttribPointer(locationID[VERTEX_TEXTURE_COORD], 2, GL_FLOAT, false, 0, (void*)sizeof(cubeVertexPosition));
	setMatrixUniforms();
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, vboId[1]);
	glDrawElements(GL_TRIANGLES, sizeof(cubeVertexIndices), GL_UNSIGNED_BYTE,0);
	glPopMatrix();
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	shader.setShaderActive(false);
	
	rot+=0.06;	
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

