#include "scorer.h"

#include <unordered_map>

bool ByTime(const Event* a, const Event* b) {
    return a->time < b->time;
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::vector<const Event*> sorted_events;
    for (const auto& i : events) {
        sorted_events.push_back(&i);
    }
    std::sort(sorted_events.begin(), sorted_events.end(), ByTime);

    std::unordered_map<StudentName, std::unordered_map<TaskName, EventType>> all_events;
    for (const auto& i : sorted_events) {
        if (i->time > score_time) {
            break;
        }
        all_events[i->student_name][i->task_name] = i->event_type;
    }

    ScoreTable score_table;
    for (const auto& i : all_events) {
        for (const auto& j : i.second) {
            if (j.second == EventType::CheckSuccess || j.second == EventType::MergeRequestClosed) {
                score_table[i.first].insert(j.first);
            }
        }
    }
    return score_table;
}
