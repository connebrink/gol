PRJNAME=life

MAINSRC=src/$(PRJNAME).cpp

DEPDIR=bin
OUTDIR=trg
OUTDIRBIN=$(OUTDIR)/bin

CXX=g++
CXXFLAGS=-std=c++20
CXXFLAGSREL=$(CXXFLAGS) -static -O2 -s -g0 -DNDEBUG
CXXFLAGSDEB=$(CXXFLAGS) -O0 -g -DDEBUG

LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system

.PHONY: all

all: clean debug

debug:
	@mkdir -p $(OUTDIRBIN)
	@echo "Compile : $(MAINSRC) -> $(OUTDIRBIN)/$(PRJNAME)"
	@ $(CXX) $(CXXFLAGSDEB) -o $(OUTDIRBIN)/$(PRJNAME) $(MAINSRC) $(LDLIBS)
	@mkdir -p $(DEPDIR)
	@ cp $(OUTDIRBIN)/$(PRJNAME) $(DEPDIR) 

release: clean
	@mkdir -p $(OUTDIRBIN)
	@echo "Compile : $(MAINSRC) -> $(OUTDIRBIN)/$(PRJNAME)"
	@ $(CXX) $(CXXFLAGSREL) -o $(OUTDIRBIN)/$(PRJNAME) $(MAINSRC) $(LDLIBS)
	@mkdir -p $(DEPDIR)
	@ cp $(OUTDIRBIN)/$(PRJNAME) $(DEPDIR) 

clean:
	@rm -rf $(OUTDIR)
