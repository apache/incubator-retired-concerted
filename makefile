OBJS = obj/CacheManager.o obj/ConcDCT.o obj/ConcMAT.o obj/ConcQueue.o obj/ConcSegHashTable.o obj/ConcInvertedIndex.o

all: mkdirectory libconcerted.a obj/CacheManager.o obj/ConcDCT.o obj/ConcInvertedIndex.o obj/ConcMAT.o obj/ConcQueue.o obj/ConcSegHashTable.o

mkdirectory :
	mkdir -p obj
	mkdir -p build

libconcerted.a : $(OBJS)
	ar cr build/libconcerted.a $(OBJS)

obj/CacheManager.o : src/CacheManager.h
	g++ -c $< -o $@

obj/ConcDCT.o : src/ConcDCT.h
	g++ -c $< -o $@

obj/ConcInvertedIndex.o : src/ConcInvertedIndex.h
	g++ -c $< -o $@

obj/ConcMAT.o : src/ConcMAT.h
	g++ -c $< -o $@

obj/ConcQueue.o : src/ConcQueue.h
	g++ -c $< -o $@

obj/ConcSegHashTable.o : src/ConcSegHashTable.h
	g++ -c $< -o $@

clean:
	rm build/libconcerted.a
	rm -r obj
	rm -r build