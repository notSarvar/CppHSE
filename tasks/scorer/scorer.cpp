#include "scorer.h"

#include <unordered_map>

bool ByTime(const Event* a, const Event* b) {
    return a->time < b->time;
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::vector<const Event*> sorted_events;
    for (const auto& i : events) {
        sorted_events.push_back(&i);  // добавить сюда std::move?
    }
    std::sort(sorted_events.begin(), sorted_events.end(), ByTime);

    std::unordered_map<StudentName, std::unordered_map<TaskName, std::pair<int, int>>> all_events;
    for (const auto& i : sorted_events) {
        if (i->time > score_time) {
            break;
        }
        all_events[i->student_name][i->task_name] = {0, 1};
        if (i->event_type == EventType::CheckSuccess) {
            all_events[i->student_name][i->task_name] = {1, all_events[i->student_name][i->task_name].second};
        } else if (i->event_type == EventType::CheckFailed) {
            all_events[i->student_name][i->task_name] = {0, all_events[i->student_name][i->task_name].second};
        }
        if (i->event_type == EventType::MergeRequestClosed) {
            all_events[i->student_name][i->task_name] = {all_events[i->student_name][i->task_name].first, 1};
        } else if (i->event_type == EventType::MergeRequestOpen) {
            all_events[i->student_name][i->task_name] = {all_events[i->student_name][i->task_name].first, 0};
        }
    }

    ScoreTable score_table;
    for (const auto& i : all_events) {
        for (const auto& j : i.second) {
            if (j.second == std::make_pair(1, 1)) {
                score_table[i.first].insert(j.first);  // тут возникала ошибка с i.first когда поменял StudentName
            }
        }
    }
    return score_table;
}
