// liorbrown@outlook.co.il

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <string>
#include "doctest.hpp"
#include "PlayersList.hpp"
#include "Baron.hpp"
#include "Spy.hpp"
#include "General.hpp"
#include "Governor.hpp"
#include "Merchant.hpp"
#include "Judge.hpp"

void emplaceBack(PlayersList& list, Player* newPlayer)
{
    list.list.emplace_back(newPlayer);
}

/// @brief Checks if 2 string arrays are equals
/// @param left Left strings array
/// @param right Right strings array
/// @return True - if all cells equals
bool isEqual(string* left, string* right, size_t size)
{
    return false;
}

TEST_SUITE("Player list testing")
{
    TEST_CASE("Creating PlayerList")
    {
        // Init list
        CHECK(PlayersList::getInstance().newPlayer("lior"));
        CHECK(PlayersList::getInstance().newPlayer("magi"));
        CHECK(PlayersList::getInstance().newPlayer("aviad"));
        CHECK(PlayersList::getInstance().newPlayer("shachar"));
        CHECK(PlayersList::getInstance().newPlayer("elina"));

        // Check that can't insert same name twice return false and not inserting
        CHECK_FALSE(PlayersList::getInstance().newPlayer("magi"));

        CHECK(PlayersList::getInstance().newPlayer("imri"));

        // Check that can't insert more then 6 players
        CHECK_THROWS_AS(PlayersList::getInstance().newPlayer("bob"),out_of_range);

        // Check that all players are in,
        // on the way checks getPlayer method
        CHECK(PlayersList::getInstance().getPlayer("lior"));
        CHECK(PlayersList::getInstance().getPlayer("magi"));
        CHECK(PlayersList::getInstance().getPlayer("aviad"));
        CHECK(PlayersList::getInstance().getPlayer("shachar"));

        // Check if getPlayer return null for non-exist name
        CHECK_FALSE(PlayersList::getInstance().getPlayer("herut"));
    }

    TEST_CASE("Test getNext()")
    {
        // Check that getNext go according to insertion order, in cycle
        CHECK_EQ(PlayersList::getInstance().getNext()->getName(), "lior");
        CHECK_EQ(PlayersList::getInstance().getNext()->getName(), "magi");
        CHECK_EQ(PlayersList::getInstance().getNext()->getName(), "aviad");
        CHECK_EQ(PlayersList::getInstance().getNext()->getName(), "shachar");
        CHECK_EQ(PlayersList::getInstance().getNext()->getName(), "elina");
        CHECK_EQ(PlayersList::getInstance().getNext()->getName(), "imri");
        CHECK_EQ(PlayersList::getInstance().getNext()->getName(), "lior");
        CHECK_EQ(PlayersList::getInstance().getNext()->getName(), "magi");
    }

    TEST_CASE("Remove player")
    {
        Player* player;

        CHECK((player = PlayersList::getInstance().getPlayer("aviad")));
        
        // Remove player after current player magi
        PlayersList::getInstance().remove(player);

        CHECK((player = PlayersList::getInstance().getPlayer("lior")));
        
        // Remove player before current player magi
        PlayersList::getInstance().remove(player);

        // Check list after removing
        CHECK_EQ(PlayersList::getInstance().getNext()->getName(), "shachar");
        CHECK_EQ(PlayersList::getInstance().getNext()->getName(), "elina");
        CHECK_EQ(PlayersList::getInstance().getNext()->getName(), "imri");
        CHECK_EQ(PlayersList::getInstance().getNext()->getName(), "magi");

        // Save this player for next checking
        CHECK_EQ((player = PlayersList::getInstance().getNext())->getName(), "shachar");

        // Try to remove current turn player
        CHECK_THROWS_AS(PlayersList::getInstance().remove(player),invalid_argument);

        // Try remove null
        CHECK_THROWS_AS(PlayersList::getInstance().remove(nullptr),invalid_argument);

        player = new Baron("somebody");

        // Try remove player not in list
        CHECK_THROWS_AS(PlayersList::getInstance().remove(player), invalid_argument);

        player = PlayersList::getInstance().getPlayer("elina");
        PlayersList::getInstance().remove(player);

        player = PlayersList::getInstance().getPlayer("magi");
        PlayersList::getInstance().remove(player);

        player = PlayersList::getInstance().getPlayer("imri");
        PlayersList::getInstance().remove(player);

        // Check getNext when only 1 player remaining
        // suppose to return  null, and this is the signal that the game end
        CHECK_FALSE(PlayersList::getInstance().getNext());
    }

    TEST_CASE("Test current and clear methods")
    {
        // Check current method
        CHECK_EQ(PlayersList::getInstance().current()->getName(), "shachar");

        // Checking clear method
        PlayersList::getInstance().clear();

        // Try to getNext on empty list
        CHECK_THROWS_AS(PlayersList::getInstance().getNext(),out_of_range);

        // Check players not exist
        CHECK_FALSE(PlayersList::getInstance().getPlayer("shachar"));
        CHECK_FALSE(PlayersList::getInstance().getPlayer("elina"));
        CHECK_FALSE(PlayersList::getInstance().getPlayer("imri"));
        CHECK_FALSE(PlayersList::getInstance().getPlayer("magi"));

        // Try get current on empty list
        CHECK_THROWS_AS(PlayersList::getInstance().current(),out_of_range);

        CHECK(PlayersList::getInstance().newPlayer("lior"));
        CHECK(PlayersList::getInstance().newPlayer("magi"));
        CHECK(PlayersList::getInstance().newPlayer("aviad"));
        CHECK(PlayersList::getInstance().newPlayer("shachar"));

        // Try get current, when list iterator is not set yet 
        // because getNext not called since last init
        CHECK_THROWS_AS(PlayersList::getInstance().current(),out_of_range);
    }

    TEST_CASE("Test getListString()")
    {
        PlayersList::getInstance().clear();

        string excpected;
        string actual = PlayersList::getInstance().getListString();

        // Check string of empty list
        CHECK_EQ(actual, excpected); 

        emplaceBack(PlayersList::getInstance(), new Baron("lior"));
        emplaceBack(PlayersList::getInstance(), new Spy("magi"));
        emplaceBack(PlayersList::getInstance(), new Judge("aviad"));
        emplaceBack(PlayersList::getInstance(), new General("shachar"));
 
        excpected = "lior the Baron\nmagi the Spy\naviad the Judge\nshachar the General\n";
        actual = PlayersList::getInstance().getListString();

        // Check string of full list
        CHECK_EQ(actual, excpected);
    }

    TEST_CASE("Test players()")
    {
        vector<string> expected{"lior", "magi", "aviad", "shachar"};
        vector<string> actual = PlayersList::getInstance().players();

        // Check full list
        CHECK_EQ(actual, expected);

        PlayersList::getInstance().clear();

        expected.clear();
        actual = PlayersList::getInstance().players();

        // Check empty list
        CHECK_EQ(actual, expected);
    }

    TEST_CASE("Test PlayersList::itearator")
    {
        // Check begin and end empty list
        CHECK_THROWS_AS(PlayersList::getInstance().begin(), out_of_range);
        CHECK_THROWS_AS(PlayersList::getInstance().end(), out_of_range);

        // Init list
        CHECK(PlayersList::getInstance().newPlayer("lior"));
        CHECK(PlayersList::getInstance().newPlayer("magi"));
        CHECK(PlayersList::getInstance().newPlayer("aviad"));
        CHECK(PlayersList::getInstance().newPlayer("shachar"));
        CHECK(PlayersList::getInstance().newPlayer("elina"));

        // Check begin and end when turn not set yet
        CHECK_THROWS_AS(PlayersList::getInstance().begin(), out_of_range);
        CHECK_THROWS_AS(PlayersList::getInstance().end(), out_of_range);

        // Move current turn to aviad
        PlayersList::getInstance().getNext();
        PlayersList::getInstance().getNext();
        PlayersList::getInstance().getNext();

        // Note that iterator skip on current player aviad
        // because it gives only other players
        // See for iterator documantation for more details and explanation
        string excpected[]{"lior", "magi", "shachar", "elina",};
        size_t i = 0;

        // I test all iterator opertaors in 1 loop
        // I didn't use foreach because its not test the -> operator
        // note that unlike regular iterator * and -> returns the same
        // See for iterator documantation for more details and explanation
        for 
        (
            auto player = PlayersList::getInstance().begin();
            player != PlayersList::getInstance().end();
            ++player)
        {
            CHECK_EQ((*player)->getName(), excpected[i]);
            CHECK_EQ(player->getName(), excpected[i++]);
        }
    }
}

// This test suite test all the actions that are not depends on special rolls abilities
TEST_SUITE("Basic player actions")
{
    // I use the spy classes only because all basic actions are regular
    // and the Player base class itself is unaccesible
    TEST_CASE("Init players list")
    {
        PlayersList::getInstance().clear();

        emplaceBack(PlayersList::getInstance(), new Spy("lior"));
        emplaceBack(PlayersList::getInstance(), new Spy("magi"));
        emplaceBack(PlayersList::getInstance(), new Spy("aviad"));
        emplaceBack(PlayersList::getInstance(), new Spy("shachar"));
    }
    TEST_CASE("Gather")
    {
        Player* magi = PlayersList::getInstance().getPlayer("magi");

        magi->gather();

        size_t excpected = 1;
        size_t actual = magi->getCoins();

        // Check first gather
        CHECK_EQ(excpected, actual);

        magi->gather();

        excpected = 2;
        actual = magi->getCoins();

        // Check seconed gather
        CHECK_EQ(excpected, actual);
    }    

    TEST_CASE("Tax")
    {
        Player* shachar = PlayersList::getInstance().getPlayer("shachar");

        shachar->tax();

        size_t excpected = 2;
        size_t actual = shachar->getCoins();

        // Check first gather
        CHECK_EQ(excpected, actual);

        shachar->tax();

        excpected = 4;
        actual = shachar->getCoins();

        // Check seconed gather
        CHECK_EQ(excpected, actual);
    }

    TEST_CASE("Bribe")
    {
        Player* magi = PlayersList::getInstance().getPlayer("magi");

        // Check bribe when game not active
        CHECK_THROWS_AS(magi->bribe(), runtime_error);

        // Move turn to magi
        PlayersList::getInstance().getNext();
        PlayersList::getInstance().getNext();

        // Ensure we are on magi turn, and she have 2 coins
        CHECK_EQ(PlayersList::getInstance().current()->getName(), "magi");
        CHECK_EQ(magi->getCoins(), 2);

        // Check try to bribe withot enough coins
        CHECK_THROWS_AS(magi->bribe(), logic_error);

        magi->tax();

        // Ensure magi have enough coins
        CHECK_EQ(magi->getCoins(), 4);

        magi->bribe();

        // Ensure magi pay the price
        CHECK_FALSE(magi->getCoins());

        // Forward one turn
        PlayersList::getInstance().getNext();

        // Ensure it's still magi turn
        CHECK_EQ(PlayersList::getInstance().current()->getName(), "magi");

        // Check try to bribe when already bribed
        CHECK_THROWS_AS(magi->bribe(), logic_error);

        // Forward seconed turn
        PlayersList::getInstance().getNext();

        // Check that turn moved on to next player
        CHECK_NE(PlayersList::getInstance().current()->getName(), "magi");
    }

    TEST_CASE("Arrest")
    {
        // Init list
        PlayersList::getInstance().clear();
        emplaceBack(PlayersList::getInstance(), new Spy("lior"));
        emplaceBack(PlayersList::getInstance(), new Spy("magi"));
        emplaceBack(PlayersList::getInstance(), new Spy("aviad"));
        emplaceBack(PlayersList::getInstance(), new Spy("shachar"));

        Player* player = PlayersList::getInstance().getPlayer("magi");
        
        // Try to arrest when game not active
        // This is problam because arrested() go to PlayersList::getInstance().current
        CHECK_THROWS_AS(player->arrested(), out_of_range);

        // Move turn to magi
        PlayersList::getInstance().getNext(); // lior
        Player* current = PlayersList::getInstance().getNext(); // magi

        //Ensure it's magi turn
        CHECK_EQ(PlayersList::getInstance().current()->getName(), "magi");

        // Try to be arrested by your self 🙄
        CHECK_THROWS_AS(player->arrested(), logic_error);

        player = PlayersList::getInstance().getPlayer("lior");

        // Ensure lior don't have any coins
        CHECK_FALSE(player->getCoins());

        // Try to arrest lior
        CHECK_FALSE(player->arrested());

        // Ensure current player magi didn't get coin
        CHECK_FALSE(current->getCoins());

        player = PlayersList::getInstance().getPlayer("shachar");
        player->tax();

        // Ensure shachar coins count
        CHECK_EQ(player->getCoins(), 2);

        // Check good arrest
        CHECK(player->arrested());

        // Check shachar lost 1 coin and magi get 1 coin
        CHECK_EQ(player->getCoins(), 1);
        CHECK_EQ(current->getCoins(), 1);

        // Try to arrest shachar in the next turn
        PlayersList::getInstance().getNext(); // aviad

        CHECK_THROWS_AS(player->arrested(), logic_error);

        // Move to lior turn
        PlayersList::getInstance().getNext(); // shachar
        current = PlayersList::getInstance().getNext(); // lior

        CHECK_FALSE(current->getCoins());
        CHECK_EQ(player->getCoins(),1);

        // Try to arrest shachar after few turns
        CHECK(player->arrested());

        CHECK_EQ(current->getCoins(),1);
        CHECK_FALSE(player->getCoins());
    }

    TEST_CASE("Sanction")
    {
        Player* sanctioner = PlayersList::getInstance().getPlayer("aviad");
        Player* sanctioned = PlayersList::getInstance().getPlayer("lior");

        // Check try to sanction whaen don't have enough coins
        CHECK_THROWS_AS(sanctioner->sanction(sanctioned), logic_error);

        // Check try to sanction null
        CHECK_THROWS_AS(sanctioner->sanction(nullptr), invalid_argument);

        // Check try to sanction itself
        CHECK_THROWS_AS(sanctioner->sanction(sanctioner), logic_error);

        sanctioner->tax();
        sanctioner->tax();

        // Ensure aviad have 4 coins before sanction
        CHECK_EQ(sanctioner->getCoins(), 4);

        sanctioner->sanction(sanctioned);

        // Ensure aviad pay the price
        CHECK_EQ(sanctioner->getCoins(), 1);

        sanctioned = PlayersList::getInstance().getNext(); // magi

        // Ensure magi is not sanctioned
        CHECK_FALSE(sanctioned->getIsSanctioned());

        CHECK_EQ(sanctioned->getCoins(), 1);

        sanctioned->gather();
        sanctioned->tax();

        CHECK_EQ(sanctioned->getCoins(), 4);
        
        // Move turn to lior
        sanctioned = PlayersList::getInstance().getNext(); // aviad
        sanctioned = PlayersList::getInstance().getNext(); // shachar
        sanctioned = PlayersList::getInstance().getNext(); // lior

        // Ensure lior is sanctioned
        CHECK(sanctioned->getIsSanctioned());

        CHECK_THROWS_AS(sanctioned->gather(), logic_error);
        CHECK_THROWS_AS(sanctioned->tax(), logic_error);
        
        // Release lior
        sanctioned->getIsSanctioned() = false;

        // Check that lior not sanctioned any more
        CHECK_FALSE(sanctioned->getIsSanctioned());

        CHECK_EQ(sanctioned->getCoins(), 1);
        sanctioned->gather();
        sanctioned->tax();

        CHECK_EQ(sanctioned->getCoins(), 4);
    }

    TEST_CASE("Coup")
    {
        Player* couper = PlayersList::getInstance().getPlayer("magi");
        Player* couped = PlayersList::getInstance().getPlayer("aviad");

        CHECK_EQ(couper->getCoins(), 4);

        // Check try to coup when don't have enough coins
        CHECK_THROWS_AS(couper->coup(couped), logic_error);

        // Check try to coup null
        CHECK_THROWS_AS(couper->coup(nullptr), invalid_argument);

        // Check try to coup himself
        CHECK_THROWS_AS(couper->coup(couper), logic_error);

        couper->tax();
        couper->tax();

        // Ensure couper coins before coup couper pay the price
        CHECK_EQ(couper->getCoins(), 8);

        couper->coup(couped);

        // Check couper pay the price
        CHECK_EQ(couper->getCoins(), 1);

        // Ensure aviad couped
        CHECK_FALSE(PlayersList::getInstance().getPlayer("aviad"));

        // Ensure list is OK
        CHECK_EQ(PlayersList::getInstance().getNext()->getName(), "magi");
        CHECK_EQ(PlayersList::getInstance().getNext()->getName(), "shachar");
        CHECK_EQ(PlayersList::getInstance().getNext()->getName(), "lior");
        CHECK_EQ(PlayersList::getInstance().getNext()->getName(), "magi");
    }

    TEST_CASE("Opertors")
    {
        Player* magi = PlayersList::getInstance().getPlayer("magi");
        magi->getCoins() = 0;

        // Check ++
        ++*magi;

        CHECK_EQ(magi->getCoins(),1);

        // Check ++ return player itself after increasing
        CHECK_EQ((++*magi).getCoins(),2);

        // Check --
        --*magi;

        CHECK_EQ(magi->getCoins(),1);

        // Check -- return player itself after increasing
        CHECK_FALSE((--*magi).getCoins());

        // Ensure that -- on 0 coins do nothing and not exception
        // Check -- return player itself after increasing
        CHECK_FALSE((--*magi).getCoins());
    }
}

// In practice, it turned out that the code itself of the inheriting classes 
//is very, very sparse, and accordingly so are their tests. 
// See the Readme file for a detailed explanation of the reasons
TEST_SUITE("Rolls testing")
{
    TEST_CASE("Init players list")
    {
        // Init list
        PlayersList::getInstance().clear();
        emplaceBack(PlayersList::getInstance(), new Spy("Spy"));
        emplaceBack(PlayersList::getInstance(), new Merchant("Merchant"));
        emplaceBack(PlayersList::getInstance(), new Baron("Baron"));
        emplaceBack(PlayersList::getInstance(), new Judge("Judge"));
        emplaceBack(PlayersList::getInstance(), new Governor("Governor"));
        emplaceBack(PlayersList::getInstance(), new General("General"));
    }

    TEST_CASE("Spy")
    {
        Player::specialAbility excpected = Player::SPYING;
        Player::specialAbility actual = PlayersList::getInstance().getPlayer("Spy")->getAbility();

        // Ensure spy have the right flag, the implementaion itself is in the GUI game class
        CHECK_EQ(excpected, actual);
    }

    TEST_CASE("Merchant")
    {
        Player* merchant = PlayersList::getInstance().getPlayer("Merchant");

        // Check that increaseCoins not work when it not have enough coins
        CHECK_FALSE(merchant->getCoins());
        merchant->increaseCoins();
        CHECK_FALSE(merchant->getCoins());

        // Check it works whan have 3 or more coins
        merchant->tax();
        merchant->tax();

        CHECK_EQ(merchant->getCoins(), 4);
        merchant->increaseCoins();
        CHECK_EQ(merchant->getCoins(), 5);

        // Move to Spy turn
        Player* spy = PlayersList::getInstance().getNext();
        CHECK_FALSE(spy->getCoins());

        // Test that when arrested its lose 2 coins and the arrester player not get any
        merchant->arrested();

        CHECK_EQ(merchant->getCoins(), 3);
        CHECK_FALSE(spy->getCoins());
    }

    TEST_CASE("Baron")
    {
        Player* baron = PlayersList::getInstance().getPlayer("Baron");

        Player::specialAbility excpected = Player::EXCHANGE;
        Player::specialAbility actual = baron->getAbility();

        // Ensure Baron have the right flag, the implementaion itself is in the GUI game class
        CHECK_EQ(excpected, actual);

        // Ensure that when Baron sanctioned he gains 1 coin
        Player* spy = PlayersList::getInstance().getPlayer("Spy");

        spy->tax();
        spy->tax();

        CHECK_FALSE(baron->getCoins());
        spy->sanction(baron);
        CHECK_EQ(baron->getCoins(), 1);

        // Ensure that sanction itself works
        CHECK_THROWS_AS(baron->gather(), logic_error);
        CHECK_THROWS_AS(baron->tax(), logic_error);
    }

    TEST_CASE("Judge")
    {
        Player* judge = PlayersList::getInstance().getPlayer("Judge");

        Player::specialAbility excpected = Player::BLOCK_BRIBE;
        Player::specialAbility actual = judge->getAbility();

        // Ensure judge have the right flag, the implementaion itself is in the GUI game class
        CHECK_EQ(excpected, actual);

        Player* spy = PlayersList::getInstance().getPlayer("Spy");

        spy->tax();
        spy->tax();

        // Ensure that when player sanction judge he pays additional coin
        CHECK_EQ(spy->getCoins(), 5);
        spy->sanction(judge);
        CHECK_EQ(spy->getCoins(), 1);

        judge->getIsSanctioned() = false;

        spy->tax();
        
        // Ensure that when player that sanction judge have exactly 3
        // the sanction work and it not entered into minus
        CHECK_EQ(spy->getCoins(), 3);
        spy->sanction(judge);
        CHECK_FALSE(spy->getCoins());

        // Ensure that judge sanctioned successfuly
        // Ensure that sanction itself works
        CHECK_THROWS_AS(judge->gather(), logic_error);
        CHECK_THROWS_AS(judge->tax(), logic_error);
    }

    TEST_CASE("Governor")
    {
        Player* governor = PlayersList::getInstance().getPlayer("Governor");

        Player::specialAbility excpected = Player::BLOCK_TAX;
        Player::specialAbility actual = governor->getAbility();

        // Ensure governor have the right flag, the implementaion itself is in the GUI game class
        CHECK_EQ(excpected, actual);

        // Ensure governor get 3 coins when tax
        CHECK_FALSE(governor->getCoins());
        governor->tax();
        CHECK_EQ(governor->getCoins(), 3);
    }
    TEST_CASE("General")
    {
        Player* general = PlayersList::getInstance().getPlayer("General");

        Player::specialAbility excpected = Player::BLOCK_COUP;
        Player::specialAbility actual = general->getAbility();

        // Ensure general have the right flag, the implementaion itself is in the GUI game class
        CHECK_EQ(excpected, actual);

        Player* current = PlayersList::getInstance().current();

        // Check that when have no coins, can't arrest him like others
        CHECK_FALSE(general->arrested());

        general->tax();

        // Check that when have coins, he not loose it, and the other player get a coin
        CHECK_FALSE(current->getCoins());
        CHECK_EQ(general->getCoins(), 2);

        CHECK(general->arrested());

        CHECK_EQ(current->getCoins(), 1);
        CHECK_EQ(general->getCoins(), 2);
    }
}

TEST_CASE("Free memory")
{
    PlayersList::free();
}
