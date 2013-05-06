/* Include files */

#include <stddef.h>
#include "blas.h"
#include "quadtestmodel_sfun.h"
#include "c2_quadtestmodel.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "quadtestmodel_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c2_debug_family_names[18] = { "Xdot", "Ts", "q", "DCM", "p",
  "r", "qdotM", "nargin", "nargout", "a", "g", "agsamp", "t", "y", "P", "X",
  "oldagsamp", "oldt" };

/* Function Declarations */
static void initialize_c2_quadtestmodel(SFc2_quadtestmodelInstanceStruct
  *chartInstance);
static void initialize_params_c2_quadtestmodel(SFc2_quadtestmodelInstanceStruct *
  chartInstance);
static void enable_c2_quadtestmodel(SFc2_quadtestmodelInstanceStruct
  *chartInstance);
static void disable_c2_quadtestmodel(SFc2_quadtestmodelInstanceStruct
  *chartInstance);
static void c2_update_debugger_state_c2_quadtestmodel
  (SFc2_quadtestmodelInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_quadtestmodel
  (SFc2_quadtestmodelInstanceStruct *chartInstance);
static void set_sim_state_c2_quadtestmodel(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_st);
static void finalize_c2_quadtestmodel(SFc2_quadtestmodelInstanceStruct
  *chartInstance);
static void sf_c2_quadtestmodel(SFc2_quadtestmodelInstanceStruct *chartInstance);
static void c2_chartstep_c2_quadtestmodel(SFc2_quadtestmodelInstanceStruct
  *chartInstance);
static void initSimStructsc2_quadtestmodel(SFc2_quadtestmodelInstanceStruct
  *chartInstance);
static void registerMessagesc2_quadtestmodel(SFc2_quadtestmodelInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static real_T c2_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_b_oldt, const char_T *c2_identifier);
static real_T c2_b_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_c_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_b_oldagsamp, const char_T *c2_identifier);
static real_T c2_d_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_e_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_b_X, const char_T *c2_identifier, real_T
  c2_y[16]);
static void c2_f_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[16]);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_g_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_b_P, const char_T *c2_identifier, real_T
  c2_y[256]);
static void c2_h_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[256]);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_i_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_y, const char_T *c2_identifier, real_T
  c2_b_y[16]);
static void c2_j_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[16]);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_k_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_l_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[16]);
static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_m_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[9]);
static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_n_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[4]);
static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[33]);
static void c2_eml_scalar_eg(SFc2_quadtestmodelInstanceStruct *chartInstance);
static void c2_b_eml_scalar_eg(SFc2_quadtestmodelInstanceStruct *chartInstance);
static const mxArray *c2_k_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_o_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_p_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_quadtestmodel, const char_T
  *c2_identifier);
static uint8_T c2_q_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_quadtestmodelInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_quadtestmodel(SFc2_quadtestmodelInstanceStruct
  *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_P_not_empty = FALSE;
  chartInstance->c2_X_not_empty = FALSE;
  chartInstance->c2_oldagsamp_not_empty = FALSE;
  chartInstance->c2_oldt_not_empty = FALSE;
  chartInstance->c2_is_active_c2_quadtestmodel = 0U;
}

static void initialize_params_c2_quadtestmodel(SFc2_quadtestmodelInstanceStruct *
  chartInstance)
{
}

static void enable_c2_quadtestmodel(SFc2_quadtestmodelInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_quadtestmodel(SFc2_quadtestmodelInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_quadtestmodel
  (SFc2_quadtestmodelInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c2_quadtestmodel
  (SFc2_quadtestmodelInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i0;
  real_T c2_u[16];
  const mxArray *c2_b_y = NULL;
  int32_T c2_i1;
  real_T c2_b_u[256];
  const mxArray *c2_c_y = NULL;
  int32_T c2_i2;
  real_T c2_c_u[16];
  const mxArray *c2_d_y = NULL;
  real_T c2_hoistedGlobal;
  real_T c2_d_u;
  const mxArray *c2_e_y = NULL;
  real_T c2_b_hoistedGlobal;
  real_T c2_e_u;
  const mxArray *c2_f_y = NULL;
  uint8_T c2_c_hoistedGlobal;
  uint8_T c2_f_u;
  const mxArray *c2_g_y = NULL;
  real_T (*c2_h_y)[16];
  c2_h_y = (real_T (*)[16])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(6), FALSE);
  for (c2_i0 = 0; c2_i0 < 16; c2_i0++) {
    c2_u[c2_i0] = (*c2_h_y)[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 16), FALSE);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  for (c2_i1 = 0; c2_i1 < 256; c2_i1++) {
    c2_b_u[c2_i1] = chartInstance->c2_P[c2_i1];
  }

  c2_c_y = NULL;
  if (!chartInstance->c2_P_not_empty) {
    sf_mex_assign(&c2_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 16, 16),
                  FALSE);
  }

  sf_mex_setcell(c2_y, 1, c2_c_y);
  for (c2_i2 = 0; c2_i2 < 16; c2_i2++) {
    c2_c_u[c2_i2] = chartInstance->c2_X[c2_i2];
  }

  c2_d_y = NULL;
  if (!chartInstance->c2_X_not_empty) {
    sf_mex_assign(&c2_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 1, 16),
                  FALSE);
  }

  sf_mex_setcell(c2_y, 2, c2_d_y);
  c2_hoistedGlobal = chartInstance->c2_oldagsamp;
  c2_d_u = c2_hoistedGlobal;
  c2_e_y = NULL;
  if (!chartInstance->c2_oldagsamp_not_empty) {
    sf_mex_assign(&c2_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_d_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c2_y, 3, c2_e_y);
  c2_b_hoistedGlobal = chartInstance->c2_oldt;
  c2_e_u = c2_b_hoistedGlobal;
  c2_f_y = NULL;
  if (!chartInstance->c2_oldt_not_empty) {
    sf_mex_assign(&c2_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c2_f_y, sf_mex_create("y", &c2_e_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c2_y, 4, c2_f_y);
  c2_c_hoistedGlobal = chartInstance->c2_is_active_c2_quadtestmodel;
  c2_f_u = c2_c_hoistedGlobal;
  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", &c2_f_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 5, c2_g_y);
  sf_mex_assign(&c2_st, c2_y, FALSE);
  return c2_st;
}

static void set_sim_state_c2_quadtestmodel(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[16];
  int32_T c2_i3;
  real_T c2_dv1[256];
  int32_T c2_i4;
  real_T c2_dv2[16];
  int32_T c2_i5;
  real_T (*c2_y)[16];
  c2_y = (real_T (*)[16])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)), "y",
                        c2_dv0);
  for (c2_i3 = 0; c2_i3 < 16; c2_i3++) {
    (*c2_y)[c2_i3] = c2_dv0[c2_i3];
  }

  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)), "P",
                        c2_dv1);
  for (c2_i4 = 0; c2_i4 < 256; c2_i4++) {
    chartInstance->c2_P[c2_i4] = c2_dv1[c2_i4];
  }

  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 2)), "X",
                        c2_dv2);
  for (c2_i5 = 0; c2_i5 < 16; c2_i5++) {
    chartInstance->c2_X[c2_i5] = c2_dv2[c2_i5];
  }

  chartInstance->c2_oldagsamp = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 3)), "oldagsamp");
  chartInstance->c2_oldt = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 4)), "oldt");
  chartInstance->c2_is_active_c2_quadtestmodel = c2_p_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 5)),
     "is_active_c2_quadtestmodel");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_quadtestmodel(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_quadtestmodel(SFc2_quadtestmodelInstanceStruct
  *chartInstance)
{
}

static void sf_c2_quadtestmodel(SFc2_quadtestmodelInstanceStruct *chartInstance)
{
  int32_T c2_i6;
  int32_T c2_i7;
  int32_T c2_i8;
  real_T *c2_agsamp;
  real_T *c2_t;
  real_T (*c2_g)[3];
  real_T (*c2_y)[16];
  real_T (*c2_a)[3];
  c2_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c2_agsamp = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c2_g = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c2_y = (real_T (*)[16])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_a = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i6 = 0; c2_i6 < 3; c2_i6++) {
    _SFD_DATA_RANGE_CHECK((*c2_a)[c2_i6], 0U);
  }

  for (c2_i7 = 0; c2_i7 < 16; c2_i7++) {
    _SFD_DATA_RANGE_CHECK((*c2_y)[c2_i7], 1U);
  }

  for (c2_i8 = 0; c2_i8 < 3; c2_i8++) {
    _SFD_DATA_RANGE_CHECK((*c2_g)[c2_i8], 2U);
  }

  _SFD_DATA_RANGE_CHECK(*c2_agsamp, 3U);
  _SFD_DATA_RANGE_CHECK(*c2_t, 4U);
  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_quadtestmodel(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_quadtestmodelMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c2_chartstep_c2_quadtestmodel(SFc2_quadtestmodelInstanceStruct
  *chartInstance)
{
  real_T c2_hoistedGlobal;
  real_T c2_b_hoistedGlobal;
  int32_T c2_i9;
  real_T c2_a[3];
  int32_T c2_i10;
  real_T c2_g[3];
  real_T c2_agsamp;
  real_T c2_t;
  uint32_T c2_debug_family_var_map[18];
  real_T c2_Xdot[16];
  real_T c2_Ts;
  real_T c2_q[4];
  real_T c2_DCM[9];
  real_T c2_p;
  real_T c2_r;
  real_T c2_qdotM[16];
  real_T c2_b_q;
  real_T c2_nargin = 4.0;
  real_T c2_nargout = 1.0;
  real_T c2_y[16];
  int32_T c2_i11;
  static real_T c2_dv3[16] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  int32_T c2_i12;
  int32_T c2_i13;
  int32_T c2_i14;
  int32_T c2_i15;
  real_T c2_b;
  real_T c2_b_y;
  real_T c2_b_a;
  real_T c2_b_b;
  real_T c2_c_y;
  real_T c2_c_b;
  real_T c2_d_y;
  real_T c2_c_a;
  real_T c2_d_b;
  real_T c2_e_y;
  real_T c2_e_b;
  real_T c2_f_y;
  real_T c2_d_a;
  real_T c2_f_b;
  real_T c2_g_y;
  real_T c2_g_b;
  real_T c2_h_y;
  real_T c2_e_a;
  real_T c2_h_b;
  real_T c2_i_y;
  real_T c2_i_b;
  real_T c2_j_y;
  real_T c2_f_a;
  real_T c2_j_b;
  real_T c2_k_y;
  real_T c2_k_b;
  real_T c2_l_y;
  real_T c2_g_a;
  real_T c2_l_b;
  real_T c2_m_y;
  real_T c2_m_b;
  real_T c2_n_y;
  real_T c2_h_a;
  real_T c2_n_b;
  real_T c2_o_y;
  real_T c2_o_b;
  real_T c2_p_y;
  real_T c2_i_a;
  real_T c2_p_b;
  real_T c2_q_y;
  real_T c2_q_b;
  real_T c2_r_y;
  real_T c2_j_a;
  real_T c2_r_b;
  real_T c2_s_y;
  real_T c2_s_b;
  real_T c2_t_y;
  real_T c2_k_a;
  real_T c2_t_b;
  real_T c2_u_y;
  real_T c2_u_b;
  real_T c2_v_y;
  real_T c2_l_a;
  real_T c2_v_b;
  real_T c2_w_y;
  real_T c2_w_b;
  real_T c2_x_y;
  real_T c2_m_a;
  real_T c2_x_b;
  real_T c2_y_y;
  real_T c2_y_b;
  real_T c2_ab_y;
  real_T c2_n_a;
  real_T c2_ab_b;
  real_T c2_bb_y;
  real_T c2_bb_b;
  real_T c2_cb_y;
  real_T c2_o_a;
  real_T c2_cb_b;
  real_T c2_db_y;
  real_T c2_db_b;
  real_T c2_eb_y;
  real_T c2_p_a;
  real_T c2_eb_b;
  real_T c2_fb_y;
  real_T c2_fb_b;
  real_T c2_gb_y;
  real_T c2_q_a;
  real_T c2_gb_b;
  real_T c2_hb_y;
  real_T c2_hb_b;
  real_T c2_ib_y;
  real_T c2_r_a;
  real_T c2_ib_b;
  real_T c2_jb_y;
  real_T c2_jb_b;
  real_T c2_kb_y;
  real_T c2_s_a;
  real_T c2_kb_b;
  real_T c2_lb_y;
  int32_T c2_i16;
  real_T c2_c_hoistedGlobal[16];
  int32_T c2_i17;
  int32_T c2_i18;
  int32_T c2_i19;
  int32_T c2_i20;
  real_T c2_t_a[9];
  int32_T c2_i21;
  real_T c2_lb_b[3];
  int32_T c2_i22;
  real_T c2_mb_y[3];
  int32_T c2_i23;
  int32_T c2_i24;
  int32_T c2_i25;
  real_T c2_dv4[16];
  int32_T c2_i26;
  int32_T c2_i27;
  int32_T c2_i28;
  int32_T c2_i29;
  int32_T c2_i30;
  real_T c2_u_a[16];
  int32_T c2_i31;
  real_T c2_mb_b[4];
  int32_T c2_i32;
  real_T c2_nb_y[4];
  int32_T c2_i33;
  int32_T c2_i34;
  int32_T c2_i35;
  int32_T c2_i36;
  int32_T c2_i37;
  int32_T c2_i38;
  int32_T c2_i39;
  real_T c2_d_hoistedGlobal[16];
  int32_T c2_i40;
  real_T c2_ob_y;
  real_T c2_scale;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_x;
  real_T c2_b_x;
  real_T c2_absxk;
  real_T c2_b_t;
  int32_T c2_i41;
  real_T c2_B;
  real_T c2_pb_y;
  real_T c2_qb_y;
  int32_T c2_i42;
  int32_T c2_i43;
  int32_T c2_i44;
  int32_T c2_i45;
  real_T *c2_b_agsamp;
  real_T *c2_c_t;
  real_T (*c2_rb_y)[16];
  real_T (*c2_b_g)[3];
  real_T (*c2_v_a)[3];
  c2_c_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c2_b_agsamp = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c2_b_g = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c2_rb_y = (real_T (*)[16])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_v_a = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *c2_b_agsamp;
  c2_b_hoistedGlobal = *c2_c_t;
  for (c2_i9 = 0; c2_i9 < 3; c2_i9++) {
    c2_a[c2_i9] = (*c2_v_a)[c2_i9];
  }

  for (c2_i10 = 0; c2_i10 < 3; c2_i10++) {
    c2_g[c2_i10] = (*c2_b_g)[c2_i10];
  }

  c2_agsamp = c2_hoistedGlobal;
  c2_t = c2_b_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 18U, 19U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Xdot, 0U, c2_e_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Ts, 1U, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_q, MAX_uint32_T, c2_j_sf_marshallOut,
    c2_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_DCM, 3U, c2_i_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_p, 4U, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_r, 5U, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_qdotM, 6U, c2_h_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_q, MAX_uint32_T,
    c2_f_sf_marshallOut, c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 7U, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 8U, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_a, 9U, c2_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_g, 10U, c2_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_agsamp, 11U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_t, 12U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_y, 13U, c2_e_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_P, 14U,
    c2_d_sf_marshallOut, c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_X, 15U,
    c2_c_sf_marshallOut, c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_oldagsamp, 16U,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_oldt, 17U,
    c2_sf_marshallOut, c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 7);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c2_oldt_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 8);
    chartInstance->c2_oldt = 0.0;
    chartInstance->c2_oldt_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 10);
  if (CV_EML_IF(0, 1, 1, !chartInstance->c2_oldagsamp_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 11);
    chartInstance->c2_oldagsamp = 0.0;
    chartInstance->c2_oldagsamp_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 13);
  if (CV_EML_IF(0, 1, 2, !chartInstance->c2_X_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 14);
    for (c2_i11 = 0; c2_i11 < 16; c2_i11++) {
      chartInstance->c2_X[c2_i11] = c2_dv3[c2_i11];
    }

    chartInstance->c2_X_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 16);
  if (CV_EML_IF(0, 1, 3, !chartInstance->c2_P_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 17);
    for (c2_i12 = 0; c2_i12 < 256; c2_i12++) {
      chartInstance->c2_P[c2_i12] = 0.0;
    }

    chartInstance->c2_P_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 20);
  for (c2_i13 = 0; c2_i13 < 16; c2_i13++) {
    c2_Xdot[c2_i13] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 22);
  if (CV_EML_IF(0, 1, 4, c2_agsamp != chartInstance->c2_oldagsamp)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 23);
    chartInstance->c2_oldagsamp = c2_agsamp;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 24);
    c2_Ts = c2_t - chartInstance->c2_oldt;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 25);
    chartInstance->c2_oldt = c2_t;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
    for (c2_i14 = 0; c2_i14 < 3; c2_i14++) {
      c2_Xdot[c2_i14] = chartInstance->c2_X[c2_i14 + 3];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 31);
    for (c2_i15 = 0; c2_i15 < 4; c2_i15++) {
      c2_q[c2_i15] = chartInstance->c2_X[c2_i15 + 6];
    }

    _SFD_SYMBOL_SWITCH(2U, 2U);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 33);
    c2_b = c2_q[2];
    c2_b_y = 2.0 * c2_b;
    c2_b_a = c2_b_y;
    c2_b_b = c2_q[2];
    c2_c_y = c2_b_a * c2_b_b;
    c2_c_b = c2_q[3];
    c2_d_y = 2.0 * c2_c_b;
    c2_c_a = c2_d_y;
    c2_d_b = c2_q[3];
    c2_e_y = c2_c_a * c2_d_b;
    c2_e_b = c2_q[1];
    c2_f_y = 2.0 * c2_e_b;
    c2_d_a = c2_f_y;
    c2_f_b = c2_q[2];
    c2_g_y = c2_d_a * c2_f_b;
    c2_g_b = c2_q[3];
    c2_h_y = 2.0 * c2_g_b;
    c2_e_a = c2_h_y;
    c2_h_b = c2_q[0];
    c2_i_y = c2_e_a * c2_h_b;
    c2_i_b = c2_q[1];
    c2_j_y = 2.0 * c2_i_b;
    c2_f_a = c2_j_y;
    c2_j_b = c2_q[3];
    c2_k_y = c2_f_a * c2_j_b;
    c2_k_b = c2_q[2];
    c2_l_y = 2.0 * c2_k_b;
    c2_g_a = c2_l_y;
    c2_l_b = c2_q[0];
    c2_m_y = c2_g_a * c2_l_b;
    c2_m_b = c2_q[1];
    c2_n_y = 2.0 * c2_m_b;
    c2_h_a = c2_n_y;
    c2_n_b = c2_q[2];
    c2_o_y = c2_h_a * c2_n_b;
    c2_o_b = c2_q[3];
    c2_p_y = 2.0 * c2_o_b;
    c2_i_a = c2_p_y;
    c2_p_b = c2_q[0];
    c2_q_y = c2_i_a * c2_p_b;
    c2_q_b = c2_q[1];
    c2_r_y = 2.0 * c2_q_b;
    c2_j_a = c2_r_y;
    c2_r_b = c2_q[1];
    c2_s_y = c2_j_a * c2_r_b;
    c2_s_b = c2_q[3];
    c2_t_y = 2.0 * c2_s_b;
    c2_k_a = c2_t_y;
    c2_t_b = c2_q[3];
    c2_u_y = c2_k_a * c2_t_b;
    c2_u_b = c2_q[2];
    c2_v_y = 2.0 * c2_u_b;
    c2_l_a = c2_v_y;
    c2_v_b = c2_q[3];
    c2_w_y = c2_l_a * c2_v_b;
    c2_w_b = c2_q[1];
    c2_x_y = 2.0 * c2_w_b;
    c2_m_a = c2_x_y;
    c2_x_b = c2_q[0];
    c2_y_y = c2_m_a * c2_x_b;
    c2_y_b = c2_q[1];
    c2_ab_y = 2.0 * c2_y_b;
    c2_n_a = c2_ab_y;
    c2_ab_b = c2_q[3];
    c2_bb_y = c2_n_a * c2_ab_b;
    c2_bb_b = c2_q[2];
    c2_cb_y = 2.0 * c2_bb_b;
    c2_o_a = c2_cb_y;
    c2_cb_b = c2_q[0];
    c2_db_y = c2_o_a * c2_cb_b;
    c2_db_b = c2_q[2];
    c2_eb_y = 2.0 * c2_db_b;
    c2_p_a = c2_eb_y;
    c2_eb_b = c2_q[3];
    c2_fb_y = c2_p_a * c2_eb_b;
    c2_fb_b = c2_q[1];
    c2_gb_y = 2.0 * c2_fb_b;
    c2_q_a = c2_gb_y;
    c2_gb_b = c2_q[0];
    c2_hb_y = c2_q_a * c2_gb_b;
    c2_hb_b = c2_q[1];
    c2_ib_y = 2.0 * c2_hb_b;
    c2_r_a = c2_ib_y;
    c2_ib_b = c2_q[1];
    c2_jb_y = c2_r_a * c2_ib_b;
    c2_jb_b = c2_q[2];
    c2_kb_y = 2.0 * c2_jb_b;
    c2_s_a = c2_kb_y;
    c2_kb_b = c2_q[2];
    c2_lb_y = c2_s_a * c2_kb_b;
    c2_DCM[0] = (1.0 - c2_c_y) - c2_e_y;
    c2_DCM[3] = c2_g_y + c2_i_y;
    c2_DCM[6] = c2_k_y - c2_m_y;
    c2_DCM[1] = c2_o_y - c2_q_y;
    c2_DCM[4] = (1.0 - c2_s_y) - c2_u_y;
    c2_DCM[7] = c2_w_y + c2_y_y;
    c2_DCM[2] = c2_bb_y + c2_db_y;
    c2_DCM[5] = c2_fb_y - c2_hb_y;
    c2_DCM[8] = (1.0 - c2_jb_y) - c2_lb_y;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 38);
    for (c2_i16 = 0; c2_i16 < 16; c2_i16++) {
      c2_c_hoistedGlobal[c2_i16] = chartInstance->c2_X[c2_i16];
    }

    c2_i17 = 0;
    for (c2_i18 = 0; c2_i18 < 3; c2_i18++) {
      c2_i19 = 0;
      for (c2_i20 = 0; c2_i20 < 3; c2_i20++) {
        c2_t_a[c2_i20 + c2_i17] = c2_DCM[c2_i19 + c2_i18];
        c2_i19 += 3;
      }

      c2_i17 += 3;
    }

    for (c2_i21 = 0; c2_i21 < 3; c2_i21++) {
      c2_lb_b[c2_i21] = c2_a[c2_i21] - c2_c_hoistedGlobal[c2_i21 + 10];
    }

    c2_eml_scalar_eg(chartInstance);
    c2_eml_scalar_eg(chartInstance);
    for (c2_i22 = 0; c2_i22 < 3; c2_i22++) {
      c2_mb_y[c2_i22] = 0.0;
      c2_i23 = 0;
      for (c2_i24 = 0; c2_i24 < 3; c2_i24++) {
        c2_mb_y[c2_i22] += c2_t_a[c2_i23 + c2_i22] * c2_lb_b[c2_i24];
        c2_i23 += 3;
      }
    }

    for (c2_i25 = 0; c2_i25 < 3; c2_i25++) {
      c2_Xdot[c2_i25 + 3] = c2_mb_y[c2_i25];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 39);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 42);
    c2_p = c2_g[0] - chartInstance->c2_X[13];
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
    c2_b_q = c2_g[1] - chartInstance->c2_X[14];
    _SFD_SYMBOL_SWITCH(2U, 7U);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 44);
    c2_r = c2_g[2] - chartInstance->c2_X[15];
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 46);
    c2_dv4[0] = 0.0;
    c2_dv4[4] = -c2_p;
    c2_dv4[8] = -c2_b_q;
    c2_dv4[12] = -c2_r;
    c2_dv4[1] = c2_p;
    c2_dv4[5] = 0.0;
    c2_dv4[9] = c2_r;
    c2_dv4[13] = -c2_b_q;
    c2_dv4[2] = c2_b_q;
    c2_dv4[6] = -c2_r;
    c2_dv4[10] = 0.0;
    c2_dv4[14] = c2_p;
    c2_dv4[3] = c2_r;
    c2_dv4[7] = c2_b_q;
    c2_dv4[11] = -c2_p;
    c2_dv4[15] = 0.0;
    c2_i26 = 0;
    for (c2_i27 = 0; c2_i27 < 4; c2_i27++) {
      for (c2_i28 = 0; c2_i28 < 4; c2_i28++) {
        c2_qdotM[c2_i28 + c2_i26] = 0.5 * c2_dv4[c2_i28 + c2_i26];
      }

      c2_i26 += 4;
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 52);
    for (c2_i29 = 0; c2_i29 < 16; c2_i29++) {
      c2_c_hoistedGlobal[c2_i29] = chartInstance->c2_X[c2_i29];
    }

    for (c2_i30 = 0; c2_i30 < 16; c2_i30++) {
      c2_u_a[c2_i30] = c2_qdotM[c2_i30];
    }

    for (c2_i31 = 0; c2_i31 < 4; c2_i31++) {
      c2_mb_b[c2_i31] = c2_c_hoistedGlobal[c2_i31 + 6];
    }

    c2_b_eml_scalar_eg(chartInstance);
    c2_b_eml_scalar_eg(chartInstance);
    for (c2_i32 = 0; c2_i32 < 4; c2_i32++) {
      c2_nb_y[c2_i32] = 0.0;
      c2_i33 = 0;
      for (c2_i34 = 0; c2_i34 < 4; c2_i34++) {
        c2_nb_y[c2_i32] += c2_u_a[c2_i33 + c2_i32] * c2_mb_b[c2_i34];
        c2_i33 += 4;
      }
    }

    for (c2_i35 = 0; c2_i35 < 4; c2_i35++) {
      c2_Xdot[c2_i35 + 6] = c2_nb_y[c2_i35];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 55);
    for (c2_i36 = 0; c2_i36 < 6; c2_i36++) {
      c2_Xdot[c2_i36 + 10] = 0.0;
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 57);
    for (c2_i37 = 0; c2_i37 < 16; c2_i37++) {
      chartInstance->c2_X[c2_i37] += c2_Xdot[c2_i37] * c2_Ts;
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 58);
    for (c2_i38 = 0; c2_i38 < 16; c2_i38++) {
      c2_c_hoistedGlobal[c2_i38] = chartInstance->c2_X[c2_i38];
    }

    for (c2_i39 = 0; c2_i39 < 16; c2_i39++) {
      c2_d_hoistedGlobal[c2_i39] = chartInstance->c2_X[c2_i39];
    }

    for (c2_i40 = 0; c2_i40 < 4; c2_i40++) {
      c2_mb_b[c2_i40] = c2_d_hoistedGlobal[c2_i40 + 6];
    }

    c2_ob_y = 0.0;
    c2_scale = 2.2250738585072014E-308;
    for (c2_k = 1; c2_k < 5; c2_k++) {
      c2_b_k = c2_k;
      c2_x = c2_mb_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
        ("", (real_T)c2_b_k), 1, 4, 1, 0) - 1];
      c2_b_x = c2_x;
      c2_absxk = muDoubleScalarAbs(c2_b_x);
      if (c2_absxk > c2_scale) {
        c2_b_t = c2_scale / c2_absxk;
        c2_ob_y = 1.0 + c2_ob_y * c2_b_t * c2_b_t;
        c2_scale = c2_absxk;
      } else {
        c2_b_t = c2_absxk / c2_scale;
        c2_ob_y += c2_b_t * c2_b_t;
      }
    }

    c2_ob_y = c2_scale * muDoubleScalarSqrt(c2_ob_y);
    for (c2_i41 = 0; c2_i41 < 4; c2_i41++) {
      c2_mb_b[c2_i41] = c2_c_hoistedGlobal[c2_i41 + 6];
    }

    c2_B = c2_ob_y;
    c2_pb_y = c2_B;
    c2_qb_y = c2_pb_y;
    for (c2_i42 = 0; c2_i42 < 4; c2_i42++) {
      c2_mb_b[c2_i42] /= c2_qb_y;
    }

    for (c2_i43 = 0; c2_i43 < 4; c2_i43++) {
      chartInstance->c2_X[c2_i43 + 6] = c2_mb_b[c2_i43];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 62);
  for (c2_i44 = 0; c2_i44 < 16; c2_i44++) {
    c2_y[c2_i44] = chartInstance->c2_X[c2_i44];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -62);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i45 = 0; c2_i45 < 16; c2_i45++) {
    (*c2_rb_y)[c2_i45] = c2_y[c2_i45];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_quadtestmodel(SFc2_quadtestmodelInstanceStruct
  *chartInstance)
{
}

static void registerMessagesc2_quadtestmodel(SFc2_quadtestmodelInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  if (!chartInstance->c2_oldt_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_b_oldt, const char_T *c2_identifier)
{
  real_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_oldt), &c2_thisId);
  sf_mex_destroy(&c2_b_oldt);
  return c2_y;
}

static real_T c2_b_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_oldt_not_empty = FALSE;
  } else {
    chartInstance->c2_oldt_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
    c2_y = c2_d0;
  }

  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_oldt;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_b_oldt = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_oldt), &c2_thisId);
  sf_mex_destroy(&c2_b_oldt);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  if (!chartInstance->c2_oldagsamp_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_c_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_b_oldagsamp, const char_T *c2_identifier)
{
  real_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_oldagsamp),
    &c2_thisId);
  sf_mex_destroy(&c2_b_oldagsamp);
  return c2_y;
}

static real_T c2_d_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d1;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_oldagsamp_not_empty = FALSE;
  } else {
    chartInstance->c2_oldagsamp_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d1, 1, 0, 0U, 0, 0U, 0);
    c2_y = c2_d1;
  }

  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_oldagsamp;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_b_oldagsamp = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_oldagsamp),
    &c2_thisId);
  sf_mex_destroy(&c2_b_oldagsamp);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i46;
  real_T c2_b_inData[16];
  int32_T c2_i47;
  real_T c2_u[16];
  const mxArray *c2_y = NULL;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i46 = 0; c2_i46 < 16; c2_i46++) {
    c2_b_inData[c2_i46] = (*(real_T (*)[16])c2_inData)[c2_i46];
  }

  for (c2_i47 = 0; c2_i47 < 16; c2_i47++) {
    c2_u[c2_i47] = c2_b_inData[c2_i47];
  }

  c2_y = NULL;
  if (!chartInstance->c2_X_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 16), FALSE);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_e_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_b_X, const char_T *c2_identifier, real_T
  c2_y[16])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_X), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_X);
}

static void c2_f_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[16])
{
  real_T c2_dv5[16];
  int32_T c2_i48;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_X_not_empty = FALSE;
  } else {
    chartInstance->c2_X_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv5, 1, 0, 0U, 1, 0U, 1, 16);
    for (c2_i48 = 0; c2_i48 < 16; c2_i48++) {
      c2_y[c2_i48] = c2_dv5[c2_i48];
    }
  }

  sf_mex_destroy(&c2_u);
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_X;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[16];
  int32_T c2_i49;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_b_X = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_X), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_X);
  for (c2_i49 = 0; c2_i49 < 16; c2_i49++) {
    (*(real_T (*)[16])c2_outData)[c2_i49] = c2_y[c2_i49];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i50;
  int32_T c2_i51;
  int32_T c2_i52;
  real_T c2_b_inData[256];
  int32_T c2_i53;
  int32_T c2_i54;
  int32_T c2_i55;
  real_T c2_u[256];
  const mxArray *c2_y = NULL;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i50 = 0;
  for (c2_i51 = 0; c2_i51 < 16; c2_i51++) {
    for (c2_i52 = 0; c2_i52 < 16; c2_i52++) {
      c2_b_inData[c2_i52 + c2_i50] = (*(real_T (*)[256])c2_inData)[c2_i52 +
        c2_i50];
    }

    c2_i50 += 16;
  }

  c2_i53 = 0;
  for (c2_i54 = 0; c2_i54 < 16; c2_i54++) {
    for (c2_i55 = 0; c2_i55 < 16; c2_i55++) {
      c2_u[c2_i55 + c2_i53] = c2_b_inData[c2_i55 + c2_i53];
    }

    c2_i53 += 16;
  }

  c2_y = NULL;
  if (!chartInstance->c2_P_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 16, 16),
                  FALSE);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_g_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_b_P, const char_T *c2_identifier, real_T
  c2_y[256])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_P), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_P);
}

static void c2_h_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[256])
{
  real_T c2_dv6[256];
  int32_T c2_i56;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_P_not_empty = FALSE;
  } else {
    chartInstance->c2_P_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv6, 1, 0, 0U, 1, 0U, 2, 16,
                  16);
    for (c2_i56 = 0; c2_i56 < 256; c2_i56++) {
      c2_y[c2_i56] = c2_dv6[c2_i56];
    }
  }

  sf_mex_destroy(&c2_u);
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_P;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[256];
  int32_T c2_i57;
  int32_T c2_i58;
  int32_T c2_i59;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_b_P = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_P), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_P);
  c2_i57 = 0;
  for (c2_i58 = 0; c2_i58 < 16; c2_i58++) {
    for (c2_i59 = 0; c2_i59 < 16; c2_i59++) {
      (*(real_T (*)[256])c2_outData)[c2_i59 + c2_i57] = c2_y[c2_i59 + c2_i57];
    }

    c2_i57 += 16;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i60;
  real_T c2_b_inData[16];
  int32_T c2_i61;
  real_T c2_u[16];
  const mxArray *c2_y = NULL;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i60 = 0; c2_i60 < 16; c2_i60++) {
    c2_b_inData[c2_i60] = (*(real_T (*)[16])c2_inData)[c2_i60];
  }

  for (c2_i61 = 0; c2_i61 < 16; c2_i61++) {
    c2_u[c2_i61] = c2_b_inData[c2_i61];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 16), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_i_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_y, const char_T *c2_identifier, real_T
  c2_b_y[16])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_y), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_y);
}

static void c2_j_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[16])
{
  real_T c2_dv7[16];
  int32_T c2_i62;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv7, 1, 0, 0U, 1, 0U, 1, 16);
  for (c2_i62 = 0; c2_i62 < 16; c2_i62++) {
    c2_y[c2_i62] = c2_dv7[c2_i62];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_y;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[16];
  int32_T c2_i63;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_y = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_y), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_y);
  for (c2_i63 = 0; c2_i63 < 16; c2_i63++) {
    (*(real_T (*)[16])c2_outData)[c2_i63] = c2_b_y[c2_i63];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i64;
  real_T c2_b_inData[3];
  int32_T c2_i65;
  real_T c2_u[3];
  const mxArray *c2_y = NULL;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i64 = 0; c2_i64 < 3; c2_i64++) {
    c2_b_inData[c2_i64] = (*(real_T (*)[3])c2_inData)[c2_i64];
  }

  for (c2_i65 = 0; c2_i65 < 3; c2_i65++) {
    c2_u[c2_i65] = c2_b_inData[c2_i65];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_k_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d2;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d2, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d2;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i66;
  int32_T c2_i67;
  int32_T c2_i68;
  real_T c2_b_inData[16];
  int32_T c2_i69;
  int32_T c2_i70;
  int32_T c2_i71;
  real_T c2_u[16];
  const mxArray *c2_y = NULL;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i66 = 0;
  for (c2_i67 = 0; c2_i67 < 4; c2_i67++) {
    for (c2_i68 = 0; c2_i68 < 4; c2_i68++) {
      c2_b_inData[c2_i68 + c2_i66] = (*(real_T (*)[16])c2_inData)[c2_i68 +
        c2_i66];
    }

    c2_i66 += 4;
  }

  c2_i69 = 0;
  for (c2_i70 = 0; c2_i70 < 4; c2_i70++) {
    for (c2_i71 = 0; c2_i71 < 4; c2_i71++) {
      c2_u[c2_i71 + c2_i69] = c2_b_inData[c2_i71 + c2_i69];
    }

    c2_i69 += 4;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 4, 4), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_l_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[16])
{
  real_T c2_dv8[16];
  int32_T c2_i72;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv8, 1, 0, 0U, 1, 0U, 2, 4, 4);
  for (c2_i72 = 0; c2_i72 < 16; c2_i72++) {
    c2_y[c2_i72] = c2_dv8[c2_i72];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_qdotM;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[16];
  int32_T c2_i73;
  int32_T c2_i74;
  int32_T c2_i75;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_qdotM = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_qdotM), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_qdotM);
  c2_i73 = 0;
  for (c2_i74 = 0; c2_i74 < 4; c2_i74++) {
    for (c2_i75 = 0; c2_i75 < 4; c2_i75++) {
      (*(real_T (*)[16])c2_outData)[c2_i75 + c2_i73] = c2_y[c2_i75 + c2_i73];
    }

    c2_i73 += 4;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i76;
  int32_T c2_i77;
  int32_T c2_i78;
  real_T c2_b_inData[9];
  int32_T c2_i79;
  int32_T c2_i80;
  int32_T c2_i81;
  real_T c2_u[9];
  const mxArray *c2_y = NULL;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i76 = 0;
  for (c2_i77 = 0; c2_i77 < 3; c2_i77++) {
    for (c2_i78 = 0; c2_i78 < 3; c2_i78++) {
      c2_b_inData[c2_i78 + c2_i76] = (*(real_T (*)[9])c2_inData)[c2_i78 + c2_i76];
    }

    c2_i76 += 3;
  }

  c2_i79 = 0;
  for (c2_i80 = 0; c2_i80 < 3; c2_i80++) {
    for (c2_i81 = 0; c2_i81 < 3; c2_i81++) {
      c2_u[c2_i81 + c2_i79] = c2_b_inData[c2_i81 + c2_i79];
    }

    c2_i79 += 3;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_m_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[9])
{
  real_T c2_dv9[9];
  int32_T c2_i82;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv9, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c2_i82 = 0; c2_i82 < 9; c2_i82++) {
    c2_y[c2_i82] = c2_dv9[c2_i82];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_DCM;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[9];
  int32_T c2_i83;
  int32_T c2_i84;
  int32_T c2_i85;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_DCM = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_DCM), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_DCM);
  c2_i83 = 0;
  for (c2_i84 = 0; c2_i84 < 3; c2_i84++) {
    for (c2_i85 = 0; c2_i85 < 3; c2_i85++) {
      (*(real_T (*)[9])c2_outData)[c2_i85 + c2_i83] = c2_y[c2_i85 + c2_i83];
    }

    c2_i83 += 3;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i86;
  real_T c2_b_inData[4];
  int32_T c2_i87;
  real_T c2_u[4];
  const mxArray *c2_y = NULL;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i86 = 0; c2_i86 < 4; c2_i86++) {
    c2_b_inData[c2_i86] = (*(real_T (*)[4])c2_inData)[c2_i86];
  }

  for (c2_i87 = 0; c2_i87 < 4; c2_i87++) {
    c2_u[c2_i87] = c2_b_inData[c2_i87];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_n_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[4])
{
  real_T c2_dv10[4];
  int32_T c2_i88;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv10, 1, 0, 0U, 1, 0U, 1, 4);
  for (c2_i88 = 0; c2_i88 < 4; c2_i88++) {
    c2_y[c2_i88] = c2_dv10[c2_i88];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_q;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[4];
  int32_T c2_i89;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_q = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_q), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_q);
  for (c2_i89 = 0; c2_i89 < 4; c2_i89++) {
    (*(real_T (*)[4])c2_outData)[c2_i89] = c2_y[c2_i89];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_quadtestmodel_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo;
  c2_ResolvedFunctionInfo c2_info[33];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i90;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  c2_info_helper(c2_info);
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 33), FALSE);
  for (c2_i90 = 0; c2_i90 < 33; c2_i90++) {
    c2_r0 = &c2_info[c2_i90];
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->context)), "context", "nameCaptureInfo",
                    c2_i90);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c2_r0->name)), "name", "nameCaptureInfo", c2_i90);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c2_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c2_i90);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->resolved)), "resolved", "nameCaptureInfo",
                    c2_i90);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c2_i90);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c2_i90);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c2_i90);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c2_i90);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[33])
{
  c2_info[0].context = "";
  c2_info[0].name = "mtimes";
  c2_info[0].dominantType = "double";
  c2_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[0].fileTimeLo = 1289523292U;
  c2_info[0].fileTimeHi = 0U;
  c2_info[0].mFileTimeLo = 0U;
  c2_info[0].mFileTimeHi = 0U;
  c2_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[1].name = "eml_index_class";
  c2_info[1].dominantType = "";
  c2_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[1].fileTimeLo = 1323174178U;
  c2_info[1].fileTimeHi = 0U;
  c2_info[1].mFileTimeLo = 0U;
  c2_info[1].mFileTimeHi = 0U;
  c2_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[2].name = "eml_scalar_eg";
  c2_info[2].dominantType = "double";
  c2_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[2].fileTimeLo = 1286822396U;
  c2_info[2].fileTimeHi = 0U;
  c2_info[2].mFileTimeLo = 0U;
  c2_info[2].mFileTimeHi = 0U;
  c2_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[3].name = "eml_xgemm";
  c2_info[3].dominantType = "char";
  c2_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c2_info[3].fileTimeLo = 1299080372U;
  c2_info[3].fileTimeHi = 0U;
  c2_info[3].mFileTimeLo = 0U;
  c2_info[3].mFileTimeHi = 0U;
  c2_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c2_info[4].name = "eml_blas_inline";
  c2_info[4].dominantType = "";
  c2_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[4].fileTimeLo = 1299080368U;
  c2_info[4].fileTimeHi = 0U;
  c2_info[4].mFileTimeLo = 0U;
  c2_info[4].mFileTimeHi = 0U;
  c2_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c2_info[5].name = "mtimes";
  c2_info[5].dominantType = "double";
  c2_info[5].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[5].fileTimeLo = 1289523292U;
  c2_info[5].fileTimeHi = 0U;
  c2_info[5].mFileTimeLo = 0U;
  c2_info[5].mFileTimeHi = 0U;
  c2_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c2_info[6].name = "eml_index_class";
  c2_info[6].dominantType = "";
  c2_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[6].fileTimeLo = 1323174178U;
  c2_info[6].fileTimeHi = 0U;
  c2_info[6].mFileTimeLo = 0U;
  c2_info[6].mFileTimeHi = 0U;
  c2_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c2_info[7].name = "eml_scalar_eg";
  c2_info[7].dominantType = "double";
  c2_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[7].fileTimeLo = 1286822396U;
  c2_info[7].fileTimeHi = 0U;
  c2_info[7].mFileTimeLo = 0U;
  c2_info[7].mFileTimeHi = 0U;
  c2_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c2_info[8].name = "eml_refblas_xgemm";
  c2_info[8].dominantType = "char";
  c2_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c2_info[8].fileTimeLo = 1299080374U;
  c2_info[8].fileTimeHi = 0U;
  c2_info[8].mFileTimeLo = 0U;
  c2_info[8].mFileTimeHi = 0U;
  c2_info[9].context = "";
  c2_info[9].name = "norm";
  c2_info[9].dominantType = "double";
  c2_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c2_info[9].fileTimeLo = 1336525694U;
  c2_info[9].fileTimeHi = 0U;
  c2_info[9].mFileTimeLo = 0U;
  c2_info[9].mFileTimeHi = 0U;
  c2_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c2_info[10].name = "eml_index_class";
  c2_info[10].dominantType = "";
  c2_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[10].fileTimeLo = 1323174178U;
  c2_info[10].fileTimeHi = 0U;
  c2_info[10].mFileTimeLo = 0U;
  c2_info[10].mFileTimeHi = 0U;
  c2_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c2_info[11].name = "eml_xnrm2";
  c2_info[11].dominantType = "double";
  c2_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c2_info[11].fileTimeLo = 1299080376U;
  c2_info[11].fileTimeHi = 0U;
  c2_info[11].mFileTimeLo = 0U;
  c2_info[11].mFileTimeHi = 0U;
  c2_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c2_info[12].name = "eml_blas_inline";
  c2_info[12].dominantType = "";
  c2_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[12].fileTimeLo = 1299080368U;
  c2_info[12].fileTimeHi = 0U;
  c2_info[12].mFileTimeLo = 0U;
  c2_info[12].mFileTimeHi = 0U;
  c2_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c2_info[13].name = "eml_index_class";
  c2_info[13].dominantType = "";
  c2_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[13].fileTimeLo = 1323174178U;
  c2_info[13].fileTimeHi = 0U;
  c2_info[13].mFileTimeLo = 0U;
  c2_info[13].mFileTimeHi = 0U;
  c2_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c2_info[14].name = "eml_refblas_xnrm2";
  c2_info[14].dominantType = "double";
  c2_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[14].fileTimeLo = 1299080384U;
  c2_info[14].fileTimeHi = 0U;
  c2_info[14].mFileTimeLo = 0U;
  c2_info[14].mFileTimeHi = 0U;
  c2_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[15].name = "realmin";
  c2_info[15].dominantType = "char";
  c2_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c2_info[15].fileTimeLo = 1307654842U;
  c2_info[15].fileTimeHi = 0U;
  c2_info[15].mFileTimeLo = 0U;
  c2_info[15].mFileTimeHi = 0U;
  c2_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c2_info[16].name = "eml_realmin";
  c2_info[16].dominantType = "char";
  c2_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c2_info[16].fileTimeLo = 1307654844U;
  c2_info[16].fileTimeHi = 0U;
  c2_info[16].mFileTimeLo = 0U;
  c2_info[16].mFileTimeHi = 0U;
  c2_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c2_info[17].name = "eml_float_model";
  c2_info[17].dominantType = "char";
  c2_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c2_info[17].fileTimeLo = 1326731596U;
  c2_info[17].fileTimeHi = 0U;
  c2_info[17].mFileTimeLo = 0U;
  c2_info[17].mFileTimeHi = 0U;
  c2_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[18].name = "eml_index_class";
  c2_info[18].dominantType = "";
  c2_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[18].fileTimeLo = 1323174178U;
  c2_info[18].fileTimeHi = 0U;
  c2_info[18].mFileTimeLo = 0U;
  c2_info[18].mFileTimeHi = 0U;
  c2_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[19].name = "eml_index_minus";
  c2_info[19].dominantType = "double";
  c2_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[19].fileTimeLo = 1286822378U;
  c2_info[19].fileTimeHi = 0U;
  c2_info[19].mFileTimeLo = 0U;
  c2_info[19].mFileTimeHi = 0U;
  c2_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[20].name = "eml_index_class";
  c2_info[20].dominantType = "";
  c2_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[20].fileTimeLo = 1323174178U;
  c2_info[20].fileTimeHi = 0U;
  c2_info[20].mFileTimeLo = 0U;
  c2_info[20].mFileTimeHi = 0U;
  c2_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[21].name = "eml_index_times";
  c2_info[21].dominantType = "coder.internal.indexInt";
  c2_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[21].fileTimeLo = 1286822380U;
  c2_info[21].fileTimeHi = 0U;
  c2_info[21].mFileTimeLo = 0U;
  c2_info[21].mFileTimeHi = 0U;
  c2_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[22].name = "eml_index_class";
  c2_info[22].dominantType = "";
  c2_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[22].fileTimeLo = 1323174178U;
  c2_info[22].fileTimeHi = 0U;
  c2_info[22].mFileTimeLo = 0U;
  c2_info[22].mFileTimeHi = 0U;
  c2_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[23].name = "eml_index_plus";
  c2_info[23].dominantType = "coder.internal.indexInt";
  c2_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[23].fileTimeLo = 1286822378U;
  c2_info[23].fileTimeHi = 0U;
  c2_info[23].mFileTimeLo = 0U;
  c2_info[23].mFileTimeHi = 0U;
  c2_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[24].name = "eml_index_class";
  c2_info[24].dominantType = "";
  c2_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[24].fileTimeLo = 1323174178U;
  c2_info[24].fileTimeHi = 0U;
  c2_info[24].mFileTimeLo = 0U;
  c2_info[24].mFileTimeHi = 0U;
  c2_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[25].name = "eml_int_forloop_overflow_check";
  c2_info[25].dominantType = "";
  c2_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[25].fileTimeLo = 1346513940U;
  c2_info[25].fileTimeHi = 0U;
  c2_info[25].mFileTimeLo = 0U;
  c2_info[25].mFileTimeHi = 0U;
  c2_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c2_info[26].name = "intmax";
  c2_info[26].dominantType = "char";
  c2_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[26].fileTimeLo = 1311258916U;
  c2_info[26].fileTimeHi = 0U;
  c2_info[26].mFileTimeLo = 0U;
  c2_info[26].mFileTimeHi = 0U;
  c2_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[27].name = "abs";
  c2_info[27].dominantType = "double";
  c2_info[27].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[27].fileTimeLo = 1343833966U;
  c2_info[27].fileTimeHi = 0U;
  c2_info[27].mFileTimeLo = 0U;
  c2_info[27].mFileTimeHi = 0U;
  c2_info[28].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[28].name = "eml_scalar_abs";
  c2_info[28].dominantType = "double";
  c2_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c2_info[28].fileTimeLo = 1286822312U;
  c2_info[28].fileTimeHi = 0U;
  c2_info[28].mFileTimeLo = 0U;
  c2_info[28].mFileTimeHi = 0U;
  c2_info[29].context = "";
  c2_info[29].name = "mrdivide";
  c2_info[29].dominantType = "double";
  c2_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[29].fileTimeLo = 1357955148U;
  c2_info[29].fileTimeHi = 0U;
  c2_info[29].mFileTimeLo = 1319733566U;
  c2_info[29].mFileTimeHi = 0U;
  c2_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[30].name = "rdivide";
  c2_info[30].dominantType = "double";
  c2_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[30].fileTimeLo = 1346513988U;
  c2_info[30].fileTimeHi = 0U;
  c2_info[30].mFileTimeLo = 0U;
  c2_info[30].mFileTimeHi = 0U;
  c2_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[31].name = "eml_scalexp_compatible";
  c2_info[31].dominantType = "double";
  c2_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c2_info[31].fileTimeLo = 1286822396U;
  c2_info[31].fileTimeHi = 0U;
  c2_info[31].mFileTimeLo = 0U;
  c2_info[31].mFileTimeHi = 0U;
  c2_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[32].name = "eml_div";
  c2_info[32].dominantType = "double";
  c2_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c2_info[32].fileTimeLo = 1313351410U;
  c2_info[32].fileTimeHi = 0U;
  c2_info[32].mFileTimeLo = 0U;
  c2_info[32].mFileTimeHi = 0U;
}

static void c2_eml_scalar_eg(SFc2_quadtestmodelInstanceStruct *chartInstance)
{
}

static void c2_b_eml_scalar_eg(SFc2_quadtestmodelInstanceStruct *chartInstance)
{
}

static const mxArray *c2_k_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static int32_T c2_o_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i91;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i91, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i91;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_p_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_quadtestmodel, const char_T
  *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_q_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_quadtestmodel), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_quadtestmodel);
  return c2_y;
}

static uint8_T c2_q_emlrt_marshallIn(SFc2_quadtestmodelInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_quadtestmodelInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_quadtestmodel_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4068640189U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3477872025U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3957179316U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3503884497U);
}

mxArray *sf_c2_quadtestmodel_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("QYbLBtWzHXctwqt63DOgTB");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(16);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_quadtestmodel_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c2_quadtestmodel(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x6'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[4],M[0],T\"P\",S'l','i','p'{{M1x2[93 94],M[0],}}},{M[4],M[0],T\"X\",S'l','i','p'{{M1x2[95 96],M[0],}}},{M[4],M[0],T\"oldagsamp\",S'l','i','p'{{M1x2[97 106],M[0],}}},{M[4],M[0],T\"oldt\",S'l','i','p'{{M1x2[107 111],M[0],}}},{M[8],M[0],T\"is_active_c2_quadtestmodel\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 6, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_quadtestmodel_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_quadtestmodelInstanceStruct *chartInstance;
    chartInstance = (SFc2_quadtestmodelInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _quadtestmodelMachineNumber_,
           2,
           1,
           1,
           5,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_quadtestmodelMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_quadtestmodelMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _quadtestmodelMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"a");
          _SFD_SET_DATA_PROPS(1,2,0,1,"y");
          _SFD_SET_DATA_PROPS(2,1,1,0,"g");
          _SFD_SET_DATA_PROPS(3,1,1,0,"agsamp");
          _SFD_SET_DATA_PROPS(4,1,1,0,"t");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,5,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",33,-1,1224);
        _SFD_CV_INIT_EML_IF(0,1,0,112,128,-1,146);
        _SFD_CV_INIT_EML_IF(0,1,1,147,168,-1,191);
        _SFD_CV_INIT_EML_IF(0,1,2,192,205,-1,271);
        _SFD_CV_INIT_EML_IF(0,1,3,272,285,-1,308);
        _SFD_CV_INIT_EML_IF(0,1,4,331,353,-1,1216);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_g_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 16;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_e_sf_marshallOut,(MexInFcnForType)
            c2_e_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_g_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c2_agsamp;
          real_T *c2_t;
          real_T (*c2_a)[3];
          real_T (*c2_y)[16];
          real_T (*c2_g)[3];
          c2_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c2_agsamp = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c2_g = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c2_y = (real_T (*)[16])ssGetOutputPortSignal(chartInstance->S, 1);
          c2_a = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_a);
          _SFD_SET_DATA_VALUE_PTR(1U, *c2_y);
          _SFD_SET_DATA_VALUE_PTR(2U, *c2_g);
          _SFD_SET_DATA_VALUE_PTR(3U, c2_agsamp);
          _SFD_SET_DATA_VALUE_PTR(4U, c2_t);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _quadtestmodelMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "f8KUeLkmC03dtrQuB6NBNH";
}

static void sf_opaque_initialize_c2_quadtestmodel(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_quadtestmodelInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_quadtestmodel((SFc2_quadtestmodelInstanceStruct*)
    chartInstanceVar);
  initialize_c2_quadtestmodel((SFc2_quadtestmodelInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_quadtestmodel(void *chartInstanceVar)
{
  enable_c2_quadtestmodel((SFc2_quadtestmodelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_quadtestmodel(void *chartInstanceVar)
{
  disable_c2_quadtestmodel((SFc2_quadtestmodelInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_quadtestmodel(void *chartInstanceVar)
{
  sf_c2_quadtestmodel((SFc2_quadtestmodelInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_quadtestmodel(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_quadtestmodel
    ((SFc2_quadtestmodelInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_quadtestmodel();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c2_quadtestmodel(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_quadtestmodel();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_quadtestmodel((SFc2_quadtestmodelInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_quadtestmodel(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_quadtestmodel(S);
}

static void sf_opaque_set_sim_state_c2_quadtestmodel(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c2_quadtestmodel(S, st);
}

static void sf_opaque_terminate_c2_quadtestmodel(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_quadtestmodelInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_quadtestmodel_optimization_info();
    }

    finalize_c2_quadtestmodel((SFc2_quadtestmodelInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_quadtestmodel((SFc2_quadtestmodelInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_quadtestmodel(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_quadtestmodel((SFc2_quadtestmodelInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_quadtestmodel(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_quadtestmodel_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,2,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(4134241657U));
  ssSetChecksum1(S,(2543684910U));
  ssSetChecksum2(S,(3936383600U));
  ssSetChecksum3(S,(1638308188U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_quadtestmodel(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_quadtestmodel(SimStruct *S)
{
  SFc2_quadtestmodelInstanceStruct *chartInstance;
  chartInstance = (SFc2_quadtestmodelInstanceStruct *)utMalloc(sizeof
    (SFc2_quadtestmodelInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_quadtestmodelInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_quadtestmodel;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_quadtestmodel;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_quadtestmodel;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_quadtestmodel;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_quadtestmodel;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_quadtestmodel;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_quadtestmodel;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_quadtestmodel;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_quadtestmodel;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_quadtestmodel;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_quadtestmodel;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c2_quadtestmodel_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_quadtestmodel(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_quadtestmodel(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_quadtestmodel(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_quadtestmodel_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
