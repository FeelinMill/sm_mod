// Aran

#include <stddef.h>
#include <string.h>

#include "ida_types.h"
#include "variables.h"
#include "funcs.h"
#include "sm_rtl.h"
#include "sm_91.h"


static void CopyRevealedBlockToXrayBg2(uint16 dst_r22, const uint8 *jp);
static void CopyBlockToXrayBg2(uint16 dst_r22, uint16 j);
static void CopyRevealedBlockToXrayBg2OneBlockRight(uint16 dst_r22, const uint8 *jp);
static void CopyRevealedBlockToXrayBg2OneBlockDown(uint16 dst_r22, const uint8 *jp);
static void CopyFlippedBlockToXrayBg1(uint16 dst_r22, uint16 j);

typedef struct Pair_R18_R20 {
  uint16 r18, r20;
} Pair_R18_R20;

Pair_R18_R20 TranslateCustomControllerBindingsToDefault(void);


static Func_V *const kSamusInputHandlers[28] = {
  Samus_Input_00_Standing,
  Samus_Input_01_Running,
  Samus_Input_02_NormalJumping,
  Samus_Input_03_SpinJumping,
  Samus_Input_04_MorphBallOnGround,
  Samus_Input_05_Crouching,
  Samus_Input_06_Falling,
  Samus_Input_07_Unused,
  Samus_Input_08_MorphBallFalling,
  Samus_Input_09_Unused,
  Samus_Input_0A_KnockbackOrCrystalFlashEnding,
  Samus_Input_0B_Unused,
  Samus_Input_0C_Unused,
  Samus_Input_0D_Unused,
  Samus_Input_0E_TurningAroundOnGround,
  Samus_Input_0F_CrouchingEtcTransition,
  Samus_Input_10_Moonwalking,
  Samus_Input_11_SpringBallOnGround,
  Samus_Input_12_SpringBallInAir,
  Samus_Input_13_SpringBallFalling,
  Samus_Input_14_WallJumping,
  Samus_Input_15_RanIntoWall,
  Samus_Input_16_Grappling,
  Samus_Input_17_TurningAroundJumping,
  Samus_Input_18_TurningAroundFalling,
  Samus_Input_19_DamageBoost,
  Samus_Input_1A_GrabbedByDraygon,
  Samus_Input_1B_ShinesparkEtc,
};
void Samus_InputHandler(void) {  // 0x918000
  kSamusInputHandlers[samus_movement_type]();
}

void Samus_Input_00_Standing(void) {  // 0x91804D
  if (samus_pose && samus_pose != kPose_9B_FaceF_VariaGravitySuit || elevator_status == kElevatorStatus_Inactive)
    Samus_LookupTransitionTable();
}

void Samus_Input_01_Running(void) {  // 0x918066
  Samus_LookupTransitionTable();
}

void Samus_Input_02_NormalJumping(void) {  // 0x91806E
  Samus_LookupTransitionTable();
}

void Samus_Input_03_SpinJumping(void) {  // 0x918076
  Samus_LookupTransitionTable();
}

void Samus_Input_04_MorphBallOnGround(void) {  // 0x91807E
  Samus_LookupTransitionTable();
}

void Samus_Input_07_Unused(void) {  // 0x918086
  ;
}

void Samus_Input_05_Crouching(void) {  // 0x918087
  if (time_is_frozen_flag) {
    XraySamusPostInputHandler();
  } else {
    Samus_LookupTransitionTable();
    if (samus_movement_type == kMovementType_00_Standing) {
      samus_y_pos -= 5;
      samus_prev_y_pos -= 5;
    }
  }
}

void Samus_Input_06_Falling(void) {  // 0x9180B6
  Samus_LookupTransitionTable();
}

void Samus_Input_08_MorphBallFalling(void) {  // 0x91810A
  Samus_LookupTransitionTable();
}

void Samus_Input_09_Unused(void) {  // 0x918112
  ;
}

void Samus_Input_0A_KnockbackOrCrystalFlashEnding(void) {  // 0x918113
  Samus_LookupTransitionTable();
  if (samus_movement_type != kMovementType_0A_KnockbackOrCrystalFlashEnding) {
    Samus_InitJump();
    samus_knockback_timer = 0;
  }
}

void Samus_Input_0B_Unused(void) {  // 0x91812D
  ;
}

void Samus_Input_0C_Unused(void) {  // 0x918132
  Samus_LookupTransitionTable();
}

void Samus_Input_0D_Unused(void) {  // 0x91813A
  Samus_LookupTransitionTable();
}

void Samus_Input_0E_TurningAroundOnGround(void) {  // 0x918142
  Samus_LookupTransitionTable();
}

void Samus_Input_0F_CrouchingEtcTransition(void) {  // 0x918146
  ;
}

void Samus_Input_10_Moonwalking(void) {  // 0x918147
  Samus_LookupTransitionTable();
}

void Samus_Input_11_SpringBallOnGround(void) {  // 0x91814F
  Samus_LookupTransitionTable();
}

void Samus_Input_12_SpringBallInAir(void) {  // 0x918157
  Samus_LookupTransitionTable();
}

void Samus_Input_13_SpringBallFalling(void) {  // 0x91815F
  Samus_LookupTransitionTable();
}

void Samus_Input_14_WallJumping(void) {  // 0x918167
  Samus_LookupTransitionTable();
}

void Samus_Input_15_RanIntoWall(void) {  // 0x91816F
  if (time_is_frozen_flag)
    XraySamusPostInputHandler();
  else
    Samus_LookupTransitionTable();
}

void Samus_Input_16_Grappling(void) {  // 0x918181
  Samus_LookupTransitionTable();
}

void Samus_Input_17_TurningAroundJumping(void) {  // 0x918189
  Samus_LookupTransitionTable();
}

void Samus_Input_18_TurningAroundFalling(void) {  // 0x91818D
  Samus_LookupTransitionTable();
}

void Samus_Input_19_DamageBoost(void) {  // 0x918191
  Samus_LookupTransitionTable();
}

void Samus_Input_1A_GrabbedByDraygon(void) {  // 0x918199
  Samus_LookupTransitionTable();
}

void Samus_Input_1B_ShinesparkEtc(void) {  // 0x9181A1
  Samus_LookupTransitionTable();
}

void Samus_LookupTransitionTable(void) {  // 0x9181A9
  if (joypad1_lastkeys != 0) {
    Pair_R18_R20 pair = TranslateCustomControllerBindingsToDefault();
    const PoseEntry *pe = get_PoseEntry(samus_pose);
    if (pe->new_input == 0xFFFF)
      return;
    do {
      if ((pair.r18 & pe->new_input) == 0 && (pair.r20 & pe->cur_input) == 0) {
        if (pe->new_pose != samus_pose) {
          samus_new_pose = pe->new_pose;
          bomb_jump_dir = kBombJumpDir_None;
        }
        return;
      }
      pe++;
    } while (pe->new_input != 0xFFFF);
  }
  UNUSED_word_7E0A18 = 0;
  Samus_LookupTransitionTableFailureHandler();
}

Pair_R18_R20 TranslateCustomControllerBindingsToDefault(void) {  // 0x9181F4
  uint16 default_newkeys = joypad1_newkeys & (kButton_Up | kButton_Down | kButton_Left | kButton_Right);
  uint16 default_lastkeys = joypad1_lastkeys & (kButton_Up | kButton_Down | kButton_Left | kButton_Right);
  uint16 custom_newkeys = joypad1_newkeys;
  uint16 custom_lastkeys = joypad1_lastkeys;

  if (custom_newkeys & button_config_shoot)
    default_newkeys |= kButton_X;
  if (custom_newkeys & button_config_jump)
    default_newkeys |= kButton_A;
  if (custom_newkeys & button_config_run)
    default_newkeys |= kButton_B;
  if (custom_newkeys & button_config_itemcancel)
    default_newkeys |= kButton_Y;
  if (custom_newkeys & button_config_aim_up) {
    if (button_config_aim_up & (kButton_L | kButton_R))
      default_newkeys |= kButton_R;
  }
  if (custom_newkeys & button_config_aim_down) {
    if (button_config_aim_down & (kButton_L | kButton_R))
      default_newkeys |= kButton_L;
  }

  if (custom_lastkeys & button_config_shoot)
    default_lastkeys |= kButton_X;
  if (custom_lastkeys & button_config_jump)
    default_lastkeys |= kButton_A;
  if (custom_lastkeys & button_config_run)
    default_lastkeys |= kButton_B;
  if (custom_lastkeys & button_config_itemcancel)
    default_lastkeys |= kButton_Y;
  if (custom_lastkeys & button_config_aim_up) {
    if (button_config_aim_up & (kButton_L | kButton_R))
      default_lastkeys |= kButton_R;
  }
  if (custom_lastkeys & button_config_aim_down) {
    if (button_config_aim_down & (kButton_L | kButton_R))
      default_lastkeys |= kButton_L;
  }

  return (Pair_R18_R20) { ~default_newkeys, ~default_lastkeys };
}

void Samus_LookupTransitionTableFailureHandler(void) {  // 0x9182D9
  if (SetNewPoseCommand() & 1 || kPoseParams[samus_pose].new_pose_unless_buttons == 0xFF)
    samus_new_pose = samus_pose;
  else
    samus_new_pose = kPoseParams[samus_pose].new_pose_unless_buttons;
}

static const uint8 kSamus_Pose_Func2_Tab[28] = {  // 0x918304
  2, 1, 1, 0, 6, 2, 8, 2, 1, 6, 2, 2, 2, 6, 2, 2,
  2, 6, 6, 6, 6, 2, 6, 2, 2, 2, 2, 2,
};

uint8 SetNewPoseCommand(void) {

  uint16 v0 = kSamus_Pose_Func2_Tab[samus_movement_type];
  if (v0 != 1)
    goto LABEL_2;
  if (!samus_x_base_speed && !samus_x_base_subspeed) {
    v0 = 2;
LABEL_2:
    samus_new_pose_command = v0;
    return 0;
  }
  samus_new_pose_command = 1;
  return 1;
}

void EnableDemoInput(void) {  // 0x91834E
  samus_input_handler = FUNC16(Samus_InputHandler_Demo);
  demo_enable |= 0x8000;
}

void DisableDemoInput(void) {  // 0x91835F
  samus_input_handler = FUNC16(Samus_InputHandler_Normal);
  demo_enable &= ~0x8000;
}

void ResetDemoData(void) {  // 0x918370
  demo_input_pre_instr = 0;
  demo_input_instr_timer = 0;
  demo_input_instr_ptr = 0;
  demo_timer_counter = 0;
  xray_angle = 0;
  demo_input = 0;
  demo_input_new = 0;
  demo_input_prev = 0;
  demo_input_prev_new = 0;
  demo_enable = 0;
}

void LoadDemoInputObject(uint16 a, uint16 j) {  // 0x918395
  DemoInputObject dio;
  xray_angle = a;
  dio = get_DemoInputObject(j);
  demo_input_pre_instr = dio.pre_instr;
  demo_input_instr_ptr = dio.instr_ptr;
  demo_input_instr_timer = 1;
  demo_timer_counter = 0;
  //  Call(dio->ptr | 0x910000);
}

void DemoObjectInputHandler(void) {  // 0x9183C0
  if ((demo_enable & 0x8000) != 0) {
    if (demo_input_instr_ptr) {
      ProcessDemoInputObject();
      joypad1_input_samusfilter = demo_input_prev;
      joypad1_newinput_samusfilter = demo_input_prev_new;
      joypad1_lastkeys = demo_input;
      demo_input_prev = demo_input;
      joypad1_newkeys = demo_input_new;
      demo_input_prev_new = demo_input_new;
    }
  }
}

void CallDemoPreInstr(uint32 ea) {
  switch (ea) {
  case fnDemoPreInstr_nullsub_162: return;
  case fnDemoPreInstr_BabyMetroidDiscovery_RunLeft: DemoPreInstr_BabyMetroidDiscovery_RunLeft(); return;
  case fnDemoPreInstr_BabyMetroidDiscovery_StopAndLook: DemoPreInstr_BabyMetroidDiscovery_StopAndLook(); return;
  case fnDemoPreInstr_CheckLeaveDemo: DemoPreInstr_CheckLeaveDemo(); return;
  case fnDemoPreInstr_CheckLeaveDemo_Shinespark: DemoPreInstr_CheckLeaveDemo_Shinespark(); return;
  default: Unreachable();
  }
}

uint16 CallDemoInstr(uint32 ea, uint16 k, uint16 j) {
  switch (ea) {
  case fnDemoInstr_Finish: return DemoInstr_Finish(k, j);
  case fnDemoInstr_SetPreInstr: return DemoInstr_SetPreInstr(k, j);
  case fnDemoInstr_ClearPreInstr: return DemoInstr_ClearPreInstr(k, j);
  case fnDemoInstr_Goto: return DemoInstr_Goto(k, j);
  case fnDemoInstr_DecTimerAndGoto: return DemoInstr_DecTimerAndGoto(k, j);
  case fnDemoInstr_SetTimer: return DemoInstr_SetTimer(k, j);
  case fnDemoInstr_GiveInputToPlayerAndDisableDemo: return DemoInstr_GiveInputToPlayerAndDisableDemo(k, j);
  case fnDemoInstr_DisableDemo: return DemoInstr_DisableDemo(k, j);
  case fnDemoInstr_FaceSamusLeftAndDisableDemo: return DemoInstr_FaceSamusLeftAndDisableDemo(k, j);
  default: return Unreachable();
  }
}

void ProcessDemoInputObject(void) {  // 0x9183F2
  CallDemoPreInstr(demo_input_pre_instr | 0x910000);
  if (!--demo_input_instr_timer) {
    uint16 instr_ptr = demo_input_instr_ptr;
    DemoInputEntry DIE;
    while (1) {
      DIE = get_DemoInputEntry(instr_ptr);
      if ((DIE.func_ptr & 0x8000) == 0)
        break;
      instr_ptr = CallDemoInstr(DIE.func_ptr | 0x910000, 0, DIE.instr_list_ptr);
      if (instr_ptr == 0)
        return;
    }
    demo_input_instr_timer = DIE.timer;
    demo_input = DIE.cur_input;
    demo_input_new = DIE.new_input;
    demo_input_instr_ptr = instr_ptr + sizeof(DemoInputEntry);
  }
}

uint16 DemoInstr_Finish(uint16 k, uint16 j) {  // 0x918427
  demo_input_instr_ptr = 0;
  demo_input = 0;
  demo_input_new = 0;
  return 0;
}

uint16 DemoInstr_SetPreInstr(uint16 k, uint16 j) {  // 0x918434
  demo_input_pre_instr = j;
  return j + 2;
}

uint16 DemoInstr_ClearPreInstr(uint16 k, uint16 j) {  // 0x91843F
  demo_input_pre_instr = addr_kDemoPreInstr_Empty;
  return j;
}

uint16 DemoInstr_Goto(uint16 k, uint16 j) {  // 0x918448
  return j;
}

uint16 DemoInstr_DecTimerAndGoto(uint16 k, uint16 j) {  // 0x91844F
  if (--demo_timer_counter)
    return DemoInstr_Goto(k, j);
  else
    return j + 2;
}

uint16 DemoInstr_SetTimer(uint16 k, uint16 j) {  // 0x918459
  demo_timer_counter = j;
  return j + 2;
}

uint16 DemoInstr_GiveInputToPlayerAndDisableDemo(uint16 k, uint16 j) {  // 0x9185FC
  frame_handler_alfa = FUNC16(Samus_FrameHandlerAlfa_Normal);
  frame_handler_beta = FUNC16(Samus_FrameHandlerBeta_Normal);
  DisableDemoInput();
  return j;
}

void DemoPreInstr_BabyMetroidDiscovery_RunLeft(void) {  // 0x91864F
  if (sign16(samus_x_pos - 178)) {
    demo_input_pre_instr = FUNC16(DemoPreInstr_BabyMetroidDiscovery_StopAndLook);
    demo_input_instr_ptr = addr_kDemoInstrs_BabyMetroidDiscovery_StopAndLook;
    demo_input_instr_timer = 1;
  }
}

void DemoPreInstr_BabyMetroidDiscovery_StopAndLook(void) {  // 0x91866A
  if (!eproj_x_pos[0]) {
    demo_input_pre_instr = FUNC16(DemoPreInstr_nullsub_162);
    demo_input_instr_ptr = addr_kDemoInstrs_BabyMetroidDiscovery_End;
    demo_input_instr_timer = 1;
  }
}

uint16 DemoInstr_DisableDemo(uint16 k, uint16 j) {  // 0x918682
  frame_handler_alfa = FUNC16(Samus_FrameHandlerBeta_DoNothing);
  frame_handler_beta = FUNC16(Samus_FrameHandlerBeta_DoNothing);
  DisableDemoInput();
  return j;
}

void UNUSED_FaceSamusLeftAndDisableDemo(void) {  // 0x9186FE
  frame_handler_alfa = FUNC16(Samus_FrameHandlerAlfa_SamusLocked);
  samus_pose = kPose_02_FaceL_Normal;
  SamusFunc_F433();
  Samus_SetAnimationFrameIfPoseChanged();
  samus_last_different_pose = samus_prev_pose;
  *(uint16 *)&samus_last_different_pose_x_dir = *(uint16 *)&samus_prev_pose_x_dir;
  samus_prev_pose = samus_pose;
  *(uint16 *)&samus_prev_pose_x_dir = *(uint16 *)&samus_pose_x_dir;
  DisableDemoInput();
  samus_input_handler = FUNC16(nullsub_152);
}

uint16 DemoInstr_FaceSamusLeftAndDisableDemo(uint16 k, uint16 j) {  // 0x918739
  frame_handler_alfa = FUNC16(Samus_FrameHandlerAlfa_SamusLocked);
  samus_pose = kPose_02_FaceL_Normal;
  SamusFunc_F433();
  Samus_SetAnimationFrameIfPoseChanged();
  samus_last_different_pose = samus_prev_pose;
  *(uint16 *)&samus_last_different_pose_x_dir = *(uint16 *)&samus_prev_pose_x_dir;
  samus_prev_pose = samus_pose;
  *(uint16 *)&samus_prev_pose_x_dir = *(uint16 *)&samus_pose_x_dir;
  DisableDemoInput();
  samus_input_handler = FUNC16(nullsub_152);
  return j;
}

static Func_V *const kDemoSetFuncPtrs_0[6] = {  // 0x918790
  DemoSet_LandingSite,
  DemoSet_StandFaceRight,
  DemoSet_StandFaceRight,
  DemoSet_StandFaceLeft,
  DemoSet_StandFaceRight,
  DemoSet_MorphBallMoveLeft,
};
static Func_V *const kDemoSetFuncPtrs_1[6] = {
  DemoSet_StandFaceLeft,
  DemoSet_StandFaceLeft,
  DemoSet_StandFaceRight,
  DemoSet_StandFaceLeft,
  DemoSet_StandFaceRight,
  DemoSet_FallFaceLeft,
};
static Func_V *const kDemoSetFuncPtrs_2[6] = {
  DemoSet_StandFaceLeft,
  DemoSet_Shinespark,
  DemoSet_StandFaceRight,
  DemoSet_StandFaceRight,
  DemoSet_StandFaceRight,
  DemoSet_StandFaceRight,
};
static Func_V *const kDemoSetFuncPtrs_3[5] = {
  DemoSet_GauntletEntrance,
  DemoSet_StandFaceLeft,
  DemoSet_StandFaceLeft,
  DemoSet_StandFaceRight,
  DemoSet_StandFaceLeft_LowHealth,
};

static Func_V *const *const kDemoSetFuncPtrs[4] = {
  kDemoSetFuncPtrs_0,
  kDemoSetFuncPtrs_1,
  kDemoSetFuncPtrs_2,
  kDemoSetFuncPtrs_3,
};

void LoadDemoData(void) {
  DemoSetDef DemoSetDef;

  //uint16 instr_ptr = 16 * demo_scene + kDemoSetDefPtrs[demo_set];
  //DemoSetDef = get_DemoSetDef(instr_ptr);
  DemoSetDef = kDemoSetDefPtrs[demo_set][demo_scene];
  collected_items = DemoSetDef.items;
  equipped_items = collected_items;
  samus_max_missiles = DemoSetDef.missiles;
  samus_missiles = samus_max_missiles;
  samus_max_super_missiles = DemoSetDef.super_missiles;
  samus_super_missiles = samus_max_super_missiles;
  samus_max_power_bombs = DemoSetDef.power_bombs;
  samus_power_bombs = samus_max_power_bombs;
  samus_max_health = DemoSetDef.health;
  samus_health = samus_max_health;
  collected_beams = DemoSetDef.collected_beams_;
  equipped_beams = DemoSetDef.equipped_beams_;
  samus_reserve_health = 0;
  ResetDemoData();
  EnableDemoInput();
  //uint16 demo_obj = get_DemoSetDef(instr_ptr)->demo_obj;
  uint16 demo_obj = DemoSetDef.demo_obj;
  LoadDemoInputObject(demo_obj, demo_obj);
  kDemoSetFuncPtrs[demo_set][demo_scene]();
  frame_handler_alfa = FUNC16(Samus_FrameHandlerAlfa_Demo);
  frame_handler_beta = FUNC16(Samus_FrameHandlerBeta_TitleDemo);
  samus_new_pose_command = 0;
  samus_new_pose_interrupted_command = 0;
  samus_new_pose_transitional_command = 0;
  Samus_LoadSuitPalette();
  UpdateBeamTilesAndPalette();
  button_config_up = kButton_Up;
  button_config_down = kButton_Down;
  button_config_left = kButton_Left;
  button_config_right = kButton_Right;
  button_config_shoot = kButton_X;
  button_config_jump = kButton_A;
  button_config_run = kButton_B;
  button_config_itemcancel = kButton_Y;
  button_config_itemswitch = kButton_Select;
  button_config_aim_up = kButton_R;
  button_config_aim_down = kButton_L;
  UNUSED_word_7E09E8 = 1;
  debug_flag = 1;
  moonwalk_flag = 0;
  UNUSED_word_7E0DF8 = 0;
  UNUSED_word_7E0DFA = 0;
  UNUSED_word_7E0DFC = 0;
}

void DemoSet_LandingSite(void) {  // 0x918A33
  MakeSamusFaceForward();
  samus_draw_handler = FUNC16(Samus_DrawHandler_Default);
}

void DemoSet_MorphBallMoveLeft(void) {  // 0x918A3E
  DemoSet_SetSamusPose(kPose_1F_MoveL_Morphball_Ground);
}

void DemoSet_StandFaceLeft_LowHealth(void) {  // 0x918A43
  samus_health = 20;
  DemoSet_StandFaceLeft();
}

void DemoSet_StandFaceLeft(void) {  // 0x918A49
  DemoSet_SetSamusPose(kPose_02_FaceL_Normal);
}

void DemoSet_FallFaceLeft(void) {  // 0x918A4E
  DemoSet_SetSamusPose(kPose_2A_FaceL_Fall);
}

void DemoSet_StandFaceRight(void) {  // 0x918A53
  DemoSet_SetSamusPose(kPose_01_FaceR_Normal);
}

void DemoSet_SetSamusPose(uint16 a) {  // 0x918A56
  samus_pose = a;
  SamusFunc_F433();
  Samus_SetAnimationFrameIfPoseChanged();
  samus_draw_handler = FUNC16(Samus_DrawHandler_Default);
}

void DemoSet_Shinespark(void) {  // 0x918A68
  samus_draw_handler = FUNC16(Samus_DrawHandler_Default);
  TriggerShinesparkWindup();
  samus_pose = kPose_CD_FaceR_Shinespark_Diag;
  SamusFunc_F433();
  Samus_SetAnimationFrameIfPoseChanged();
}

void DemoSet_GauntletEntrance(void) {  // 0x918A81
  samus_draw_handler = FUNC16(Samus_DrawHandler_Default);
  TriggerShinesparkWindup();
  samus_pose = kPose_CA_FaceL_Shinespark_Horiz;
  SamusFunc_F433();
  Samus_SetAnimationFrameIfPoseChanged();
}

void DemoPreInstr_CheckLeaveDemo(void) {  // 0x918A9B
  if (game_state == kGameState_44_TransitionFromDemo) {
    demo_input_instr_ptr = addr_kDemoInstrs_LeaveDemo;
    demo_input_instr_timer = 1;
  }
}

void DemoPreInstr_CheckLeaveDemo_Shinespark(void) {  // 0x918AB0
  if (samus_movement_type != kMovementType_1A_GrabbedByDraygon) {
    demo_input_pre_instr = FUNC16(DemoPreInstr_CheckLeaveDemo);
    demo_input_instr_ptr = addr_kDemoInstrs_Shinespark_UnseenSection;
    demo_input_instr_timer = 1;
  }
}


typedef struct XrayHdmaCtx {
  uint16 r22;
  uint16 r24;
  uint16 r26;
  uint16 r28;
  uint16 r30;
  uint16 r32;
  uint16 r18_avoid;
  uint16 *dest;
} XrayHdmaCtx;

static void XrayFillUp(uint16 *dest, uint16 fill_with, uint16 v1) {
  do {
    dest[v1 >> 1] = fill_with;
  } while (!sign16(v1 -= 2));
}

static void XrayFillDown(uint16 *dest, uint16 fill_with, uint16 v1) {
  do {
    dest[v1 >> 1] = fill_with;
  } while ((v1 += 2) < 460);
}

static void XrayFillUpRamped(uint16 *dest, int pos, uint32 left, uint32 left_step, uint32 right, uint32 right_step, int adjust) {
  do {
    left += left_step;
    right += right_step;
    uint32 left_val = (left & ~0xffff) ? (((int32)left < 0) ? 0 : 0xffff) : left;
    uint32 right_val = (right & ~0xffff) ? (((int32)right < 0) ? 0 : 0xffff) : right;
    // If both left and right reached the end, fill the remainder with 0xff
    bool finished = (left & ~0xffff) && (right & ~0xffff) && (((left_step ^ left) | (right_step ^ right)) >> 31) == 0;
    dest[pos >> 1] = ((int32)right < 0 || (int32)left >= 0x10000) ? 0xff : (left_val >> 8 | right_val & ~0xff);
    if (finished) {
      pos += adjust;
      while ((pos -= 2) >= 0)
        dest[pos >> 1] = 0xff;
      return;
    }
  } while ((pos -= 2) >= 0);
}

static void XrayFillDownRamped(uint16 *dest, int pos, uint32 left, uint32 left_step, uint32 right, uint32 right_step, int adjust) {
  do {
    left += left_step;
    right += right_step;
    uint32 left_val = (left & ~0xffff) ? (((int32)left < 0) ? 0 : 0xffff) : left;
    uint32 right_val = (right & ~0xffff) ? (((int32)right < 0) ? 0 : 0xffff) : right;
    bool finished = (left & ~0xffff) && (right & ~0xffff) && (((left_step ^ left) | (right_step ^ right)) >> 31) == 0;
    // If both left and right got clamped, fill the remainder with 0xff
    dest[pos >> 1] = ((int32)right < 0 || (int32)left >= 0x10000) ? 0xff : (left_val >> 8 | right_val & ~0xff);
    if (finished) {
      pos += adjust;
      while ((pos += 2) < 460)
        dest[pos >> 1] = 0xff;
      return;
    }
  } while ((pos += 2) < 460);
}

typedef void XrayHdma0Func(XrayHdmaCtx *ctx);
static void XrayHdmaFunc_BeamAimedD(XrayHdmaCtx *ctx);
static void XrayHdmaFunc_BeamAimedL(XrayHdmaCtx *ctx);
static void XrayHdmaFunc_BeamAimedR(XrayHdmaCtx *ctx);
static void XrayHdmaFunc_BeamAimedU(XrayHdmaCtx *ctx);
static void XrayHdmaFunc_BeamHoriz(XrayHdmaCtx *ctx);
static void XrayHdmaOnScreen_BeamAimedD(XrayHdmaCtx *ctx);
static void XrayHdmaOnScreen_BeamAimedL(XrayHdmaCtx *ctx);
static void XrayHdmaOnScreen_BeamAimedR(XrayHdmaCtx *ctx);
static void XrayHdmaOnScreen_BeamAimedU(XrayHdmaCtx *ctx);
static void XrayHdmaOnScreen_BeamHoriz(XrayHdmaCtx *ctx);

static void XrayHdmaFunc_BeamAimedR(XrayHdmaCtx *ctx) {  // 0x91BEC2
  int p = 2 * ctx->r24;
  XrayFillUpRamped(ctx->dest, p - 2, ctx->r22 - 0x10000, ctx->r30, 65535, 1, 2);
  XrayFillDownRamped(ctx->dest, p, ctx->r22 - 0x10000, ctx->r32, 65535, 1, -2);
}

static void XrayHdmaFunc_BeamAimedL(XrayHdmaCtx *ctx) {  // 0x91BF72
  int t = 2 * ctx->r24;
  XrayFillUpRamped(ctx->dest, t - 2, 0, -1, ctx->r22 + 0x10000, -ctx->r32, 2);
  XrayFillDownRamped(ctx->dest, t, 0, -1, ctx->r22 + 0x10000, -ctx->r30, -2);
}

static void XrayHdmaFunc_BeamAimedU(XrayHdmaCtx *ctx) {
  int p = 2 * ctx->r24;
  if (sign16(ctx->r26 - 192)) {
    XrayFillUpRamped(ctx->dest, p - 2, ctx->r22 - 0x10000, ctx->r30, ctx->r22 - 0x10000, ctx->r32, 0);
  } else if (sign16(ctx->r28 - 192)) {
    XrayFillUpRamped(ctx->dest, p - 2, ctx->r22 + 0x10000, -ctx->r30, ctx->r22 - 0x10000, ctx->r32, 0);
  } else {
    XrayFillUpRamped(ctx->dest, p - 2, ctx->r22 + 0x10000, -ctx->r30, ctx->r22 + 0x10000, -ctx->r32, 2);
  }
  XrayFillDown(ctx->dest, 0xff, p);
}

static void XrayHdmaFunc_BeamAimedD(XrayHdmaCtx *ctx) {
  int p = 2 * ctx->r24;
  if (sign16(ctx->r28 - 128)) {
    XrayFillDownRamped(ctx->dest, p, ctx->r22 - 0x10000, ctx->r32, ctx->r22 - 0x10000, ctx->r30, 0);
  } else if (sign16(ctx->r26 - 128)) {
    XrayFillDownRamped(ctx->dest, p, ctx->r22 + 0x10000, -ctx->r32, ctx->r22 - 0x10000, ctx->r30, 0);
  } else {
    XrayFillDownRamped(ctx->dest, p, ctx->r22 + 0x10000, -ctx->r32, ctx->r22 + 0x10000, -ctx->r30, 0);
  }
  XrayFillUp(ctx->dest, 0xff, p - 2);
}

static void XrayHdmaFunc_BeamHoriz(XrayHdmaCtx *ctx) {  // 0x91C505
  uint16 v0 = 2 * (ctx->r24 - 1);
  ctx->dest[v0 >> 1] = 0xff00;
  XrayFillUp(ctx->dest, 0xff, v0 - 2);
  XrayFillDown(ctx->dest, 0xff, v0 + 2);
}

static void XrayHdmaOnScreen_BeamAimedR(XrayHdmaCtx *ctx) {  // 0x91C5FF
  int p = 2 * ctx->r24;
  ctx->dest[(p - 2) >> 1] = ctx->r22 >> 8 | 0xff00;
  XrayFillUpRamped(ctx->dest, p - 4, ctx->r22, ctx->r30, 65535, 1, 2);
  XrayFillDownRamped(ctx->dest, p, ctx->r22, ctx->r32, 65535, 1, -2);
}

static void XrayHdmaOnScreen_BeamAimedL(XrayHdmaCtx *ctx) {  // 0x91C660
  int v0 = 2 * ctx->r24;
  ctx->dest[(v0 - 2) >> 1] = (ctx->r22 >> 8) << 8;
  XrayFillUpRamped(ctx->dest, v0 - 4, 0, -1, ctx->r22, -ctx->r32, 2);
  XrayFillDownRamped(ctx->dest, v0, 0, -1, ctx->r22, -ctx->r30, -2);
}

static void XrayHdmaOnScreen_BeamAimedU(XrayHdmaCtx *ctx) {  // 0x91C6C1
  int v0 = 2 * ctx->r24;
  ctx->dest[(v0 - 2) >> 1] = (ctx->r22 >> 8) * 0x101;
  if (sign16(ctx->r26 - 192)) {
    XrayFillUpRamped(ctx->dest, v0 - 4, ctx->r22, ctx->r30, ctx->r22, ctx->r32, 0);
  } else if (sign16(ctx->r28 - 192)) {
    XrayFillUpRamped(ctx->dest, v0 - 4, ctx->r22, -ctx->r30, ctx->r22, ctx->r32, 0);
  } else {
    XrayFillUpRamped(ctx->dest, v0 - 4, ctx->r22, -ctx->r30, ctx->r22, -ctx->r32, 2);
  }
  XrayFillDown(ctx->dest, 0xff, v0);
}

static void XrayHdmaOnScreen_BeamAimedD(XrayHdmaCtx *ctx) {  // 0x91C822
  int v0 = 2 * ctx->r24;
  ctx->dest[(v0 - 2) >> 1] = (ctx->r22 >> 8) * 0x101;
  if (sign16(ctx->r28 - 128)) {
    XrayFillDownRamped(ctx->dest, v0, ctx->r22, ctx->r32, ctx->r22, ctx->r30, 0);
  } else if (sign16(ctx->r26 - 128)) {
    XrayFillDownRamped(ctx->dest, v0, ctx->r22, -ctx->r32, ctx->r22, ctx->r30, 0);
  } else {
    XrayFillDownRamped(ctx->dest, v0, ctx->r22, -ctx->r32, ctx->r22, -ctx->r30, 0);
  }
  XrayFillUp(ctx->dest, 0xff, v0 - 4);
}

static void XrayHdmaOnScreen_BeamHoriz(XrayHdmaCtx *ctx) {  // 0x91C998
  uint16 v0 = 2 * (ctx->r24 - 1);
  uint32 t = (ctx->r22 >> 8);
  ctx->dest[v0 >> 1] = (ctx->r18_avoid == 64) ? t | 0xFF00 : t << 8;
  XrayFillUp(ctx->dest, 0xff, v0 - 2);
  XrayFillDown(ctx->dest, 0xff, v0 + 2);
}

void CalculateXrayHdmaTableInner(uint16 k, uint16 j, uint16 r18, uint16 r20, bool off_screen, uint16 *dest_addr) {
  int v3;
  XrayHdmaCtx ctx[1];
  ctx->dest = (uint16*)dest_addr;
  ctx->r18_avoid = r18;
  ctx->r22 = k << 8;
  ctx->r24 = j;
  ctx->r26 = r18 - r20;
  ctx->r26 += (ctx->r26 & 0x8000) != 0 ? 0x100 : 0;
  ctx->r28 = r20 + r18;
  if (!sign16(r20 + r18 - 257))
    ctx->r28 = r20 + r18 - 256;
  ctx->r30 = kAbsTanTable[sign16(ctx->r26 - 128) ? ctx->r26 : ctx->r26 - 128];
  ctx->r32 = kAbsTanTable[sign16(ctx->r28 - 128) ? ctx->r28 : ctx->r28 - 128];

  if (!r20 && (r18 == 64 || r18 == 192)) {
    v3 = 8;
  } else if (sign16(ctx->r26 - 128)) {
    if (!sign16(ctx->r26 - 64)) {
      v3 = 4;
    } else if (!sign16(ctx->r28 - 64)) {
      v3 = 0;
    } else {
      v3 = 2;
    }
  } else {
    if (!sign16(ctx->r26 - 192)) {
      v3 = 2;
    } else if (!sign16(ctx->r28 - 192)) {
      v3 = 6;
    } else {
      v3 = 4;
    }
  }

  if (off_screen) {
    static XrayHdma0Func *const kXrayHdmaFuncs[5] = {  // 0x91BE11
      XrayHdmaFunc_BeamAimedR,
      XrayHdmaFunc_BeamAimedU,
      XrayHdmaFunc_BeamAimedD,
      XrayHdmaFunc_BeamAimedL,
      XrayHdmaFunc_BeamHoriz,
    };
    kXrayHdmaFuncs[v3 >> 1](ctx);
  } else {
    static XrayHdma0Func *const kXrayHdmaOnScreen_Funcs[5] = {
      XrayHdmaOnScreen_BeamAimedR,
      XrayHdmaOnScreen_BeamAimedU,
      XrayHdmaOnScreen_BeamAimedD,
      XrayHdmaOnScreen_BeamAimedL,
      XrayHdmaOnScreen_BeamHoriz,
    };
    kXrayHdmaOnScreen_Funcs[v3 >> 1](ctx);
  }
}

void XrayRunHandler(void) {  // 0x91CAD6
  if (!time_is_frozen_flag && (button_config_run & joypad1_lastkeys) != 0) {
    if (Xray_Initialize() & 1) {
        static const SpawnHdmaObject_Args kSpawnHdmaObject_91CAF2 = {
          .hdma_control = HDMA_CONTROL(0, 1, 1),
          .hdma_target = REG(WH2),
          .hdma_instr_list_ptr = addr_kHdmaObject_IList_Xray
        };
        SpawnHdmaObject(0x91, &kSpawnHdmaObject_91CAF2);
    }
  }
}

void Xray_SetupStage1_FreezeTime_BackupBg2(uint16 k) {  // 0x91CAF9
  LOBYTE(time_is_frozen_flag) = 1;
  *((uint8 *)hdma_object_A + (uint8)k) = reg_BG2HOFS;
  *((uint8 *)hdma_object_A + (uint8)k + 1) = HIBYTE(reg_BG2HOFS);
  *((uint8 *)hdma_object_B + (uint8)k) = reg_BG2VOFS;
  *((uint8 *)hdma_object_B + (uint8)k + 1) = HIBYTE(reg_BG2VOFS);
  *((uint8 *)hdma_object_C + (uint8)k) = reg_BG2SC;
}

void Xray_SetupStage2_ReadBg1_2ndScreen(void) {  // 0x91CB1C
  uint16 v0 = vram_read_queue_tail;
  *(uint16 *)((uint8 *)&vram_read_queue[0].vram_target + v0) = ((reg_BG1SC & 0xFC) << 8) + 1024;
  *(uint16 *)((uint8 *)&vram_read_queue[0].dma_control + v0) = 129;
  *(uint16 *)((uint8 *)&vram_read_queue[0].dma_target + v0) = 57;
  *(VoidP *)((uint8 *)&vram_read_queue[0].src.addr + v0) = ADDR16_OF_RAM(ram4000) + 0x2800;
  *(uint16 *)(&vram_read_queue[0].src.bank + v0) = 126;
  *(uint16 *)((uint8 *)&vram_read_queue[0].size + v0) = 2048;
  vram_read_queue_tail = v0 + 9;
}

void Xray_SetupStage3_ReadBg1_1stScreen(void) {  // 0x91CB57

  uint16 v0 = vram_read_queue_tail;
  *(uint16 *)((uint8 *)&vram_read_queue[0].vram_target + v0) = (reg_BG1SC & 0xFC) << 8;
  *(uint16 *)((uint8 *)&vram_read_queue[0].dma_control + v0) = 129;
  *(uint16 *)((uint8 *)&vram_read_queue[0].dma_target + v0) = 57;
  *(VoidP *)((uint8 *)&vram_read_queue[0].src.addr + v0) = ADDR16_OF_RAM(ram4000) + 0x2000;
  *(uint16 *)(&vram_read_queue[0].src.bank + v0) = 126;
  *(uint16 *)((uint8 *)&vram_read_queue[0].size + v0) = 2048;
  vram_read_queue_tail = v0 + 9;
}

void Xray_SetupStage4_SetupAndReadBg2_1stScreen(void) {  // 0x91CB8E
  uint16 r24 = 4 * ((layer1_y_pos + bg1_y_offset) & 0xF0);
  r24 += ((layer1_x_pos + bg1_x_offset) & 0xF0) >> 3;
  r24 += 4 * ((layer1_x_pos + bg1_x_offset) & 0x100);
  uint16 r22 = 0;
  int m = 16;
  do {
    int n = 16;
    uint16 r26 = r24 & 0x7E0;
    uint16 r28 = r24 & 0x1F;
    uint16 r30 = 0;
    do {
      if (!sign16(r30 + r28 - 32)) {
        r26 = (r26 + 1024) & 0x7E0;
        r28 = 0;
        r30 = 0;
      }
      uint16 v0 = r30 + r28 + r26;
      uint16 v11 = ram4000.xray_tilemaps[v0 + 4096];
      uint16 v10 = ram4000.xray_tilemaps[v0 + 4097];
      uint16 v9 = ram4000.xray_tilemaps[v0 + 4128];
      uint16 v1 = ram4000.xray_tilemaps[v0 + 4129];
      *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[33] + r22) = v1;
      *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[32] + r22) = v9;
      *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[1] + r22) = v10;
      *(uint16 *)((uint8 *)ram4000.xray_tilemaps + r22) = v11;
      r22 += 4;
      r30 += 2;
    } while (--n);
    CopyBottomBg1RowToXrayBg2(r22, r26, r28, r30);
    r24 = (r24 & 0x400) + ((r24 + 64) & 0x3FF);
    r22 += 64;
  } while (--m);
  assert((uint16)(layer1_y_pos >> 12) == 0);
  uint16 r34 = Mult8x8(layer1_y_pos >> 4, room_width_in_blocks) + (layer1_x_pos >> 4);
  r22 = 0;
  m = 16;
  do {
    LoadRightHalfOfRevealedBlock(r22, r34);
    int n = 16;
    uint16 r36 = r34;
    do {
      LoadRevealedBlock(n, r22, r36);
      r22 += 4;
      r36 += 1;
    } while (--n);
    uint16 v12 = r22;
    r22 += 1984;
    LoadRevealedBlock(0, r22, r36);
    r22 = v12 + 64;
    r34 += room_width_in_blocks;
  } while (--m);
  LoadXrayBlocks();
  uint16 v7 = vram_read_queue_tail;
  *(uint16 *)((uint8 *)&vram_read_queue[0].vram_target + v7) = (reg_BG2SC & 0xFC) << 8;
  *(uint16 *)((uint8 *)&vram_read_queue[0].dma_control + v7) = 129;
  *(uint16 *)((uint8 *)&vram_read_queue[0].dma_target + v7) = 57;
  *(VoidP *)((uint8 *)&vram_read_queue[0].src.addr + v7) = 0x5000;
  *(uint16 *)(&vram_read_queue[0].src.bank + v7) = 126;
  *(uint16 *)((uint8 *)&vram_read_queue[0].size + v7) = 2048;
  vram_read_queue_tail = v7 + 9;
}

void CopyBottomBg1RowToXrayBg2(uint16 dst_r22, uint16 r26, uint16 r28, uint16 r30) {  // 0x91CCF1
  int16 v0;

  uint16 R32 = r26;
  v0 = r30 + r28;
  if (!sign16(r30 + r28 - 32)) {
    R32 = (R32 + 1024) & 0x7E0;
    v0 = 0;
  }
  uint16 v1 = R32 + v0;
  uint16 v6 = ram4000.xray_tilemaps[v1 + 4096];
  uint16 v5 = ram4000.xray_tilemaps[v1 + 4097];
  uint16 v4 = ram4000.xray_tilemaps[v1 + 4128];
  uint16 v3 = ram4000.xray_tilemaps[v1 + 4129];
  uint16 v2 = dst_r22 + 1984;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[33] + v2) = v3;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[32] + v2) = v4;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[1] + v2) = v5;
  *(uint16 *)((uint8 *)ram4000.xray_tilemaps + v2) = v6;
}

static const uint8 *Xray_GetXrayedBlock(uint16 k) {  // 0x91CDD6
  uint16 block_type;

  uint16 bts = BTS[k];
  uint16 r40 = level_data[k] & 0xF000;
  for (int i = 0; ; ++i) {
    block_type = kXrayBlockData[i].block_type;
    if (block_type == 0xFFFF)
      break;
    if (block_type == r40) {
      for (const uint8 *p = RomPtr_91(kXrayBlockData[i].instr_list); ; p += 4) {
        block_type = GET_WORD(p);
        if (block_type == 0xFFFF)
          break;
        if (block_type == 0xFF00 || block_type == bts)
          return RomPtr_91(GET_WORD(p + 2));
      }
      return NULL;
    }
  }
  return NULL;
}


void LoadRightHalfOfRevealedBlock(uint16 dst_r22, uint16 r34) {  // 0x91CD42
  // bug: passing 0xffff to this function is invalid and will read invalid memory.
  if (r34 == 0)
    return;
  const uint8 *jp = Xray_GetXrayedBlock(r34 - 1);
  uint16 *dst = (uint16 *)((uint8 *)ram4000.xray_tilemaps + dst_r22);

  if (jp == NULL)
    return;

  if (GET_WORD(jp) != FUNC16(RevealedBlock_Func_Copy2x1BlockToXrayBg2)) {
    if (GET_WORD(jp) != FUNC16(RevealedBlock_Func_Copy2x2BlockToXrayBg2))
      return;
    TileTable *src = tile_table.tables + GET_WORD(jp + 8);
    dst[64] = src->top_left;
    dst[65] = src->top_right;
    dst[96] = src->bottom_left;
    dst[97] = src->bottom_right;
  }
  TileTable *src = tile_table.tables + GET_WORD(jp + 4);
  dst[0] = src->top_left;
  dst[1] = src->top_right;
  dst[32] = src->bottom_left;
  dst[33] = src->bottom_right;
}

static void Xray_CombinedMove(uint16 dst_r22, uint16 r36, bool which_dir) {
  uint16 y = r36 / room_width_in_blocks;
  uint16 x = r36 % room_width_in_blocks;
  uint16 r48 = level_data[r36] & 0xF000;
  int step = (int8)BTS[r36];
  if (step) {
    uint16 *variable = which_dir ? &y : &x;
    for (;;) {
      if ((int16)(*variable + step) < 0) {
        CopyBlockToXrayBg2(dst_r22, 0xFF);
        return;
      }
      *variable += step;
      int pos = y * room_width_in_blocks + x;
      step = (int8)BTS[pos];
      r48 = level_data[pos] & 0xF000;
      if (r48 == 0xd000) {
        variable = &y;
        continue;
      }
      if (r48 != 0x5000)
        break;
      if (step < 0)
        variable = &x; // wtf?
    }
  }

  if (kXrayBlockData[1].block_type == r48) {
    uint16 *t = (uint16 *)RomPtr_91(kXrayBlockData[1].instr_list);
    for (; t[0] != 0xffff; t += 2) {
      if (t[0] == 0xff00 || t[0] == (step & 0xff)) {
        CopyRevealedBlockToXrayBg2(dst_r22, RomPtr_91(t[1] + 2));
        return;
      }
    }
  }
}

static void RevealedBlock_Func_Copy1x1BlockToXrayBg2(uint16 dst_r22, const uint8 *jp) {  // 0x91CF36
  CopyRevealedBlockToXrayBg2(dst_r22, jp + 2);
}

static void RevealedBlock_Func_Copy1x1BlockToXrayBg2_Brinstar(uint16 dst_r22, const uint8 *jp) {  // 0x91CF3E
  if (area_index == kArea_1_Brinstar)
    CopyRevealedBlockToXrayBg2(dst_r22, jp + 2);
}

static void RevealedBlock_Func_Copy2x1BlockToXrayBg2(uint16 r18, uint16 dst_r22, const uint8 *jp) {  // 0x91CF4E
  CopyRevealedBlockToXrayBg2(dst_r22, jp + 2);
  if (r18 != 1)
    CopyRevealedBlockToXrayBg2OneBlockRight(dst_r22, jp + 4);
}

static void RevealedBlock_Func_Copy1x2BlockToXrayBg2(uint16 dst_r22, const uint8 *jp) {  // 0x91CF62
  CopyRevealedBlockToXrayBg2(dst_r22, jp + 2);
  CopyRevealedBlockToXrayBg2OneBlockDown(dst_r22, jp + 2);
}

static void RevealedBlock_Func_Copy2x2BlockToXrayBg2(uint16 r18, uint16 dst_r22, const uint8 *jp) {  // 0x91CF6F
  CopyRevealedBlockToXrayBg2(dst_r22, jp + 2);
  if (r18 != 1)
    CopyRevealedBlockToXrayBg2OneBlockRight(dst_r22, jp + 4);
  CopyRevealedBlockToXrayBg2OneBlockDown(dst_r22, jp + 6);
  if (r18 != 1) {
    uint16 v5 = GET_WORD(jp + 8);
    uint16 top_left = tile_table.tables[v5].top_left;
    uint16 top_right = tile_table.tables[v5].top_right;
    uint16 bottom_left = tile_table.tables[v5].bottom_left;
    uint16 bottom_right = tile_table.tables[v5].bottom_right;
    *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[99] + dst_r22) = bottom_right;
    *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[98] + dst_r22) = bottom_left;
    *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[67] + dst_r22) = top_right;
    *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[66] + dst_r22) = top_left;
  }
}

static void CallXrayFunc(uint32 ea, const uint8 *jp, uint16 r18, uint16 r22, uint16 r36) {
  switch (ea) {
  case fnRevealedBlock_Func_Vertical: Xray_CombinedMove(r22, r36, true); return;
  case fnRevealedBlock_Func_Horizontal: Xray_CombinedMove(r22, r36, false); return;
  case fnRevealedBlock_Func_Copy1x1BlockToXrayBg2: RevealedBlock_Func_Copy1x1BlockToXrayBg2(r22, jp); return;
  case fnRevealedBlock_Func_Copy1x1BlockToXrayBg2_Brinstar: RevealedBlock_Func_Copy1x1BlockToXrayBg2_Brinstar(r22, jp); return;
  case fnRevealedBlock_Func_Copy2x1BlockToXrayBg2: RevealedBlock_Func_Copy2x1BlockToXrayBg2(r18, r22, jp); return;
  case fnRevealedBlock_Func_Copy1x2BlockToXrayBg2: RevealedBlock_Func_Copy1x2BlockToXrayBg2(r22, jp); return;
  case fnRevealedBlock_Func_Copy2x2BlockToXrayBg2: RevealedBlock_Func_Copy2x2BlockToXrayBg2(r18, r22, jp); return;
  default: Unreachable();
  }
}

void LoadRevealedBlock(uint16 r18, uint16 r22, uint16 r36) {  // 0x91CDBE
  const uint8 *jp = Xray_GetXrayedBlock(r36);
  if (jp != NULL) {
    CallXrayFunc(GET_WORD(jp) | 0x910000, jp, r18, r22, r36);
  }
}

static void CopyRevealedBlockToXrayBg2(uint16 dst_r22, const uint8 *jp) {  // 0x91CFBF
  CopyBlockToXrayBg2(dst_r22, GET_WORD(jp));
}

static void CopyBlockToXrayBg2(uint16 dst_r22, uint16 a) {  // 0x91CFC1
  uint16 top_left = tile_table.tables[a].top_left;
  uint16 top_right = tile_table.tables[a].top_right;
  uint16 bottom_left = tile_table.tables[a].bottom_left;
  uint16 bottom_right = tile_table.tables[a].bottom_right;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[33] + dst_r22) = bottom_right;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[32] + dst_r22) = bottom_left;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[1] + dst_r22) = top_right;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[0] + dst_r22) = top_left;
}

static void CopyRevealedBlockToXrayBg2OneBlockRight(uint16 dst_r22, const uint8 *jp) {  // 0x91CFEE
  uint16 a = GET_WORD(jp);
  uint16 top_left = tile_table.tables[a].top_left;
  uint16 top_right = tile_table.tables[a].top_right;
  uint16 bottom_left = tile_table.tables[a].bottom_left;
  uint16 bottom_right = tile_table.tables[a].bottom_right;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[35] + dst_r22) = bottom_right;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[34] + dst_r22) = bottom_left;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[3] + dst_r22) = top_right;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[2] + dst_r22) = top_left;
}

static void CopyRevealedBlockToXrayBg2OneBlockDown(uint16 dst_r22, const uint8 *jp) {  // 0x91D01D
  uint16 a = GET_WORD(jp);
  uint16 top_left = tile_table.tables[a].top_left;
  uint16 top_right = tile_table.tables[a].top_right;
  uint16 bottom_left = tile_table.tables[a].bottom_left;
  uint16 bottom_right = tile_table.tables[a].bottom_right;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[97] + dst_r22) = bottom_right;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[96] + dst_r22) = bottom_left;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[65] + dst_r22) = top_right;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[64] + dst_r22) = top_left;
}

static void CopyFlippedBlockToXrayBg1(uint16 dst_r22, uint16 a) {  // 0x91D0A6
  uint16 top_left = tile_table.tables[a].top_left;
  uint16 top_right = tile_table.tables[a].top_right;
  uint16 bottom_left = tile_table.tables[a].bottom_left;
  uint16 bottom_right = tile_table.tables[a].bottom_right;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[1] + dst_r22) = bottom_right;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[0] + dst_r22) = bottom_left;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[33] + dst_r22) = top_right;
  *(uint16 *)((uint8 *)&ram4000.xray_tilemaps[32] + dst_r22) = top_left;
}

/**
* @brief Loads the level data block to the X-ray background 2
* @param level_data_blk The level data block to load
* @param x_blk The x position of the block
* @param y_blk The y position of the block
*/
void LoadBlockToXrayBg2(uint16 level_data_blk, uint16 x_blk, uint16 y_blk) {  // 0x91D04C
  uint16 x_blk_offset = x_blk - (layer1_x_pos / 16);
  uint16 y_blk_offset = y_blk - (layer1_y_pos / 16);
  if (0 <= x_blk_offset && x_blk_offset < 16 && 0 <= y_blk_offset && y_blk_offset < 16) {
    uint16 xray_bg2_tilemap_idx = 4 * (x_blk_offset + 32 * y_blk_offset);
    if (level_data_blk & BLK_VERT_FLIP)
      CopyFlippedBlockToXrayBg1(xray_bg2_tilemap_idx, level_data_blk & 0x3FF);
    else
      CopyBlockToXrayBg2(xray_bg2_tilemap_idx, level_data_blk & 0x3FF);
  }
}

void Xray_SetupStage5_ReadBg2_2ndScreen(void) {  // 0x91D0D3
  unsigned int v1;

  if (CanXrayShowBlocks()) {
    if (earthquake_timer) {
      reg_BG1HOFS = layer1_x_pos + bg1_x_offset;
      reg_BG1VOFS = layer1_y_pos + bg1_y_offset;
    }
    reg_BG2HOFS = reg_BG1HOFS & 0xF;
    reg_BG2VOFS = reg_BG1VOFS & 0xF;
    reg_BG2SC = 73;
  }
  uint16 v0 = vram_read_queue_tail;
  v1 = vram_read_queue_tail;
  *(uint16 *)((uint8 *)&vram_read_queue[0].vram_target + vram_read_queue_tail) = ((reg_BG2SC & 0xFC) << 8) + 1024;
  *(uint16 *)((uint8 *)&vram_read_queue[0].dma_target + v1) = 57;
  *(VoidP *)((uint8 *)&vram_read_queue[0].src.addr + v0) = 0x5800;
  *(uint16 *)(&vram_read_queue[0].src.bank + v0) = 126;
  *(uint16 *)((uint8 *)&vram_read_queue[0].size + v0) = 2048;
  vram_read_queue_tail = v0 + 9;
}

bool CanXrayShowBlocks(void) {  // 0x91D143
  if (room_ptr == addr_kRoom_TourianEntrance || room_ptr == addr_kRoom_n00bTube)
    return false;
  if (fx_type == kFxType_24_Fireflea)
    return false;
  if (boss_id == kBossId_3_Kraid || boss_id == kBossId_6_Crocomire || boss_id == kBossId_7_Phantoon
      || boss_id == kBossId_8_Draygon || boss_id == kBossId_10_MotherBrain)
    return false;
  return true;
}

void Xray_SetupStage6_TransferBg_1stScreen(void) {  // 0x91D173
  VramWriteEntry *v1;

  if (CanXrayShowBlocks()) {
    uint16 v0 = vram_write_queue_tail;
    v1 = gVramWriteEntry(vram_write_queue_tail);
    v1->size = 2048;
    v1->src.addr = ADDR16_OF_RAM(ram4000);
    *(uint16 *)&v1->src.bank = 126;
    v1->vram_dst = (reg_BG2SC & 0xFC) << 8;
    vram_write_queue_tail = v0 + 7;
  }
}

void Xray_SetupStage7_InitXrayBeam_TransferBg_2ndScreen(void) {  // 0x91D1A0
  VramWriteEntry *v1;

  if (CanXrayShowBlocks()) {
    uint16 v0 = vram_write_queue_tail;
    v1 = gVramWriteEntry(vram_write_queue_tail);
    v1->size = 2048;
    v1->src.addr = 0x4800;
    *(uint16 *)&v1->src.bank = 126;
    v1->vram_dst = ((reg_BG2SC & 0xFC) << 8) + 1024;
    vram_write_queue_tail = v0 + 7;
  }
  mov24(&hdma_ptr_1, 0x9800E4);
  mov24(&hdma_ptr_2, 0x98C8E4);
  mov24(&hdma_ptr_3, 0x999098);
  hdma_var_1 = 0;
  demo_input_pre_instr = 0;
  demo_input_instr_timer = 0;
  demo_input_instr_ptr = 0;
  demo_input = 0;
  demo_input_new = 0;
  if (samus_pose_x_dir == kSamusXDir_FaceLeft)
    xray_angle = 192;
  else
    xray_angle = 64;
}

void HdmaobjPreInstr_XraySetup(uint16 k) {  // 0x91D27F
  uint16 win_2_config;

  win_2_config = kLayerBlendWindow2Configuration_10_XrayActive_FirefleaFx;
  if (fx_type == kFxType_24_Fireflea) {
    if ((reg_COLDATA[0] & 0x1F) >= 7)
      goto LABEL_5;
    goto LABEL_4;
  }
  win_2_config = kLayerBlendWindow2Configuration_20_XrayActive_BlocksNotDrawn;
  if (CanXrayShowBlocks()) {
    win_2_config = kLayerBlendWindow2Configuration_40_XrayActive_BlocksDrawn;
LABEL_4:
    reg_COLDATA[0] = 0x27;
    reg_COLDATA[1] = 0x47;
    reg_COLDATA[2] = 0x87;
  }
LABEL_5:
  fx_layer_blending_window_2_config |= win_2_config;
}

void Xray_SetupStage8_SetBackdropColor(void) {  // 0x91D2BC
  palette_buffer.bg1_bg2_pal_0[0] = 3171;
}

void GameState_28_Unused_(void) {  // 0x91D4DA
  Unreachable();
}

void VariaSuitPickup(void) {  // 0x91D4E4
  suit_pickup_color_math_R = 0x30;
  suit_pickup_color_math_G = 0x50;
  suit_pickup_color_math_B = 0x80;
  suit_pickup_palette_transition_color = 0;
  Samus_CancelSpeedBoost();
  SetHiLo(&samus_x_extra_run_speed, &samus_x_extra_run_subspeed, 0);
  samus_x_base_speed = 0;
  samus_x_base_subspeed = 0;
  samus_y_subspeed = 0;
  samus_y_speed = 0;
  samus_y_dir = 0;
  morph_ball_bounce_state = kMorphBallBounceState_NoBounce;
  samus_x_accel_mode = 0;
  elevator_status = 0;
  substate = 0;
  suit_pickup_light_beam_pos = 0;
  suit_pickup_light_beam_widening_speed = 0x100;
  for (int i = 510; i >= 0; i -= 2)
    hdma_table_1[i >> 1] = 0x00FF;
  if (samus_movement_type == kMovementType_03_SpinJumping || samus_movement_type == kMovementType_14_WallJumping)
    QueueSfx1_Max9(kSfx1_SpinJumpEnd_Silence);
  if (equipped_items & kItem_GravitySuit)
    samus_pose = kPose_9B_FaceF_VariaGravitySuit;
  else
    samus_pose = kPose_00_FaceF_Powersuit;
  SamusFunc_F433();
  Samus_SetAnimationFrameIfPoseChanged();
  RunSamusCode(kSamusCode_21_LockToSuitAcquisition);
  samus_x_pos = layer1_x_pos + 120;
  samus_prev_x_pos = samus_x_pos;
  samus_y_pos = layer1_y_pos + 136;
  samus_prev_y_pos = samus_y_pos;
  QueueSfx2_Max6(kSfx2_AcquiredSuit);
  static const SpawnHdmaObject_Args kSpawnHdmaObject_91D59B = {
    .hdma_control = HDMA_CONTROL(0, 1, 1),
    .hdma_target = REG(WH0),
    .hdma_instr_list_ptr = addr_kHdmaObject_IList_VariaSuitPickup_Window1_Pos
  };
  SpawnHdmaObject(0x91, &kSpawnHdmaObject_91D59B);
}

void GravitySuitPickup(void) {  // 0x91D5BA
  suit_pickup_color_math_R = 0x30;
  suit_pickup_color_math_G = 0x49;
  suit_pickup_color_math_B = 0x90;
  suit_pickup_palette_transition_color = 1;
  Samus_CancelSpeedBoost();
  SetHiLo(&samus_x_extra_run_speed, &samus_x_extra_run_subspeed, 0);
  samus_x_base_speed = 0;
  samus_x_base_subspeed = 0;
  samus_y_subspeed = 0;
  samus_y_speed = 0;
  samus_y_dir = 0;
  morph_ball_bounce_state = kMorphBallBounceState_NoBounce;
  samus_x_accel_mode = 0;
  elevator_status = 0;
  substate = 0;
  suit_pickup_light_beam_pos = 0;
  suit_pickup_light_beam_widening_speed = 0x100;
  for (int i = 510; i >= 0; i -= 2)
    hdma_table_1[i >> 1] = 0x00FF;
  if (samus_movement_type == kMovementType_03_SpinJumping || samus_movement_type == kMovementType_14_WallJumping)
    QueueSfx1_Max9(kSfx1_SpinJumpEnd_Silence);
  if (equipped_items & kItem_VariaSuit)
    samus_pose = kPose_9B_FaceF_VariaGravitySuit;
  else
    samus_pose = kPose_00_FaceF_Powersuit;
  SamusFunc_F433();
  Samus_SetAnimationFrameIfPoseChanged();
  RunSamusCode(kSamusCode_21_LockToSuitAcquisition);
  samus_x_pos = layer1_x_pos + 120;
  samus_prev_x_pos = samus_x_pos;
  samus_y_pos = layer1_y_pos + 136;
  samus_prev_y_pos = samus_y_pos;
  QueueSfx2_Max6(kSfx2_AcquiredSuit);
  static const SpawnHdmaObject_Args kSpawnHdmaObject_91D673 = {
    .hdma_control = HDMA_CONTROL(0, 1, 1),
    .hdma_target = REG(WH0),
    .hdma_instr_list_ptr = addr_kHdmaObject_IList_GravitySuitPickup_Window1_Pos
  };
  SpawnHdmaObject(0x91, &kSpawnHdmaObject_91D673);
}

void InitializeSuitPickupHdma(void) {  // 0x91D692
  reg_TM = 19;
  reg_TMW = 19;
  reg_TS = 4;
  reg_TSW = 4;
  next_gameplay_CGWSEL = 16;
  reg_W12SEL = 0;
  reg_W34SEL = 2;
  reg_WOBJSEL = 32;
  next_gameplay_CGADSUB = 51;
  reg_COLDATA[0] = suit_pickup_color_math_R;
  reg_COLDATA[1] = suit_pickup_color_math_G;
  reg_COLDATA[2] = suit_pickup_color_math_B;
  mov24(&hdma_ptr_1, 0x9800E4);
  mov24(&hdma_ptr_2, 0x98C8E4);
  mov24(&hdma_ptr_3, 0x999098);
  hdma_var_1 = 0;
}


static Func_U8 *const kSamus_PaletteHandlerFuncs[11] = {  // 0x91D6F7
  Samus_HandleScrewAttackSpeedBoostingPals,
  Samus_SpeedBoosterShinePals,
  (Func_U8 *)HandleMiscSamusPalette,
  0,
  0,
  0,
  Samus_HandleShinesparkingPals,
  Samus_HandleCrystalFlashPals,
  Samus_HandleXrayPals,
  HandleVisorPalette,
  nullsub_164,
};

void Samus_HandlePalette(void) {
  if ((samus_special_super_palette_flags & 0x8000) == 0
      && (HandleBeamChargePalettes() & 1
          || !(kSamus_PaletteHandlerFuncs[special_samus_palette_type]() & 1))) {
    CopyToSamusSuitPalette(kSamusPalette_Normal[samus_suit_palette_index >> 1]);
  }
  HandleMiscSamusPalette();
}

/**
* @brief Handles the timer, index, and palette for charging up a beam
*/
uint8 HandleBeamChargePalettes(void) {  // 0x91D743
  if (charged_shot_glow_timer != 0) {
    if (hyper_beam_flag) {
      if ((charged_shot_glow_timer & 1) == 0) {
        if ((charged_shot_glow_timer & 0x1E) == 0) {
          charged_shot_glow_timer = 0;
          return 1;
        }
        CopyToSamusSuitPalette(kSamusPalette_HyperBeam[(charged_shot_glow_timer & 0x1E) >> 1]);
      }
      --charged_shot_glow_timer;
      return 0;
    }
    if (--charged_shot_glow_timer != 0) {
      memset7E(palette_buffer.sprite_pal_4 + 1, 1023, 0x1E);
      return 0;
    }
    else {
      return 1;
    }
  }
  else if (grapple_beam_function == FUNC16(GrappleBeamFunc_Inactive) && flare_counter != 0 && flare_counter >= 60) {
    uint16 samus_palette_entry;
    if (samus_contact_damage_index == kSamusContactDamageIndex_4_PsuedoScrewAttack)
      samus_palette_entry = kSamusPalette_PseudoScrew[samus_suit_palette_index >> 1];
    else
      samus_palette_entry = kSamusPalette_NonPseudoScrew[samus_suit_palette_index >> 1];
    CopyToSamusSuitPalette(*(uint16 *)RomPtr_91(samus_palette_entry + samus_charge_palette_index));
    uint16 next_charge_palette_index = samus_charge_palette_index + 2;
    if (next_charge_palette_index >= 12)
      next_charge_palette_index = 0;
    samus_charge_palette_index = next_charge_palette_index;
    return 0;
  }
  else {
    samus_charge_palette_index = 0;
    return HandleVisorPalette();
  }
}

uint8 HandleVisorPalette(void) {  // 0x91D83F
  if (special_samus_palette_type == 8)
    return 0;
  if (fx_layer_blending_config_a == 40 || fx_layer_blending_config_a == 42) {
    uint16 v1 = samus_visor_palette_timer_index - 1;
    samus_visor_palette_timer_index = v1;
    if ((uint8)v1)
      return 0;
    samus_visor_palette_timer_index = v1 | 5;
    palette_buffer.sprite_pal_4[4] = kSamus_VisorColors[HIBYTE(v1) >> 1];
    int v2 = HIBYTE(v1) + 2;
    if (sign16(v2 - 12)) {
      samus_visor_palette_timer_index = swap16(v2) | (uint8)samus_visor_palette_timer_index;
    } else {
      samus_visor_palette_timer_index = (uint8)samus_visor_palette_timer_index | 0x600;
    }
    return 0;
  } else {
    samus_visor_palette_timer_index = 1537;
    return 0;
  }
}


void HandleMiscSamusPalette(void) {  // 0x91D8A5
  if (!samus_special_super_palette_flags) {
    uint16 v0 = samus_hurt_flash_counter;
    if (!samus_hurt_flash_counter)
      return;
    if (samus_hurt_flash_counter == 2) {
      if (!cinematic_function
          && (frame_handler_beta != FUNC16(Samus_FrameHandlerBeta_SamusBeingDrained)
              || samus_pose != kPose_54_FaceL_Knockback)) {
        QueueSfx1_Max6(kSfx1_SamusDamaged_HighPriority);
        goto LABEL_14;
      }
      v0 = samus_hurt_flash_counter;
    }
    if (!sign16(v0 - 7))
      goto LABEL_17;
    if ((v0 & 1) != 0) {
      CopyToSamusSuitPalette(addr_kSamusPalette_HurtFlash);
      goto LABEL_17;
    }
LABEL_14:
    if (cinematic_function)
      CopyToSamusSuitPalette(addr_kSamusPalette_IntroSamus_Grayscale);
    else
      Samus_LoadSuitPalette();
LABEL_17:;
    uint16 v1 = samus_hurt_flash_counter + 1;
    samus_hurt_flash_counter = v1;
    if (v1 == 40) {
      if (grapple_beam_function == FUNC16(GrappleBeamFunc_Inactive)) {
        if (samus_movement_type == kMovementType_03_SpinJumping || samus_movement_type == kMovementType_14_WallJumping) {
          RunSamusCode(kSamusCode_28_PlaySpinSfxIfSpinJumping);
        } else if (!sign16(flare_counter - 16) && (button_config_shoot & joypad1_lastkeys) != 0) {
          play_resume_charging_beam_sfx = 1;
        }
      } else if (sign16(grapple_beam_function + 0x37AA)) {
        QueueSfx1_Max9(kSfx1_Grappling);
      }
    } else if (!sign16(v1 - 60)) {
      samus_hurt_flash_counter = 0;
    }
    return;
  }
  if ((samus_special_super_palette_flags & 0x8000) != 0) {
    CopyToSamusSuitPalette(kSamus_HyperBeamPalettes[samus_charge_palette_index]);
    bool v2 = (--special_samus_palette_timer & 0x8000) != 0;
    if (!special_samus_palette_timer || v2) {
      special_samus_palette_timer = special_samus_palette_frame;
      if (!sign16(++samus_charge_palette_index - 10))
        samus_charge_palette_index = 0;
    }
  } else {
    if ((samus_special_super_palette_flags & 1) != 0)
      CopyToSamusSuitPalette(kSamus_SpeedBoostingPalettes[samus_suit_palette_index >> 1]);
    else
      Samus_LoadSuitPalette();
    ++samus_special_super_palette_flags;
  }
}


uint8 Samus_HandleScrewAttackSpeedBoostingPals(void) {  // 0x91D9B2
  if ((samus_suit_palette_index & kSuitPaletteIndex_4_Gravity) == 0) {
    uint16 samus_top_bound = Samus_GetTopBound();
    if ((fx_y_pos & 0x8000) != 0) {
      if ((lava_acid_y_pos & 0x8000) == 0 && sign16(lava_acid_y_pos - samus_top_bound))
        return 1;
    } else if (sign16(fx_y_pos - samus_top_bound) && !(fx_liquid_options & kFxLiquidOption_4_LiquidPhysicsDisabled)) {
      return 1;
    }
  }
  if (samus_movement_type == kMovementType_03_SpinJumping) {
    if ((equipped_items & kItem_ScrewAttack) == 0)
      goto LABEL_10;
    if (samus_anim_frame) {
      if (!sign16(samus_anim_frame - 27))
        return 0;
      goto LABEL_18;
    }
    goto LABEL_21;
  }
  if (samus_movement_type == kMovementType_14_WallJumping) {
    if ((equipped_items & kItem_ScrewAttack) == 0)
      return 1;
    if (!sign16(samus_anim_frame - 3)) {
LABEL_18:;
      uint16 R36 = kSamusPal_ScrewAttack[samus_suit_palette_index >> 1];
      uint16 v1 = *(uint16 *)RomPtr_91(R36 + special_samus_palette_frame);
      CopyToSamusSuitPalette(v1);
      uint16 v2 = special_samus_palette_frame + 2;
      if (special_samus_palette_frame >= 10)
        v2 = 0;
      special_samus_palette_frame = v2;
      return 1;
    }
LABEL_21:
    special_samus_palette_frame = 0;
    return 1;
  }
LABEL_10:
  if (speed_boost_counter != SPEED_BOOST_THRESHOLD)
    return 1;
  bool v3 = (--special_samus_palette_timer & 0x8000) != 0;
  if (!special_samus_palette_timer || v3) {
    special_samus_palette_timer = 4;
    uint16 R36 = kSamusPal_SpeedBoost[samus_suit_palette_index >> 1];
    // Bugfix: The original game can do an out of bounds read here.
    if (special_samus_palette_frame > 6)
      special_samus_palette_frame = 6;
    uint16 v4 = *(uint16 *)RomPtr_91(R36 + special_samus_palette_frame);
    CopyToSamusSuitPalette(v4);
    uint16 v5 = special_samus_palette_frame + 2;
    if (special_samus_palette_frame >= 6)
      v5 = 6;
    special_samus_palette_frame = v5;
  }
  return 1;
}


uint8 Samus_SpeedBoosterShinePals(void) {  // 0x91DAC7
  uint16 v0 = samus_shine_timer;
  if (samus_shine_timer == 170) {
    uint16 v4 = samus_shine_timer;
    QueueSfx3_Max9(kSfx3_StoredShinespark);
    v0 = v4;
  }
  samus_shine_timer = v0 - 1;
  if ((int16)(v0 - 1) <= 0) {
    special_samus_palette_frame = 0;
    special_samus_palette_type = 0;
    return 0;
  } else {
    uint16 R36 = kSamusPal_SpeedBoostShine[samus_suit_palette_index >> 1];
    uint16 v1 = *(uint16 *)RomPtr_91(R36 + special_samus_palette_frame);
    CopyToSamusSuitPalette(v1);
    uint16 v2 = special_samus_palette_frame + 2;
    if (!sign16(special_samus_palette_frame - 10))
      v2 = 0;
    special_samus_palette_frame = v2;
    return 1;
  }
}

uint8 Samus_HandleShinesparkingPals(void) {  // 0x91DB3A
  bool v0 = (--samus_shine_timer & 0x8000) != 0;
  if (!samus_shine_timer || v0) {
    special_samus_palette_type = 0;
    special_samus_palette_frame = 0;
    return 0;
  } else {
    uint16 R36 = kSamusPal_Shinespark[samus_suit_palette_index >> 1];
    uint16 v1 = *(uint16 *)RomPtr_91(R36 + special_samus_palette_frame);
    CopyToSamusSuitPalette(v1);
    uint16 v2 = special_samus_palette_frame + 2;
    if (!sign16(special_samus_palette_frame - 6))
      v2 = 0;
    special_samus_palette_frame = v2;
    return 1;
  }
}

uint8 Samus_HandleCrystalFlashPals(void) {  // 0x91DB93
  if ((samus_shine_timer & 0x8000) != 0) {
    WriteBeamPalette_A(equipped_beams);
    special_samus_palette_type = 0;
    special_samus_palette_frame = 0;
    special_samus_palette_timer = 0;
    samus_shine_timer = 0;
    return 0;
  } else {
    if ((int16)--samus_shine_timer <= 0) {
      samus_shine_timer = 5;
      Samus_Copy6PalColors(kSamusPal_CrystalFlash10to15[special_samus_palette_frame >> 1]);
      uint16 v0 = special_samus_palette_frame + 2;
      if (!sign16(special_samus_palette_frame - 10))
        v0 = 0;
      special_samus_palette_frame = v0;
    }
    bool v1 = (int16)-- * (uint16 *)&suit_pickup_color_math_B < 0;
    if (!*(uint16 *)&suit_pickup_color_math_B || v1) {
      *(uint16 *)&suit_pickup_color_math_B = *(uint16 *)((uint8 *)&kSamusPal_CrystalFlash0to9[0].timer + special_samus_palette_timer);
      Samus_Copy10PalColors(*(VoidP *)((uint8 *)&kSamusPal_CrystalFlash0to9[0].pal_ptr + special_samus_palette_timer));
      uint16 v2 = special_samus_palette_timer + 4;
      if (!sign16(special_samus_palette_timer - 36))
        v2 = 0;
      special_samus_palette_timer = v2;
    }
    return 1;
  }
}

void Samus_Copy10PalColors(uint16 v0) {  // 0x91DC34
  memcpy(&palette_buffer.sprite_pal_6[0], RomPtr_9B(v0), 20);
}

void Samus_Copy6PalColors(uint16 j) {  // 0x91DC82
  memcpy(&palette_buffer.sprite_pal_6[10], RomPtr_9B(j), 12);
}

uint8 Samus_HandleXrayPals(void) {  // 0x91DCB4
  if ((demo_timer_counter & 0x8000) != 0) {
    special_samus_palette_type = 0;
    special_samus_palette_frame = 0;
    special_samus_palette_timer = 0;
    demo_timer_counter = 0;
    return 0;
  } else {
    if (!demo_timer_counter) {
      if (sign16(demo_input_pre_instr - 2)) {
        bool v0 = (--special_samus_palette_timer & 0x8000) != 0;
        if (!special_samus_palette_timer || v0) {
          special_samus_palette_timer = 5;
          palette_buffer.sprite_pal_4[4] = kSamus_VisorColors[special_samus_palette_frame >> 1];
          if (sign16(special_samus_palette_frame - 4))
            special_samus_palette_frame += 2;
        }
        return 1;
      }
      special_samus_palette_frame = 6;
      special_samus_palette_timer = 1;
      demo_timer_counter = 1;
    }
    bool v2 = (--special_samus_palette_timer & 0x8000) != 0;
    if (special_samus_palette_timer && !v2)
      return 1;
    special_samus_palette_timer = 5;
    palette_buffer.sprite_pal_4[4] = kSamus_VisorColors[special_samus_palette_frame >> 1];
    uint16 v3 = special_samus_palette_frame + 2;
    if (!sign16(special_samus_palette_frame - 10))
      v3 = 6;
    special_samus_palette_frame = v3;
    return 1;
  }
}

uint8 nullsub_164(void) {  // 0x91DD31
  return 0;
}

void CopyToSamusSuitPalette(uint16 k) {  // 0x91DD5B
  memcpy(palette_buffer.sprite_pal_4, (uint16 *)RomPtr_9B(k), sizeof(palette_buffer.sprite_pal_4));
}

void CopyToSamusSuitTargetPalette(uint16 k) {  // 0x91DDD7
  memcpy(target_palettes.sprite_pal_4, (uint16 *)RomPtr_9B(k), sizeof(target_palettes.sprite_pal_4));
}

void Samus_CancelSpeedBoost(void) {  // 0x91DE53
  if (samus_has_momentum_flag) {
    samus_has_momentum_flag = 0;
    speed_boost_timer = 0;
    speed_boost_counter = 0;
    special_samus_palette_frame = 0;
    special_samus_palette_timer = 0;
    if (equipped_items & kItem_GravitySuit) {
      CopyToSamusSuitPalette(addr_kSamusPalette_GravitySuit);
    }
    else if (equipped_items & kItem_VariaSuit) {
      CopyToSamusSuitPalette(addr_kSamusPalette_VariaSuit);
    }
    else {
      CopyToSamusSuitPalette(addr_kSamusPalette_GravitySuit);
    }
  }
  if ((speed_echoes_index & 0x8000) == 0) {
    speed_echoes_index = -1;
    if (samus_pose_x_dir == kSamusXDir_FaceLeft) {
      speed_echo_xspeed[0] = -8;
      speed_echo_xspeed[1] = -8;
    }
    else {
      speed_echo_xspeed[0] = 8;
      speed_echo_xspeed[1] = 8;
    }
  }
}

void Samus_LoadSuitPalette(void) {  // 0x91DEBA
  if (equipped_items & kItem_GravitySuit) {
    CopyToSamusSuitPalette(addr_kSamusPalette_GravitySuit);
  }
  else if (equipped_items & kItem_VariaSuit) {
    CopyToSamusSuitPalette(addr_kSamusPalette_VariaSuit);
  }
  else {
    CopyToSamusSuitPalette(addr_kSamusPalette_GravitySuit);
  }
}

void Samus_LoadSuitTargetPalette(void) {  // 0x91DEE6
  if (equipped_items & kItem_GravitySuit) {
    CopyToSamusSuitTargetPalette(addr_kSamusPalette_GravitySuit);
  }
  else if (equipped_items & kItem_VariaSuit) {
    CopyToSamusSuitTargetPalette(addr_kSamusPalette_VariaSuit);
  }
  else {
    CopyToSamusSuitTargetPalette(addr_kSamusPalette_GravitySuit);
  }
}

void Samus_RestoreHealth(uint16 a) {  // 0x91DF12
  samus_health += a;
  if (samus_health >= samus_max_health) {
    uint16 health_overflow = samus_health - samus_max_health;
    uint16 min_health = samus_reserve_health + health_overflow;
    if (min_health >= samus_max_reserve_health)
        min_health = samus_max_reserve_health;
    samus_reserve_health = min_health;
    if (samus_reserve_health != 0) {
      if (reserve_health_mode == kReserveHealthMode_0_None)
        reserve_health_mode = kReserveHealthMode_1_Auto;
    }
    samus_health = samus_max_health;
  }
}

void Samus_DealDamage(uint16 a) {  // 0x91DF51
  if ((a & 0x8000) == 0) {
    if (a != 300 && !time_is_frozen_flag) {
      samus_health -= a;
      if ((samus_health & 0x8000) != 0)
        samus_health = 0;
    }
  } else {
    InvalidInterrupt_Crash();
  }
}

void Samus_RestoreMissiles(uint16 a) {  // 0x91DF80
  samus_missiles += a;
  if (samus_missiles >= samus_max_missiles) {
    uint16 missile_overflow = samus_missiles - samus_max_missiles;
    if (samus_max_missiles < 99) {
      samus_reserve_missiles += missile_overflow;
      if (samus_reserve_missiles >= samus_max_missiles)
        samus_reserve_missiles = samus_max_missiles;
    } else {
      samus_reserve_missiles += missile_overflow;
      if (samus_reserve_missiles >= 99)
        samus_reserve_missiles = 99;
    }
    samus_missiles = samus_max_missiles;
  }
}

void Samus_RestoreSuperMissiles(uint16 a) {  // 0x91DFD3
  samus_super_missiles += a;
  if (samus_super_missiles > samus_max_super_missiles)
    samus_super_missiles = samus_max_super_missiles;
}

void Samus_RestorePowerBombs(uint16 a) {  // 0x91DFF0
  samus_power_bombs += a;
  if (samus_power_bombs > samus_max_power_bombs)
    samus_power_bombs = samus_max_power_bombs;
}

void Samus_Initialize(void) {  // 0x91E00D
  static const uint16 word_909EAF = 0;
  static const uint16 word_909EAD = 1;
  static const uint16 word_909EB3 = 0;
  static const uint16 word_909EB1 = 1;
  static const uint16 word_909EA1 = 0x1c00;
  static const uint16 word_909EA7 = 0;
  uint16 r18 = debug_invincibility;
  uint16 start_samus_ram = 0xA02;
  uint16 samus_ram_size = 0xE0B - start_samus_ram;
  memset(g_ram + start_samus_ram, 0, samus_ram_size);
  if (game_state != kGameState_40_TransitionToDemo) {
    frame_handler_alfa = FUNC16(Samus_FrameHandlerBeta_DoNothing);
    if (loading_game_state == kLoadingGameState_22_EscapingCeres) {
      frame_handler_beta = FUNC16(Samus_FrameHandlerBeta_SamusLocked);
      samus_draw_handler = FUNC16(Samus_DrawHandler_Default);
      samus_new_pose_command = -1;
      samus_new_pose_interrupted_command = 0;
      samus_new_pose_transitional_command = 0;
      Samus_LoadSuitPalette();
      samus_input_handler = FUNC16(Samus_InputHandler_Normal);
    } else {
      frame_handler_beta = FUNC16(Samus_FrameHandlerBeta_SamusAppears);
      samus_draw_handler = FUNC16(Samus_DrawHandler_Default);
      samus_new_pose_command = 0;
      samus_new_pose_interrupted_command = 0;
      samus_new_pose_transitional_command = 0;
      samus_input_handler = FUNC16(Samus_InputHandler_Normal);
      debug_invincibility = r18;
    }
  }
  samus_new_pose = -1;
  samus_new_pose_interrupted = -1;
  samus_new_pose_transitional = -1;
  if (area_index == kArea_6_Ceres)
    frame_handler_gamma = FUNC16(Samus_FrameHandlerGamma_HandleTimer);
  else
    frame_handler_gamma = FUNC16(nullsub_152);
  samus_movement_handler = FUNC16(Samus_MovementHandler_Normal);
  UNUSED_word_7E0A5E = -2764;
  samus_prev_health_for_flash = 50;
  samus_visor_palette_timer_index = 1537;
  uint16 v1 = 0;
  do {
    projectile_pre_instructions[v1 >> 1] = FUNC16(ProjPreInstr_Empty);
    v1 += 2;
  } while ((int16)(v1 - 20) < 0);
  grapple_beam_function = FUNC16(GrappleBeamFunc_Inactive);
  enable_horiz_slope_coll = 3;
  samus_hurt_flash_counter = 0;
  samus_special_super_palette_flags = 0;
  camera_x_subspeed = word_909EAF;
  camera_x_speed = word_909EAD;
  camera_y_subspeed = word_909EB3;
  camera_y_speed = word_909EB1;
  for (int i = 510; i >= 0; i -= 2)
    hdma_table_1[i >> 1] = 255;
  samus_y_subaccel = word_909EA1;
  samus_y_accel = word_909EA7;
  fx_y_pos = -1;
  lava_acid_y_pos = -1;
  UpdateBeamTilesAndPalette();
  cinematic_function = 0;
  samus_pose = kPose_00_FaceF_Powersuit;
  *(uint16 *)&samus_pose_x_dir = 0;
  samus_prev_pose = 0;
  *(uint16 *)&samus_prev_pose_x_dir = 0;
  samus_last_different_pose = 0;
  *(uint16 *)&samus_last_different_pose_x_dir = 0;
  enemy_index_to_shake = -1;
  hud_item_index = kHudItem_0_Nothing;
  samus_auto_cancel_hud_item_index = 0;
  samus_invincibility_timer = 0;
  samus_knockback_timer = 0;
  samus_hurt_flash_counter = 0;
  debug_invincibility = 0;
  if (game_state == kGameState_40_TransitionToDemo)
    LoadDemoData();
  samus_prev_health_for_flash = samus_health;
}

uint8 Xray_Initialize(void) {  // 0x91E16D
  static const uint8 kXray_InitalizeIfMovementType[28] = {
  1, 1, 0, 0, 0, 2, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 0, 0,
  };

  if (cooldown_timer == 7 && bomb_counter == 5 && samus_x_speed_divisor == 2
      || !sign16(samus_pose - kPose_A4_FaceR_LandJump)
      && (sign16(samus_pose - kPose_A8_FaceR_Grappling)
          || !sign16(samus_pose - kPose_E0_FaceR_LandJump_AimU) && sign16(samus_pose - kPose_E8_FaceR_Drained_CrouchFalling))
      || game_state != kGameState_8_MainGameplay
      || power_bomb_explosion_status != kPowerBombExplosionStatus_Inactive
      || samus_y_speed != 0
      || samus_y_subspeed != 0
      || kXray_InitalizeIfMovementType[samus_prev_movement_type_] == 0) {
    return 0;
  }
  if (kXray_InitalizeIfMovementType[samus_movement_type] == 1) {
    if (samus_pose_x_dir == kSamusXDir_FaceLeft)
      samus_new_pose_interrupted = kPose_D6_FaceL_Xray_Stand;
    else
      samus_new_pose_interrupted = kPose_D5_FaceR_Xray_Stand;
  } else {
    if (kXray_InitalizeIfMovementType[samus_movement_type] != 2)
      return 0;
    if (samus_pose_x_dir == kSamusXDir_FaceLeft)
      samus_new_pose_interrupted = kPose_DA_FaceL_Xray_Crouch;
    else
      samus_new_pose_interrupted = kPose_D9_FaceR_Xray_Crouch;
  }
  time_is_frozen_flag = 1;
  samus_new_pose_interrupted_command = 5;
  for (int i = 510; i >= 0; i -= 2)
    hdma_table_1[i >> 1] = 255;
  DisableEprojs();
  DisablePLMs();
  DisableAnimtiles();
  DisablePaletteFx();
  mov24(&hdma_ptr_1, 0x980001);
  *(uint16 *)((uint8 *)&demo_num_input_frames + 1) = 0;
  demo_input_prev = -26424;
  mov24(&hdma_ptr_3, 0x999098);
  hdma_var_1 = 0;
  demo_input_pre_instr = 0;
  demo_input_instr_timer = 0;
  demo_input_instr_ptr = 0;
  demo_input = 0;
  demo_input_new = 0;
  if (samus_pose_x_dir == kSamusXDir_FaceLeft)
    xray_angle = 192;
  else
    xray_angle = 64;
  return 1;
}

void SetNonXraySamusPose(void) {  // 0x91E2AD
  if (samus_movement_type == kMovementType_05_Crouching) {
    if (samus_pose_x_dir == kSamusXDir_FaceLeft)
      samus_pose = kPose_28_FaceL_Crouch;
    else
      samus_pose = kPose_27_FaceR_Crouch;
  } else if (samus_pose_x_dir == kSamusXDir_FaceLeft) {
    samus_pose = kPose_02_FaceL_Normal;
  } else {
    samus_pose = kPose_01_FaceR_Normal;
  }
  SamusFunc_F433();
  Samus_SetAnimationFrameIfPoseChanged();
  samus_last_different_pose = samus_prev_pose;
  *(uint16 *)&samus_last_different_pose_x_dir = *(uint16 *)&samus_prev_pose_x_dir;
  samus_prev_pose = samus_pose;
  *(uint16 *)&samus_prev_pose_x_dir = *(uint16 *)&samus_pose_x_dir;
  samus_movement_handler = FUNC16(Samus_MovementHandler_Normal);
  samus_input_handler = FUNC16(Samus_InputHandler_Normal);
  demo_timer_counter = -1;
  uint16 r18 = kPoseParams[samus_pose].y_radius - samus_y_radius;
  if ((r18 & 0x8000) == 0) {
    samus_y_pos -= r18;
    samus_prev_y_pos = samus_y_pos;
  }
  EnableEprojs();
  EnablePLMs();
  EnableAnimtiles();
  EnablePaletteFx();
}

void MakeSamusFaceForward(void) {  // 0x91E3F6
  if ((equipped_items & kItem_GravitySuit) != 0 || (equipped_items & kItem_VariaSuit) != 0)
    samus_pose = kPose_9B_FaceF_VariaGravitySuit;
  else
    samus_pose = kPose_00_FaceF_Powersuit;
  SamusFunc_F433();
  Samus_SetAnimationFrameIfPoseChanged();
  samus_last_different_pose = samus_prev_pose;
  *(uint16 *)&samus_last_different_pose_x_dir = *(uint16 *)&samus_prev_pose_x_dir;
  samus_prev_pose = samus_pose;
  *(uint16 *)&samus_prev_pose_x_dir = *(uint16 *)&samus_pose_x_dir;
  if (samus_y_radius != 24) {
    samus_y_pos -= 3;
    samus_prev_y_pos = samus_y_pos;
  }
  frame_handler_alfa = FUNC16(Samus_FrameHandlerAlfa_SamusLocked);
  frame_handler_beta = FUNC16(Samus_FrameHandlerBeta_SamusLocked);
  samus_new_pose = -1;
  samus_new_pose_interrupted = -1;
  samus_new_pose_transitional = -1;
  samus_new_pose_command = 0;
  samus_new_pose_interrupted_command = 0;
  samus_new_pose_transitional_command = 0;
  RunSamusCode(kSamusCode_31_KillGrappleBeam);
  SetHiLo(&samus_x_extra_run_speed, &samus_x_extra_run_subspeed, 0);
  samus_x_base_speed = 0;
  samus_x_base_subspeed = 0;
  samus_y_subspeed = 0;
  samus_y_speed = 0;
  samus_y_dir = 0;
  morph_ball_bounce_state = kMorphBallBounceState_NoBounce;
  samus_x_accel_mode = 0;
  flare_counter = 0;
  flare_animation_frame = 0;
  flare_slow_sparks_anim_frame = 0;
  flare_fast_sparks_anim_frame = 0;
  flare_animation_timer = 0;
  flare_slow_sparks_anim_timer = 0;
  flare_fast_sparks_anim_timer = 0;
  Samus_LoadSuitPalette();
}

static Func_U8 *const kDrainedSamusHandler[5] = {  // 0x91E4AD
  DrainedSamusHandler_0_LetSamusFall,
  DrainedSamusHandler_1_SetSamusStandingDrainedPose,
  DrainedSamusHandler_2_ReleaseSamusFromDrainedPose,
  DrainedSamusHandler_3_EnableHyperBeam,
  DrainedSamusHandler_4_SetSamusCrouchOrFallDrainedPose,
};

void DrainedSamusHandler(uint16 a) {
  if (kDrainedSamusHandler[a]() & 1) {
    samus_last_different_pose = samus_prev_pose;
    *(uint16 *)&samus_last_different_pose_x_dir = *(uint16 *)&samus_prev_pose_x_dir;
    samus_prev_pose = samus_pose;
    *(uint16 *)&samus_prev_pose_x_dir = *(uint16 *)&samus_pose_x_dir;
    samus_new_pose = -1;
    samus_new_pose_interrupted = -1;
    samus_new_pose_transitional = -1;
    samus_new_pose_command = 0;
    samus_new_pose_interrupted_command = 0;
    samus_new_pose_transitional_command = 0;
  }
}

uint8 DrainedSamusHandler_0_LetSamusFall(void) {  // 0x91E4F8
  samus_y_pos -= 21 - samus_y_radius;
  samus_prev_y_pos = samus_y_pos;
  if (samus_pose_x_dir == kSamusXDir_FaceLeft)
    samus_pose = kPose_E9_FaceL_Drained_CrouchFalling;
  else
    samus_pose = kPose_E8_FaceR_Drained_CrouchFalling;
  samus_anim_frame_skip = 2;
  SamusFunc_F433();
  Samus_SetAnimationFrameIfPoseChanged();
  samus_y_radius = kPoseParams[samus_pose].y_radius;
  samus_x_base_speed = 0;
  samus_x_base_subspeed = 0;
  samus_y_subspeed = 0;
  samus_y_speed = 0;
  samus_y_dir = 2;
  flare_counter = 0;
  flare_animation_frame = 0;
  flare_slow_sparks_anim_frame = 0;
  flare_fast_sparks_anim_frame = 0;
  flare_animation_timer = 0;
  flare_slow_sparks_anim_timer = 0;
  flare_fast_sparks_anim_timer = 0;
  Samus_LoadSuitPalette();
  return 1;
}

uint8 DrainedSamusHandler_1_SetSamusStandingDrainedPose(void) {  // 0x91E571
  samus_anim_frame_timer = 16;
  samus_anim_frame = 0;
  if (samus_pose_x_dir == kSamusXDir_FaceLeft)
    samus_pose = kPose_EB_FaceL_Drained_Stand;
  else
    samus_pose = kPose_EA_FaceR_Drained_Stand;
  frame_handler_gamma = FUNC16(nullsub_152);
  return 1;
}

uint8 DrainedSamusHandler_2_ReleaseSamusFromDrainedPose(void) {  // 0x91E59B
  if (samus_pose == kPose_E8_FaceR_Drained_CrouchFalling || samus_pose == kPose_E9_FaceL_Drained_CrouchFalling) {
    samus_anim_frame_timer = 1;
    samus_anim_frame = 13;
  } else if (samus_pose == kPose_EA_FaceR_Drained_Stand || samus_pose == kPose_EB_FaceL_Drained_Stand) {
    samus_anim_frame_timer = 1;
    samus_anim_frame = 4;
  }
  samus_y_radius = kPoseParams[samus_pose].y_radius;
  samus_x_base_speed = 0;
  samus_x_base_subspeed = 0;
  samus_y_subspeed = 0;
  samus_y_speed = 0;
  samus_y_dir = 2;
  return 1;
}

uint8 DrainedSamusHandler_3_EnableHyperBeam(void) {  // 0x91E5F0
  equipped_beams = (kBeam_Charge | kBeam_Plasma | kBeam_Wave);
  UpdateBeamTilesAndPalette();
  SpawnPalfxObject(addr_kPalfx_HyperBeam);
  hyper_beam_flag = FUNC16(Samus_InputHandler);
  play_resume_charging_beam_sfx = 0;
  return 0;
}

uint8 DrainedSamusHandler_4_SetSamusCrouchOrFallDrainedPose(void) {  // 0x91E60C
  samus_anim_frame_timer = 16;
  samus_anim_frame = 8;
  if (samus_pose_x_dir == kSamusXDir_FaceLeft)
    samus_pose = kPose_E9_FaceL_Drained_CrouchFalling;
  else
    samus_pose = kPose_E8_FaceR_Drained_CrouchFalling;
  return 1;
}

void nullsub_17(void) {}

static Func_V *const off_91E6E1[28] = {  // 0x91E633
  Samus_UpdatePoseFromEquipmentChange_Standing,
  nullsub_17,
  nullsub_17,
  Samus_UpdatePoseFromEquipmentChange_SpinJump,
  Samus_UpdatePoseFromEquipmentChange_MorphBall,
  nullsub_17,
  nullsub_17,
  nullsub_17,
  Samus_UpdatePoseFromEquipmentChange_MorphBall,
  nullsub_17,
  nullsub_17,
  nullsub_17,
  nullsub_17,
  nullsub_17,
  nullsub_17,
  nullsub_17,
  nullsub_17,
  Samus_UpdatePoseFromEquipmentChange_SpringBall,
  Samus_UpdatePoseFromEquipmentChange_SpringBall,
  Samus_UpdatePoseFromEquipmentChange_SpringBall,
  Samus_UpdatePoseFromEquipmentChange_WallJump,
  nullsub_17,
  nullsub_17,
  nullsub_17,
  nullsub_17,
  nullsub_17,
  nullsub_17,
  nullsub_17,
};

void Samus_UpdatePoseFromEquipmentChange(void) {
  off_91E6E1[samus_movement_type]();
  if ((equipped_items & kItem_SpeedBooster) != 0) {
    if (samus_has_momentum_flag && speed_boost_timer == 0 && speed_boost_counter == 0) {
      special_samus_palette_timer = 0;
      special_samus_palette_frame = 0;
      speed_boost_timer = LOBYTE(kSpeedBoostToCtr[0]);
      speed_boost_counter = HIBYTE(kSpeedBoostToCtr[0]);
    }
  } else {
    speed_echoes_index = 0;
    speed_echo_xspeed[0] = 0;
    speed_echo_xspeed[1] = 0;
    samus_has_momentum_flag = 0;
    speed_boost_timer = 0;
    speed_boost_counter = 0;
    special_samus_palette_frame = 0;
    special_samus_palette_timer = 0;
    speed_echo_xpos[0] = 0;
    speed_echo_xpos[1] = 0;
    speed_echo_ypos[0] = 0;
    speed_echo_ypos[1] = 0;
  }
  if (grapple_beam_function == FUNC16(GrappleBeamFunc_Inactive)) {
    if ((equipped_beams & kBeam_Charge) != 0) {
      if (!sign16(flare_counter - 16))
        QueueSfx1_Max6(kSfx1_ResumeChargingBeam);
    } else {
      flare_counter = 0;
      flare_animation_frame = 0;
      flare_slow_sparks_anim_frame = 0;
      flare_fast_sparks_anim_frame = 0;
      flare_animation_timer = 0;
      flare_slow_sparks_anim_timer = 0;
      flare_fast_sparks_anim_timer = 0;
    }
  } else {
    LoadProjectilePalette(2);
    QueueSfx1_Max6(kSfx1_Grappling);
  }
  Samus_LoadSuitPalette();
  if (sign16(samus_health - 31))
    QueueSfx3_Max6(kSfx3_LowHealthBeep);
}

void Samus_UpdatePreviousPose_0(void) {  // 0x91E719
  samus_last_different_pose = samus_prev_pose;
  *(uint16 *)&samus_last_different_pose_x_dir = *(uint16 *)&samus_prev_pose_x_dir;
  samus_prev_pose = samus_pose;
  *(uint16 *)&samus_prev_pose_x_dir = *(uint16 *)&samus_pose_x_dir;
}

void Samus_UpdatePoseFromEquipmentChange_Standing(void) {  // 0x91E733
  if (samus_pose) {
    if (samus_pose == kPose_9B_FaceF_VariaGravitySuit && (equipped_items & kItem_VariaSuit) == 0 && (equipped_items & kItem_GravitySuit) == 0) {
      samus_pose = kPose_00_FaceF_Powersuit;
      goto LABEL_10;
    }
  } else if ((equipped_items & kItem_VariaSuit) != 0 || (equipped_items & kItem_GravitySuit) != 0) {
    samus_pose = kPose_9B_FaceF_VariaGravitySuit;
LABEL_10:
    SamusFunc_F433();
    Samus_SetAnimationFrameIfPoseChanged();
    Samus_UpdatePreviousPose_0();
  }
}

void Samus_UpdatePoseFromEquipmentChange_SpinJump(void) {  // 0x91E776
  if (samus_pose_x_dir == kSamusXDir_FaceLeft)
    *(uint16 *)&samus_prev_pose_x_dir = 260;
  else
    *(uint16 *)&samus_prev_pose_x_dir = 264;
  if (samus_pose != kPose_81_FaceR_Screwattack && samus_pose != kPose_82_FaceL_Screwattack) {
    if (samus_pose != kPose_1B_FaceR_SpaceJump && samus_pose != kPose_1C_FaceL_SpaceJump)
      goto LABEL_18;
    if ((equipped_items & kItem_ScrewAttack) != 0) {
      if (samus_pose_x_dir == kSamusXDir_FaceLeft)
        samus_pose = kPose_82_FaceL_Screwattack;
      else
        samus_pose = kPose_81_FaceR_Screwattack;
      goto LABEL_18;
    }
    goto LABEL_15;
  }
  if ((equipped_items & kItem_ScrewAttack) == 0) {
LABEL_15:
    if (samus_pose_x_dir == kSamusXDir_FaceLeft)
      samus_pose = kPose_1A_FaceL_SpinJump;
    else
      samus_pose = kPose_19_FaceR_SpinJump;
  }
LABEL_18:
  SamusFunc_F433();
  Samus_SetAnimationFrameIfPoseChanged();
  if (samus_pose_x_dir == kSamusXDir_FaceLeft)
    *(uint16 *)&samus_prev_pose_x_dir = 772;
  else
    *(uint16 *)&samus_prev_pose_x_dir = 776;
  Samus_UpdatePreviousPose_0();
}

void Samus_UpdatePoseFromEquipmentChange_MorphBall(void) {  // 0x91E83A
  if ((equipped_items & kItem_SpringBall) != 0) {
    if (samus_pose_x_dir == kSamusXDir_FaceLeft)
      samus_pose = kPose_7A_FaceL_Springball_Ground;
    else
      samus_pose = kPose_79_FaceR_Springball_Ground;
    SamusFunc_F433();
    Samus_SetAnimationFrameIfPoseChanged();
    Samus_UpdatePreviousPose_0();
  }
}

void Samus_UpdatePoseFromEquipmentChange_SpringBall(void) {  // 0x91E867
  if ((equipped_items & kItem_SpringBall) == 0) {
    if (samus_pose_x_dir == kSamusXDir_FaceLeft)
      samus_pose = kPose_41_FaceL_Morphball_Ground;
    else
      samus_pose = kPose_1D_FaceR_Morphball_Ground;
    SamusFunc_F433();
    Samus_SetAnimationFrameIfPoseChanged();
    Samus_UpdatePreviousPose_0();
  }
}

void Samus_UpdatePoseFromEquipmentChange_WallJump(void) {  // 0x91E894
  if ((equipped_items & kItem_ScrewAttack) != 0)
    samus_anim_frame = 23;
  else
    samus_anim_frame = 3;
}

void nullsub_18(void) {
}

static Func_V *const kSamus_HandleTransFromBlockColl[6] = {  // 0x91E8B6
  [kSolidVertCollResult_0_NoChange]   = nullsub_18,
  [kSolidVertCollResult_1_Landed]     = Samus_HandleTransFromBlockColl_1,
  [kSolidVertCollResult_2_Falling]    = Samus_HandleTransFromBlockColl_2,
  [kSolidVertCollResult_3_Unused]     = Samus_HandleTransFromBlockColl_3,
  [kSolidVertCollResult_4_HitCeiling] = Samus_HandleTransFromBlockColl_4,
  [kSolidVertCollResult_5_WallJumped] = Samus_HandleTransFromBlockColl_5,
};

void Samus_HandleTransFromBlockColl(void) {
  if (samus_solid_vertical_coll_result != kSolidVertCollResult_0_NoChange)
    kSamus_HandleTransFromBlockColl[LOBYTE(samus_solid_vertical_coll_result)]();
}
void Samus_HandleTransFromBlockColl_3(void) {  // 0x91E8D8
  samus_new_pose = samus_pose;
  samus_new_pose_command = 5;
}

void Samus_HandleTransFromBlockColl_4(void) {  // 0x91E8E5
  samus_new_pose = samus_pose;
  samus_new_pose_command = 5;
}

uint8 nullsub_18_U8(void) {
  return 0;
}

void Samus_HandleTransFromBlockColl_2(void) {  // 0x91E8F2
  if (HIBYTE(samus_solid_vertical_coll_result) != kDownwardCollResult_Falling_4_NoChange) {
    uint16 v0 = 4 * HIBYTE(samus_solid_vertical_coll_result);
    if (samus_pose_x_dir == kSamusXDir_FaceLeft)
      samus_new_pose = kSamusNewPose_Falling[(v0 >> 1) + 1];
    else
      samus_new_pose = kSamusNewPose_Falling[v0 >> 1];
    samus_new_pose_command = 5;
  }
}

static Func_U8 *const off_91E951[6] = {  // 0x91E931
  Samus_HandleTransFromBlockColl_1_0,
  Samus_HandleTransFromBlockColl_1_1,
  Samus_HandleTransFromBlockColl_1_2,
  Samus_HandleTransFromBlockColl_1_3,
  nullsub_18_U8,
  Samus_HandleTransFromBlockColl_1_5,
};

void Samus_HandleTransFromBlockColl_1(void) {
  if (HIBYTE(samus_solid_vertical_coll_result) != kDownwardCollResult_Landed_4_NoChange) {
    if (off_91E951[HIBYTE(samus_solid_vertical_coll_result)]() & 1)
      samus_new_pose_command = 0;
    else
      samus_new_pose_command = 5;
  }
}

uint8 Samus_HandleTransFromBlockColl_1_0(void) {  // 0x91E95D
  int16 v0;

  if (samus_prev_movement_type == kMovementType_03_SpinJumping
      || samus_prev_movement_type == kMovementType_14_WallJumping) {
    if (samus_pose_x_dir == kSamusXDir_FaceLeft)
      samus_new_pose = kPose_A7_FaceL_LandSpinJump;
    else
      samus_new_pose = kPose_A6_FaceR_LandSpinJump;
    return 0;
  } else {
    v0 = kPoseParams[samus_pose].direction_shots_fired;
    if (v0 == 255) {
      if (samus_pose_x_dir == kSamusXDir_FaceLeft)
        samus_new_pose = kPose_A5_FaceL_LandJump;
      else
        samus_new_pose = kPose_A4_FaceR_LandJump;
      return 0;
    } else {
      if (v0 != 2 && v0 != 7)
        goto LABEL_6;
      if ((button_config_shoot & joypad1_lastkeys) == 0) {
        v0 = kPoseParams[samus_pose].direction_shots_fired;
LABEL_6:
        samus_new_pose = kSamusNewPose_Landing[v0];
        return 0;
      }
      if (samus_pose_x_dir == kSamusXDir_FaceLeft)
        samus_new_pose = kPose_E7_FaceL_LandJump_Fire;
      else
        samus_new_pose = kPose_E6_FaceR_LandJump_Fire;
      return 0;
    }
  }
}

uint8 Samus_HandleTransFromBlockColl_1_1(void) {  // 0x91EA07
  if (morph_ball_bounce_state != kMorphBallBounceState_NoBounce) {
    if (morph_ball_bounce_state == kMorphBallBounceState_Morph_FirstBounce) {
      samus_new_pose = samus_pose;
      return 0;
    }
    if (morph_ball_bounce_state != kMorphBallBounceState_Morph_SecondBounce)
      Unreachable();
  }
  else if ((int16)samus_y_speed >= 3) {
    samus_new_pose = samus_pose;
    return 0;
  }

  if (samus_pose_x_dir == kSamusXDir_FaceLeft)
    samus_new_pose = kPose_41_FaceL_Morphball_Ground;
  else
    samus_new_pose = kPose_1D_FaceR_Morphball_Ground;
  return 0;
}

uint8 Samus_HandleTransFromBlockColl_1_2(void) {  // 0x91EA48
  if (samus_pose_x_dir == kSamusXDir_FaceLeft)
    samus_new_pose = 66;
  else
    samus_new_pose = 32;
  return 0;
}

uint8 Samus_HandleTransFromBlockColl_1_3(void) {  // 0x91EA63
  if (joypad1_lastkeys & button_config_jump) {
    samus_new_pose = samus_pose;
    return 0;
  }
  if ((uint8)morph_ball_bounce_state != kMorphBallBounceState_NoBounce) {
    if ((uint8)morph_ball_bounce_state == (uint8)kMorphBallBounceState_Spring_FirstBounce) {
      samus_new_pose = samus_pose;
      return 0;
    }
    if ((uint8)morph_ball_bounce_state != (uint8)kMorphBallBounceState_Spring_SecondBounce)
      Unreachable();
  }
  else if ((int16)samus_y_speed >= 3) {
    samus_new_pose = samus_pose;
    return 0;
  }
  if (samus_pose_x_dir == kSamusXDir_FaceLeft)
    samus_new_pose = kPose_7A_FaceL_Springball_Ground;
  else
    samus_new_pose = kPose_79_FaceR_Springball_Ground;
  return 0;
}

uint8 Samus_HandleTransFromBlockColl_1_5(void) {  // 0x91EAB6
  samus_new_pose = samus_pose;
  return 0;
}

void Samus_HandleTransFromBlockColl_5(void) {  // 0x91EABE
  if (samus_pose_x_dir == kSamusXDir_FaceLeft)
    samus_new_pose = kPose_84_FaceL_Walljump;
  else
    samus_new_pose = kPose_83_FaceR_Walljump;
  samus_new_pose_command = 5;
}


void Samus_CheckWalkedIntoSomething(void) {  // 0x91EADE
  int32 amt;

  if (samus_stopped_by_collision && samus_movement_type == kMovementType_01_Running) {
    samus_new_pose = kSamusNewPose_RanIntoWall[kPoseParams[samus_pose].direction_shots_fired];
    samus_stopped_by_collision = 0;
    return;
  }
  if (samus_new_pose == 0xFFFF || kPoseParams[samus_new_pose].movement_type != kMovementType_01_Running) {
    samus_stopped_by_collision = 0;
    return;
  }
  if (samus_pose_x_dir != kSamusXDir_FaceLeft) {
    samus_collision_direction = 1;
    amt = INT16_SHL16(1);
    CheckEnemyColl_Result cres = Samus_CheckSolidEnemyColl(amt);
    if (!cres.collision) {
      samus_collision_direction = 1;
      amt = INT16_SHL16(1);
      goto LABEL_10;
    }
LABEL_11:
    samus_new_pose = kSamusNewPose_RanIntoWall[kPoseParams[samus_new_pose].direction_shots_fired];
    samus_stopped_by_collision = 0;
    return;
  }
  samus_collision_direction = 0;
  amt = INT16_SHL16(1);
  CheckEnemyColl_Result cres = Samus_CheckSolidEnemyColl(amt);
  if (cres.collision)
    goto LABEL_11;
  amt = INT16_SHL16(-1);
  samus_collision_direction = 0;
LABEL_10:
  Samus_MoveRight_NoSolidColl(amt);
  if (samus_collision_flag)
    goto LABEL_11;
  samus_stopped_by_collision = 0;
}

void nullsub_19(void) {}
void nullsub_20(void) {}
void nullsub_21(void) {}
void nullsub_22(void) {}
static Func_V *const kSamus_HandleTransitionsA[9] = {  // 0x91EB88
  nullsub_18,
  Samus_HandleTransitionsA_1,
  Samus_HandleTransitionsA_2,
  nullsub_21,
  nullsub_22,
  Samus_HandleTransitionsA_5,
  Samus_HandleTransitionsA_6,
  Samus_HandleTransitionsA_7,
  Samus_HandleTransitionsA_8,
};
static Func_V *const kSamus_HandleTransitionsB[11] = {
  nullsub_18,
  Samus_HandleTransitionsB_1,
  Samus_HandleTransitionsB_2,
  Samus_HandleTransitionsB_3,
  Samus_HandleTransitionsB_4,
  Samus_HandleTransitionsB_5,
  nullsub_19,
  nullsub_20,
  Samus_HandleTransitionsB_8,
  Samus_HandleTransitionsB_9,
  Samus_HandleTransitionsB_10,
};
static Func_V *const kSamus_HandleTransitionsC[9] = {
  nullsub_18,
  Samus_HandleTransitionsC_1,
  Samus_HandleTransitionsC_2,
  Samus_HandleTransitionsC_3,
  Samus_HandleTransitionsC_4,
  Samus_HandleTransitionsC_5,
  Samus_HandleTransitionsC_6,
  Samus_HandleTransitionsC_7,
  Samus_HandleTransitionsC_8,
};

void Samus_HandleTransitions(void) {
  if ((samus_new_pose_transitional & 0x8000) == 0) {
    if (samus_new_pose_transitional_command != 3) {
      if (samus_new_pose_transitional_command == 1)
        goto LABEL_7;
      goto LABEL_6;
    }
    if (samus_new_pose_interrupted_command != 9) {
LABEL_6:
      samus_pose = samus_new_pose_transitional;
      SamusFunc_F433();
      Samus_SetAnimationFrameIfPoseChanged();
LABEL_7:
      kSamus_HandleTransitionsC[samus_new_pose_transitional_command]();
LABEL_15:
      samus_last_different_pose = samus_prev_pose;
      *(uint16 *)&samus_last_different_pose_x_dir = *(uint16 *)&samus_prev_pose_x_dir;
      samus_prev_pose = samus_pose;
      *(uint16 *)&samus_prev_pose_x_dir = *(uint16 *)&samus_pose_x_dir;
      goto LABEL_16;
    }
  }
  if ((samus_new_pose_interrupted & 0x8000) == 0) {
    samus_pose = samus_new_pose_interrupted;
    if (!(SamusFunc_F404() & 1))
      kSamus_HandleTransitionsB[samus_new_pose_interrupted_command]();
    goto LABEL_15;
  }
  Samus_CheckWalkedIntoSomething();
  if ((samus_new_pose & 0x8000) == 0) {
    samus_pose = samus_new_pose;
    if (!(SamusFunc_F404() & 1))
      kSamus_HandleTransitionsA[samus_new_pose_command]();
    goto LABEL_15;
  }
LABEL_16:
  samus_solid_vertical_coll_result = kSolidVertCollResult_0_NoChange;
}

void Samus_HandleTransitionsA_1(void) {  // 0x91EC50
  if (samus_x_base_speed || samus_x_base_subspeed) {
    AddToHiLo(&samus_x_base_speed, &samus_x_base_subspeed, __PAIR32__(samus_x_extra_run_speed, samus_x_extra_run_subspeed));
    samus_x_accel_mode = 2;
    Samus_CancelSpeedBoost();
    SetHiLo(&samus_x_extra_run_speed, &samus_x_extra_run_subspeed, 0);
    SamusFunc_EC80();
  } else {
    Samus_HandleTransitionsA_2();
  }
}

void Samus_HandleTransitionsA_6(void) {  // 0x91EC85
  samus_x_accel_mode = 0;
  samus_x_base_speed = 0;
  samus_x_base_subspeed = 0;
  Samus_HandleTransitionsA_8();
}

void Samus_HandleTransitionsA_8(void) {  // 0x91EC8E
  Samus_CancelSpeedBoost();
  SetHiLo(&samus_x_extra_run_speed, &samus_x_extra_run_subspeed, 0);
  SamusFunc_EC80();
}

void Samus_HandleTransitionsA_2(void) {  // 0x91ECD0
  samus_x_accel_mode = 0;
  Samus_CancelSpeedBoost();
}

static const uint16 word_91ED36[12] = {  // 0x91ECDA
  5, 5, 9, 9, 0, 0, 0, 0,
  0, 0, 0, 0,
};

void Samus_HandleTransitionsA_7(void) {
  int32 amt;

  if (sign16(samus_pose - kPose_DB)) {
    amt = INT16_SHL16(word_91ED36[samus_pose - 53]);
    if (amt) {
LABEL_4:
      samus_y_radius = kPoseParams[samus_pose].y_radius;
      amt = Samus_CollDetectChangedPose(amt);
    }
    samus_y_pos += amt >> 16;
    samus_prev_y_pos = samus_y_pos;
    if (morph_ball_bounce_state != kMorphBallBounceState_NoBounce) {
      morph_ball_bounce_state = kMorphBallBounceState_NoBounce;
      samus_y_subspeed = 0;
      samus_y_speed = 0;
      samus_y_dir = 0;
    }
  } else if (!sign16(samus_pose - kPose_F1_FaceR_CrouchTrans_AimU) && sign16(samus_pose - kPose_F7_FaceR_StandTrans_AimU)) {
    amt = INT16_SHL16(5);
    goto LABEL_4;
  }
}

static Func_U8 *const kSamus_HandleTransitionsB_1[28] = {  // 0x91ED4E
  Samus_HandleTransitionsB_1_0,
  Samus_HandleTransitionsB_1_0,
  Samus_HandleTransitionsB_1_0,
  Samus_HandleTransitionsB_1_0,
  Samus_HandleTransitionsB_1_4,
  Samus_HandleTransitionsB_1_0,
  Samus_HandleTransitionsB_1_6,
  Samus_HandleTransitionsB_1_7,
  Samus_HandleTransitionsB_1_4,
  Samus_HandleTransitionsB_1_4,
  Samus_HandleTransitionsB_1_10,
  Samus_HandleTransitionsB_1_11,
  Samus_HandleTransitionsB_1_11,
  Samus_HandleTransitionsB_1_0,
  Samus_HandleTransitionsB_1_11,
  Samus_HandleTransitionsB_1_11,
  Samus_HandleTransitionsB_1_0,
  Samus_HandleTransitionsB_1_4,
  Samus_HandleTransitionsB_1_4,
  Samus_HandleTransitionsB_1_4,
  Samus_HandleTransitionsB_1_0,
  Samus_HandleTransitionsB_1_0,
  Samus_HandleTransitionsB_1_10,
  Samus_HandleTransitionsB_1_11,
  Samus_HandleTransitionsB_1_11,
  Samus_HandleTransitionsB_1_11,
  Samus_HandleTransitionsB_1_11,
  Samus_HandleTransitionsB_1_11,
};

void Samus_HandleTransitionsB_1(void) {
  kSamus_HandleTransitionsB_1[samus_prev_movement_type]();
  Samus_SetSpeedForKnockback_Y();
  bomb_jump_dir = kBombJumpDir_None;
  samus_contact_damage_index = kSamusContactDamageIndex_0_Normal;
  samus_hurt_flash_counter = 1;
}

uint8 Samus_HandleTransitionsB_1_10(void) {  // 0x91EDA2
  return 0;
}

uint8 Samus_HandleTransitionsB_1_11(void) {  // 0x91EDA4
  return 0;
}

uint8 Samus_HandleTransitionsB_1_6(void) {  // 0x91EDA6
  if (frame_handler_gamma == FUNC16(Samus_FrameHandlerGamma_SpecialFalling_Unused))
    return 0;
  else
    return Samus_HandleTransitionsB_1_0();
}

uint8 Samus_HandleTransitionsB_1_0(void) {  // 0x91EDB0
  if (samus_pose_x_dir == kSamusXDir_FaceLeft) {
    if (knockback_x_dir == kKnockbackXDir_Left) {
      if (joypad1_lastkeys & kButton_Left) {
        knockback_dir = kKnockbackDir_DownLeft;
      }
      else {
        knockback_dir = kKnockbackDir_UpLeft;
      }
    }
    else {
      if (joypad1_lastkeys & kButton_Left)
        knockback_dir = kKnockbackDir_DownRight;
      else
        knockback_dir = kKnockbackDir_UpRight;
    }
  }
  else /* samus_pose_x_dir == kSamusXDir_FaceRight */ {
    if (knockback_x_dir == kKnockbackXDir_Left) {
      if (joypad1_lastkeys & kButton_Right) {
        knockback_dir = kKnockbackDir_DownLeft;
      }
      else {
        knockback_dir = kKnockbackDir_UpLeft;
      }
    }
    else {
      if (joypad1_lastkeys & kButton_Right)
        knockback_dir = kKnockbackDir_DownRight;
      else
        knockback_dir = kKnockbackDir_UpRight;
    }
  }
  samus_movement_handler = FUNC16(Samus_MovementHandler_Knockback);
  return 1;
}

uint8 Samus_HandleTransitionsB_1_4(void) {  // 0x91EE27
  if (samus_pose_x_dir == kSamusXDir_FaceLeft)
    knockback_dir = kKnockbackDir_UpLeft;
  else
    knockback_dir = kKnockbackDir_UpRight;
  samus_movement_handler = FUNC16(Samus_MovementHandler_Knockback);
  return 0;
}

uint8 Samus_HandleTransitionsB_1_7(void) {  // 0x91EE48
  if (samus_pose_x_dir == kSamusXDir_FaceLeft)
    knockback_dir = kKnockbackDir_UpLeft;
  else
    knockback_dir = kKnockbackDir_UpRight;
  samus_movement_handler = FUNC16(Samus_MovementHandler_Knockback);
  return 1;
}

void Samus_HandleTransitionsB_2(void) {  // 0x91EE69
  knockback_dir = kKnockbackDir_None;
  samus_movement_handler = FUNC16(Samus_MovementHandler_Normal);
  samus_y_speed = 0;
  samus_y_subspeed = 0;
  samus_y_dir = 0;
  Samus_AlignBottomWithPrevPose();
}

void Samus_HandleTransitionsB_3(void) {  // 0x91EE80
  bomb_jump_dir |= kBombJumpDir_Active;
  samus_movement_handler = FUNC16(Samus_MovementHandler_BombJumpStart);
  if (samus_input_handler != FUNC16(Samus_InputHandler_Demo))
    samus_input_handler = FUNC16(nullsub_152);
}

void Samus_HandleTransitionsB_4(void) {  // 0x91EEA1
  Samus_InitJump();
}

void Samus_HandleTransitionsB_5(void) {  // 0x91EEA6
  switch (samus_movement_type) {
  case kMovementType_00_Standing:
    goto LABEL_5;
  case kMovementType_05_Crouching:
    if (samus_pose_x_dir == kSamusXDir_FaceLeft)
      xray_angle = 192;
    else
      xray_angle = 64;
    goto LABEL_11;
  case kMovementType_15_RanIntoWall:
  case kMovementType_01_Running:
LABEL_5:
    if (samus_pose_x_dir == kSamusXDir_FaceLeft)
      xray_angle = 192;
    else
      xray_angle = 64;
LABEL_11:
    samus_anim_frame = 2;
    samus_anim_frame_timer = 63;
    samus_movement_handler = FUNC16(Samus_MovementHandler_Xray);
    samus_input_handler = FUNC16(Samus_InputHandler_Xray);
    special_samus_palette_type = 8;
    special_samus_palette_timer = 1;
    special_samus_palette_frame = 0;
    samus_shine_timer = 0;
    flare_counter = 0;
    flare_animation_frame = 0;
    flare_slow_sparks_anim_frame = 0;
    flare_fast_sparks_anim_frame = 0;
    flare_animation_timer = 0;
    flare_slow_sparks_anim_timer = 0;
    flare_fast_sparks_anim_timer = 0;
    QueueSfx1_Max6(kSfx1_Xray);
    break;
  }
}

void Samus_HandleTransitionsB_8(void) {  // 0x91EF3B
  samus_y_pos -= 5;
  samus_prev_y_pos = samus_y_pos;
  frame_handler_alfa = FUNC16(Samus_FrameHandlerBeta_DoNothing);
}

void Samus_HandleTransitionsB_9(void) {  // 0x91EF4F
  int16 v0;
  int16 v1;

  GrappleBeamFunc_BD95();
  v0 = samus_x_pos - samus_prev_x_pos;
  if ((int16)(samus_x_pos - samus_prev_x_pos) < 0) {
    if (sign16(v0 + 12))
      samus_prev_x_pos = samus_x_pos + 12;
  } else if (!sign16(v0 - 13)) {
    samus_prev_x_pos = samus_x_pos - 12;
  }
  v1 = samus_y_pos - samus_prev_y_pos;
  if ((int16)(samus_y_pos - samus_prev_y_pos) < 0) {
    if (sign16(v1 + 12))
      samus_prev_y_pos = samus_y_pos + 12;
  } else if (!sign16(v1 - 13)) {
    samus_prev_y_pos = samus_y_pos - 12;
  }
  Samus_CancelSpeedBoost();
  samus_x_base_speed = 0;
  samus_x_base_subspeed = 0;
  samus_y_subspeed = 0;
  samus_y_speed = 0;
  SetHiLo(&samus_x_extra_run_speed, &samus_x_extra_run_subspeed, 0);
}

void Samus_HandleTransitionsB_10(void) {  // 0x91EFBC
  GrappleBeamFunc_BEEB();
  Samus_HandleTransitionsB_9B();
}

void Samus_HandleTransitionsB_9B(void) {  // 0x91EF53
  int16 v0;
  int16 v1;

  v0 = samus_x_pos - samus_prev_x_pos;
  if ((int16)(samus_x_pos - samus_prev_x_pos) < 0) {
    if (sign16(v0 + 12))
      samus_prev_x_pos = samus_x_pos + 12;
  } else if (!sign16(v0 - 13)) {
    samus_prev_x_pos = samus_x_pos - 12;
  }
  v1 = samus_y_pos - samus_prev_y_pos;
  if ((int16)(samus_y_pos - samus_prev_y_pos) < 0) {
    if (sign16(v1 + 12))
      samus_prev_y_pos = samus_y_pos + 12;
  } else if (!sign16(v1 - 13)) {
    samus_prev_y_pos = samus_y_pos - 12;
  }
  Samus_CancelSpeedBoost();
  samus_x_base_speed = 0;
  samus_x_base_subspeed = 0;
  samus_y_subspeed = 0;
  samus_y_speed = 0;
  SetHiLo(&samus_x_extra_run_speed, &samus_x_extra_run_subspeed, 0);
}


void nullsub_23(void) {  // 0x91EFDE
}


static Func_V *const kSamus_HandleTransitionsA_5[7] = {  // 0x91EFC4
  [kSolidVertCollResult_0_NoChange]   = sub_91EFC3,
  [kSolidVertCollResult_1_Landed]     = Samus_HandleTransitionsA_5_1,
  [kSolidVertCollResult_2_Falling]    = Samus_HandleTransitionsA_5_2,
  [kSolidVertCollResult_3_Unused]     = nullsub_23,
  [kSolidVertCollResult_4_HitCeiling] = Samus_HandleTransitionsA_5_4,
  [kSolidVertCollResult_5_WallJumped] = Samus_HandleTransitionsA_5_5,
  Samus_HandleTransitionsA_5_6,
};
void Samus_HandleTransitionsA_5(void) {
  kSamus_HandleTransitionsA_5[(uint8)samus_solid_vertical_coll_result]();
}

void Samus_HandleTransitionsA_5_4(void) {  // 0x91EFDF
  samus_y_subspeed = 0;
  samus_y_speed = 0;
  UNUSED_word_7E0B1A = 0;
  samus_y_dir = 2;
}

void Samus_HandleTransitionsA_5_2(void) {  // 0x91EFEF
  if (samus_y_dir != 1) {
    morph_ball_bounce_state = kMorphBallBounceState_NoBounce;
    samus_y_subspeed = 0;
    samus_y_speed = 0;
    samus_is_falling_flag = 1;
    samus_y_dir = 2;
  }
  UNUSED_word_7E0A18 = 0;
}

void sub_91EFC3(void) {}
uint8 sub_91EFC3_rv(void) { return 0; }

static Func_U8 *const kSamus_HandleTransitionsA_5_1[6] = {  // 0x91F010
  [kDownwardCollResult_Landed_0_Grounded]       = Samus_HandleTransitionsA_5_1_0,
  [kDownwardCollResult_Landed_1_MorphGrounded]  = Samus_MorphBallBounceNoSpringballTrans,
  [kDownwardCollResult_Landed_2_Unused]         = Samus_HandleTransitionsA_5_1_2,
  [kDownwardCollResult_Landed_3_SpringGrounded] = Samus_MorphBallBounceSpringballTrans,
  [kDownwardCollResult_Landed_4_NoChange]       = sub_91EFC3_rv,
  Samus_HandleTransitionsA_5_1_5,
};

void Samus_HandleTransitionsA_5_1(void) {
  HandleLandingSoundEffectsAndGfx();
  if (HIBYTE(samus_solid_vertical_coll_result) == kDownwardCollResult_Landed_4_NoChange) {
    SamusFunc_F1D3();
  }
  else if (!(kSamus_HandleTransitionsA_5_1[HIBYTE(samus_solid_vertical_coll_result)]() & 1)) {
    UNUSED_word_7E0A18 = 0;
    samus_x_accel_mode = 0;
    samus_x_base_speed = 0;
    samus_x_base_subspeed = 0;
    SamusFunc_F1D3();
  }
}

void HandleLandingSoundEffectsAndGfx(void) {  // 0x91F046
  if ((samus_prev_movement_type == kMovementType_03_SpinJumping
       || samus_prev_movement_type == kMovementType_14_WallJumping)
      && !cinematic_function) {
    if (samus_prev_pose == kPose_81_FaceR_Screwattack || samus_prev_pose == kPose_82_FaceL_Screwattack)
      QueueSfx1_Max6(kSfx1_ScrewAttackEnd_Silence);
    else
      QueueSfx1_Max6(kSfx1_SpinJumpEnd_Silence);
  }
  if (samus_y_speed && !sign16(samus_y_speed - 5)) {
    if (!cinematic_function)
      QueueSfx3_Max6(kSfx3_SamusLandedHard);
  } else {
    if (!samus_y_subspeed)
      return;
    if (!cinematic_function)
      QueueSfx3_Max6(kSfx3_SamusLanded_WallJumped);
  }
  HandleLandingGraphics();
}

static Func_V *const kHandleLandingGraphicsAreaFuncs[8] = {  // 0x91F0A5
  [kArea_0_Crateria] = HandleLandingGraphics_Crateria,
  [kArea_1_Brinstar] = HandleLandingGraphics_Brinstar,
  [kArea_2_Norfair] = HandleLandingGraphics_Norfair_WreckedShip_Dust,
  [kArea_3_WreckedShip] = HandleLandingGraphics_Norfair_WreckedShip_Dust,
  [kArea_4_Maridia] = HandleLandingGraphics_Maridia_FootstepSplashes,
  [kArea_5_Tourian] = HandleLandingGraphics_Tourian,
  [kArea_6_Ceres] = HandleLandingGraphics_Delete,
  [kArea_7_Debug] = HandleLandingGraphics_Delete,
};
void HandleLandingGraphics(void) {
  kHandleLandingGraphicsAreaFuncs[(area_index)]();
}

void HandleLandingGraphics_Delete(void) {  // 0x91F0BE
  atmospheric_gfx_frame_and_type[2] = 0;
  atmospheric_gfx_frame_and_type[3] = 0;
}
static const uint8 kWetRooms[17] = {  // 0x91F0C5
  1, 0, 0, 0, 0, 2, 0, 4,
  0, 4, 4, 4, 4, 0, 4, 0,
  0,
};
void HandleLandingGraphics_Crateria(void) {
  if (cinematic_function)
    goto LABEL_13;
  if (room_index == 28) {
    HandleLandingGraphics_Norfair_WreckedShip_Dust();
    return;
  }
  if ((int16)(room_index - 16) >= 0)
    goto LABEL_13;
  if ((kWetRooms[room_index] & 1) == 0) {
    if ((kWetRooms[room_index] & 2) != 0) {
      if (!sign16(samus_y_pos - 944))
        goto LABEL_14;
    } else if ((kWetRooms[room_index] & 4) != 0) {
      goto LABEL_14;
    }
LABEL_13:
    HandleLandingGraphics_Delete();
    return;
  }
  if (fx_type != kFxType_A_Rain)
    goto LABEL_13;
LABEL_14:
  HandleLandingGraphics_Maridia_FootstepSplashes();
}

void HandleLandingGraphics_Maridia_FootstepSplashes(void) {  // 0x91F116
  uint16 samus_bottom_bound = Samus_GetBottomBound();
  if ((fx_y_pos & 0x8000) == 0) {
    if (sign16(fx_y_pos - samus_bottom_bound) && !(fx_liquid_options & kFxLiquidOption_4_LiquidPhysicsDisabled))
      return;
LABEL_7:
    LOBYTE(atmospheric_gfx_frame_and_type[2]) = 0;
    HIBYTE(atmospheric_gfx_frame_and_type[2]) = kAtmosphericGraphicType_1_FootstepSplashes;

    LOBYTE(atmospheric_gfx_frame_and_type[3]) = 0;
    HIBYTE(atmospheric_gfx_frame_and_type[3]) = kAtmosphericGraphicType_1_FootstepSplashes;

    atmospheric_gfx_anim_timer[2] = 3;
    atmospheric_gfx_anim_timer[3] = 3;

    atmospheric_gfx_x_pos[2] = samus_x_pos + 4;
    atmospheric_gfx_x_pos[3] = samus_x_pos - 3;
    atmospheric_gfx_y_pos[2] = samus_bottom_bound - 4;
    atmospheric_gfx_y_pos[3] = samus_bottom_bound - 4;
    return;
  }
  if ((lava_acid_y_pos & 0x8000) != 0 || !sign16(lava_acid_y_pos - samus_bottom_bound))
    goto LABEL_7;
}

void HandleLandingGraphics_Norfair_WreckedShip_Dust(void) {  // 0x91F166
  uint16 samus_bottom_bound = Samus_GetBottomBound();
  if ((fx_y_pos & 0x8000) == 0) {
    if (sign16(fx_y_pos - samus_bottom_bound) && !(fx_liquid_options & kFxLiquidOption_4_LiquidPhysicsDisabled))
      return;
LABEL_7:
    LOBYTE(atmospheric_gfx_frame_and_type[2]) = 0;
    HIBYTE(atmospheric_gfx_frame_and_type[2]) = kAtmosphericGraphicType_6_LandingDust;

    LOBYTE(atmospheric_gfx_frame_and_type[3]) = 0;
    HIBYTE(atmospheric_gfx_frame_and_type[3]) = kAtmosphericGraphicType_6_LandingDust;

    atmospheric_gfx_anim_timer[2] = 3;
    atmospheric_gfx_anim_timer[3] = 3;

    atmospheric_gfx_x_pos[2] = samus_x_pos + 8;
    atmospheric_gfx_x_pos[3] = samus_x_pos - 8;
    atmospheric_gfx_y_pos[2] = samus_bottom_bound;
    atmospheric_gfx_y_pos[3] = samus_bottom_bound;
    return;
  }
  if ((lava_acid_y_pos & 0x8000) != 0 || !sign16(lava_acid_y_pos - samus_bottom_bound))
    goto LABEL_7;
}

void HandleLandingGraphics_Brinstar(void) {  // 0x91F1B2
  if (room_index == 8)
    HandleLandingGraphics_Norfair_WreckedShip_Dust();
  else
    HandleLandingGraphics_Tourian();
}

void HandleLandingGraphics_Tourian(void) {  // 0x91F1BA
  if (!sign16(room_index - 5) && (sign16(room_index - 9) || room_index == 11)) {
    HandleLandingGraphics_Norfair_WreckedShip_Dust();
  } else {
    atmospheric_gfx_frame_and_type[2] = 0;
    atmospheric_gfx_frame_and_type[3] = 0;
  }
}

void SamusFunc_F1D3(void) {  // 0x91F1D3
  samus_is_falling_flag = 0;
  UNUSED_word_7E0B1A = 0;
  UNUSED_word_7E0B2A = 0;
  samus_y_subspeed = 0;
  samus_y_speed = 0;
  samus_y_dir = 0;
  UNUSED_word_7E0B38 = 0;
  morph_ball_bounce_state = kMorphBallBounceState_NoBounce;
}

uint8 Samus_HandleTransitionsA_5_1_0(void) {  // 0x91F1EC
  if (samus_input_handler != FUNC16(Samus_InputHandler_Demo))
    samus_input_handler = FUNC16(Samus_InputHandler_AutoJump);
  return 0;
}

static const uint16 kSamusPhys_MorphBounceYSpeed = 1;
static const uint16 kSamusPhys_MorphBounceYSubspeed = 0;
uint8 Samus_MorphBallBounceNoSpringballTrans(void) {  // 0x91F1FC
  if (morph_ball_bounce_state != kMorphBallBounceState_NoBounce) {
    if (morph_ball_bounce_state == kMorphBallBounceState_Morph_FirstBounce) {
      ++morph_ball_bounce_state;
      samus_y_dir = kSamusYDir_Up;
      samus_y_subspeed = kSamusPhys_MorphBounceYSubspeed;
      samus_y_speed = kSamusPhys_MorphBounceYSpeed - 1;
      return 1;
    }
    if (morph_ball_bounce_state != kMorphBallBounceState_Morph_SecondBounce)
      Unreachable();
  }
  else if ((int16)samus_y_speed >= 3) {
    ++morph_ball_bounce_state;
    samus_y_dir = kSamusYDir_Up;
    samus_y_subspeed = kSamusPhys_MorphBounceYSubspeed;
    samus_y_speed = kSamusPhys_MorphBounceYSpeed;
    return 1;
  }
  morph_ball_bounce_state = kMorphBallBounceState_NoBounce;
  samus_y_dir = kSamusYDir_None;
  samus_y_subspeed = 0;
  samus_y_speed = 0;
  return 0;
}

uint8 Samus_HandleTransitionsA_5_1_2(void) {  // 0x91F253
  morph_ball_bounce_state = 0;
  enable_horiz_slope_coll = 3;
  return 0;
}

uint8 Samus_MorphBallBounceSpringballTrans(void) {  // 0x91F25E
  if (joypad1_lastkeys & button_config_jump) {
    morph_ball_bounce_state = 0;
    Samus_InitJump();
    return 1;
  }
  if ((uint8)morph_ball_bounce_state != kMorphBallBounceState_NoBounce) {
    if ((uint8)morph_ball_bounce_state == (uint8)kMorphBallBounceState_Spring_FirstBounce) {
      morph_ball_bounce_state = kMorphBallBounceState_Spring_SecondBounce;
      samus_y_dir = kSamusYDir_Up;
      samus_y_subspeed = kSamusPhys_MorphBounceYSubspeed;
      samus_y_speed = kSamusPhys_MorphBounceYSpeed - 1;
      return 1;
    }
    if ((uint8)morph_ball_bounce_state != (uint8)kMorphBallBounceState_Spring_SecondBounce)
      Unreachable();
  }
  else if ((int16)samus_y_speed >= 3) {
    morph_ball_bounce_state = kMorphBallBounceState_Spring_FirstBounce;
    samus_y_dir = kSamusYDir_Up;
    samus_y_subspeed = kSamusPhys_MorphBounceYSubspeed;
    samus_y_speed = kSamusPhys_MorphBounceYSpeed;
    return 1;
  }
  morph_ball_bounce_state = kMorphBallBounceState_NoBounce;
  samus_y_dir = kSamusYDir_None;
  samus_y_subspeed = 0;
  samus_y_speed = 0;
  return 0;
}

uint8 Samus_HandleTransitionsA_5_1_5(void) {  // 0x91F2CE
  morph_ball_bounce_state = kMorphBallBounceState_NoBounce;
  return 0;
}

void Samus_HandleTransitionsA_5_5(void) {  // 0x91F2D3
  samus_x_accel_mode = 0;
  samus_stopped_by_collision = 0;
  samus_is_falling_flag = 0;
  UNUSED_word_7E0B1A = 0;
  samus_x_base_speed = 0;
  samus_x_base_subspeed = 0;
  UNUSED_word_7E0A18 = 0;
  QueueSfx3_Max6(kSfx3_SamusLanded_WallJumped);
}

void Samus_HandleTransitionsA_5_6(void) {  // 0x91F2F0
  if (samus_stopped_by_collision) {
    if (samus_prev_movement_type == 9) {
      enable_horiz_slope_coll = samus_pose_x_dir != kSamusXDir_FaceLeft;
      UNUSED_word_7E0A18 = 0;
    }
  }
}

void Samus_HandleTransitionsC_1(void) {  // 0x91F31D
  knockback_dir = kKnockbackDir_None;
  samus_movement_handler = FUNC16(Samus_MovementHandler_Normal);
  morph_ball_bounce_state = kMorphBallBounceState_NoBounce;
  samus_y_subspeed = 0;
  samus_y_speed = 0;
  samus_is_falling_flag = 1;
  samus_y_dir = 2;
  Samus_AlignBottomWithPrevPose();
  if (samus_input_handler != FUNC16(Samus_InputHandler_Demo))
    samus_input_handler = FUNC16(Samus_InputHandler_Normal);
}

void Samus_HandleTransitionsC_2(void) {  // 0x91F34E
  Samus_AlignBottomWithPrevPose();
  samus_movement_handler = FUNC16(Samus_MovementHandler_Normal);
  if (game_state == kGameState_42_PlayingDemo)
    samus_input_handler = FUNC16(Samus_InputHandler_Demo);
  else
    samus_input_handler = FUNC16(Samus_InputHandler_Normal);
}

void Samus_HandleTransitionsC_3(void) {  // 0x91F36E
  morph_ball_bounce_state = kMorphBallBounceState_NoBounce;
  samus_anim_frame_timer += samus_anim_frame_buffer;
}

void Samus_HandleTransitionsC_4(void) {  // 0x91F37C
  samus_x_pos = layer1_x_pos + 128;
  samus_prev_x_pos = layer1_x_pos + 128;
  samus_y_pos = layer1_y_pos + 128;
  samus_prev_y_pos = layer1_y_pos + 128;
}

void Samus_HandleTransitionsC_5(void) {  // 0x91F397
  samus_y_pos += 5;
  samus_prev_y_pos = samus_y_pos;
}

void Samus_HandleTransitionsC_6(void) {  // 0x91F3A5
  HandleJumpTransition();
}

void Samus_HandleTransitionsC_7(void) {  // 0x91F3AA
  int16 v0;
  int16 v1;

  v0 = samus_x_pos - samus_prev_x_pos;
  if ((int16)(samus_x_pos - samus_prev_x_pos) < 0) {
    if (sign16(v0 + 12))
      samus_prev_x_pos = samus_x_pos + 12;
  } else if (!sign16(v0 - 13)) {
    samus_prev_x_pos = samus_x_pos - 12;
  }
  v1 = samus_y_pos - samus_prev_y_pos;
  if ((int16)(samus_y_pos - samus_prev_y_pos) < 0) {
    if (sign16(v1 + 12))
      samus_prev_y_pos = samus_y_pos + 12;
  } else if (!sign16(v1 - 13)) {
    samus_prev_y_pos = samus_y_pos - 12;
  }
}

void Samus_HandleTransitionsC_8(void) {  // 0x91F3FD
  Samus_HandleTransitionsC_1();
  Samus_HandleTransitionsC_3();
}

uint8 SamusFunc_F404(void) {  // 0x91F404
  SamusPose v1;

  v1 = samus_pose;
  if (samus_pose != samus_prev_pose) {
    HandleCollDueToChangedPose();
    SamusFunc_F433();
    HandleJumpTransition();
    Samus_SetAnimationFrameIfPoseChanged();
    samus_anim_frame_skip = 0;
  }
  return v1 != samus_pose;
}

void SamusFunc_F433(void) {  // 0x91F433
  samus_pose_x_dir = kPoseParams[samus_pose].pose_x_dir;
  samus_movement_type = kPoseParams[samus_pose].movement_type;
  SamusFunc_F468();
  if ((samus_prev_movement_type == kMovementType_03_SpinJumping || samus_prev_movement_type == kMovementType_14_WallJumping)
      && (equipped_items & kItem_ScrewAttack)) {
    Samus_LoadSuitPalette();
  }
}

static Func_U8 *const off_91F4A2[28] = {  // 0x91F468
  SamusFunc_F468_Standing,
  SamusFunc_F468_Running,
  SamusFunc_F468_NormalJump,
  SamusFunc_F468_SpinJump,
  SamusFunc_F468_MorphBall,
  SamusFunc_F468_Crouching,
  SamusFunc_F468_Falling,
  SamusFunc_F468_Unused,
  SamusFunc_F468_MorphBall,
  SamusFunc_F468_Unused,
  SamusFunc_F468_Unused,
  SamusFunc_F468_Unused,
  SamusFunc_F468_Unused,
  SamusFunc_F468_Unused,
  SamusFunc_F468_TurningAroundOnGround,
  SamusFunc_F468_CrouchTransEtc,
  SamusFunc_F468_Moonwalking,
  SamusFunc_F468_Springball,
  SamusFunc_F468_Springball,
  SamusFunc_F468_Springball,
  SamusFunc_F468_WallJumping,
  SamusFunc_F468_Unused,
  SamusFunc_F468_Unused,
  SamusFunc_F468_TurnAroundJumping,
  SamusFunc_F468_TurnAroundFalling,
  SamusFunc_F468_DamageBoost,
  SamusFunc_F468_Unused,
  SamusFunc_F468_Shinespark,
};

void SamusFunc_F468(void) {
  if (off_91F4A2[samus_movement_type]()) {
    samus_pose_x_dir = kPoseParams[samus_pose].pose_x_dir;
    samus_movement_type = kPoseParams[samus_pose].movement_type;
    if (samus_movement_type == kMovementType_0E_TurningAroundOnGround) {
      off_91F4A2[kMovementType_0E_TurningAroundOnGround]();
      samus_pose_x_dir = kPoseParams[samus_pose].pose_x_dir;
      samus_movement_type = kPoseParams[samus_pose].movement_type;
    }
  }
}

uint8 SamusFunc_F468_Unused(void) {  // 0x91F4DA
  return 0;
}

uint8 SamusFunc_F468_Standing(void) {  // 0x91F4DC
  if ((kPoseParams[samus_pose].direction_shots_fired == 0
       || kPoseParams[samus_pose].direction_shots_fired == 9)
      && (kPoseParams[samus_prev_pose].direction_shots_fired == 0
          || kPoseParams[samus_prev_pose].direction_shots_fired == 9)) {
    samus_anim_frame_skip = 1;
  }
  return 0;
}

uint8 SamusFunc_F468_Running(void) {  // 0x91F50C
  if (samus_prev_movement_type == 1)
    samus_anim_frame_skip = 0x8000;
  if (!UNUSED_word_7E0DF8)
    return 0;
  if (samus_pose == (kPose_44_FaceL_Turn_Crouch | kPose_01_FaceR_Normal)) {
    samus_pose = kPose_25_FaceR_Turn_Stand;
    return 1;
  }
  if (samus_pose == (kPose_44_FaceL_Turn_Crouch | kPose_02_FaceL_Normal)) {
    samus_pose = kPose_26_FaceL_Turn_Stand;
    return 1;
  }
  return 0;
}

uint8 SamusFunc_F468_NormalJump(void) {  // 0x91F543
  if (samus_pose != kPose_4E_FaceL_Jump_NoAim_NoMove_NoGun) {
    if (samus_pose == kPose_4D_FaceR_Jump_NoAim_NoMove_NoGun || samus_pose == kPose_15_FaceR_Jump_AimU) {
LABEL_7:
      if (samus_shine_timer) {
        samus_pose = kPose_C7_FaceR_ShinesparkWindup_Vert;
LABEL_11:
        TriggerShinesparkWindup();
        if (samus_prev_movement_type == kMovementType_02_NormalJumping)
          samus_prev_y_pos = --samus_y_pos;
        return 1;
      }
      goto LABEL_14;
    }
    if (samus_pose != kPose_16_FaceL_Jump_AimU && samus_pose != kPose_6A_FaceL_Jump_AimUL) {
      if (samus_pose != kPose_69_FaceR_Jump_AimUR)
        goto LABEL_14;
      goto LABEL_7;
    }
  }
  if (samus_shine_timer) {
    samus_pose = kPose_C8_FaceL_ShinesparkWindup_Vert;
    goto LABEL_11;
  }
LABEL_14:
  if (samus_x_extra_run_speed || samus_x_extra_run_subspeed)
    samus_x_accel_mode = 2;
  else
    samus_x_accel_mode = 0;
  if ((samus_pose == kPose_15_FaceR_Jump_AimU || samus_pose == kPose_16_FaceL_Jump_AimU)
      && (samus_prev_pose == kPose_55_FaceR_Jumptrans_AimU || samus_prev_pose == kPose_56_FaceL_Jumptrans_AimU)) {
    samus_anim_frame_skip = 1;
  }
  if ((button_config_shoot & joypad1_newkeys) != 0)
    new_projectile_direction_changed_pose = kPoseParams[samus_pose].direction_shots_fired | 0x8000;
  return 0;
}

uint8 SamusFunc_F468_Crouching(void) {  // 0x91F5EB
  if ((samus_pose == kPose_85_FaceR_Crouch_AimU || samus_pose == kPose_86_FaceL_Crouch_AimU)
      && (samus_prev_pose == kPose_F1_FaceR_CrouchTrans_AimU || samus_prev_pose == kPose_F2_FaceL_CrouchTrans_AimU)) {
    samus_anim_frame_skip = 1;
  }
  return 0;
}

uint8 SamusFunc_F468_Falling(void) {  // 0x91F60D
  if (samus_x_extra_run_speed || samus_x_extra_run_subspeed)
    samus_x_accel_mode = 2;
  else
    samus_x_accel_mode = 0;
  return 0;
}

uint8 SamusFunc_F468_SpinJump(void) {  // 0x91F624
  if (samus_prev_movement_type == kMovementType_03_SpinJumping
      || samus_prev_movement_type == kMovementType_14_WallJumping) {
    samus_anim_frame_skip = 1;
    if ((samus_prev_pose_x_dir & 0xF) == 8) {
      if (*(uint16 *)&samus_pose_x_dir != 772)
        goto LABEL_9;
    } else if ((samus_prev_pose_x_dir & 0xF) != 4 || *(uint16 *)&samus_pose_x_dir != 776) {
      goto LABEL_9;
    }
    AddToHiLo(&samus_x_base_speed, &samus_x_base_subspeed, __PAIR32__(samus_x_extra_run_speed, samus_x_extra_run_subspeed));
    Samus_CancelSpeedBoost();
    SetHiLo(&samus_x_extra_run_speed, &samus_x_extra_run_subspeed, 0);
    samus_x_accel_mode = 1;
  }
LABEL_9:
  if (samus_pose_x_dir == kSamusXDir_FaceLeft) {
    if ((equipped_items & kItem_GravitySuit) == 0) {
      uint16 samus_top_bound = Samus_GetTopBound();
      if ((fx_y_pos & 0x8000) != 0) {
        if ((lava_acid_y_pos & 0x8000) == 0 && sign16(lava_acid_y_pos - samus_top_bound))
          return 0;
      } else if (sign16(fx_y_pos - samus_top_bound) && !(fx_liquid_options & kFxLiquidOption_4_LiquidPhysicsDisabled)) {
        return 0;
      }
    }
    if ((equipped_items & kItem_ScrewAttack) != 0) {
      samus_pose = kPose_82_FaceL_Screwattack;
      goto LABEL_40;
    }
    if ((equipped_items & kItem_SpaceJump) != 0) {
      QueueSfx1_Max6(kSfx1_SpaceJump);
      samus_pose = kPose_1C_FaceL_SpaceJump;
      return 0;
    }
    if (!samus_anim_frame_skip && !cinematic_function) {
LABEL_22:
      QueueSfx1_Max6(kSfx1_SpinJump);
      return 0;
    }
    return 0;
  }
  if ((equipped_items & kItem_GravitySuit) == 0) {
    uint16 samus_top_bound = Samus_GetTopBound();
    if ((fx_y_pos & 0x8000) != 0) {
      if ((lava_acid_y_pos & 0x8000) == 0 && sign16(lava_acid_y_pos - samus_top_bound))
        return 0;
    } else if (sign16(fx_y_pos - samus_top_bound) && !(fx_liquid_options & kFxLiquidOption_4_LiquidPhysicsDisabled)) {
      return 0;
    }
  }
  if ((equipped_items & kItem_ScrewAttack) != 0) {
    samus_pose = kPose_81_FaceR_Screwattack;
LABEL_40:
    if (!samus_anim_frame_skip)
      QueueSfx1_Max6(kSfx1_ScrewAttack);
    return 0;
  }
  if ((equipped_items & kItem_SpaceJump) == 0) {
    if (samus_anim_frame_skip || cinematic_function)
      return 0;
    goto LABEL_22;
  }
  QueueSfx1_Max6(kSfx1_SpaceJump);
  samus_pose = kPose_1B_FaceR_SpaceJump;
  return 0;
}

static Func_U8 *const off_91F790[12] = {  // 0x91F758
  Samus_CrouchTrans,
  Samus_CrouchTrans,
  Samus_MorphTrans,
  Samus_MorphTrans,
  MaybeUnused_sub_91F7F4,
  MaybeUnused_sub_91F840,
  Samus_StandOrUnmorphTrans,
  Samus_StandOrUnmorphTrans,
  Samus_StandOrUnmorphTrans,
  Samus_StandOrUnmorphTrans,
  Samus_StandOrUnmorphTrans,
  Samus_StandOrUnmorphTrans,
};

static Func_U8 *const off_91F7A8[4] = {
  Samus_MorphTrans,
  Samus_MorphTrans,
  Samus_StandOrUnmorphTrans,
  Samus_StandOrUnmorphTrans,
};

uint8 SamusFunc_F468_CrouchTransEtc(void) {
  uint16 v0;
  if (sign16(samus_pose - kPose_F1_FaceR_CrouchTrans_AimU)) {
    if (sign16(samus_pose - kPose_DB)) {
      v0 = 2 * (samus_pose - 53);
LABEL_4:
      samus_new_pose_command = 7;
      return off_91F790[v0 >> 1]();
    }
    return off_91F7A8[samus_pose - 219]();
  } else {
    if (sign16(samus_pose - kPose_F7_FaceR_StandTrans_AimU)) {
      v0 = 0;
      goto LABEL_4;
    }
    samus_new_pose_command = 7;
  }
  return 0;
}

uint8 Samus_CrouchTrans(void) {  // 0x91F7B0
  if (speed_boost_counter >= SPEED_BOOST_THRESHOLD) {
    samus_shine_timer = 180;
    special_samus_palette_type = 1;
    special_samus_palette_frame = 0;
  }
  return 0;
}

uint8 Samus_StandOrUnmorphTrans(void) {  // 0x91F7CC
  return 0;
}

uint8 Samus_MorphTrans(void) {  // 0x91F7CE
  if ((equipped_items & kItem_MorphBall) != 0) {
    if (samus_prev_movement_type == kMovementType_03_SpinJumping)
      samus_x_accel_mode = 2;
    bomb_spread_charge_timeout_counter = 0;
    return 0;
  } else {
    samus_pose = samus_prev_pose;
    return 1;
  }
}

uint8 MaybeUnused_sub_91F7F4(void) {  // 0x91F7F4
  if (samus_prev_movement_type == kMovementType_08_MorphBallFalling
      || samus_prev_movement_type == kMovementType_13_SpringBallFalling) {
    if ((equipped_items & kItem_SpringBall) != 0)
      samus_pose = kPose_7D_FaceR_Springball_Fall;
    else
      samus_pose = kPose_31_FaceR_Morphball_Air;
  } else if ((equipped_items & kItem_SpringBall) != 0) {
    samus_pose = kPose_79_FaceR_Springball_Ground;
  } else {
    samus_pose = kPose_1D_FaceR_Morphball_Ground;
  }
  return 1;
}

uint8 MaybeUnused_sub_91F840(void) {  // 0x91F840
  if (samus_prev_movement_type == kMovementType_08_MorphBallFalling
      || samus_prev_movement_type == kMovementType_13_SpringBallFalling) {
    if ((equipped_items & kItem_SpringBall) != 0)
      samus_pose = kPose_7E_FaceL_Springball_Fall;
    else
      samus_pose = kPose_32_FaceL_Morphball_Air;
  } else if ((equipped_items & kItem_SpringBall) != 0) {
    samus_pose = kPose_7A_FaceL_Springball_Ground;
  } else {
    samus_pose = kPose_41_FaceL_Morphball_Ground;
  }
  return 1;
}

uint8 SamusFunc_F468_Moonwalking(void) {  // 0x91F88C
  if (moonwalk_flag)
    return 0;
  if (samus_pose_x_dir == kSamusXDir_FaceLeft)
    samus_pose = kPose_25_FaceR_Turn_Stand;
  else
    samus_pose = kPose_26_FaceL_Turn_Stand;
  return 1;
}

uint8 SamusFunc_F468_DamageBoost(void) {  // 0x91F8AE
  return SamusFunc_F468_DamageBoost_();
}

uint8 MaybeUnused_sub_91F8B0(void) {  // 0x91F8B0
  if (samus_pose_x_dir == kSamusXDir_FaceLeft)
    samus_pose = kPose_54_FaceL_Knockback;
  else
    samus_pose = kPose_53_FaceR_Knockback;
  return 1;
}

uint8 SamusFunc_F468_DamageBoost_(void) {  // 0x91F8CB
  samus_movement_handler = FUNC16(Samus_MovementHandler_Normal);
  return 0;
}

uint8 SamusFunc_F468_TurningAroundOnGround(void) {  // 0x91F8D3
  if (samus_prev_pose && samus_prev_pose != kPose_9B_FaceF_VariaGravitySuit) {
    uint16 v0 = kPoseParams[samus_prev_pose].direction_shots_fired;
    if (samus_prev_movement_type == kMovementType_10_Moonwalking) {
      new_projectile_direction_changed_pose = v0 | 0x100;
      if ((button_config_jump & joypad1_lastkeys) != 0) {
        samus_pose = kSamusTurnPose_Moonwalk[v0];
      } else {
        samus_pose = kSamusTurnPose_Standing[v0];
      }
    } else if (samus_prev_movement_type == 5) {
      samus_pose = kSamusTurnPose_Crouching[v0];
    } else {
      samus_pose = kSamusTurnPose_Standing[v0];
    }
  }
  AddToHiLo(&samus_x_base_speed, &samus_x_base_subspeed, __PAIR32__(samus_x_extra_run_speed, samus_x_extra_run_subspeed));
  SetHiLo(&samus_x_extra_run_speed, &samus_x_extra_run_subspeed, 0);
  samus_x_accel_mode = 1;
  return 1;
}

uint8 SamusFunc_F468_TurnAroundJumping(void) {  // 0x91F952
  samus_pose = kSamusTurnPose_Jumping[kPoseParams[samus_prev_pose].direction_shots_fired];
  AddToHiLo(&samus_x_base_speed, &samus_x_base_subspeed, __PAIR32__(samus_x_extra_run_speed, samus_x_extra_run_subspeed));
  SetHiLo(&samus_x_extra_run_speed, &samus_x_extra_run_subspeed, 0);
  samus_x_accel_mode = 1;
  return 1;
}

uint8 SamusFunc_F468_TurnAroundFalling(void) {  // 0x91F98A
  samus_pose = kSamusTurnPose_Falling[kPoseParams[samus_prev_pose].direction_shots_fired];
  AddToHiLo(&samus_x_base_speed, &samus_x_base_subspeed, __PAIR32__(samus_x_extra_run_speed, samus_x_extra_run_subspeed));
  SetHiLo(&samus_x_extra_run_speed, &samus_x_extra_run_subspeed, 0);
  samus_x_accel_mode = 1;
  return 1;
}

uint8 SamusFunc_F468_MorphBall(void) {  // 0x91F9F4
  if (samus_prev_movement_type == kMovementType_04_MorphBallOnGround
      || samus_prev_movement_type == kMovementType_08_MorphBallFalling) {
    samus_anim_frame_skip = 0x8000;
  }
  SamusFunc_FA0A();
  return 0;
}

void SamusFunc_FA0A(void) {  // 0x91FA0F
  if (samus_prev_pose_x_dir == 8) {
    if (samus_pose_x_dir != kSamusXDir_FaceLeft)
      return;
    goto LABEL_5;
  }
  if (samus_pose_x_dir == kSamusXDir_FaceRight) {
LABEL_5:;
    AddToHiLo(&samus_x_base_speed, &samus_x_base_subspeed, __PAIR32__(samus_x_extra_run_speed, samus_x_extra_run_subspeed));
    Samus_CancelSpeedBoost();
    SetHiLo(&samus_x_extra_run_speed, &samus_x_extra_run_subspeed, 0);
    samus_x_accel_mode = 1;
  }
}

uint8 SamusFunc_F468_Springball(void) {  // 0x91FA56
  if (samus_prev_movement_type == kMovementType_11_SpringBallOnGround
      || samus_prev_movement_type == kMovementType_12_SpringBallInAir
      || samus_prev_movement_type == kMovementType_13_SpringBallFalling) {
    samus_anim_frame_skip = 0x8000;
  }
  SamusFunc_FA0A();
  return 0;
}

uint8 SamusFunc_F468_WallJumping(void) {  // 0x91FA76
  uint16 samus_bottom_bound = Samus_GetBottomBound();
  if ((fx_y_pos & 0x8000) != 0) {
    if ((lava_acid_y_pos & 0x8000) == 0 && sign16(lava_acid_y_pos - samus_bottom_bound))
      return 0;
  } else if (sign16(fx_y_pos - samus_bottom_bound) && !(fx_liquid_options & kFxLiquidOption_4_LiquidPhysicsDisabled)) {
    return 0;
  }
  LOBYTE(atmospheric_gfx_frame_and_type[3]) = 0;
  HIBYTE(atmospheric_gfx_frame_and_type[3]) = kAtmosphericGraphicType_6_LandingDust;
  atmospheric_gfx_anim_timer[3] = 3;
  atmospheric_gfx_y_pos[3] = samus_bottom_bound;
  if (samus_pose_x_dir != kSamusXDir_FaceRight) {
    atmospheric_gfx_x_pos[3] = samus_x_pos + 6;
    return 0;
  }
  atmospheric_gfx_x_pos[3] = samus_x_pos - 6;
  return 0;
}

static uint16 kSamusFunc_F468_Shinespark[6] = {  // 0x91FACA
  (uint16)fnSamus_MovementHandler_HorizontalShinespark,
  (uint16)fnSamus_MovementHandler_HorizontalShinespark,
  (uint16)fnSamus_MovementHandler_VerticalShinespark,
  (uint16)fnSamus_MovementHandler_VerticalShinespark,
  (uint16)fnSamus_MovementHandler_DiagonalShinespark,
  (uint16)fnSamus_MovementHandler_DiagonalShinespark,
};
uint8 SamusFunc_F468_Shinespark(void) {
  if (sign16(samus_pose - kPose_CF_FaceR_Ranintowall_AimUR)) {
    samus_movement_handler = kSamusFunc_F468_Shinespark[samus_pose - 201];
    samus_input_handler = FUNC16(nullsub_152);
    speed_echoes_index = 0;
    speed_echo_xspeed[0] = 0;
    speed_echo_xspeed[1] = 0;
    speed_echo_xpos[0] = 0;
    speed_echo_xpos[1] = 0;
    QueueSfx3_Max9(kSfx3_Shinespark);
  }
  return 0;
}
static const uint16 kSamusPhys_AnimDelayInWater = 3;
static const uint16 kSamusPhys_AnimDelayInAcid = 2;

void Samus_SetAnimationFrameIfPoseChanged(void) {  // 0x91FB08
  uint16 anim_delay;
  if (equipped_items & kItem_GravitySuit) {
    anim_delay = samus_x_speed_divisor;
  }
  else {
    int16 samus_bottom_bound = Samus_GetBottomBound();
    if ((int16)fx_y_pos >= 0) {
      if ((int16)fx_y_pos < samus_bottom_bound && !(fx_liquid_options & kFxLiquidOption_4_LiquidPhysicsDisabled))
        anim_delay = kSamusPhys_AnimDelayInWater;
      else
        anim_delay = samus_x_speed_divisor;
    }
    else if (0 <= (int16)lava_acid_y_pos && (int16)lava_acid_y_pos < samus_bottom_bound) {
      anim_delay = kSamusPhys_AnimDelayInAcid;
    }
    else {
      anim_delay = samus_x_speed_divisor;
    }
  }
  if ((samus_anim_frame_skip & 0x8000) == 0 && samus_pose != samus_prev_pose) {
    samus_anim_frame = samus_anim_frame_skip;
    samus_anim_frame_timer = anim_delay + get_AnimationDelayData(samus_pose)[samus_anim_frame_skip];
  }
}

void SamusFunc_EC80(void) {  // 0x91FB8E
  if (samus_prev_movement_type != kMovementType_06_Falling && samus_movement_type == kMovementType_06_Falling) {
    samus_y_subspeed = 0;
    samus_y_speed = 0;
    samus_y_dir = 2;
  }
}

void UNUSED_HandleJumpTransition_MovementTypeD(void);

void nullsub_24(void) {}
void nullsub_25(void) {}

static Func_V *const kHandleJumpTrans[28] = {  // 0x91FBBB
  nullsub_24,
  nullsub_24,
  HandleJumpTransition_NormalJump,
  HandleJumpTransition_SpinJump,
  nullsub_24,
  nullsub_24,
  nullsub_24,
  nullsub_24,
  nullsub_24,
  nullsub_24,
  nullsub_24,
  nullsub_24,
  nullsub_24,
  UNUSED_HandleJumpTransition_MovementTypeD,
  nullsub_24,
  nullsub_24,
  nullsub_24,
  nullsub_24,
  HandleJumpTransition_SpringBallInAir,
  nullsub_24,
  HandleJumpTransition_WallJump,
  nullsub_24,
  nullsub_24,
  nullsub_24,
  nullsub_24,
  nullsub_25,
  nullsub_24,
  nullsub_24,
};

void HandleJumpTransition(void) {
  kHandleJumpTrans[(samus_movement_type)]();
}


void HandleJumpTransition_WallJump(void) {  // 0x91FC08
  if (samus_prev_movement_type != kMovementType_14_WallJumping)
    Samus_InitWallJump();
}

void HandleJumpTransition_SpringBallInAir(void) {  // 0x91FC18
  if (samus_pose == kPose_7F_FaceR_Springball_Air) {
    if (samus_prev_movement_type != kMovementType_11_SpringBallOnGround)
      return;
LABEL_6:
    Samus_InitJump();
    return;
  }
  if (samus_pose == kPose_80_FaceL_Springball_Air && samus_prev_movement_type == kMovementType_11_SpringBallOnGround)
    goto LABEL_6;
}

void UNUSED_HandleJumpTransition_MovementTypeD(void) {  // 0x91FC42
  if (samus_pose == (kPose_44_FaceL_Turn_Crouch | kPose_01_FaceR_Normal | 0x20)) {
    if (samus_prev_pose != kPose_64)
      return;
LABEL_6:
    Samus_InitJump();
    return;
  }
  if (samus_pose == (kPose_44_FaceL_Turn_Crouch | kPose_02_FaceL_Normal | 0x20) && samus_prev_pose == kPose_63)
    goto LABEL_6;
}

void HandleJumpTransition_NormalJump(void) {  // 0x91FC66
  if (samus_pose == kPose_4B_FaceR_Jumptrans
      || samus_pose == kPose_4C_FaceL_Jumptrans
      || !sign16(samus_pose - kPose_55_FaceR_Jumptrans_AimU) && sign16(samus_pose - kPose_5B)) {
    if (samus_prev_pose == kPose_27_FaceR_Crouch || samus_prev_pose == kPose_28_FaceL_Crouch)
      samus_y_pos -= 10;
    Samus_InitJump();
  }
}

void HandleJumpTransition_SpinJump(void) {  // 0x91FC99
  if (samus_prev_movement_type != kMovementType_03_SpinJumping
      && samus_prev_movement_type != kMovementType_14_WallJumping) {
    Samus_InitJump();
  }
}

void XraySamusPostInputHandler(void) {  // 0x91FCAF
  if (samus_movement_type == kMovementType_0E_TurningAroundOnGround) {
    if (samus_anim_frame == 2 && samus_anim_frame_timer == 1) {
      if (samus_pose_x_dir == kSamusXDir_FaceLeft) {
        if (samus_pose == kPose_25_FaceR_Turn_Stand)
          samus_pose = kPose_D6_FaceL_Xray_Stand;
        else
          samus_pose = kPose_DA_FaceL_Xray_Crouch;
      } else if (samus_pose == kPose_26_FaceL_Turn_Stand) {
        samus_pose = kPose_D5_FaceR_Xray_Stand;
      } else {
        samus_pose = kPose_D9_FaceR_Xray_Crouch;
      }
      SamusFunc_F433();
      Samus_SetAnimationFrameIfPoseChanged();
      samus_last_different_pose = samus_prev_pose;
      *(uint16 *)&samus_last_different_pose_x_dir = *(uint16 *)&samus_prev_pose_x_dir;
      samus_prev_pose = samus_pose;
      *(uint16 *)&samus_prev_pose_x_dir = *(uint16 *)&samus_pose_x_dir;
    }
  } else {
    if (samus_pose_x_dir == kSamusXDir_FaceLeft) {
      if ((button_config_right & joypad1_lastkeys) == 0)
        return;
      xray_angle = 256 - xray_angle;
      if (samus_movement_type == kMovementType_05_Crouching)
        samus_pose = kPose_44_FaceL_Turn_Crouch;
      else
        samus_pose = kPose_26_FaceL_Turn_Stand;
    } else {
      if ((button_config_left & joypad1_lastkeys) == 0)
        return;
      xray_angle = 256 - xray_angle;
      if (samus_movement_type == kMovementType_05_Crouching)
        samus_pose = kPose_43_FaceR_Turn_Crouch;
      else
        samus_pose = kPose_25_FaceR_Turn_Stand;
    }
    SamusFunc_F433();
    Samus_SetAnimationFrameIfPoseChanged();
    samus_last_different_pose = samus_prev_pose;
    *(uint16 *)&samus_last_different_pose_x_dir = *(uint16 *)&samus_prev_pose_x_dir;
    samus_prev_pose = samus_pose;
    *(uint16 *)&samus_prev_pose_x_dir = *(uint16 *)&samus_pose_x_dir;
  }
}

static Func_U8 *const kSolidEnemyCollFuncs[4] = {  // 0x91FDAE
  HandleCollDueToChangedPose_Solid_NoColl,
  HandleCollDueToChangedPose_Solid_CollAbove,
  HandleCollDueToChangedPose_Solid_CollBelow,
  HandleCollDueToChangedPose_Solid_CollBoth,
};
static Func_U8 *const kBlockCollFuncs[4] = {
  HandleCollDueToChangedPose_Block_NoColl,
  HandleCollDueToChangedPose_Block_CollAbove,
  HandleCollDueToChangedPose_Block_CollBelow,
  HandleCollDueToChangedPose_Block_CollBoth,
};

void HandleCollDueToChangedPose(void) {
  CheckEnemyColl_Result cres;
  int32 amt;
  int16 v0;

  if (!samus_pose || samus_pose == kPose_9B_FaceF_VariaGravitySuit)
    return;
  solid_enemy_collision_flags = 0;
  block_collision_flags = 0;
  v0 = kPoseParams[samus_prev_pose].y_radius;
  if (!sign16(v0 - kPoseParams[samus_pose].y_radius))
    return;
  samus_y_radius = kPoseParams[samus_prev_pose].y_radius;
  samus_y_radius_diff = kPoseParams[samus_pose].y_radius - v0;
  samus_collision_direction = 2;
  cres = Samus_CheckSolidEnemyColl(INT16_SHL16(samus_y_radius_diff));
  samus_collision_flag = cres.collision, amt = cres.amt;
  if (samus_collision_flag)
    solid_enemy_collision_flags = 1;
  samus_space_to_move_up_enemy = (amt >> 16);
  samus_collision_direction = 3;
  cres = Samus_CheckSolidEnemyColl(INT16_SHL16(samus_y_radius_diff));
  samus_collision_flag = cres.collision, amt = cres.amt;
  if (samus_collision_flag)
    solid_enemy_collision_flags |= 2;
  samus_space_to_move_down_enemy = (amt >> 16);
  if (kSolidEnemyCollFuncs[solid_enemy_collision_flags]()) {
    samus_pose = samus_prev_pose;
    return;
  }
  amt = Samus_CollDetectChangedPose(INT16_SHL16(-samus_y_radius_diff));
  if (samus_collision_flag)
    block_collision_flags = 1;
  samus_space_to_move_up_blocks = (amt >> 16);
  
  amt = Samus_CollDetectChangedPose(INT16_SHL16(samus_y_radius_diff));
  if (samus_collision_flag)
    block_collision_flags |= 2;
  samus_space_to_move_down_blocks = (amt >> 16);
  if (kBlockCollFuncs[block_collision_flags]()) {
    samus_pose = samus_prev_pose;
  }
}

uint8 HandleCollDueToChangedPose_Solid_NoColl(void) {  // 0x91FE9A
  return 0;
}

uint8 HandleCollDueToChangedPose_Solid_CollBoth(void) {  // 0x91FE9C
  return 0;
}

uint8 HandleCollDueToChangedPose_Solid_CollAbove(void) {  // 0x91FE9E
  uint16 v1 = samus_y_radius;
  samus_y_radius = kPoseParams[samus_pose].y_radius;
  samus_collision_direction = 3;
  CheckEnemyColl_Result cres = Samus_CheckSolidEnemyColl(INT16_SHL16(samus_y_radius_diff - samus_space_to_move_up_enemy));
  samus_y_radius = v1;
  samus_collision_flag = cres.collision;
  if (samus_collision_flag)
    return 1;
  samus_space_to_move_up_enemy = cres.amt >> 16;
  return 0;
}

uint8 HandleCollDueToChangedPose_Solid_CollBelow(void) {  // 0x91FEDF
  uint16 v1 = samus_y_radius;
  samus_y_radius = kPoseParams[samus_pose].y_radius;
  samus_collision_direction = 2;
  CheckEnemyColl_Result cres = Samus_CheckSolidEnemyColl(INT16_SHL16(samus_y_radius_diff - samus_space_to_move_down_enemy));
  samus_y_radius = v1;
  samus_collision_flag = cres.collision;
  if (samus_collision_flag)
    return 1;
  samus_space_to_move_down_enemy = cres.amt >> 16;
  return 0;
}

uint8 HandleCollDueToChangedPose_Block_CollAbove(void) {  // 0x91FF20
  int32 amt = Samus_CollDetectChangedPose(INT16_SHL16(samus_y_radius_diff - samus_space_to_move_up_blocks));
  if (samus_collision_flag)
    return 1;
  if ((solid_enemy_collision_flags & 2) != 0)
    return HandleCollDueToChangedPose_Block_CollBoth();
  samus_y_pos += amt >> 16;
  samus_prev_y_pos = samus_y_pos;
  return 0;
}

uint8 HandleCollDueToChangedPose_Block_CollBelow(void) {  // 0x91FF49
  int32 amt = Samus_CollDetectChangedPose(INT16_SHL16(samus_space_to_move_down_blocks - samus_y_radius_diff));
  if (samus_collision_flag)
    return 1;
  if ((solid_enemy_collision_flags & 1) != 0)
    return HandleCollDueToChangedPose_Block_CollBoth();
  samus_y_pos -= amt >> 16;
  samus_prev_y_pos = samus_y_pos;
  return 0;
}

uint8 HandleCollDueToChangedPose_Block_NoColl(void) {  // 0x91FF76
  switch (solid_enemy_collision_flags) {
  case 0:
    return 0;
  case 1:
    samus_y_pos += samus_space_to_move_up_enemy;
    samus_prev_y_pos = samus_y_pos;
    return 0;
  case 2:
    samus_y_pos -= samus_space_to_move_down_enemy;
    samus_prev_y_pos = samus_y_pos;
    return 0;
  case 3:
    return HandleCollDueToChangedPose_Block_CollBoth();
  default:
    Unreachable();
    return 0;
  }
}

uint8 HandleCollDueToChangedPose_Block_CollBoth(void) {  // 0x91FFA7
  if (sign16(samus_y_radius - 8))
    return 1;
  samus_pose = (samus_pose_x_dir == kSamusXDir_FaceLeft) ? kPose_28_FaceL_Crouch : kPose_27_FaceR_Crouch;
  uint16 r18 = kPoseParams[samus_pose].y_radius;
  if (sign16(samus_y_radius - r18)) {
    samus_y_pos += samus_y_radius - r18;
    samus_prev_y_pos = samus_y_pos;
  }
  return 0;
}
