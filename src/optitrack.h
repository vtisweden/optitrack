/*
 * optitrack.h
 *
 *  Created on: Aug 19, 2014
 *      Author: Bjorn Blissing
 */
#ifndef _OPTITRACK_H_
#define _OPTITRACK_H_

#include <string>
#include <NPTrackingTools.h>

class OptiTrack {
	public:
		OptiTrack() : m_projectFile(""), m_initialized(false) {};
		~OptiTrack() { terminate(); }
		int initialize();
		int isInitialized() const { return m_initialized; }
		int terminate();
		void setProjectFile(std::string filename) { m_projectFile = filename; }
		bool getPosition(int rigidBodyId, float& x, float& y, float& z);
		bool getOrientation(int rigidBodyId, float& yaw, float& pitch, float& roll);
		bool getOrientation(int rigidBodyId, float& qx, float& qy, float& qz, float& qw);
		bool getPositionAndOrientation(int rigidBodyId, float& x, float& y, float& z, float& yaw, float& pitch, float& roll);
		bool getPositionAndOrientation(int rigidBodyId, float& x, float& y, float& z, float& qx, float& qy, float& qz, float& qw);
		size_t getNumberOfCameras() const;
		size_t getNumberOfRigidBodies() const;
		std::string getNameOfCamera(int id) const;
		std::string getNameOfRigidBody(int id) const;
	protected:
		int checkResult(int result);
		std::string m_projectFile;
	private:
		bool m_initialized;
};

#endif
