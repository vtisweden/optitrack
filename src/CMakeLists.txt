# Target name
SET(TARGET_LIBRARYNAME OptiTrack)
SET(TARGET_TARGETNAME OptiTrackExample)

# Target source files
SET(TARGET_LIB_SRC
	optitrack.cpp
)

# Target headerfiles
SET(TARGET_LIB_H
	optitrack.h
)

#####################################################################
# Create library
#####################################################################

ADD_LIBRARY(${TARGET_LIBRARYNAME} ${TARGET_LIB_SRC} ${TARGET_LIB_H})

#####################################################################
# Create example executable
#####################################################################

ADD_EXECUTABLE(${TARGET_TARGETNAME} main.cpp)
TARGET_LINK_LIBRARIES(${TARGET_TARGETNAME} ${TARGET_LIBRARYNAME})


#####################################################################
# Linker options
#####################################################################

# Link to optitrack libs
TARGET_LINK_LIBRARIES(${TARGET_TARGETNAME}  ${OPTITRACK_SDK_LIBRARIES} )

####################################################################
# Create user file for correct environment string
#####################################################################
		
IF(WIN32)
    IF(MSVC)
		IF (OPTITRACK_SDK_FOUND)
			# Build path
			SET(USERFILE_ENVIRONMENT_DEBUG "PATH=")
			SET(USERFILE_ENVIRONMENT_RELEASE "PATH=")

			# Add location of needed dll files to path
			SET(USERFILE_ENVIRONMENT_DEBUG "${USERFILE_ENVIRONMENT_DEBUG}${OPTITRACK_SDK_BIN_DIRS}")
			SET(USERFILE_ENVIRONMENT_RELEASE "${USERFILE_ENVIRONMENT_RELEASE}${OPTITRACK_SDK_BIN_DIRS}")

			# For visual studio 2010 (MSVC10), 2012 (MSVC11) and 2013 (MSVC12)
			IF(MSVC10 OR MSVC11 OR MSVC12)
				CONFIGURE_FILE(optitrack.vcxproj.template ${TARGET_TARGETNAME}.vcxproj.user @ONLY)
			ENDIF()

		ENDIF (OPTITRACK_SDK_FOUND)
    ENDIF(MSVC)
ENDIF(WIN32)
