#ifndef IOBSERVABLE_H
#define IOBSERVABLE_H

// Forward declaration of IObserver to break dependency loops
class IObserver;

class IObservable {
public:
  virtual ~IObservable() = default;
  virtual void addObserver(IObserver* observer) = 0;
  virtual void removeObserver(IObserver* observer) = 0;
  virtual void notify() = 0;
};

#endif // IOBSERVABLE_H
