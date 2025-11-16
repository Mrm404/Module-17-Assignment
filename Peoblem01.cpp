#include <bits/stdc++.h>
using namespace std;

struct Meeting {
    int id;
    int start, end;
    int attendees;
    vector<string> equipment;
    int priority;
};

struct Room {
    string id;
    int capacity;
    vector<string> equipment;
};

bool hasEquipment(const vector<string>& roomEq, const vector<string>& needEq) {
    for (auto &eq : needEq)
        if (find(roomEq.begin(), roomEq.end(), eq) == roomEq.end()) return false;
    return true;
}

bool isFree(const vector<pair<int,int>>& schedule, int start, int end) {
    for (auto &slot : schedule)
        if (!(end <= slot.first || start >= slot.second)) return false;
    return true;
}

int main() {
    vector<Meeting> meetings = {
        {1, 9, 10, 8, {"projector"}, 3},
        {2, 9, 11, 4, {}, 4},
        {3, 10, 12, 12, {"projector", "vc"}, 5}
    };

    vector<Room> rooms = {
        {"B", 6, {"vc", "projector"}},       
        {"C", 15, {"projector", "vc", "whiteboard"}}, 
        {"A", 10, {"projector", "whiteboard"}}
    };

    unordered_map<string, vector<pair<int,int>>> roomSchedule;

    sort(meetings.begin(), meetings.end(), [](auto &a, auto &b){
        return a.end < b.end;
    });

    vector<tuple<int,string,int,int>> finalSchedule;

    for (auto &m : meetings) {
        if (m.id == 1) continue; 

        for (auto &r : rooms) {
            if (r.capacity < m.attendees) continue;
            if (!hasEquipment(r.equipment, m.equipment)) continue;
            if (!isFree(roomSchedule[r.id], m.start, m.end)) continue;

            roomSchedule[r.id].push_back({m.start, m.end});
            finalSchedule.push_back({m.id, r.id, m.start, m.end});
            break;
        }
    }

    cout << "Schedule:\n";
    for (auto &s : finalSchedule) {
        int id, start, end;
        string room;
        tie(id, room, start, end) = s;
        cout << "{ meeting_id: " << id
             << ", room_id: " << room
             << ", time: (" << start << ", " << end << ") }" << endl;
    }

    return 0;
}
