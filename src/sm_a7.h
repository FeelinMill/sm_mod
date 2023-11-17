#pragma once

//#define kKraid_BgTargetPalette6 ((uint16*)RomFixedPtr(0xa786c7))
//#define kKraid_BgTargetPalette3 ((uint16*)RomFixedPtr(0xa7aaa6))
//#define kEproj_RocksFallingKraidCeilingXPositions ((uint16*)RomFixedPtr(0xa7acb3))
//#define kKraid_InvulnerableRoarInstrLists (*(KraidInstrList*)RomFixedPtr(0xa796d2))
//#define kKraid_VulnerableRoarInstrLists (*(KraidInstrList*)RomFixedPtr(0xa796da))
//#define kKraid_BodyHitboxTable ((uint16*)RomFixedPtr(0xa7b161))
//#define kKraid_BgPalette7 ((uint16*)RomFixedPtr(0xa7b3d3))
//#define kKraid_BgPalette7_KraidDeath ((uint16*)RomFixedPtr(0xa7b4f3))
//#define kKraid_SprPalette7 ((uint16*)RomFixedPtr(0xa7b513))
//#define kKraid_EyeGlowingInstrLists ((KraidInstrList*)RomFixedPtr(0xa7974a))
//#define kKraid_DyingInstrLists ((KraidInstrList*)RomFixedPtr(0xa79764))
//#define kKraid_LintBoundary (*(Hitbox*)RomFixedPtr(0xa792b7))
//#define kKraid_XMovementTable ((uint16*)RomFixedPtr(0xa7ba7d))
//#define kEproj_RocksKraidSpits_RandomParameters ((uint16*)RomFixedPtr(0xa7bc65))
//#define kKraid_GoodFingernailInstrLists (*(SpriteDrawInstr*)RomFixedPtr(0xa78b0a))
//#define kKraidsFingernail_UpwardsVelocityTable ((uint16*)RomFixedPtr(0xa7be3e))
//#define kKraidsFingernail_DownwardsVelocityTable ((uint16*)RomFixedPtr(0xa7be46))
//#define kKraidsFingernail_BoundaryOffsets ((uint16*)RomFixedPtr(0xa7bf1d))
//#define kKraidSinkEntry ((KraidSinkTable*)RomFixedPtr(0xa7c5e7))
//#define kPhantoon_InstrListPtrs ((uint16*)RomFixedPtr(0xa7ce8e))
//#define kPhantoon_MaterialisationSoundEffects ((uint16*)RomFixedPtr(0xa7cded))
//#define kPhantoon_BrokenCode ((ExtendedSpriteMap*)RomFixedPtr(0xa7902d))
//#define kEproj_DestroyableFireballs_Positions ((uint8*)RomFixedPtr(0xa7cfc2))
//#define kPhantoon_CasualFlameTimerPtrs ((uint16*)RomFixedPtr(0xa7ccfd))
//#define kPhantoon_Figure8VulnerabilityTimers ((uint16*)RomFixedPtr(0xa7cd41))
//#define kPhantoon_EyeClosedTimers ((uint16*)RomFixedPtr(0xa7cd53))
//#define kPhantoon_FireballRainHidingTimers ((uint16*)RomFixedPtr(0xa7cd63))
//#define kPhantoon_EyeballDirectionInstrListPtrs ((uint16*)RomFixedPtr(0xa7d40d))
//#define kPhantoon_FlameRainSpawnPositions ((uint16*)RomFixedPtr(0xa7cdad))
//#define kPhantoon_DyingExplosionsTable ((uint8*)RomFixedPtr(0xa7da1d))
//#define kPhantoon_HealthPalettePtrs ((uint16*)RomFixedPtr(0xa7dc4a))
//#define kDachora_PalettePtrs_1 ((uint16*)RomFixedPtr(0xa7f787))
//#define kDachora_PalettePtrs_2 ((uint16*)RomFixedPtr(0xa7f92d))
//#define kPhantoon_FadeOutTargetPalettes ((uint16*)RomFixedPtr(0xa7ca41))
//#define kWreckedShipOn_Bg1AndBg2TargetPalettes ((uint16*)RomFixedPtr(0xa7ca61))
//#define kSpritePaletteRamPtrs ((uint16*)RomFixedPtr(0xa7f55f))

uint16 kKraid_BgTargetPalette6[] = {
   0x400, 0x2d6b, 0x2d6b, 0x2d6b, 0x1986, 0x14c2,  0x840,  0x400, 0x31ed, 0x18c6, 0x10c3,  0x420,  0x252, 0x2d6b, 0x4a52,    0x0,
};

uint16 kKraid_BgTargetPalette3[] = {
     0x0,    0x0,    0x0,    0x0,    0x0,  0xdf6,  0xd92,  0xcec,  0xca9,    0x0,    0x0,    0x0,    0x0,    0x0,    0x0,    0x0,
};

uint16 kEproj_RocksFallingKraidCeilingXPositions[] = {
    104,   216,    40,   168,    88,   200,    56,   184,    72,
};

KraidInstrList kKraid_InvulnerableRoarInstrLists = {    10, 0x97c8, 0x9788, 0xffff, };

KraidInstrList kKraid_VulnerableRoarInstrLists = {    0xa, };

uint16 kKraid_BodyHitboxTable[] = {
   0x3ff, 0xffd0, 
    0x10, 0xffd0, 
     0x0, 0xffe0, 
  0xffe0, 0xffe8, 
  0xffd0, 0xfff8, 
  0xffb0,    0x0, 
  0xff90,    0x8, 
  0x8000,    0x8,
};

uint16 kKraid_BgPalette7[] = {
  0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff,
};

uint16 kKraid_BgPalette7_KraidDeath[] = {
  0x3800,  0x807,  0x404,    0x0, 0x127a,  0xe17,  0xdd3,  0x970,  0x92d,  0x4ca,  0x486,   0x23,  0x443, 0x3e52, 0x4ad5,    0x0,
};

uint16 kKraid_SprPalette7[] = {
  0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff,
};

KraidInstrList kKraid_EyeGlowingInstrLists[] = {
      5, 0x97c8, 0x9788, 0xffff, 
     10, 0x9ac8, 0x9790, 0x97b0, 
      5, 0x97c8, 0x9788, 0xffff, 
  0xffff,
};

KraidInstrList kKraid_DyingInstrLists[] = {
     25, 0x97c8, 0x9788, 0xffff, 
     25, 0x9ac8, 0x9790, 0x97b0, 
     25, 0x9dc8, 0x9798, 0x97b8, 
  44959,   0x40, 0xa0c8, 0x97a0, 
  0x97c0,
};

Hitbox kKraid_LintBoundary = { 0xffe8, 0xfffc,    0x4,    0x6, 0x948b, 0x94b5, };

uint16 kKraid_XMovementTable[] = {
    0xf0, 0xba95, 
   0x160, 0xbaa9, 
   0x180, 0xbabd, 
    0xd0, 0xbad1, 
   0x140, 0xbae5, 
   0x170, 0xbaf9,
};

uint16 kEproj_RocksKraidSpits_RandomParameters[] = {
  0xfc00, 0xfc40, 0xfb40, 0xfb80, 0xfb40, 0xfc00, 0xfb80, 0xfc40,
};

SpriteDrawInstr kKraid_GoodFingernailInstrLists = {     3, 0xa617, };

uint16 kKraidsFingernail_UpwardsVelocityTable[] = {
  0xbe4e, 0xbe5e, 0xbe6e, 0xbe7e,
};

uint16 kKraidsFingernail_DownwardsVelocityTable[] = {
  0xbe56, 0xbe66, 0xbe76, 0xbe86,
};

uint16 kKraidsFingernail_BoundaryOffsets[] = {
  0xffc0,   0x10, 
  0xffd8, 0xffd8, 
  0xfff0, 0xffa0, 
     0x8, 0xff80,
};

KraidSinkTable kKraidSinkEntry[] = {
   0x130,  0x8a0, 0xc691, 
   0x138,  0x880, 0xc6a6, 
   0x140,  0x860, 0xc6a6, 
   0x148,  0x840, 0xc6a7, 
   0x150,  0x820, 0xc6a6, 
   0x158,  0x800, 0xc6a6, 
   0x160,  0x3e0, 0xc6bd, 
   0x168,  0x3c0, 0xc6a6, 
   0x170,  0x3a0, 0xc6a6, 
   0x178,  0x380, 0xc6a6, 
   0x180,  0x360, 0xc6d3, 
   0x188,  0x340, 0xc6a6, 
   0x190,  0x320, 0xc6a6, 
   0x198,  0x300, 0xc6e9, 
   0x1a0,  0x2e0, 0xc6a6, 
   0x1a8,  0x2c0, 0xc6a6, 
   0x1b0,  0x2a0, 0xc6ff, 
   0x1b8,  0x280, 0xc6a6, 
   0x1c0,  0x260, 0xc6a6, 
   0x1c8,  0x240, 0xc6a6, 
   0x1d0,  0x220, 0xc6a6, 
   0x1d8,  0x200, 0xc6a6, 
   0x1e0,  0x1e0, 0xc6a6, 
   0x1e8,  0x1c0, 0xc6a6, 
   0x1f0,  0x1a0, 0xc6a6, 
   0x1f8,  0x180, 0xc6a6, 
   0x200,  0x160, 0xc6a6, 
   0x208,  0x140, 0xc6a6, 
  0xffff,
};

uint16 kPhantoon_InstrListPtrs[] = {
  0xcc41, 0xcc7b, 0xccd7, 0xccf7,
};

uint16 kPhantoon_MaterialisationSoundEffects[] = {
    0x79,   0x7a,   0x7b,
};

ExtendedSpriteMap kPhantoon_BrokenCode[] = {
  0xffd4,    0x8, 0x9507, 0x9321, 
  0xffdb,    0x2, 0x9539, 0x937f, 
     0x0,    0x0, 0x9579, 0x9411, 
  0xffd2,    0x4, 0x9507, 0x9321, 
  0xffd9, 0xfffe, 0x9539, 0x937f,
};

uint8 kEproj_DestroyableFireballs_Positions[] = {
    5,   7,   0,   7,   5,   3,   1,   3,
};

uint16 kPhantoon_CasualFlameTimerPtrs[] = {
  0xcd05, 0xcd13, 0xcd1d, 0xcd2f,
};

uint16 kPhantoon_Figure8VulnerabilityTimers[] = {
     60,    30,    15,    30,    60,    30,    15,    60,
};

uint16 kPhantoon_EyeClosedTimers[] = {
    720,    60,   360,   720,   360,    60,   360,   720,
};

uint16 kPhantoon_FireballRainHidingTimers[] = {
     60,   120,    30,    60,    30,    60,    30,    30,
};

uint16 kPhantoon_EyeballDirectionInstrListPtrs[] = {
  0xcca7, 0xccad, 0xccb3, 0xccb9, 0xccbf, 0xccbf, 0xccc5, 0xcccb, 0xccd1, 0xcca7,
};

uint16 kPhantoon_FlameRainSpawnPositions[] = {
      1,   128,    96,     0, 
     71,   168,    64,     0, 
    136,   208,    96,     0, 
    201,   168,   128,     0, 
      1,   128,    96,     0, 
    334,    88,    64,     0, 
    399,    48,    96,     0, 
    465,    88,   128,     0,
};

uint8 kPhantoon_DyingExplosionsTable[] = {
    0,   0,  29,  16, 
   32, 224,  29,  16, 
  224,  32,  29,  16, 
  224, 224,  29,  16, 
   32,  32,  29,  32, 
  224, 248,  29,   8, 
    0,   0,   3,   8, 
   32, 248,  29,   8, 
    0,   0,   3,   8, 
    0,  24,   3,   8, 
    0,  48,  29,   8, 
  232,  24,   3,   8, 
   24,  24,   3,   8,
};

uint16 kPhantoon_HealthPalettePtrs[] = {
  0xcb41, 0xcb61, 0xcb81, 0xcba1, 0xcbc1, 0xcbe1, 0xcc01, 0xcc21,
};

uint16 kDachora_PalettePtrs_1[] = {
  0xf245, 0xf265, 0xf285, 0xf2a5,
};

uint16 kDachora_PalettePtrs_2[] = {
  0xf2c5, 0xf2e5, 0xf305, 0xf325,
};

uint16 kPhantoon_FadeOutTargetPalettes[] = {
      0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
};

uint16 kWreckedShipOn_Bg1AndBg2TargetPalettes[] = {
     0x0,  0x2df,  0x1d7,   0xac, 0x5ebb, 0x3db3, 0x292e, 0x1486,  0xbb1, 0x48fb, 0x7fff,    0x0, 0x7fff, 0x44e5, 0x7fff,    0x0, 
  0x2003,  0xbb1, 0x1ea9,  0x145, 0x5ebb, 0x3db3, 0x292e, 0x1486, 0x6318, 0x1ce7, 0x1084,    0x0, 0x7fff,  0x2df,   0x1f,    0x0, 
  0x2003, 0x72bc, 0x48fb, 0x1816, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x7fff,    0x0, 
     0x0, 0x72b2, 0x71c7, 0x4d03, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x7fff,    0x0, 
     0x0, 0x3ef4, 0x262e,  0xd68, 0x3e94, 0x25ce,  0xd08, 0x1484, 0x6e94, 0x55ce, 0x3d08, 0x2c84, 0x1ea9,  0xbb1, 0x7fff,    0x0, 
     0x0, 0x1246,  0x145,   0xc0, 0x3652, 0x1d8c,  0x4c6,  0x484, 0x6231, 0x496b, 0x30a5, 0x2021,   0x15,  0x25b, 0x7fff,    0x0, 
     0x0, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x6318, 0x7fff,    0x0,
};

uint16 kSpritePaletteRamPtrs[] = {
  0xc100, 0xc120, 0xc140, 0xc160, 0xc180, 0xc1a0, 0xc1c0, 0xc1e0,
};


