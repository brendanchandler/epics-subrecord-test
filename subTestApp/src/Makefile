TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS BELOW HERE

# Use typed rset structure (see 3.16.1 release notes)
USR_CPPFLAGS += -DUSE_TYPED_RSET

# xxxRecord.h will be created from xxxRecord.dbd
DBDINC += xxxRecord

# Install xxxSupport.dbd into <top>/dbd
DBD += xxxSupport.dbd

# Build an IOC support library
LIBRARY_IOC += subTestSupport

# Compile and add code to the support library
subTestSupport_SRCS += xxxRecord.c
subTestSupport_SRCS += devXxxSoft.c

# Link locally-provided code into the support library,
# rather than directly into the IOC application, that
# causes problems on Windows DLL builds
subTestSupport_SRCS += dbSubExample.c
subTestSupport_SRCS += devsubTestVersion.c
subTestSupport_SRCS += subTestHello.c
subTestSupport_SRCS += initTrace.c

subTestSupport_LIBS += $(EPICS_BASE_IOC_LIBS)

# Auto-generate a header file containing a version string.
# Version comes from the VCS if available, else date+time.
GENVERSION = subTestVersion.h
# Macro name
GENVERSIONMACRO = subTestVERSION

# Build the IOC application
PROD_IOC = subTest

# subTest.dbd will be created and installed
DBD += subTest.dbd

# subTest.dbd will include these files:
subTest_DBD += base.dbd
subTest_DBD += xxxSupport.dbd
subTest_DBD += dbSubExample.dbd
subTest_DBD += devsubTestVersion.dbd
subTest_DBD += subTestHello.dbd
subTest_DBD += initTrace.dbd

# subTest_registerRecordDeviceDriver.cpp derives from subTest.dbd
subTest_SRCS += subTest_registerRecordDeviceDriver.cpp

# Build the main IOC entry point where needed
subTest_SRCS_DEFAULT += subTestMain.cpp
subTest_SRCS_vxWorks += -nil-

# Link in the code from our support library
subTest_LIBS += subTestSupport

# To build SNL programs, SNCSEQ must be defined
# in the <top>/configure/RELEASE file
ifneq ($(SNCSEQ),)
    # Build sncExample into subTestSupport
    sncExample_SNCFLAGS += +r
    subTest_DBD += sncExample.dbd
    # A .stt sequence program is *not* pre-processed:
    subTestSupport_SRCS += sncExample.stt
    subTestSupport_LIBS += seq pv
    subTest_LIBS += seq pv

    # Build sncProgram as a standalone program
    PROD_HOST += sncProgram
    sncProgram_SNCFLAGS += +m
    # A .st sequence program *is* pre-processed:
    sncProgram_SRCS += sncProgram.st
    sncProgram_LIBS += seq pv
    sncProgram_LIBS += $(EPICS_BASE_HOST_LIBS)
endif

# Link QSRV (pvAccess Server) if available
ifdef EPICS_QSRV_MAJOR_VERSION
    subTest_LIBS += qsrv
    subTest_LIBS += $(EPICS_BASE_PVA_CORE_LIBS)
    subTest_DBD += PVAServerRegister.dbd
    subTest_DBD += qsrv.dbd
endif

# Finally link IOC to the EPICS Base libraries
subTest_LIBS += $(EPICS_BASE_IOC_LIBS)


# begin test
TARGETS += $(COMMON_DIR)/testsub.dbd
DBDDEPENDS_FILES += testsub.dbd$(DEP)

TESTFILES += $(COMMON_DIR)/testsub.dbd

TESTPROD_HOST += testsub
testsub_SRCS := testsub.cc
testsub_SRCS += dbSubExample.c
testsub_SRCS += testsub_registerRecordDeviceDriver.cpp

testsub_LIBS := $(IOCSTD_IOC_LIBS)
testsub_LIBS += $(EPICS_BASE_IOC_LIBS)

testsub_DBD := dbSubExample.dbd
testsub_DBD += base.dbd

TESTS += testsub
TESTSCRIPTS_HOST += $(TESTS:%=%.t)
# end test


include $(TOP)/configure/RULES
#----------------------------------------
#  ADD EXTRA GNUMAKE RULES BELOW HERE

# Explicit dependency needed for generated header file
devsubTestVersion$(DEP): $(COMMON_DIR)/$(GENVERSION)
