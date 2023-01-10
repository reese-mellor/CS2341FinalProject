// #define CATCH_CONFIG_MAIN
// #include "catch2/catch.hpp"
// #include "AVLTree.h"
// // add includes


// TEST_CASE("Check that file object works", "[file]"){
//     AVLTree <int> a;
//     //make public function for imbalance and check -- after insert that would make tree imbalanced
//     //call insert multiple times
//     SECTION("Insert"){
//         a.insert(10);
//         REQUIRE((a.size() == 1));
//         REQUIRE((a.contains(10) == true));
//         a.insert(12);
//         REQUIRE((a.size() == 2));
//         REQUIRE((a.contains(12) == true));
//         a.insert(14);
//         REQUIRE((a.size() == 3));
//         REQUIRE((a.contains(14) == true));
//         a.insert(9);
//         REQUIRE((a.size() == 4));
//         REQUIRE((a.contains(9) == true));
//         a.insert(8);
//         REQUIRE((a.size() == 5));
//         REQUIRE((a.contains(8) == true));
//         a.insert(74);
//         REQUIRE((a.size() == 6));
//         REQUIRE((a.contains(74) == true));
//         a.insert(2);
//         REQUIRE((a.size() == 7));
//         REQUIRE((a.contains(2) == true));
//         a.insert(1);
//         REQUIRE((a.size() == 8));
//         REQUIRE((a.contains(1) == true));
//         a.insert(3);
//         REQUIRE((a.size() == 9));
//         REQUIRE((a.contains(3) == true));
//         a.insert(4);
//         REQUIRE((a.size() == 10));
//         REQUIRE((a.contains(4) == true));
//     };
// }