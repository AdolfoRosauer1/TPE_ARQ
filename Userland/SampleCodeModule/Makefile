include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin

SOURCES=$(wildcard [^_]*.c)
SOURCES_ASM=$(wildcard asm/*.asm)
SOURCES_LIBRARIES=$(wildcard libraries/*.c)
SOURCES_PROGRAMS=$(wildcard programs/*.c)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_PROGRAMS=$(SOURCES_PROGRAMS:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_LIBRARIES=$(SOURCES_LIBRARIES:.c=.o)

all: $(MODULE)

$(MODULE): $(OBJECTS) $(OBJECTS_ASM) $(OBJECTS_LIBRARIES) $(OBJECTS_PROGRAMS)
	$(LD) $(LDFLAGS) -T sampleCodeModule.ld -o ../$(MODULE) $^

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o programs/*.o asm/*.o libraries/*.o

.PHONY: all clean print