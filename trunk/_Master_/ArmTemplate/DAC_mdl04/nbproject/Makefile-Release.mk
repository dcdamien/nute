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
FC=
AS=arm-none-eabi-as.exe

# Macros
CND_PLATFORM=Yagarto-Windows
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/lib/startup/startup_stm32f10x_hd_vl.o \
	${OBJECTDIR}/lib/startup/startup_stm32f10x_ld_vl.o \
	${OBJECTDIR}/sound_data.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/lib/startup/startup_stm32f10x_md_vl.o \
	${OBJECTDIR}/lib/startup/startup_stm32f10x_xl.o \
	${OBJECTDIR}/lib/startup/startup_stm32f10x_hd.o \
	${OBJECTDIR}/lib/startup/startup_stm32f10x_cl.o \
	${OBJECTDIR}/lib/startup/startup_stm32f10x_md.o \
	${OBJECTDIR}/lib/startup/startup_stm32f10x_ld.o \
	${OBJECTDIR}/delay_util.o \
	${OBJECTDIR}/uart.o \
	${OBJECTDIR}/dac.o


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
	"${MAKE}"  -f nbproject/Makefile-Release.mk output/output.elf.exe

output/output.elf.exe: ${OBJECTFILES}
	${MKDIR} -p output
	${LINK.cc} -o output/output.elf ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/lib/startup/startup_stm32f10x_hd_vl.o: lib/startup/startup_stm32f10x_hd_vl.s 
	${MKDIR} -p ${OBJECTDIR}/lib/startup
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/lib/startup/startup_stm32f10x_hd_vl.o lib/startup/startup_stm32f10x_hd_vl.s

${OBJECTDIR}/lib/startup/startup_stm32f10x_ld_vl.o: lib/startup/startup_stm32f10x_ld_vl.s 
	${MKDIR} -p ${OBJECTDIR}/lib/startup
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/lib/startup/startup_stm32f10x_ld_vl.o lib/startup/startup_stm32f10x_ld_vl.s

${OBJECTDIR}/sound_data.o: sound_data.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DSTM32F10X_MD_VL -DUSE_STDPERIPH_DRIVER -Ilib -Ilib/CoreSupport -Ilib/inc -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/sound_data.o sound_data.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DSTM32F10X_MD_VL -DUSE_STDPERIPH_DRIVER -Ilib -Ilib/CoreSupport -Ilib/inc -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/lib/startup/startup_stm32f10x_md_vl.o: lib/startup/startup_stm32f10x_md_vl.s 
	${MKDIR} -p ${OBJECTDIR}/lib/startup
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/lib/startup/startup_stm32f10x_md_vl.o lib/startup/startup_stm32f10x_md_vl.s

${OBJECTDIR}/lib/startup/startup_stm32f10x_xl.o: lib/startup/startup_stm32f10x_xl.s 
	${MKDIR} -p ${OBJECTDIR}/lib/startup
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/lib/startup/startup_stm32f10x_xl.o lib/startup/startup_stm32f10x_xl.s

${OBJECTDIR}/lib/startup/startup_stm32f10x_hd.o: lib/startup/startup_stm32f10x_hd.s 
	${MKDIR} -p ${OBJECTDIR}/lib/startup
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/lib/startup/startup_stm32f10x_hd.o lib/startup/startup_stm32f10x_hd.s

${OBJECTDIR}/lib/startup/startup_stm32f10x_cl.o: lib/startup/startup_stm32f10x_cl.s 
	${MKDIR} -p ${OBJECTDIR}/lib/startup
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/lib/startup/startup_stm32f10x_cl.o lib/startup/startup_stm32f10x_cl.s

${OBJECTDIR}/lib/startup/startup_stm32f10x_md.o: lib/startup/startup_stm32f10x_md.s 
	${MKDIR} -p ${OBJECTDIR}/lib/startup
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/lib/startup/startup_stm32f10x_md.o lib/startup/startup_stm32f10x_md.s

${OBJECTDIR}/lib/startup/startup_stm32f10x_ld.o: lib/startup/startup_stm32f10x_ld.s 
	${MKDIR} -p ${OBJECTDIR}/lib/startup
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/lib/startup/startup_stm32f10x_ld.o lib/startup/startup_stm32f10x_ld.s

${OBJECTDIR}/delay_util.o: delay_util.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DSTM32F10X_MD_VL -DUSE_STDPERIPH_DRIVER -Ilib -Ilib/CoreSupport -Ilib/inc -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/delay_util.o delay_util.cpp

${OBJECTDIR}/uart.o: uart.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DSTM32F10X_MD_VL -DUSE_STDPERIPH_DRIVER -Ilib -Ilib/CoreSupport -Ilib/inc -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/uart.o uart.cpp

${OBJECTDIR}/dac.o: dac.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -DSTM32F10X_MD_VL -DUSE_STDPERIPH_DRIVER -Ilib -Ilib/CoreSupport -Ilib/inc -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/dac.o dac.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} output/output.elf.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc