#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

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
    if (hand.size() < 5)
    {
        return false;
    }
    
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
    if (hand.size() < 5)
    {
        return false;
    }
    
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
    if (hand.size() == 3)
    {
        return false;
    }
    
    int count = 1;
    for(int i = 0; i < hand.size() - 1; i++)
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
    if (hand.size() < 5)
    {
        return false;
    }
    
    int count = 1;
    int pairCount = 0;
    for(int i = 0; i < hand.size() - 1; i++)
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
        if (hand[hand.size() - 1].num > high)
        {
            high = hand[hand.size() - 1].num;
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
    for(int i = 0; i < hand.size() - 1; i++)
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
        if (hand[hand.size() - 1].num > high)
        {
            high = hand[hand.size() - 1].num;
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
    if (hand.size() < 5)
    {
        return false;
    }
    
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

bool isFantasy(vector<Card>& hand)
{
    int dummy = 0;
    
    vector<Card> top;
    for (int i = 10; i < hand.size(); i++)
    {
        top.push_back(hand[i]);
    }

    sort(top.begin(), top.end(), pointer_less());
    int temp_top_str = hand_type(top, dummy);
    
    if (temp_top_str == 6)
    {
        return true;
    }
    else
    {
        vector<Card> bottom;
        for (int i = 0; i < 5; i++)
        {
            bottom.push_back(hand[i]);
        }

        sort(bottom.begin(), bottom.end(), pointer_less());
        int temp_bot_str = hand_type(bottom, dummy);
        
        if (temp_bot_str <= 2)
        {
            return true;
        }
    }
    
    return false;
}

// function to calculate royalties for a given hand
double calculateRoyalties(vector<Card>& hand, vector<double> b_points, vector<double> m_points) {
    // initialize royalties to 0
    double royalties = 0;
    
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

int combinations_top(vector<Card> iterable, vector<Card>& temp, int r, vector<Card>& bestHand, double& bestRoyalties, vector<double> b_points, vector<double> m_points, vector<Card>& bestFantasy, double& bestFantRoyal)
{
    int n = iterable.size();
    if (r > n)
    {
        return 3;
    }
    vector<int> indices(r);
    for(int i = 0; i < r; i++)
    {
        indices[i] = i;
    }

    for(int i = 0; i < r; i++)
    {
        temp[i + 10] = iterable[indices[i]];
    }
    double royalties = calculateRoyalties(temp, b_points, m_points);
    
    if (royalties >= 10 && royalties > bestFantRoyal)
    {
        if (isFantasy(temp))
        {
            bestFantasy = temp;
            bestFantRoyal = royalties;
        }
    }
    
    if (royalties == -1)
    {
        return 1;
    }
    else if (royalties == -2)
    {
        return 2;
    }
    else if (royalties > bestRoyalties)
    {
        bestHand = temp;
        bestRoyalties = royalties;
    }
    else if (royalties == bestRoyalties)
    {
        vector<Card> temp_top;
        for (int i = 10; i < temp.size(); i++)
        {
            temp_top.push_back(temp[i]);
        }
        vector<Card> best_top;
        for (int i = 10; i < bestHand.size(); i++)
        {
            best_top.push_back(bestHand[i]);
        }
        int temp_high = 0;
        int best_high = 0;
        
        sort(temp_top.begin(), temp_top.end(), pointer_less());
        sort(best_top.begin(), best_top.end(), pointer_less());
        
        int best_top_str = hand_type(best_top, best_high);
        int temp_top_str = hand_type(temp_top, temp_high);
        
        if (best_top_str == temp_top_str && best_top_str == 9)
        {
            for (int i = 0; i < best_top.size(); i++)
            {
                if (temp_top[i].num > best_top[i].num)
                {
                    bestHand = temp;
                    break;
                }
                else if (best_top[i].num > iterable[i].num)
                {
                    break;
                }
            }
        }
        else if (best_top_str == temp_top_str && best_top_str == 8)
        {
            if (temp_high == best_high)
            {
                for (int i = 0; i < temp_top.size(); i++)
                {
                    if (temp_top[i].num != best_high && bestHand[10].num != best_high && temp_top[i].num > bestHand[10].num)
                    {
                        bestHand = temp;
                        break;
                    }
                    else if (temp_top[i].num != best_high && bestHand[12].num != best_high && temp_top[i].num > bestHand[12].num)
                    {
                        bestHand = temp;
                        break;
                    }
                }
            }
        }
        
        vector<Card> temp_mid;
        for (int i = 5; i < 10; i++)
        {
            temp_mid.push_back(temp[i]);
        }
        vector<Card> best_mid;
        for (int i = 5; i < 10; i++)
        {
            best_mid.push_back(bestHand[i]);
        }
        temp_high = 0;
        best_high = 0;
        
        sort(temp_mid.begin(), temp_mid.end(), pointer_less());
        sort(best_mid.begin(), best_mid.end(), pointer_less());
        
        int best_mid_str = hand_type(best_mid, best_high);
        int temp_mid_str = hand_type(temp_mid, temp_high);
        
        if (best_mid_str == temp_mid_str && best_mid_str == 7)
        {
            if (temp_high > best_high)
            {
                bestHand = temp;
            }
        }
    }
    
    
    while(true)
    {
        int i = r - 1;
        for(; i >= 0; i--) {
            if (indices[i] != i + n - r) {
                break;
            }
        }
        if(i == -1)
        {
            return 3;
        }
        indices[i] += 1;
        for(int j = i + 1; j < r; j++)
        {
            indices[j] = indices[j-1] + 1;
        }
        for(int i = 0; i < r; i++)
        {
            temp[i + 10] = iterable[indices[i]];
        }
        
        royalties = calculateRoyalties(temp, b_points, m_points);
        
        if (royalties >= 10 && royalties > bestFantRoyal)
        {
            if (isFantasy(temp))
            {
                bestFantasy = temp;
                bestFantRoyal = royalties;
            }
        }
        
        if (royalties == -1)
        {
            return 1;
        }
        else if (royalties == -2)
        {
            return 2;
        }
        else if (royalties > bestRoyalties)
        {
            bestHand = temp;
            bestRoyalties = royalties;
        }
        else if (royalties == bestRoyalties)
        {
            vector<Card> temp_top;
            for (int i = 10; i < temp.size(); i++)
            {
                temp_top.push_back(temp[i]);
            }
            vector<Card> best_top;
            for (int i = 10; i < bestHand.size(); i++)
            {
                best_top.push_back(bestHand[i]);
            }
            int temp_high = 0;
            int best_high = 0;
            
            sort(temp_top.begin(), temp_top.end(), pointer_less());
            sort(best_top.begin(), best_top.end(), pointer_less());
            
            int best_top_str = hand_type(best_top, best_high);
            int temp_top_str = hand_type(temp_top, temp_high);

            if (best_top_str == temp_top_str && best_top_str == 9)
            {
                for (int i = 0; i < best_top.size(); i++)
                {
                    if (temp_top[i].num > best_top[i].num)
                    {
                        bestHand = temp;
                        break;
                    }
                    else if (best_top[i].num > iterable[i].num)
                    {
                        break;
                    }
                }
            }
            else if (best_top_str == temp_top_str && best_top_str == 8)
            {
                if (temp_high == best_high)
                {
                    for (int i = 0; i < temp_top.size(); i++)
                    {
                        if (temp_top[i].num != best_high && bestHand[10].num != best_high && temp_top[i].num > bestHand[10].num)
                        {
                            bestHand = temp;
                            break;
                        }
                        else if (temp_top[i].num != best_high && bestHand[12].num != best_high && temp_top[i].num > bestHand[12].num)
                        {
                            bestHand = temp;
                            break;
                        }
                    }
                }
            }
            
            vector<Card> temp_mid;
            for (int i = 5; i < 10; i++)
            {
                temp_mid.push_back(temp[i]);
            }
            vector<Card> best_mid;
            for (int i = 5; i < 10; i++)
            {
                best_mid.push_back(bestHand[i]);
            }
            temp_high = 0;
            best_high = 0;
            
            sort(temp_mid.begin(), temp_mid.end(), pointer_less());
            sort(best_mid.begin(), best_mid.end(), pointer_less());
            
            int best_mid_str = hand_type(best_mid, best_high);
            int temp_mid_str = hand_type(temp_mid, temp_high);
            
            if (best_mid_str == temp_mid_str && best_mid_str == 7)
            {
                if (temp_high > best_high)
                {
                    bestHand = temp;
                }
            }
        }
    }
}

void combinations_middle(vector<Card> iterable, vector<Card>& temp, int r, vector<Card>& bestHand, double& bestRoyalties, vector<double> b_points, vector<double> m_points, vector<Card>& bestFantasy, double& bestFantRoyal)
{
    int n = iterable.size();
    if (r > n) {
        return;
    }
    vector<int> indices(r);
    for(int i = 0; i < r; i++) {
        indices[i] = i;
    }

    for(int i = 0; i < r; i++)
    {
        temp[i + 5] = iterable[indices[i]];
    }
    
    bool check = false;
    vector<Card> iterable_2;
    for(int i = 0; i < iterable.size(); i++)
    {
        for (int j = 0; j < r; j++)
        {
            if (i == indices[j])
            {
                check = true;
                break;
            }
        }
        if (check)
        {
            check = false;
            continue;
        }
        iterable_2.push_back(iterable[i]);
    }
    
    if(combinations_top(iterable_2, temp, 3, bestHand, bestRoyalties, b_points, m_points, bestFantasy, bestFantRoyal) == 1)
    {
        return;
    }
    

    while(true)
    {
        int i = r - 1;
        for(; i >= 0; i--) {
            if (indices[i] != i + n - r) {
                break;
            }
        }
        if(i == -1) {
            return;
        }
        indices[i] += 1;
        for(int j = i + 1; j < r; j++) {
            indices[j] = indices[j-1] + 1;
        }
        
        for(int i = 0; i < r; i++)
        {
            temp[i + 5] = iterable[indices[i]];
        }
        
        bool check = false;
        iterable_2.clear();
        for(int i = 0; i < iterable.size(); i++)
        {
            for (int j = 0; j < r; j++)
            {
                if (i == indices[j])
                {
                    check = true;
                    break;
                }
            }
            if (check)
            {
                check = false;
                continue;
            }
            iterable_2.push_back(iterable[i]);
        }
        
        if(combinations_top(iterable_2, temp, 3, bestHand, bestRoyalties, b_points, m_points, bestFantasy, bestFantRoyal) == 1)
        {
            return;
        }
    }
}

void combinations_bottom(vector<Card> iterable, vector<Card>& temp, int r, vector<Card>& bestHand, double& bestRoyalties, vector<double> b_points, vector<double> m_points, vector<Card>& bestFantasy, double& bestFantRoyal)
{
    vector<vector<Card>> result;
    int n = iterable.size();
    if (r > n) {
        return;
    }
    vector<int> indices(r);
    for(int i = 0; i < r; i++) {
        indices[i] = i;
    }

    for(int i = 0; i < r; i++)
    {
        temp[i] = iterable[indices[i]];
    }
    
    bool check = false;
    vector<Card> iterable_2;
    for(int i = 0; i < iterable.size(); i++)
    {
        for (int j = 0; j < r; j++)
        {
            if (i == indices[j])
            {
                check = true;
                break;
            }
        }
        if (check)
        {
            check = false;
            continue;
        }
        iterable_2.push_back(iterable[i]);
    }
    
    combinations_middle(iterable_2, temp, 5, bestHand, bestRoyalties, b_points, m_points, bestFantasy, bestFantRoyal);

    while(true)
    {
        int i = r - 1;
        for(; i >= 0; i--) {
            if (indices[i] != i + n - r) {
                break;
            }
        }
        if(i == -1) {
            return;
        }
        indices[i] += 1;
        for(int j = i + 1; j < r; j++) {
            indices[j] = indices[j-1] + 1;
        }
        
        
        for(int i = 0; i < r; i++)
        {
            temp[i] = iterable[indices[i]];
        }
        
        bool check = false;
        iterable_2.clear();
        for(int i = 0; i < iterable.size(); i++)
        {
            for (int j = 0; j < r; j++)
            {
                if (i == indices[j])
                {
                    check = true;
                    break;
                }
            }
            if (check)
            {
                check = false;
                continue;
            }
            iterable_2.push_back(iterable[i]);
        }
        
        combinations_middle(iterable_2, temp, 5, bestHand, bestRoyalties, b_points, m_points, bestFantasy, bestFantRoyal);
    }
}



int main() {
    // create vector of cards (usually don't initialize this is just for testing)
    //vector<Card> card_set = {Card(14, 'H'), Card(14, 'C'), Card(13, 'H'), Card(13, 'C'), Card(12, 'S'), Card(12, 'C'), Card(10, 'S'), Card(10, 'C'), Card(9, 'S'), Card(9, 'C'), Card(8, 'D'), Card(6, 'C'), Card(4, 'S'), Card(2, 'H')};
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
    vector<Card> bestHand(13);
    double bestRoyalties = -1;
    vector<Card> current(13);
    vector<Card> bestFantasy(13);
    double bestFantRoyal = -1;
    //create vectors for the amount of points per row
    vector<double> b_points;
    vector<double> m_points;
    
    b_points.push_back(25);
    b_points.push_back(15);
    b_points.push_back(10);
    b_points.push_back(6);
    b_points.push_back(4);
    b_points.push_back(2);
    for (double i = 4; i >= 0; i--)
    {
        b_points.push_back(i/20);
    }
    
    m_points.push_back(50);
    m_points.push_back(30);
    m_points.push_back(20);
    m_points.push_back(12);
    m_points.push_back(8);
    m_points.push_back(4);
    m_points.push_back(2);
    for (double i = 3; i >= 0; i--)
    {
        m_points.push_back(i/20);
    }
    
    combinations_bottom(card_set, current, 5, bestHand, bestRoyalties, b_points, m_points, bestFantasy, bestFantRoyal);
    
    bestRoyalties = floor(bestRoyalties);
    bestFantRoyal = floor(bestFantRoyal);
    
    // add if statement for if bestFantRoyal != -1 then ask which hand they want
    if (bestFantRoyal != -1 && bestFantRoyal != bestRoyalties)
    {
        cout << "Would you like the hand with the best royalties (royalties: " << bestRoyalties << ") or the hand to keep you in fantasy (royalties: " << bestFantRoyal << ") or both? (r/f/b): ";
        cin >> y_n;
        
        if (y_n == 'r')
        {
            for (int i = bestHand.size() - 1; i >= 0; i--)
            {
                cout << bestHand[i].num << bestHand[i].suit << " ";
                if (i == 10 || i == 5)
                {
                    cout << endl;
                }
            }
            
            cout << endl << "Amount of Royalties: " << floor(bestRoyalties) << endl;
        }
        else if (y_n == 'f')
        {
            for (int i = bestFantasy.size() - 1; i >= 0; i--)
            {
                cout << bestFantasy[i].num << bestFantasy[i].suit << " ";
                if (i == 10 || i == 5)
                {
                    cout << endl;
                }
            }
            
            cout << endl << "Amount of Royalties: " << floor(bestFantRoyal) << endl;
        }
        else
        {
            cout << "Best Hand:" << endl;
            for (int i = bestHand.size() - 1; i >= 0; i--)
            {
                cout << bestHand[i].num << bestHand[i].suit << " ";
                if (i == 10 || i == 5)
                {
                    cout << endl;
                }
            }
            
            cout << endl << "Amount of Royalties: " << floor(bestRoyalties) << endl;
            
            cout << "Fantasy Land Hand:" << endl;
            for (int i = bestFantasy.size() - 1; i >= 0; i--)
            {
                cout << bestFantasy[i].num << bestFantasy[i].suit << " ";
                if (i == 10 || i == 5)
                {
                    cout << endl;
                }
            }
            
            cout << endl << "Amount of Royalties: " << floor(bestFantRoyal) << endl;
        }
    }
    else
    {
        for (int i = bestHand.size() - 1; i >= 0; i--)
        {
            cout << bestHand[i].num << bestHand[i].suit << " ";
            if (i == 10 || i == 5)
            {
                cout << endl;
            }
        }
        
        cout << endl << "Amount of Royalties: " << bestRoyalties << endl;
    }
    
    return 0;
}
