#include<bits/stdc++.h>
using namespace std;

bool customSort(const pair<string, array<int,4>> &a, const pair<string, array<int,4>> &b)
{
    return (a.second[1] > b.second[1]);
}

int main(){
    int n, p;
    cin>>n>>p;
    vector<string> names(n);
    map<string, vector<pair<string,int>>> name_to_skills;
    map<string, vector<pair<int, string>>> skill_to_names;
    map<string, bool> assigned;

    for(int i=0; i<n; i++){
        cin>>names[i];
        assigned[names[i]] = false;
        int k; cin>>k;
        for(int j=0; j<k; j++){
            string s; int level;
            cin>>s>>level;
            name_to_skills[names[i]].push_back({s,level});
            skill_to_names[s].push_back({level, names[i]});
        }
    }

    vector<pair<string, array<int,4>>> projects(p);
    map<string, vector<pair<string,int>>> requirements;
    for(int i=0; i<p; i++){
        string projectName; cin>>projectName;
        for(int j=0; j<4; j++){
            cin>>projects[i].second[j];
        }

        projects[i].first = projectName;

        for(int j=0; j<projects[i].second[3]; j++){
            string s; int level;
            cin>>s>>level;
            requirements[projectName].push_back({s, level});
        }
    }
    // input over

    
    for(auto i=skill_to_names.begin(); i!=skill_to_names.end(); i++){
        sort(i->second.begin(), i->second.end());
    }

    int executed = 0;
    vector<string> projectCompleted;
    vector<vector<string>> namesInProject;
    
    sort(projects.begin(), projects.end(), customSort);
    for(int i=0; i<p; i++){
        bool flag = true;
        string projectName = projects[i].first;
        vector<string> people;
        vector<int> increaseSkill;
        
        for(int j=0; j<projects[i].second[3]; j++){
            string s = requirements[projectName][j].first;
            int level = requirements[projectName][j].second;

            // check for person
            for(int k=0; k<skill_to_names[s].size(); k++){
                if(assigned[skill_to_names[s][k].second]==false and skill_to_names[s][k].first>=level){
                    people.push_back(skill_to_names[s][k].second);
                    increaseSkill.push_back(k);
                    assigned[skill_to_names[s][k].second] = true;
                    break;
                }
            }
        }

        if(people.size() != projects[i].second[3]){
            flag = false;
        }

        for(int j=0; j<people.size(); j++){
            assigned[people[j]] = false;
        }

        if(flag){
            executed++;
            projectCompleted.push_back(projectName);
            namesInProject.push_back(people);

            for(int j=0; j<increaseSkill.size(); j++){
                string s = requirements[projectName][j].first;
                int level = requirements[projectName][j].second;
                int k = increaseSkill[j];
                if(level>=skill_to_names[s][k].first){
                    skill_to_names[s][k].first++;
                }
            }

            for(int j=0; j<increaseSkill.size(); j++){
                string s = requirements[projectName][j].first;
                sort(skill_to_names[s].begin(), skill_to_names[s].end());
            }
        }
    }

    cout<<executed<<endl;
    for(int i=0; i<executed; i++){
        cout<<projectCompleted[i]<<endl;
        for(int j=0; j<namesInProject[i].size(); j++){
            cout<< namesInProject[i][j]<<" ";
        }
        cout<<endl;
    }


}