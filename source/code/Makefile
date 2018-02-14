BINDIR  := ../bin
OBJDIR  := ../build
APPNAME := $(BINDIR)/call_cost_calculator
SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,$(OBJDIR)/%.o, $(SOURCES))

INCLUDE := 
LIBPATH := 
LIBS    := 
CXXFLAGS := -std=c++98 -Wall -Wextra -Wpedantic -Werror	-Wabi -Wabi-tag        \
-Waddress -Waggressive-loop-optimizations -Warray-bounds -Wattributes          \
-Wcast-align -Wcast-qual -Wchar-subscripts -Wclobbered                         \
-Wconditionally-supported -Wconversion -Wconversion-null -Wcoverage-mismatch   \
-Wcpp -Wctor-dtor-privacy -Wdate-time -Wdelete-incomplete                      \
-Wdelete-non-virtual-dtor -Wdeprecated -Wdeprecated-declarations               \
-Wdisabled-optimization -Wdiv-by-zero -Wdouble-promotion -Weffc++ -Wempty-body \
-Wenum-compare -Wextra -Wfloat-equal -Wformat-contains-nul -Wformat-extra-args \
-Wformat-nonliteral -Wformat-security -Wformat-y2k -Wformat-zero-length        \
-Wfree-nonheap-object -Wignored-qualifiers -Winherited-variadic-ctor           \
-Winit-self -Winline -Wint-to-pointer-cast -Winvalid-memory-model              \
-Winvalid-offsetof -Wlogical-op -Wlong-long -Wmain -Wmaybe-uninitialized       \
-Wmemset-transposed-args -Wmissing-braces -Wmissing-declarations               \
-Wmissing-field-initializers -Wnarrowing -Wnoexcept -Wnon-template-friend      \
-Wnon-virtual-dtor -Wnonnull -Wold-style-cast -Wopenmp-simd -Woverflow         \
-Woverlength-strings -Woverloaded-virtual -Wpacked -Wpacked-bitfield-compat    \
-Wparentheses -Wpedantic -Wpmf-conversions -Wpointer-arith -Wpragmas           \
-Wredundant-decls -Wreorder -Wreturn-local-addr -Wreturn-type -Wsequence-point \
-Wshadow -Wsign-compare -Wsign-promo -Wsizeof-pointer-memaccess                \
-Wstack-protector -Wstrict-null-sentinel -Wsuggest-attribute=const             \
-Wsuggest-attribute=format -Wsuggest-attribute=noreturn                        \
-Wsuggest-attribute=pure -Wswitch -Wswitch-default -Wsync-nand -Wsynth         \
-Wtrampolines -Wtype-limits -Wuninitialized -Wunknown-pragmas                  \
-Wunsafe-loop-optimizations -Wunused -Wunused-but-set-parameter                \
-Wunused-but-set-variable -Wunused-function -Wunused-label                     \
-Wunused-local-typedefs -Wunused-macros -Wunused-parameter -Wunused-result     \
-Wunused-value -Wunused-variable -Wuseless-cast -Wvarargs                      \
-Wvector-operation-performance -Wvirtual-move-assign -Wvla                     \
-Wvolatile-register-var -Wwrite-strings

CXX  := g++

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJECTS) -o $(APPNAME) $(LIBPATH) $(LIBS)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@
  
clean:
	rm -rf $(OBJDIR)/*
	rm -f $(APPNAME)
