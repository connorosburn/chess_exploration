#include "../catch.hpp"
#include "../../lib/GameEngine/Chess.hpp"

TEST_CASE("The game starts with zero moves") {
    Chess chess;
    REQUIRE(chess.getTurnCount() == 0);
}

TEST_CASE("Can tell you where pieces are") {
    Chess chess;
    REQUIRE(chess.getPiece("a2").toString() == "p0");
    REQUIRE(chess.getPiece("a1").toString() == "r0");
    REQUIRE(chess.getPiece("a7").toString() == "p1");
    REQUIRE(chess.getPiece("a8").toString() == "r1");
    REQUIRE(chess.getPiece("c8").toString() == "b1");
    REQUIRE(chess.getPiece("d1").toString() == "q0");
}

TEST_CASE("Increments the turn counter") {
    Chess chess;
    REQUIRE(chess.getTurnCount() == 0);
    REQUIRE(chess.move("a2", "a4"));
    REQUIRE(chess.getTurnCount() == 1);
    REQUIRE(chess.move("c7", "c5"));
    REQUIRE(chess.getTurnCount() == 2);
}

TEST_CASE("Does not allow a player to move out of turn") {
    Chess chess;
    REQUIRE(chess.move("a2", "a4"));
    REQUIRE(!chess.move("b2", "b4"));
}

TEST_CASE("Allows a pawn to move twice on its first move") {
    Chess chess;
    REQUIRE(chess.move("a2", "a4"));
    REQUIRE(chess.move("c7", "c5"));
    REQUIRE(chess.getPiece("a4").toString() == "p0");
    REQUIRE(chess.getPiece("c5").toString() == "p1");
}

TEST_CASE("Does not allow a pawn to move twice after the first move") {
    Chess chess;
    REQUIRE(chess.move("a2", "a4"));
    REQUIRE(chess.move("c7", "c5"));
    REQUIRE(!chess.move("a4", "a6"));
}

TEST_CASE("Does not allow a pawn to move diagonally under normal circumstances") {
    Chess chess;
    REQUIRE(!chess.move("a2", "b3"));
}

TEST_CASE("Allows a pawn to capture") {
    Chess chess;
    REQUIRE(chess.move("a2", "a4"));
    REQUIRE(chess.move("b7", "b5"));
    REQUIRE(chess.move("a4", "b5"));
}

TEST_CASE("Allows rooks to move properly") {
    Chess chess;
    REQUIRE(chess.move("a2", "a4"));
    REQUIRE(chess.move("a7", "a5"));
    REQUIRE(chess.move("a1", "a3"));
    REQUIRE(chess.move("a8", "a6"));
    REQUIRE(chess.move("a3", "c3"));
    REQUIRE(chess.move("a6", "c6"));
}

TEST_CASE("Does not allow rooks to move improperly") {
    Chess chess;
    REQUIRE(chess.move("b2", "b3"));
    REQUIRE(!chess.move("a1", "b2"));
}

TEST_CASE("Allows bishops to move properly") {
    Chess chess;
    REQUIRE(chess.move("b2", "b3"));
    REQUIRE(chess.move("d7", "d6"));
    REQUIRE(chess.move("c1", "a3"));
    REQUIRE(chess.move("c8", "h3"));
}

TEST_CASE("Does not allow bishops to move improperly") {
    Chess chess;
    REQUIRE(chess.move("c2", "c4"));
    REQUIRE(chess.move("c7", "c5"));
    REQUIRE(!chess.move("c1", "c3"));
    REQUIRE(!chess.move("c8", "c6"));
}

TEST_CASE("Allows queen to move properly") {
    Chess chess;

    REQUIRE(chess.move("d2", "d4"));
    REQUIRE(chess.move("d7", "d5"));

    REQUIRE(chess.move("d1", "d3"));
    REQUIRE(chess.move("d8", "d6"));

    REQUIRE(chess.move("d3", "a6"));
    REQUIRE(chess.move("d6", "g3"));
}

TEST_CASE("Allows knight to move properly") {
    Chess chess;

    REQUIRE(chess.move("b1", "a3"));
    REQUIRE(chess.move("g8", "h6"));
    REQUIRE(chess.move("a3", "c4"));
    REQUIRE(chess.move("h6", "f5"));
}

TEST_CASE("Allows king to move properly") {
    Chess chess;

    REQUIRE(chess.move("e2", "e3"));
    REQUIRE(chess.move("e7", "e6"));
    REQUIRE(chess.move("e1", "e2"));
    REQUIRE(chess.move("e8", "e7"));
    REQUIRE(chess.move("e2", "d3"));
    REQUIRE(chess.move("e7", "f6"));
}