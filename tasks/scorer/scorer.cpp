#include "scorer.h"

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::map<StudentName, std::set<TaskName>> score_table;
    for (size_t i = 0; i < events.size(); ++i) {
        if ((events[i].event_type == EventType::CheckSuccess || events[i].event_type == EventType::MergeRequestClosed)
            && events[i].time <= score_time) {
            score_table[events[i].student_name].insert(events[i].task_name);
        } else {
            if (score_table.contains(events[i].student_name)) {
                score_table[events[i].student_name].erase(events[i].task_name);
            }
        }
    }
    return score_table;
}
