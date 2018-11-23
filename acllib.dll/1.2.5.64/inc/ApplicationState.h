#pragma once

enum ApplicationState { 
  USER_UNKNOWN  = -1,
  USER_OFFLINE  = 0,
  USER_ONLINE   = 1,
  USER_WORK     = 2,
  USER_BUSY     = 3,
  USER_DND      = 4,
  USER_AWAY     = 5,
  USER_LOSS_CONNECTION = 6,
  USER_HIDDEN   = 7
};
