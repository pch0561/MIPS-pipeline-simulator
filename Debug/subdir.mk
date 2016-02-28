################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../decode.cpp \
../execute.cpp \
../fetch.cpp \
../instruction.cpp \
../memaccess.cpp \
../pipeline.cpp \
../stage.cpp \
../writeback.cpp 

OBJS += \
./decode.o \
./execute.o \
./fetch.o \
./instruction.o \
./memaccess.o \
./pipeline.o \
./stage.o \
./writeback.o 

CPP_DEPS += \
./decode.d \
./execute.d \
./fetch.d \
./instruction.d \
./memaccess.d \
./pipeline.d \
./stage.d \
./writeback.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


