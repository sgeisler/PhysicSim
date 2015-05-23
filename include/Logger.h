//
// Created by Sebastian on 23.05.2015.
//

#ifndef PHYSICSIM_LOGGER_H
#define PHYSICSIM_LOGGER_H

std::string getFileName(std::string s)
{
    s.erase(s.begin(), s.begin() + s.find_last_of('/'));
    s.erase(s.begin(), s.begin() + s.find_last_of('\\'));
    return s;
}

#define LOG(msg) \
    std::cout << getFileName(__FILE__) << " (line: " << __LINE__ << "): " << msg << std::endl

#endif //PHYSICSIM_LOGGER_H
