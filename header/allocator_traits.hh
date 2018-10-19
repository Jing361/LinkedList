#ifndef __ALLOCATOR_TRAITS_HH__
#define __ALLOCATOR_TRAITS_HH__

#include<utility>

namespace gsw{

/*!
 * @tparam Alloc
 */
template<typename Alloc>
class allocator_traits{
public:
  using allocator_type = Alloc;
  using value_type = typename allocator_type::value_type;
  using size_type  = typename allocator_type::size_type;
  using pointer    = value_type*;
  using reference  = value_type&;

  /*!
   * @param alloc
   *
   * @param number
   */
  static
  pointer
  allocate( allocator_type& alloc, size_type number ){
    return alloc.allocate( number );
  }

  /*!
   * @param alloc
   *
   * @param ptr
   *
   * @param number
   */
  static
  void
  deallocate( allocator_type& alloc, pointer ptr, size_type number ){
    alloc.deallocate( ptr, number );
  }

  /*!
   * @tparam T
   *
   * @tparam ...Args
   *
   * @param alloc
   *
   * @param ptr
   *
   * @param args
   */
  template<typename T, class ...Args>
  static
  void
  construct( allocator_type& alloc, T* ptr, Args&&... args ){
    ( void )alloc;
    ::new ( ptr ) value_type( std::forward<Args>( args )... );
  }

  /*!
   * @param alloc
   *
   * @param ptr
   */
  static
  void
  destroy( allocator_type& alloc, pointer ptr ){
    ( void )alloc;
    ptr->~value_type();
  }
};

}

#endif
