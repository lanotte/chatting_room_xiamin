include scripts/Makefile

modules_make = $(MAKE) -C $(1);
modules_clean = $(MAKE) clean -C $(1);

.PHONY: all mm mc clean

all : $(Target)

mm:
	@$(foreach n,$(Modules),$(call modules_make,$(n)))
mc:
	@$(foreach n,$(Modules),$(call modules_clean,$(n)))

$(Target) : mm
	$(CC) $(AllObjs) -o $(Target) $(Libs) $(Libq)
	@ echo $(Target) make done!

clean : mc
	@rm -rf $(Target)
	@ echo clean done!
