﻿#include <iostream>
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
enum TYPE { FIRE, WATER, GRASS, ELECTRIC};
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
        return GRASS;
    case 3:
        return ELECTRIC;
    }
}

class Pokemon
{
public:                     //Sorry :(
    string name;
    SIZEP size;
    TYPE type;
    uint hp;
    uint max_hp;
    uint ap;
    uint max_ap;
    uint damage; // Scratch - 1, Wait - 2, Dodge - 3, Special - 4

    string TypeToStr()
    {
        switch (type)
        {
        case 0:
            return "Fire";
        case 1:
            return "Water";
        case 2:
            return "GRASS";
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

    TYPE getType()
    {
        return type;
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

    uint getMaxHp()
    {
        return max_hp;
    }

    uint getMaxAp()
    {
        return max_ap;
    }


    uint getDamage()
    {
        return damage;
    }

    void addHp(uint count)
    {
        if (hp + count > max_hp)
        {
            hp = max_hp;
        }
        else
        hp += count;
    }

    void addAp(uint count)
    {
        if (ap + count > max_ap)
        {
            ap = max_ap;
        }
        else
        ap += count;
    }

    void DoDamage(Pokemon* pok)
    {
        int dg = pok->hp - damage;
        if (dg <= 0)
        {
            pok->hp = 0;
        }
        pok->hp = dg;
    }

    friend class BuilderSmallPokemon;
    friend class BuilderMediumPokemon;
    friend class BuilderBigPokemon;
};

class BuilderPokemon 
{
public:
    virtual void setType(TYPE _type) const = 0;
    virtual void setName(string _name) const = 0;
    virtual void setHpAp(uint mhp, uint map) const = 0;
    virtual void setName() const = 0;
    
    
    virtual Pokemon* GetPokemon() const = 0;
};

class BuilderSmallPokemon : public BuilderPokemon
{
    Pokemon* res = new Pokemon;

    void setType(TYPE _type) const override
    {
        res->type = _type;
    }

    void setHpAp(uint mhp, uint map) const override
    {
        res->max_hp = mhp;
        res->max_ap = map;
        res->hp = res->max_hp;
        res->ap = res->max_ap;
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

    void setName(string _name) const override
    {
        res->name = _name;
    }

    Pokemon* GetPokemon() const override
    {
        res->damage = 4;
        res->size = SMALL;
        return res;
    }
};

class BuilderMediumPokemon : public BuilderPokemon
{
    Pokemon* res = new Pokemon;

    void setType(TYPE _type) const override
    {
        res->type = _type;
    }

    void setHpAp(uint mhp, uint map) const override
    {
        res->max_hp = mhp;
        res->max_ap = map;
        res->hp = res->max_hp;
        res->ap = res->max_ap;
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

    void setName(string _name) const override
    {
        res->name = _name;
    }

    Pokemon* GetPokemon() const override
    {
        res->damage = 9;
        res->size = MEDIUM;
        return res;
    }
};

class BuilderBigPokemon : public BuilderPokemon
{
    Pokemon* res = new Pokemon;

    void setType(TYPE _type) const override
    {
        res->type = _type;
    }
    void setHpAp(uint mhp, uint map) const override
    {
        res->max_hp = mhp;
        res->max_ap = map;
        res->hp = res->max_hp;
        res->ap = res->max_ap;
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

    void setName(string _name) const override
    {
        res->name = _name;
    }

    Pokemon* GetPokemon() const override
    {
        res->damage = 16;
        res->size = BIG;
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
        uint choose = rand();
        uint ma_hp = 0;
        uint ma_ap = 0;
        switch (coef)
        {
        case 1:
            builder = new BuilderSmallPokemon;    
            ma_hp = ((choose % 100) + 1) / 3;
            choose = (choose % 10) + 1;
            ma_ap = (choose * 3);
            builder->setHpAp(ma_hp, ma_ap);
            break;
        case 2:
            builder = new BuilderMediumPokemon;
            ma_hp = ((choose % 100) + 1) / 2;
            choose = (choose % 10) + 1;
            ma_ap = (choose * 3) / 2;
            builder->setHpAp(ma_hp, ma_ap);
            break;
        case 3:
            builder = new BuilderBigPokemon;
            ma_hp = ((choose % 100) + 1);
            choose = (choose % 10) + 1;
            ma_ap = choose;
            builder->setHpAp(ma_hp, ma_ap);
            break;
        }
        builder->setType(IntToTYPE(rand() % 4));
        builder->setName();
        
        return builder->GetPokemon();
    }

    Pokemon* CreateCharmander()
    {
        srand(time(NULL));
        uint coef = (rand() % 3) + 1;
        builder = new BuilderMediumPokemon;

        builder->setName("Charmander");
        builder->setHpAp(25, 8);
        builder->setType(FIRE);

        return builder->GetPokemon();
    }

    Pokemon* CreatePikachu()
    {
        srand(time(NULL));
        uint coef = (rand() % 3) + 1;
        builder = new BuilderMediumPokemon;

        builder->setName("Pikachu");
        builder->setHpAp(20, 13);
        builder->setType(ELECTRIC);

        return builder->GetPokemon();
    }

    Pokemon* CreateSquirtle()
    {
        srand(time(NULL));
        uint coef = (rand() % 3) + 1;
        builder = new BuilderMediumPokemon;

        builder->setName("Squirtle");
        builder->setHpAp(15, 18);
        builder->setType(WATER);

        return builder->GetPokemon();
    }

    Pokemon* CreateBulbasaur()
    {
        srand(time(NULL));
        uint coef = (rand() % 3) + 1;
        builder = new BuilderMediumPokemon;

        builder->setName("Bulbasaur");
        builder->setHpAp(16, 16);
        builder->setType(GRASS);

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
    PokemonTrainer() {};
    PokemonTrainer(string _name, uint balls, Pokemon* s_pok)
    {
        name = _name;
        pokeballs = balls;
        pokemons.push_back(s_pok);
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
                << ". HP: " << pokemons[i]->getHp() << "\\" << pokemons[i]->getMaxHp()
                << ". AP: " << pokemons[i]->getAp() << "\\" << pokemons[i]->getMaxAp()
                << ". Type: " << pokemons[i]->TypeToStr()
                << ". Size: " << pokemons[i]->SizeToStr()
                << '\n';
        }
    }

    void MedCenter()
    {
        for (uint i = 0, u = pokemons.size(); i < u; i++)
        {
            pokemons[i]->addHp(pokemons[i]->getMaxHp());
            pokemons[i]->addAp(pokemons[i]->getMaxAp());
        }
    }
    friend class GUI;
};


class GUI
{
    PokemonTrainer* main_character;
    string test;
    string main_name;

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

    uint SelectFightAction()
    {
        string res;
        cout << '\n'
            << "What would you want to do?" << '\n'
            << "1. Actions" << '\n'
            << "2. Try to catch" << '\n'
            << "3. Run away" << '\n';
        cin >> res;

        while (!((res > "0") && (res < "4")))
        {
            cout << "You did not answer\n";
            cin >> res;
        }
        int an = std::stoi(res, nullptr, 10);

        return an;
    }

    uint Actions()
    {
        string res;
        cout << '\n'
            << "What would you want to do?" << '\n'
            << "1. Scratch" << '\n'
            << "2. Wait" << '\n'
            << "3. Dodge" << '\n'
            << "4. Special ability" << '\n';
        cin >> res;

        while (!((res > "0") && (res < "5")))
        {
            cout << "You did not answer\n";
            cin >> res;
        }
        int an = std::stoi(res, nullptr, 10);

        return an;
    }

    void PokeFight(Pokemon* pok1, Pokemon* pok2)
    {
        PlaySound(TEXT("Music\\Battle.wav"), NULL, SND_ASYNC | SND_LOOP);
        this_thread::sleep_for(chrono::seconds(2));

        bool stun1 = false;
        bool stun2 = false;
        bool dodge1 = false;
        bool dodge2 = false;
        TYPE tp = pok1->getType();
        while ((pok1->getHp() > 0) && (pok2->getHp() > 0))
        {
            cout << "Your pokemon: " << pok1->getName() << '\n'
                << "HP: " << pok1->getHp() << "\\" << pok1->getMaxHp() << '\n'
                << "AP: " << pok1->getAp() << "\\" << pok1->getMaxAp() << '\n'
                << "---------------------------------------------" << '\n'
                << "Wild Pokemon: " << pok2->getName() << '\n'
                << "HP: " << pok2->getHp() << "\\" << pok2->getMaxHp() << '\n'
                << "AP: " << pok2->getAp() << "\\" << pok2->getMaxAp() << '\n';
            switch (SelectFightAction())
            {
            case 1:
            {
                switch (Actions())
                {
                case 1:
                {
                    if (pok1->getAp() == 0)
                    {
                        cout << pok1->getName() << " is tired. He is waiting\n";
                        if (tp == WATER)
                        {
                            cout << pok1->getName() << " 2 Action point restored\n";
                            pok1->addAp(2);
                        }
                        else
                        {
                            cout << pok1->getName() << " 1 Action point restored\n";
                            pok1->addAp(1);
                        }
                        break;
                    }
                    if (dodge2 == false)
                    {
                        pok1->DoDamage(pok2);
                        pok1->ap--;
                        if (tp == FIRE)
                        {
                            srand(time(NULL));
                            if (rand() % 4 == 0)
                            {
                                pok1->DoDamage(pok2);
                                cout << pok1->getName() << " deals " << (pok1->getDamage() * 2)
                                    << " damage to " << pok2->getName() << '\n';
                                break;
                            }
                        }
                        else if (tp == ELECTRIC)
                        {
                            if (rand() % 8 == 0)
                            {
                                stun2 = true;
                                cout << "The enemy is stunned\n";
                                break;
                            }
                        }
                        cout << pok1->getName() << " deals " << pok1->getDamage()
                            << " damage to " << pok2->getName() << '\n';
                        break;
                    }
                    cout << "Attack missed\n";
                    break;
                }
                case 2:
                    if (tp == WATER)
                    {
                        cout << pok1->getName() << " 2 Action point restored\n";
                        pok1->addAp(2);
                    }
                    else
                    {
                        cout << pok1->getName() << " 1 Action point restored\n";
                        pok1->addAp(1);
                    }
                    break;
                case 3:
                    cout << "Pokemon dodge next attack\n";
                    dodge1 = true;
                    break;
                case 4:
                    if (tp == FIRE)
                    {
                        cout << "Attacks have a 25% chance of double damage\n";
                    }
                    else if (tp == WATER)
                    {
                        cout << "2 AP recovers while waiting\n";
                    }
                    else if (tp == ELECTRIC)
                    {
                        cout << "Attacks have a 5% chance of stun pokemon\n";
                    }
                    else if (tp == GRASS)
                    {
                        cout << "Each round your pokemon restores 5% health\n";
                    }
                    break;
                }
                break;
            }
            case 2:
                if ((pok2->getHp() <= 15) && (main_character->pokeballs > 0))
                {
                    main_character->pokemons.push_back(pok2);
                    cout << "Congratulation! You were got a " << pok2->getName() << '\n';
                }
                else if (main_character->CatchPokemon(pok2))
                {
                    cout << "Congratulation! You were got a " << pok2->getName() << '\n';
                }
                else cout << "You can't catch pokemon :(\n";
                if (main_character->pokeballs > 0)
                {
                    main_character->pokeballs--;
                }
                this_thread::sleep_for(chrono::seconds(1));
                return;
            case 3:
                cout << "You ran away\n";
                this_thread::sleep_for(chrono::seconds(1));
                return;
            }
            if (tp == GRASS)
            {
                uint heal = (pok1->getMaxHp() / 100) * 5;
                pok1->addHp(heal);
                cout << "Pokemon restore " << heal << " HP\n";
            }

            if (stun2 == true)
            {
                cout << pok2->getName() << " skip";
            }
            else
            if (pok2->getAp() > 0)
            {
                pok2->DoDamage(pok1);
                pok2->ap--;
                cout << pok2->getName() << " deals " << pok2->getDamage()
                    << " damage to " << pok1->getName() << '\n';
            }
            else
            {
                pok2->addAp(1);
                cout << pok2->getName() << " 1 Action point restored\n";
            }
        }
        cout << "END\n";
        return;
    }
public:
    void Intro()
    {
        this->main_name = main_name;
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

        for (uint i = 0; i < 2; i++)
        {
            getline(myfile, test);
            this_thread::sleep_for(chrono::seconds(2));
            cout << test << '\n';
        }
        for (uint i = 0; i < 4; i++)
        {
            getline(myfile, test);
            this_thread::sleep_for(chrono::seconds(0));
            cout << test << '\n';
        }

        cin >> test;

        while (!((test > "0") && (test < "5")))
        {
            cout << "You did not answer\n";
            cin >> test;
        }
        int an = std::stoi(test, nullptr, 10);

        Pokemons bp;
        Pokemon* poki;
        switch (an)
        {
        case 1:
            poki = bp.CreateCharmander();
            break;
        case 2:
            poki = bp.CreatePikachu();
            break;
        case 3:
            poki = bp.CreateSquirtle();
            break;
        case 4:
            poki = bp.CreateBulbasaur();
            break;
        default:
            poki = bp.CreateRandomPokemon();
            break;
        }

        main_character = new PokemonTrainer(main_name, 4, poki);

        for (uint i = 0; i < 2; i++)
        {
            getline(myfile, test);
            this_thread::sleep_for(chrono::seconds(2));
            cout << test << '\n';
        }
        return;
    }


    void Game()
    {   
        uint count_m;
        while (true)
        {
            switch (SelectAction())
            {
            case 1:
                cout << "The number of pokeballs: " << main_character->pokeballs << '\n';
                cout << "My pokemons:\n";
                main_character->Pokedex();
                break;
            case 2:
                cout << "How much balls do you want?\n";
                cin >> count_m;
                main_character->pokeballs += count_m;
                break;
            case 3:
                main_character->MedCenter();
                cout << "All pokemons restored\n";
                break;
            case 4:
                if (main_character->FindPokemon())
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
                        system("cls");
                        cout << "Battle start!\n";
                        PlaySound(NULL, 0, 0);
                        PokeFight(main_character->pokemons.back(), poki);
                        system("cls");
                        PlaySound(NULL, 0, 0);
                        PlaySound(TEXT("Music\\BackgroundMusic.wav"), NULL, SND_ASYNC | SND_LOOP);
                        /*if (main_character->CatchPokemon(poki))
                        {
                            cout << "Congratulation! You were got a " << poki->getName() << '\n';
                        }
                        else cout << "You can't catch pokemon :(\n";
                        if (main_character->pokeballs > 0)
                        {
                            main_character->pokeballs--;
                        }*/
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

    game.Intro();
    game.Game();
}
