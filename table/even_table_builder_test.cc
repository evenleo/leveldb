#include <iostream>
#include "leveldb/table_builder.h"
#include <leveldb/db.h>
#include <leveldb/comparator.h>
#include "leveldb/env.h"
#include "util/testharness.h"

namespace leveldb {

static std::string Reverse(const Slice& key) {
  std::string str(key.ToString());
  std::string rev("");
  for (std::string::reverse_iterator rit = str.rbegin(); rit != str.rend();
       ++rit) {
    rev.push_back(*rit);
  }
  return rev;
}

class ReverseKeyComparator : public Comparator {
 public:
  const char* Name() const override {
    return "leveldb.ReverseBytewiseComparator";
  }

  int Compare(const Slice& a, const Slice& b) const override {
    return BytewiseComparator()->Compare(Reverse(a), Reverse(b));
  }

  void FindShortestSeparator(std::string* start,
                             const Slice& limit) const override {
    std::string s = Reverse(*start);
    std::string l = Reverse(limit);
    BytewiseComparator()->FindShortestSeparator(&s, l);
    *start = Reverse(s);
  }

  void FindShortSuccessor(std::string* key) const override {
    std::string s = Reverse(*key);
    BytewiseComparator()->FindShortSuccessor(&s);
    *key = Reverse(s);
  }
};

void table_builder_test() {
  leveldb::Options options;
  leveldb::Env* env = leveldb::Env::Default();
  std::string test_dir = ".";
  std::string file_path = test_dir + "/table_builder.sst";

  leveldb::WritableFile* file = nullptr;
  ASSERT_OK(env->NewAppendableFile(file_path, &file));
  TableBuilder table_builder(options, file);
  table_builder.Add("even1", "hello1");
  table_builder.Add("even2", "hello2");
  table_builder.Add("even3", "hello3");
  table_builder.Add("even4", "hello4");
  table_builder.Add("even5", "hello5");
  table_builder.Add("even6", "hello6");
  table_builder.Add("even7", "hello7");

  table_builder.Finish();
  delete file;

}


}

int main() {
  leveldb::table_builder_test();
  return 0;
}