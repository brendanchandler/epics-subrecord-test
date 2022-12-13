#include "caeventmask.h"
#include <callback.h>
#include <dbAccessDefs.h>
#include <dbStaticLib.h>
#include <dbUnitTest.h>
#include <epicsUnitTest.h>
#include <errlog.h>
#include <string>
#include <testMain.h>
#include <epicsThread.h>

extern "C" {
int testsub_registerRecordDeviceDriver(DBBASE *pbase);
}

void test_subrecord(void) {

  testdbPrepare();
  testdbReadDatabase("testsub.dbd", nullptr, nullptr);
  testsub_registerRecordDeviceDriver(pdbbase);

  testdbReadDatabase("../../Db/dbSubExample.db", 0, "user=bren");
  testIocInitOk();
    
  std::string proc{"bren:subExample.PROC"};
  testdbGetFieldEqual(proc.c_str(), DBF_UCHAR, 0);

  // Create a monitor to detect any further changes
  testMonitor *proc_monitor =
      testMonitorCreate(proc.c_str(), DBE_VALUE, 0);
  testOk1(proc_monitor != nullptr);

  testdbPutFieldOk(proc.c_str(), DBF_UCHAR, 1);
  errlogPrintf("Waiting for PROC to change to 1.\n");
  testMonitorWait(proc_monitor);

#if 0
  eltc(0);
  errlogPrintf("sync callbacks!\n");
  int const MAX_SYNC_CALLBACKS = 10000;
  for (int i = 0;
       i < MAX_SYNC_CALLBACKS && testMonitorCount(proc_monitor, 0) < 2; ++i) {
    testSyncCallback();
  }
  eltc(1);
#endif

  callbackQueueShow(0);

  errlogPrintf("Waiting for PROC to change to 0.\n");
  testMonitorWait(proc_monitor);
  testdbGetFieldEqual(proc.c_str(), DBF_UCHAR, 0);

  testMonitorDestroy(proc_monitor);

  testIocShutdownOk();
  testdbCleanup();
}

MAIN(mytestmain) {
  testPlan(0);
  test_subrecord();
  return testDone();
}
