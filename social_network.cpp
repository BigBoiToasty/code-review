#include "user.h"
#include "network.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    Network* social_network = new Network();
    int working = social_network->readUsers(argv[1]);
    int good = social_network->readPosts(argv[2]);
    bool work = true;
    do
    {
        int number;
        cout << "1. Add a user" << endl;
        cout << "2. Add a friend connection" << endl;
        cout << "3. Delete a friend connection" << endl;
        cout << "4. Print users" << endl;
        cout << "5. Print friends" << endl;
        cout << "6. Write to file" << endl;
        cout << "7. Find the shortest path between 2 friends" << endl;
        cout << "8. Find users at a given distance from you" << endl;
        cout << "9. Find friend suggestions for a certain user" << endl;
        cout << "10. Find groups of people" << endl;
        cout << "11. View posts from a user" << endl;
        cin >> number;
        if(number == 1){
            cout << "Give name, birth year, and zip code" << endl;
            string fname;
            string lname;
            int year;
            int zip;
            cin >> fname;
            cin >> lname;
            cin >> year;
            cin >> zip;
            string fullname = fname + " " + lname;
            int id = social_network->numUsers();
            std::set<int> friends;
            User* user = new User(id,fullname,year,zip,friends);
            social_network->addUser(user);
        } else if(number == 2) {
            cout << "List 2 usernames to make friends of each other" << endl;
            string fname1;
            string lname1;
            string fname2;
            string lname2;
            cin >> fname1;
            cin >> lname1;
            cin >> fname2;
            cin >> lname2;
            string fullname1 = fname1 + " " + lname1;
            string fullname2 = fname2 + " " + lname2;
            int test = social_network->addConnection(fullname1,fullname2);
            if(test == -1)
            {
                cout << "One of the users does not exist" << endl;
            }
        } else if(number == 3) {
            cout << "List 2 usernames to delete the friend relationship of" << endl;
            string fname1;
            string lname1;
            string fname2;
            string lname2;
            cin >> fname1;
            cin >> lname1;
            cin >> fname2;
            cin >> lname2;
            string fullname1 = fname1 + " " + lname1;
            string fullname2 = fname2 + " " + lname2;
            int test = social_network->deleteConnection(fullname1,fullname2);
            if(test == -1)
            {
                cout << "One of the users does not exist or they are not friends" << endl;
            }
        } else if(number == 4) {
            for(int i = 0; i < social_network->numUsers(); i++)
            {
                cout << i << " " << social_network->getUser(i)->getName() << endl;
            }
        } else if(number == 5) {
            cout << "A name of the user's friends you want to see" << endl;
            string fname1;
            string lname1;
            cin >> fname1;
            cin >> lname1;
            string fullname1 = fname1 + " " + lname1;
            int id = social_network->getId(fullname1);
            User* temp = social_network->getUser(id);
            if(temp == nullptr){
                cout << "User does not exist" << endl;
            } else {
                set<int> tempFriends = temp->getFriends();
                for(int temp :tempFriends){
                    cout << temp << " " << social_network->getUser(temp)->getName() << endl;
                }
            }
        } else if(number == 6) {
            cout << "What do you want the file name to write the user data to" << endl;
            char * filename;
            cin >> filename;
            social_network->writeUsers(filename);
        } else if(number == 7){
            cout << "Give 2 names you'd like to see their friend path of" << endl;
            string fname1;
            string lname1;
            string fullname1;
            string fname2;
            string lname2;
            string fullname2;
            cin >> fname1;
            cin >> lname1;
            fullname1 = fname1 + " " + lname1;
            cin >> fname2;
            cin >> lname2;
            fullname2 = fname2 + " " + lname2;
            int id1 = social_network->getId(fullname1);
            int id2 = social_network->getId(fullname2);
            vector<int> path = social_network->shortestPath(id1,id2);
            if(!path.empty())
            {
            cout << "Distance: " << path.size()-1 << endl;
            cout << social_network->getUser(path[0])->getName();
            for(int i = 1; i < path.size();i++)
            {
                cout << "->" << social_network->getUser(path[i])->getName();
            }
            cout << endl;
            }
            else if (path[0] == -1)
            {
                cout << "None" << endl;
            }
            else
            {
                cout << "Distance: " << 0 << endl;
                cout << fullname1 << endl; 
            }
        }
        else if(number == 8)
        {
            cout << "Give a name and a distance to find a friend" << endl;
            string fname1;
            string lname1;
            string fullname1;
            int length;
            cin >> fname1;
            cin >> lname1;
            cin >> length;
            fullname1 = fname1 + " " + lname1;
            int id1 = social_network->getId(fullname1);
            int id2 = -1;
            vector<int> path = social_network->distanceUser(id1,id2,length);
            if(!path.empty())
            {
                cout << social_network->getUser(id2)->getName() << ": ";
                cout << social_network->getUser(path[0])->getName();
                for(int i = 1; i < path.size();i++)
                {
                    cout << "->" << social_network->getUser(path[i])->getName();
                }
                cout << endl;
            }
            else if (id2 == -1)
            {
                cout << "None" << endl;
            }
        } 
        else if(number == 9)
        {
            cout << "Give a name for friend suggestions" << endl;
            string fname1;
            string lname1;
            string fullname1;
            cin >> fname1;
            cin >> lname1;
            fullname1 = fname1 + " " + lname1;
            int score = 0;
            int id = social_network->getId(fullname1);
            vector<int> suggest = social_network->suggestFriends(id,score);
            cout<< "The suggested friend(s) is/are:" << endl;
            for(int temp: suggest)
            {
                cout << social_network->getUser(temp)->getName() << " Score: " << score << endl;
            }

        }
        else if(number == 10)
        {
            vector<vector<int>> groups = social_network->groups();
            int count = 0;
            for(vector<int> temp:groups)
            {
                count++;
                cout << "Set " << count << "=>";
                cout << temp[0];
                for(int i = 1; i < temp.size();i++)
                {
                    cout << ", "<< social_network->getUser(i)->getName();
                }
                cout << endl;
            }
        }
        else if(number == 11)
        {
            cout << "Give a name to see their posts and how many of their posts you would like to see" << endl;
            string fname1;
            string lname1;
            string fullname1;
            int howMany = 0;
            cin >> fname1;
            cin >> lname1;
            cin >> howMany;
            fullname1 = fname1 + " " + lname1;
            int id = social_network->getId(fullname1);
            string posts = social_network->getPostsString(id,howMany,false);
            cout << posts << endl;
        }
        else {
            work = false;
        }
    } while (work);

    return 0;
} 