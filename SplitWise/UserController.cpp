#pragma once
#include<vector>
#include "User.cpp"
#include<unordered_map>
#include<iostream>
class UserController
{
private:
    /* data */
    // vector<shared_ptr<User>>allUsers;
    unordered_map<int,shared_ptr<User>>allUsers;
public:
    UserController(/* args */)
    {
        allUsers=unordered_map<int,shared_ptr<User>>();
    }
    ~UserController(){}

    void addUser(shared_ptr<User>user)
    {
        int userId=user->getUserid();
        allUsers[userId]=user;
    }
    shared_ptr<User> getUserbyId(int userId)
    {
        if(allUsers.find(userId)!=allUsers.end())
        {
            cout<<"User Found"<<endl;
            return allUsers[userId];
        }
        cout<<"User Not Found"<<endl;
        return nullptr;
    }

};

