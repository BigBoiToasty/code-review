#ifndef USER_H
#define USER_H
#include "post.h"
#include <string>
#include <set>
#include <vector>

class User {
public:
    //pre: none
    //post: User has been initialized as an empty user
    User();
    
    //pre: none
    //post: User has been initialized as a user
    User(int id, std::string name, int year, int zip, std::set<int> friends);

    //pre: none
    //post: id of friend has been added to the set of friends_
    void addFriend(int id);

    //pre: id is in the set of friends_
    //post: id of friends in the set of friends_ has been deleted
    void deleteFriend(int id);

    //pre: none
    //post: returns the id of the user
    int getId();

    //pre: none
    //post: returns the name of the user
    std::string getName();
    
    //pre: none
    //post: returns the year of the user
    int getYear();
    
    //pre: none
    //post: returns the zipcode of the user
    int getZip();
    
    //pre: none
    //post: returns the set of friends of the user
    std::set<int>& getFriends();

    //pre: none
    //post: adds a Post to messages_
    void addPost(Post*);

    //pre: none
    //post: returns messages_
    std::vector<Post*> getPosts();
    
    //pre: none
    //post: returns the amount of recent posts the user requested either public or private
    std::string getPostsString(int howMany, bool showOnlyPublic);

private:
    int id_;
    std::string name_;
    int year_;
    int zip_; 
    std::set<int> friends_;
    std::vector<Post*> messages_;
};

#endif