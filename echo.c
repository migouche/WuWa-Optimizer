/*
    Stats to identifier:
    0: HP%,
    1: ATK%,
    2: DEF%,
    3: HP,
    4: ATK,
    5: ENERGY REGEN%,
    6: CRIT RATE%,
    7: CRIT DMG%,
    8: HEALING BONUS:
    9: GLACIO DMG BONUS%,
    10: FUSION DMG BONUS%,
    11: ELECTRO DMG BONUS%,
    12: AE DMG BONUS%,
    13: SPECTRO DMG BONUS%,
    14: HAVOC DMG BONUS%,
    15: BASIC ATK DMG BONUS%,
    16: HEAVY ATK DMG BONUS%,
    17: RESONANCE SKILL DMG BONUS%,
    18: RESONANCE LIBERATION DMG BONUS%,
    19: DEF,
*/

#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char* name;
    int element;

    int main_stat;

    int roll_1_id;
    float roll_1_value;

    int roll_2_id;
    float roll_2_value;

    int roll_3_id;
    float roll_3_value;

    int roll_4_id;
    float roll_4_value;

    int roll_5_id;
    float roll_5_value;
} Echo;

// ...existing code...

int stat_string_to_id(const char* stat) {
    if (strcmp(stat, "HP%") == 0) return 0;
    if (strcmp(stat, "ATK%") == 0) return 1;
    if (strcmp(stat, "DEF%") == 0) return 2;
    if (strcmp(stat, "HP") == 0) return 3;
    if (strcmp(stat, "ATK") == 0) return 4;
    if (strcmp(stat, "ENERGY REGEN%") == 0) return 5;
    if (strcmp(stat, "CRIT RATE%") == 0) return 6;
    if (strcmp(stat, "CRIT DMG%") == 0) return 7;
    if (strcmp(stat, "HEALING BONUS") == 0) return 8;
    if (strcmp(stat, "GLACIO DMG BONUS%") == 0) return 9;
    if (strcmp(stat, "FUSION DMG BONUS%") == 0) return 10;
    if (strcmp(stat, "ELECTRO DMG BONUS%") == 0) return 11;
    if (strcmp(stat, "AE DMG BONUS%") == 0) return 12;
    if (strcmp(stat, "SPECTRO DMG BONUS%") == 0) return 13;
    if (strcmp(stat, "HAVOC DMG BONUS%") == 0) return 14;
    if (strcmp(stat, "BASIC ATK DMG BONUS%") == 0) return 15;
    if (strcmp(stat, "HEAVY ATK DMG BONUS%") == 0) return 16;
    if (strcmp(stat, "RESONANCE SKILL DMG BONUS%") == 0) return 17;
    if (strcmp(stat, "RESONANCE LIBERATION DMG BONUS%") == 0) return 18;
    if (strcmp(stat, "DEF") == 0) return 19;
    return -1; // Unknown stat
}

Echo json_to_echo(char* filename) {
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

    Echo echo;

    echo.name = strdup(cJSON_GetObjectItem(json, "name")->valuestring);
    echo.main_stat = stat_string_to_id(cJSON_GetObjectItem(json, "main_stat")->valuestring);

    cJSON* substats = cJSON_GetObjectItem(json, "substats");
    echo.roll_1_id = stat_string_to_id(cJSON_GetArrayItem(substats, 0)->string);
    echo.roll_1_value = (float)cJSON_GetArrayItem(substats, 0)->valuedouble;
    echo.roll_2_id = stat_string_to_id(cJSON_GetArrayItem(substats, 1)->string);
    echo.roll_2_value = (float)cJSON_GetArrayItem(substats, 1)->valuedouble;
    echo.roll_3_id = stat_string_to_id(cJSON_GetArrayItem(substats, 2)->string);
    echo.roll_3_value = (float)cJSON_GetArrayItem(substats, 2)->valuedouble;
    echo.roll_4_id = stat_string_to_id(cJSON_GetArrayItem(substats, 3)->string);
    echo.roll_4_value = (float)cJSON_GetArrayItem(substats, 3)->valuedouble;
    echo.roll_5_id = stat_string_to_id(cJSON_GetArrayItem(substats, 4)->string);
    echo.roll_5_value = (float)cJSON_GetArrayItem(substats, 4)->valuedouble;

    cJSON_Delete(json);
    free(data);

    return echo;
}

void free_echo(Echo* echo) {
    free(echo->name);
}

int main(){
    Echo echo = json_to_echo("echo.json");
    printf("Name: %s\n", echo.name);
    printf("Main stat: %d\n", echo.main_stat);
    printf("Roll 1: %d, %f\n", echo.roll_1_id, echo.roll_1_value);
    printf("Roll 2: %d, %f\n", echo.roll_2_id, echo.roll_2_value);
    printf("Roll 3: %d, %f\n", echo.roll_3_id, echo.roll_3_value);
    printf("Roll 4: %d, %f\n", echo.roll_4_id, echo.roll_4_value);
    printf("Roll 5: %d, %f\n", echo.roll_5_id, echo.roll_5_value);

    free_echo(&echo);
    return 0;
}
