#include "scorer.h"

void Scorer::OnCheckSuccess(const StudentName &student_name, const TaskName &task_name) {
    all_actions_[student_name].check_stat_ = true;
    if (all_actions_[student_name].check_stat_ && all_actions_[student_name].merge_stat_) {
        actual_scores_[student_name].insert(task_name);
    }
}

void Scorer::OnCheckFailed(const StudentName &student_name, const TaskName &task_name) {
    all_actions_[student_name].check_stat_ = false;
    actual_scores_[student_name].erase(task_name);
    if (actual_scores_[student_name].empty()) {
        actual_scores_.erase(student_name);
    }
}

void Scorer::OnMergeRequestOpen(const StudentName &student_name, const TaskName &task_name) {
    all_actions_[student_name].merge_stat_ = false;
    actual_scores_[student_name].erase(task_name);
    if (actual_scores_[student_name].empty()) {
        actual_scores_.erase(student_name);
    }
}

void Scorer::OnMergeRequestClosed(const StudentName &student_name, const TaskName &task_name) {
    all_actions_[student_name].merge_stat_ = true;
    if (all_actions_[student_name].check_stat_ && all_actions_[student_name].merge_stat_) {
        actual_scores_[student_name].insert(task_name);
    }
}

void Scorer::Reset() {
    all_actions_.clear();
    actual_scores_.clear();
}

ScoreTable Scorer::GetScoreTable() const {
    return actual_scores_;
}
