#include "scorer.h"

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    Events events_copy = events;
    sort(events_copy.begin(), events_copy.end(), [](Event event1, Event event2) { return event1.time < event2.time; });
    std::map<StudentName, std::set<TaskName>> score_table;
    for (size_t i = 0; i < events_copy.size(); ++i) {
        if (events_copy[i].time > score_time) {
            break;
        }
        if (events_copy[i].event_type == EventType::CheckSuccess ||
            events_copy[i].event_type == EventType::MergeRequestClosed) {
            score_table[events_copy[i].student_name].insert(events_copy[i].task_name);
        } else {
            if (score_table.contains(events_copy[i].student_name)) {
                score_table[events_copy[i].student_name].erase(events_copy[i].task_name);
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
