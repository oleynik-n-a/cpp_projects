#include "scorer.h"

#include <algorithm>

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::vector<const Event*> events_copy(events.size());
    for (size_t i = 0; i < events.size(); ++i) {
        events_copy[i] = &events[i];
    }
    sort(events_copy.begin(), events_copy.end(),
         [](const Event* event1, const Event* event2) { return event1->time < event2->time; });
    std::map<StudentName, std::set<TaskName>> score_table;
    for (size_t i = 0; i < events_copy.size(); ++i) {
        if (events_copy[i]->time > score_time) {
            break;
        }
        if (events_copy[i]->event_type == EventType::CheckSuccess ||
            events_copy[i]->event_type == EventType::MergeRequestClosed) {
            score_table[events_copy[i]->student_name].insert(events_copy[i]->task_name);
        } else {
            if (score_table.contains(events_copy[i]->student_name)) {
                score_table[events_copy[i]->student_name].erase(events_copy[i]->task_name);
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
