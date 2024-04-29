#ifndef POST_H
#define POST_H
#include <string>

class Post
{
public:

    //pre: none
    //post: Post has been initialized as an empty Post
    Post();

    //pre: none
    //post: Post has been initialized as a Post
    Post(int messageId, int ownerId, std::string message, int likes);
    
    //pre: none
    //post: Post has been given a certain string to be made when called
    std::string toString();

    //pre: none
    //post: returns messageId
    int getMessageId();
    
    //pre: none
    //post: returns ownerId
    int getOwnerId();
    
    //pre: none
    //post: returns message
    std::string getMessage();
    
    //pre: none
    //post: returns likes
    int getLikes();
    
    //pre: none
    //post: returns nothing
    virtual std::string getAuthor();
    
    //pre: none
    //post: returns true
    virtual bool getIsPublic();
private:
    int messageId_;
    int ownerId_;
    std::string message_;
    int likes_;
};

class IncomingPost : public Post
{
public:

    //pre: none
    //post: initializes an empty IncomingPost
    IncomingPost();

    //pre: none
    //post: initializes an IncomingPost
    IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author);

    //pre: none
    //post: IncomingPost has been given a certain string to be made when called
    std::string toString();

    //pre: none
    //post: return author
    std::string getAuthor();

    //pre: none
    //post: return isPublic
    bool getIsPublic();
private:
    std::string author_;
    bool isPublic_;
};
#endif

