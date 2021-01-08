#include "db/memtable.h"
#include <iostream>

namespace leveldb {

void memtable_test() {
  InternalKeyComparator cmp(BytewiseComparator());
  MemTable *memtable = new MemTable(cmp);
  memtable->Ref();
  memtable->Add(123, kTypeValue, "even", "leo");
  LookupKey key("even", 123);
  std::string value;
  Status status;
  bool res = memtable->Get(key, &value, &status);
  assert(res);
  assert(value.compare("leo") == 0);
  assert(status.ok());
}

}

int main(int argc, char** argv) {
  leveldb::memtable_test();
  return 0;
}