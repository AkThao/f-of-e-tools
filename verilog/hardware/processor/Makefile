DESIGN  = sail
PROGRAM = template


# First recipe in the Makefile is the default recipe
# Hardware (design) recipe:
#       Copy the hex files to be besides all the design .v files
#       Copy the toplevel design if its not already present into the processor build (to allow for different builds with different toplevels).
#       In the yosys script, change the project name, remove CSR.v from the build, and tell it to output the
#	final synthesised .v file for examination, saving this all as a new yscript into the current directory.
#       Run yosys quietly with desired project name.
#	If one doesn't already exist, create a custom pcf for the design+program build by copying and renaming sail.pcf.
#       Run the rest of the build with the desired project naming system.
#	The output of nextpnr and icetime is saved into one file, with 4 extra newlines to separate them.
design:
	cp programs/data.hex $(DESIGN)-core/verilog/
	cp programs/program.hex $(DESIGN)-core/verilog/
#	test -s $(DESIGN)-core/verilog/toplevel.v || cp toplevel.v $(DESIGN)-core/verilog/toplevel.v
	cat ../../../yscripts/sail.ys |\
	sed "s/sail/$(DESIGN)-$(PROGRAM)/" |\
	sed "s/verilog\/CSR\.v //g" |\
#	sed "s/verilog\//$(DESIGN)-core\/verilog\//g" |\
#	sed "s/toplevel/$(DESIGN)-core\/verilog\/toplevel/" |\
	sed "s/blif$$/blif\nwrite_verilog $(DESIGN)-$(PROGRAM)-synth.v/" > $(DESIGN)-$(PROGRAM).ys
	yosys -q $(DESIGN)-$(PROGRAM).ys
#	yosys -p "show -format pdf -prefix $(DESIGN)-$(PROGRAM) -colors 10 -width -stretch" $(DESIGN)-$(PROGRAM)-synth.v
	test -s pcf/$(DESIGN)-$(PROGRAM).pcf || cp pcf/sail.pcf pcf/$(DESIGN)-$(PROGRAM).pcf
	nextpnr-ice40 --up5k --package uwg30 --json $(DESIGN)-$(PROGRAM).json --pcf pcf/$(DESIGN)-$(PROGRAM).pcf --asc $(DESIGN)-$(PROGRAM).asc --log $(DESIGN)-$(PROGRAM)-pnr.txt
	echo >> $(DESIGN)-$(PROGRAM)-pnr.txt; echo >> $(DESIGN)-$(PROGRAM)-pnr.txt; echo >> $(DESIGN)-$(PROGRAM)-pnr.txt; echo >> $(DESIGN)-$(PROGRAM)-pnr.txt;
	icetime -p pcf/$(DESIGN)-$(PROGRAM).pcf -P uwg30 -d up5k -t $(DESIGN)-$(PROGRAM).asc 2>&1 | tee -a $(DESIGN)-$(PROGRAM)-pnr.txt
	icepack $(DESIGN)-$(PROGRAM).asc $(DESIGN)-$(PROGRAM).bin
#	sudo iceprog -S $(DESIGN)-$(PROGRAM).bin


# Software (program) recipe:
#	Change directory to the appropriate software's directory and run make if it exists.
program:
	cd source/$(PROGRAM) && ($(MAKE); $(MAKE) install)
	cd $(CURDIR) # Change back to the original directory


# The software compilation and the hardware build are required for this comprehensive recipe.
all: program design

clean-program:
	cd source/$(PROGRAM) && $(MAKE) clean
	cd $(CURDIR)
clean:
	rm -f *.json *.blif *.asc *.bin *.ys *-synth.v *-pnr.txt
