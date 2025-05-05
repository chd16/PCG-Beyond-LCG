OBJDIR = .
SCRDIR =.
OBJS = lk_hash.o
OBJS += scrambler.o
OBJS += select_scram.o
OBJS += pcg_random_dropshift.o
OBJS += pcg_random_rotate.o
OBJS += pcg_random_xorshift.o
OBJS += pcg_fixed_xorshift.o
OBJS += scrambler_mixer.o
OBJS += constant_multiplier.o
OBJS += fixed_dropshift.o
OBJS += rightshift.o
build: $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	g++ -c $< -o $@
clean:
	rm *.o
