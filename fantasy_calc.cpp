#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Card {
public:
    Card(int num_, char suit_);
    Card();
    int num;
    char suit;
    bool operator==(const Card& card_2) const
    {
        if (this->num == card_2.num && this->suit == card_2.suit)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

struct pointer_less
{
    bool operator()( Card const lhs, Card const rhs ) const
        {
            return lhs.num < rhs.num;
        }
};

Card::Card()
{
    num = 0;
    suit = 'S';
}

Card::Card(int num_, char suit_)
{
    num = num_;
    suit = suit_;
}


//Check if the hand is a flush
bool isFlush(vector<Card>& hand)
{
    if (hand.size() < 5)
    {
        return false;
    }
    
    for (int i = 0; i < hand.size() - 1; i++)
    {
        if (hand[i].suit != hand[i + 1].suit)
        {
            return false;
        }
    }
    
    return true;
}

//Check if the hand is a straight
bool isStraight(vector<Card>& hand)
{
    if (hand.size() < 5)
    {
        return false;
    }
    
    if (hand[4].num == 14)
    {
        // Come in here if we have an ace because it can be high or low
        bool ace_high = true;
        bool ace_low = true;
        for (int i = 0; i < hand.size() - 1; i++)
        {
            if (hand[i].num != hand[i + 1].num - 1)
            {
                 ace_high = false;
            }
        }
        
        rotate(hand.rbegin(), hand.rbegin() + 1, hand.rend());
        for (int i = 0; i < hand.size() - 1; i++)
        {
            if ((hand[i].num % 13) != hand[i + 1].num - 1)
            {
                 ace_low = false;
            }
        }
        
        if (ace_high || ace_low)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        for (int i = 0; i < hand.size() - 1; i++)
        {
            if (hand[i].num != hand[i + 1].num - 1)
            {
                return false;
            }
        }
    }
    
    
    
    return true;
}

//Check if the hand is a royal flush
bool isRoyal(vector<Card>& hand)
{
    if (hand[4].num == 14 && hand[3].num == 13 && isFlush(hand) && isStraight(hand))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Check if the hand is a straight flush
bool isStraightFlush(vector<Card>& hand)
{
    if (isFlush(hand) && isStraight(hand))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Check if the hand is quads
bool isQuads(vector<Card>& hand, int& high)
{
    int count = 1;
    for(int i = 0; i < hand.size(); i++)
    {
        if (hand[i].num == hand[i + 1].num)
        {
            count += 1;
            if (count == 4)
            {
                high = hand[i].num;
                return true;
            }
        }
        else
        {
            count = 1;
        }
    }
    
    return false;
}

//Check if the hand is trips
bool isTrips(vector<Card>& hand, int& high)
{
    int count = 1;
    for(int i = 0; i < hand.size(); i++)
    {
        if (hand[i].num == hand[i + 1].num)
        {
            count += 1;
            if (count == 3)
            {
                high = hand[i].num;
                return true;
            }
        }
        else
        {
            count = 1;
        }
    }
    
    return false;
}

// Check if the hand is 2 pair
bool isTwoPair(vector<Card>& hand, int& high)
{
    int count = 1;
    int pairCount = 0;
    for(int i = 0; i < hand.size(); i++)
    {
        if (hand[i].num == hand[i + 1].num)
        {
            count += 1;
        }
        else
        {
            if (count == 2)
            {
                pairCount += 1;
                if (hand[i - 1].num > high)
                {
                    high = hand[i - 1].num;
                }
            }
            count = 1;
        }
    }
    
    if (count == 2)
    {
        pairCount += 1;
        if (hand[5].num > high)
        {
            high = hand[5].num;
        }
    }
    
    if (pairCount == 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Check if the hand has a pair
bool isPair(vector<Card>& hand, int& high)
{
    int count = 1;
    int pairCount = 0;
    for(int i = 0; i < hand.size(); i++)
    {
        if (hand[i].num == hand[i + 1].num)
        {
            count += 1;
        }
        else
        {
            if (count == 2)
            {
                pairCount += 1;
                if (hand[i - 1].num > high)
                {
                    high = hand[i - 1].num;
                }
            }
            count = 1;
        }
    }
    
    if (count == 2)
    {
        pairCount += 1;
        if (hand[5].num > high)
        {
            high = hand[5].num;
        }
    }
    
    if (pairCount == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Check if the hand is a full house
bool isFull(vector<Card>& hand, int& high)
{
    if (isPair(hand, high) && isTrips(hand, high))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Check all hand types from best to worst to see what the hand is
int hand_type(vector<Card>& hand, int& high)
{
    if (isRoyal(hand))
    {
        return 0;
    }
    else if (isStraightFlush(hand))
    {
        return 1;
    }
    else if (isQuads(hand, high))
    {
        return 2;
    }
    else if (isFull(hand, high))
    {
        return 3;
    }
    else if (isFlush(hand))
    {
        return 4;
    }
    else if (isStraight(hand))
    {
        return 5;
    }
    else if (isTrips(hand, high))
    {
        return 6;
    }
    else if (isTwoPair(hand, high))
    {
        return 7;
    }
    else if (isPair(hand, high))
    {
        return 8;
    }
    else
    {
        return 9;
    }
}

// function to calculate royalties for a given hand
int calculateRoyalties(vector<Card>& hand, vector<int> b_points, vector<int> m_points) {
    // initialize royalties to 0
    int royalties = 0;
    
    vector<Card> bottom;
    vector<Card> middle;
    vector<Card> top;
    
    
    for (int i = 0; i < 5; i++)
    {
        bottom.push_back(hand[i]);
        middle.push_back(hand[i + 5]);
        if (i < 3)
        {
            top.push_back(hand[i + 10]);
        }
    }
    
    int b_high = 0;
    int m_high = 0;
    
    sort(bottom.begin(), bottom.end(), pointer_less());
    sort(middle.begin(), middle.end(), pointer_less());
    int b_strength = hand_type(bottom, b_high);
    int m_strength = hand_type(middle, m_high);
    
    
    if (b_strength < m_strength)
    {
        // If the bottom strength is better than the middle then we just add their royalties
        royalties += b_points[b_strength];
        royalties += m_points[m_strength];
    }
    else if (b_strength > m_strength)
    {
        // If the middle strength is better than the bottom we crack so we return -1
        return -1;
    }
    else
    {
        //If we are in here then the strengths are equal and we need to check which set has higher cards
        if (b_strength == 0)
        {
            //If b_strength is 0 then both bottom and middle are royals so we just add their royalties
            royalties += b_points[b_strength];
            royalties += m_points[m_strength];
        }
        else if (b_strength == 1 || b_strength == 4 || b_strength == 5 || b_strength == 9)
        {
            //If the hand is a straight flush, flush, straight, or high card we have to check the cards for the highest one
            for (int i = 0; i < bottom.size(); i++)
            {
                if (bottom[i].num > middle[i].num)
                {
                    royalties += b_points[b_strength];
                    royalties += m_points[m_strength];
                    break;
                }
                else if (bottom[i].num == middle[i].num)
                {
                    continue;
                }
                else
                {
                    return -1;
                }
            }
            if (royalties == 0)
            {
                // If we went through the whole loop without adding to royalties then we have the same hand and can add the royalties for both
                royalties += b_points[b_strength];
                royalties += m_points[m_strength];
            }
        }
        else
        {
            // We have quads, full, trips, two pair, or pair so we just check which has the highest card in the set (aka which is the higher number for quads, full, trips, two pair, or pair
            if (b_high < m_high)
            {
                return -1;
            }
            else
            {
                royalties += b_points[b_strength];
                royalties += m_points[m_strength];
            }
        }
    }
    
    //To check the middle vs the top hand
    int t_high = 0;
    sort(top.begin(), top.end(), pointer_less());
    int t_strength = hand_type(top, t_high);
    
    if (m_strength < t_strength)
    {
        // If the middle strength is better than the top we just add the royalties
        if (t_strength == 6)
        {
            royalties += t_high + 8;
        }
        else if (t_strength == 8)
        {
            if (t_high >= 6)
            {
                royalties += t_high - 5;
            }
        }
    }
    else if (m_strength > t_strength)
    {
        // If the top stength is better than the middle we crack
        return -2;
    }
    else
    {
        // We have the same strength hand so we have to check which has higher card
        if (t_strength == 8)
        {
            // This means we have a pair in the middle and top so we check which is greater
            if (m_high > t_high)
            {
                if (t_high >= 6)
                {
                    royalties += t_high - 5;
                }
            }
            else if (m_high == t_high)
            {
                // If the pairs equal eachother then we check the last card to see which hand is better
                if (top[2].num > middle[2].num)
                {
                    return -2;
                }
                else
                {
                    if (t_high >= 6)
                    {
                        royalties += t_high - 5;
                    }
                }
            }
            else
            {
                return -2;
            }
        }
        else if (t_strength == 6)
        {
            // This means we have trips so we check which is higher
            if (m_high > t_high)
            {
                royalties += t_high + 8;
            }
            else
            {
                return -2;
            }
        }
        else
        {
            // This means we have high card in both rows so we check the cards to see if we crack
            for (int i = 0; i < top.size(); i++)
            {
                if (middle[i].num > top[i].num)
                {
                    break;
                }
                else if (middle[i].num == top[i].num)
                {
                    continue;
                }
                else
                {
                    return -2;
                }
            }
        }
    }
    
    return royalties;
}

// function to generate all possible combinations of cards
void generateCombinations(vector<Card>& cards, vector<Card>& combination, vector<Card>& bestHand, int& bestRoyalties, vector<int> b_points, vector<int> m_points, int& count, vector<vector<Card>>& seen) {
    // base case: combination size is 13
    if (combination.size() == 13) {
        // calculate royalties for combination
        int royalties = calculateRoyalties(combination, b_points, m_points);
        
        if (royalties == -1)
        {
            count = 8;
        }
        else if (royalties == -2)
        {
            count = 3;
        }
        // check if royalties are better than current best
        if (royalties > bestRoyalties)
        {
            bestRoyalties = royalties;
            bestHand = combination;
        }
        return;
    }
    
    // iterate through all remaining cards
    for (int i = 0; i < cards.size(); i++)
    {
        if (count > 0)
        {
            count--;
            return;
        }
        // check if card is already in combination
        if (find(combination.begin(), combination.end(), cards[i]) != combination.end())
        {
            continue;
        }
        // add current card to combination
        combination.push_back(cards[i]);
        // generate combinations with remaining cards
       if (combination.size() == 5)
       {
            vector<Card> copy(5);
            partial_sort_copy(begin(combination), end(combination), begin(copy), end(copy), pointer_less());
            
            if (find(seen.begin(), seen.end(), copy) != seen.end())
            {
                combination.pop_back();
            }
            else
            {
                seen.push_back(copy);
                generateCombinations(cards, combination, bestHand, bestRoyalties, b_points, m_points, count, seen);
                // remove current card from combination
                combination.pop_back();
            }
        }
        else
        {
            generateCombinations(cards, combination, bestHand, bestRoyalties, b_points, m_points, count, seen);
            // remove current card from combination
            combination.pop_back();
        }
    }
}

int main() {
    // create vector of cards (usually don't initialize this is just for testing)
    //vector<Card> card_set = {Card(2, 'S'), Card(13, 'S'), Card(14, 'S'), Card(10, 'S'), Card(8, 'S'), Card(11, 'S'), Card(8, 'D'), Card(8, 'C'), Card(4, 'S'), Card(10, 'C'), Card(13, 'C'), Card(13, 'H'), Card(3, 'S'), Card(5, 'S')};
    vector<Card> card_set;
    int num = 0;
    char suit;
    // Uncomment to put your own cards in
    
    bool again = true;
    char y_n;
    bool valid_input = false;
    for (int i = 0; i < 14; i++)
    {
        again = true;
        cout << "Enter card " << i + 1 << "'s number (J = 11, Q = 12, K = 13, A = 14): ";
        cin >> num;
        if (!(valid_input = cin.good()))
        {
            cout << "That input is invalid, enter a number!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            num = 1000;
        }
        else
        {
            cout << "Enter card " << i + 1 << "'s suit (D, S, H, C): ";
            cin >> suit;
        }
        while (again)
        {
            if ((suit != 'D' && suit != 'S' && suit != 'H' && suit != 'C') || num < 2 || num > 14 || find(card_set.begin(), card_set.end(), Card(num, suit)) != card_set.end())
            {
                if (valid_input)
                {
                    cout << "Invalid Card!" << endl;
                }
                cout << "Want to enter card again or quit (y/n)? ";
                cin >> y_n;
                if (y_n == 'y' || y_n == 'Y')
                {
                    cout << "Current hand: ";
                    for (int j = 0; j < card_set.size(); j++)
                    {
                        cout << card_set[j].num << card_set[j].suit << " ";
                    }
                    cout << endl << "Enter card " << i + 1 << "'s number (J = 11, Q = 12, K = 13, A = 14): ";
                    cin >> num;
                    if (!(valid_input = cin.good()))
                    {
                        cout << "That input is invalid!" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        num = 1000;
                        continue;
                    }
                    cout << "Enter card " << i + 1 << "'s suit (D, S, H, C): ";
                    cin >> suit;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                again = false;
            }
        }
        card_set.push_back(Card(num, suit));
    }
    
    
    //create vectors for the amount of points per row
    vector<int> b_points;
    vector<int> m_points;
    
    b_points.push_back(25);
    b_points.push_back(15);
    b_points.push_back(10);
    b_points.push_back(6);
    b_points.push_back(4);
    b_points.push_back(2);
    for (int i = 0; i < 5; i++)
    {
        b_points.push_back(0);
    }
    
    m_points.push_back(50);
    m_points.push_back(30);
    m_points.push_back(20);
    m_points.push_back(12);
    m_points.push_back(8);
    m_points.push_back(4);
    m_points.push_back(2);
    for (int i = 0; i < 4; i++)
    {
        m_points.push_back(0);
    }
    
    // create vector to store best hand and royalties
    vector<Card> bestHand;
    int bestRoyalties = 0;
    // generate all combinations of cards and calculate royalties
    int count = 0;
    vector<Card> current;
    vector<vector<Card>> seen;
    generateCombinations(card_set, current, bestHand, bestRoyalties, b_points, m_points, count, seen);
    
    for (int i = bestHand.size() - 1; i >= 0; i--)
    {
        cout << bestHand[i].num << bestHand[i].suit << " ";
        if (i == 10 || i == 5)
        {
            cout << endl;
        }
    }
    
    cout << endl << "Amount of Royalties: " << bestRoyalties << endl;
    
    return 0;
}
