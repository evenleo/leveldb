#include <iostream>

#include "leveldb/env.h"
#include "port/port.h"
#include "util/env_posix_test_helper.h"
#include "util/testharness.h"
#include "db/log_reader.h"

using namespace std;

 struct LogReporter : public leveldb::log::Reader::Reporter {
    void Corruption(size_t bytes, const leveldb::Status& s) override {
    }
  };

int main() {
  leveldb::Env* env = leveldb::Env::Default();
  std::string test_dir = ".";
  std::string file_path = test_dir + "/close_on_exec_appendable.txt";

  LogReporter reporter;
  leveldb::SequentialFile* file = nullptr;
  ASSERT_OK(env->NewSequentialFile(file_path, &file));
  leveldb::log::Reader reader(file, &reporter, true, 0);

  std::string scratch;
  leveldb::Slice record;

  while (reader.ReadRecord(&record, &scratch)) {
    std::cout << "record: " << record.ToString() << std::endl;
  }
  
  delete file;

  return 0;
}