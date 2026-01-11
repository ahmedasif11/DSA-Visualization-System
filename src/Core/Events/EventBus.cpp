#include "EventBus.h"
#include <algorithm>

namespace DSA {

EventBus& EventBus::getInstance() {
    static EventBus instance;
    return instance;
}

EventBus::SubscriptionID EventBus::subscribe(EventType type, EventCallback callback) {
    SubscriptionID id = m_nextId++;
    m_subscribers[type].push_back({type, std::move(callback), id});
    return id;
}

void EventBus::unsubscribe(SubscriptionID id) {
    for (auto& [type, subscribers] : m_subscribers) {
        auto it = std::find_if(subscribers.begin(), subscribers.end(),
            [id](const Subscription& sub) { return sub.id == id; });
        
        if (it != subscribers.end()) {
            subscribers.erase(it);
            break;
        }
    }
}

void EventBus::publish(const Event& event) {
    auto it = m_subscribers.find(event.getType());
    if (it != m_subscribers.end()) {
        auto subscribers = it->second;
        for (const auto& subscription : subscribers) {
            subscription.callback(event);
        }
    }
}

void EventBus::queue(const Event& event) {
    m_eventQueue.push(event);
}

void EventBus::processEvents() {
    while (!m_eventQueue.empty()) {
        publish(m_eventQueue.front());
        m_eventQueue.pop();
    }
}

void EventBus::clear() {
    m_subscribers.clear();
    while (!m_eventQueue.empty()) {
        m_eventQueue.pop();
    }
    m_nextId = 1;
}

void EventBus::clear(EventType type) {
    m_subscribers.erase(type);
}

}
