#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	for (int i = 0; i < 80; i++) {

		this->noise_seed_list.push_back(glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000)));
		this->noise_step_list.push_back(ofRandom(1000));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int i = 0; i < this->noise_seed_list.size(); i++) {

		int param = int(ofRandom(120) + ofGetFrameNum()) % 120;
		int len = param < 60 ? ofMap(param, 0, 60, 30, 1) : ofMap(param, 60, 120, 1, 30);

		vector<glm::vec3> vertices;
		for (int k = 0; k < len; k++) {

			auto location = glm::vec3(
				ofMap(ofNoise(this->noise_seed_list[i].x, this->noise_step_list[i] + k * 0.003), 0, 1, -350, 350),
				ofMap(ofNoise(this->noise_seed_list[i].y, this->noise_step_list[i] + k * 0.003), 0, 1, -350, 350),
				ofMap(ofNoise(this->noise_seed_list[i].z, this->noise_step_list[i] + k * 0.003), 0, 1, -350, 350));

			vertices.push_back(location);
		}

		ofNoFill();
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape();

		ofFill();
		ofDrawSphere(vertices.front(), 5);
		ofDrawSphere(vertices.back(), 5);

		this->noise_step_list[i] += 0.003;
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}