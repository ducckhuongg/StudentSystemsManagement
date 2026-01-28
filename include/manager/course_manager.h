#pragma once
#ifndef SMS_INCLUDE_MANAGERS_COURSE_MANAGER_H
#define SMS_INCLUDE_MANAGERS_COURSE_MANAGER_H

#include <unordered_map>
#include <string>
#include <vector>
#include <optional>

#include "modules/course.h"

namespace sms {

class CourseManager {
public:
    bool add(Course c) {
        if (!c.is_valid()) return false;
        const auto key = c.code();
        if (courses_.find(key) != courses_.end()) return false;
        courses_.emplace(key, std::move(c));
        return true;
    }

    bool update(const std::string& code, std::string new_name, Course::Credits new_credits) {
        auto it = courses_.find(code);
        if (it == courses_.end()) return false;
        it->second.set_name(std::move(new_name));
        it->second.set_credits(new_credits);
        return it->second.is_valid();
    }

    bool remove(const std::string& code) {
        return courses_.erase(code) > 0;
    }

    const Course* find(const std::string& code) const {
        auto it = courses_.find(code);
        return (it == courses_.end()) ? nullptr : &it->second;
    }

    std::vector<Course> list() const {
        std::vector<Course> out;
        out.reserve(courses_.size());
        for (const auto& kv : courses_) out.push_back(kv.second);
        return out;
    }

    bool exists(const std::string& code) const {
        return courses_.find(code) != courses_.end();
    }

private:
    std::unordered_map<std::string, Course> courses_; // key = course code
};

} // namespace sms

#endif // SMS_INCLUDE_MANAGERS_COURSE_MANAGER_H
