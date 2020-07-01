#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <thread>
#include <windows.h>
#include <stdlib.h>     
#include <time.h> 

typedef unsigned int uint;
using namespace std;
enum SIZEP { SMALL, MEDIUM, BIG };
enum TYPE { FIRE, WATER, GROUND, ELECTRIC};
enum ACTION { One, Two, Three, Four, Five };
vector<string> pokenames;
vector<string> hum_names;
//enum PBALLS { POKEBALL, GREATBALL, ULTRABALL};
//enum TERRAIN {SEA, VOLCANO, FOREST};

SIZEP IntToSIZEP(uint num)
{
    switch (num)
    {
    case 0:
        return SMALL;
    case 1:
        return MEDIUM;
    case 2:
        return BIG;
    }
}

TYPE IntToTYPE(uint num)
{
    switch (num)
    {
    case 0:
        return FIRE;
    case 1:
        return WATER;
    case 2:
        return GROUND;
    case 3:
        return ELECTRIC;
    }
}

class Pokemon
{
public:
    string name;
    SIZEP size;
    TYPE type;   
    uint hp;
    uint ap;

    string GetName()
    {
        return name;
    }

};

class BuilderPokemon
{
protected:
    string Bname;
    SIZEP Bsize;
    TYPE Btype;
    uint Bhp;
    uint Bap;
private:
    virtual void setType() = 0;
    virtual void setSize() = 0;
    virtual void setHpAp() = 0;
    virtual void setName()
    {
        if (pokenames.size() == 0)
        {
            Bname = "Default";
        }
        else
        {
            Bname = pokenames[rand() % pokenames.size()];            // TODO
        }
    }
    
    virtual Pokemon* GetPokemon() = 0;

    friend class Pokemons;
};

class BuilderSmallPokemon : public BuilderPokemon
{
    void setType()
    {
        Btype = IntToTYPE((rand() % 5) + 1);
    }
    void setSize()
    {
        Bsize = SMALL;
    }
    void setHpAp()
    {
        uint choose = rand();
        Bhp = ((choose % 100) + 1);
        choose = (choose % 10) + 1;
        Bap = (choose * 3);
    }

    Pokemon* GetPokemon()
    {
        Pokemon* res = new Pokemon;
        res->size = Bsize;
        res->hp = Bhp;
        res->ap = Bap;
        res->type = Btype;
        res->name = Bname;

        return res;
    }
};

class BuilderMediumPokemon : public BuilderPokemon
{
    void setType()
    {
        Btype = IntToTYPE((rand() % 5) + 1);
    }
    void setSize()
    {
        Bsize = MEDIUM;
    }
    void setHpAp()
    {
        uint choose = rand();
        Bhp = ((choose % 100) + 1) / 2;
        choose = (choose % 10) + 1;
        Bap = (choose * 3) / 2;
    }

    Pokemon* GetPokemon()
    {
        Pokemon* res = new Pokemon;
        res->size = Bsize;
        res->hp = Bhp;
        res->ap = Bap;
        res->type = Btype;
        res->name = Bname;

        return res;
    }
};

class BuilderBigPokemon : public BuilderPokemon
{
    void setType()
    {
        Btype = IntToTYPE((rand() % 5) + 1);
    }
    void setSize()
    {
        Bsize = BIG;
    }
    void setHpAp()
    {
        uint choose = rand();
        Bhp = ((choose % 100) + 1) / 3;
        choose = (choose % 10) + 1;
        Bap = (choose * 3) / 3;
    }

    Pokemon* GetPokemon()
    {
        Pokemon* res = new Pokemon;
        res->size = Bsize;
        res->hp = Bhp;
        res->ap = Bap;
        res->type = Btype;
        res->name = Bname;

        return res;
    }
};

class Pokemons
{
    BuilderPokemon* builder;
public:

    Pokemon* CreateRandomPokemon()
    {
        srand(time(NULL));
        uint coef = (rand() % 3) + 1;

        switch (coef)
        {
        case 1:
            builder = new BuilderSmallPokemon;
            break;
        case 2:
            builder = new BuilderMediumPokemon;
            break;
        case 3:
            builder = new BuilderBigPokemon;
            break;
        }

        builder->setSize();
        builder->setHpAp();
        builder->setType();
        builder->setName();
        
        return builder->GetPokemon();
    }
};

class PokemonTrainer
{
    string name;
    uint pokeballs;
    vector<Pokemon*> pokemons;

    bool CatchPokemon(Pokemon *pok)
    {
        if (pokeballs == 0)
        {
            cout << "You haven't a pokeballs. Go to shop\n";
            return false;
        }
        string res;  
        int an;
        cout << "How much do you want to throw a pokeball?\n"
            << "1 - Weak\n10 - Strong\n";
        cin >> res;

        while (!(((res > "0") && (res < "9")) || (res == "10")))
        {
            cout << "You did not answer\n";
            cin >> res;
        }
        an = std::stoi(res, nullptr, 10);

        if (rand() % an == 0)
        {
            pokemons.push_back(pok);
            return true;
        }
        else return false;
    }

    PokemonTrainer(string _name, vector<Pokemon *> pokes)
    {
        name = _name;
        pokeballs = 0;
        pokemons = pokes;
    }

public:
    PokemonTrainer(string _name, uint balls)
    {
        name = _name;
        pokeballs = balls;
    }

    bool FindPokemon()
    {
        srand(time(NULL));

        if (rand() % 3 == 0)
        {
            return true;
        }
        else return false;
    }

    void BuyPokeballs(uint count)
    {
        pokeballs = count;
    }

    void Pokedex()
    {
        for (uint i = 0, u = pokemons.size(); i < u; i++)
        {
            cout << (i + 1) << ". " << pokemons[i]->GetName()
                << ". HP: " << pokemons[i]->hp
                << ". AP: " << pokemons[i]->ap
                << '\n';
        }
    }
    friend class GUI;
};

class GUI
{
    string main_name;
    string test;

    void Intro()
    {
        ifstream names("Texts\\Pokemons.txt");
        ifstream myfile("Texts\\GameStart.txt");

        while (getline(names, test))
        {
            pokenames.push_back(test);
        }
        names.close();
        names.open("Texts\\People.txt");

        while (getline(names, test))
        {
            hum_names.push_back(test);
        }
        
        HWND console = GetConsoleWindow();
        RECT r;
        GetWindowRect(console, &r);

        MoveWindow(console, r.left, r.top, 1400, 600, TRUE);

        for (uint i = 0; i < 7; i++)
        {
            getline(myfile, test);
            cout << test << '\n';

        }

        this_thread::sleep_for(chrono::seconds(1));
        system("cls");

        PlaySound(TEXT("Music\\Menu.wav"), NULL, SND_ASYNC | SND_LOOP);

        for (uint i = 0; i < 18; i++)
        {
            getline(myfile, test);
            cout << test << '\n';

        }

        myfile.close();

        cout << '\n' << '\n';
        this_thread::sleep_for(chrono::seconds(2));

        cout << "Write Start and press enter\n";
        cin >> test;
        while (!((test == "Start") || (test == "start")))
        {
            cout << "Write Start or start. Not something else.\n";
            cin >> test;
        }
        

        myfile.open("Texts\\Begin.txt");

        cout << "Please enter your name: ";
        cin >> main_name;
        PlaySound(NULL, 0, 0);
        system("cls");
        PlaySound(TEXT("Music\\BackgroundMusic.wav"), NULL, SND_ASYNC | SND_LOOP);

        cout << "Hello " << main_name << '\n';

        while (getline(myfile, test))
        {
            this_thread::sleep_for(chrono::seconds(1));
            cout << test << '\n';
        }

        return;
    }

    uint SelectAction()
    {
        string res;
        cout << '\n'
            << "What would you want to do?" << '\n'
            << "1. Show my inventory" << '\n'
            << "2. Go to the shop" << '\n'
            << "3. Go to medicine center" << '\n'
            << "4. Try to find pokemon" << '\n'
            << "5. Exit" << '\n';

        cin >> res;

        while (!((res > "0") && (res < "6")))
        {
            cout << "You did not answer\n";
            cin >> res;
        }
        int an = std::stoi(res, nullptr, 10);

        return an;
    }
public:
    void Game()
    { 
        Intro();

        PokemonTrainer main_character(main_name, 1);
        uint count_m;
        while (true)
        {
            switch (SelectAction())
            {
            case 1:
                cout << "The number of pokeballs: " << main_character.pokeballs << '\n';
                cout << "My pokemons:\n";
                main_character.Pokedex();
                break;
            case 2:
                cout << "How much balls do you want?\n";
                cin >> count_m;
                main_character.pokeballs += count_m;
                break;
            case 3:
                cout << "Not yet\n";
                break;
            case 4:
                if (main_character.FindPokemon())
                {
                    cout << "You are find the pokemon. Do you want to catch him?\n"
                        << "1 - yes\n2 - no\n";
                    cin >> test;
                    while (!((test == "2") || (test == "1")))
                    {
                        cout << "You did not answer\n";
                        cin >> test;
                    }
                    if (test == "2")
                    {
                        break;
                    }
                    else
                    if (test == "1")
                    {
                        Pokemons bp;
                        Pokemon* poki = bp.CreateRandomPokemon();

                        if (main_character.CatchPokemon(poki))
                        {
                            cout << "Congratulation! You were got a " << poki->GetName() << '\n';
                        }
                        else cout << "You can't cath pokemon :(\n";
                        if (main_character.pokeballs > 0)
                        {
                            main_character.pokeballs--;
                        }
                    }
                }
                else cout << "You can't find pokemon\n";
                
                break;
            case 5:
                cout << "Goodbye\n";
                return;
            default:
                cout << "You did not answer\n";
            }

        }
        PlaySound(NULL, 0, 0);

        
    }
};

int main()
{
    GUI game;
    game.Game();
}
