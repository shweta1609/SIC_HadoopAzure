#include <memory>
#include <functional>
#include <algorithm>
#include <unistd.h>
#include <stdlib.h> 
#include <conservator/ConservatorFrameworkFactory.h>
#include <zookeeper/zookeeper.h>

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
  enum workerstate {AVAILABLE=0,BUSY=1};
	
  std::unordered_map<std::string, workerstate> worker_state;
  std::vector<std::string> worker_ip;
  std::string user_id;
  size_t n_partitions;
  size_t n_workers;
  size_t n_shards;
  // std::vector<FileShard> file_shard;
  std::vector<bool> shard_processed;
  std::vector<std::vector<std::string>> intermed_files;
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

int getNodeNumFromName(std::string name);
int getNodeNumFromName(std::string name)
{
   return std::stoi(name.substr(2));
}

void startNodeMonitor(void);
void stopNodeMonitor(void);
void createRootIfNotExists(void); 
void createChildAndSetWatch(void);
std::vector<int> getMastersChildList(void);
bool amItheLeader(void);
std::string getPreviousNode(void);

void existsWatcherFunc(zhandle_t *zh, int type,
                    int state, const char *path,void *watcherCtx);

static unique_ptr<ConservatorFramework> framework;
static std::string myName;
static int myNodeNum;
static bool iamLeader;


void startNodeMonitor(void){
    framework->start();
}

void stopNodeMonitor(void){
    framework->close();
}

void createRootIfNotExists(void){
    //Create a Znode "/Masters" with data "test"
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

void createChildAndSetWatch(void){
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
        framework->checkExists()->withWatcher(existsWatcherFunc, (void*) framework.get())->forPath("/Masters/"+prevNode);
    }
    else
    {
        iamLeader = true;
    }
    
}

std::string getPreviousNode(void)
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

std::vector<int> getMastersChildList(void){
    std::vector<int> retval;
    std::vector<std::string> nodeList = framework->getChildren()->forPath("/Masters");
    for(auto &&child : nodeList)
    {
        retval.push_back(getNodeNumFromName(child));
    }
    return retval;
}

bool amItheLeader(void){
    return iamLeader;
}

void existsWatcherFunc(zhandle_t *zh, int type,
                        int state, const char *path,void *watcherCtx) {
    std::cout << "exists watcher function called" << std::endl;
    bool retval = false;
    std::vector<int> nodeList;
    nodeList = getMastersChildList();
    int min_val=*std::min_element(nodeList.begin(),nodeList.end());
    if(myNodeNum == min_val)
        iamLeader = true;
    else
    {
        std::string prevNode = getPreviousNode();
        framework->checkExists()->withWatcher(existsWatcherFunc, watcherCtx)->forPath("/Masters/"+prevNode);
    }
    
}

int main(int argc, char** argv)
{

  std::string server_address, zk_address, my_address;
  if (argc == 4) {
    /* User defined server address */
    server_address = std::string(argv[1]);
    zk_address = std::string(argv[2]);
    my_address = (std::string(argv[3])+" ");
  }
  else if(argc == 3) {
    server_address = std::string(argv[1]);
    zk_address = std::string(argv[2]);
    my_address = "Master2";
  }
  else if(argc == 2) {
    server_address = std::string(argv[1]);
    zk_address = "0.0.0.0:2181";
    my_address = "Master2";
  }
  else {
    /* Default server address */
    server_address = "0.0.0.0:50056";
    zk_address = "0.0.0.0:2181";
    my_address = "Master2";
  }

    ConservatorFrameworkFactory factory = ConservatorFrameworkFactory();
    //Create a new connection object to Zookeeper
    framework = std::move(factory.newClient(zk_address,2000));

    startNodeMonitor();
    createRootIfNotExists();
    createChildAndSetWatch();

    while(true){
        if(amItheLeader())
        {
            MasterClient master_client(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));
            std::string workerResponse;
            master_client.checkAlive(my_address+" ",workerResponse);
            std::cout<<workerResponse<<std::endl;
        }
        sleep(6);
    }
    stopNodeMonitor();
    return 0;
}
