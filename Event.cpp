#include "Event.hpp"



Event::Event(){
    this -> name_ = "Not Set Yet";
    this -> timestamp_ = -1;
}

Event::Event(const std::string& name, const long& timestamp){
    this -> name_ = name;
    this -> timestamp_ = timestamp;
}


std::string Event::getName() const{
    return name_;
}

long Event::getTimestamp() const{
    return timestamp_;

}
std::vector<std::string> Event::getGuests() const{

    return guests_;
}
void Event::setName(const std::string& name){
    name_ = name;
}
bool Event::setTimestamp(const long& timestamp){
    if(timestamp < 0){
        return false;
    }
    timestamp_ = timestamp;
    return true;
    }
bool Event::setGuests(const std::vector<std::string>& guests){
    for(size_t i = 0; i< guests.size(); i++){
        if(guests[i]==" "){
            return false;
        }
        guests_ = guests;
        return true;
    }
}
std::ostream& operator<<(std::ostream& os, const Event& event){
    os<< "Name: "<< event.name_ << "\n";
    os<< "Time: "<< event.timeToString() << "\n";
    os<< "Guest:"<< "\n";
    for(size_t index = 0; index < event.guests_.size(); index++){
        os<< index <<": " << event.guests_[index] << "\n";
    }
    os<< "-------------------------------------------"<<"\n";
    return os;
}
std::istream& operator>>(std::istream& is, Event&event){
    std:: string guest;
    while(std::getline(is, guest)){
        if(guest!=""){
            event.guests_.push_back(guest);
        }
        return is;
    }
}

bool Event::addGuest(const std::string& name){
    if(name== ""){
        return false;
    }
    guests_.push_back(name);
    return true;

}
bool Event::addGuest(const std::vector<std::string>& names) {
    for (size_t i = 0; i < names.size(); ++i) {
        if (names[i]== " ") {
            return false;
        }
    }
    guests_.insert(guests_.end(), names.begin(), names.end());
    return true;
}

bool Event::removeGuest(const std::string& name){
        for (auto desire_Remove = guests_.begin(); desire_Remove != guests_.end(); desire_Remove++) {
        if (*desire_Remove == name) {
            guests_.erase(desire_Remove);
            return true;
        }
    }
    return false;
}
        /**
         * @brief Remove a guest from the event by index
         * 
         * @param id Index of the guest to remove
         * @return true If the index is within the size of the guests list and is removed
         * @return false If the index is not within the guests list and can't be removed
         * @post Guest removed from the event if index is within the size of the list and the order of guests is maintained
         */
bool Event::removeGuest(const size_t& id){
    while(id < guests_.size()){
            guests_.erase(guests_.begin() + id);
            return true;
    }
    return false;
}

//TODO: REMOVE THIS COMMENT. DON'T MODIFY THIS FUNCTION IMPLEMENTATION. USE IT IN THE OUTPUT STREAM OPERATOR OVERLOAD.
std::string Event::timeToString() const {
    // if timestamp is -1, it is not valid and is the result of default constructor
    if (timestamp_ == -1) {
        return "Not Set Yet";
    }
    struct tm* dt = localtime(&timestamp_);
    std::string time = asctime(dt);
    time.pop_back();
    return time;
}




