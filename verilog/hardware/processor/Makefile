# Purely for control over output build name. Always gets HDL source code from sail-core directory.
DESIGN  = sail

# Decides source code directory for software.
PROGRAM = bsort

ATTEMPTS := 5
NUMBERS := $(shell seq 1 ${ATTEMPTS})
JOBS := $(addprefix pnr,${NUMBERS})


# First recipe in the Makefile is the default recipe
design: synth ${JOBS}

# Hardware (design) recipe:
#	Copy the hex files to be besides all the design .v files
#	Copy the toplevel design if its not already present into the processor build (to allow for different builds with different toplevels).
#	In the yosys script, change the project name, remove CSR.v from the build, and tell it to output the
#	final synthesised .v file for examination, saving this all as a new yscript into the current directory.
#	Run yosys quietly with desired project name.
#	If one doesn't already exist, create a custom pcf for the design+program build by copying and renaming sail.pcf.
#	Run the rest of the build with the desired project naming system.
#	The output of nextpnr and icetime is saved into one file, with 4 extra newlines to separate them.
synth:
	cat ../../../yscripts/sail.ys |\
	sed "s/sail/$(DESIGN)-$(PROGRAM)/" |\
	sed "s/verilog\/CSR\.v //g" |\
	sed "s/blif$$/blif\nwrite_verilog $(DESIGN)-$(PROGRAM)-synth.v/" > $(DESIGN)-$(PROGRAM).ys
	yosys -q $(DESIGN)-$(PROGRAM).ys
	test -s pcf/$(DESIGN)-$(PROGRAM).pcf || cp pcf/sail.pcf pcf/$(DESIGN)-$(PROGRAM).pcf;
${JOBS}: pnr%: synth
	nextpnr-ice40 --up5k --package uwg30 --json $(DESIGN)-$(PROGRAM).json --pcf pcf/$(DESIGN)-$(PROGRAM).pcf --asc $(DESIGN)-$(PROGRAM)$*.asc --log $(DESIGN)-$(PROGRAM)$*-pnr.txt
	echo >> $(DESIGN)-$(PROGRAM)$*-pnr.txt; echo >> $(DESIGN)-$(PROGRAM)$*-pnr.txt; echo >> $(DESIGN)-$(PROGRAM)$*-pnr.txt; echo >> $(DESIGN)-$(PROGRAM)$*-pnr.txt;
	icetime -p pcf/$(DESIGN)-$(PROGRAM).pcf -P uwg30 -d up5k -t $(DESIGN)-$(PROGRAM)$*.asc 2>&1 | tee -a $(DESIGN)-$(PROGRAM)$*-pnr.txt
	{ { date +"%D %T"; echo $(DESIGN)-$(PROGRAM)$*; } | tr "\n" "\t\t"; tail -n 2 $(DESIGN)-$(PROGRAM)$*-pnr.txt | head -n 1; }  >> pnr-timings.txt
	icepack $(DESIGN)-$(PROGRAM)$*.asc $(DESIGN)-$(PROGRAM)$*.bin



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
	rm programs/*
clean:
	rm -f *.json *.blif *.asc *.bin *.ys *-synth.v *-pnr.txt
