SUBDIRS := demos

all: ext/lwip/FILES
	@for i in $(SUBDIRS); do \
		$(MAKE) -C $$i $@; \
	done

ext/lwip/FILES:
	cd ext && unzip -x lwip-1.4.1_patched.zip

clean:
	@for i in $(SUBDIRS); do \
		$(MAKE) -C $$i $@; \
	done
	rm -rf ext/lwip

.PHONY: all clean $(SUBDIRS)
