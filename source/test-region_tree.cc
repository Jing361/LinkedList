#include<catch.hpp>

#include<region_tree.hh>

using namespace gsw;

TEST_CASE( "Region trees (such as quad tree and octree)", "[region_tree]" ){
  quad_tree<double> qt( {0, 0}, {100, 100} );

  qt.insert( 12.0, {25, 25} );
  qt.insert( 15.0, {20, 20} );

  CHECK( qt.get_groups() == std::set<std::set<double> >{{12.0, 15.0}} );

  qt.insert( 18.0, {75, 75} );
  qt.insert( 21.0, {70, 70} );

  CHECK( qt.get_groups() == std::set<std::set<double> >{{12.0, 15.0},
                                                        {18.0, 21.0}} );

  qt.insert( 24.0, {71, 71} );

  CHECK( qt.get_groups() == std::set<std::set<double> >{{12.0, 15.0},
                                                        {24.0, 21.0},
                                                        {18}} );

  SECTION( "too many objects in a region after a split splits again" ){
  }
}
