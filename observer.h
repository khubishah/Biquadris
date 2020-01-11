#ifndef _OBSERVER_H_
#define _OBSERVER_H_

template <typename InfoType> class Subject; // forward declaration
class Cell;

template <typename InfoType> class Observer {
 public:
  virtual void notify(Subject<InfoType> &whoFrom) = 0; // pass the Subject that called the notify method
  virtual ~Observer() = default;
};
#endif





