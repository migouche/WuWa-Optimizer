#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char* name;
    int base_stats[8];
    int elemental_bonuses[6];
    int constellations;
    struct {
        int basic_attack;
        int resonance_skill;
        int forte_circuit;
        int resonance_liberation;
        int intro_skill;
        int basic_skills[4];
        int inherent_skills[2];
    } talents;
} Character;

int stat_string_to_id(const char* stat) {
    if (strcmp(stat, "HP") == 0) return 0;
    if (strcmp(stat, "ATK") == 0) return 1;
    if (strcmp(stat, "DEF") == 0) return 2;
    if (strcmp(stat, "Energy Regen") == 0) return 3;
    if (strcmp(stat, "Crit. Rate") == 0) return 4;
    if (strcmp(stat, "Crit. DMG") == 0) return 5;
    if (strcmp(stat, "Healing Bonus") == 0) return 6;
    if (strcmp(stat, "Max Energy") == 0) return 7;
    if (strcmp(stat, "Glacio") == 0) return 0;
    if (strcmp(stat, "Fusion") == 0) return 1;
    if (strcmp(stat, "Electro") == 0) return 2;
    if (strcmp(stat, "Aero") == 0) return 3;
    if (strcmp(stat, "Spectro") == 0) return 4;
    if (strcmp(stat, "Havoc") == 0) return 5;
    return -1; // Unknown stat
}

Character json_to_character(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* data = (char*)malloc(length + 1);
    fread(data, 1, length, file);
    fclose(file);
    data[length] = '\0';

    cJSON* json = cJSON_Parse(data);
    if (json == NULL) {
        printf("Error parsing JSON\n");
        exit(1);
    }

    Character character;
    character.name = strdup(cJSON_GetObjectItem(json, "name")->valuestring);

    cJSON* base_stats = cJSON_GetObjectItem(json, "base_stats");
    character.base_stats[0] = cJSON_GetObjectItem(base_stats, "HP")->valueint;
    character.base_stats[1] = cJSON_GetObjectItem(base_stats, "ATK")->valueint;
    character.base_stats[2] = cJSON_GetObjectItem(base_stats, "DEF")->valueint;
    character.base_stats[3] = cJSON_GetObjectItem(base_stats, "Energy Regen")->valueint;
    character.base_stats[4] = cJSON_GetObjectItem(base_stats, "Crit. Rate")->valueint;
    character.base_stats[5] = cJSON_GetObjectItem(base_stats, "Crit. DMG")->valueint;
    character.base_stats[6] = cJSON_GetObjectItem(base_stats, "Healing Bonus")->valueint;
    character.base_stats[7] = cJSON_GetObjectItem(base_stats, "Max Energy")->valueint;

    cJSON* elemental_bonuses = cJSON_GetObjectItem(json, "elemental_bonuses");
    character.elemental_bonuses[0] = cJSON_GetObjectItem(elemental_bonuses, "Glacio")->valueint;
    character.elemental_bonuses[1] = cJSON_GetObjectItem(elemental_bonuses, "Fusion")->valueint;
    character.elemental_bonuses[2] = cJSON_GetObjectItem(elemental_bonuses, "Electro")->valueint;
    character.elemental_bonuses[3] = cJSON_GetObjectItem(elemental_bonuses, "Aero")->valueint;
    character.elemental_bonuses[4] = cJSON_GetObjectItem(elemental_bonuses, "Spectro")->valueint;
    character.elemental_bonuses[5] = cJSON_GetObjectItem(elemental_bonuses, "Havoc")->valueint;

    character.constellations = cJSON_GetObjectItem(json, "constellations")->valueint;

    cJSON* talents = cJSON_GetObjectItem(json, "talents");
    character.talents.basic_attack = cJSON_GetObjectItem(talents, "basic_attack")->valueint;
    character.talents.resonance_skill = cJSON_GetObjectItem(talents, "resonance_skill")->valueint;
    character.talents.forte_circuit = cJSON_GetObjectItem(talents, "forte_circuit")->valueint;
    character.talents.resonance_liberation = cJSON_GetObjectItem(talents, "resonance_liberation")->valueint;
    character.talents.intro_skill = cJSON_GetObjectItem(talents, "intro_skill")->valueint;

    cJSON* basic_skills = cJSON_GetObjectItem(talents, "basic_skills");
    character.talents.basic_skills[0] = cJSON_GetObjectItem(basic_skills, "left")->valueint;
    character.talents.basic_skills[1] = cJSON_GetObjectItem(basic_skills, "center_left")->valueint;
    character.talents.basic_skills[2] = cJSON_GetObjectItem(basic_skills, "center_right")->valueint;
    character.talents.basic_skills[3] = cJSON_GetObjectItem(basic_skills, "right")->valueint;

    cJSON* inherent_skills = cJSON_GetObjectItem(talents, "inherent_skills");
    character.talents.inherent_skills[0] = cJSON_GetArrayItem(inherent_skills, 0)->valueint;
    character.talents.inherent_skills[1] = cJSON_GetArrayItem(inherent_skills, 1)->valueint;

    cJSON_Delete(json);
    free(data);

    return character;
}

void free_character(Character* character) {
    free(character->name);
}

int main() {
    Character character = json_to_character("character.json");
    printf("Name: %s\n", character.name);
    printf("Base Stats: HP=%d, ATK=%d, DEF=%d, Energy Regen=%d, Crit. Rate=%d, Crit. DMG=%d, Healing Bonus=%d, Max Energy=%d\n",
           character.base_stats[0], character.base_stats[1], character.base_stats[2], character.base_stats[3],
           character.base_stats[4], character.base_stats[5], character.base_stats[6], character.base_stats[7]);
    printf("Elemental Bonuses: Glacio=%d, Fusion=%d, Electro=%d, Aero=%d, Spectro=%d, Havoc=%d\n",
           character.elemental_bonuses[0], character.elemental_bonuses[1], character.elemental_bonuses[2],
           character.elemental_bonuses[3], character.elemental_bonuses[4], character.elemental_bonuses[5]);
    printf("Constellations: %d\n", character.constellations);
    printf("Talents: Basic Attack=%d, Resonance Skills=%d, Forte Circuit=%d, Resonance Liberation=%d, Intro Skill=%d\n",
           character.talents.basic_attack, character.talents.resonance_skill, character.talents.forte_circuit,
           character.talents.resonance_liberation, character.talents.intro_skill);
    printf("Basic Skills: Left=%d, Center Left=%d, Center Right=%d, Right=%d\n",
           character.talents.basic_skills[0], character.talents.basic_skills[1], character.talents.basic_skills[2],
           character.talents.basic_skills[3]);
    printf("Inherent Skills: %d, %d\n", character.talents.inherent_skills[0], character.talents.inherent_skills[1]);

    free_character(&character);
    return 0;
}