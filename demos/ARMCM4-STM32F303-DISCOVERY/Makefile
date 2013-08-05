TRGT  = arm-none-eabi-
GDB   = $(TRGT)gdb
HSDIR = build_haskell

all: $(HSDIR)/jhc_rts_header.h
	make -f forc.mk

$(HSDIR)/jhc_rts_header.h: hs_src/Main.hs
	mkdir -p $(HSDIR)
	ajhc -fffi --tdir=$(HSDIR) -C --include=hs_src $<

clean:
	rm -rf build_haskell
	make -f forc.mk clean

gdbwrite: all
	@echo '################################################'
	@echo '##### Use me after running "sudo st-util". #####'
	@echo '################################################'
	$(GDB) -x gdbwrite.boot build/ch.elf

gdbattach: all
	@echo '################################################'
	@echo '##### Use me after running "sudo st-util". #####'
	@echo '################################################'
	$(GDB) -x gdbattach.boot build/ch.elf
