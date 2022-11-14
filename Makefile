# Usage:
# make        # compile all binary

.PHONY = all

CC = g++

SRCS := main.cpp
OUT := vcpp2048

all: build2048

build2048:
	@echo "Building vcpp2048..."
	${CC} ${SRCS} -o ${OUT}