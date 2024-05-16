# man flags
CC=clang
CXX=clang++
CFLAGS=-O1 -fno-omit-frame-pointer -gline-tables-only -fsanitize=address,undefined -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link
LIB_FUZZING_ENGINE=-fsanitize=fuzzer

# man compile
TARGET=Fuzzer

# man fuzzer
json=fuzz_json
string=fuzz_string
time=fuzz_time
xml=fuzz_xml
uri=fuzz_uri
digest=fuzz_digest

# program fuzzer
EXTCFLAGS=$(CFLAGS) -std=c++17 -DHAVE_CONFIG_H -g -O2 -Wall -Werror=partial-availability -Wall -Werror 
LibFLAGS=../lib/.libs/libfilezilla.a -lcrypt -lgnutls -lnettle -lhogweed -lgmp -lpthread

all: $(TARGET)

$(TARGET):
	$(CXX) $(EXTCFLAGS) -c $(json).cpp
	$(CXX) $(EXTCFLAGS) -c $(string).cpp
	$(CXX) $(EXTCFLAGS) -c $(time).cpp
	$(CXX) $(EXTCFLAGS) -c $(xml).cpp
	$(CXX) $(EXTCFLAGS) -c $(uri).cpp
	$(CXX) $(EXTCFLAGS) -c $(digest).cpp

	$(CXX) $(EXTCFLAGS) -o $(json) 		$(json).o 	$(LibFLAGS) $(LIB_FUZZING_ENGINE) $(CFLAGS)
	$(CXX) $(EXTCFLAGS) -o $(string) 	$(string).o $(LibFLAGS) $(LIB_FUZZING_ENGINE) $(CFLAGS)
	$(CXX) $(EXTCFLAGS) -o $(time) 		$(time).o 	$(LibFLAGS) $(LIB_FUZZING_ENGINE) $(CFLAGS)
	$(CXX) $(EXTCFLAGS) -o $(xml) 		$(xml).o 	$(LibFLAGS) $(LIB_FUZZING_ENGINE) $(CFLAGS)
	$(CXX) $(EXTCFLAGS) -o $(uri) 		$(uri).o 	$(LibFLAGS) $(LIB_FUZZING_ENGINE) $(CFLAGS)
	$(CXX) $(EXTCFLAGS) -o $(digest) 	$(digest).o $(LibFLAGS) $(LIB_FUZZING_ENGINE) $(CFLAGS)

clean:
	rm $(json) $(string) $(time) $(xml) $(uri) $(digest) *.o

.PHONY: all clean
