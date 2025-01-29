/*
 * Copyright (c) 2024 Muhammad Haziq
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "drone_com.h"

//*
int main()
{
  Wifi wifi = Wifi();
  wifi.connect();

  startSocketServer();

  while(1)
  {
    k_msleep(1000);
  }

  return 0;
}
//*/
