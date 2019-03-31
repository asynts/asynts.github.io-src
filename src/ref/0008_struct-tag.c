typedef struct CharacterClass {
    CopyFun copy;
    FreeFun free;
    EqualFun equal;
    ToStringFun to_string;
    AttackFun attack;
    DefenseFun defense;
} CharacterClass;

typedef struct CharacterClass { // here!
    CopyFun copy;
    FreeFun free;
    EqualFun equal;
    ToStringFun to_string;
    AttackFun attack;
    DefenseFun defense;
} WizardClass;

