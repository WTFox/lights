# Rule for flashing a specific device with a specific target
define flash_device_rule
flash-$(1):
	@echo "Flashing to $(1)"
	@particle flash $(1) --target "$(2)" .
endef

# Define devices and their targets
$(eval $(call flash_device_rule,a1,5.5.0))
$(eval $(call flash_device_rule,p1,3.3.1))
$(eval $(call flash_device_rule,p2_1,5.5.0))
$(eval $(call flash_device_rule,patio,3.3.1))

# Rule for flashing all devices
flash-all: flash-a1 flash-p1 flash-p2_1 flash-patio

# Set the level of parallelism
MAKEFLAGS += -j4
