#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=avr-gcc.exe
CCC=avr-g++.exe
CXX=avr-g++.exe
FC=
AS=avr-as.exe

# Macros
CND_PLATFORM=WinAVR-Windows
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/time_utils.o \
	${OBJECTDIR}/portal.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Debug.mk dist/Debug/WinAVR-Windows/firmware.exe

dist/Debug/WinAVR-Windows/firmware.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/WinAVR-Windows
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/firmware ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/time_utils.o: time_utils.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -DF_CPU\ 1000000 -D__AVR_ATmega88__ -IC/WinAVR/avr/include -IC/WinAVR/source/avr/gcc/4.3.3 -MMD -MP -MF $@.d -o ${OBJECTDIR}/time_utils.o time_utils.c

${OBJECTDIR}/portal.o: portal.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -DF_CPU\ 1000000 -D__AVR_ATmega88__ -IC/WinAVR/avr/include -IC/WinAVR/source/avr/gcc/4.3.3 -MMD -MP -MF $@.d -o ${OBJECTDIR}/portal.o portal.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/WinAVR-Windows/firmware.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
