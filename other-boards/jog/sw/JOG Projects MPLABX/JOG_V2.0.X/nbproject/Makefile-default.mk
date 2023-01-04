#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/JOG_V2.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/JOG_V2.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../JOG_main.c ../conf.c ../HALL_JOG.c ../MC_PWM_JOG.c ../QEI_JOG.c ../SPI_JOG.c ../UART_JOG.c ../CAN_JOG.c ../traps.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/JOG_main.o ${OBJECTDIR}/_ext/1472/conf.o ${OBJECTDIR}/_ext/1472/HALL_JOG.o ${OBJECTDIR}/_ext/1472/MC_PWM_JOG.o ${OBJECTDIR}/_ext/1472/QEI_JOG.o ${OBJECTDIR}/_ext/1472/SPI_JOG.o ${OBJECTDIR}/_ext/1472/UART_JOG.o ${OBJECTDIR}/_ext/1472/CAN_JOG.o ${OBJECTDIR}/_ext/1472/traps.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/JOG_main.o.d ${OBJECTDIR}/_ext/1472/conf.o.d ${OBJECTDIR}/_ext/1472/HALL_JOG.o.d ${OBJECTDIR}/_ext/1472/MC_PWM_JOG.o.d ${OBJECTDIR}/_ext/1472/QEI_JOG.o.d ${OBJECTDIR}/_ext/1472/SPI_JOG.o.d ${OBJECTDIR}/_ext/1472/UART_JOG.o.d ${OBJECTDIR}/_ext/1472/CAN_JOG.o.d ${OBJECTDIR}/_ext/1472/traps.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/JOG_main.o ${OBJECTDIR}/_ext/1472/conf.o ${OBJECTDIR}/_ext/1472/HALL_JOG.o ${OBJECTDIR}/_ext/1472/MC_PWM_JOG.o ${OBJECTDIR}/_ext/1472/QEI_JOG.o ${OBJECTDIR}/_ext/1472/SPI_JOG.o ${OBJECTDIR}/_ext/1472/UART_JOG.o ${OBJECTDIR}/_ext/1472/CAN_JOG.o ${OBJECTDIR}/_ext/1472/traps.o

# Source Files
SOURCEFILES=../JOG_main.c ../conf.c ../HALL_JOG.c ../MC_PWM_JOG.c ../QEI_JOG.c ../SPI_JOG.c ../UART_JOG.c ../CAN_JOG.c ../traps.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/JOG_V2.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC804
MP_LINKER_FILE_OPTION=,--script=p33FJ128MC804.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/JOG_main.o: ../JOG_main.c  .generated_files/flags/default/7a68714de89af21c2c4d4412086d0eca5cc3d642 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/JOG_main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/JOG_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../JOG_main.c  -o ${OBJECTDIR}/_ext/1472/JOG_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/JOG_main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I".." -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/conf.o: ../conf.c  .generated_files/flags/default/cbd01233d103b42add365a1cc007b1e531930a32 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/conf.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/conf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../conf.c  -o ${OBJECTDIR}/_ext/1472/conf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/conf.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I".." -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/HALL_JOG.o: ../HALL_JOG.c  .generated_files/flags/default/462e7b9a06d413daa1c4476ea2f8abf99f9a1642 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/HALL_JOG.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HALL_JOG.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../HALL_JOG.c  -o ${OBJECTDIR}/_ext/1472/HALL_JOG.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/HALL_JOG.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I".." -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/MC_PWM_JOG.o: ../MC_PWM_JOG.c  .generated_files/flags/default/367db0377609858c54548a71ace8840d14d8adb3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MC_PWM_JOG.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MC_PWM_JOG.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../MC_PWM_JOG.c  -o ${OBJECTDIR}/_ext/1472/MC_PWM_JOG.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/MC_PWM_JOG.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I".." -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/QEI_JOG.o: ../QEI_JOG.c  .generated_files/flags/default/93cc4126843e09aeff688911ea43a2cdeb60c6b7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/QEI_JOG.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/QEI_JOG.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../QEI_JOG.c  -o ${OBJECTDIR}/_ext/1472/QEI_JOG.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/QEI_JOG.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I".." -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/SPI_JOG.o: ../SPI_JOG.c  .generated_files/flags/default/34d91bd4e692704517aa76c1fb87fed92f06d347 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/SPI_JOG.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SPI_JOG.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SPI_JOG.c  -o ${OBJECTDIR}/_ext/1472/SPI_JOG.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/SPI_JOG.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I".." -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/UART_JOG.o: ../UART_JOG.c  .generated_files/flags/default/e33d3b733ab0e3f387c60ed7dc43cc4b4fb6d22d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/UART_JOG.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/UART_JOG.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../UART_JOG.c  -o ${OBJECTDIR}/_ext/1472/UART_JOG.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/UART_JOG.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I".." -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/CAN_JOG.o: ../CAN_JOG.c  .generated_files/flags/default/cfbbbf65ea4016210ca75adc7e803d504170dec3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CAN_JOG.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CAN_JOG.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../CAN_JOG.c  -o ${OBJECTDIR}/_ext/1472/CAN_JOG.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/CAN_JOG.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I".." -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/traps.o: ../traps.c  .generated_files/flags/default/d663ed33aeeef96e644f835e7f17d0edc9f4dd32 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/traps.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../traps.c  -o ${OBJECTDIR}/_ext/1472/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/traps.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I".." -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/1472/JOG_main.o: ../JOG_main.c  .generated_files/flags/default/edd7fbaad241a65e6936e042080aea80e282d7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/JOG_main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/JOG_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../JOG_main.c  -o ${OBJECTDIR}/_ext/1472/JOG_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/JOG_main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I".." -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/conf.o: ../conf.c  .generated_files/flags/default/b7ca90c1755ee856e972056a2ec65e99c57df14c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/conf.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/conf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../conf.c  -o ${OBJECTDIR}/_ext/1472/conf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/conf.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I".." -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/HALL_JOG.o: ../HALL_JOG.c  .generated_files/flags/default/21915c1383277199b349dc1a47649362214b92fd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/HALL_JOG.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HALL_JOG.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../HALL_JOG.c  -o ${OBJECTDIR}/_ext/1472/HALL_JOG.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/HALL_JOG.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I".." -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/MC_PWM_JOG.o: ../MC_PWM_JOG.c  .generated_files/flags/default/84401df1d36e82416d864e5fad5c719912f26ba9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/MC_PWM_JOG.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MC_PWM_JOG.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../MC_PWM_JOG.c  -o ${OBJECTDIR}/_ext/1472/MC_PWM_JOG.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/MC_PWM_JOG.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I".." -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/QEI_JOG.o: ../QEI_JOG.c  .generated_files/flags/default/45f49d20ba8af99e1338d5183a3cb40630e85514 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/QEI_JOG.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/QEI_JOG.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../QEI_JOG.c  -o ${OBJECTDIR}/_ext/1472/QEI_JOG.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/QEI_JOG.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I".." -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/SPI_JOG.o: ../SPI_JOG.c  .generated_files/flags/default/e1e517bb9424b1b8cdd4ca341b292e925a54d1a6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/SPI_JOG.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SPI_JOG.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../SPI_JOG.c  -o ${OBJECTDIR}/_ext/1472/SPI_JOG.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/SPI_JOG.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I".." -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/UART_JOG.o: ../UART_JOG.c  .generated_files/flags/default/9734a72671f9561677f57e75d431411e089bdc1f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/UART_JOG.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/UART_JOG.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../UART_JOG.c  -o ${OBJECTDIR}/_ext/1472/UART_JOG.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/UART_JOG.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I".." -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/CAN_JOG.o: ../CAN_JOG.c  .generated_files/flags/default/aad6e44eccb34e479803820efce85597dbb00869 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/CAN_JOG.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/CAN_JOG.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../CAN_JOG.c  -o ${OBJECTDIR}/_ext/1472/CAN_JOG.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/CAN_JOG.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I".." -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1472/traps.o: ../traps.c  .generated_files/flags/default/19eadc59776bae0d5c06b99263d34efd9b5033e2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/traps.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../traps.c  -o ${OBJECTDIR}/_ext/1472/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/traps.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I".." -I"." -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/JOG_V2.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/JOG_V2.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="..",--library-path=".",--no-force-link,--smart-io,-Map="${DISTDIR}/JOG_V2.0.X.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/JOG_V2.0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/JOG_V2.0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="..",--library-path=".",--no-force-link,--smart-io,-Map="${DISTDIR}/JOG_V2.0.X.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/JOG_V2.0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
