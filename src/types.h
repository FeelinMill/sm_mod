#ifndef SM_TYPES_H_
#define SM_TYPES_H_

#include <stdint.h>
#include <stdbool.h>

#if defined(_WIN32) && !COMPILER_TCC
#include <crtdbg.h>
#define assert _ASSERTE
#else
#include <assert.h>
#endif


typedef uint8_t uint8;
typedef int8_t int8;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint32_t uint32;
typedef int32_t int32;
typedef uint64_t uint64;
typedef int64_t int64;
typedef unsigned int uint;

typedef uint16 VoidP;

#define arraysize(x) (sizeof(x)/sizeof(x[0]))
#define arrayend(x) (sizeof(x)/sizeof(x[0]) - 1)
#define sign8(x) ((x) & 0x80)  // 0 if positive, 1 if negative
#define sign16(x) ((x) & 0x8000)  // 0 if positive, 1 if negative
#define sign32(x) ((x) & 0x80000000)  // 0 if positive, 1 if negative
#define load24(x) ((*(uint32*)&(x))&0xffffff)

#ifdef _MSC_VER
#pragma warning(disable: 4244)
#define countof _countof
#define NORETURN __declspec(noreturn)
#define FORCEINLINE __forceinline
#define NOINLINE __declspec(noinline)
#else
#define countof(a) (sizeof(a)/sizeof(*(a)))
#define NORETURN
#define FORCEINLINE inline
#define NOINLINE
#endif

#ifdef _DEBUG
#define kDebugFlag 1
#else
#define kDebugFlag 0
#endif

static FORCEINLINE uint16 abs16(uint16 t) { return sign16(t) ? -t : t; }
static FORCEINLINE uint8 abs8(uint8 t) { return sign8(t) ? -t : t; }
static FORCEINLINE int IntMin(int a, int b) { return a < b ? a : b; }
static FORCEINLINE int IntMax(int a, int b) { return a > b ? a : b; }
static FORCEINLINE uint UintMin(uint a, uint b) { return a < b ? a : b; }
static FORCEINLINE uint UintMax(uint a, uint b) { return a > b ? a : b; }

// windows.h defines this too
#ifdef HIBYTE
#undef HIBYTE
#endif

#define BYTE(x) (*(uint8*)&(x))
#define WORD(x) (*(uint16*)&(x))
#define DWORD(x) (*(uint32*)&(x))
#define XY(x, y) ((y)*64+(x))

static inline uint16 swap16(uint16 v) { return (v << 8) | (v >> 8); }

void NORETURN Die(const char *error);
void Warning(const char *error);

// compile time assertion
#define __CASSERT_N0__(l) COMPILE_TIME_ASSERT_ ## l
#define __CASSERT_N1__(l) __CASSERT_N0__(l)
#define CASSERT(cnd) typedef char __CASSERT_N1__(__LINE__) [(cnd) ? 1 : -1]

#define USE_COROUTINES 1

typedef uint8_t CoroutineRet;

#define COROUTINE_BEGIN(state_var, start_pos) \
  uint8 *_state_variable_ = &(state_var);     \
  switch(*_state_variable_) {                 \
  case start_pos:

#define COROUTINE_MANUAL_POS(position)        \
  case (position):

#define COROUTINE_AWAIT(position, function)   \
  case (position): {                          \
      uint8 _coret_ = (function);             \
      if (_coret_) {                          \
        *_state_variable_ = (position);       \
        return _coret_;                       \
      }}

#define COROUTINE_AWAIT_ONLY(function)        \
      { uint8 _coret_ = (function);           \
      if (_coret_)                            \
        return _coret_;                       \
      }

#define COROUTINE_END(position)               \
  }                                           \
  *_state_variable_ = (position);             \
  return 0

#define kCoroutineNone 0

#pragma pack(push, 1)
typedef union AnimtilesEntry {
  struct {
    uint16 timer;
    VoidP tile_src;
  };
  struct {
    uint16 func_ptr;
    union {
      struct {
        union {
          struct {
            uint8 boss_bit;
            uint8 area;
          };
          uint16 game_event;
        };
        uint16 instr_list_ptr2;
      };
      uint16 instr_list_ptr1;
      uint16 tourian_statue_state;
      uint16 palette_offset;
      uint16 eproj_param;
      uint16 palfx_id;
    };
  };
} AnimtilesEntry;

/* 18 */
typedef struct Mode7ObjectDef {
    VoidP object_def_ptr;
    VoidP pre_instr;
    VoidP instr_list;
}Mode7ObjectDef;

/* 30 */
typedef struct SamusPoseParams {  // 0x91B629
  uint8 pose_x_dir;
  uint8 movement_type;
  uint8 new_pose_unless_buttons;
  uint8 direction_shots_fired;
  uint8 y_offset_proj_origin_to_gfx;
  uint8 UNUSED_field_5;
  uint8 y_radius;
  uint8 UNUSED_field_7;
} SamusPoseParams;

/* 38 */
typedef union DemoInputEntry {
    struct {
        uint16 timer;
        uint16 cur_input;
        uint16 new_input;
    };
    struct {
        uint16 func_ptr;
        uint16 instr_list_ptr;
    };
} DemoInputEntry;

/* 45 */
typedef union ProjectileInstr {
    struct {
        uint16 timer;
        VoidP spritemap_ptr;
        uint8 x_radius;
        uint8 y_radius;
        uint16 trail_frame;
    };
    struct {
        VoidP func_ptr;
        VoidP instr_list_ptr;
    };
} ProjectileInstr;

/* 90 */
typedef struct LongPtr {
  VoidP addr;
  uint8 bank;
} LongPtr;
#pragma pack (pop)

static inline bool __CFADD__uint16(uint16 x, uint16 y) { return (uint16)(x) > (uint16)(x + y); }
static inline bool __CFADD__uint8(uint8 x, uint8 y) { return (uint8)(x) > (uint8)(x + y); }

typedef struct PairU16 {
  uint16 k, j;
} PairU16;

typedef struct Point16U {
  uint16 x, y;
} Point16U;

typedef struct Rect16U {
  uint16 x, y, w, h;
} Rect16U;

// Some convenience macros to make partial accesses nicer
#define LAST_IND(x,part_type)    (sizeof(x)/sizeof(part_type) - 1)
#define HIGH_IND(x,part_type)  LAST_IND(x,part_type)
#define LOW_IND(x,part_type)   0
// first unsigned macros:
#define BYTEn(x, n)   (*((uint8*)&(x)+n))
#define WORDn(x, n)   (*((uint16*)&(x)+n))

#define LOBYTE(x)  BYTEn(x,LOW_IND(x,uint8))
#define LOWORD(x)  WORDn(x,LOW_IND(x,uint16))
#define HIBYTE(x)  BYTEn(x,HIGH_IND(x,uint8))
#define HIWORD(x)  WORDn(x,HIGH_IND(x,uint16))

#define GET_HIBYTE(x) (((x) & 0xff00) >> 8)

#define PAIR16(high, low) ((uint16)((high) << 8) | (uint8)low)

// Generate a pair of operands.
#define __PAIR32__(high, low)   (((uint32) (high) << 16) | (uint16)(low))
#define IPAIR32(high, low)   ((int32)(( (high) << 16) | (uint16)(low)))

// Helper functions to represent some assembly instructions.

// compile time assertion
#define __CASSERT_N0__(l) COMPILE_TIME_ASSERT_ ## l
#define __CASSERT_N1__(l) __CASSERT_N0__(l)
#define CASSERT(cnd) typedef char __CASSERT_N1__(__LINE__) [(cnd) ? 1 : -1]


#endif  // SM_TYPES_H_

