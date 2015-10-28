OBJS = obj/CacheManager.o obj/ConcDCT.o obj/ConcMAT.o obj/ConcQueue.o obj/ConcSegHashTable.o obj/ConcInvertedIndex.o
EXECUTABLE = ./testmain.exe
TEST_DIR = test/

.PHONY : all clean $(TEST_DIR) $(EXECUTABLE)

all: mkdirectory libconcerted.a obj/CacheManager.o obj/ConcDCT.o obj/ConcInvertedIndex.o obj/ConcMAT.o obj/ConcQueue.o obj/ConcSegHashTable.o

mkdirectory :
	mkdir -p obj
	mkdir -p build

libconcerted.a : $(OBJS)
	ar cr build/libconcerted.a $(OBJS)

obj/CacheManager.o : include/CacheManager.h
	g++ -c $< -o $@

obj/ConcDCT.o : include/ConcDCT.h
	g++ -c $< -o $@

obj/ConcInvertedIndex.o : include/ConcInvertedIndex.h
	g++ -c $< -o $@

obj/ConcMAT.o : include/ConcMAT.h
	g++ -c $< -o $@

obj/ConcQueue.o : include/ConcQueue.h
	g++ -c $< -o $@

obj/ConcSegHashTable.o : include/ConcSegHashTable.h
	g++ -c $< -o $@

clean:
	-rm build/libconcerted.a
	-rm -r obj
	-rm -r build
	-rm testmain.exe
	$(MAKE) --directory $(TEST_DIR) $@

check : $(TEST_DIR)
	$(EXECUTABLE)

$(TEST_DIR):
	$(MAKE) --directory $@

$(EXECUTABLE):
	./testmain.exe

run : $(EXECUTABLE)
