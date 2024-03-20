# Hedef dizini belirleyin
obj-m := task3.o

# Çekirdek derleme dizini
KERNELDIR := /lib/modules/$(shell uname -r)/build

# Varsayılan hedef
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

# Temizleme hedefi
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
