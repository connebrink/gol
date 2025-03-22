SRCDIR=src
SUBTOOLSRCDIR=
SUBTOOLSRCFILES=
SUBTOOLTARGET=

OUTDIR=trg
OUTDIRBIN=$(OUTDIR)/bin
OUTDIROBJ=$(OUTDIR)/obj

CXX=g++
CXXCHK=clang++

CXXFLAGS=-std=c++20 -Wall
CXXFLAGSREL=$(CXXFLAGS) -O2 -s -g0 -DNDEBUG
CXXFLAGSDEB=$(CXXFLAGS) -O0 -g
CXXFLAGSREAL=$(CXXFLAGS)
CXXFLAGSADD=

LFLAGS=-static -o
LFLAGSREL=$(LFLAGS)
LFLAGSDEB=$(LFLAGS)
LFLAGSADD=

SRCDIRSTOOLS  := $(shell find $(SRCDIR) -maxdepth 3 -type d)
SRCFILESTOOLS := $(foreach dir,$(SRCDIRSTOOLS),$(wildcard $(dir)/*.cpp))

.PHONY: all

all: clean debug

define addFlags
	$(eval LFLAGSADD=$(if $(strip $(findstring 4dsql,$1)),-l4d_sql,))
endef

define compile
	@echo "\nSource :" $1
	$(call addFlags,$1)
	@ $(CXX) $(CXXFLAGSREAL) $(CXXFLAGSADD) $(LFLAGSADD) $(LFLAGS) $(addprefix $(OUTDIRBIN)/,$(notdir $(patsubst %.cpp,%,$1))) $1
	@echo "  Tool :" $(addprefix $(OUTDIRBIN)/,$(notdir $(patsubst %.cpp,%,$1)))
endef

debug: CXXFLAGSREAL=$(CXXFLAGSDEB)
debug: clean
	@mkdir -p $(OUTDIRBIN)
	@ $(foreach s,$(SRCFILESTOOLS),$(call compile,$(s)))
	@echo "\n"

release: CXXFLAGSREAL=$(CXXFLAGSREL)
release: clean
	@mkdir -p $(OUTDIRBIN)
	@ $(foreach s,$(SRCFILESTOOLS),$(call compile,$(s)))
	@echo "\n"

stool:
	@mkdir -p $(OUTDIRBIN)
	@rm -rf $(OUTDIRBIN)/$(SUBTOOLTARGET)
	@ $(foreach s,$(SUBTOOLSRCFILES),$(call compile,$(s)))
	@echo "\n"

dupfind: SUBTOOLTARGET=dupfind
dupfind: SUBTOOLSRCFILES=$(foreach dir,$(SRCDIR)/01-dupfind,$(wildcard $(dir)/*.cpp))
dupfind: stool

4dsql: SUBTOOLTARGET=4dsql
4dsql: SUBTOOLSRCFILES=$(foreach dir,$(SRCDIR)/02-4dsql,$(wildcard $(dir)/*.cpp))
4dsql: stool

check-syntax:
	$(call addFlags,$1)
	$(CXXCHK) $(CXXFLAGS) $(CXXFLAGSADD) -s -o /dev/null -S $(CHK_SOURCES)

clean:
	@rm -rf $(OUTDIR)
