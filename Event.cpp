#include "Event.hpp"
#include <algorithm>

// Default constructor
Event::Event() : name_("Not Set Yet"), timestamp_(-1) {}

// Parameterized constructor
Event::Event(const std::string& name, const long& timestamp) : name_(name), timestamp_(timestamp) {}

// Get the name of the event
std::string Event::getName() const {
    return name_;
}

// Get the timestamp of the event
long Event::getTimestamp() const {
    return timestamp_;
}

// Get the list of guests for the event
std::vector<std::string> Event::getGuests() const {
    return guests_;
}

// Set the event name
void Event::setName(const std::string& name) {
    name_ = name;
}

// Set the event timestamp
bool Event::setTimestamp(const long& timestamp) {
    if (timestamp < 0) {
        return false;
    }
    timestamp_ = timestamp;
    return true;
}

// Set the guests list
bool Event::setGuests(const std::vector<std::string>& guests) {
    for (const std::string& guest : guests) {
        if (guest.empty()) {
            return false;
        }
    }
    guests_ = guests;
    return true;
}

// Overloaded stream insertion operator for Event
std::ostream& operator<<(std::ostream& os, const Event& event) {
    os << "Name: " << event.getName() << std::endl;
    os << "Time: " << event.timeToString() << std::endl;
    os << "Guests:" << std::endl;
    for (size_t i = 0; i < event.guests_.size(); ++i) {
        os << i << ": " << event.guests_[i] << std::endl;
    }
    return os;
}

// Overloaded stream extraction operator for Event
std::istream& operator>>(std::istream& is, Event& event) {
    std::string guest;
    std::getline(is, guest);
    if (!guest.empty()) {
        event.guests_.push_back(guest);
    }
    return is;
}

// Add a single guest to the guests list
bool Event::addGuest(const std::string& name) {
    if (name.empty()) {
        return false;
    }
    guests_.push_back(name);
    return true;
}

// Add multiple guests to the guests list
bool Event::addGuest(const std::vector<std::string>& names) {
    for (const std::string& name : names) {
        if (name.empty()) {
            return false;
        }
    }
    guests_.insert(guests_.end(), names.begin(), names.end());
    return true;
}

// Remove a guest from the event by name
bool Event::removeGuest(const std::string& name) {
    auto it = std::find(guests_.begin(), guests_.end(), name);
    if (it != guests_.end()) {
        guests_.erase(it);
        return true;
    }
    return false;
}

// Remove a guest from the event by index
bool Event::removeGuest(const size_t& id) {
    if (id < guests_.size()) {
        guests_.erase(guests_.begin() + id);
        return true;
    }
    return false;
}

// Convert the event unix timestamp to string format
std::string Event::timeToString() const {
    // if timestamp is -1, it is not valid and is the result of default constructor
    if (timestamp_ == -1) {
        return "Not Set Yet";
    }
    time_t raw_time = static_cast<time_t>(timestamp_);
    struct tm* dt = localtime(&raw_time);
    std::string time = asctime(dt);
    time.pop_back();  // remove trailing newline
    return time;
}




