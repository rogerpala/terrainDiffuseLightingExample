#include "testApp.h"

#define USE_DIFFUSE_SHADER 0
#define USE_TRIANGLE_STRIPS 1

//--------------------------------------------------------------
void testApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(255, 255, 255);
	ofSetVerticalSync(false);
	ofEnableAlphaBlending();
	
	glEnable(GL_DEPTH_TEST);
		
	//we load a font and tell OF to make outlines so we can draw it as GL shapes rather than textures
	font.loadFont("type/verdana.ttf", 100, true, false, true, 0.4, 72);
	
	if(USE_DIFFUSE_SHADER)
		shader.load("shaders/diffuse.vert", "shaders/diffuse.frag");
	else 
		shader.load("shaders/noise.vert", "shaders/noise.frag");
	
	doShader = true;	
	

	
	int cols = 8;
	int rows = 8;
	
	// Mesh indices
	int totalQuads		= (cols-1) * (rows-1);
	int totalTriangles	= totalQuads * 2;
	int totalIndices	= (cols*2) * (rows-1);
	cout << "total number of quads: " << totalQuads << endl;
	cout << "total number of triangles: " << totalTriangles << endl;
	cout << "total number of indices: " << totalIndices << endl;
	
	int n	= 0;
	int colSteps = cols * 2;
	int rowSteps = rows - 1;
	vector<int> indices;
	for ( int r = 0; r < rowSteps; r++ ) {
		for ( int c = 0; c < colSteps; c++ ) {
			int t = c + r * colSteps;
			
			if ( c == colSteps - 1 ) {
				indices.push_back( n );
			}
			else {
				indices.push_back( n );
				
				( t%2 == 0 ) ? n += cols : (r%2 == 0) ? n -= (cols-1) : n -= (cols+1);
			}
		}
	}
	
	
	
	
	
	for ( int a = 0; a < indices.size(); a++ ) {
		if(USE_TRIANGLE_STRIPS) mesh.addIndex( indices[a] );
	}
	
	int spaceX = 100;
	int spaceY = 100;

	for ( int y = 0; y < rows; y++ ) {
		for ( int x = 0; x < cols; x++ ) {

			ofVec3f point( x * spaceX, y * spaceY, ofRandom(200) );
			mesh.addVertex( point );
			
		}
	}
	
	vector<ofVec3f> triangleVertices;
	vector<ofVec3f> triangleNormals;
	
	vector<int> triangleVerticesIndices;
	vector< vector<int> > vectorTriangleVerticesIndices;
	
	int l = 0;
	for (int h = 0; h < indices.size(); h++) {
		triangleVertices.clear();
		triangleVerticesIndices.clear();
		
		if (l == cols * 2 - 2) {
			h+= 2;
			l = 0;
		}
		
		triangleVertices.push_back( mesh.getVertex(indices[h]) );
		triangleVertices.push_back( mesh.getVertex(indices[h+1]) );
		triangleVertices.push_back( mesh.getVertex(indices[h+2]) );
		
		ofVec3f normal = getNormalFromTriangleVertices(triangleVertices);
		triangleNormals.push_back(normal);
		
		triangleVerticesIndices.push_back( indices[h] );
		triangleVerticesIndices.push_back( indices[h+1] );
		triangleVerticesIndices.push_back( indices[h+2]);
		vectorTriangleVerticesIndices.push_back(triangleVerticesIndices);
		
		if(!USE_TRIANGLE_STRIPS){
			mesh.addIndex(indices[h]);
			mesh.addIndex(indices[h+1]);
			mesh.addIndex(indices[h+2]);
		}

		if (indices[h+2] == (cols * rows - 1)) {
			break;
		}
		l++;
		
	}
	
	
	vector<ofVec3f> averageNormals;
	for (int k = 0; k < mesh.getNumVertices(); k++) {
		vector<ofVec3f> normalsVector;
		for (int i = 0; i < vectorTriangleVerticesIndices.size(); i++) {
			for ( int j = 0; j < 3; j++ ) {
				if(vectorTriangleVerticesIndices[i][j] == k){
					normalsVector.push_back(triangleNormals[i]);
				}
			}
		}
		ofVec3f sumNormals;
		for (int h = 0; h < normalsVector.size(); h++) {
			sumNormals += normalsVector[h];
		}
		averageNormals.push_back(sumNormals / normalsVector.size());
	}
	
	mesh.addNormals(averageNormals);
	
	
	
	int colorCount = 0;
	
	for ( int y = 0; y < rows; y++ ) {
		for ( int x = 0; x < cols; x++ ) {
			
	
			if (colorCount % 3 == 0) {
				mesh.addColor(ofFloatColor(0.0, 1.0, 1.0, 1.0));
			}else if( colorCount % 2 == 0){
				mesh.addColor(ofFloatColor(1.0, 0.0, 1.0, 1.0));
			}else {
				mesh.addColor(ofFloatColor(1.0, 1.0, 0.0, 1.0));
			}
			
			//mesh.addColor(ofFloatColor(0.0, 0.5, 0.0, 1.0));

			colorCount++;
			
		}
	}
	
	
	
	vbo.setMesh(mesh, GL_DYNAMIC_DRAW);
	
	
	//////// TRACE //////
	
	cout << "///////// TRACE ///////// " << endl;
	
	cout << "NUM VERTEX: " << mesh.getNumVertices() << endl;
	int i;
	for (i = 0; i < mesh.getNumVertices(); i++) {
		cout << "		Vertex " << i << ": " << mesh.getVertex(i) << endl;
	}
	cout << endl;
	
	cout << "NUM INDICES: " << mesh.getNumIndices() << endl;
	for (i = 0; i < mesh.getNumIndices(); i++) {
		cout << "		Index " << i << ": " << mesh.getIndex(i) << endl;
	}
	cout << endl;
	
	cout << "NUM VERTEX NORMALS: " << mesh.getNumNormals() << endl;

	for (i = 0; i < mesh.getNumNormals(); i++) {
		cout << "		Vertex Normal " << i << ": " << mesh.getNormal(i) << endl;
	}
	cout << endl;
	
	cout << "NUM TRIANGLES: " << vectorTriangleVerticesIndices.size() << endl;
	
	for (i = 0; i < vectorTriangleVerticesIndices.size(); i++) {
		cout << "		Triangle " << i << ": " << vectorTriangleVerticesIndices[i][0] << " , " << vectorTriangleVerticesIndices[i][1] << " , " << vectorTriangleVerticesIndices[i][2] << " , " << endl;
	}
	cout << endl;
	
	cout << "NUM TRIANGLE NORMALS: " << triangleNormals.size() << endl;
	
	for (i = 0; i < triangleNormals.size(); i++) {
		cout << "		Triangle " << i << " Normal: " << triangleNormals[i] << endl;
	}
	cout << endl;
	
	cout << "//////// END TRACE ////// " << endl;
	
	
	
	
	 
	
	
	gui.addTitle("VIDEO SETTINGS");
	gui.addSlider("lightX", lightX, -3000, 3000);
	gui.addSlider("lightY", lightY, -3000, 3000);
	gui.addSlider("lightZ", lightZ, -3000, 3000);
	
	gui.addSlider("viewX", viewX, -3000, 3000);
	gui.addSlider("viewY", viewY, -3000, 3000);
	gui.addSlider("viewZ", viewZ, -3000, 3000);
	gui.addToggle("isRotatingActive", isRotatingActive);
	gui.loadFromXML();
	gui.show();
	
}

ofVec3f testApp::getNormalFromTriangleVertices(vector<ofVec3f> triangleVertices)
{
    // now is same as RedBook (OpenGL Programming Guide)
    ofVec3f u = triangleVertices[0] - triangleVertices[1];
    ofVec3f v = triangleVertices[1] - triangleVertices[2];
	
	/*cout << " triangleVertices[0].x: " << triangleVertices[0].x << " triangleVertices[0].y: " << triangleVertices[0].y << " triangleVertices[0].z: " << triangleVertices[0].z << endl;
	cout << " triangleVertices[1].x: " << triangleVertices[1].x << " triangleVertices[1].y: " << triangleVertices[1].y << " triangleVertices[1].z: " << triangleVertices[1].z << endl;
	cout << " triangleVertices[2].x: " << triangleVertices[2].x << " triangleVertices[2].y: " << triangleVertices[2].y << " triangleVertices[2].z: " << triangleVertices[2].z << endl;
	
	
	cout << " u.x: " << u.x << " u.y: " << u.y << " u.z: " << u.z << endl;
	cout << " v.x: " << v.x << " v.y: " << v.y << " v.z: " << v.z << endl;*/
	
	ofVec3f normal = u.getPerpendicular(v);
	//cout << " normal.x: " << normal.x << " normal.y: " << normal.y << " normal.z: " << normal.z << endl;
    return normal;
}


//--------------------------------------------------------------
void testApp::update(){
	//light.setPosition(0, 100 * sin(ofGetElapsedTimef()), -150);

}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(225);
	ofDrawBitmapString("'s' toggles shader", 10, 20);

	ofSetColor(245, 58, 135);
	ofFill();
	
	ofPushMatrix();
	//glEnable(GL_LIGHTI)
	
	if( doShader ){
		shader.begin();
			
		if(USE_DIFFUSE_SHADER){
			//we also pass in the mouse position 
			//we have to transform the coords to what the shader is expecting which is 0,0 in the center and y axis flipped. 
			shader.setUniform2f("mouse", mouseX - ofGetWidth()/2, ofGetHeight()/2-mouseY );
			shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1 );
			shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.18 );
			shader.setUniform4f("lightPosition", lightX, lightY, lightZ, 0.0);
			//we also pass in the mouse position 
			//we have to transform the coords to what the shader is expecting which is 0,0 in the center and y axis flipped. 
			shader.setUniform2f("mouse", mouseX - ofGetWidth()/2, ofGetHeight()/2-mouseY );
			shader.setUniform1i("applyLighting", 1);
		}else{
			//we want to pass in some varrying values to animate our type / color 
			shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1 );
			shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.18 );
			shader.setUniform3f("lightDirection", lightX, lightY, lightZ);
			shader.setUniform3f("viewPosition", viewX, viewY, viewZ);
			shader.setUniform4f("lightAmbientColor", 0.3, 0.1, 0.2, 1.0);
			shader.setUniform4f("lightDiffuseColor", 0.5, 0.2, 0.0, 1.0);
			shader.setUniform4f("lightSpecularColor", 0.6, 0.3, 0.3, 1.0);
			
			shader.setUniform4f("materialAmbientColor", 0.4, 0.8, 0.0, 1.0);
			shader.setUniform4f("materialDiffuseColor", 0.1, 0.0, 0.1, 1.0);
			shader.setUniform4f("materialSpecularColor", 0.3, 0.0, 0.5, 1.0);
			shader.setUniform1f("shininess", 2.0);
		}
		
		
			
	}
	
	
	
	if(!USE_DIFFUSE_SHADER){
		ofTranslate(ofGetWidth() / 4, ofGetHeight() / 4, 0);
		
		if(isRotatingActive){
			rotationX = mouseY;
			rotationY = mouseX;
		}
		
		ofRotateX(rotationX);
		ofRotateY(rotationY);
		
		
	}else{
		ofTranslate(ofGetWidth() / 3, ofGetHeight() / 3, 0);
	}
	
	
		//finally draw our text
		//font.drawStringAsShapes("openFrameworks", 90, 260);
	
	mesh.drawWireframe();
	
	//ofSphere(200, 200, 0, 200);
	
	
	
	if( doShader ){
		
		//vbo.draw(GL_QUAD_STRIP, 0, 4 * 100);
		if(USE_TRIANGLE_STRIPS)
			vbo.drawElements(GL_TRIANGLE_STRIP, mesh.getNumIndices());
		else 
			vbo.drawElements(GL_TRIANGLES, mesh.getNumIndices());
		
		shader.end();
	}
	ofPopMatrix();
	
	gui.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	if( key == 's' ){
		doShader = !doShader;
	}
	
	if( key == 'r' ){
		isRotatingActive = !isRotatingActive;
	}
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

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

