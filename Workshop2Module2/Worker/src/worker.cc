#include <memory>
#include <iostream>
#include <functional>
#include <glog/logging.h>
#include <stdlib.h> 
#include <conservator/ConservatorFrameworkFactory.h>
#include <zookeeper/zookeeper.h>

#include <grpc++/grpc++.h>

#include "zk.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using masterworker::AliveRequest;
using masterworker::AliveResponse;
using masterworker::MasterWorker;

class WorkerService final : public MasterWorker::Service {

  public:
    WorkerService() : gtid_("gatech") {}

  private:
    Status sendAliveRequest(::grpc::ServerContext* context,
        const ::masterworker::AliveRequest* request,
        ::masterworker::AliveResponse* response) override {
      response->set_reply(request->alivequery() + gtid_);
      LOG(INFO) << request->alivequery();
      google::FlushLogFiles(google::INFO);
      return Status::OK;
    }

    const std::string gtid_;
};


int main(int argc, char** argv)
{
  // Initialize Google's logging library.
    google::SetLogDestination(google::GLOG_INFO, "/home/ssinghal43/src/grpc/examples/cpp/helloworld/logs/server");
    google::InitGoogleLogging(argv[0]);

  std::string server_address, zk_address;

  if (argc == 3) {
    /* User defined server address */
    server_address = std::string(argv[1]);
    zk_address = std::string(argv[2]);
  }
  else if(argc ==2) {
    server_address = std::string(argv[1]);
    zk_address = "0.0.0.0:2181";
  }
  else {
    /* Default server address */
    server_address = "0.0.0.0:50056";
    zk_address = "0.0.0.0:2181";
  }

  std::string server_addressess(server_address);
  WorkerService service;
  ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
  static unique_ptr<ConservatorFramework> framework;
  //Create a new connection object to Zookeeper
  framework = std::move(factory.newClient(zk_address,2000));
  framework->start();
  //Create a Znode "/Workers" with data "test"
  auto response = framework->create()->forPath("/Workers",(char *) "test");
  //Verify that it was correctly created (see zookeeper.h at original project for error definitions")
  if(response == ZOK)
      std::cout<<"Created correctly: "<<std::endl;
  else
      std::cout<<"error creating the node"<<std::endl;

  //Verify that znode exists in the Zookeeper Server
  auto check = framework->checkExists()->forPath("/Workers");
  if(check == ZOK)
      std::cout<<"/Workers exists"<<std::endl;
  else
      std::cout<<"Failed creation of /Workers"<<std::endl;

  ServerBuilder builder;
  builder.AddListeningPort(server_addressess, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_addressess << std::endl;
  server->Wait();

  framework->close();
  return 0;
}
