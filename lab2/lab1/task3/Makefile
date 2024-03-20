obj-m += export_demo.o
obj-m += export_gpl_demo.o
obj-m += use_variable.o

KDIR := /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
