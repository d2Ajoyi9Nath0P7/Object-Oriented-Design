#include <bits/stdc++.h>
using namespace std;
#include <random>

class Player
{
public:
    string name;
    int position;
    int moves;
    
    Player(string name)
    {
        this->name = name;
        this->position = 0;
        this->moves = 0;
    }
    int rollDice()//c++ 11 version
    {
        return rand() % 6 + 1;
    }
    void move(int spaces)
    {
        position += spaces;
        moves++;
    }
};

class Board
{
public:
    int size;
    vector<int>playerPositions;
    vector<int>snakesPositions;
    vector<int>laddersPositions;
    Board(int s)
    {
        size = s;
    }
    void movePlayer(Player& p,int roll)
    {
        int newPosition = p.position + roll;
        if(newPosition > size)
        {
            return;
        }
        for(int i = 0 ; i < laddersPositions.size() ; i = i + 2)
        {
            if(newPosition == laddersPositions[i])
            {
                newPosition = laddersPositions[i+1];
                break;
            }
        }

        for(int i = 0 ; i < snakesPositions.size() ; i = i + 2)
        {
            if(newPosition == snakesPositions[i])
            {
                newPosition = snakesPositions[i+1];
                break;
            }
        }
        p.position = newPosition;
    }

    bool checkWinner(Player& p)
    {
        if(p.position == size)
        {
            cout<<"Congratulation "<<p.name<<" win the games!!!!! \n";
            return true;
        }

        return false;
    }
};

class Game
{
public:
    Board board;
    vector<Player>players;
    vector<pair<int,int>>snakes;
    vector<pair<int,int>>ladders;
    Game(int boardSize,vector<string>playerNames,vector<pair<int,int>>s,vector<pair<int,int>>l) : board(boardSize)
    {
        for(int i = 0 ; i < playerNames.size() ; i++)
        {
            players.push_back(Player(playerNames[i]));
        }
        snakes = s;
        ladders = l;

        initialBoard();
    }

    void initialBoard()
    {
        for(int i = 0 ; i < snakes.size() ; i++)
        {
            board.snakesPositions.push_back(snakes[i].first);
            board.snakesPositions.push_back(snakes[i].second);
        }

        for(int i = 0 ; i < ladders.size() ; i++)
        {
            board.laddersPositions.push_back(ladders[i].first);
            board.laddersPositions.push_back(ladders[i].second);
        }
    }

    void play()
    {
        while(true)
        {
            for(int i = 0 ; i < players.size() ; i++)
            {
                int roll = players[i].rollDice();
                cout<<players[i].name<<" rolled a "<<roll<<"\n";
                board.movePlayer(players[i],roll);

                cout<<players[i].name<<" is now positions : "<<players[i].position<<"\n\n";

                if(board.checkWinner(players[i]))
                {
                    return;
                }
            }
        }
    }
};

int main()
{
    vector<string> players = {"Player-1","Player-2"};

    vector<pair<int,int>>snakes = {{16,6},{47,26},{49,11},{98,3}};
    vector<pair<int,int>>ladders = {{12,56},{34,48},{67,89},{24,78}};

    srand(time(0));

    Game game(100,players,snakes,ladders);
    game.play();

    return 0;
}
