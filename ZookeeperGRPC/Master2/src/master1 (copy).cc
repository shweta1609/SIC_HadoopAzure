#include <memory>
#include <functional>
#include <algorithm>
#include <unistd.h>
#include <stdlib.h> 
#include <conservator/ConservatorFrameworkFactory.h>
#include <zookeeper/zookeeper.h>

//include <node_monitor.h>

#include <grpc++/grpc++.h>

#include "zk.grpc.pb.h"

using masterworker::MasterWorker;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using masterworker::AliveRequest;
using masterworker::AliveResponse;

class MasterClient {

 public:
  MasterClient(std::shared_ptr<Channel>);
  bool checkAlive(const std::string& requestMsg, std::string& responseMsg);

 private:
  std::unique_ptr<MasterWorker::Stub> stub_;
};

MasterClient::MasterClient(std::shared_ptr<Channel> channel)
  : stub_(MasterWorker::NewStub(channel)) 
  {}

bool MasterClient::checkAlive(const std::string& requestMsg, std::string& responseMsg) {
  AliveRequest request;
  request.set_alivequery(requestMsg);

  AliveResponse response;
  ClientContext context;

  Status status = stub_->sendAliveRequest(&context, request, &response);

  if (!status.ok()) {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    return false;
  }

  responseMsg = response.reply();

  return true;
}
// void existsWatcherFunc(zhandle_t *zh, int type,
//                         int state, const char *path,void *watcherCtx);
int getNodeNumFromName(std::string name);
int getNodeNumFromName(std::string name)
{
   return std::stoi(name.substr(2));
}
// Node Monitor class 
class NodeMonitor{
    public:
        NodeMonitor(unique_ptr<ConservatorFramework> framework) : framework(std::move(framework)),iamLeader(false){}
        void startNodeMonitor(void);
        void stopNodeMonitor(void);
        void createRootIfNotExists(void); 
        void createChildAndSetWatch(void);
        std::vector<int> getMastersChildList(void);
        bool amItheLeader(void);
        std::string getPreviousNode(void);
        // void existsWatcherFunc(void);
        static void existsWatcherFunc(zhandle_t *zh, int type,
                            int state, const char *path,void *watcherCtx);
    private:
        unique_ptr<ConservatorFramework> framework;
        std::string myName;
        int myNodeNum;
        bool iamLeader;
};

void NodeMonitor::startNodeMonitor(void){
    framework->start();
}

void NodeMonitor::stopNodeMonitor(void){
    framework->close();
}

void NodeMonitor::createRootIfNotExists(void){
    //Create a Znode "/foo" with data "test"
    auto response = framework->create()->forPath("/Masters",(char *) "test");
    //Verify that it was correctly created (see zookeeper.h at original project for error definitions")
    if(response == ZOK)
        std::cout<<"Created correctly: "<<std::endl;
    else
        std::cout<<"error creating the node"<<std::endl;

    //Verify that znode exists in the Zookeeper Server
    auto check = framework->checkExists()->forPath("/Masters");
    if(check == ZOK)
        std::cout<<"/Masters exists"<<endl;
    else
        std::cout<<"Failed creation of /Masters"<<std::endl;
}

void NodeMonitor::createChildAndSetWatch(void){
    std::string childpath;
    //Create an ephemeral and sequential node.
    auto ephemeral = framework->create()->withFlags(ZOO_EPHEMERAL|ZOO_SEQUENCE)->forPath("/Masters/N_",NULL,childpath);
    if(ephemeral == ZOK)
    {
      std::cout<<"Ephemeral created correctly"<<std::endl;
    }
    else
    {
      std::cout<<"Error creating ephimeral"<<std::endl;
    }
    std::size_t found = childpath.find_last_of("/\\");
    myName = childpath.substr(found+1);
    myNodeNum = getNodeNumFromName(myName.substr(2));
    std::cout<<"My name is ----->"<<myName<<" : "<<myNodeNum<<std::endl;
    std::string prevNode = getPreviousNode();
    if(prevNode.compare(myName)!=0)
    {
        // std::function<void()> watchFunc = std::bind(&NodeMonitor::existsWatcherFunc, this);
        framework->checkExists()->withWatcher(existsWatcherFunc, (void*) framework.get())->forPath("/Masters/"+prevNode);
    }
    else
    {
        iamLeader = true;
    }
    
}

std::string NodeMonitor::getPreviousNode(void)
{
    std::vector<int> retval;
    std::vector<std::string> nodeList = framework->getChildren()->forPath("/Masters");
    std::sort(nodeList.begin(), nodeList.end());

	auto it = std::find(nodeList.begin(), nodeList.end(), myName);
 
    int index = distance(nodeList.begin(), it);
    if(index)
        index--;
    return nodeList[index];
}

std::vector<int> NodeMonitor::getMastersChildList(void){
    std::vector<int> retval;
    std::vector<std::string> nodeList = framework->getChildren()->forPath("/Masters");
    for(auto &&child : nodeList)
    {
        retval.push_back(getNodeNumFromName(child));
    }
    return retval;
}

bool NodeMonitor::amItheLeader(void){
    return iamLeader;
}

void NodeMonitor::existsWatcherFunc(zhandle_t *zh, int type,
                        int state, const char *path,void *watcherCtx) {
    std::cout << "exists watcher function called" << std::endl;
    bool retval = false;
    std::vector<int> nodeList;
    nodeList = this->getMastersChildList();
    int min_val=*std::min_element(nodeList.begin(),nodeList.end());
    if(this->myNodeNum == min_val)
        this->iamLeader = true;
    else
    {
        std::string prevNode = obj->getPreviousNode();
        // std::function<void> watchFunc = std::bind(&NodeMonitor::existsWatcherFunc, this);
        this->framework->checkExists()->withWatcher(existsWatcherFunc, watcherCtx)->forPath("/Masters/"+prevNode);
    }
    
}

int main(int argc, char** argv)
{
    
  std::string server_address;
  if (argc == 2) {
    /* User defined server address */
    server_address = std::string(argv[1]);
  }
  else {
    /* Default server address */
    server_address = "0.0.0.0:50056";
  }
    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    //Create a new connection object to Zookeeper
    // unique_ptr<ConservatorFramework> framework = factory.newClient("localhost:2181",10000);
    NodeMonitor nodeMonitor(factory.newClient("localhost:2181",10000));
    nodeMonitor.startNodeMonitor();
    nodeMonitor.createRootIfNotExists();
    nodeMonitor.createChildAndSetWatch();

    while(true){
        if(nodeMonitor.amItheLeader())
        {
            MasterClient master_client(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));
            std::string workerResponse;
            master_client.checkAlive("hello ",workerResponse);
            std::cout<<workerResponse<<std::endl;
        }
        sleep(10);
    }
    nodeMonitor.stopNodeMonitor();
    return 0;
}