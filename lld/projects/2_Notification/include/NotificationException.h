#ifndef NOTIFICATION_EXCEPTION_H
#define NOTIFICATION_EXCEPTION_H

#include <stdexcept>
#include <string>

class NotificationException : public std::runtime_error {
public:
  explicit NotificationException(const std::string &msg)
      : std::runtime_error(msg) {}
};

#endif // NOTIFICATION_EXCEPTION_H
