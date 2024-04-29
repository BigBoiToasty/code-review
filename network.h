#ifndef NETWORK_H
#define NETWORK_H
#include "user.h"
#include <vector>
#include <string>

class Network {
public:
    //pre: none
    //post: Network has been initialized as an empty network
    Network();
    
    //pre: none
    //post: user has been added to the vector of users
    void addUser(User*);
    
    //pre: Users with the names are already in the vector of users_
    //post: adds each id of each user into each other's friends_
    int addConnection(std::string s1, std::string s2);
    
    //pre: Useres with the names are already in the vector of users_
    //post: adds each id of each user into each other's friends_
    int deleteConnection(std::string s1, std::string s2);
    
    //pre: a User with the name is already in the vector of users_
    //post: finds the id of the User with the given name
    int getId(std::string name);
    
    //pre: none
    //post: reads a text file with all the Users and inputs all their information into users)
    int readUsers(char* fname);
    
    //pre: none
    //post: writes a text file with all the Users and their information
    int writeUsers(char *fname);
    
    //pre: none
    //post: returns the amount of Users in the vector
    int numUsers();
    
    //pre: there is a user with this id in the vector
    //post: returns the pointer corresponding to the User with the id
    User* getUser(int id);

    //pre: from and to are both ids that exist in users_
    //post: returns the path to get to one friend to another
    std::vector<int> shortestPath(int from,int to);

    //pre: from exists as an id in users_
    //post: returns the path to the user that is the distance away from the from
    std::vector<int> distanceUser(int from, int &to,int distance);

    //pre: the user has friends
    //post: returns a vector of friends with the highest score of common friends with the user
    std::vector<int> suggestFriends(int who, int& score);

    //pre: none
    //post: returns a vector of vectors that contain friends that are connected components
    std::vector<std::vector<int>> groups();

    //pre: none
    //post: adds an Incoming post or regular post to a user's messages_
    void addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic);

    //pre: none
    //post: returns a certain amount of posts from the most recents posts from a specific user either public or private
    std::string getPostsString(int ownerId, int howMany, bool showOnlyPublic);

    //pre: a working file
    //post: reads a text file with all the posts and inputs their information to user's messages_
    int readPosts(char* fname);

    //pre: none
    //post: writes a text file with all the Posts and their information
    int writePosts(char* fname);

private:
    std::vector<User*> users_;
};

#endif