#pragma once

//#define kUnchargedBeamTrailOffsets ((uint16*)RomFixedPtr(0x9ba4b3))
//#define kChargedBeamTrailOffsets ((uint16*)RomFixedPtr(0x9ba4cb))
//#define kSpazerSbaTrailOffsets ((uint16*)RomFixedPtr(0x9ba4e3))
//#define kDeathSequencePals_SuitOffset_1 ((uint16*)RomFixedPtr(0x9bb5c8))
//#define kDeathSequencePalette_ExplosionTabs ((uint8*)RomFixedPtr(0x9bb823))
//#define kDeathSequencePals_SuitOffset_2 ((uint16*)RomFixedPtr(0x9bb6d2))
////#define kDeathSequencePals_PowerSuit ((uint16*)RomFixedPtr(0x9bb7d3))
////#define kDeathSequencePals_VariaSuit ((uint16*)RomFixedPtr(0x9bb7e7))
////#define kDeathSequencePals_GravitySuit ((uint16*)RomFixedPtr(0x9bb7fb))
//#define kDeathSequencePals_Suitless ((uint16*)RomFixedPtr(0x9bb80f))
//#define kGrappleBlockDefaultConnectionPtrs ((uint16*)RomFixedPtr(0x9bc3c6))
//#define kGrappleBlockVerticalMovementConnectionPtrs ((uint16*)RomFixedPtr(0x9bc3ee))
//#define kGrappleBlockCrouchConnectionPtrs ((uint16*)RomFixedPtr(0x9bc416))
//#define kGrappleBeam_SpecialAngles ((GrappleBeamSpecialAngles*)RomFixedPtr(0x9bc43e))
//#define kGrappleBeam_SwingingData ((uint8*)RomFixedPtr(0x9bc1c2))
//#define kGrappleBeam_SwingingData2 ((uint8*)RomFixedPtr(0x9bc2c2))
//#define kGrappleBeam_SwingingData3 ((uint8*)RomFixedPtr(0x9bc302))
//#define kGrappleBeam_OriginX_NoRun ((uint16*)RomFixedPtr(0x9bc122))
//#define kGrappleBeam_OriginY_NoRun ((uint16*)RomFixedPtr(0x9bc136))
//#define kGrappleBeam_0x0d1a_offs_NoRun ((uint16*)RomFixedPtr(0x9bc14a))
//#define kGrappleBeam_0x0d1c_offs_NoRun ((uint16*)RomFixedPtr(0x9bc15e))
//#define kGrappleBeam_OriginX_Run ((uint16*)RomFixedPtr(0x9bc172))
//#define kGrappleBeam_OriginY_Run ((uint16*)RomFixedPtr(0x9bc186))
//#define kGrappleBeam_0x0d1a_offs_Run ((uint16*)RomFixedPtr(0x9bc19a))
//#define kGrappleBeam_0x0d1c_offs_Run ((uint16*)RomFixedPtr(0x9bc1ae))
//#define kGrappleBeamFlareTileEndPtr (*(uint16*)RomFixedPtr(0x9bc344))
//#define kGrappleBeamFlareTileBeginPtr (*(uint16*)RomFixedPtr(0x9bc342))
//#define kGrappleBeamTilePtrs ((uint16*)RomFixedPtr(0x9bc346))
////#define kFlareAnimDelays ((uint16*)RomFixedPtr(0x90c481))
//#define kFlareAnimDelays_Main ((uint8*)RomFixedPtr(0x90c487))
////#define kFlareAnimDelays_SlowSparks ((uint8*)RomFixedPtr(0x90c4a7))
////#define kFlareAnimDelays_FastSparks ((uint8*)RomFixedPtr(0x90c4ae))
//#define kFlareLeftSpritemapOffsets ((uint16*)RomFixedPtr(0x93a22b))
//#define kFlareRightSpritemapOffsets ((uint16*)RomFixedPtr(0x93a225))
//#define kGrappleToStandingSamusPoses ((uint8*)RomFixedPtr(0x9bc9ba))
//#define kGrappleToCrouchingSamusPoses ((uint8*)RomFixedPtr(0x9bc9c4))
//#define kGrappleBeam_Ext_Xvel ((uint16*)RomFixedPtr(0x9bc0db))
//#define kGrappleBeam_Ext_Yvel ((uint16*)RomFixedPtr(0x9bc0ef))
//#define kGrappleBeam_Init_EndAngle ((uint16*)RomFixedPtr(0x9bc104))

uint16 kUnchargedBeamTrailOffsets[] = {
  0xa50b, 0xa4f7, 0xa50b, 0xa4f7, 0xa50b, 0xa50b, 0xa51f, 0xa533, 0xa50b, 0xa50b, 0xa547, 0xa55b,
};

uint16 kChargedBeamTrailOffsets[] = {
  0xa98f, 0xa9a3, 0xa98f, 0xa9a3, 0xa98f, 0xa98f, 0xa9b7, 0xa9cb, 0xa98f, 0xa98f, 0xa9df, 0xa9f3,
};

uint16 kSpazerSbaTrailOffsets[] = {
     0x0,    0x0,    0x0,    0x0, 0xb37b, 0xb327, 0xb37b,    0x0,    0x0,    0x0,
};

uint16 kDeathSequencePals_SuitOffset_1[] = {
  0xb7d3, 0xb7e7, 0xb7fb,
};

uint8 kDeathSequencePalette_ExplosionTabs[] = {
   21,  0,
    6,  2,
    3,  3,
    4,  4,
    5,  5,
    5,  6,
    6,  7,
    6,  8,
   80,  9,
};

uint16 kDeathSequencePals_SuitOffset_2[] = {
  0xb7d3, 0xb7e7, 0xb7fb,
};

uint16 kDeathSequencePals_Suitless[] = {
  0xa120, 0xa120, 0xa140, 0xa160, 0xa180, 0xa1a0, 0xa1c0, 0xa1e0, 0xa200, 0xa220,
};

uint16 kGrappleBlockDefaultConnectionPtrs[] = {
  0xc79d, 0xb9d9, 
  0xc79d, 0xb9d9, 
  0xc77e, 0xb9ea, 
  0xc77e, 0xb9f3, 
  0xc77e, 0xb9fc, 
  0xc77e, 0xb9fc, 
  0xc77e, 0xb9fc, 
  0xc77e, 0xba05, 
  0xc79d, 0xb9e2, 
  0xc79d, 0xb9e2,
};

uint16 kGrappleBlockVerticalMovementConnectionPtrs[] = {
  0xc79d, 0xb9d9, 
  0xc79d, 0xb9d9, 
  0xc79d, 0xb9d9, 
  0xc79d, 0xb9d9, 
  0xc79d, 0xb9d9, 
  0xc79d, 0xb9e2, 
  0xc79d, 0xb9e2, 
  0xc79d, 0xb9e2, 
  0xc79d, 0xb9e2, 
  0xc79d, 0xb9e2,
};

uint16 kGrappleBlockCrouchConnectionPtrs[] = {
  0xc79d, 0xb9d9, 
  0xc79d, 0xb9d9, 
  0xc77e, 0xba0e, 
  0xc77e, 0xba17, 
  0xc77e, 0xb9fc, 
  0xc77e, 0xb9fc, 
  0xc77e, 0xba20, 
  0xc77e, 0xba29, 
  0xc79d, 0xb9e2, 
  0xc79d, 0xb9e2,
};

GrappleBeamSpecialAngles kGrappleBeam_SpecialAngles[] = {
  0xd680,   0xb6, 0xffe2, 0xffe8, 0xc77e,
  0x2a80,   0xb7,   0x1e, 0xffe8, 0xc77e,
  0xb380,   0xb6, 0xffe4, 0xfff8, 0xc77e,
  0x4d80,   0xb7,   0x1c, 0xfff8, 0xc77e,
  0x6a80,   0xb9,   0x18,   0x10, 0xc814,
  0x9680,   0xb8, 0xffe8,   0x10, 0xc814,
  0x7380,   0xb8, 0xfff8,   0x10, 0xc814,
  0x8d80,   0xb9,    0x8,   0x10, 0xc814,
};

uint8 kGrappleBeam_SwingingData[] = {
    0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   2,   2,   2,   2, 
    2,   2,   2,   2,   3,   3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4, 
    4,   4,   4,   4,   5,   5,   5,   5,   5,   5,   5,   5,   6,   6,   6,   6, 
    6,   6,   6,   6,   7,   7,   7,   7,   7,   7,   7,   7,   8,   8,   8,   8, 
    8,   8,   8,   8,   9,   9,   9,   9,   9,   9,   9,   9,  10,  10,  10,  10, 
   10,  10,  10,  10,  11,  11,  11,  11,  11,  11,  11,  11,  12,  12,  12,  12, 
   12,  12,  12,  12,  13,  13,  13,  13,  13,  13,  13,  13,  14,  14,  14,  14, 
   14,  14,  14,  14,  15,  15,  15,  15,  15,  15,  15,  15,  16,  16,  16,  16, 
   16,  16,  16,  16,  17,  17,  17,  17,  17,  17,  17,  17,  18,  18,  18,  18, 
   18,  18,  18,  18,  19,  19,  19,  19,  19,  19,  19,  19,  20,  20,  20,  20, 
   20,  20,  20,  20,  21,  21,  21,  21,  21,  21,  21,  21,  22,  22,  22,  22, 
   22,  22,  22,  22,  23,  23,  23,  23,  23,  23,  23,  23,  24,  24,  24,  24, 
   24,  24,  24,  24,  25,  25,  25,  25,  25,  25,  25,  25,  26,  26,  26,  26, 
   26,  26,  26,  26,  27,  27,  27,  27,  27,  27,  27,  27,  28,  28,  28,  28, 
   28,  28,  28,  28,  29,  29,  29,  29,  29,  29,  29,  29,  30,  30,  30,  30, 
   30,  30,  30,  30,  31,  31,  31,  31,  31,  31,  31,  31,   0,   0,   0,   0,
};

uint8 kGrappleBeam_SwingingData2[] = {
   0x0,0xf1,  0x7,0xf2,  0xc,0xf5, 0x12,0xf6, 0x16,0xfa, 0x1a, 0x2, 0x1d, 0x5, 0x1f, 0xa, 0x1f,0x11, 0x1e,0x16, 0x1b,0x1b, 0x1a,0x1f, 0x15,0x26, 0x10,0x29, 0x10,0x2c,  0x8,0x2e, 
   0x0,0x2f, 0xf9,0x2e, 0xf4,0x2b, 0xee,0x2a, 0xea,0x26, 0xe6,0x1e, 0xe3,0x1b, 0xe1,0x16, 0xe1, 0xf, 0xe2, 0xa, 0xe5, 0x5, 0xe6, 0x1, 0xeb,0xfa, 0xf0,0xf7, 0xf0,0xf4, 0xf8,0xf2,
};

uint8 kGrappleBeam_SwingingData3[] = {
   0x0,0xf2,  0x9,0xf3, 0x10,0xf6, 0x12,0xf8, 0x15,0xfb, 0x1a, 0x2, 0x1c, 0x6, 0x1e, 0xa, 0x1e,0x10, 0x1e,0x17, 0x1b,0x1c, 0x1a,0x21, 0x15,0x25, 0x10,0x29,  0xb,0x2b,  0x5,0x2d, 
   0x0,0x2e, 0xf7,0x2d, 0xf0,0x2a, 0xee,0x28, 0xeb,0x25, 0xe6,0x1e, 0xe4,0x1a, 0xe2,0x16, 0xe1, 0xf, 0xe2, 0x9, 0xe5, 0x4, 0xe6,0xff, 0xeb,0xfb, 0xf0,0xf7, 0xf5,0xf5, 0xfb,0xf3,
};

uint16 kGrappleBeam_OriginX_NoRun[] = {
     0x2,    0xa,    0x2,    0xa,    0x3, 0xfffc, 0xfff6, 0xfffe, 0xfff6, 0xfffe,
};

uint16 kGrappleBeam_OriginY_NoRun[] = {
  0xfff0, 0xfff4,    0x2,    0x0,    0x6,    0x6,    0x0,    0x2, 0xfff4, 0xfff0,
};

uint16 kGrappleBeam_0x0d1a_offs_NoRun[] = {
     0x2,   0x12,    0xf,   0x11,    0x3, 0xfffc, 0xffef, 0xfff1, 0xffee, 0xfffe,
};

uint16 kGrappleBeam_0x0d1c_offs_NoRun[] = {
  0xffe4, 0xffed,    0x1,    0x6,   0x11,   0x11,    0x6,    0x1, 0xffec, 0xffe4,
};

uint16 kGrappleBeam_OriginX_Run[] = {
     0x2,    0xa,    0x2,    0xa,    0x3, 0xfffc, 0xfff6, 0xfffe, 0xfff6, 0xfffe,
};

uint16 kGrappleBeam_OriginY_Run[] = {
  0xfff0, 0xfff4, 0xfffe,    0x0,    0x6,    0x6,    0x0, 0xfffe, 0xfff4, 0xfff0,
};

uint16 kGrappleBeam_0x0d1a_offs_Run[] = {
     0x2,   0x13,   0x14,   0x12,    0x3, 0xfffc, 0xffee, 0xffec, 0xffed, 0xfffe,
};

uint16 kGrappleBeam_0x0d1c_offs_Run[] = {
  0xffe0, 0xffea, 0xfffd,    0x6,   0x19,   0x19,    0x6, 0xfffd, 0xffec, 0xffe0,
};

uint16 kGrappleBeamFlareTileEndPtr = { 0x8a00, };

uint16 kGrappleBeamFlareTileBeginPtr = { 0x8200, };

uint16 kGrappleBeamTilePtrs[] = {
  0x9220, 0x9220, 0x9220, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x8220, 0x8220, 0x8220, 0x8220, 0x8220, 
  0x8220, 0x8220, 0x8220, 0x8220, 0x8220, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x9220, 0x9220, 0x9220, 
  0x9220, 0x9220, 0x9220, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x8220, 0x8220, 0x8220, 0x8220, 0x8220, 
  0x8220, 0x8220, 0x8220, 0x8220, 0x8220, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x8a20, 0x9220, 0x9220, 0x9220,
};

uint8 kFlareAnimDelays_Main[] = {
    3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3, 
    3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3, 254,  14,
};

uint16 kFlareLeftSpritemapOffsets[] = {
      0,   42,   48,
};

uint16 kFlareRightSpritemapOffsets[] = {
      0,   30,   36,
};

uint8 kGrappleToStandingSamusPoses[] = {
   0x0, 0x1c,  0x0, 0x34,  0x0, 0x1c, 0xf0, 0xe0, 0xe0, 0xc0,
};

uint8 kGrappleToCrouchingSamusPoses[] = {
  0x85, 0x71, 0x27, 0x73, 0x27, 0x28, 0x74, 0x28, 0x72, 0x86,
};

uint16 kGrappleBeam_Ext_Xvel[] = {
     0x0,  0x87c,  0xbf4,  0x87c,    0x0,    0x0, 0xf784, 0xf40c, 0xf784,    0x0,
};

uint16 kGrappleBeam_Ext_Yvel[] = {
  0xf40c, 0xf784,    0x0,  0x87c,  0xbf4,  0xbf4,  0x87c,    0x0, 0xf784, 0xf40c,
};

uint16 kGrappleBeam_Init_EndAngle[] = {
  0x8000, 0xa000, 0xc000, 0xe000,    0x0,    0x0, 0x2000, 0x4000, 0x6000, 0x8000,
};



