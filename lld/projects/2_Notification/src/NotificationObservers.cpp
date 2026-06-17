#include "NotificationObservers.h"
#include "INotificationStrategy.h"
#include "NotificationException.h"
#include "NotificationObservable.h"
#include "NotificationService.h"
#include <iostream>

NotificationEngine::NotificationEngine() {
  observable = NotificationService::getInstance()->getObservable();
  observable->addObserver(this);
}

void NotificationEngine::update() {
  if (strategies.empty())
    throw NotificationException("no strategies are set");
  for (auto strategy : strategies) {
    strategy->sendNotification(observable->getNotification());
  }
}

void NotificationEngine::addStrategy(INotificationStrategy *strategy) {
  if (strategy == nullptr)
    throw NotificationException("can not set empty strategy");
  strategies.push_back(strategy);
}

NotificationEngine::~NotificationEngine() {
  for (auto &strategy : strategies)
    delete strategy;
}

Logger::Logger() {
  observable = NotificationService::getInstance()->getObservable();
  observable->addObserver(this);
}

void Logger::update() {
  std::cout << "[Logger]" << (observable->getNotification()->getContent())
            << '\n';
}
