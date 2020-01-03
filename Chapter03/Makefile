obj-m := dedicated-workqueue.o hr-timer.o shared-workqueue.o std-timer.o tasklet.o user-invoke.o waitqueue.o

#KERNELDIR ?= /lib/modules/$(shell uname -r)/build
KERNELDIR ?= /home/aijazbaig1/EmbLearning/buildroot-2019.02.5/output/build/linux-custom/

all default: modules
install: modules_install

modules modules_install help clean:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) $@
