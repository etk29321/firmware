## -*- Makefile -*-

CCC = mingw32-gcc
CXX = mingw32-g++
LD = mingw32-g++
CFLAGS = -g
CCFLAGS = $(CFLAGS)
CXXFLAGS = $(CFLAGS)
RM = rm -f
RMDIR = rm -f -r
MKDIR = mkdir -p

# root of the project relative to this folder
SRC_ROOT=../

# location of this folder relative to the root
SRC_PATH=test
SPARK=../spark-firmware/
WIRING=$(SPARK)/wiring/
HAL=$(SPARK)/hal/
WIRING_SRC=$(WIRING)src/

TARGETDIR=obj/
TARGET=runner

BUILD_PATH=$(TARGETDIR)test/
# Define the target directories. Nest 2 levels deep since we also include
# sources from libraries via ../core-common-lib

# Recursive wildcard function
rwildcard = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# enumerates files in the filesystem and returns their path relative to the project root
# $1 the directory relative to the project root
# $2 the pattern to match, e.g. *.cpp
target_files = $(patsubst $(SRC_ROOT)%,%,$(call rwildcard,$(SRC_ROOT)$1,$2))

CSRC += $(call target_files,boost_test,*.c)
CPPSRC += $(call target_files,boost_test,*.cpp)

CPPSRC += $(SOURCE_PATH)platform/wiring/temperatureFormats.cpp
CPPSRC += $(SOURCE_PATH)platform/wiring/str_functions.cpp
CPPSRC += $(SOURCE_PATH)app/controller/Filter/FilterFixed.cpp
CPPSRC += $(SOURCE_PATH)app/controller/Filter/FilterCascaded.cpp
CPPSRC += $(SOURCE_PATH)app/controller/Pid.cpp
CPPSRC += $(SOURCE_PATH)app/devices/Actuator/ActuatorPwm.cpp
CPPSRC += $(SOURCE_PATH)app/devices/Actuator/ActuatorTimeLimited.cpp
CPPSRC += $(SOURCE_PATH)app/controller/SetPoint.cpp
CPPSRC += $(SOURCE_PATH)app/controller/defaultDevices.cpp
CPPSRC += $(SOURCE_PATH)app/devices/Actuator/ActuatorMutexGroup.cpp
CPPSRC += $(SOURCE_PATH)app/controller/Control.cpp

ifeq ($(BOOST_ROOT),)
$(error BOOST_ROOT not set. Download boost and add BOOST_ROOT to your environment variables.)
endif
CFLAGS += -I$(BOOST_ROOT)

INCLUDE_DIRS += $(SOURCE_PATH)platform/wiring
INCLUDE_DIRS += $(SOURCE_PATH)app/controller
INCLUDE_DIRS += $(SOURCE_PATH)app/controller/Filter
INCLUDE_DIRS += $(SOURCE_PATH)app/fallback
INCLUDE_DIRS += $(SOURCE_PATH)app/devices/TempSensor
INCLUDE_DIRS += $(SOURCE_PATH)app/devices/Actuator
INCLUDE_DIRS += $(SOURCE_PATH)app/devices/
INCLUDE_DIRS += $(SOURCE_PATH)app/controller/esj

CFLAGS += $(patsubst %,-I$(SRC_ROOT)%,$(INCLUDE_DIRS)) -I.
CFLAGS += -ffunction-sections -Wall

# Flag compiler error for [-Wdeprecated-declarations]
CFLAGS += -Werror=deprecated-declarations

# Generate dependency files automatically.
CFLAGS += -MD -MP -MF $@.d
CFLAGS += -DSPARK=1
CFLAGS += -DDEBUG_BUILD

CPPFLAGS += -std=gnu++11

LDFLAGS +=  -Wl,--gc-sections 

# Collect all object and dep files
ALLOBJ += $(addprefix $(BUILD_PATH), $(CSRC:.c=.o))
ALLOBJ += $(addprefix $(BUILD_PATH), $(CPPSRC:.cpp=.o))

ALLDEPS += $(addprefix $(BUILD_PATH), $(CSRC:.c=.o.d))
ALLDEPS += $(addprefix $(BUILD_PATH), $(CPPSRC:.cpp=.o.d))


all: runner

runner: $(TARGETDIR)$(TARGET)

$(TARGETDIR)$(TARGET) : $(BUILD_PATH) $(ALLOBJ)
	@echo Building target: $@
	@echo Invoking: GCC C++ Linker
	$(MKDIR) $(dir $@)
	$(LD) $(CFLAGS) $(ALLOBJ) --output $@ $(LDFLAGS)
	@echo

$(BUILD_PATH): 
	$(MKDIR) $(BUILD_PATH)

# Tool invocations

# C compiler to build .o from .c in $(BUILD_DIR)
$(BUILD_PATH)%.o : $(SRC_ROOT)%.c
	@echo Building file: $<
	@echo Invoking: GCC C Compiler
	$(MKDIR) $(dir $@)
	$(CCC) $(CCFLAGS) -c -o $@ $<
	@echo

# CPP compiler to build .o from .cpp in $(BUILD_DIR)
# Note: Calls standard $(CC) - gcc will invoke g++ as appropriate
$(BUILD_PATH)%.o : $(SRC_ROOT)%.cpp
	@echo Building file: $<
	@echo Invoking: GCC CPP Compiler
	$(MKDIR) $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<
	@echo

# Other Targets
clean:	
	$(RM) $(ALLOBJ) $(ALLDEPS) $(TARGETDIR)$(TARGET)
	$(RMDIR) $(TARGETDIR)
	@echo

.PHONY: all clean runner
.SECONDARY:

# Include auto generated dependency files
-include $(ALLDEPS)



