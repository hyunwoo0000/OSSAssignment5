#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

 //텍스트 rpg게임으로 자신의 캐릭터와 적의 캐릭터를 구분하지 않고 생성하기 위해 만든 클래스
class Character {
public:
    string name;
    int health, maxHealth;
    int mp, maxMp;
    int minAttack, maxAttack;
    int defense;
    int gold;
    int level, exp, expToLevelUp;
    string weapon;
    
    Character(string n, int h, int mp, int ma, int d, int g) : name(n), maxHealth(h), health(h), maxMp(mp), mp(mp), maxAttack(ma), minAttack(int(ma * 0.7)), defense(d), gold(g), weapon("기본 무기"), level(1), exp(0), expToLevelUp(100) {}

    void attackTarget(Character& target) {
        int damage = (rand() % (maxAttack - minAttack + 1) + minAttack) - target.defense;
        if (damage > 0) {
            target.health -= damage;
            cout << name << "가 " << target.name << "에게 " << damage << "의 피해를 입혔습니다.\n";
        } else {
            cout << name << "의 공격이 무효화되었습니다.\n";
        }
        displayStatus();
    }

    void useSkill(Character& target) {
        if (mp >= 10) {
            mp -= 10;
            int damage = (maxAttack * 2) - target.defense;
            target.health -= damage;
            cout << name << "가 스킬로 " << target.name << "에게 " << damage << "의 피해를 입혔습니다.\n";
        } else {
            cout << "MP가 부족합니다.\n";
        }
        displayStatus();
    }

    void gainExp(int amount) {
        exp += amount;
        cout << amount << "의 경험치를 획득했습니다.\n";
        if (exp >= expToLevelUp) {
            levelUp();
        }
    }

    void levelUp() {
        exp = 0;
        level++;
        expToLevelUp += 50;

        int prevMaxHealth = maxHealth;
        int prevMaxMp = maxMp;
        int prevMaxAttack = maxAttack;
        int prevMinAttack = minAttack;
        int prevDefense = defense;

        maxHealth += 20;
        health = maxHealth;
        maxMp += 10;
        mp = maxMp;
        maxAttack += 5;
        minAttack = int(maxAttack * 0.7);
        defense += 3;

        cout << "레벨업!\n";
        cout << "레벨: " << level << "\n";
        cout << "체력: " << prevMaxHealth << " -> " << maxHealth << "\n";
        cout << "마나: " << prevMaxMp << " -> " << maxMp << "\n";
        cout << "공격력: " << prevMinAttack << " ~ " << prevMaxAttack << " -> " << minAttack << " ~ " << maxAttack << "\n";
        cout << "방어력: " << prevDefense << " -> " << defense << "\n";
    }

    void displayStatus() {
        cout << name << "의현재 상태 - Health: " << health << "/" << maxHealth << ", MP: " << mp << "/" << maxMp << "\n";
    }
};

class Equipment {
public:
    string name;
    int healthBoost, mpBoost, attackBoost, defenseBoost;
    
    Equipment(string n, int h, int mp, int a, int d) : name(n), healthBoost(h), mpBoost(mp), attackBoost(a), defenseBoost(d) {}
};

void equipItem(Character& player, Equipment& item) {
    
    player.health += item.healthBoost;
    player.maxHealth += item.healthBoost;
    
    player.mp += item.mpBoost;
    player.maxMp += item.mpBoost;
    
    player.minAttack += item.attackBoost;
    player.maxAttack += item.attackBoost;
    
    player.defense += item.defenseBoost;
    
    player.weapon = item.name;
    
    cout << item.name << "을(를) 장착했습니다.\n";
}

void shop(Character& player) {
    Equipment Warrior_Sword("전용 검", 100, 40, 20, 10);
    Equipment Archer_Bow("전용 활", 70, 70, 30, 7);
    Equipment Mage_Staff("전용 스태프", 50, 90, 40, 5);
    
    while (true) {
            cout << "상점에 오신 것을 환영합니다! 현재 골드: " << player.gold << "\n";
            cout << "1. 물약 (50 골드) - 회복\n";
            cout << "2. ";
            if(player.name == "전사") cout << "헬스";
            else if (player.name == "궁수") cout << "과녁 맞히기";
            else cout << "명상";
            
            cout << "(80 골드) - 공격력 증가\n";
            cout << "3. 전용 무기 구매 (200 골드)\n";
            cout << "4. 나가기\n";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    if (player.gold >= 50) {
                        player.gold -= 50;
                        
                        player.health = player.maxHealth;
                        player.mp = player.maxMp;
                        
                        cout << "체력과 마나가 모두 회복되었습니다!\n";
                    } else {
                        cout << "골드가 부족합니다.\n";
                    }
                    break;
                case 2:
                    if (player.gold >= 80) {
                        player.gold -= 80;
                        player.maxAttack += 10;
                        player.minAttack = int(player.maxAttack * 0.7);
                        cout << "공격력이 증가했습니다!\n";
                    } else {
                        cout << "골드가 부족합니다.\n";
                    }
                    break;
                case 3:
                    if (player.gold >= 200) {
                        player.gold -= 200;
                        
                        if (player.name == "전사") equipItem(player, Warrior_Sword);
                        else if(player.name == "궁수") equipItem(player, Archer_Bow);
                        else if (player.name == "마법사") equipItem(player, Mage_Staff);
                        
                        cout << "전용 무기를 획득했습니다!";
                    } else {
                        cout << "골드가 부족합니다.\n";
                    }
                    break;
                    
                case 4:
                    return;
                    
                default:
                    cout << "잘못된 선택입니다.\n";
                    break;
            }
        }
}

 

bool singleBattle(Character& player, Character& enemy) {
    
    cout << enemy.name << "가 등장했습니다!\n";

    while (player.health > 0 && enemy.health > 0) {
        cout << "1. 공격 2. 스킬 사용\n";
        int choice;
        cin >> choice;

        if (choice == 1) {
            player.attackTarget(enemy);
        } else if (choice == 2) {
            player.useSkill(enemy);
        } else {
            cout << "잘못된 선택입니다.\n";
        }

        if (enemy.health > 0) enemy.attackTarget(player);
    }
    
    if (player.health <= 0) {
        cout << player.name << "가 쓰러졌습니다. 게임 오버!\n";
        return false;
    } else {
        cout << enemy.name << "를 무찌르셨습니다!\n";
        player.gold += enemy.gold;
        player.gainExp(20 + enemy.level * 7);
        return true;
    }
}

void battle(Character& player, int stage) {
    
    int i = stage;
    
    Character enemy("적 " + to_string(i), 50 + i * 10, 0, 10 + i * 5, 5 + i * 3, 20 + i * 10);
    enemy.level = stage;
    if (i == 10) enemy.name = "보스";

    if (!singleBattle(player, enemy)) return;
    
    if(i == 10)
        cout << "보스를 쓰러뜨리고 게임에서 승리했습니다!!\n";
    
}

int main() {
    srand(time(nullptr));

    // 캐릭터 생성
    Character Warrior("전사", 100, 50, 20, 10, 100);
    Character Archer("궁수", 80, 60, 15, 5, 100);
    Character Mage("마법사", 60, 80, 25, 3, 100);


    // 직업 선택
    cout << "직업을 선택하세요: 1. 전사  2. 궁수  3. 마법사\n";
    int choice;
    cin >> choice;

    Character* player;

    switch (choice) {
        case 1:
            player = &Warrior;
            break;
        case 2:
            player = &Archer;
            break;
        case 3:
            player = &Mage;
            break;
        default:
            cout << "잘못된 선택입니다.\n";
            return 1;
    }
    
    int stage = 1;
    // 메뉴
    while (player->health > 0) {
        
        cout << "무엇을 하시겠습니까?\n";
        cout << "1. 상점  2. 전투  3. 캐릭터 정보  4. 게임 종료\n";
        cin >> choice;

        switch (choice) {
            case 1:
                shop(*player);
                break;
            case 2:
                battle(*player, stage++);
                break;
            case 3:
                cout << "직업: " << player->name
                << "\n레벨: " << player->level
                << "\n체력: " << player->health
                << "/" << player->maxHealth
                << "\n마나: " << player->mp
                << "/" << player->maxMp
                << "\n공격력: " << player->minAttack << " ~ " << player->maxAttack
                << "\n방어력: " << player->defense
                << "\n경험치: " << player->exp << "/" << player->expToLevelUp
                <<"\n골드: " << player->gold
                << "\n무기: " << player->weapon
                << "\n";
                break;
            case 4:
                return 0;
            default:
                cout << "잘못된 선택입니다.\n";
                break;
        }
        if (stage > 10) break;
    }

    return 0;
}

 







