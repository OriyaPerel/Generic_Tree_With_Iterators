
#include "doctest.h"
#include "Player.hpp"
#include "Board.hpp"
#include "Hexigon.hpp"
#include "catan.hpp"
#include "developmentCard.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
using namespace std;

Player *p1 = new Player("Player 1");
Player *p2 = new Player("Player 2");
Player *p3 = new Player("Player 3");

Catan game(p1, p2, p3);
Board &board = game.getBoard();

TEST_CASE("the player is created with the correct name")
{
    CHECK(p1->getName() == "Player 1");
}

TEST_CASE("the turn is set and pass correctly")
{
    CHECK(p1->isHisTurn() == true);
    CHECK(p2->isHisTurn() == false);
    game.endTurn(p1);
    CHECK(p1->isHisTurn() == false);
    CHECK(p2->isHisTurn() == true);
}

TEST_CASE("the player dont have enough resources or its not his turn for settlement")
{

    vector<string> places2 = {"lumber", "ore", "lumber"};
    vector<int> placesNum2 = {8, 3, 11};

    CHECK_THROWS_MESSAGE(p1->placeSettelemnt(places2, placesNum2, board), "it is not your turn");
    vector<string> places3 = {"sea", "sea", "grain"};
    vector<int> placesNum3 = {3, 2, 12};
    p2->placeSettelemnt(places3, placesNum3, board);
    vector<string> places4 = {"grain", "grain", "lumber"};
    vector<int> placesNum4 = {12, 9, 11};
    p2->placeSettelemnt(places4, placesNum4, board);
    p2->RemoveOraddResource(ResourceType::brick, -2);
    CHECK_THROWS_MESSAGE(p2->placeSettelemnt(places2, placesNum2, board), "player can't buy a settlement");
}

TEST_CASE("the player can place a settelemt in corrent place")
{
    vector<string> places2 = {"grain", "grian", "sea"};
    vector<int> placesNum2 = {9, 12, 3};
    CHECK_THROWS_MESSAGE(p2->placeSettelemnt(places2, placesNum2, board), "There is already a settlement in this edge");
    vector<string> places3 = {"sea", "grian", "sea"};
    vector<int> placesNum3 = {4, 9, 3};
    CHECK_THROWS_MESSAGE(p2->placeSettelemnt(places3, placesNum3, board), "There are no 2 roads between the vertex and the player's settlements");
}

TEST_CASE("the player can place a road in corrent place")
{
    vector<string> roads3 = {"sea", "lumber"};
    vector<int> roadsNum3 = {4, 11};
    CHECK_THROWS_MESSAGE(p2->placeRoad(roads3, roadsNum3, board), "There is no common edge in this places");

    vector<string> roads4 = {"wool", "lumber"};
    vector<int> roadsNum4 = {2, 9};
    CHECK_THROWS_MESSAGE(p2->placeRoad(roads4, roadsNum4, board), "There is no settlement in this edge");

    CHECK_THROWS_MESSAGE(p2->placeRoad(roads4, roadsNum4, board), "There is already a road in this edge");

    vector<string> roads5 = {"grain", "grain"};
    vector<int> roadsNum5 = {12, 9};
    p2->placeRoad(roads5, roadsNum5, board);
    vector<string> roads6 = {"grain", "sea"};
    vector<int> roadsNum6 = {12, 2};
    p2->placeRoad(roads6, roadsNum6, board);
    vector<string> roads7 = {"ore", "sea"};
    vector<int> roadsNum7 = {10, 1};
    CHECK_THROWS_MESSAGE(p2->placeRoad(roads7, roadsNum7, board), "There is not a path to this edge");
    game.endTurn(p2);
}

TEST_CASE("chenging settlement to city")
{
    vector<string> places1 = {"sea", "sea", "lumber"};
    vector<int> placesNum1 = {5, 6, 8};
    p3->placeSettelemnt(places1, placesNum1, board);
    
   // p3->printPlaces(); we can see that the settlement is in the right place
    CHECK_THROWS_MESSAGE(p1->chengeSettlementToCity(places1, placesNum1, board), "It's not your turn");

    CHECK_THROWS_MESSAGE(p3->chengeSettlementToCity(places1, placesNum1, board), "player can't buy a city");

    // Now give p3 enough resources, but ensure they don't own the settlement
    p3->RemoveOraddResource(ResourceType::ore, 3);
    p3->RemoveOraddResource(ResourceType::grain, 2);

    CHECK_THROWS_MESSAGE(p2->chengeSettlementToCity(places1, placesNum1, board), "You can't change this settlement, it's not yours");
    p3->chengeSettlementToCity(places1, placesNum1, board);
   // p3->printPlaces(); we can see that the settlement is now a city
}