#pragma once

#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using StudentName = std::string;
using TaskName = std::string;

using ScoreTable = std::map<StudentName, std::set<TaskName>>;

struct TaskStatus {
    bool check_stat_ = false;
    bool merge_stat_ = true;
};

class Scorer {
public:
    void OnCheckFailed(const StudentName& student_name, const TaskName& task_name);
    void OnCheckSuccess(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name);
    void Reset();

    ScoreTable GetScoreTable() const;

private:
    ScoreTable actual_scores_;
    std::unordered_map<StudentName, TaskStatus> all_actions_;
};
