SUBDIRS := ARMCM4-STM32F303-DISCOVERY

all clean:
	@for i in $(SUBDIRS); do \
		$(MAKE) -C $$i $@; \
	done

.PHONY: all clean $(SUBDIRS)
