/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to you under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <iostream>
#include "../include/tests/ConcDCTTest.h"
#include "../include/tests/ConcMATTest.h"
#include "../include/tests/ConcSegHashTableTest.h"
#include "../include/tests/ConcInvertedIndexTest.h"
#include "../include/tests/QueueLockTest.h"

using namespace std;

int main()
{
  int res1 = 0;
  int res2 = 0;
  int res3 = 0;

  res1 = testDCT(0);
  if (res1)
    throw;

  res2 = testMAT(0);
  if (res2)
    throw;

  testSegHashTable(0);

  res3 = testInvertedIndex(0);
  if (res3)
    throw;

  cout <<"All tests passed"<<endl;
}
