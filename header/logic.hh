#ifndef __LOGIC_HH__
#define __LOGIC_HH__

/*!
 * @example test-logic.cc
 */

#include<string>
#include<set>
#include<memory>

namespace gsw{

class prop;

prop operator""_lvar( const char* name, size_t sz );

/*! Logical proposition
 */
class prop{
private:
  struct operation{
    virtual bool evaluate( const std::set<std::string>& facts ) const = 0;
  };

  using op_ptr = std::shared_ptr<operation>;

  struct variable : public operation{
    std::string name;

    bool evaluate( const std::set<std::string>& facts ) const;
  };
  struct conjunction : public operation{
    op_ptr lhs;
    op_ptr rhs;

    bool evaluate( const std::set<std::string>& facts ) const;
  };
  struct disjunction : public operation{
    op_ptr lhs;
    op_ptr rhs;

    bool evaluate( const std::set<std::string>& facts ) const;
  };
  struct negation : public operation{
    op_ptr operand;

    bool evaluate( const std::set<std::string>& facts ) const;
  };

  prop( const op_ptr value );

  op_ptr mValue;

public:
  prop operator&&( const prop& conjunct ) const;

  prop operator||( const prop& disjunct ) const;

  prop operator!() const;

  prop implies( const prop& consequent ) const;

  /*! If and only if
   *
   * @param consequent proposition to evaluate against
   */
  prop iff( const prop& consequent ) const;

  /*! Evaluate proposition using given facts
   *
   * @param facts Set of established truths.
   *
   * @return Whether the proposition is true given facts
   */
  bool evaluate( const std::set<std::string> facts ) const;

  /*! Reverse evaluation
   *
   * @param variables set of variables to work with
   *
   * @return set of all possible solutions to proposition
   *
   * Determine what combinations of given variables make proposition true.
   * Provided solutions only consist of those that can be made up from vars
   * provided in variables.
   */
  std::set<std::set<std::string> > evaluate_all( const std::set<std::string>& variables ) const;

  /*! Creates basic proposition that consists only of a variable named name
   *
   * User string literal operator.
   * Used as:
   * "foo"_lvar;
   *
   * To create a variable proposition named foo.
   */
  friend prop operator""_lvar( const char* name, size_t sz );
};

}

#endif

