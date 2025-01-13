skill_hit = char_atk * char_skill_mult * skill_scaling_bonus
expected_hit = skill_hit * (elemental_dmg_bonus + skill_dmg_bonus) * deepen_efect * (crit_dmg * crit_rate)


/*
aero, glacio, fusion, electro, spectro, havoc
*/

| Stat                  | Rank 2 (LVL 1 - 10) | Rarity 3 (LVL 1 - 15) | Rarity 4 (LVL 1 - 20) | Rarity 5 (LVL 1 - 25) |
|-----------------------|---------------------|-----------------------|-----------------------|-----------------------|
| **1-Cost Echo**        |                     |                       |                 pti      |                       |
| HP%                   | 2.8% - 7.2%         | 3.0% - 10.20%         | 3.4% - 14.2%          | 4.5% - 22.8%          |
| ATK%                  | 2.2% - 5.7%         | 2.4% - 8.1%           | 2.7% - 11.3%          | 3.6% - 18.0%          |
| DEF%                  | 2.2% - 5.7%         | 2.4% - 8.1%           | 2.7% - 11.3%          | 3.6% - 18.0%          |
| HP                    | 114 - 296           | 152 - 516             | 228 - 957             | 456 - 2280            |
| **3-Cost Echo**        |                     |                       |                       |                       |
| HP%                   | 3.7% - 9.6%         | 4.0% - 14.0%          | 4.5% - 18.9%          | 6.0% - 30%            |
| ATK%                  | 3.7% - 9.6%         | 4.0% - 14.0%          | 4.5% - 18.9%          | 6.0% - 30%            |
| DEF%                  | 4.7% - 12.3%        | 5.0% - 17%            | 5.7% - 23.9%          | 7.6% - 38%            |
| Glacio DMG Bonus       | 3.7% - 9.6%         | 4.0% - 14%            | 4.5% - 18.9%          | 6.0% - 30%            |
| Fusion DMG Bonus       | 3.7% - 9.6%         | 4.0% - 14%            | 4.5% - 18.9%          | 6.0% - 30%            |
| Electro DMG Bonus      | 3.7% - 9.6%         | 4.0% - 14%            | 4.5% - 18.9%          | 6.0% - 30%            |
| Aero DMG Bonus         | 3.7% - 9.6%         | 4.0% - 14%            | 4.5% - 18.9%          | 6.0% - 30%            |
| Spectro DMG Bonus      | 3.7% - 9.6%         | 4.0% - 14%            | 4.5% - 18.9%          | 6.0% - 30%            |
| Havoc DMG Bonus        | 3.7% - 9.6%         | 4.0% - 14%            | 4.5% - 18.9%          | 6.0% - 30%            |
| Energy Regen           | - 10%               | 4.2% - 14.2%          | 4.8% - 20.1%          | 6.4% - 32.0%          |
| ATK                   | 12 - 31             | 13 - 44               | 15 - 63               | 20 - 100              |
| **4-Cost Echo**        |                     |                       |                       |                       |
| ATK                   | 18 - 46             | 20 - 68               | 22 - 92               | 30 - 150              |
| HP%                   | 4.1% - 10.6%        | 4.3% - 14.6%          | 4.9% - 20.5%          | 6.6% - 33.0%          |
| ATK%                  | 4.1% - 10.6%        | 4.3% - 14.6%          | 4.9% - 20.5%          | 6.6% - 33.0%          |
| DEF%                  | 5.2% - 13.5%        | 5.5% - 18.7%          | 6.2% - 26.0%          | 8.3% - 41.5%          |
| Crit. Rate             | 2.7% - 7.1%         | 2.9% - 9.8%           | 3.3% - 13.8%          | 4.4% - 22.0%          |
| Crit. DMG              | 5.4% - 14.3%        | 5.8% - 19.7%          | 6.6% - 27.7%          | 8.5% - 36.3%          |
| Healing Bonus          | - 8.5%              | 3.5% - 11.9%          | 3.9% - 16.3%          | 5.2% - 26.0%          |



Substats are supposed to follow Gaussian distribution with the following parameters:

| Substat                      | Range of Values | Median Value |
|------------------------------|-----------------|--------------|
| ATK                          | 30 - 70         | 50           |
| HP                           | 320 - 580       | 450          |
| DEF                          | 30 - 70         | 50           |
| ATK%                         | 6.4% - 11.6%    | 9.0%         |
| HP%                          | 6.4% - 11.6%    | 9.0%         |
| DEF%                         | 8.1% - 14.7%    | 11.39%       |
| Energy Regen                 | 5.6% - 14.9%    | 10.25%       |
| Crit. Rate                   | 6.3% - 10.5%    | 8.4%         |
| Crit. DMG                    | 12.6% - 21.0%   | 16.8%        |
| Basic Attack DMG Bonus        | 6.4% - 11.6%    | 9.0%         |
| Heavy Attack DMG Bonus        | 6.4% - 11.6%    | 9.0%         |
| Resonance Skill DMG Bonus     | 6.4% - 11.6%    | 9.0%         |
| Resonance Liberation DMG Bonus| 6.4% - 11.6%    | 9.0%         |

## Format

### Echoes


we will assume lvl 25 for now

```json
{
    name: "Name", // Not used by optimizer
    main_stat: "HP%", // HP%, ATK%, DEF%, Crit. Rate, Crit. DMG, Healing Bonus
    substats: {
        "HP%": 4.5,
        "ATK%": 6.0,
        "DEF%": 7.6,
        "Crit. Rate": 4.4,
        "Crit. DMG": 8.5,
        "Healing Bonus": 5.2
    },
}
```

### Characters

We will assume lvl 90 for now

```json
{
    name: "Spectro Rover", // Not used by optimizer
    base_stats: {
        "HP": 11400,
        "ATK": 375,
        "DEF": 100,
        "Energy Regen": 10,
        "Crit. Rate": 5,
        "Crit. DMG": 150,
        "Healing Bonus": 0,
        "Max Energy": 100
    },
    elemental_bonuses: {
        "Glacio": 0,
        "Fusion": 0,
        "Electro": 0,
        "Aero": 0,
        "Spectro": 0,
        "Havoc": 0
    },
    constellations: 0,
    talents: {
        basic_attack: {
            level: 10, // 1 - 10
        },
        resonance_skilsl: {
            level: 10, // 1 - 10
        },
        forte_circuit: {
            level: 10, // 1 - 10
        },
        resonance_liberation: {
            level: 10, // 1 - 10
        },
        intro_skill: {
            level: 10, // 1 - 10
        },
        basic_skills{
            left: {
                true, false // two levels
            },
            center_left: {
                true, false // two levels
            },
            center_right: {
                true, false // two levels
            },
            right: {
                true, false // two levels
            },
        }
        inherent_skills{
            true, true // two levels
        }
    }
}
```
