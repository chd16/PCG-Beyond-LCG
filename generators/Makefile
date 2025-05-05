OBJDIR = .
SRCDIR = .
OBJS = lcg.o
OBJS += xor.o
OBJS += generator.o
OBJS += select_gen.o
OBJS += curtime.o
OBJS += mlfg.o
OBJS += lcg_fctrl.o
OBJS += MT.o

build: $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	g++ -c $< -o $@

clean:
	rm *.o
