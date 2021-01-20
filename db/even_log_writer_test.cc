#include <iostream>

#include "leveldb/env.h"
#include "port/port.h"
#include "util/env_posix_test_helper.h"
#include "util/testharness.h"
#include "db/log_writer.h"

using namespace std;

int main() {
  leveldb::Env* env = leveldb::Env::Default();
  std::string test_dir = ".";
  std::string file_path = test_dir + "/close_on_exec_appendable.txt";

  leveldb::WritableFile* file = nullptr;
  ASSERT_OK(env->NewAppendableFile(file_path, &file));
  leveldb::log::Writer writer(file);
  writer.AddRecord("evenleo");
  writer.AddRecord("jack");
  
  delete file;

  // ASSERT_OK(env->DeleteFile(file_path));
  return 0;
}