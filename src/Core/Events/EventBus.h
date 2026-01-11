#pragma once

#include "Event.h"
#include "EventTypes.h"
#include <functional>
#include <unordered_map>
#include <vector>
#include <queue>

namespace DSA {

class EventBus {
public:
    using EventCallback = std::function<void(const Event&)>;
    using SubscriptionID = std::size_t;

    static EventBus& getInstance();
    SubscriptionID subscribe(EventType type, EventCallback callback);
    void unsubscribe(SubscriptionID id);
    void publish(const Event& event);
    void queue(const Event& event);
    void processEvents();
    void clear();
    void clear(EventType type);

private:
    EventBus() = default;
    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    struct Subscription {
        EventType type;
        EventCallback callback;
        SubscriptionID id;
    };
    
    std::unordered_map<EventType, std::vector<Subscription>> m_subscribers;
    std::queue<Event> m_eventQueue;
    SubscriptionID m_nextId = 1;
};

}
