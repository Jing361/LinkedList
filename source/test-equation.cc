#include<catch.hpp>

#include<algorithm.hh>
#include<equation.hh>

using namespace gsw;

TEST_CASE( "Mathematical operators behave as expected", "[equ]" ){
  SECTION( "Basic operation" ){
    REQUIRE( ( "X"_evar ).evaluate( {{"X", 1}} ) == 1 );
    REQUIRE( ( "X"_evar ).evaluate( {{"X", 5}} ) == 5 );
    //REQUIRE( ( "x"_evar ).solve( {"x"} ) ==
    //         set<set<string> > {{"foo"}} );
  }

  SECTION( "Constants" ){
    REQUIRE( ( "1"_evar ).evaluate( {} ) == 1 );
    REQUIRE( ( "5"_evar ).evaluate( {{"X", 1}} ) == 5 );
    REQUIRE( ( "4.2"_evar ).evaluate( {{"X", 1}} ) == 4.2 );
    REQUIRE( ( 1.0_evar ).evaluate( {} ) == 1 );
    REQUIRE( ( 5.0_evar ).evaluate( {{"X", 1}} ) == 5 );
    REQUIRE( ( 4.2_evar ).evaluate( {{"X", 1}} ) == 4.2 );
  }

  SECTION( "Negation" ){
    REQUIRE( ( -"X"_evar ).evaluate( {{"X", 1}} ) == -1 );
    REQUIRE( ( - -"X"_evar ).evaluate( {{"X", 1}} ) == 1 );

    REQUIRE( ( -"5"_evar ).evaluate( {{"X", 1}} ) == -5 );
    REQUIRE( ( - -"5"_evar ).evaluate( {{"X", 1}} ) == 5 );
    REQUIRE( ( "-5"_evar ).evaluate( {{"X", 1}} ) == -5 );
    REQUIRE( ( - "-5"_evar ).evaluate( {{"X", 1}} ) == 5 );

    REQUIRE( ( - 5.0_evar ).evaluate( {{"X", 1}} ) == -5 );
    REQUIRE( ( - - 5.0_evar ).evaluate( {{"X", 1}} ) == 5 );
    REQUIRE( ( -5.0_evar ).evaluate( {{"X", 1}} ) == -5 );
    REQUIRE( ( - -5.0_evar ).evaluate( {{"X", 1}} ) == 5 );

    //REQUIRE( ( !"foo"_lvar ).solve( {"foo"} ) ==
    //         set<set<string> > {{}} );
  }

  SECTION( "Multiplication (*)" ){
    REQUIRE( ( "X"_evar * "Y"_evar ).evaluate( {{"X", 2}, {"Y", 3}} ) == 6 );
    REQUIRE( ( "X"_evar * "Y"_evar ).evaluate( {{"X", 3}, {"Y", -3}} ) == -9 );
    REQUIRE( ( "X"_evar * "Y"_evar ).evaluate( {{"X", -4}, {"Y", -3}} ) == 12 );
    REQUIRE( ( "X"_evar * "X"_evar ).evaluate( {{"X", 3}} ) == 9 );
    REQUIRE( ( "X"_evar * "5"_evar ).evaluate( {{"X", 3}} ) == 15 );
    REQUIRE( ( "4.2"_evar * "X"_evar ).evaluate( {{"X", 2}} ) == 8.4 );
    REQUIRE( ( "3"_evar * "5"_evar ).evaluate({}) == 15 );

    REQUIRE( ( "X"_evar * 5.0_evar ).evaluate( {{"X", 3}} ) == 15 );
    REQUIRE( ( 4.2_evar * "X"_evar ).evaluate( {{"X", 2}} ) == 8.4 );
    REQUIRE( ( 3.0_evar * 5.0_evar ).evaluate({}) == 15 );

    //REQUIRE( ( "foo"_lvar && "bar"_lvar ).solve( {"foo", "bar"} ) ==
    //         set<set<string> >( {{"foo", "bar"}} ) );
  }

  SECTION( "Division (/)" ){
    REQUIRE( ( "X"_evar / "Y"_evar ).evaluate( {{"X", 12}, {"Y", 4}} ) == 3 );
    REQUIRE( ( "X"_evar / "Y"_evar ).evaluate( {{"X", 12}, {"Y", -2}} ) == -6 );
    REQUIRE( ( "X"_evar / "X"_evar ).evaluate( {{"X", 12}} ) == 1 );
    REQUIRE( ( "X"_evar / "3"_evar ).evaluate( {{"X", 12}} ) == 4 );
    REQUIRE( ( "4.2"_evar / "X"_evar ).evaluate( {{"X", 2}} ) == 2.1 );
    REQUIRE( ( "15"_evar / "3"_evar ).evaluate( {} ) == 5 );

    REQUIRE( ( "X"_evar / 3.0_evar ).evaluate( {{"X", 12}} ) == 4 );
    REQUIRE( ( 4.2_evar / "X"_evar ).evaluate( {{"X", 2}} ) == 2.1 );
    REQUIRE( ( 15.0_evar / 3.0_evar ).evaluate( {} ) == 5 );
  }

  SECTION( "Addition (+)" ){
    REQUIRE( ( "X"_evar + "Y"_evar ).evaluate( {{"X", 1}, {"Y", 2}} ) == 3 );
    REQUIRE( ( "X"_evar + "Y"_evar ).evaluate( {{"X", 3}, {"Y", 2}} ) == 5 );
    REQUIRE( ( "X"_evar + "Y"_evar ).evaluate( {{"X", 5}, {"Y", -7}} ) == -2 );
    REQUIRE( ( "X"_evar + "3"_evar ).evaluate( {{"X", 3}} ) == 6 );
    REQUIRE( ( "5"_evar + "3"_evar ).evaluate( {} ) == 8 );

    REQUIRE( ( "X"_evar + 3.0_evar ).evaluate( {{"X", 3}} ) == 6 );
    REQUIRE( ( 5.0_evar + 3.0_evar ).evaluate( {} ) == 8 );

    //REQUIRE( ( "x"_evar || "y"_evar ).solve( {"x", "y"} ) ==
    //         set<set<string> >( {{"foo", "bar"}, {"foo"}, {"bar"}} ) );
  }

  SECTION( "Subtraction (-)" ){
    REQUIRE( ( "X"_evar - "Y"_evar ).evaluate( {{"X", 5}, {"Y", 4}} ) == 1 );
    REQUIRE( ( "X"_evar - "Y"_evar ).evaluate( {{"X", 5}, {"Y", 7}} ) == -2 );
    REQUIRE( ( "X"_evar - "Y"_evar ).evaluate( {{"X", 5}, {"Y", -7}} ) == 12 );
    REQUIRE( ( "X"_evar - "3"_evar ).evaluate( {{"X", 5}} ) == 2 );
    REQUIRE( ( "5"_evar - "3"_evar ).evaluate( {} ) == 2 );

    REQUIRE( ( "X"_evar - 3.0_evar ).evaluate( {{"X", 5}} ) == 2 );
    REQUIRE( ( 5.0_evar - 3.0_evar ).evaluate( {} ) == 2 );

    //REQUIRE( ( "x"_evar || "y"_lvar ).solve( {"x", "y"} ) ==
    //         set<set<string> >( {{"foo", "bar"}, {"foo"}, {"bar"}} ) );
  }

  SECTION( "Exponentiation (^)" ){
    REQUIRE( ( "X"_evar ).pow( "Y"_evar ).evaluate( {{"X", 2}, {"Y", 10}} ) == 1024 );
    REQUIRE( ( "X"_evar ).pow( "Y"_evar ).evaluate( {{"X", 3}, {"Y", 3}} ) == 27 );
    REQUIRE( ( "X"_evar ).pow( "Y"_evar ).evaluate( {{"X", 3}, {"Y", -3}} ) == ( 1.0 / 27.0 ) );
    REQUIRE( ( "X"_evar ).pow( "Y"_evar ).evaluate( {{"X", 2}, {"Y", 1.5}} ) == std::pow( 2, 1.5 ) );
    REQUIRE( ( "2"_evar ).pow( "X"_evar ).evaluate( {{"X", 3}} ) == std::pow( 2, 3 ) );
    REQUIRE( ( "X"_evar ).pow( "3"_evar ).evaluate( {{"X", 3}} ) == 27 );
    REQUIRE( ( "X"_evar ).pow( 3 ).evaluate( {{"X", 3}} ) == 27 );
    REQUIRE( are_equal( gsw::log( "X"_evar, "8"_evar ).evaluate( {{"X", 2}} ), std::log2( 8 ) ) );

    REQUIRE( ( 2.0_evar ).pow( "X"_evar ).evaluate( {{"X", 3}} ) == std::pow( 2, 3 ) );
    REQUIRE( ( "X"_evar ).pow( 3.0_evar ).evaluate( {{"X", 3}} ) == 27 );
  }

  SECTION( "Derivation" ){
    REQUIRE( ( "2"_evar ).derive( "X" ).evaluate( {} ) == 0 );
    REQUIRE( ( "2"_evar ).derive( "X" ).evaluate( {{"X", 5}} ) == 0 );
    REQUIRE( ( "X"_evar ).derive( "X" ).evaluate( {} ) == 1 );
    REQUIRE( ( "5"_evar * "X"_evar.pow( 2.0_cvar ) + ( "2"_evar * "X"_evar ) ).derive( "X" ).evaluate( {{"X", 3}} ) == 32 );
    REQUIRE( ( "2"_evar * "X"_evar ).derive( "X" ).evaluate( {{"X", 0}} ) == 2 );
    REQUIRE( e_evar.pow( "X"_evar ).evaluate( {{"X", 1}} ) == e_evar.evaluate( {} ) );
    REQUIRE( e_evar.pow( "X"_evar ).evaluate( {{"X", 0}} ) == 1 );
    REQUIRE( are_equal( e_evar.pow( "X"_evar ).derive( "X" ).evaluate( {{"X", 1}} ), e_evar.evaluate( {} ) ) );
    REQUIRE( are_equal( e_evar.pow( "X"_evar ).derive( "X" ).evaluate( {{"X", 0}} ), 1.0 ) );
    REQUIRE( ( "X"_evar ).pow( 2.0_cvar ).derive( "X" ).evaluate( {{"X", 3}} ) == 6 );

    REQUIRE( ( "2"_evar ).derive( "X", 2 ).evaluate( {} ) == 0 );
    REQUIRE( ( "2"_evar ).derive( "X", 2 ).evaluate( {{"X", 5}} ) == 0 );
    REQUIRE( ( "X"_evar ).derive( "X", 2 ).evaluate( {} ) == 0 );
    REQUIRE( ( "5"_evar * "X"_evar.pow( 2.0_cvar ) + ( "2"_evar * "X"_evar ) ).derive( "X", 2 ).evaluate( {{"X", 3}} ) == 10 );
    REQUIRE( ( "2"_evar * "X"_evar ).derive( "X", 2 ).evaluate( {{"X", 0}} ) == 0 );
    REQUIRE( ( "X"_evar ).pow( 2.0_cvar ).derive( "X", 2 ).evaluate( {{"X", 3}} ) == 2 );
    REQUIRE( ( "X"_evar ).pow( 2.0_cvar ).derive( "X", 2 ).evaluate( {{"X", 5}} ) == 2 );
    //REQUIRE( are_equal( e_evar.pow( "X"_evar ).derive( "X", 2 ).evaluate( {{"X", 1}} ), e_evar.evaluate( {} ) ) );
    //REQUIRE( are_equal( e_evar.pow( "X"_evar ).derive( "X", 2 ).evaluate( {{"X", 0}} ), 1 ) );

    equation temp = e_evar.pow( "X"_evar );
    REQUIRE( are_equal( temp.evaluate( {{"X", 1}} ), e_evar.evaluate( {} ) ) );
    /*for( int i = 0; i < 10; ++i ){
      temp = temp.derive( "X" );
      REQUIRE( are_equal( temp.evaluate( {{"X", 1}} ), e_evar.evaluate( {} ) ) );
    }*/
  }
}
