/*
 * optitrack.cpp
 *
 *  Created on: Aug 19, 2014
 *      Author: Bjorn Blissing
 */

#include "optitrack.h"
#include <iostream>

int OptiTrack::initialize()
{
	if (m_projectFile.empty()) {
		std::cerr << "Error: OptiTrack Project filename cannot be empty." << std::endl;
		return 1;
	}

	int errorCode = 0;
	// Try to initialize the OptiTrack system
	errorCode = checkResult(TT_Initialize());
	
	// Do an update to pick up any recently-arrived cameras.
	errorCode = checkResult(TT_Update());
	
	// Load project definition file
	errorCode = checkResult(TT_LoadProject(m_projectFile.c_str()));
	
	if (errorCode == NPRESULT_SUCCESS) {
		m_initialized = true;
		return 0;
	}

	return errorCode;
}

int OptiTrack::terminate() {
	int errorCode = checkResult(TT_Shutdown());

	errorCode = checkResult(TT_FinalCleanup());

	m_initialized = false;

	return 0;
}

size_t OptiTrack::getNumberOfCameras() const {
	if (m_initialized) {
		return TT_TrackableCount();
	}
	return 0;
}

size_t OptiTrack::getNumberOfRigidBodies() const {
	if (m_initialized) {
		return TT_TrackableCount();
	}
	return 0;
}

std::string OptiTrack::getNameOfCamera(int id) const {
	if (m_initialized) {
		if (id <= TT_TrackableCount()) {
			return std::string(TT_TrackableName(id));
		}
	}
	return std::string("");
}

std::string OptiTrack::getNameOfRigidBody(int id) const {
	if (m_initialized) {
		if (id <= TT_TrackableCount()) {
			return std::string(TT_TrackableName(id));
		}
	}
	return std::string("");
}

bool OptiTrack::getPosition(int rigidBodyId, float& x, float& y, float& z)
{
	if(m_initialized &&  TT_Update() == NPRESULT_SUCCESS ) {
		float qx, qy, qz, qw, yaw, pitch, roll;
		TT_TrackableLocation( rigidBodyId, &x, &y, &z, &qx, &qy, &qz, &qw, &yaw, &pitch, &roll);
		if( TT_IsTrackableTracked(rigidBodyId)) {
			return true;
		}
	}
	return false;
}

bool OptiTrack::getOrientation(int rigidBodyId, float& yaw, float& pitch, float& roll)
{
	if(m_initialized &&  TT_Update() == NPRESULT_SUCCESS ) {
		float x, y, z, qx, qy, qz, qw;
		TT_TrackableLocation( rigidBodyId, &x, &y, &z, &qx, &qy, &qz, &qw, &yaw, &pitch, &roll);
		if( TT_IsTrackableTracked(rigidBodyId)) {
			return true;
		}
	}
	return false;
}

bool OptiTrack::getOrientation(int rigidBodyId, float& qx, float& qy, float& qz, float& qw)
{
	if(m_initialized &&  TT_Update() == NPRESULT_SUCCESS ) {
		float x, y, z, yaw, pitch, roll;
		TT_TrackableLocation( rigidBodyId, &x, &y, &z, &qx, &qy, &qz, &qw, &yaw, &pitch, &roll);
		if( TT_IsTrackableTracked(rigidBodyId)) {
			return true;
		}
	}
	return false;
}

bool OptiTrack::getPositionAndOrientation(int rigidBodyId, float& x, float& y, float& z, float& yaw, float& pitch, float& roll)
{
	if(m_initialized &&  TT_Update() == NPRESULT_SUCCESS ) {
		float qx,qy,qz,qw;
		TT_TrackableLocation( rigidBodyId, &x, &y, &z, &qx, &qy, &qz, &qw, &yaw, &pitch, &roll);
		if( TT_IsTrackableTracked(rigidBodyId)) {
			return true;
		}
	}
	return false;
}

int OptiTrack::checkResult(int result) {
	if (result != NPRESULT_SUCCESS) {
		std::cerr << "Error: " << TT_GetResultString(result) << std::endl;
	}
	return result;
}
