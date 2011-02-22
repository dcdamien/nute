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
	${OBJECTDIR}/battery.o \
	${OBJECTDIR}/delay_util.o \
	${OBJECTDIR}/leds.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/cc1101.o


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
	"${MAKE}"  -f nbproject/Makefile-Debug.mk c\AvrDragon\AVRDragon.exe

c\AvrDragon\AVRDragon.exe: ${OBJECTFILES}
	${MKDIR} -p c\AvrDragon
	${LINK.c} -o c:\AvrDragon\AVRDragon.exe ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/battery.o: battery.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -D__AVR_ATmega16A__ -DF_CPU\ 4000000 -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/battery.o battery.c

${OBJECTDIR}/delay_util.o: delay_util.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -D__AVR_ATmega16A__ -DF_CPU\ 4000000 -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/delay_util.o delay_util.c

${OBJECTDIR}/leds.o: leds.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -D__AVR_ATmega16A__ -DF_CPU\ 4000000 -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/leds.o leds.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -D__AVR_ATmega16A__ -DF_CPU\ 4000000 -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/cc1101.o: cc1101.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -D__AVR_ATmega16A__ -DF_CPU\ 4000000 -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/cc1101.o cc1101.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} c:\AvrDragon\AVRDragon.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
