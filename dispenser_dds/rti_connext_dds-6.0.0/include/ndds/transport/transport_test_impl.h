/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)transport_test_impl.h    generated by: makeheader    Thu Feb 28 22:11:54 2019
 *
 *		built from:	test_impl.ifc
 */

#ifndef transport_test_impl_h
#define transport_test_impl_h


#ifdef __cplusplus
    extern "C" {
#endif


  #define NDDS_TRANSPORT_TEST_SETTING_IOV_COMBINATION_COUNT_MAX (6)
  #define testM(index) (NDDS_TRANSPORT_TEST_SETTING_IOV_COMBINATION[index][0])
  #define testN(index) (NDDS_TRANSPORT_TEST_SETTING_IOV_COMBINATION[index][1])
  #define NDDS_TRANSPORT_TEST_SETTING_IOV_COUNT_MAX (32)
  #define NDDS_TRANSPORT_TEST_SETTING_BUFFER_SIZE_SMALL (32)
  #define NDDS_TRANSPORT_TEST_SETTING_BUFFER_SIZE_LARGE (1024)

extern int NDDS_TRANSPORT_TEST_SETTING_IOV_COMBINATION[
    NDDS_TRANSPORT_TEST_SETTING_IOV_COMBINATION_COUNT_MAX][2];

extern char NDDS_TRANSPORT_TESTER_SMALL_STORAGE[
    NDDS_TRANSPORT_TEST_SETTING_IOV_COUNT_MAX-1][
	NDDS_TRANSPORT_TEST_SETTING_BUFFER_SIZE_SMALL];

extern char NDDS_TRANSPORT_TESTER_LARGE_STORAGE[
    NDDS_TRANSPORT_TEST_SETTING_BUFFER_SIZE_LARGE];

extern char NDDS_TRANSPORT_TESTER_RECEIVE_STORAGE[
    NDDS_TRANSPORT_TEST_SETTING_BUFFER_SIZE_LARGE];

struct REDABuffer NDDS_TRANSPORT_TESTER_SEND_BUFFER[
    NDDS_TRANSPORT_TEST_SETTING_IOV_COUNT_MAX];


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* transport_test_impl_h */
