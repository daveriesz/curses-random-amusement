
PROGRAM = cra

CSOURCES = main.c display.c debug.c
COBJECTS = $(CSOURCES:.c=.o)

CC       = cc
CFLGAS   = $(COPT) $(CINC) $(CDEF)
COPT     = 
CINC     = 
CDEF     = 

LDCC     = cc
LDFLAGS  = $(LDOPT) $(LDDIR) $(LDLIB)
LDOPT    = 
LDDIR    = 
LDLIB    = -lncurses

all: $(PROGRAM)

$(PROGRAM): $(COBJECTS)
	$(LDCC) -o $@ $^ $(LDFLAGS)

run: $(PROGRAM)
	./$<

debug: $(PROGRAM)
	./$< -g 2>cra-debug.log

clean: execlean objclean
execlean:
	$(RM) $(PROGRAM)
objclean:
	$(RM) $(COBJECTS)

%.o: %.c cra.h

