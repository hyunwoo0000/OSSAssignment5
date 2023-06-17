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
     int minAttack, maxAttack;
     int defense;
     string weapon;
     
     void attackTarget(Character& target) {
        int damage = (rand() % (maxAttack - minAttack + 1) + minAttack) - target.defense;
        if (damage > 0) {
            target.health -= damage;
            cout << name << "가 " << target.name << "에게 " << damage << "의 피해를 입혔습니다.\n";
        } else {
            cout << name << "의 공격이 무효화되었습니다.\n";
        }
    }
     
     Character(string n, int h, int ma, int d) : name(n), maxHealth(h), health(h), maxAttack(ma), minAttack(int(ma * 0.7)), defense(d), weapon("기본 무기") {}

 };

 

void battle(Character& player) {
    for (int i = 1; i <= 10; i++) {
        Character enemy("적 " + to_string(i), 50 + i * 10, 10 + i * 5, 5 + i * 2);
        if (i == 10) enemy.name = "보스";

        cout << enemy.name << "가 등장했습니다!\n";

        while (player.health > 0 && enemy.health > 0) {
            player.attackTarget(enemy);
            if (enemy.health > 0) enemy.attackTarget(player);
        }

        if (player.health <= 0) {
            cout << player.name << "가 쓰러졌습니다. 게임 오버!\n";
            return;
        } else {
            cout << enemy.name << "를 무찌르셨습니다!\n";
        }
    }
    cout << "모든 적을 무찌르고 게임에서 승리했습니다!\n";
}

 int main() {
     srand(time(nullptr));

     // 캐릭터 생성
     Character Warrior("전사", 100, 20, 10);
     Character Archer("궁수", 80, 15, 5);
     Character Mage("마법사", 60, 25, 3);


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
     
     battle(*player);
     

     return 0;
 }

 


