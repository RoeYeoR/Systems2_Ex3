#ifndef DEVELOPMENT_CARD_HPP
#define DEVELOPMENT_CARD_HPP

// Enum class for different types of development cards
enum class DevelopmentCardType {
    Promotion,
    VictoryPoint,
    Knight
};



class DevelopmentCard {
    
    public:
    virtual ~DevelopmentCard() {}
    virtual void use() = 0;
};

#endif // DEVELOPMENT_CARD_HPP
