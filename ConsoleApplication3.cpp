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
vector<string> pokenames;
vector<string> hum_names;
//enum PBALLS { POKEBALL, GREATBALL, ULTRABALL};
//enum TERRAIN {SEA, VOLCANO, FOREST};

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
private:
    string name;
    SIZEP size;
    TYPE type;
    uint hp;
    uint ap;
    vector<uint> action;
public:
    string TypeToStr()
    {
        switch (type)
        {
        case 0:
            return "Fire";
        case 1:
            return "Water";
        case 2:
            return "Ground";
        case 3:
            return "Electric";
        }
    }

    string SizeToStr()
    {
        switch (size)
        {
        case 0:
            return "Small";
        case 1:
            return "Medium";
        case 2:
            return "Big";
        }
    }

    string getName()
    {
        return name;
    }

    uint getHp()
    {
        return hp;
    }

    uint getAp()
    {
        return ap;
    }

    friend class BuilderSmallPokemon;
    friend class BuilderMediumPokemon;
    friend class BuilderBigPokemon;

};

class BuilderPokemon 
{
public:
    virtual void setType() const = 0;
    virtual void setSize() const = 0;
    virtual void setHpAp() const = 0;
    virtual void setName() const = 0;
    
    
    virtual Pokemon* GetPokemon() const = 0;
};

class BuilderSmallPokemon : public BuilderPokemon
{
    Pokemon* res = new Pokemon;

    void setType() const override
    {
        srand(time(NULL));
        res->type = IntToTYPE(rand() % 4);
    }
    void setSize() const override
    {
        res->size = SMALL;
    }
    void setHpAp() const override
    {
        srand(time(NULL));
        uint choose = rand();
        res->hp = ((choose % 100) + 1) / 3;
        choose = (choose % 10) + 1;
        res->ap = (choose * 3);
    }

    void setName() const override
    {
        srand(time(NULL));
        if (pokenames.size() == 0)
        {
            res->name = "Default";
        }
        else
        {
            res->name = pokenames[rand() % pokenames.size()];            // TODO
        }
    }

    Pokemon* GetPokemon() const override
    {
        return res;
    }
};

class BuilderMediumPokemon : public BuilderPokemon
{
    Pokemon* res = new Pokemon;

    void setType() const override
    {
        srand(time(NULL));
        res->type = IntToTYPE(rand() % 4);
    }
    void setSize() const override
    {
        res->size = MEDIUM;
    }
    void setHpAp() const override
    {
        srand(time(NULL));
        uint choose = rand();
        res->hp = ((choose % 100) + 1) / 2;
        choose = (choose % 10) + 1;
        res->ap = (choose * 3) / 2;
    }

    void setName() const override
    {
        srand(time(NULL));
        if (pokenames.size() == 0)
        {
            res->name = "Default";
        }
        else
        {
            res->name = pokenames[rand() % pokenames.size()];            // TODO
        }
    }

    Pokemon* GetPokemon() const override
    {
        return res;
    }
};

class BuilderBigPokemon : public BuilderPokemon
{
    Pokemon* res = new Pokemon;

    void setType() const override
    {
        srand(time(NULL));
        res->type = IntToTYPE(rand() % 4);
    }
    void setSize() const override
    {
        res->size = BIG;
    }
    void setHpAp() const override
    {
        srand(time(NULL));
        uint choose = rand();
        res->hp = ((choose % 100) + 1);
        choose = (choose % 10) + 1;
        res->ap = (choose * 3) / 3;
    }

    void setName() const override
    {
        srand(time(NULL));
        if (pokenames.size() == 0)
        {
            res->name = "Default";
        }
        else
        {
            res->name = pokenames[rand() % pokenames.size()];            // TODO
        }
    }

    Pokemon* GetPokemon() const override
    {
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

        if (true)//rand() % an == 0)
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

        if (true)//rand() % 3 == 0)
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
            cout << (i + 1) << ". " << pokemons[i]->getName()
                << ". HP: " << pokemons[i]->getHp()
                << ". AP: " << pokemons[i]->getAp()
                << ". Type: " << pokemons[i]->TypeToStr()
                << ". Size: " << pokemons[i]->SizeToStr()
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
                            cout << "Congratulation! You were got a " << poki->getName() << '\n';
                        }
                        else cout << "You can't catch pokemon :(\n";
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
