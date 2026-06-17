#ifndef NOTIFICATION_STRATEGIES_H
#define NOTIFICATION_STRATEGIES_H

#include "INotificationStrategy.h"
#include <string>

class INotification;

class EmailStrategy : public INotificationStrategy {
private:
  std::string fromEmail;

public:
  explicit EmailStrategy(const std::string &email);
  void sendNotification(INotification *notification) override;
};

class SMSStrategy : public INotificationStrategy {
private:
  std::string senderNumber;

public:
  explicit SMSStrategy(const std::string &senderPhone);
  void sendNotification(INotification *notification) override;
};

class PopUpStrategy : public INotificationStrategy {
public:
  void sendNotification(INotification *notification) override;
};

#endif // NOTIFICATION_STRATEGIES_H
