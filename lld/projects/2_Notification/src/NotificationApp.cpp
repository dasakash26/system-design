#include "NotificationDecorators.h"
#include "NotificationObservers.h"
#include "NotificationService.h"
#include "NotificationStrategies.h"
#include <iostream>

int main() {
  std::cout << "\n\n---Notification Service---\n\n";
  NotificationService *notificationService = NotificationService::getInstance();
  Logger *logger = new Logger();
  NotificationEngine *notificationEngine = new NotificationEngine();

  notificationEngine->addStrategy(new EmailStrategy("unknown@fsociety.com"));
  notificationEngine->addStrategy(new SMSStrategy("+91 100 100 100"));
  notificationEngine->addStrategy(new PopUpStrategy());

  INotification *notification = new SimpleNotification("Leave me here.");
  notification = new SignatureDecorator(notification, "Mr. Robot");
  notification = new TimestampDecorator(notification);

  // std::cout << notification->getContent() << std::endl;
  notificationService->sendNotification(notification);

  delete notificationService;
  delete logger;
  delete notificationEngine;

  return 0;
}
