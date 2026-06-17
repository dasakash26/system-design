#include "NotificationStrategies.h"
#include "INotification.h"
#include "NotificationException.h"
#include <iostream>

EmailStrategy::EmailStrategy(const std::string &email) : fromEmail(email) {
  if (email.find("@") == std::string::npos) {
    throw NotificationException("Email address is invalid (missing '@')");
  }
}

void EmailStrategy::sendNotification(INotification *notification) {
  if (notification == nullptr) {
    throw NotificationException(
        "Notification pointer cannot be null in EmailStrategy");
  }
  std::cout << "[Email Strategy] Dispatching from " << fromEmail << ":\n"
            << notification->getContent() << "\n\n";
}

SMSStrategy::SMSStrategy(const std::string &senderPhone)
    : senderNumber(senderPhone) {
  if (senderPhone.empty()) {
    throw NotificationException(
        "Sender phone number/short code cannot be empty");
  }
}

void SMSStrategy::sendNotification(INotification *notification) {
  if (notification == nullptr) {
    throw NotificationException(
        "Notification pointer cannot be null in SMSStrategy");
  }
  std::cout << "[SMS Strategy] Dispatching from " << senderNumber << ":\n"
            << notification->getContent() << "\n\n";
}

void PopUpStrategy::sendNotification(INotification *notification) {
  if (notification == nullptr) {
    throw NotificationException(
        "Notification pointer cannot be null in PopUpStrategy");
  }
  std::cout << "[Popup Strategy] Toast alert:\n"
            << notification->getContent() << "\n\n";
}
