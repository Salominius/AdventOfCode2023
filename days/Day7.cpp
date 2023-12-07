#include "../helpers/inputHelpers.hpp"
#include "../helpers/lists.hpp"
#include <algorithm>
#include <map>

struct Hand {
  std::string cards;
  int type;
  int bid;
};

int getHandType(string hand) {
  std::map<char, size_t> cards;
  for (const char& card : hand)
    if (cards.count(card) == 0)
      cards[card] = 1;
    else
      cards[card]++;
  
  switch (cards.size()) {
    case 5:
      return 0; // high card
    case 4:
      return 1; // one pair
    case 3:
      for (const auto& card : cards) {
        if (card.second == 2)
          return 2; // two pair
        if (card.second == 3)
          return 3; // three of a kind
      }
    case 2:
      for (const auto& card : cards) {
        if (card.second == 3)
          return 4; // full house
        if (card.second == 4) 
          return 5; // four of a kind
      }
    case 1:
      return 6; // five of a kind
  }
  return -1; // error
}

int getHandTypePart2(string hand) {
  if (hand.find("J") == std::string::npos)
    return getHandType(hand); // no jokers
  
  std::map<char, size_t> cards;
  int jokers = 0;
  for (const char& card : hand) {
    if (card != 'J')
      if (cards.count(card) == 0)
        cards[card] = 1;
      else
        cards[card]++;
    else
      jokers++;
  }

  if (jokers >= 4)
    return 6; // 5 of a kind
  
  // This logic is based on the knowledge that we have at least one joker:
  switch(cards.size()) {
    case 4: 
      return 1; // nothing becomes one pair
    case 3:
      return 3; // nothing or one pair both become three of a kind
    case 2:
      if (jokers == 2 || jokers == 3)
        return 5; // nothing or one pair both become four of a kind
      if (jokers == 1) {
        if(cards.begin()->second == 2)
          return 4; // Two pair becomes full house
        else
          return 5; // Three of a kind becomes four of a kind
      }
    case 1:
      return 6; // five of a kind
  }

  return -1; // error
}

bool compareHands(Hand a, Hand b, std::string ranking) {
  if (a.type != b.type)
    return a.type < b.type;

  for (int i = 0; i < 5; i++) {
    if (a.cards[i] == b.cards[i])
      continue;
    
    return ranking.find(a.cards[i]) < ranking.find(b.cards[i]);
  }

  return true;
}

bool compareHandsPart1(Hand a, Hand b) {
  return compareHands(a, b, "23456789TJQKA");
}

bool compareHandsPart2(Hand a, Hand b) {
  return compareHands(a, b, "J23456789TQKA");
}

int main() {
  int part1 = 0;
  int part2 = 0;

  // Read input
  std::vector<Hand> hands;
  for (const string& line : getInput("../inputs/day7.txt")) {
    std::string hand = line.substr(0, line.find(" "));
    int type = getHandType(hand);
    int bid = stoi(line.substr(line.find(" ") + 1));
    hands.push_back({hand, type, bid});
  }
  
  // Part 1:
  std::sort(hands.begin(), hands.end(), compareHandsPart1);
  for (int i = 0; i < hands.size(); i++)
    part1 += hands[i].bid * (i + 1);
  
  // Part 2:
  for (Hand& hand : hands)
    hand.type = getHandTypePart2(hand.cards);

  std::sort(hands.begin(), hands.end(), compareHandsPart2);
  for (int i = 0; i < hands.size(); i++)
    part2 += hands[i].bid * (i + 1);

  std::cout << "Part 1: " << part1 << std::endl; //246409899
  std::cout << "Part 2: " << part2 << std::endl; //244848487
}