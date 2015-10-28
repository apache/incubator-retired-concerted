OBJS = obj/ConcDCTTest.o obj/ConcMATTest.o obj/ConcSegHashTableTest.o obj/ConcInvertedIndexTest.o obj/QueueLockTest.o obj/TestMain.o

all: mkdirectory testmain.exe obj/ConcDCTTest.o obj/ConcInvertedIndexTest.o obj/ConcMATTest.o obj/ConcSegHashTableTest.o obj/QueueLockTest.o obj/TestMain.o

mkdirectory :
	mkdir -p obj

testmain.exe : $(OBJS)
	g++  $(OBJS) -o ../testmain.exe -lpthread -lrt

obj/ConcDCTTest.o : ConcDCTTest.cpp
	g++ -c $< -o $@ -lpthread -lrt

obj/ConcInvertedIndexTest.o : ConcInvertedIndexTest.cpp
	g++ -c $< -o $@ -lpthread -lrt

obj/ConcMATTest.o : ConcMATTest.cpp
	g++ -c $< -o $@ -lpthread -lrt

obj/ConcQueue.o : ConcQueueTest.cpp
	g++ -c $< -o $@ -lpthread -lrt

obj/QueueLockTest.o : QueueLockTest.cpp
	g++ -c $< -o $@ -lpthread -lrt

obj/ConcSegHashTableTest.o : ConcSegHashTableTest.cpp
	g++ -c $< -o $@ -lpthread -lrt

obj/TestMain.o : TestMain.cpp
	g++ -c $< -o $@ -lpthread -lrt

clean:
	-rm -r obj