#pragma once

#include "EventTypes.h"
#include <any>
#include <string>

namespace DSA {

class Event {
public:
    explicit Event(EventType type) : m_type(type) {}
    
    virtual ~Event() = default;
    
    EventType getType() const noexcept { return m_type; }
    
    bool isType(EventType type) const noexcept { return m_type == type; }
    
    void setData(const std::any& data) { m_data = data; }
    
    std::any getData() const { return m_data; }
    
    bool hasData() const { return m_data.has_value(); }

private:
    EventType m_type;
    std::any m_data;
};

}
