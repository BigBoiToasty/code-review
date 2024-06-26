#include "post.h"
#include <string>

Post::Post() {}
    
Post::Post(int messageId, int ownerId, std::string message, int likes)
{
    messageId_ = messageId;
    ownerId_ = ownerId;
    message_ = message;
    likes_ = likes;
}
    
std::string Post::toString()
{
    std::string number = std::to_string(getLikes());
    return message_ + " Liked by " + number + " people.";
}

int Post::getMessageId()
{
    return messageId_;
}
    
int Post::getOwnerId()
{
    return ownerId_;
}
    
std::string Post::getMessage(){
    return message_;
}
    
int Post::getLikes()
{
    return likes_;
}
    
std::string Post::getAuthor() 
{
    return "";
}
    
bool Post::getIsPublic()
{
    return true;
}

IncomingPost::IncomingPost() {}

IncomingPost::IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author) : Post::Post{messageId,ownerId,message,likes}
{
    isPublic_ = isPublic;
    author_ = author;
}

std::string IncomingPost::toString()
{
    std::string pub;
    if(isPublic_)
    {
        pub = "";
    } else
    {
        pub = "(private)";
    }

    return author_ + " wrote" + pub + ": " + Post::toString();
}

std::string IncomingPost::getAuthor()
{
    return author_;
}

bool IncomingPost::getIsPublic()
{
    return isPublic_;
}