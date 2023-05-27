#include "scorer.h"

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::map<StudentName, std::set<TaskName>> score_table;
    std::map<std::pair<StudentName, TaskName>, std::pair<bool, bool>> progress;
    for (size_t i = 0; i < events.size(); ++i) {
        progress[std::pair(events[i].student_name, events[i].task_name)].second = true;
    }
    for (size_t i = 0; i < events.size(); ++i) {
        if (events[i].time <= score_time) {
            if (events[i].event_type == EventType::CheckFailed) {
                progress[std::pair(events[i].student_name, events[i].task_name)].first = false;
            } else if (events[i].event_type == EventType::CheckSuccess) {
                progress[std::pair(events[i].student_name, events[i].task_name)].first = true;
            } else if (events[i].event_type == EventType::MergeRequestOpen) {
                progress[std::pair(events[i].student_name, events[i].task_name)].second = false;
            } else if (events[i].event_type == EventType::MergeRequestClosed) {
                progress[std::pair(events[i].student_name, events[i].task_name)].second = true;
            }
            if (progress.contains(std::pair(events[i].student_name, events[i].task_name))) {
                if (progress[std::pair(events[i].student_name, events[i].task_name)] == std::pair(true, true)) {
                    score_table[events[i].student_name].insert(events[i].task_name);
                } else {
                    score_table[events[i].student_name].erase(events[i].task_name);
                }
            }
        }
    }
    for (const auto& pair : score_table) {
        if (pair.second.empty()) {
            score_table.erase(pair.first);
        }
    }
    return score_table;
}
