#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <exception>
#include <stdexcept>

using namespace std;

#define MAX_NAME 32
#define MAX_HEALTH 1000
#define MAX_POWER 500

/**
 * @class GameCharacter
 * @brief Represents a character in a game with attributes such as name, health, and attack power.
 * 
 * This class manages a game character's attributes and ensures validation of values. 
 * Each character instance is assigned a unique ID, and the total count of active objects is tracked.
 * 
 * Made by: Aleksandra Nikitkova
 */
class GameCharacter {
public:
    string name;
    int health;
    int attackPower;

    int id;
    
    static int uniqueId;
    static int ObjectCount;

    /**
     * @brief Constructor to initialize a character with default attributes.
     * 
     * The name set to "Name", health is set to -1 (invincible), and the attack power is set to 0.
     */
    GameCharacter() {
        init("Name", -1, 0);
    }

    /**
     * @brief Constructor to initialize a character with a name, health, and attack power.
     * 
     * @param name The name of the character.
     * @param health The health points of the character (positive value or -1 for invincible).
     * @param attackPower The attack power of the character.
     * @throw std::invalid_argument If name, health, or attack power is invalid.
     */
    GameCharacter(string name, int health, int attackPower) {
        init(name, health, attackPower);
    }

    /**
     * @brief Destructor to decrement the object count when a character is deleted.
     */
    ~GameCharacter() {
        --ObjectCount;
    }

    /**
     * @brief Sets the character's name with validation.
     * 
     * The name must start with a capital letter, contain only alphabetic characters and spaces,
     * and must not end with a space.
     * 
     * @param characterName The new name for the character.
     * @throw std::invalid_argument If the name is invalid.
     */
    void setName(string characterName) {
        validateName(characterName);
        name = characterName;
    }

    /**
     * @brief Gets the character's name.
     * @return The character's name as a string.
     */
    string getName() {
        return name;
    }

    /**
     * @brief Gets the character's health points.
     * @return The health points of the character.
     */
    int getHealth() {
        return health;
    }

    /**
     * @brief Gets the character's attack power.
     * @return The attack power of the character.
     */
    int getAttackPower() {
        return attackPower;
    }

    /**
     * @brief Gets the unique ID of the character.
     * @return The unique ID of the character.
     */
    int getPersonalId() {
        return id;
    }

    /**
     * @brief Converts character attributes to a formatted string representation.
     * @return A string containing the character's name, health, and attack power.
     */
    string toString() {
        stringstream ss;
        ss << name << " " << health << " " << attackPower;
        return ss.str();
    }

    /**
     * @brief Gets the number of active GameCharacter objects.
     * @return The count of existing GameCharacter instances.
     */
    static int getObjectCount() {
        return ObjectCount;
    }

    /**
     * @brief Gets the total number of characters created.
     * @return The total number of character instances ever created.
     */
    static int getIdCount() {
        return uniqueId;
    }

private:
    /**
     * @brief Initializes the GameCharacter object with the provided attributes.
     * 
     * This method sets the character's name, health, and attack power while also
     * assigning a unique ID and increasing the object count.
     * 
     * @param name The name of the character.
     * @param health The health points of the character.
     * @param attackPower The attack power of the character.
     */
    void init(string name, int health, int attackPower) {
        setName(name);
        setHealth(health);
        setAttackPower(attackPower);
        id = uniqueId++;
        ++ObjectCount;
    }

    /**
     * @brief Sets the character's health with validation.
     * 
     * The health must be a positive integer or -1 for invincibility.
     * 
     * @param characterHealth The health value to set.
     * @throw std::invalid_argument If the health value is out of bounds.
     */
    void setHealth(int characterHealth) {
        validateHealth(characterHealth);
        health = characterHealth;
    }

    /**
     * @brief Sets the character's attack power with validation.
     * 
     * @param characterAttackPower The attack power value to set.
     * @throw std::invalid_argument If the attack power exceeds the allowed limit.
     */
    void setAttackPower(int characterAttackPower) {
        validateAttackPower(characterAttackPower);
        attackPower = characterAttackPower;
    }

    /**
     * @brief Validates and sets the health of the character.
     * 
     * Ensures that the health value is either a positive integer or -1 for invincibility.
     * Throws an exception if the value exceeds the maximum limit.
     * 
     * @param characterHealth The health value to set.
     * @throw std::invalid_argument If the health value is invalid.
     */
    void validateHealth(int characterHealth) {
        if (characterHealth <= 0 && characterHealth != -1) {
            throw invalid_argument("Health must be positive or -1 for invincible character.");
        }
        if (characterHealth > MAX_HEALTH) {
            throw invalid_argument("Health cannot exceed " + to_string(MAX_HEALTH) + ".");
        }
    }

    /**
     * @brief Validates and sets the attack power of the character.
     * 
     * Ensures the attack power does not exceed the predefined maximum limit.
     * Throws an exception if the attack power is too high.
     * 
     * @param characterAttackPower The attack power value to set.
     * @throw std::invalid_argument If the attack power exceeds the allowed limit.
     */
    void validateAttackPower(int characterAttackPower) {
        if (characterAttackPower > MAX_POWER) {
            throw invalid_argument("Attack power cannot exceed " + to_string(MAX_POWER) + ".");
        }
    }

    /**
     * @brief Validates and sets the character's name.
     * 
     * The name must start with a capital letter, contain only alphabetic characters and spaces,
     * and must not end with a space. It also ensures no consecutive spaces appear in the name.
     * 
     * @param characterName The new name for the character.
     * @throw std::invalid_argument If the name does not meet the validation criteria.
     */
    void validateName(string characterName) {
        if (characterName == "") {
            throw invalid_argument("Character name cannot be empty.");
        }
        if (characterName[0] < 'A' || characterName[0] > 'Z') {
            throw invalid_argument("Name must start with an uppercase letter.");
        }
        if(characterName.length() > MAX_NAME) {
            throw invalid_argument("Name length cannot exceed " + to_string(MAX_NAME) + " characters.");
        }
        bool space = false;
        for (int i = 0; i < characterName.length(); ++i) {
            if (characterName[i] == ' ' && characterName[i+1] == '\0') {
                throw invalid_argument("Invalid character name. Last character cannot be space.");
            }
            if ((characterName[i] < 'A' || characterName[i] > 'Z') && (characterName[i] < 'a' || characterName[i] > 'z')) {
                if (characterName[i] == ' ' && !space) {
                    space = true;
                    continue;
                } else if (space) {
                    throw invalid_argument("Invalid character name. It should not contain spaces following another space.");
                }
                throw invalid_argument("Name must contain only alphabetic characters and spaces.");
            }
            space = false;
        }
    }
};

int GameCharacter::uniqueId = 0;
int GameCharacter::ObjectCount = 0;

int main() {
    try {
        assert(GameCharacter::getObjectCount() == 0);

        GameCharacter *npc[3];

        npc[0] = new GameCharacter("Leonardo da Vinci", 1000, 20);

        assert(npc[0]->toString() == "Leonardo da Vinci 1000 20");
        assert(GameCharacter::getObjectCount() == 1);

        assert(npc[0]->getPersonalId() == 0);
        assert(npc[0]->getName() == "Leonardo da Vinci");
        assert(npc[0]->getHealth() == 1000);
        assert(npc[0]->getAttackPower() == 20);
    
        npc[1] = new GameCharacter();

        assert(npc[1]->toString() == "Name -1 0");
        assert(GameCharacter::getObjectCount() == 2);
        assert(GameCharacter::getIdCount() == 2);
    
        assert(npc[1]->getPersonalId() == 1);
        assert(npc[1]->getName() == "Name");
        assert(npc[1]->getHealth() == -1);
        assert(npc[1]->getAttackPower() == 0);

        npc[1]->setName("B");
        assert(npc[1]->getName() == "B");

        npc[2] = new GameCharacter("Jack", 10, 30);

        assert(GameCharacter::getObjectCount() == 3);
        assert(GameCharacter::getIdCount() == 3);
    
        assert(npc[2]->getPersonalId() == 2);
        assert(npc[2]->getName() == "Jack");
        assert(npc[2]->getHealth() == 10);
        assert(npc[2]->getAttackPower() == 30);


        for (int i = 0; i < 3; ++i) {
            delete npc[i];

        }
        assert(GameCharacter::getObjectCount() == 0);
        assert(GameCharacter::getIdCount() == 3);

    }
    catch (invalid_argument e) {
        cout << e.what() << endl;
    }
    catch (exception e) {
        cout << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown error." << endl;
    }
}
