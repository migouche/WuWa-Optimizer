// This will be the boilerplate for the generated c file to maximize damage


// NOTE: every multiplication is based off a factor, not a percentage

#define AVG_DAMAGE 1
#define CRIT_DAMAGE 2
#define BASE_DAMAGE 3

inline double base_hit_damage(double ability_attribute, double motion_value_factor)
{
    return ability_attribute * motion_value_factor;
}

inline double hit_damage(double base_hit_damage, double resistances, double bonuses){
    return base_hit_damage * resistances * bonuses;
}

inline double calculate_bonuses(double dmg_bonus, double dmg_amplify, double crit_rate, double crit_dmg, unsigned char type){
    switch(type){
        case AVG_DAMAGE: return dmg_bonus * dmg_amplify * crit_rate * crit_dmg;
        case CRIT_DAMAGE: return dmg_bonus * dmg_amplify * crit_dmg;
        case BASE_DAMAGE: return dmg_bonus * dmg_amplify;
        default: return 0;
    }
}

template <typename... Args>
inline double calculate_bonuses(Args... args){ // also works for amplification
    return 1.0 + (args + ...);
}



double damage(int atk, int def, float hp, float er, float crit_rate, float crit_dmg) {
    return 0; // Placeholder
}