// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "tests.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <iostream>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

using boost::shared_ptr;

using namespace  std;

class testsHandler : virtual public testsIf {
 public:
  testsHandler() {
    // Your initialization goes here
  }

  void test1(std::string& _return, const std::string& doc_id) {
    // Your implementation goes here
    cout << __FILE__ << __LINE__ <<  "test1" << endl;
    _return = "test1";
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<testsHandler> handler(new testsHandler());

  shared_ptr<TProcessor> processor(new testsProcessor(handler));
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  // using thread pool with maximum 15 threads to handle incoming requests
  shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(15);
  shared_ptr<PosixThreadFactory> threadFactory = shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
  threadManager->threadFactory(threadFactory);
  threadManager->start();
  TNonblockingServer server(processor, protocolFactory, 8888, threadManager);
  server.serve();
  return 0;
}

