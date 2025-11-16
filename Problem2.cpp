#include <bits/stdc++.h>
using namespace std;

struct Meeting {
    int id;
    int priority;
    int duration;
    map<string,int> equipment_required;
};

double computeEquipmentSatisfaction(const map<string,int>& required, const map<string,int>& available) {
    double ratio = 1.0;
    for (auto &[eq, req] : required) {
        if (available.find(eq) == available.end() || available.at(eq) == 0) {
            ratio = min(ratio, 0.0);
        } else {
            ratio = min(ratio, (double)available.at(eq)/req);
        }
    }
    return ratio;
}

int main() {
    map<string,int> equipment_available = {{"projector",3},{"vc",2},{"whiteboard",4}};

    vector<Meeting> meetings = {
        {1,3,2,{{"projector",1},{"vc",1}}},
        {2,5,1,{{"projector",1}}}
    };

    vector<pair<double,int>> ratio_index;
    for (int i = 0; i < meetings.size(); ++i) {
        int total_req = 0;
        for (auto &[eq, cnt] : meetings[i].equipment_required) total_req += cnt;
        double sat = computeEquipmentSatisfaction(meetings[i].equipment_required, equipment_available);
        double value = meetings[i].priority * meetings[i].duration * sat;
        double ratio = value / max(1,total_req);
        ratio_index.push_back({ratio, i});
    }

    sort(ratio_index.rbegin(), ratio_index.rend());

    double totalValue = 0.0;
    map<string,int> available = equipment_available;
    vector<pair<int,double>> scheduled;

    for (auto &[ratio, idx] : ratio_index) {
        Meeting &m = meetings[idx];
        double sat = computeEquipmentSatisfaction(m.equipment_required, available);
        if (sat == 0) continue;

        totalValue += m.priority * m.duration * sat;

        for (auto &[eq, req] : m.equipment_required) {
            int use = ceil(req*sat);
            available[eq] -= use;
            if (available[eq]<0) available[eq]=0;
        }

        scheduled.push_back({m.id, sat});
    }

    cout << "Total value: " << totalValue << endl;
    cout << "Scheduled meetings:\n";
    for (auto &[id, sat] : scheduled) {
        cout << "Meeting " << id << ", satisfaction ratio: " << sat << endl;
    }

    return 0;
}
