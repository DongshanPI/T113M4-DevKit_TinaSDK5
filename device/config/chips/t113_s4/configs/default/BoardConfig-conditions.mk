# condition config

# arch

# kernel
ifeq ($(filter-out %5.4,$(LICHEE_KERN_VER)),)
	ifeq ($(LICHEE_PLATFORM),linux)
		LICHEE_KERN_DEFCONF?=sun8iw20p1smp_defconfig
	endif
endif

