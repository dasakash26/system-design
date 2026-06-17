#ifndef NOTIFICATION_DECORATORS_H
#define NOTIFICATION_DECORATORS_H

#include "INotificationDecorator.h"
#include <string>

class SimpleNotification : public INotification {
private:
  std::string text;

public:
  explicit SimpleNotification(const std::string &msg);
  std::string getContent() override;
};

class TimestampDecorator : public INotificationDecorator {
public:
  explicit TimestampDecorator(INotification *n);
  std::string getContent() override;
};

class SignatureDecorator : public INotificationDecorator {
private:
  std::string signature;

public:
  SignatureDecorator(INotification *n, const std::string &sig);
  std::string getContent() override;
};

#endif // NOTIFICATION_DECORATORS_H
