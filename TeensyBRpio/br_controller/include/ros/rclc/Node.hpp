#ifndef _ROS_IMPL_NODE_HPP_
#define _ROS_IMPL_NODE_HPP_

#include "defines/string.h"
#include "logging.hpp"
#include "ros/message_cast.hpp"
#include "ros/rclc/Publisher.hpp"
#include "ros/rclc/Subscriber.hpp"
#include "ros/rclc/macros.hpp"

#include <rcl/rcl.h>
#include <rcl_interfaces/msg/log.h>
#include <rclc/executor.h>
#include <rclc/rclc.h>
#include <rcutils/logging_macros.h>

#include <functional>
#include <memory>
#include <optional>

namespace ros_rclc {

template <>
class type_support_t<rcl_interfaces__msg__Log> {
  public:
    static support_t get() { return ROSIDL_GET_MSG_TYPE_SUPPORT(rcl_interfaces, msg, Log); }
};

template <typename T>
class Publisher;

template <typename T>
class Subscription;

class Node {

  public:
    Node(string_t name) : m_name(std::move(name)), m_msgLog() {
        RCCHECK_HARD(rclc_support_init(m_support.get(), 0, NULL, m_allocator.get()));
        RCCHECK_HARD(rclc_node_init_default(m_node.get(), m_name.c_str(), "", m_support.get()));
        RCCHECK_HARD(rclc_executor_init(m_executor.get(), &m_support->context, 8, m_allocator.get()));

        m_logger.emplace(createPublisher<rcl_interfaces__msg__Log>("rosout"));
    }

    void spin_once() { RCCHECK_HARD(rclc_executor_spin_some(m_executor.get(), 0)); }

    template <typename T>
    Subscription<T> createSubscription(const string_t &topic, std::function<void(const T &)> callback) {
        return Subscription<T>(m_node, m_executor.get(), topic, callback);
    }

    template <typename T>
    Publisher<T> createPublisher(const string_t &topic, QosReliability reliability = AllowBestEffort) {
        return Publisher<T>(m_node, topic, reliability);
    }

    void sendLog(LogSeverity severity, const string_t &message) {
        switch (severity) {
            case INFO:
                m_msgLog.level = rcl_interfaces__msg__Log__INFO;
                break;
            case WARN:
                m_msgLog.level = rcl_interfaces__msg__Log__WARN;
                break;
            case ERROR:
                m_msgLog.level = rcl_interfaces__msg__Log__ERROR;
                break;
            case FATAL:
                m_msgLog.level = rcl_interfaces__msg__Log__FATAL;
                break;
            case DEBUG:
                m_msgLog.level = rcl_interfaces__msg__Log__DEBUG;
                break;
            default:
                sendLog(ERROR, "Unknown log type: %d; defaulting to INFO");
                m_msgLog.level = rcl_interfaces__msg__Log__INFO;
                break;
        }

        m_msgLog.name.data = (char *)m_name.c_str();
        m_msgLog.name.size = m_name.size();
        m_msgLog.name.capacity = m_name.capacity();

        m_msgLog.msg.data = (char *)message.c_str();
        m_msgLog.msg.size = message.size();
        m_msgLog.msg.capacity = message.capacity();

        if (m_logger) {
            m_logger->publish(m_msgLog);
        }
    }

  private:
    // Not sure if boxing is necessary
    std::unique_ptr<rcl_allocator_t> m_allocator = std::make_unique<rcl_allocator_t>(rcl_get_default_allocator());
    std::unique_ptr<rclc_support_t> m_support = std::make_unique<rclc_support_t>();
    std::unique_ptr<rclc_executor_t> m_executor = std::make_unique<rclc_executor_t>();
    std::shared_ptr<rcl_node_t> m_node = std::make_shared<rcl_node_t>();

    string_t m_name;
    rcl_interfaces__msg__Log m_msgLog;
    std::optional<Publisher<rcl_interfaces__msg__Log>> m_logger;
};
} // namespace ros_rclc

#endif