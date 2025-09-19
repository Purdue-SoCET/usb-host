#-----------------------------
# Begin Variables
#-----------------------------
TOP_LEVEL_CORE = socet:usb:host

FUSESOC_RUN_FLAGS = --cores-root . run --setup --build --build-root usb_host
#-----------------------------
# End Variables
#-----------------------------

#-----------------------------
# Begin Utilty
#-----------------------------
define LINE
@echo "-------------------------------------------------------------------"
endef

define FUSESOC_DONE
$(LINE)
@echo "Build finished! Run with 'fusesoc run', or by navigating to the"
@echo "build directory created by FuseSoC and using the Makefile there."
$(LINE)
endef
#-----------------------------
# End Utilty
#-----------------------------


#-----------------------------
# Begin Rules
#-----------------------------
.phony: default config verilate lint clean

default:
	$(LINE)
	@echo "Build Targets:"
	@echo "    verilate  : Invoke FuseSoC to build the verilator target"
	@echo "    clean     : Cleans all build files"
	$(LINE)

config:
	$(LINE)
	@echo "Configurating the USB Host design."
	@echo "TODO(anyone): update this when there is something to configure!"
	$(LINE)

verilate: config
	$(LINE)
	@echo "Building USB Host."
	$(LINE)
	@fusesoc $(FUSESOC_RUN_FLAGS) --target verilator_build $(TOP_LEVEL_CORE) --make_options='-j'
	$(FUSESOC_DONE)

lint: config
	$(LINE)
	@echo "Linting USB Host."
	@echo "WARNING: Broken. Do NOT trust!"
	$(LINE)
	@fusesoc $(FUSESOC_RUN_FLAGS) --target lint --tool veriblelint $(TOP_LEVEL_CORE)


format: config
	$(LINE)
	@echo "Formatting USB Host."
	@echo "WARNING: Broken. Do NOT trust!"
	$(LINE)
	@fusesoc $(FUSESOC_RUN_FLAGS) --target format --tool veribleformat $(TOP_LEVEL_CORE)

clean:
	rm -rf build
	rm -rf usb_host
#-----------------------------
# End Rules
#-----------------------------
