//
// File: ros2webots_go_to_point_controller_model_cg.cpp
//
// Code generated for Simulink model 'ros2webots_go_to_point_controller_model_cg'.
//
// Model version                  : 1.347
// Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
// C/C++ source code generated on : Sat Mar  2 16:57:53 2024
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "ros2webots_go_to_point_controller_model_cg.h"
#include "rtwtypes.h"
#include <cmath>
#include "ros2webots_go_to_point_controller_model_cg_private.h"
#include "rt_defines.h"

extern "C"
{

#include "rt_nonfinite.h"

}

// Named constants for Chart: '<S1>/Chart'
const uint8_T ros2webots_go_IN_controller_off{ 1U };

const uint8_T ros2webots_go__IN_controller_on{ 2U };

const real_T ros2webots_param_error_distance{ 0.05 };

// Exported data definition

// Const memory section
// Definition for custom storage class: Const
const real_T laterl_PID_kd{ 0.0 };    // Referenced by: '<S31>/Derivative Gain'

// Lateral PID controller gain: Kd
const real_T laterl_PID_ki{ 0.3 };     // Referenced by: '<S34>/Integral Gain'

// Lateral PID controller gain: Ki
const real_T laterl_PID_kp{ 1. };  // Referenced by: '<S42>/Proportional Gain'

// Lateral PID controller gain: Kp
const real_T longitudinal_speed_gain{ 0.1 };// Referenced by: '<S1>/Gain'

// The gain thay manipulate main state machine velocity command
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
void ros2webots_go_to_point_controller_model_cg::step()
{
  real_T rtb_MatrixMultiply_tmp;
  real_T rtb_MatrixMultiply_tmp_0;
  real_T rtb_VectorConcatenate_idx_0;
  real_T rtb_VectorConcatenate_idx_1;
  real_T rtb_error_heading;
  uint8_T rtb_command_vel;

  // Sum: '<S1>/Subtract' incorporates:
  //   Inport: '<Root>/x_act'
  //   Inport: '<Root>/x_des'

  rtb_VectorConcatenate_idx_0 = ros2webots_go_to_point_contro_U.x_des -
    ros2webots_go_to_point_contro_U.x_act;

  // Sum: '<S1>/Subtract1' incorporates:
  //   Inport: '<Root>/y_act'
  //   Inport: '<Root>/y_des'

  rtb_VectorConcatenate_idx_1 = ros2webots_go_to_point_contro_U.y_des -
    ros2webots_go_to_point_contro_U.y_act;

  // MATLAB Function: '<S1>/Rotation matrix: 2D, Z' incorporates:
  //   Inport: '<Root>/yaw_act'

  rtb_MatrixMultiply_tmp = std::sin(ros2webots_go_to_point_contro_U.yaw_act);
  rtb_MatrixMultiply_tmp_0 = std::cos(ros2webots_go_to_point_contro_U.yaw_act);

  // Product: '<S1>/MatrixMultiply' incorporates:
  //   MATLAB Function: '<S1>/Rotation matrix: 2D, Z'

  rtb_error_heading = rtb_MatrixMultiply_tmp_0 * rtb_VectorConcatenate_idx_0 +
    rtb_MatrixMultiply_tmp * rtb_VectorConcatenate_idx_1;
  rtb_VectorConcatenate_idx_1 = -rtb_MatrixMultiply_tmp *
    rtb_VectorConcatenate_idx_0 + rtb_MatrixMultiply_tmp_0 *
    rtb_VectorConcatenate_idx_1;

  // MATLAB Function: '<S1>/Error calculator' incorporates:
  //   Product: '<S1>/MatrixMultiply'

  rtb_VectorConcatenate_idx_0 = std::sqrt(rtb_error_heading * rtb_error_heading
    + rtb_VectorConcatenate_idx_1 * rtb_VectorConcatenate_idx_1);
  rtb_error_heading = rt_atan2d_snf(rtb_VectorConcatenate_idx_1,
    rtb_error_heading);

  // Chart: '<S1>/Chart'
  if (ros2webots_go_to_point_contr_DW.is_active_c8_ros2webots_go_to_p == 0U) {
    ros2webots_go_to_point_contr_DW.is_active_c8_ros2webots_go_to_p = 1U;
    ros2webots_go_to_point_contr_DW.is_c8_ros2webots_go_to_point_co =
      ros2webots_go_IN_controller_off;

    // Outport: '<Root>/controller_state'
    ros2webots_go_to_point_contro_Y.controller_state = 0U;
    rtb_command_vel = 0U;
  } else if (ros2webots_go_to_point_contr_DW.is_c8_ros2webots_go_to_point_co ==
             ros2webots_go_IN_controller_off) {
    if (rtb_VectorConcatenate_idx_0 >= ros2webots_param_error_distance) {
      ros2webots_go_to_point_contr_DW.is_c8_ros2webots_go_to_point_co =
        ros2webots_go__IN_controller_on;

      // Outport: '<Root>/controller_state'
      ros2webots_go_to_point_contro_Y.controller_state = 1U;
      rtb_command_vel = 1U;
    } else {
      // Outport: '<Root>/controller_state'
      ros2webots_go_to_point_contro_Y.controller_state = 0U;
      rtb_command_vel = 0U;
    }

    // case IN_controller_on:
  } else if (rtb_VectorConcatenate_idx_0 < 0.21000000000000002) {
    ros2webots_go_to_point_contr_DW.is_c8_ros2webots_go_to_point_co =
      ros2webots_go_IN_controller_off;

    // Outport: '<Root>/controller_state'
    ros2webots_go_to_point_contro_Y.controller_state = 0U;
    rtb_command_vel = 0U;
  } else {
    // Outport: '<Root>/controller_state'
    ros2webots_go_to_point_contro_Y.controller_state = 1U;
    rtb_command_vel = 1U;
  }

  // End of Chart: '<S1>/Chart'

  // Outport: '<Root>/command_velocity' incorporates:
  //   DataTypeConversion: '<S1>/Data Type Conversion'
  //   Gain: '<S1>/Gain'

  ros2webots_go_to_point_contro_Y.command_velocity = longitudinal_speed_gain *
    static_cast<real_T>(rtb_command_vel);

  // Gain: '<S40>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S32>/Filter'
  //   Gain: '<S31>/Derivative Gain'
  //   Sum: '<S32>/SumD'

  rtb_VectorConcatenate_idx_0 = (laterl_PID_kd * rtb_error_heading -
    ros2webots_go_to_point_contr_DW.Filter_DSTATE) * 100.0;

  // Sum: '<S46>/Sum' incorporates:
  //   DiscreteIntegrator: '<S37>/Integrator'
  //   Gain: '<S42>/Proportional Gain'

  ros2webots_go_to_point_contro_Y.command_steering_angle = (laterl_PID_kp *
    rtb_error_heading + ros2webots_go_to_point_contr_DW.Integrator_DSTATE) +
    rtb_VectorConcatenate_idx_0;

  // Saturate: '<S1>/Saturation'
  if (ros2webots_go_to_point_contro_Y.command_steering_angle >
      (2*0.78539816339744828)) {
    // Sum: '<S46>/Sum' incorporates:
    //   Outport: '<Root>/command_steering_angle'

    ros2webots_go_to_point_contro_Y.command_steering_angle = 2*0.78539816339744828;
  } else if (ros2webots_go_to_point_contro_Y.command_steering_angle <
             (2*-0.78539816339744828)) {
    // Sum: '<S46>/Sum' incorporates:
    //   Outport: '<Root>/command_steering_angle'

    ros2webots_go_to_point_contro_Y.command_steering_angle =
      2*-0.78539816339744828;
  }

  // End of Saturate: '<S1>/Saturation'

  // Update for DiscreteIntegrator: '<S37>/Integrator' incorporates:
  //   Gain: '<S34>/Integral Gain'

  ros2webots_go_to_point_contr_DW.Integrator_DSTATE += laterl_PID_ki *
    rtb_error_heading * 0.05;

  // Update for DiscreteIntegrator: '<S32>/Filter'
  ros2webots_go_to_point_contr_DW.Filter_DSTATE += 0.05 *
    rtb_VectorConcatenate_idx_0;
}

// Model initialize function
void ros2webots_go_to_point_controller_model_cg::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
}

// Model terminate function
void ros2webots_go_to_point_controller_model_cg::terminate()
{
  // (no terminate code required)
}

// Constructor
ros2webots_go_to_point_controller_model_cg::
  ros2webots_go_to_point_controller_model_cg() :
  ros2webots_go_to_point_contro_U(),
  ros2webots_go_to_point_contro_Y(),
  ros2webots_go_to_point_contr_DW(),
  ros2webots_go_to_point_contr_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
ros2webots_go_to_point_controller_model_cg::
  ~ros2webots_go_to_point_controller_model_cg() = default;

// Real-Time Model get method
ros2webots_go_to_point_controller_model_cg::RT_MODEL_ros2webots_go_to_poi_T
  * ros2webots_go_to_point_controller_model_cg::getRTM()
{
  return (&ros2webots_go_to_point_contr_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
