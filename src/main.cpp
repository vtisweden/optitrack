/*
 * main.cpp
 *
 *  Created on: Aug 19, 2014
 *      Author: Bjorn Blissing
 */

#include "optitrack.h"
#include <iostream>
#include <cmath>

int main()
{
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;
	float lastX = x;
	float lastY = y;
	float lastZ = z;
	OptiTrack* tracker = new OptiTrack;
	// Load camera and rigid body definition must be done before initialization
	tracker->setProjectFile("project.ttp");
	tracker->initialize();
	
	std::cout << "Number of cameras: " << tracker->getNumberOfCameras() << std::endl;
	for (size_t i=0; i < tracker->getNumberOfCameras(); ++i) {
		std::cout << "Camera name (" << i << "): " << tracker->getNameOfCamera(i) << std::endl;
	}

	std::cout << "Number of rigid bodies: " << tracker->getNumberOfRigidBodies() << std::endl;
	for (size_t i=0; i < tracker->getNumberOfRigidBodies(); ++i) {
		std::cout << "Rigid body name (" << i << "): " << tracker->getNameOfRigidBody(i) << std::endl;
	}
	
 	while (true) {
		tracker->getPosition(0, x, y, z);
		std::cout << "Current position: Sensor: " << 1 << "\tx: " << x << "\ty: " << y << "\tz: " << z << std::endl;
		float dx = x - lastX;
		float dy = y - lastY;
		float dz = z - lastZ;
		float distance = sqrt((dx*dx) + (dy*dy) + (dz*dz));
		std::cout << "Distance since last measurement: " << distance << std::endl;
		lastX = x;
		lastY = y;
		lastZ = z;
		std::cin.ignore();
	}

	delete tracker;
	return 0;
}