#ifndef __ITERATOR_H__
#define __ITERATOR_H__

namespace Jing{

template<class T>
class Iterator{
public:
  virtual bool hasNext() = 0;
  virtual T next() = 0;
  virtual void remove() = 0;
};

}

#endif
