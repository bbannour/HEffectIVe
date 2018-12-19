################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bdd_cash_marking.c \
../bdd_elim_rezize.c \
../bdd_operator.c \
../external_theory.c \
../prime.c \
../prime_bounded.c \
../robdd.c \
../setminus.c \
../solutions.c \
../stack.c \
../toDot.c 

OBJS += \
./bdd_cash_marking.o \
./bdd_elim_rezize.o \
./bdd_operator.o \
./external_theory.o \
./prime.o \
./prime_bounded.o \
./robdd.o \
./setminus.o \
./solutions.o \
./stack.o \
./toDot.o 

C_DEPS += \
./bdd_cash_marking.d \
./bdd_elim_rezize.d \
./bdd_operator.d \
./external_theory.d \
./prime.d \
./prime_bounded.d \
./robdd.d \
./setminus.d \
./solutions.d \
./stack.d \
./toDot.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DPRIME -DHOMOGENEOUS_PROBA -DEXTERN_THEO -I"C:\Users\bb222989\git\2019\org.eclipse.efm-safety\itvLibProba" -I"C:\Users\bb222989\git\2019\org.eclipse.efm-safety\HEffectIVe" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


