#include <string>
#include <set>
#include "user.h"

User::User() {}
User::User(int id, std::string name, int year, int zip, std::set<int> friends) {
    id_ = id;
    name_ = name;
    year_ = year;
    zip_ = zip;
    friends_ = friends;
}
void User::addFriend(int id) {
    friends_.insert(id);
}
void User::deleteFriend(int id) {
    auto iter = friends_.find(id);        
    if(iter == friends_.end()) {
        return;
    } else {
        friends_.erase(iter);
    }
}
int User::getId() { return id_; }
std::string User::getName() { return name_; }
int User::getYear() { return year_; }
int User::getZip() { return zip_; }
std::set<int>& User::getFriends() { return   friends_; }

void User::addPost(Post* a)
{
    messages_.push_back(a);
}

std::vector<Post*> User::getPosts()
{
    return messages_;
}
    
std::string User::getPostsString(int howMany, bool showOnlyPublic)
{
    std::string many;
    int count = 0;
    for(int i = messages_.size()-1; i >= 0; i--)
    {
        if(count == howMany)
        {
            break;
        }
        if(showOnlyPublic && !messages_[i]->getIsPublic())
        {

        }
        else
        {
            many = many + messages_[i]->toString();
            many = many + "\n\n";
        }
        count++;
    }
    return many;
} 