#ifndef __EVENT_HANDLER__HH__
#define __EVENT_HANDLER__HH__

/*!
 * @example test-events.cc
 */

#include <map>
#include <functional>
#include <utility>
#include <memory>
#include <tuple>
#include <stdexcept>

namespace gsw {

template<typename T, template<typename> typename U>
class event_channel_impl;

template<typename T>
class void_combiner{
public:
  //!@TODO ranges?
  //!@TODO make some constraints about types/iter types here?
  template<typename Iter>
  void operator()(Iter, Iter){}
};

template<typename T>
using default_combiner = void_combiner<T>;

/*! Event channel system
 *
 * @tparam Args...
 *
 * @TODO non-blocking event handling
 * probably return a future
 *
 * @TODO could add a couple special type parameters to distinguish different event_channels within the type system
 *
 * parameter might be a dummy, kinda like what's used in the named_type system
 * this dummy might look like struct OnMousePressed, to help distinguish between different possible events
 */
template<template<typename> typename COMBINER, typename R, typename ...Args>
class event_channel_impl<R(Args...), COMBINER> {
public:
  class event_trigger {
  public:
    using channel_t = event_channel_impl;

  private:
    std::shared_ptr<channel_t> mChannel;

  public:
    auto fire(Args... args) {
      return mChannel->fire(args...);
    }

    event_trigger()
            : mChannel(new channel_t) {
    }

    std::weak_ptr<channel_t> getChannel() const {
      return mChannel;
    }
  };

  friend class event_trigger;

  /*! Container for handling events
   */
  class event_handler {
  public:
    using counter_t = unsigned long long;
    using event_channel = event_channel_impl;
    using handler = std::function<R(event_channel&, counter_t, Args...)>;
    using simple_handler = std::function<R(Args...)>;
    friend event_channel;

  private:
    event_channel& mChannel;
    handler mHandler;
    simple_handler mSHandler;
    counter_t mCounter;

    /*! Private constructor
     *
     * Constructor is private so that only the channel creates handlers
     */
    event_handler(event_channel& channel, counter_t counter, handler handle)
            : mChannel(channel)
            , mHandler(handle)
            , mCounter(counter) {
    }

    /*! Private constructor
     *
     * Constructor is private so that only the channel creates handlers
     */
    event_handler(event_channel& channel, counter_t counter, simple_handler handle)
            : mChannel(channel)
            , mSHandler(handle)
            , mCounter(counter) {
    }

    /*! Call event
     *
     * Made private so that only the channel triggers events
     */
    auto operator()(Args... args) {
      if(mHandler) {
        return mHandler(mChannel, mCounter, args...);
      }
      if(mSHandler) {
        return mSHandler(args...);
      }
      throw std::runtime_error("Handler called with no handler assigned.  (idiot..)");
    }

  public:
    event_handler(const event_handler&) = default;
    event_handler(event_handler&&) noexcept = default;

    event_handler& operator=(const event_handler&) = default;
    event_handler& operator=(event_handler&&) noexcept = default;

    friend auto operator<=>(const event_handler&, const event_handler&) = default;
  };

  /*!
   */
  using counter_t = unsigned long long;

  /*!
   * @todo wrap std::function into something that contains counter
   *    this will allow operator -= to identify which handler to use
   */
  using handler = typename event_handler::handler;
  using simple_handler = typename event_handler::simple_handler;

  /*!
   * @tparam N
   */
  template<size_t N> using arg_types = typename std::tuple_element<N, std::tuple<Args...>>::type;

private:
  std::map<counter_t, event_handler> handlers;
  counter_t idCounter = 0;

protected:
  /*! Fire the event!
   *
   * @param args Arguments to pass on to handlers
   *
   * parameters will not be forwarded because they cannot be moved to multiple
   * places at once.
   *
   * @todo find a nice way to fire handlers in parallel
   * @todo should event parameters be forwarded
   * the initial reaction is "obviously yes", but then moved/gutted objects
   * could not be used for the second handler.  I'm not yet 100% sure if the
   * answer should continue to be 'no'(seems as though it should).
   */
  auto fire(Args... args) {
    using handler_result = typename event_handler::handler::result_type;
    if constexpr (std::is_same_v<handler_result, void>){
      for(auto& [id, handler] : handlers){
        handler(args...);
      }

      return;
    } else {
      std::vector<handler_result> results;

      for(auto& [id, handler] : handlers) {
        results.emplace_back(handler(args...));
      }

      return COMBINER<handler_result>()(results.begin(), results.end());
    }
  }

  /*! Fire the event!
   *
   * @param args Arguments to pass on to handlers
   */
  void operator()(Args... args) {
    fire(std::forward<Args>(args)...);
  }

  event_channel_impl() = default;

  event_channel_impl(const event_channel_impl&) = default;

  event_channel_impl(event_channel_impl&&) noexcept = default;

public:
  ~event_channel_impl() = default;

  event_channel_impl& operator=(const event_channel_impl&) = default;

  event_channel_impl& operator=(event_channel_impl&&) noexcept = default;

  /*! Register new handler
   *
   * @param handler Handler to enlist
   *
   * @return The new modified channel
   */
  event_handler subscribe(const handler& handle) {
    handlers.emplace(std::make_pair(idCounter, event_handler{ *this, idCounter, handle }));

    return handlers.at(idCounter++);
  }

  /*!
   */
  event_handler subscribe(const simple_handler& handle) {
    handlers.emplace(std::make_pair(idCounter, event_handler{ *this, idCounter, handle }));

    return handlers.at(idCounter++);
  }

  /*! Unregister a previously registered handler
   *
   * @param ref Handler to no longer be fired when the event goes off
   */
  void unsubscribe(const event_handler& handle) {
    handlers.erase(handlers.find(handle.mCounter));
  }

  /*! Register new handler
   *
   * @param handler Handler to register
   *
   * @return The new modified channel
   */
  event_channel_impl& operator+=(const handler& handle) {
    subscribe(handle);

    return *this;
  }

  /*!
   * @todo implement handler de-registration
   */
  event_channel_impl& operator-=(const event_handler& handler) {
    unsubscribe(handler);

    return *this;
  }

  /*! Remove all registered handlers
   */
  void clear() {
    handlers.clear();
    idCounter = 0;
  }

  friend auto operator<=>(const event_channel_impl&, const event_channel_impl&) = default;
};

template<typename Signature, template<typename> typename COMBINER = default_combiner>
using event_channel = event_channel_impl<Signature, COMBINER>;

template<typename Signature, template<typename> typename COMBINER = default_combiner>
using event_trigger = typename event_channel<Signature, COMBINER>::event_trigger;

}

#endif
