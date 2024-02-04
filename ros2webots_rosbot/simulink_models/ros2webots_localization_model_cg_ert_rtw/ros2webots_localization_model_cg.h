//
// File: ros2webots_localization_model_cg.h
//
// Code generated for Simulink model 'ros2webots_localization_model_cg'.
//
// Model version                  : 1.252
// Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
// C/C++ source code generated on : Sun Feb  4 13:15:47 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_ros2webots_localization_model_cg_h_
#define RTW_HEADER_ros2webots_localization_model_cg_h_
#include "rtwtypes.h"
#include "ros2webots_localization_model_cg_types.h"

extern "C"
{

#include "rtGetNaN.h"

}

extern "C"
{

#include "rt_nonfinite.h"

}

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#define ros2webots_localization_model_cg_M (ros2webots_localization_mode_M)

// Exported data declaration

// Const memory section
// Declaration for custom storage class: Const
extern const real_T rosbot_wheel_radius;// Referenced by:
                                           //  '<S12>/Multiply'
                                           //  '<S16>/Multiply'
                                           //  '<S20>/Multiply'
                                           //  '<S24>/Multiply'


// ROSBot wheel radius
extern const real_T wheel_based_localization_x_initial_coord;// Referenced by: '<S9>/Delay' 

// Initial x coordinate of localization using only wheel pose data
extern const real_T wheel_based_localization_y_initial_coord;// Referenced by: '<S9>/Delay1' 

// Initial y coordinate of localization using only wheel pose data

// Class declaration for model ros2webots_localization_model_cg
class ros2webots_localization_model_cg final
{
  // public data and function members
 public:
  // Block states (default storage) for system '<Root>'
  struct DW_ros2webots_localization_mo_T {
    real_T Delay_DSTATE;               // '<S9>/Delay'
    real_T Delay_DSTATE_g;             // '<S11>/Delay'
    real_T Delay_DSTATE_j;             // '<S19>/Delay'
    real_T Delay_DSTATE_o;             // '<S15>/Delay'
    real_T Delay_DSTATE_i;             // '<S23>/Delay'
    real_T Delay1_DSTATE;              // '<S9>/Delay1'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU_ros2webots_localization__T {
    real_T imu_orientation_vector[4];  // '<Root>/imu_orientation_vector'
    real_T imu_angular_velocity_vector[3];// '<Root>/imu_angular_velocity_vector' 
    real_T imu_linear_acceleration_vector[3];
                                     // '<Root>/imu_linear_acceleration_vector'
    real_T fl_wheel_pose;              // '<Root>/fl_wheel_pose'
    real_T fr_wheel_pose;              // '<Root>/fr_wheel_pose'
    real_T rl_wheel_pose;              // '<Root>/rl_wheel_pose'
    real_T rr_wheel_pose;              // '<Root>/rr_wheel_pose'
    real_T fl_wheel_pose_update_dt;    // '<Root>/fl_wheel_pose_update_dt'
    real_T fr_wheel_pose_update_dt;    // '<Root>/fr_wheel_pose_update_dt'
    real_T rl_wheel_pose_update_dt;    // '<Root>/rl_wheel_pose_update_dt'
    real_T rr_wheel_pose_update_dt;    // '<Root>/rr_wheel_pose_update_dt'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY_ros2webots_localization__T {
    real_T odometry_vector[3];         // '<Root>/odometry_vector'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_ros2webots_localizat_T {
    const char_T * volatile errorStatus;
  };

  // Copy Constructor
  ros2webots_localization_model_cg(ros2webots_localization_model_cg const&) =
    delete;

  // Assignment Operator
  ros2webots_localization_model_cg& operator= (ros2webots_localization_model_cg
    const&) & = delete;

  // Move Constructor
  ros2webots_localization_model_cg(ros2webots_localization_model_cg &&) = delete;

  // Move Assignment Operator
  ros2webots_localization_model_cg& operator= (ros2webots_localization_model_cg &&)
    = delete;

  // Real-Time Model get method
  ros2webots_localization_model_cg::RT_MODEL_ros2webots_localizat_T * getRTM();

  // Root inports set method
  void setExternalInputs(const ExtU_ros2webots_localization__T
    *pExtU_ros2webots_localization__T)
  {
    ros2webots_localization_model_U = *pExtU_ros2webots_localization__T;
  }

  // Root outports get method
  const ExtY_ros2webots_localization__T &getExternalOutputs() const
  {
    return ros2webots_localization_model_Y;
  }

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  ros2webots_localization_model_cg();

  // Destructor
  ~ros2webots_localization_model_cg();

  // private data and function members
 private:
  // External inputs
  ExtU_ros2webots_localization__T ros2webots_localization_model_U;

  // External outputs
  ExtY_ros2webots_localization__T ros2webots_localization_model_Y;

  // Block states
  DW_ros2webots_localization_mo_T ros2webots_localization_mode_DW;

  // private member function(s) for subsystem '<S11>/If Action Subsystem'
  static void ros2webots_lo_IfActionSubsystem(real_T rtu_In1, real_T
    rtu_dt_data_change, real_T *rty_Out1);

  // Real-Time Model
  RT_MODEL_ros2webots_localizat_T ros2webots_localization_mode_M;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S2>/Scope' : Unused code path elimination
//  Block '<S3>/Scope' : Unused code path elimination
//  Block '<S6>/Scope' : Unused code path elimination
//  Block '<S7>/Scope' : Unused code path elimination
//  Block '<S10>/Scope' : Unused code path elimination


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'ros2webots_localization_model_cg'
//  '<S1>'   : 'ros2webots_localization_model_cg/localization'
//  '<S2>'   : 'ros2webots_localization_model_cg/localization/FL Wheel Velocity Estimator'
//  '<S3>'   : 'ros2webots_localization_model_cg/localization/FR Wheel Velocity Estimator'
//  '<S4>'   : 'ros2webots_localization_model_cg/localization/Left Side Velocity'
//  '<S5>'   : 'ros2webots_localization_model_cg/localization/Middle Velocity'
//  '<S6>'   : 'ros2webots_localization_model_cg/localization/RL Wheel Velocity Estimator'
//  '<S7>'   : 'ros2webots_localization_model_cg/localization/RR Wheel Velocity Estimator'
//  '<S8>'   : 'ros2webots_localization_model_cg/localization/Right Side Velocity'
//  '<S9>'   : 'ros2webots_localization_model_cg/localization/Subsystem'
//  '<S10>'  : 'ros2webots_localization_model_cg/localization/yaw_estimator'
//  '<S11>'  : 'ros2webots_localization_model_cg/localization/FL Wheel Velocity Estimator/fl_wheel_speed_calc'
//  '<S12>'  : 'ros2webots_localization_model_cg/localization/FL Wheel Velocity Estimator/wheel rps 2 wheel mps'
//  '<S13>'  : 'ros2webots_localization_model_cg/localization/FL Wheel Velocity Estimator/fl_wheel_speed_calc/If Action Subsystem'
//  '<S14>'  : 'ros2webots_localization_model_cg/localization/FL Wheel Velocity Estimator/fl_wheel_speed_calc/If Action Subsystem1'
//  '<S15>'  : 'ros2webots_localization_model_cg/localization/FR Wheel Velocity Estimator/fl_wheel_speed_calc'
//  '<S16>'  : 'ros2webots_localization_model_cg/localization/FR Wheel Velocity Estimator/wheel rps 2 wheel mps'
//  '<S17>'  : 'ros2webots_localization_model_cg/localization/FR Wheel Velocity Estimator/fl_wheel_speed_calc/If Action Subsystem'
//  '<S18>'  : 'ros2webots_localization_model_cg/localization/FR Wheel Velocity Estimator/fl_wheel_speed_calc/If Action Subsystem1'
//  '<S19>'  : 'ros2webots_localization_model_cg/localization/RL Wheel Velocity Estimator/fl_wheel_speed_calc'
//  '<S20>'  : 'ros2webots_localization_model_cg/localization/RL Wheel Velocity Estimator/wheel rps 2 wheel mps'
//  '<S21>'  : 'ros2webots_localization_model_cg/localization/RL Wheel Velocity Estimator/fl_wheel_speed_calc/If Action Subsystem'
//  '<S22>'  : 'ros2webots_localization_model_cg/localization/RL Wheel Velocity Estimator/fl_wheel_speed_calc/If Action Subsystem1'
//  '<S23>'  : 'ros2webots_localization_model_cg/localization/RR Wheel Velocity Estimator/fl_wheel_speed_calc'
//  '<S24>'  : 'ros2webots_localization_model_cg/localization/RR Wheel Velocity Estimator/wheel rps 2 wheel mps'
//  '<S25>'  : 'ros2webots_localization_model_cg/localization/RR Wheel Velocity Estimator/fl_wheel_speed_calc/If Action Subsystem'
//  '<S26>'  : 'ros2webots_localization_model_cg/localization/RR Wheel Velocity Estimator/fl_wheel_speed_calc/If Action Subsystem1'
//  '<S27>'  : 'ros2webots_localization_model_cg/localization/yaw_estimator/Quaternions to Rotation Angles'
//  '<S28>'  : 'ros2webots_localization_model_cg/localization/yaw_estimator/Quaternions to Rotation Angles/Angle Calculation'
//  '<S29>'  : 'ros2webots_localization_model_cg/localization/yaw_estimator/Quaternions to Rotation Angles/Quaternion Normalize'
//  '<S30>'  : 'ros2webots_localization_model_cg/localization/yaw_estimator/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input'
//  '<S31>'  : 'ros2webots_localization_model_cg/localization/yaw_estimator/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input/If Action Subsystem'
//  '<S32>'  : 'ros2webots_localization_model_cg/localization/yaw_estimator/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input/If Action Subsystem1'
//  '<S33>'  : 'ros2webots_localization_model_cg/localization/yaw_estimator/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input/If Action Subsystem2'
//  '<S34>'  : 'ros2webots_localization_model_cg/localization/yaw_estimator/Quaternions to Rotation Angles/Quaternion Normalize/Quaternion Modulus'
//  '<S35>'  : 'ros2webots_localization_model_cg/localization/yaw_estimator/Quaternions to Rotation Angles/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'

#endif                        // RTW_HEADER_ros2webots_localization_model_cg_h_

//
// File trailer for generated code.
//
// [EOF]
//
