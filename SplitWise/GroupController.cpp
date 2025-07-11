#include "Group.cpp"

class GroupController
{
private:
    /* data */
    unordered_map<int,shared_ptr<Group>>allGroups;
public:
    GroupController(/* args */){
        allGroups=unordered_map<int,shared_ptr<Group>>();
    }
    ~GroupController(){}

    void addGroup(shared_ptr<Group>group)
    {
        int groupId = group->getGroupId();
        if(allGroups.find(groupId)!=allGroups.end())
        {
            cout<<"Already Group added."<<endl;
            return;
        }
        allGroups[groupId]=group;
    }

    shared_ptr<Group>getGroupById(int groupId)
    {
         if(allGroups.find(groupId)==allGroups.end())
        {
            cout<<"Group is not present."<<endl;
            return nullptr;
        }
        return allGroups[groupId];
       
    }


};
