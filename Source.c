#define _CRT_SECURE_NO_WARNINGS
#define HP 0 // Index for Health Points
#define MP 1 // Index for Magic Points
#define S 2 // Index for Strength
#define F 3 // Index for Fire Magic
#define B 4 // Index for Blizzard Magic
#define T 5 // Index for Thunder Magic
#define FC 6 // Index for Fire Magic Cost
#define BC 7 // Index for Blizzard Magic Cost
#define TC 8 // Index for Thunder Magic Cost
#define D 9 // Index for Defence
#define A 10 // Index for Agility
#define L 11 // Index for Luck
#define G 12 // Index for Genre
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Magic {
	char name[9];
	int strength;
	int cost;
}magic;

typedef struct Character {
	char name[12];
	int healthPoints;
	int magicPoints;
	int strength;
	magic fire;
	magic blizzard;
	magic thunder;
	int defence;
	int agility;
	int luck;
	char genre[13];
}character;

void battle(character hero, character enemy);
int heroAct(int fCost, int bCost, int tCost, int mp);
int enemyAct(char name[], int fCost, int bCost, int tCost, int mp);
void heroSelection(character* hero);
void enemySelection(character* enemy);

int main() {
	character hero, enemy;

	//Character selection
	heroSelection(&hero);
	enemySelection(&enemy);
	//Battle process
	srand(time(NULL));
	printf("\n!!!The battle has started!!!\n\n\n\a");
	battle(hero, enemy);

	return 0;
}

void battle(character hero, character enemy) {
	int hAct, eAct, hStrength, eStrength;
	float x, crit = 1;
	//Statistics of characters
	printf("\t\tHP\tMP\n");
	printf("\t      ------  ------\n");
	printf("%s:\t\t%d\t%d\n", hero.name, hero.healthPoints, hero.magicPoints);
	printf("%s:\t\t%d\t%d\n\n", enemy.name, enemy.healthPoints, enemy.magicPoints);
	//Hero action
	hAct = heroAct(hero.fire.cost, hero.blizzard.cost, hero.thunder.cost, hero.magicPoints);
	//Enemy action
	eAct = enemyAct(enemy.name, enemy.fire.cost, enemy.blizzard.cost, enemy.thunder.cost, enemy.magicPoints);
	//Result
	//----------------------
	//If the hero strikes or uses magic and the enemy strikes or uses magic.
	if ((hAct == S || hAct == F || hAct == B || hAct == T) && (eAct == S || eAct == F || eAct == B || eAct == T)) {
		//Determining what type of attack was used.
		if (hAct == S)
			hStrength = hero.strength;
		else if (hAct == F)
			hStrength = hero.fire.strength;
		else if (hAct == B)
			hStrength = hero.blizzard.strength;
		else
			hStrength = hero.thunder.strength;
		if (eAct == S)
			eStrength = enemy.strength;
		else if (eAct == F)
			eStrength = enemy.fire.strength;
		else if (eAct == B)
			eStrength = enemy.blizzard.strength;
		else
			eStrength = enemy.thunder.strength;

		//Battle Possibilities
		//--------------------

		//Checking if the hero is faster than or as fast as the enemy.
		if (hero.agility >= enemy.agility) {
			if (rand() % 100 + 1 <= hero.luck) {						//
				crit = 1.5;												//
				printf("!!!Your attack was critical!!!\n\n");			// Deciding if the attack was a critical attack based on luck and random chance. From now on this explanation will be shortened to "Critical".
			}															//    
			enemy.healthPoints = enemy.healthPoints - hStrength * crit;	//
			crit = 1;													//
			// Checking if the health of the enemy falls to or below 0.
			if (enemy.healthPoints <= 0) {
				printf("!!!%s has been defeated!!!\n",enemy.name);
				return;
			}
			if (rand() % 100 + 1 <= enemy.luck) {								//
				crit = 1.5;														//
				printf("!!!%s's attack was critical!!!\n\n",enemy.name);			//		Critical
			}																	//    
			hero.healthPoints = hero.healthPoints - eStrength * crit;			//
			crit = 1;															//
			// Checking if the health of the hero falls to or below 0.
			if (hero.healthPoints <= 0) {
				printf("You have died.\n");
				return;
			}
		}
		else {
			if (rand() % 100 + 1 <= enemy.luck) {						//
				crit = 1.5;												//
				printf("!!!%s's attack was critical!!!\n\n",enemy.name);	//		Critical
			}															//    
			hero.healthPoints = hero.healthPoints - eStrength * crit;	//
			crit = 1;													//
			// Checking if the health of the hero falls to or below 0.
			if (hero.healthPoints <= 0) {
				printf("You have died.\n");
				return;
			}
			if (rand() % 100 + 1 <= hero.luck) {						//
				crit = 1.5;												//
				printf("!!!Your attack was critical!!!\n\n");			//		Critical
			}															//    
			enemy.healthPoints = enemy.healthPoints - hStrength * crit;	//
			crit = 1;													//
			// Checking if the health of the enemy falls to or below 0.
			if (enemy.healthPoints <= 0) {
				printf("!!!%s has been defeated!!!\n",enemy.name);
				return;
			}
		}
		// Lowering the magic points of the hero depending on the used magic.
		if (hAct == F || hAct == B || hAct == T) {
			// Determining what type of magic was used. (The variable "hStrength" was used as the cost of the magic used because initializing another variable for this job would unnecessarily take up space in memory.)
			if (hAct == F)
				hStrength = hero.fire.cost;
			else if (hAct == B)
				hStrength = hero.blizzard.cost;
			else
				hStrength = hero.thunder.cost;

			hero.magicPoints = hero.magicPoints - hStrength;
		}
		// Lowering the magic points of the enemy depending on the used magic.
		if (eAct == F || eAct == B || eAct == T) {
			// Determining what type of magic was used. (The variable "eStrength" was used as the cost of the magic used because initializing another variable for this job would unnecessarily take up space in memory.)
			if (eAct == F)
				eStrength = enemy.fire.cost;
			else if (eAct == B)
				eStrength = enemy.blizzard.cost;
			else
				eStrength = enemy.thunder.cost;
			enemy.magicPoints = enemy.magicPoints - eStrength;
		}


	}
	//If the hero defends themselves and the enemy strikes or uses magic.
	else if (hAct == D && (eAct == S || eAct == F || eAct == B || eAct == T)) {
		//Determining what type of attack was used.
		if (eAct == S)
			eStrength = enemy.strength;
		else if (eAct == F)
			eStrength = enemy.fire.strength;
		else if (eAct == B)
			eStrength = enemy.blizzard.strength;
		else
			eStrength = enemy.thunder.strength;

		//Battle Possibilities
		//--------------------

		if (rand() % 100 + 1 <= enemy.luck) {						//
			crit = 1.5;												//
			printf("!!!%s's attack was critical!!!\n\n",enemy.name);//   Critical
		}															//
		// Determining the damage after defending.					//
		x = eStrength * crit - hero.defence;						//
		crit = 1;													//
		// Checking if there is still damage after defending.
		if (x > 0) {
			hero.healthPoints = hero.healthPoints - x;
			// Checking if the health of the hero falls to or below 0.
			if (hero.healthPoints <= 0) {
				printf("You have died.\n");
				return;
			}
		}
		// Lowering the magic points of the enemy depending on the used magic.
		if (eAct == F || eAct == B || eAct == T) {
			// Determining what type of magic was used. (The variable "eStrength" was used as the cost of the magic used because initializing another variable for this job would unnecessarily take up space in memory.)
			if (eAct == F)
				eStrength = enemy.fire.cost;
			else if (eAct == B)
				eStrength = enemy.blizzard.cost;
			else
				eStrength = enemy.thunder.cost;
			enemy.magicPoints = enemy.magicPoints - eStrength;
		}
	}
	//If the hero strikes or uses magic and the enemy defends themselves.
	else if ((hAct == S || hAct == F || hAct == B || hAct == T) && eAct == D) {
		//Determining what type of attack was used.
		if (hAct == S)
			hStrength = hero.strength;
		else if (hAct == F)
			hStrength = hero.fire.strength;
		else if (hAct == B)
			hStrength = hero.blizzard.strength;
		else
			hStrength = hero.thunder.strength;

		//Battle Possibilities
		//--------------------

		if (rand() % 100 + 1 <= hero.luck) {				//
			crit = 1.5;										//
			printf("!!!Your attack was critical!!!\n\n");	//    Critical
		}													//    
		// Determining the damage after defending.			//
		x = hStrength * crit - enemy.defence;				//
		crit = 1;											//
		// Checking if there is still damage after defending.
		if (x > 0) {
			enemy.healthPoints = enemy.healthPoints - x;
			// Checking if the health of the enemy falls to or below 0.
			if (enemy.healthPoints <= 0) {
				printf("!!!%s has been defeated!!!\n",enemy.name);
				return;
			}
		}
		// Lowering the magic points of the hero depending on the used magic.
		if (hAct == F || hAct == B || hAct == T) {
			// Determining what type of magic was used. (The variable "hStrength" was used as the cost of the magic used because initializing another variable for this job would unnecessarily take up space in memory.)
			if (hAct == F)
				hStrength = hero.fire.cost;
			else if (hAct == B)
				hStrength = hero.blizzard.cost;
			else
				hStrength = hero.thunder.cost;

			hero.magicPoints = hero.magicPoints - hStrength;
		}
	}
	//If the hero uses an item and the enemy strikes or uses magic.
	else if ((hAct == MP || hAct == HP) && (eAct == S || eAct == F || eAct == B || eAct == T)) {
		//Determining what type of attack was used.
		if (eAct == S)
			eStrength = enemy.strength;
		else if (eAct == F)
			eStrength = enemy.fire.strength;
		else if (eAct == B)
			eStrength = enemy.blizzard.strength;
		else
			eStrength = enemy.thunder.strength;

		//Determining which item was used.
		if (hAct == MP)
			hero.magicPoints += 3;
		else
			hero.healthPoints += 3;

		//Battle Possibilities
		//--------------------

		if (rand() % 100 + 1 <= enemy.luck) {						//
			crit = 1.5;												//
			printf("!!!%s's attack was critical!!!\n\n",enemy.name);//    Critical
		}															//    
		hero.healthPoints = hero.healthPoints - eStrength * crit;	//
		crit = 1;													//
		// Checking if the health of the hero falls to or below 0.
		if (hero.healthPoints <= 0) {
			printf("You have died.\n");
			return;
		}
		// Lowering the magic points of the enemy depending on the used magic.
		if (eAct == F || eAct == B || eAct == T) {
			// Determining what type of magic was used. (The variable "eStrength" was used as the cost of the magic used because initializing another variable for this job would unnecessarily take up space in memory.)
			if (eAct == F)
				eStrength = enemy.fire.cost;
			else if (eAct == B)
				eStrength = enemy.blizzard.cost;
			else
				eStrength = enemy.thunder.cost;
			enemy.magicPoints = enemy.magicPoints - eStrength;
		}
	}
	//If the hero strikes or uses magic and the enemy uses an item.
	else if ((hAct == S || hAct == F || hAct == B || hAct == T) && (eAct == MP || eAct == HP)) {
		//Determining what type of attack was used.
		if (hAct == S)
			hStrength = hero.strength;
		else if (hAct == F)
			hStrength = hero.fire.strength;
		else if (hAct == B)
			hStrength = hero.blizzard.strength;
		else
			hStrength = hero.thunder.strength;
		//Determining which item was used.
		if (eAct == MP)
			enemy.magicPoints += 3;
		else
			enemy.healthPoints += 3;

		//Battle Possibilities
		//--------------------

		if (rand() % 100 + 1 <= hero.luck) {						//
			crit = 1.5;												//
			printf("!!!Your attack was critical!!!\n\n");			//    Critical
		}															//
		enemy.healthPoints = enemy.healthPoints - hStrength * crit;	//
		crit = 1;													//
		// Checking if the health of the enemy falls to or below 0.
		if (enemy.healthPoints <= 0) {
			printf("!!!%s has been defeated!!!\n",enemy.name);
			return;
		}
		// Lowering the magic points of the hero depending on the used magic.
		if (hAct == F || hAct == B || hAct == T) {
			// Determining what type of magic was used. (The variable "hStrength" was used as the cost of the magic used because initializing another variable for this job would unnecessarily take up space in memory.)
			if (hAct == F)
				hStrength = hero.fire.cost;
			else if (hAct == B)
				hStrength = hero.blizzard.cost;
			else
				hStrength = hero.thunder.cost;

			hero.magicPoints = hero.magicPoints - hStrength;
		}
	}
	//If the hero uses an item and the enemy defends.
	else if ((hAct == MP || hAct == HP) && eAct == D) {
		//Determining which item was used.
		if (hAct == MP)
			hero.magicPoints += 3;
		else
			hero.healthPoints += 3;
	}
	//If the hero defends and the enemy uses an item.
	else if (hAct == D && (eAct == MP || eAct == HP)) {
		//Determining which item was used.
		if (eAct == MP)
			enemy.magicPoints += 3;
		else
			enemy.healthPoints += 3;
	}
	//If the hero uses an item and the enemy uses an item.
	else if ((hAct == MP || hAct == HP) && (eAct == MP || eAct == HP)) {
		//Determining which item was used.
		if (hAct == MP)
			hero.magicPoints += 3;
		else
			hero.healthPoints += 3;
		if (eAct == MP)
			enemy.magicPoints += 3;
		else
			enemy.healthPoints += 3;
	}
	//If the hero tries to run away.
	else if (hAct == L) {
		x = 1;
		if (hero.genre == enemy.genre)
			x = 1.25;
		if (hero.agility * hero.luck * x > enemy.agility * enemy.luck) {
			printf("You escaped.\n");
			return;
		}
		printf("You have failed to escape.\n");
	}
	printf("------------------------------------------------------------------------------------------\n");
	battle(hero, enemy);
}
int heroAct(int fCost, int bCost, int tCost, int mp) {
	int act, mpCost;
	
	do {
		printf("-------------------------------------------------------\n");
		printf("| 1. Strike | 2. Magic | 3. Block | 4. Item | 0. Flee |\n");
		printf("-------------------------------------------------------\n");
		printf("What do you want to do? (1, 2, 3, 4, 0) ");
		scanf("%d", &act);
		if (act == 2) {

			printf("------------------------------------------------------------------------------------------------------\n");
			printf("| 1. Fire ( Cost = %d MP ) | 2. Blizzard ( Cost = %d MP ) | 3. Thunder ( Cost = %d MP ) | 0. Go Back |\n", fCost, bCost, tCost);
			printf("------------------------------------------------------------------------------------------------------\n");
			printf("Which magic do you want to cast? (1, 2, 3, 0) ");
			scanf("%d", &act);
			if (act == 0)
				continue;
			switch (act) {
			case 1: mpCost = fCost;
				break;
			case 2: mpCost = bCost;
				break;
			case 3: mpCost = tCost;
			}
			if (mp < mpCost) {
				printf("You don't have enough MP. Choose again.\n");
				continue;
			}

			act += 5;
			break;
		}
		if (act == 4) {
			printf("---------------------------------------------------\n");
			printf("| 1. Health Potion | 2. Magic Potion | 0. Go Back |\n");
			printf("---------------------------------------------------\n");
			printf("Which potion do you want to use? (1, 2, 0)");
			scanf("%d", &act);
			if (act == 0)
				continue;
			act += 3;
		}
		break;
	} while (1 == 1);
	switch (act) {
	case 1:act = S;
		printf("\nYou striked!\n");
		break;
	case 3:act = D;
		printf("\nYou blocked!\n");
		break;
	case 4: act = HP;
		printf("\nYou used a health potion!\n");
		break;
	case 5: act = MP;
		printf("\nYou used a magic potion!\n");
		break;
	case 6: act = F;
		printf("\nYou cast fire!\n");
		break;
	case 7: act = B;
		printf("\nYou cast blizzard!\n");
		break;
	case 8: act = T;
		printf("\nYou cast thunder!\n");
		break;
	default:act = L;
		printf("\nYou tried to flee.\n");
	}
	return act;
}
int enemyAct(char name[], int fCost, int bCost, int tCost, int mp) {
	int act, mpCost;

	do {
		//The action of the enemy gets chosen randomly.
		act = rand() % 7;	
		if (act > 0 && act < 4) {
			switch (act) {
			case 1: mpCost = fCost;
				break;
			case 2: mpCost = bCost;
				break;
			case 3: mpCost = tCost;
				break;
			}
			if (mp >= mpCost)
				break;
			continue;
		}
		break;
	} while (1);
	switch (act) {
	case 0:act = S;
		printf("%s striked!\n\n",name);
		break;
	case 1:act = F;
		printf("%s cast fire!\n\n",name);
		break;
	case 2:act = B;
		printf("%s cast blizzard!\n\n",name);
		break;
	case 3:act = T;
		printf("%s cast thunder!\n\n",name);
		break;
	case 4:act = D;
		printf("%s blocked!\n\n",name);
		break;
	case 5: act = MP;
		printf("%s used a magic potion!\n\n",name);
		break;
	case 6: act = HP;
		printf("%s used a health potion\n\n",name);
		break;
	}
	return act;
}
void heroSelection(character* hero) {
	FILE* heroListPtr;
	int i;
	if ((heroListPtr = fopen("Hero_List.dat", "rb")) == NULL)
		puts("Hero_List.txt could not be opened.");
	else {
		printf("Heros\t\tHP\tMP\tStr\tFire\tBlzrd\tThndr\tF Cost\tB Cost\tT Cost\tDef\tSpd\tLuck\t\n");
		puts("-------------------------------------------------------------------------------------------------------------");
		for(i=0;i<10;i++){
			fread(hero, sizeof(character), 1, heroListPtr);
			if(i==7)
				printf("%d.%s\t\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n", i + 1, hero->name, hero->healthPoints, hero->magicPoints, hero->strength, hero->fire.strength,
					hero->blizzard.strength, hero->thunder.strength, hero->fire.cost, hero->blizzard.cost, hero->thunder.cost, hero->defence, hero->agility, hero->luck);

			else
				printf("%d.%s\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n", i+1, hero->name, hero->healthPoints, hero->magicPoints, hero->strength, hero->fire.strength, 
					hero->blizzard.strength, hero->thunder.strength, hero->fire.cost, hero->blizzard.cost, hero->thunder.cost, hero->defence, hero->agility, hero->luck);
		}
		rewind(heroListPtr);
		printf("Please choose who you want to fight as: ");
		scanf("%d", &i);
		fseek(heroListPtr, (i - 1) * sizeof(character), SEEK_SET);
		fread(hero, sizeof(character), 1, heroListPtr);
		if (strcspn(hero->name, "\t") != strlen(hero->name))
			hero->name[strcspn(hero->name, "\t")] = "";
		fclose(heroListPtr);
	}
}
void enemySelection(character* enemy) {
	FILE* enemyListPtr;
	int i;
	if ((enemyListPtr = fopen("Enemy_List.dat", "rb")) == NULL)
		puts("Enemy_List.dat could not be opened.");
	else {
		printf("Enemies\t\tHP\tMP\tStr\tFire\tBlzrd\tThndr\tF Cost\tB Cost\tT Cost\tDef\tSpd\tLuck\t\n");
		puts("-------------------------------------------------------------------------------------------------------------");

		for (i = 0; i < 10; i++) {
			fread(enemy, sizeof(character), 1, enemyListPtr);
			if(i==1 || i==4 || i==8)
				printf("%d.%s\t\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n", i + 1, enemy->name, enemy->healthPoints, enemy->magicPoints, enemy->strength, enemy->fire.strength,
					enemy->blizzard.strength, enemy->thunder.strength, enemy->fire.cost, enemy->blizzard.cost, enemy->thunder.cost, enemy->defence, enemy->agility, enemy->luck);
			else
				printf("%d.%s\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n", i+1, enemy->name, enemy->healthPoints, enemy->magicPoints, enemy->strength, enemy->fire.strength,
					enemy->blizzard.strength, enemy->thunder.strength, enemy->fire.cost, enemy->blizzard.cost, enemy->thunder.cost, enemy->defence, enemy->agility, enemy->luck);
		}
		rewind(enemyListPtr);
		printf("Please choose who you want to fight as: ");
		scanf("%d", &i);
		fseek(enemyListPtr, (i - 1) * sizeof(character), SEEK_SET);
		fread(enemy, sizeof(character), 1, enemyListPtr);
		if (strcspn(enemy->name, "\t") != strlen(enemy->name))
			enemy->name[strcspn(enemy->name, "\t")] = "";
		fclose(enemyListPtr);
	}
}