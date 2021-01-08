#include <iostream>
#include <memory>

#include "db/log_writer.h"
#include "leveldb/env.h"

namespace leveldb {

class EvenStringDest : public WritableFile {
   public:
    Status Close() override { return Status::OK(); }
    Status Flush() override {
      std::cout << contents_ << std::endl;
      return Status::OK();
    }
    Status Sync() override { return Status::OK(); }
    Status Append(const Slice& slice) override {
      contents_.append(slice.data(), slice.size());
      return Status::OK();
    }

    std::string contents_;
  };

void even_log_test() {
  EvenStringDest dest;
  std::shared_ptr<log::Writer> writer = std::make_shared<log::Writer>(&dest);
  std::string msg = "evenleo";
  writer->AddRecord(Slice(msg));
}

}

int main(int argc, char** argv) {
  leveldb::even_log_test();
  return 0;
}