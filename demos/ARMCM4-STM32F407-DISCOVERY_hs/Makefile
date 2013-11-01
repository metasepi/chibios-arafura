TRGT  = arm-none-eabi-
GDB   = $(TRGT)gdb
HSBUILD = build_haskell
HSDIR = hs_src
HSSRC = $(wildcard $(HSDIR)/*.hs $(HSDIR)/*/*.hs $(HSDIR)/*/*/*.hs $(HSDIR)/*/*/*/*.hs)

all: $(HSBUILD)/hs_main.c
	make -f forc.mk

$(HSBUILD)/hs_main.c: $(HSSRC)
	mkdir -p $(HSBUILD)
	ajhc -fffi --tdir=$(HSBUILD) -C --include=hs_src -o $@ $(HSDIR)/Main.hs

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
