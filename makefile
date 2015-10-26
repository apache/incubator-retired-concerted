# /*
#  * Licensed to the Apache Software Foundation (ASF) under one or more
#  * contributor license agreements.  See the NOTICE file distributed with
#  * this work for additional information regarding copyright ownership.
#  * The ASF licenses this file to you under the Apache License, Version 2.0
#  * (the "License"); you may not use this file except in compliance with
#  * the License.  You may obtain a copy of the License at
#  *
#  * http://www.apache.org/licenses/LICENSE-2.0
#  *
#  * Unless required by applicable law or agreed to in writing, software
#  * distributed under the License is distributed on an "AS IS" BASIS,
#  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  * See the License for the specific language governing permissions and
#  * limitations under the License.
#  */

OBJS = obj/CacheManager.o obj/ConcDCT.o obj/ConcMAT.o obj/ConcQueue.o obj/ConcSegHashTable.o obj/ConcInvertedIndex.o

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
	rm build/libconcerted.a
	rm -r obj
	rm -r build
