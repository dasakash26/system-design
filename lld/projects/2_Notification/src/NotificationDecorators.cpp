#include "NotificationDecorators.h"

SimpleNotification::SimpleNotification(const std::string &msg) : text(msg) {}

std::string SimpleNotification::getContent() { return text; }

TimestampDecorator::TimestampDecorator(INotification *n)
    : INotificationDecorator(n) {}

std::string TimestampDecorator::getContent() {
  return "[2026-06-16 16:00:00] " + wrappedNotification->getContent();
}

SignatureDecorator::SignatureDecorator(INotification *n, const std::string &sig)
    : INotificationDecorator(n), signature(sig) {}

std::string SignatureDecorator::getContent() {
  return wrappedNotification->getContent() + "\n-- " + signature;
}
