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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/delta_hd.o \
	${OBJECTDIR}/deltag_he.o \
	${OBJECTDIR}/deltag_hi.o \
	${OBJECTDIR}/deltag_hm.o \
	${OBJECTDIR}/deltag_hr.o \
	${OBJECTDIR}/ebulge.o \
	${OBJECTDIR}/edangle.o \
	${OBJECTDIR}/ehair.o \
	${OBJECTDIR}/eloop.o \
	${OBJECTDIR}/estack.o \
	${OBJECTDIR}/estruc.o \
	${OBJECTDIR}/helx_reac.o \
	${OBJECTDIR}/kfold.o \
	${OBJECTDIR}/loop_fire.o \
	${OBJECTDIR}/loop_init.o \
	${OBJECTDIR}/loop_reac.o \
	${OBJECTDIR}/loop_resum.o \
	${OBJECTDIR}/random.o \
	${OBJECTDIR}/readdata.o \
	${OBJECTDIR}/setupnuc.o \
	${OBJECTDIR}/ssareaction.o \
	${OBJECTDIR}/tdangle3.o \
	${OBJECTDIR}/tdangle5.o \
	${OBJECTDIR}/tint11.o \
	${OBJECTDIR}/tint12.o \
	${OBJECTDIR}/tint22.o \
	${OBJECTDIR}/tloop.o \
	${OBJECTDIR}/tstack.o \
	${OBJECTDIR}/tstackh.o \
	${OBJECTDIR}/tstacki.o \
	${OBJECTDIR}/v2ct.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kfold.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kfold.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kfold ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/delta_hd.o: delta_hd.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/delta_hd.o delta_hd.cpp

${OBJECTDIR}/deltag_he.o: deltag_he.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/deltag_he.o deltag_he.cpp

${OBJECTDIR}/deltag_hi.o: deltag_hi.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/deltag_hi.o deltag_hi.cpp

${OBJECTDIR}/deltag_hm.o: deltag_hm.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/deltag_hm.o deltag_hm.cpp

${OBJECTDIR}/deltag_hr.o: deltag_hr.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/deltag_hr.o deltag_hr.cpp

${OBJECTDIR}/ebulge.o: ebulge.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ebulge.o ebulge.cpp

${OBJECTDIR}/edangle.o: edangle.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/edangle.o edangle.cpp

${OBJECTDIR}/ehair.o: ehair.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ehair.o ehair.cpp

${OBJECTDIR}/eloop.o: eloop.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/eloop.o eloop.cpp

${OBJECTDIR}/estack.o: estack.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/estack.o estack.cpp

${OBJECTDIR}/estruc.o: estruc.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/estruc.o estruc.cpp

${OBJECTDIR}/helx_reac.o: helx_reac.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/helx_reac.o helx_reac.cpp

${OBJECTDIR}/kfold.o: kfold.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kfold.o kfold.cpp

${OBJECTDIR}/loop_fire.o: loop_fire.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/loop_fire.o loop_fire.cpp

${OBJECTDIR}/loop_init.o: loop_init.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/loop_init.o loop_init.cpp

${OBJECTDIR}/loop_reac.o: loop_reac.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/loop_reac.o loop_reac.cpp

${OBJECTDIR}/loop_resum.o: loop_resum.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/loop_resum.o loop_resum.cpp

${OBJECTDIR}/random.o: random.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/random.o random.cpp

${OBJECTDIR}/readdata.o: readdata.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/readdata.o readdata.cpp

${OBJECTDIR}/setupnuc.o: setupnuc.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/setupnuc.o setupnuc.cpp

${OBJECTDIR}/ssareaction.o: ssareaction.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ssareaction.o ssareaction.cpp

${OBJECTDIR}/tdangle3.o: tdangle3.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tdangle3.o tdangle3.cpp

${OBJECTDIR}/tdangle5.o: tdangle5.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tdangle5.o tdangle5.cpp

${OBJECTDIR}/tint11.o: tint11.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tint11.o tint11.cpp

${OBJECTDIR}/tint12.o: tint12.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tint12.o tint12.cpp

${OBJECTDIR}/tint22.o: tint22.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tint22.o tint22.cpp

${OBJECTDIR}/tloop.o: tloop.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tloop.o tloop.cpp

${OBJECTDIR}/tstack.o: tstack.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tstack.o tstack.cpp

${OBJECTDIR}/tstackh.o: tstackh.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tstackh.o tstackh.cpp

${OBJECTDIR}/tstacki.o: tstacki.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tstacki.o tstacki.cpp

${OBJECTDIR}/v2ct.o: v2ct.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/v2ct.o v2ct.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
