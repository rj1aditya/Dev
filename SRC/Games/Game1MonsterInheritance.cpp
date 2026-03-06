//https://www.learncpp.com/cpp-tutorial/chapter-17-comprehensive-quiz/
#include <array>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <iostream>
#include <string>
#include <string_view>

// Generate a random number between min and max (inclusive)
// Assumes std::srand() has already been called
// Assumes max - min <= RAND_MAX
int getRandomNumber(int min, int max)
{
  static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) }; // static used for efficiency, so we only calculate this value once
  // evenly distribute the random number across our range
  return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

class Creature
{
protected:
  std::string m_name;
  char m_symbol {};
  int m_health {};
  int m_damage {};
  int m_gold {};

public:
  Creature(std::string_view name, char symbol, int health, int damage, int gold)
    : m_name{ name }
    , m_symbol{ symbol }
    , m_health{ health }
    , m_damage{ damage }
    , m_gold{ gold }
  {
  }

  char getSymbol() const { return m_symbol; }
  const std::string& getName() const { return m_name; }
  bool isDead() const { return m_health <= 0; }
  int getGold() const { return m_gold; }
  void addGold(int gold) { m_gold += gold; }
  void reduceHealth(int health) { m_health -= health; }
  int getHealth() const { return m_health; }
  int getDamage() const { return m_damage; }
};

class Player : public Creature
{
  int m_level{ 1 };

public:
  Player(std::string_view name)
      : Creature{ name, '@', 10, 1, 0 }
  {
  }

  void levelUp()
  {
    ++m_level;
    ++m_damage;
  }

  int getLevel() const { return m_level; }
  bool hasWon() const { return m_level >= 20; }
};

class Monster : public Creature
{
public:
  enum class Type
  {
    dragon,
    orc,
    slime,
    max_types
  };

private:
  static const Creature& getDefaultCreature(Type type)
  {
    static const std::array<Creature, static_cast<std::size_t>(Type::max_types)> monsterData{
      { { "dragon", 'D', 20, 4, 100 },
        { "orc", 'o', 4, 2, 25 },
        { "slime", 's', 1, 1, 10 } }
    };

    return monsterData.at(static_cast<std::size_t>(type));
  }

public:
  Monster(Type type)
      : Creature{ getDefaultCreature(type) }
  {
  }

  static Monster getRandomMonster()
  {
    int num{ getRandomNumber(0, static_cast<int>(Type::max_types) - 1) };
    return Monster{ static_cast<Type>(num) };
  }
};

// This function handles the player attacking the monster
void attackMonster(Player& player, Monster& monster)
{
  // If the player is dead, we can't attack the monster
  if (player.isDead())
    return;

  std::cout << "You hit the " << monster.getName() << " for " << player.getDamage() << " damage.\n";

  // Reduce the monster's health by the player's damage
  monster.reduceHealth(player.getDamage());

  // If the monster is now dead, level the player up
  if (monster.isDead())
  {
    std::cout << "You killed the " << monster.getName() << ".\n";
    player.levelUp();
    std::cout << "You are now level " << player.getLevel() << ".\n";
    std::cout << "You found " << monster.getGold() << " gold.\n";
    player.addGold(monster.getGold());
  }
}

// This function handles the monster attacking the player
void attackPlayer(const Monster& monster, Player& player)
{
  // If the monster is dead, it can't attack the player
  if (monster.isDead())
    return;

  // Reduce the player's health by the monster's damage
  player.reduceHealth(monster.getDamage());
  std::cout << "The " << monster.getName() << " hit you for " << monster.getDamage() << " damage.\n";
}

// This function handles the entire fight between a player and a randomly generated monster
void fightMonster(Player& player)
{
  // First randomly generate a monster
  Monster monster{ Monster::getRandomMonster() };
  std::cout << "You have encountered a " << monster.getName() << " (" << monster.getSymbol() << ").\n";

  // While the monster isn't dead and the player isn't dead, the fight continues
  while (!monster.isDead() && !player.isDead())
  {
    std::cout << "(R)un or (F)ight: ";
    char input{};
    std::cin >> input;
    if (input == 'R' || input == 'r')
    {
      // 50% chance of fleeing successfully
      if (getRandomNumber(1, 2) == 1)
      {
        std::cout << "You successfully fled.\n";
        return; // success ends the encounter
      }
      else
      {
        // Failure to flee gives the monster a free attack on the player
        std::cout << "You failed to flee.\n";
        attackPlayer(monster, player);
        continue;
      }
    }

    if (input == 'F' || input == 'f')
    {
      // Player attacks first, monster attacks second
      attackMonster(player, monster);
      attackPlayer(monster, player);
    }
  }
}

int main()
{
  std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock
  std::rand(); // get rid of first result

  std::cout << "Enter your name: ";
  std::string playerName;
  std::cin >> playerName;

  Player player{ playerName };
  std::cout << "Welcome, " << player.getName() << '\n';

  // If the player isn't dead and hasn't won yet, the game continues
  while (!player.isDead() && !player.hasWon())
    fightMonster(player);

  // At this point, the player is either dead or has won
  if (player.isDead())
  {
    std::cout << "You died at level " << player.getLevel() << " and with " << player.getGold() << " gold.\n";
    std::cout << "Too bad you can't take it with you!\n";
  }
  else
  {
    std::cout << "You won the game with " << player.getGold() << " gold!\n";
  }

  return 0;
}
