#include "testApp.h"

#define VERTEX_POSITION_ATTRIBUTE 0
#define P_MATRIX_UNIFORM 1
#define MV_MATRIX_UNIFORM 2


//--------------------------------------------------------------
void testApp::setup(){

	ofBackground(0, 0, 0);
	
	shader.loadShader("shaders/shader");
	
	
    glGenBuffersARB(2, &vboId[0]);
    
	
    GLfloat triangleVertexPosition[]={
		0.0,  1.0,  0.0,
        -1.0, -1.0,  0.0,
		1.0, -1.0,  0.0
	};
	
	GLfloat squareVertexPosition[]={
		1.0,  1.0,  0.0,
        -1.0, 1.0,  0.0,
		1.0, -1.0,  0.0,
		-1.0, -1.0, 0.0
	};
	
	//GET ATTRIBUTE AND UNIFORMS
	shader.setShaderActive(true);
	locationID[VERTEX_POSITION_ATTRIBUTE] = glGetAttribLocationARB(shader.shader, "aVertexPosition");
    glEnableVertexAttribArray(locationID[VERTEX_POSITION_ATTRIBUTE]);
	locationID[P_MATRIX_UNIFORM] = glGetUniformLocationARB(shader.shader, "uPMatrix");
	locationID[MV_MATRIX_UNIFORM] = glGetUniformLocationARB(shader.shader, "uMVMatrix");
	
	shader.setShaderActive(false);
	
    //TRIANGLE BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertexPosition), triangleVertexPosition, GL_STATIC_DRAW);
	
	//SQUARE BUFFER 	
	glBindBuffer(GL_ARRAY_BUFFER, vboId[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertexPosition), squareVertexPosition, GL_STATIC_DRAW);
	
	
	

	
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
	
	
    glTranslatef(-1.5, 0.0, -7.0);
    
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
	glVertexAttribPointer(locationID[VERTEX_POSITION_ATTRIBUTE], 3, GL_FLOAT, false, 0, 0);
	setMatrixUniforms();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	
	glTranslatef(3.0, 0.0, 0.0);
	
	glBindBuffer(GL_ARRAY_BUFFER, vboId[1]);
	glVertexAttribPointer(locationID[VERTEX_POSITION_ATTRIBUTE], 3, GL_FLOAT, false, 0, 0);	
	setMatrixUniforms();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	shader.setShaderActive(false);

	
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

