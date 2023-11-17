#pragma once

//#define kBrinstarRedPipeBug_InstrListPtrs ((uint16*)RomFixedPtr(0xb3882b))
//#define kBrinstarGreenPipeBug_InstrListPtrs ((uint16*)RomFixedPtr(0xb38833))
//#define kBotwoon_HoleHitboxes ((uint16*)RomFixedPtr(0xb3949b))
//#define kBotwoon_SpeedTable ((uint16*)RomFixedPtr(0xb394bb))
//#define kBotwoon_9675PtrsUNUSED ((uint16*)RomFixedPtr(0xb39675))
//#define kBotwoonHealthThresForPalChange ((uint16*)RomFixedPtr(0xb3981b))
//#define kBotwoonHealthBasedPalette ((uint16*)RomFixedPtr(0xb3971b))
//#define kBotwoon_MouthClosedDirectionInstrListPtrs ((uint16*)RomFixedPtr(0xb3946b))
//#define kBotwoon_SpitDirectionInstrListPtrs ((uint16*)RomFixedPtr(0xb3948b))
//#define kEscapeEtecoon_XPositions ((uint16*)RomFixedPtr(0xb3e718))
//#define kEscapeEtecoon_YPositions ((uint16*)RomFixedPtr(0xb3e71e))
//#define kEscapeEtecoon_InstrListPtrs ((uint16*)RomFixedPtr(0xb3e72a))
//#define kEscapeEtecoon_FuncPtrs ((uint16*)RomFixedPtr(0xb3e724))
//#define kEscapeEtecoon_XVelocities ((uint16*)RomFixedPtr(0xb3e730))

uint16 kBrinstarRedPipeBug_InstrListPtrs[] = {
  0x87ab, 0x87cf, 0x87eb, 0x880f,
};

uint16 kBrinstarGreenPipeBug_InstrListPtrs[] = {
  0x8a1d, 0x8a31, 0x8a45, 0x8a59,
};

uint16 kBotwoon_HoleHitboxes[] = {
    0x3c,   0x44,   0x6c,   0x74, 
    0x7c,   0x84,   0xac,   0xb4, 
    0x9c,   0xa4,   0x5c,   0x64, 
    0xdc,   0xe4,   0x8c,   0x94,
};

uint16 kBotwoon_SpeedTable[] = {
      2,    24, 
      3,    16, 
      4,    12,
};

uint16 kBotwoon_9675PtrsUNUSED[] = {
  0xffff,   0xff,  0x1ff,
};

uint16 kBotwoonHealthThresForPalChange[] = {
   0xbb8,  0xa41,  0x8ca,  0x753,  0x5dc,  0x465,  0x2ee,  0x177,
};

uint16 kBotwoonHealthBasedPalette[] = {
     0x0, 0x27e9, 0x1a66, 0x1585,  0xca3, 0x3f9c, 0x2e97, 0x1d72, 0x108e,  0xa5f,  0x9db,  0x956,  0x8d2,  0x82c, 0x7fbd,  0xc05, 
  0x2003, 0x27eb, 0x1a88, 0x15a7,  0xcc4, 0x3b5c, 0x2e58, 0x1d53, 0x106f,  0xe3f,  0xdbb,  0xd36,  0xcd2,  0xc2c, 0x77bd,  0xc06, 
  0x2003, 0x23ed, 0x168a, 0x11c8,  0x8e5, 0x3afd, 0x2a38, 0x1d34, 0x1071,  0xdff,  0xd9b,  0xd36,  0xcb3,  0xc2d, 0x6fde,  0x807, 
     0x0, 0x23ef, 0x16ac, 0x11ea,  0x906, 0x36bd, 0x29f9, 0x1d15, 0x1052, 0x11df, 0x117b, 0x1116, 0x10b3, 0x102d, 0x67de,  0x808, 
     0x0, 0x23f2, 0x12cf, 0x11ec,  0x908, 0x327d, 0x25b9, 0x18d6, 0x1453, 0x11bf, 0x115c, 0x10f7, 0x1093, 0x102e, 0x5fde,  0x408, 
     0x0, 0x23f4, 0x12f1, 0x120e,  0x929, 0x2e3d, 0x257a, 0x18b7, 0x1434, 0x159f, 0x153c, 0x14d7, 0x1493, 0x142e, 0x57de,  0x409, 
     0x0, 0x1ff6,  0xef3,  0xe2f,  0x54a, 0x2dde, 0x215a, 0x1898, 0x1436, 0x155f, 0x151c, 0x14d7, 0x1474, 0x142f, 0x4fff,    0xa, 
     0x0, 0x1ff8,  0xf15,  0xe51,  0x56b, 0x299e, 0x211b, 0x1879, 0x1417, 0x193f, 0x18fc, 0x18b7, 0x1874, 0x182f, 0x47ff,    0xb,
};

uint16 kBotwoon_MouthClosedDirectionInstrListPtrs[] = {
  0x9381, 0x9379, 0x9371, 0x9369, 0x9361, 0x9351, 0x9349, 0x9341, 
  0x9389, 0x9389, 0x9389, 0x9389, 0x9389, 0x9389, 0x9389, 0x9389, 
  0x941f, 0x940f, 0x93ff, 0x93ef, 0x93df, 0x93bf, 0x93af, 0x939f,
};

uint16 kBotwoon_SpitDirectionInstrListPtrs[] = {
  0x941f, 0x940f, 0x93ff, 0x93ef, 0x93df, 0x93bf, 0x93af, 0x939f,
};

uint16 kEscapeEtecoon_XPositions[] = {
    128,   160,   232,
};

uint16 kEscapeEtecoon_YPositions[] = {
    200,   200,   200,
};

uint16 kEscapeEtecoon_InstrListPtrs[] = {
  0xe556, 0xe582, 0xe5c6,
};

uint16 kEscapeEtecoon_FuncPtrs[] = {
  0xe680, 0xe680, 0xe670,
};

uint16 kEscapeEtecoon_XVelocities[] = {
  0xfe00,  0x280,    0x0,
};


