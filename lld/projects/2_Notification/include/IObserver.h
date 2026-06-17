#ifndef IOBSERVER_H
#define IOBSERVER_H

class IObserver {
public:
  virtual ~IObserver() = default;
  virtual void update() = 0;
};

#endif // !IObserver
