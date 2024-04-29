#include "user.h"
#include <vector>
#include <string>
#include "network.h"
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
#include <iostream>

Network::Network() {}
void Network::addUser(User* user) {
     users_.push_back(user);
}
int Network::addConnection(std::string s1, std::string s2) {
    int fid = getId(s1);
    int sid = getId(s2);
    if(fid == -1 || sid == -1)
    {
        return -1;
    } else {
        users_[fid]->addFriend(sid);
        users_[sid]->addFriend(fid);
        return 0;
    }
}
int Network::deleteConnection(std::string s1, std::string s2) {
    int fid = getId(s1);
    int sid = getId(s2);
    if(fid == -1 || sid == -1)
    {
        return -1;
    } else {
        users_[fid]->deleteFriend(sid);
        users_[sid]->deleteFriend(fid);
        return 0;
    }
}
int Network::getId(std::string name) {
    for(int i = 0; i < users_.size();i++){
        if(users_[i]->getName() == name){
            return users_[i]->getId();
        }
    }
    return -1;
}
int Network::readUsers(char* fname) {
    std::string myline;
    std::ifstream myfile(fname);
    int count = 0;
    int id = 0;
    std::string name;
    int year = 0;
    int zip = 0;
    while(getline (myfile,myline))
    {
        if(count == 1){
            std::stringstream ss(myline);
            ss >> id;
        }else if(count == 2){
            name = myline;
            name = name.substr(1);
        }else if(count == 3){
            std::stringstream ss(myline);
            ss >> year;
        }else if(count == 4){
            std::stringstream ss(myline);
            ss >> zip;
        }else if(count == 5){
            std::stringstream ss(myline);
            int f;
            std::set<int> friends;
            while (ss >> f){
                friends.insert(f);
            }
            User* user = new User(id,name,year,zip,friends);
            addUser(user);
        }
        count ++;
        if(count == 6){
            count = count - 5;
        }   
    }
    myfile.close();
    return 0;
}
int Network::writeUsers(char *fname) {
    std::ofstream myfile(fname);
    int totalUsers = numUsers();
    myfile << totalUsers << std::endl;
    for(int i = 0; i < users_.size();i++){
        myfile << users_[i]->getId() << std::endl;
        myfile << "\t" << users_[i]->getName() << std::endl;
        myfile << "\t" << users_[i]->getYear() << std::endl;
        myfile << "\t" << users_[i]->getZip() << std::endl;
        myfile << "\t";
        for(int temp:users_[i]->getFriends()){
            myfile << temp << " ";
        }
        myfile << std::endl;
    }
    myfile.close();
    return 0;
}
int Network::numUsers() { return users_.size(); }
User* Network::getUser(int id) {
    for(int i = 0; i < users_.size(); i++){
        if(users_[i]->getId() == id){
            return users_[i];
        }
    }
    return nullptr;
}
std::vector<int> Network::shortestPath(int from, int to)
{
    if (from == to) {
        return {from};
    }
    std::queue<int> frontier;
    std::vector<bool> visited(users_.size(),0);
    std::vector<int> prev(users_.size(), 0);
    frontier.push(from);
    visited[from] = true;
    prev[from] = -1;
    bool found = false;
    while (!frontier.empty()) {
        int currUser = frontier.front();
        frontier.pop();
        for(int friend_: users_[currUser]->getFriends()) {
            if(!visited[friend_]) {
                prev[friend_] = currUser;
                visited[friend_] = true;
                frontier.push(friend_);
                if (friend_ == to) {
                    found = true;
                    break;
                }
            }
        }
    }
    if (found) {
        std::vector<int> path;
        int previous = to;
        path.push_back(to);
        while(prev[previous] != -1) {
            path.push_back(prev[previous]);
            previous = prev[previous];
        }
        reverse(path.begin(), path.end());
        return path;
    } else {
        return {-1};
    }
}
std::vector<int> Network::distanceUser(int from, int &to,int distance)
{
    std::stack<std::pair<int,int>> stack;
    std::vector<bool> visited(users_.size(),0);
    std::vector<int> prev(users_.size(), 0);
    stack.push({from,0});
    visited[from] = true;
    prev[from] = -1;
    bool found = false;
    while (!stack.empty()) {
        std::pair<int,int> currUser = stack.top();
        stack.pop();
        for(int friend_: users_[currUser.first]->getFriends()) {
            if(!visited[friend_]) {
                prev[friend_] = currUser.first;
                visited[friend_] = true;
                stack.push({friend_,currUser.second+1});
                if (currUser.second == distance) {
                    found = true;
                    to = currUser.first;
                    break;
                }
            }
        }
    }
    if (found) {
        std::vector<int> path;
        int previous = to;
        path.push_back(to);
        while(prev[previous] != -1) {
            path.push_back(prev[previous]);
            previous = prev[previous];
        }
        reverse(path.begin(), path.end());
        return path;
    } else {
        to = -1;
        return {};
    }
}
std::vector<int> Network::suggestFriends(int who, int& score)
{
    int common = 0;
    std::vector<int> suggest(users_.size(),0);
    std::queue<int> frontier;
    std::vector<bool> visited(users_.size(),0);
    std::vector<int> distance(users_.size(),0);
    distance[who] = 0;
    visited[who] = true;
    bool found = false;
    frontier.push(who);
    while (!frontier.empty()) {
        int currUser = frontier.front();
        frontier.pop();
        for(int friend_: users_[currUser]->getFriends()) {
            if(!visited[friend_]) {
                distance[friend_] = distance[currUser]++;
                visited[friend_] = true;
                frontier.push(friend_); 
                if(distance[currUser] == 1)
                {
                    suggest[friend_]++;
                    if(suggest[friend_]++ > common)
                    {
                        common = suggest[friend_];
                    }
                }
                else if(distance[currUser] == 2)
                {
                    break;
                }
            }
        }
    }
    score = common;
    std::vector<int> commonFriends;
    for (int i = 0; i < suggest.size(); i++)
    {
        if(suggest[i] == common)
        {
            commonFriends.push_back(i);
        }
    }
    return commonFriends;
}
std::vector<std::vector<int>> Network::groups()
{
    std::stack<int> stack;
    std::vector<bool> visited(users_.size(),0);
    bool found = false;
    std::vector<std::vector<int>> group;
    for(int i = 0; i < users_.size(); i++)
    {
        std::vector<int> minigroup;
        if(!visited[i])
        {
            stack.push(i);
            //visited[i] = true;
            //minigroup.push_back(i);
            while (!stack.empty()) {
                int currUser = stack.top();
                stack.pop();
                for(int friend_: users_[currUser]->getFriends()) {
                    if(!visited[friend_]) {
                        visited[friend_] = true;
                        minigroup.push_back(friend_);
                        stack.push({friend_});
                    }
                }
            }
            group.push_back(minigroup);
        }
    }
    return group;
}
void Network::addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic)
{
    std::vector<Post*> posts;
        for(User* tempuser : users_)
        {
            for(Post* temp :tempuser->getPosts())
            {
                posts.push_back(temp);
            }
        }
    int messageId = posts.size();
    if(isIncoming)
    {
        IncomingPost* a = new IncomingPost(messageId,ownerId,message,likes,isPublic,authorName);
        users_[ownerId]->addPost(a);
    }
    else
    {    
        Post* a = new Post(messageId,ownerId,message,likes);
        users_[ownerId]->addPost(a);
    }
}

    std::string Network::getPostsString(int ownerId, int howMany, bool showOnlyPublic)
    {
        std::string many;
        
        int count = 0;
        for(int i = users_[ownerId]->getPosts().size()-1; i >= 0; i--)
        {
            if(count == howMany)
            {
                break;
            }
            if(showOnlyPublic && !users_[ownerId]->getPosts()[i]->getIsPublic())
            {

            }
            else
            {
                many = many + users_[ownerId]->getPosts()[i]->toString();
                many = many + "\n\n";
            }
            count++;
        }
        return many;
    }

    int Network::readPosts(char* fname)
    {
        std::string myline;
        std::ifstream myfile(fname);
        if(!myfile)
        {
            return -1;
        }
        int count = 0;
        int messageid = 0;
        std::string message;
        int ownerid = 0;
        int likes = 0;
        std::string pub;
        bool isPublic = false;
        std::string author;
        while(getline (myfile,myline))
        {
            if(count == 1){
                std::stringstream ss(myline);
                ss >> messageid;
            }else if(count == 2){
                message = myline;
                message = message.substr(1);
            }else if(count == 3){
                std::stringstream ss(myline);
                ss >> ownerid;
            }else if(count == 4){
                std::stringstream ss(myline);
                ss >> likes;
            }else if(count == 5){
                pub = myline;
                if(!(pub == ""))
                {
                    pub = pub.substr(1);
                    if(pub == "public")
                    {
                        isPublic = true;
                    }
                    else if(pub == "private")
                    {
                        isPublic = false;
                    }
                    getline (myfile,myline);
                    author = myline;
                    author = author.substr(1);
                    addPost(ownerid,message,likes,true,author,isPublic);
                }
                else{
                    addPost(ownerid,message,likes,false,"",false);
                    getline (myfile,myline);
                }
            }
            count ++;
            if(count == 6){
                count = count - 5;
            }   
        }
        myfile.close();
        return 0;
    }

    bool compare(Post* a, Post* b)
    {
        return a->getMessageId() < b->getMessageId();
    }

    int Network::writePosts(char* fname)
    {
        std::ofstream myfile(fname);
        if(!myfile)
        {
            return -1;
        }
        std::vector<Post*> posts;
        for(User* tempuser : users_)
        {
            for(Post* temp :tempuser->getPosts())
            {
                posts.push_back(temp);
            }
        }
        std::sort(posts.begin(),posts.end(),compare);

        int totalPosts = posts.size();
        myfile << posts.size() << std::endl;
        for(int i = 0; i < posts.size();i++){
            myfile << posts[i]->getMessageId() << std::endl;
            myfile << "\t" << posts[i]->getMessage() << std::endl;
            myfile << "\t" << posts[i]->getOwnerId() << std::endl;
            myfile << "\t" << posts[i]->getLikes() << std::endl;
            if(posts[i]->getAuthor() != "")
            {
                if(posts[i]->getIsPublic())
                {
                    myfile << "\tpublic" << std::endl;
                }
                else
                {
                    myfile << "\tprivate" << std::endl;
                }
                myfile << "\t" << posts[i]->getAuthor() << std::endl;
            }   
            else
            {
                myfile << std::endl;
                myfile << std::endl;
            }
        }
        myfile.close();
        return 0;
    }