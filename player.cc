#include "player.h"
#include "exceptions.h"

Player::Player() {
    name = "DEFAULT PLAYER";
    id = 0;
}

// Player::Player(string name, int id) : name{name}, id{id} {}

Player::~Player() {}

void Player::init(string name, int id, ifstream& deckIn) {
    this->name = name;
    this->id = id;
    deck.init(deckIn);
    hand.init(deck);
}

void Player::TEST_printPlayerDeck() {
    cout << "Player " << id << " " << name << "'s Deck: " << endl;
    deck.TEST_printDeck();
    cout << endl;
}

void Player::TEST_printPlayerHand() {
    cout << "Player " << id << " " << name << "'s Hand: " << endl;
    hand.TEST_printHand();
    cout << endl;
}

void Player::TEST_printPlayerBoard() {
    cout << "Player " << id << " " << name << "'s Board: " << endl;
    board.TEST_printBoard();
    cout << endl;
}

void Player::TEST_printPlayerRitual() {
    cout << "Player " << id << " " << name << "'s Ritual: " << endl;
    ritual->printRitual();
    cout << endl;
}

string Player::getName() const {return name;}
int Player::getId() const {return id;}
int Player::getLife() const {return life;}
int Player::getMagic() const {return magic;}

Hand& Player::getHand() {return hand;}
Board& Player::getBoard() {return board;}
RitualPtr Player::getRitual() {return ritual;}


void Player::setLife(int n) {life = n;}
void Player::setMagic(int n) {magic = n;}
void Player::increaseMagic(int n) {magic += n;}
void Player::decreaseLife(int n) {
    life -= n;

    // checks if player is still alive
    if (life <= 0) cout << this->getName() << " is dead D:" << endl; 
    // we should throw an exception here
}

CardPtr Player::drawCard() {
    CardPtr c = deck.drawCard();
    hand.addCard(c);
    return c;
}

void Player::play(int i) {
    CardPtr cardToPlay = hand.getCard(i);

    // check if the card can be played without target
    if (cardToPlay->getNeedTarget() == true) throw no_target_provided(*cardToPlay);
    
    // check if player has enough magic to play the card
    int cost = cardToPlay->getCost();
    if (cost > magic) throw not_enough_magic(*this);

    magic -= cost;

    if (cardToPlay->getType() == CardType::Minion) {
        MinionPtr minionToPlay = dynamic_pointer_cast<Minion>(cardToPlay); // fails if cardToPlay is not MinionPtr type
        board.addCard(minionToPlay);
    } else if (cardToPlay->getType() == CardType::Ritual) {
        RitualPtr ritualToPlay = dynamic_pointer_cast<Ritual>(cardToPlay);
        // cout << "this is not a minion" << endl;
        ritual = ritualToPlay;
    } else if (cardToPlay->getType() == CardType::Spell) {
        SpellPtr spellToPlay = dynamic_pointer_cast<Spell>(cardToPlay);
        spellToPlay->applyAbility(*this);
    }
}

void Player::play(int i, int j, Player& p) {
    CardPtr cardToPlay = hand.getCard(i);
    CardPtr targetCard = p.getBoard().getCard(j);

    // check if the card needs a target to be played
    if (cardToPlay->getNeedTarget() == false) throw no_target_needed(*cardToPlay);

    // check if player has enough magic to play the card
    int cost = cardToPlay->getCost();
    if (cost > magic) throw not_enough_magic(*this);

    magic -= cost;
    
    if(cardToPlay->getType() ==   CardType::Enchantment && targetCard->getType() == CardType::Spell)
    {
        EnchantmentPtr enchantCard = dynamic_pointer_cast<Enchantment>(cardToPlay);
        MinionPtr targetMinion = dynamic_pointer_cast<Minion>(targetCard);         
            // place enchantment decorator on the Minion card, converting from enchantment's Card to its Decorator version
        p.getBoard().enchantMinion(j, enchantCard->getName());
        
    }
    else if (cardToPlay->getType() == CardType::Spell) { // spell with target
        // do something
    }
}

