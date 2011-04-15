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
CC=arm-none-eabi-gcc.exe
CCC=arm-none-eabi-g++.exe
CXX=arm-none-eabi-g++.exe
FC=gfortran
AS=arm-none-eabi-as.exe

# Macros
CND_PLATFORM=Yagarto-Windows
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES=


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tears_fmw.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tears_fmw.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tears_fmw ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/delay_util.c.gch: delay_util.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -D__AVR_ATmega88__ -DF_CPU\ 1000000 -IC/WinAVR/lib/gcc/avr/4.3.3 -IC/WinAVR/avr/include -MMD -MP -MF $@.d -o $@ delay_util.c

${OBJECTDIR}/main.c.gch: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -D__AVR_ATmega88__ -DF_CPU\ 1000000 -IC/WinAVR/lib/gcc/avr/4.3.3 -IC/WinAVR/avr/include -MMD -MP -MF $@.d -o $@ main.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tears_fmw.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
