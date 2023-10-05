#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(250, 7);
	this->mesh = ico_sphere.getMesh();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clearColors();
	this->noise_param = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.035), 0, 1, 0.0005, 0.02);
	this->noise_param = 0.00085;

	ofColor color;
	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		auto noise_value = ofMap(ofNoise(
			this->mesh.getVertex(i).x * this->noise_param,
			this->mesh.getVertex(i).y * this->noise_param + ofGetFrameNum() * 0.01), 0, 1, 0, 10,
			this->mesh.getVertex(i).z * this->noise_param);
		int int_noise_value = (int)noise_value;

		noise_value = noise_value - int_noise_value;
		auto value = ofMap(abs(noise_value - 0.5), 0, 0.5, 0, 255);
		auto alpha = ofMap(abs(noise_value - 0.5), 0, 0.5, 0, 255);
		color = ofColor(value, alpha);
		this->mesh.addColor(color);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(-27);

	this->mesh.drawFaces();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}