#include "scorer.h"

void Scorer::OnCheckSuccess(const StudentName &student_name, const TaskName &task_name) {
    this->all_actions_[student_name].check_stat_ = true;
    if (this->all_actions_[student_name].check_stat_ && this->all_actions_[student_name].merge_stat_) {
        this->actual_scores_[student_name].insert(task_name);
    }
}

void Scorer::OnCheckFailed(const StudentName &student_name, const TaskName &task_name) {
    this->all_actions_[student_name].check_stat_ = false;
    this->actual_scores_[student_name].erase(task_name);
    if (this->actual_scores_[student_name].empty()) {
        this->actual_scores_.erase(student_name);
    }
}

void Scorer::OnMergeRequestOpen(const StudentName &student_name, const TaskName &task_name) {
    this->all_actions_[student_name].merge_stat_ = false;
    this->actual_scores_[student_name].erase(task_name);
    if (this->actual_scores_[student_name].empty()) {
        this->actual_scores_.erase(student_name);
    }
}

void Scorer::OnMergeRequestClosed(const StudentName &student_name, const TaskName &task_name) {
    this->all_actions_[student_name].merge_stat_ = true;
    if (this->all_actions_[student_name].check_stat_ && this->all_actions_[student_name].merge_stat_) {
        this->actual_scores_[student_name].insert(task_name);
    }
}

void Scorer::Reset() {
    this->all_actions_.clear();
    this->actual_scores_.clear();
}

ScoreTable Scorer::GetScoreTable() const {
    return this->actual_scores_;
}
