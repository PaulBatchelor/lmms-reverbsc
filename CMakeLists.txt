CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7)
PROJECT(lmms)
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})


IF(WANT_QT5)
	SET(QT5 TRUE)

	FIND_PACKAGE(Qt5Core REQUIRED)
	FIND_PACKAGE(Qt5Gui REQUIRED)
	FIND_PACKAGE(Qt5LinguistTools)
	FIND_PACKAGE(Qt5Widgets REQUIRED)
	FIND_PACKAGE(Qt5Xml REQUIRED)

	INCLUDE_DIRECTORIES(
		${Qt5Core_INCLUDE_DIRS}
		${Qt5Gui_INCLUDE_DIRS}
		${Qt5Widgets_INCLUDE_DIRS}
		${Qt5Xml_INCLUDE_DIRS}
	)

	SET(QT_LIBRARIES
		Qt5::Core
		Qt5::Gui
		Qt5::Widgets
		Qt5::Xml
	)

	FIND_PACKAGE(Qt5Test)
	SET(QT_QTTEST_LIBRARY Qt5::Test)
ELSE()
	SET(QT5 FALSE)

	# check for Qt4
	SET(QT_MIN_VERSION "4.6.0" COMPONENTS QtCore QtGui QtXml)
	FIND_PACKAGE(Qt4 REQUIRED)
	SET(QT_USE_QTXML 1)
	IF(WIN32)
		SET(QT_TRANSLATIONS_DIR "${MINGW_PREFIX}/share/qt4/translations/")
	ENDIF(WIN32)
	IF(EXISTS "${QT_TRANSLATIONS_DIR}")
		MESSAGE("-- Found Qt translations in ${QT_TRANSLATIONS_DIR}")
		ADD_DEFINITIONS(-D'QT_TRANSLATIONS_DIR="${QT_TRANSLATIONS_DIR}"')
	ENDIF()
	IF(NOT WIN32)
		STRING(REPLACE "-DQT_DLL" "" QT_DEFINITIONS "${QT_DEFINITIONS}")
	ENDIF()
	INCLUDE("${QT_USE_FILE}")
ENDIF()

INCLUDE(BuildPlugin)
INCLUDE(AddFileDependencies)
INCLUDE(CheckIncludeFiles)
INCLUDE(FindPkgConfig)


SET(BIN2RES_CPP "${CMAKE_SOURCE_DIR}/buildtools/bin2res.cpp")
SET(BIN2RES "${CMAKE_BINARY_DIR}/bin2res")
ADD_CUSTOM_TARGET(bin2res COMMAND g++ "\"${BIN2RES_CPP}\"" -o "\"${BIN2RES}\"" DEPENDS "${BIN2RES_CPP}")

ADD_FILE_DEPENDENCIES("${CMAKE_BINARY_DIR}/lmmsconfig.h")

IF(LMMS_BUILD_LINUX)
	INSTALL(FILES ${LMMS_INCLUDES}
		"${CMAKE_BINARY_DIR}/lmmsconfig.h"
		"${CMAKE_BINARY_DIR}/lmmsversion.h"
		"${CMAKE_SOURCE_DIR}/src/gui/embed.cpp"
		DESTINATION "${CMAKE_INSTALL_PREFIX}/include/lmms/")
ENDIF(LMMS_BUILD_LINUX)

CHECK_INCLUDE_FILES(stdint.h LMMS_HAVE_STDINT_H)
CHECK_INCLUDE_FILES(stdlib.h LMMS_HAVE_STDLIB_H)
CHECK_INCLUDE_FILES(pthread.h LMMS_HAVE_PTHREAD_H)
CHECK_INCLUDE_FILES(semaphore.h LMMS_HAVE_SEMAPHORE_H)
CHECK_INCLUDE_FILES(unistd.h LMMS_HAVE_UNISTD_H)
CHECK_INCLUDE_FILES(sys/types.h LMMS_HAVE_SYS_TYPES_H)
CHECK_INCLUDE_FILES(sys/ipc.h LMMS_HAVE_SYS_IPC_H)
CHECK_INCLUDE_FILES(sys/shm.h LMMS_HAVE_SYS_SHM_H)
CHECK_INCLUDE_FILES(sys/time.h LMMS_HAVE_SYS_TIME_H)
CHECK_INCLUDE_FILES(sched.h LMMS_HAVE_SCHED_H)
CHECK_INCLUDE_FILES(sys/soundcard.h LMMS_HAVE_SYS_SOUNDCARD_H)
CHECK_INCLUDE_FILES(soundcard.h LMMS_HAVE_SOUNDCARD_H)
CHECK_INCLUDE_FILES(fcntl.h LMMS_HAVE_FCNTL_H)
CHECK_INCLUDE_FILES(sys/ioctl.h LMMS_HAVE_SYS_IOCTL_H)
CHECK_INCLUDE_FILES(ctype.h LMMS_HAVE_CTYPE_H)
CHECK_INCLUDE_FILES(string.h LMMS_HAVE_STRING_H)
CHECK_INCLUDE_FILES(process.h LMMS_HAVE_PROCESS_H)
CHECK_INCLUDE_FILES(locale.h LMMS_HAVE_LOCALE_H)
CONFIGURE_FILE("lmmsconfig.h.in"        "${CMAKE_BINARY_DIR}/lmmsconfig.h")
CONFIGURE_FILE("lmmsversion.h.in"       "${CMAKE_BINARY_DIR}/lmmsversion.h")


BUILD_PLUGIN(
	reverbsc
	ReverbSC.cpp 
	ReverbSCControls.cpp 
	ReverbSCControlDialog.cpp 
	base.c
	revsc.c
	dcblock.c
	MOCFILES 
	ReverbSC.h
	ReverbSCControls.h 
	ReverbSCControlDialog.h 
	base.h
	revsc.h
	dcblock.h
	EMBEDDED_RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.png"
)
