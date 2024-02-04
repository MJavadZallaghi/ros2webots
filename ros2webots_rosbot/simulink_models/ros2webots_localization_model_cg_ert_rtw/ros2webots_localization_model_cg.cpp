//
// File: ros2webots_localization_model_cg.cpp
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
#include "ros2webots_localization_model_cg.h"
#include "rtwtypes.h"
#include <cmath>
#include "ros2webots_localization_model_cg_private.h"
#include "rt_defines.h"

extern "C"
{

#include "rt_nonfinite.h"

}

// Exported data definition

// Const memory section
// Definition for custom storage class: Const
const real_T rosbot_wheel_radius{ 0.043 };// Referenced by:
                                             //  '<S12>/Multiply'
                                             //  '<S16>/Multiply'
                                             //  '<S20>/Multiply'
                                             //  '<S24>/Multiply'


// ROSBot wheel radius
const real_T wheel_based_localization_x_initial_coord{ 0.0 };// Referenced by: '<S9>/Delay' 

// Initial x coordinate of localization using only wheel pose data
const real_T wheel_based_localization_y_initial_coord{ 0.0 };// Referenced by: '<S9>/Delay1' 

// Initial y coordinate of localization using only wheel pose data

//
// Output and update for action system:
//    '<S11>/If Action Subsystem'
//    '<S15>/If Action Subsystem'
//    '<S19>/If Action Subsystem'
//    '<S23>/If Action Subsystem'
//
void ros2webots_localization_model_cg::ros2webots_lo_IfActionSubsystem(real_T
  rtu_In1, real_T rtu_dt_data_change, real_T *rty_Out1)
{
  // Product: '<S13>/Divide'
  *rty_Out1 = rtu_In1 / rtu_dt_data_change;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = (rtNaN);
  } else if (std::isinf(u0) && std::isinf(u1)) {
    int32_T tmp;
    int32_T tmp_0;
    if (u0 > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u1 > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = std::atan2(static_cast<real_T>(tmp), static_cast<real_T>(tmp_0));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = std::atan2(u0, u1);
  }

  return y;
}

// Model step function
void ros2webots_localization_model_cg::step()
{
  real_T rtb_Gain_i;
  real_T rtb_Multiply;
  real_T rtb_Multiply_g;
  real_T rtb_Multiply_np;
  real_T rtb_Product1_a;
  real_T rtb_Product2;

  // SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
  //   Delay: '<S9>/Delay'
  //   Outport: '<Root>/odometry_vector'

  ros2webots_localization_model_Y.odometry_vector[0] =
    ros2webots_localization_mode_DW.Delay_DSTATE;

  // If: '<S11>/If' incorporates:
  //   Delay: '<S11>/Delay'
  //   Inport: '<Root>/fl_wheel_pose'
  //   Inport: '<Root>/fl_wheel_pose_update_dt'
  //   Sum: '<S11>/Sum'

  if (ros2webots_localization_model_U.fl_wheel_pose_update_dt >= 0.001) {
    // Outputs for IfAction SubSystem: '<S11>/If Action Subsystem' incorporates:
    //   ActionPort: '<S13>/Action Port'

    ros2webots_lo_IfActionSubsystem
      (ros2webots_localization_model_U.fl_wheel_pose -
       ros2webots_localization_mode_DW.Delay_DSTATE_g,
       ros2webots_localization_model_U.fl_wheel_pose_update_dt, &rtb_Gain_i);

    // End of Outputs for SubSystem: '<S11>/If Action Subsystem'
  } else {
    // Outputs for IfAction SubSystem: '<S11>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S14>/Action Port'

    // SignalConversion generated from: '<S14>/In1' incorporates:
    //   Delay: '<S11>/Delay'
    //   Inport: '<Root>/fl_wheel_pose'
    //   Sum: '<S11>/Sum'

    rtb_Gain_i = ros2webots_localization_model_U.fl_wheel_pose -
      ros2webots_localization_mode_DW.Delay_DSTATE_g;

    // End of Outputs for SubSystem: '<S11>/If Action Subsystem1'
  }

  // End of If: '<S11>/If'

  // Gain: '<S12>/Multiply'
  rtb_Multiply = rosbot_wheel_radius * rtb_Gain_i;

  // If: '<S19>/If' incorporates:
  //   Delay: '<S19>/Delay'
  //   Inport: '<Root>/rl_wheel_pose'
  //   Inport: '<Root>/rl_wheel_pose_update_dt'
  //   Sum: '<S19>/Sum'

  if (ros2webots_localization_model_U.rl_wheel_pose_update_dt >= 0.001) {
    // Outputs for IfAction SubSystem: '<S19>/If Action Subsystem' incorporates:
    //   ActionPort: '<S21>/Action Port'

    ros2webots_lo_IfActionSubsystem
      (ros2webots_localization_model_U.rl_wheel_pose -
       ros2webots_localization_mode_DW.Delay_DSTATE_j,
       ros2webots_localization_model_U.rl_wheel_pose_update_dt, &rtb_Gain_i);

    // End of Outputs for SubSystem: '<S19>/If Action Subsystem'
  } else {
    // Outputs for IfAction SubSystem: '<S19>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S22>/Action Port'

    // SignalConversion generated from: '<S22>/In1' incorporates:
    //   Delay: '<S19>/Delay'
    //   Inport: '<Root>/rl_wheel_pose'
    //   Sum: '<S19>/Sum'

    rtb_Gain_i = ros2webots_localization_model_U.rl_wheel_pose -
      ros2webots_localization_mode_DW.Delay_DSTATE_j;

    // End of Outputs for SubSystem: '<S19>/If Action Subsystem1'
  }

  // End of If: '<S19>/If'

  // Gain: '<S20>/Multiply'
  rtb_Multiply_np = rosbot_wheel_radius * rtb_Gain_i;

  // If: '<S15>/If' incorporates:
  //   Delay: '<S15>/Delay'
  //   Inport: '<Root>/fr_wheel_pose'
  //   Inport: '<Root>/fr_wheel_pose_update_dt'
  //   Sum: '<S15>/Sum'

  if (ros2webots_localization_model_U.fr_wheel_pose_update_dt >= 0.001) {
    // Outputs for IfAction SubSystem: '<S15>/If Action Subsystem' incorporates:
    //   ActionPort: '<S17>/Action Port'

    ros2webots_lo_IfActionSubsystem
      (ros2webots_localization_model_U.fr_wheel_pose -
       ros2webots_localization_mode_DW.Delay_DSTATE_o,
       ros2webots_localization_model_U.fr_wheel_pose_update_dt, &rtb_Gain_i);

    // End of Outputs for SubSystem: '<S15>/If Action Subsystem'
  } else {
    // Outputs for IfAction SubSystem: '<S15>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S18>/Action Port'

    // SignalConversion generated from: '<S18>/In1' incorporates:
    //   Delay: '<S15>/Delay'
    //   Inport: '<Root>/fr_wheel_pose'
    //   Sum: '<S15>/Sum'

    rtb_Gain_i = ros2webots_localization_model_U.fr_wheel_pose -
      ros2webots_localization_mode_DW.Delay_DSTATE_o;

    // End of Outputs for SubSystem: '<S15>/If Action Subsystem1'
  }

  // End of If: '<S15>/If'

  // Gain: '<S16>/Multiply'
  rtb_Multiply_g = rosbot_wheel_radius * rtb_Gain_i;

  // If: '<S23>/If' incorporates:
  //   Delay: '<S23>/Delay'
  //   Inport: '<Root>/rr_wheel_pose'
  //   Inport: '<Root>/rr_wheel_pose_update_dt'
  //   Sum: '<S23>/Sum'

  if (ros2webots_localization_model_U.rr_wheel_pose_update_dt >= 0.001) {
    // Outputs for IfAction SubSystem: '<S23>/If Action Subsystem' incorporates:
    //   ActionPort: '<S25>/Action Port'

    ros2webots_lo_IfActionSubsystem
      (ros2webots_localization_model_U.rr_wheel_pose -
       ros2webots_localization_mode_DW.Delay_DSTATE_i,
       ros2webots_localization_model_U.rr_wheel_pose_update_dt, &rtb_Gain_i);

    // End of Outputs for SubSystem: '<S23>/If Action Subsystem'
  } else {
    // Outputs for IfAction SubSystem: '<S23>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S26>/Action Port'

    // SignalConversion generated from: '<S26>/In1' incorporates:
    //   Delay: '<S23>/Delay'
    //   Inport: '<Root>/rr_wheel_pose'
    //   Sum: '<S23>/Sum'

    rtb_Gain_i = ros2webots_localization_model_U.rr_wheel_pose -
      ros2webots_localization_mode_DW.Delay_DSTATE_i;

    // End of Outputs for SubSystem: '<S23>/If Action Subsystem1'
  }

  // End of If: '<S23>/If'

  // Gain: '<S5>/Gain' incorporates:
  //   Gain: '<S24>/Multiply'
  //   Gain: '<S4>/Gain'
  //   Gain: '<S8>/Gain'
  //   Sum: '<S4>/Sum'
  //   Sum: '<S5>/Sum'
  //   Sum: '<S8>/Sum'

  rtb_Gain_i = ((rosbot_wheel_radius * rtb_Gain_i + rtb_Multiply_g) * 0.5 +
                (rtb_Multiply + rtb_Multiply_np) * 0.5) * 0.5;

  // Gain: '<S1>/Multiply' incorporates:
  //   Inport: '<Root>/fl_wheel_pose_update_dt'
  //   Inport: '<Root>/fr_wheel_pose_update_dt'
  //   Inport: '<Root>/rl_wheel_pose_update_dt'
  //   Inport: '<Root>/rr_wheel_pose_update_dt'
  //   Sum: '<S1>/Sum2'

  rtb_Multiply = (((ros2webots_localization_model_U.fl_wheel_pose_update_dt +
                    ros2webots_localization_model_U.fr_wheel_pose_update_dt) +
                   ros2webots_localization_model_U.rl_wheel_pose_update_dt) +
                  ros2webots_localization_model_U.rr_wheel_pose_update_dt) *
    0.25;

  // Sqrt: '<S34>/sqrt' incorporates:
  //   Inport: '<Root>/imu_orientation_vector'
  //   Product: '<S35>/Product'
  //   Product: '<S35>/Product1'
  //   Product: '<S35>/Product2'
  //   Product: '<S35>/Product3'
  //   SignalConversion generated from: '<S10>/Vector Concatenate'
  //   Sum: '<S35>/Sum'
  //
  rtb_Multiply_np = std::sqrt
    (((ros2webots_localization_model_U.imu_orientation_vector[0] *
       ros2webots_localization_model_U.imu_orientation_vector[0] +
       ros2webots_localization_model_U.imu_orientation_vector[1] *
       ros2webots_localization_model_U.imu_orientation_vector[1]) +
      ros2webots_localization_model_U.imu_orientation_vector[2] *
      ros2webots_localization_model_U.imu_orientation_vector[2]) +
     ros2webots_localization_model_U.imu_orientation_vector[3] *
     ros2webots_localization_model_U.imu_orientation_vector[3]);

  // Product: '<S29>/Product' incorporates:
  //   Inport: '<Root>/imu_orientation_vector'
  //   SignalConversion generated from: '<S10>/Vector Concatenate'

  rtb_Multiply_g = ros2webots_localization_model_U.imu_orientation_vector[0] /
    rtb_Multiply_np;

  // Product: '<S29>/Product1' incorporates:
  //   Inport: '<Root>/imu_orientation_vector'
  //   SignalConversion generated from: '<S10>/Vector Concatenate'

  rtb_Product1_a = ros2webots_localization_model_U.imu_orientation_vector[1] /
    rtb_Multiply_np;

  // Product: '<S29>/Product2' incorporates:
  //   Inport: '<Root>/imu_orientation_vector'
  //   SignalConversion generated from: '<S10>/Vector Concatenate'

  rtb_Product2 = ros2webots_localization_model_U.imu_orientation_vector[2] /
    rtb_Multiply_np;

  // Product: '<S29>/Product3' incorporates:
  //   Inport: '<Root>/imu_orientation_vector'
  //   SignalConversion generated from: '<S10>/Vector Concatenate'

  rtb_Multiply_np = ros2webots_localization_model_U.imu_orientation_vector[3] /
    rtb_Multiply_np;

  // Trigonometry: '<S28>/Trigonometric Function3' incorporates:
  //   Fcn: '<S27>/fcn4'
  //   Fcn: '<S27>/fcn5'

  rtb_Multiply_np = rt_atan2d_snf((rtb_Product2 * rtb_Multiply_np +
    rtb_Multiply_g * rtb_Product1_a) * 2.0, ((rtb_Multiply_g * rtb_Multiply_g -
    rtb_Product1_a * rtb_Product1_a) - rtb_Product2 * rtb_Product2) +
    rtb_Multiply_np * rtb_Multiply_np);

  // Sum: '<S9>/Sum' incorporates:
  //   Delay: '<S9>/Delay'
  //   Product: '<S9>/Product'
  //   Trigonometry: '<S9>/Cos'

  ros2webots_localization_mode_DW.Delay_DSTATE += std::cos(rtb_Multiply_np) *
    rtb_Gain_i * rtb_Multiply;

  // SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
  //   Delay: '<S9>/Delay1'
  //   Outport: '<Root>/odometry_vector'

  ros2webots_localization_model_Y.odometry_vector[1] =
    ros2webots_localization_mode_DW.Delay1_DSTATE;

  // Sum: '<S9>/Sum1' incorporates:
  //   Delay: '<S9>/Delay1'
  //   Product: '<S9>/Product1'
  //   Trigonometry: '<S9>/Sin'

  ros2webots_localization_mode_DW.Delay1_DSTATE += rtb_Gain_i * rtb_Multiply *
    std::sin(rtb_Multiply_np);

  // SignalConversion generated from: '<S1>/Vector Concatenate' incorporates:
  //   Outport: '<Root>/odometry_vector'

  ros2webots_localization_model_Y.odometry_vector[2] = rtb_Multiply_np;

  // Update for Delay: '<S11>/Delay' incorporates:
  //   Inport: '<Root>/fl_wheel_pose'

  ros2webots_localization_mode_DW.Delay_DSTATE_g =
    ros2webots_localization_model_U.fl_wheel_pose;

  // Update for Delay: '<S19>/Delay' incorporates:
  //   Inport: '<Root>/rl_wheel_pose'

  ros2webots_localization_mode_DW.Delay_DSTATE_j =
    ros2webots_localization_model_U.rl_wheel_pose;

  // Update for Delay: '<S15>/Delay' incorporates:
  //   Inport: '<Root>/fr_wheel_pose'

  ros2webots_localization_mode_DW.Delay_DSTATE_o =
    ros2webots_localization_model_U.fr_wheel_pose;

  // Update for Delay: '<S23>/Delay' incorporates:
  //   Inport: '<Root>/rr_wheel_pose'

  ros2webots_localization_mode_DW.Delay_DSTATE_i =
    ros2webots_localization_model_U.rr_wheel_pose;
}

// Model initialize function
void ros2webots_localization_model_cg::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // InitializeConditions for Delay: '<S9>/Delay'
  ros2webots_localization_mode_DW.Delay_DSTATE =
    wheel_based_localization_x_initial_coord;

  // InitializeConditions for Delay: '<S9>/Delay1'
  ros2webots_localization_mode_DW.Delay1_DSTATE =
    wheel_based_localization_y_initial_coord;
}

// Model terminate function
void ros2webots_localization_model_cg::terminate()
{
  // (no terminate code required)
}

// Constructor
ros2webots_localization_model_cg::ros2webots_localization_model_cg() :
  ros2webots_localization_model_U(),
  ros2webots_localization_model_Y(),
  ros2webots_localization_mode_DW(),
  ros2webots_localization_mode_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
ros2webots_localization_model_cg::~ros2webots_localization_model_cg() = default;

// Real-Time Model get method
ros2webots_localization_model_cg::RT_MODEL_ros2webots_localizat_T
  * ros2webots_localization_model_cg::getRTM()
{
  return (&ros2webots_localization_mode_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
